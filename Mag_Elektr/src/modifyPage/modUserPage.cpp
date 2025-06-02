#include "modifyPage/modUserPage.hpp"

ModUserPage::ModUserPage(QWidget *parent)
    : QWidget(parent)
{
    this->setStyleSheet(MainStyle::StyleSheets[STYLE_MODIFYPAGE_NAME]);
    QVBoxLayout *mainLayout = new QVBoxLayout(this);

    // Table view and model
    m_model = new QSqlTableModel(this);
    m_model->setTable("User");
    m_model->select();  // Load data

    QTableView *tableView = new QTableView(this);
    tableView->setModel(m_model);
    tableView->setEditTriggers(QAbstractItemView::DoubleClicked | QAbstractItemView::SelectedClicked);

    // Add button layout
    QHBoxLayout *buttonLayout = new QHBoxLayout();
    buttonLayout->addStretch();  // push button to the right

    QPushButton *addButton = new QPushButton(tr("➕ Dodaj Użytkownika"), this);
    buttonLayout->addWidget(addButton);

    // Layout setup
    mainLayout->addWidget(tableView);
    mainLayout->addLayout(buttonLayout);

    // Signal-slot for adding user
    connect(addButton, &QPushButton::clicked, this, &ModUserPage::addUser);
}

void ModUserPage::addUser()
{
    AddUserDialog dialog(this);
    if (dialog.exec() == QDialog::Accepted) {
        m_model->select(); // Refresh table view after insertion
    }
}