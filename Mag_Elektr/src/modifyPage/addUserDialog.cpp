#include "modifyPage/addUserDialog.hpp"

bool AddUserDialog::setPosition(DB::Attrb::Position& pos){
    if(positionBox->currentText().trimmed() == "Employee"){
        pos = DB::Attrb::Position::Employee;
        return 0;
    }
    if(positionBox->currentText().trimmed() == "Logistician"){
        pos = DB::Attrb::Position::Logistician;
        return 0;
    }
    if(positionBox->currentText().trimmed() == "Admin"){
        pos = DB::Attrb::Position::Admin;
        return 0;
    }
    
    QMessageBox::critical(this, tr("Błąd nadawania uprawnień"), tr("Nie udało się wybrać uprawnień:\n"));
    return 1;
}

AddUserDialog::AddUserDialog(QWidget *parent) : QDialog(parent)
{
    setWindowTitle(tr("Dodaj nowego użytkownika"));
    this->setStyleSheet(MainStyle::StyleSheets[STYLE_MODIFYPAGE_NAME]);

    QVBoxLayout *mainLayout = new QVBoxLayout(this);
    QFormLayout *formLayout = new QFormLayout();

    firstNameEdit = new QLineEdit();
    lastNameEdit = new QLineEdit();
    emailEdit = new QLineEdit();
    passwordEdit = new QLineEdit();
    positionBox = new QComboBox();

    positionBox->addItems({"Employee", "Logistician", "Admin"});

    formLayout->addRow(tr("Imię:"), firstNameEdit);
    formLayout->addRow(tr("Nazwisko:"), lastNameEdit);
    formLayout->addRow(tr("Email:"), emailEdit);
    formLayout->addRow(tr("Hasło:"), passwordEdit);
    formLayout->addRow(tr("Poziom uprawnień:"), positionBox);

    mainLayout->addLayout(formLayout);

    addButton = new QPushButton(tr("Dodaj użytkownika"));
    addButton->setEnabled(false); // Start disabled
    mainLayout->addWidget(addButton, 0, Qt::AlignRight);

    // Connect field changes to check if form is filled
    connect(firstNameEdit, &QLineEdit::textChanged, this, &AddUserDialog::validateForm);
    connect(lastNameEdit, &QLineEdit::textChanged, this, &AddUserDialog::validateForm);
    connect(emailEdit, &QLineEdit::textChanged, this, &AddUserDialog::validateForm);
    connect(positionBox, &QComboBox::currentTextChanged, this, &AddUserDialog::validateForm);

    connect(addButton, &QPushButton::clicked, this, &AddUserDialog::onAddClicked);
}

void AddUserDialog::validateForm()
{
    const bool isFilled =
        !firstNameEdit->text().trimmed().isEmpty() &&
        !lastNameEdit->text().trimmed().isEmpty() &&
        !emailEdit->text().trimmed().isEmpty() &&
        !positionBox->currentText().trimmed().isEmpty();

    addButton->setEnabled(isFilled);
}

void AddUserDialog::onAddClicked()
{
    if(setPosition(upraw)) return;

    QString stremail = emailEdit->text().trimmed();
    DB::Attrb::User::Email email(stremail);
    DB::Attrb::User::FirstName name(firstNameEdit->text().trimmed());
    DB::Attrb::User::LastName surname(lastNameEdit->text().trimmed());
    DB::Attrb::User::Password pass(passwordEdit->text().trimmed());

    // Check for existing email
    QSqlQuery checkQuery;
    if (DB::Queries::User::CountEmail(checkQuery, stremail)){
        if (checkQuery.next() && checkQuery.value(0).toInt() > 0) {
            QMessageBox::warning(this, tr("Email zajęty"), tr("Ten adres email jest już zarejestrowany w bazie. Proszę podać inny."));
            return;
        }
    }   

    // Insert user
    QSqlQuery insertQuery;
    if (!DB::Queries::User::Add(insertQuery, email, name, surname, pass, upraw)){
        QMessageBox::warning(this, tr("Nie pykło"), tr("Nie dodano użytkownika."));
        return;
    }

    // Add operation in history
    QSqlQuery insertOperation;
    DB::Attrb::Operation::User_Email oprUser_Email(g_userEmail);
    if(!DB::Queries::Operation::InsertOperation(insertOperation, oprUser_Email)) {
        QMessageBox::warning(this, tr("Nie pykło"), tr("Nie udało się dodać operacji."));
        return;
    }

    // Get newest Operation ID
    QSqlQuery newestIDquery;
    if(!DB::Queries::Operation::GetNewestID(newestIDquery)){
        QMessageBox::warning(this, tr("Nie pykło"), tr("Nie udało się odczytać ID komponentu."));
        return;
    }
    if(newestIDquery.next()) {
        
        // Add ChangeUser operation
        QSqlQuery insertChangeUserOperation;
        DB::Attrb::Operation_ChangeUser::Operation_ID Operation_ID(newestIDquery.value(0).toInt());
        DB::Attrb::Operation_ChangeUser::User_Email chUser_Email(stremail);
        if(!DB::Queries::Operation::InsertChangeUser(insertChangeUserOperation, Operation_ID, chUser_Email, DB::Attrb::OperationType::Add)){
            QMessageBox::warning(this, tr("Nie pykło"), tr("Nie udało się dodać operacji zmiany użytkownika."));
            return;
        }
    }

    accept(); // Close dialog on success
}

#include "modifyPage/moc_addUserDialog.cpp"
// #include "modifyPage/addUserDialog.moc"