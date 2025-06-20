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

    auto *mainLayout = new QVBoxLayout(this);
    mainLayout->addWidget(m_tableView);

    auto *buttonLayout = new QHBoxLayout();
    buttonLayout->addStretch();
    buttonLayout->addWidget(m_addButton);
    mainLayout->addLayout(buttonLayout);

    setLayout(mainLayout);
}

void ModLocationsPage::refresh()
{
    m_model->select();
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
                QMessageBox::information(this, tr("Dodano regał"), tr("Regał i szuflady zostały dodane pomyślnie."));
            }
        }

    m_model->select(); // Refresh table view after insertion
}

#include "modifyPage/moc_modLocationsPage.cpp"
// #include "modyfyPage/modLocationsPage.moc"
