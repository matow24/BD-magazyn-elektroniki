#include "modifyPage/modUserPage.hpp"

ModUserPage::ModUserPage(QWidget *parent) : QWidget(parent)
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
    buttonLayout->setContentsMargins(0,0,0,0);

    QPushButton *addButton = new QPushButton(tr("➕ Dodaj użytkownika"), this);
    QPushButton *removeButton = new QPushButton(tr("➖ Usuń użytkownika"), this);
    buttonLayout->addWidget(addButton);
    buttonLayout->addWidget(removeButton);

    // Layout setup
    mainLayout->addWidget(tableView);
    mainLayout->addLayout(buttonLayout);

    // Signal-slot for adding user
    connect(addButton, &QPushButton::clicked, this, &ModUserPage::addUser);
    connect(removeButton, &QPushButton::clicked, this, &ModUserPage::removeUser);
}

void ModUserPage::addUser()
{
    AddUserDialog dialog(this);
    if (dialog.exec() == QDialog::Accepted) {
        m_model->select(); // Refresh table view after insertion
    }
}

bool ModUserPage::addOperation(QString email_to_remove)
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
        
        // Add ChangeUser operation
        QSqlQuery insertChangeUserOperation;
        DB::Attrb::Operation_ChangeUser::Operation_ID Operation_ID(newestIDquery.value(0).toInt());
        DB::Attrb::Operation_ChangeUser::User_Email chUser_Email(email_to_remove);
        if(!DB::Queries::Operation::InsertChangeUser(insertChangeUserOperation, Operation_ID, chUser_Email, DB::Attrb::OperationType::Remove)){
            QMessageBox::warning(this, tr("Nie pykło"), tr("Nie udało się dodać operacji zmiany użytkownika."));
            return 1;
        }
    }

    return 0;
}

void ModUserPage::removeUser()
{
    // Email do usunięcia
    QString email_to_remove = QInputDialog::getText(this, tr("Usuń użytkownika"), tr("Podaj email użytkownika do usunięcia:"));
    if (email_to_remove.isEmpty()) return;

    if(email_to_remove == g_userEmail) {
        QMessageBox::warning(this, tr("Email zablokowany"), tr("Nie można usunąć samego siebie."));
        return;
    }

    // Check for existing email
    QSqlQuery checkQuery;
    if (DB::Queries::User::CountEmail(checkQuery, email_to_remove)){
        if (checkQuery.next() && checkQuery.value(0).toInt() <= 0) {
            QMessageBox::warning(this, tr("Email nie istnieje"), tr("Użytkownik o podanym adresie email nie istnieje."));
            return;
        }
    }  

    //Usuń
    QSqlQuery deleteQuery;
    DB::Attrb::User::Email email(email_to_remove);
    if(!DB::Queries::User::Delete(deleteQuery, email)) {
        QMessageBox::warning(this, tr("Nie pykło"), tr("Nie udało się usunąć użytkownika."));
        return;
    }

    if(addOperation(email_to_remove)) return;

    m_model->select(); // Refresh table view
}

#include "modifyPage/moc_modUserPage.cpp"
// #include "modifyPage/modUserPage.moc"