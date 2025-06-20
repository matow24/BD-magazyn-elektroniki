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
    connect(m_addButton, &QPushButton::clicked, this, &ModComponentsPage::onAddComponentClicked);
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

#include "modifyPage/moc_modComponentsPage.cpp"
// #include "modyfyPage/modComponentsPage.moc"
