#include "modifyPage/modComponentsPage.hpp"
#include <QMessageBox>
#include <QSqlError>
#include <QDebug>

ModComponentsPage::ModComponentsPage(QWidget *parent) : QWidget(parent)
{
    this->setStyleSheet(MainStyle::StyleSheets[STYLE_MODIFYPAGE_NAME]);
    setupModel();
    setupLayout();
}

void ModComponentsPage::refresh()
{
    QSqlQuery countquery;
    if(DB::Queries::Location::CountEmptyDrawers(countquery)){
        while(countquery.next()){
            m_addButton->setEnabled(countquery.value(0).toInt() != 0);
        }
    }
}

void ModComponentsPage::setupModel()
{
    m_model = new First2ColumnsLockedTableModel(this);
    m_model->setTable("Component");
    m_model->select();

    m_model->setHeaderData(0, Qt::Horizontal, tr("ID"));
    m_model->setHeaderData(1, Qt::Horizontal, tr("Variant_Name"));
    m_model->setHeaderData(2, Qt::Horizontal, tr("Name"));
    m_model->setHeaderData(3, Qt::Horizontal, tr("Manufacturer"));
    m_model->setHeaderData(4, Qt::Horizontal, tr("Symbol"));
    m_model->setHeaderData(5, Qt::Horizontal, tr("Datasheet"));
    m_model->setHeaderData(6, Qt::Horizontal, tr("MaxQuantity"));

    m_tableView = new QTableView(this);
    m_tableView->setModel(m_model);
    m_tableView->setEditTriggers(QAbstractItemView::DoubleClicked | QAbstractItemView::SelectedClicked);
    m_tableView->resizeColumnsToContents();
} 

void ModComponentsPage::setupLayout()
{
    m_addButton = new QPushButton(tr("➕ Dodaj komponent"));
    //m_moveButton = new QPushButton(tr("Przenieś komponent"));
    connect(m_addButton, &QPushButton::clicked, this, &ModComponentsPage::onAddComponentClicked);
    //connect(m_moveButton, &QPushButton::clicked, this, &ModComponentsPage::onMoveComponentClicked);
    QSqlQuery countquery;
    if(DB::Queries::Location::CountEmptyDrawers(countquery)){
        while(countquery.next()){
            if(countquery.value(0).toInt() == 0){
                m_addButton->setEnabled(false);
                QMessageBox::critical(this, tr("Brak miejsca"), tr("W całym magazynie nie ma pustych szuflad. Należy zresetować nieużywane szuflady lub dostawić regał."));
            }       
            else if(countquery.value(0).toInt() < 5){
                QMessageBox::critical(this, tr("Mało miejsca"), tr("W całym magazynie pozostały ") % countquery.value(0).toString() % tr(" puste szuflady. Zaleca się zresetować nieużywane szuflady lub dostawić regał."));
            }
            else if(countquery.value(0).toInt() < 10){
                QMessageBox::warning(this, tr("Mało miejsca"), tr("W całym magazynie pozostało ") % countquery.value(0).toString() % tr(" pustych szuflad."));
            }
        }
    }

    auto *mainLayout = new QVBoxLayout(this);
    mainLayout->addWidget(m_tableView);

    auto *buttonLayout = new QHBoxLayout();
    buttonLayout->addStretch();
    buttonLayout->addWidget(m_addButton);
    mainLayout->addLayout(buttonLayout);

    setLayout(mainLayout);
}

void ModComponentsPage::onAddComponentClicked()
{
    AddComponentDialog dialog(this);
    if (dialog.exec() == QDialog::Accepted) {
        m_model->select(); // Refresh table view after insertion
    }
}

bool ModComponentsPage::addOperation(int nr_regalu, DB::Attrb::OperationType oprtyp)
{
    // Add operation in history
    /*QSqlQuery insertOperation;
    DB::Attrb::Operation::User_Email oprUser_Email(g_userEmail);
    if(!DB::Queries::Operation::InsertOperation(insertOperation, oprUser_Email)) {
        QMessageBox::warning(this, tr("Nie pykło"), tr("Nie udało się dodać operacji."));
        return 1;
    }

    // Get newest Operation ID
    QSqlQuery newestoperationIDquery;
    if(!DB::Queries::Operation::GetNewestID(newestoperationIDquery)) {
        QMessageBox::warning(this, tr("Nie pykło"), tr("Nie udało się odczytać ID operacji."));
        return 1;
    }
    if(newestIDquery.next()) {
        
        // Add ChangeComponent operation
            QSqlQuery insertChangeComponentOperation;
            DB::Attrb::Operation_ChangeComponent::Operation_ID Operation_ID(newestoperationIDquery.value(0).toInt());
            DB::Attrb::Operation_ChangeComponent::Component_ID Component_ID(newestIDquery.value(0).toInt());
            if(!DB::Queries::Operation::InsertChangeComponent(insertChangeComponentOperation, Operation_ID, Component_ID, oprtyp)) {
                QMessageBox::warning(this, tr("Nie pykło"), tr("Nie udało się dodać operacji zmiany komponentu."));
                return 1;
            }

            // Add MoveComponent operation
            QSqlQuery insertMoveComponentOperation;
            DB::Attrb::Operation_MoveComponent::Operation_ID MoveOperation_ID(newestoperationIDquery.value(0).toInt());
            DB::Attrb::Operation_MoveComponent::Component_ID MoveComponent_ID(newestIDquery.value(0).toInt());
            DB::Attrb::Operation_MoveComponent::Old_Location_Drawer Old_Location_Drawer();
            DB::Attrb::Operation_MoveComponent::Old_Location_Rack Old_Location_Rack();
            DB::Attrb::Operation_MoveComponent::New_Location_Rack New_Location_Rack(regalEdit->currentText().toInt());
            DB::Attrb::Operation_MoveComponent::New_Location_Drawer New_Location_Drawer(szufladaEdit->currentText().toInt());
            if(!DB::Queries::Operation::InsertMoveComponent(insertChangeComponentOperation, MoveOperation_ID, MoveComponent_ID, Old_Location_Rack, Old_Location_Drawer, New_Location_Rack, New_Location_Drawer)) {
                QMessageBox::warning(this, tr("Nie pykło"), tr("Nie udało się dodać operacji przeniesienia komponentu."));
                return 1;
            }
    }*/

    return 0;
}

void ModComponentsPage::onMoveComponentClicked()
{
    /*// Numer komponentu usunięcia
    QString strnr_regalu = QInputDialog::getText(this, tr("Przenieś komponent"), tr("Podaj ID, symbol lub nazwę komponentu do przeniesienia:"));
    if (strnr_regalu.isEmpty()) return;
    int nr_regalu = strnr_regalu.toInt();

    if(nr_regalu <= 0) {
        QMessageBox::warning(this, tr("Błąd numeru komponentu"), tr("Nie ma komponentu o takim numerze."));
        return;
    }*/
}

#include "modifyPage/moc_modComponentsPage.cpp"
// #include "modyfyPage/modComponentsPage.moc"
