#include "modifyPage/modLocationsPage.hpp"
#include <QMessageBox>
#include <QSqlError>
#include <QDebug>

ModLocationsPage::ModLocationsPage(QWidget *parent) : QWidget(parent)
{
    this->setStyleSheet(MainStyle::StyleSheets[STYLE_MODIFYPAGE_NAME]);
    setupModel();
    setupLayout();
}

void ModLocationsPage::setupModel()
{
    /*if (!DB::Queries::Location::CreateLocationWithComponentView()) {
        QMessageBox::critical(nullptr, "Database Error", "Failed to create LocationWithComponent view.");
    }*/
    m_model = new QSqlTableModel(this);
    m_model->setTable("Location");
    m_model->select();

    m_model->setHeaderData(0, Qt::Horizontal, tr("Regał"));
    m_model->setHeaderData(1, Qt::Horizontal, tr("Szuflada"));
    m_model->setHeaderData(2, Qt::Horizontal, tr("ID komponentu"));
    m_model->setHeaderData(3, Qt::Horizontal, tr("Liczba elementów w szufladzie"));

    m_tableView = new QTableView(this);
    m_tableView->setModel(m_model);
    m_tableView->setEditTriggers(QAbstractItemView::NoEditTriggers); // make view read-only
    m_tableView->resizeColumnsToContents();

    liczba_szuflad_w_regale = 2;
} 

void ModLocationsPage::setupLayout()
{
    m_addButton = new QPushButton(tr("➕ Dodaj regał"));
    connect(m_addButton, &QPushButton::clicked, this, &ModLocationsPage::onAddRegalClicked);

    m_removeButton = new QPushButton(tr("➖ Usuń pusty regał"));
    connect(m_removeButton, &QPushButton::clicked, this, &ModLocationsPage::onRemoveRegalClicked);

    auto *mainLayout = new QVBoxLayout(this);
    mainLayout->addWidget(m_tableView);

    auto *buttonLayout = new QHBoxLayout();
    buttonLayout->addStretch();
    buttonLayout->addWidget(m_addButton);
    buttonLayout->addWidget(m_removeButton);
    mainLayout->addLayout(buttonLayout);

    setLayout(mainLayout);
}

void ModLocationsPage::refresh()
{
    m_model->select();
}

bool ModLocationsPage::addOperation(int nr_regalu, DB::Attrb::OperationType oprtyp)
{
    // Add operation in history
    QSqlQuery insertOperation;
    DB::Attrb::Operation::User_Email oprUser_Email(g_userEmail);
    if(!DB::Queries::Operation::InsertOperation(insertOperation, oprUser_Email)) {
        QMessageBox::warning(this, tr("Nie pykło"), tr("Nie udało się dodać operacji."));
        return 1;
    }

    // Get newest Operation ID
    QSqlQuery newestIDquery;
    if(!DB::Queries::Operation::GetNewestID(newestIDquery)) {
        QMessageBox::warning(this, tr("Nie pykło"), tr("Nie udało się odczytać ID operacji."));
        return 1;
    }
    if(newestIDquery.next()) {
        
        // Add ChangeRack operation
        QSqlQuery oprquery;
        DB::Attrb::Operation_ChangeRack::Operation_ID Operation_ID(newestIDquery.value(0).toInt());
        DB::Attrb::Operation_ChangeRack::RackNr RackNr(nr_regalu);
        if(!DB::Queries::Operation::InsertChangeRack(oprquery, Operation_ID, RackNr, oprtyp)) {
            QMessageBox::warning(this, tr("Nie pykło"), tr("Nie udało się dodać operacji na regale."));
            return 1;
        }
    }

    return 0;
}

void ModLocationsPage::onRemoveRegalClicked()
{
    // Numer regału usunięcia
    QString strnr_regalu = QInputDialog::getText(this, tr("Usuń regał"), tr("Podaj numer regału do usunięcia:"));
    if (strnr_regalu.isEmpty()) return;
    int nr_regalu = strnr_regalu.toInt();

    if(nr_regalu <= 0) {
        QMessageBox::warning(this, tr("Błąd numeru regału"), tr("Nie ma regału o takim numerze."));
        return;
    }
    QSqlQuery rackexsistsquery;
    DB::Attrb::Location::Rack Rack(nr_regalu);
    if(!DB::Queries::Location::IsRackInDatabase(rackexsistsquery, Rack)) {
        QMessageBox::warning(this, tr("Nie pykło"), tr("Nie znaleziono numeru regału."));
        return;
    } else if (rackexsistsquery.next()) {
        if(rackexsistsquery.value(0).toInt() <= 0) {
            QMessageBox::warning(this, tr("Błąd numeru regału"), tr("Nie ma regału o takim numerze."));
            return;
        }
    }

    QSqlQuery query;
    if(!DB::Queries::Location::CountNonemptyDrawersInRack(query, Rack)) {
        QMessageBox::warning(this, tr("Nie pykło"), tr("Nie znaleziono numeru regału."));
        return;
    } else if (query.next()) {
        // Niepusty
        if(query.value(0).toInt() != 0) {
            QMessageBox::warning(this, tr("Błąd numeru regału"), tr("Ten regał nie jest pusty. Aby go usunąć, usuń wpierw wszystkie komponenty z jego szuflad."));
            return;
        }
        // Pusty; Usuń
        else {
            QSqlQuery deletequery;
            if(!DB::Queries::Location::DeleteRack(deletequery, Rack)) {
                QMessageBox::warning(this, tr("Nie pykło"), tr("Nie udało się usunąć regału."));
                return;
            }
            
            if(addOperation(nr_regalu, DB::Attrb::OperationType::Remove)) return;

            m_model->select(); // Refresh table view
        }
    }
}

void ModLocationsPage::onAddRegalClicked()
{
    // Liczba szuflad w regale
    QString no_of_drawers = QInputDialog::getText(this, tr("Nowy regał"), tr("Podaj liczbę szuflad w nowym regale:"));
    if (no_of_drawers.isEmpty()) return;
    liczba_szuflad_w_regale = no_of_drawers.toInt();
    if(liczba_szuflad_w_regale <= 0) {
        QMessageBox::warning(this, tr("Błąd liczby szuflad"), tr("Liczba szuflad musi być dodatnia."));
        return;
    }

    // Nowy nr regału
    QSqlQuery query;
    if(!DB::Queries::Location::FindNextRackNumber(query)){
        QMessageBox::warning(this, tr("Nie pykło"), tr("Nie znaleziono numeru regału."));
        return;
    } else if (query.next()) {
            DB::Attrb::Location::Rack nr_nowego_regalu(query.value(0).toInt());

            // Insert szuflady
            bool allSucceeded = true;
            for(int i=1; i<=liczba_szuflad_w_regale; i++){
                DB::Attrb::Location::Drawer nr_nowej_szuflady(i);
                QSqlQuery insertQuery;

                if (!DB::Queries::Location::Add(insertQuery, nr_nowego_regalu, nr_nowej_szuflady)) {
                    QString istr = QString::number(i);
                    QMessageBox::warning(this, tr("Nie pykło"), tr("Nie dodano szuflady ") + istr);
                    allSucceeded = false;
                    break;
                }
            }
            if (allSucceeded) {
                if(addOperation(query.value(0).toInt(), DB::Attrb::OperationType::Add)) return;

                QMessageBox::information(this, tr("Dodano regał"), tr("Regał i szuflady zostały dodane pomyślnie."));
            }
        }

    m_model->select(); // Refresh table view after insertion
}

#include "modifyPage/moc_modLocationsPage.cpp"
// #include "modyfyPage/modLocationsPage.moc"
