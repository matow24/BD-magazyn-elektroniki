#include "modifyPage/modComponentsPage.hpp"
#include <QMessageBox>
#include <QSqlError>
#include <QDebug>

ModComponentsPage::ModComponentsPage(QWidget *parent) : QWidget(parent)
{
    setupModel();
    setupLayout();
}

void ModComponentsPage::setupModel()
{
    m_model = new QSqlTableModel(this);
    m_model->setTable("Component");
    m_model->select();

    // Optional: make ID read-only
    m_model->setHeaderData(0, Qt::Horizontal, tr("ID"));
    m_model->setHeaderData(1, Qt::Horizontal, tr("Variant_Name"));
    m_model->setHeaderData(2, Qt::Horizontal, tr("Name"));
    m_model->setHeaderData(3, Qt::Horizontal, tr("Manufacturer"));
    m_model->setHeaderData(4, Qt::Horizontal, tr("Symbol"));
    m_model->setHeaderData(5, Qt::Horizontal, tr("Datasheet"));
    m_model->setHeaderData(6, Qt::Horizontal, tr("MaxQuantity"));

    m_tableView = new QTableView(this);
    m_tableView->setModel(m_model);
    m_tableView->setEditTriggers(QAbstractItemView::NoEditTriggers); // make view read-only
    m_tableView->resizeColumnsToContents();
}

void ModComponentsPage::setupLayout()
{
    m_addButton = new QPushButton(tr("➕ Dodaj komponent"));
    connect(m_addButton, &QPushButton::clicked, this, &ModComponentsPage::onAddComponentClicked);

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
    QMessageBox::information(this, "Add Component", "This will open a dialog to add a new component.");
    // TODO: Open your AddComponentDialog here
}
