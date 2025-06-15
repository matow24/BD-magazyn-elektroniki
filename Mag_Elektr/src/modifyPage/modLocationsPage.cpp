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

void ModLocationsPage::onAddRegalClicked()
{
    // Confirm dialog
    QMessageBox::StandardButton reply = QMessageBox::question(
        this,
        tr("Zatwierdź"),
        tr("Czy potwierdzasz dodanie nowego regału?"),
        QMessageBox::Yes | QMessageBox::No,
        QMessageBox::No
    );

    if (reply == QMessageBox::No)
        return;

    // Nowy nr regału
    QSqlQuery query;
    if(!DB::Queries::Location::FindNextRackNumber(query)){
        QMessageBox::warning(this, tr("Nie pykło"), tr("Nie znaleziono numeru regału."));
        return;
    } else if (query.next()) {
            DB::Attrb::Location::Rack nr_nowego_regalu(query.value(0).toInt());

            // Insert szuflady
            for(int i=0; i<LICZBA_SZUFLAD_W_REGALE; i++){
                DB::Attrb::Location::Drawer nr_nowej_szuflady(i);
                QSqlQuery insertQuery;
                if (!DB::Queries::Location::Add(insertQuery, nr_nowego_regalu, nr_nowej_szuflady)){
                    QString istr = QString::number(i);
                    QMessageBox::warning(this, tr("Nie pykło"), tr("Nie dodano szuflady ") % istr);
                    break;
                }
            }
            QMessageBox::information(this, tr("Dodano regał"), tr("Regał i szuflady zostały dodane pomyślnie."));
        }

    m_model->select(); // Refresh table view after insertion
}

#include "modifyPage/moc_modLocationsPage.cpp"
// #include "modyfyPage/modLocationsPage.moc"
