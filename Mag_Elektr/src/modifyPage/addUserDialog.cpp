#include "modifyPage/addUserDialog.hpp"

bool AddUserDialog::setPosition(char& pos){
    if(positionBox->currentText().trimmed() == "Employee"){
        pos = 'E';
        return 1;
    }
    if(positionBox->currentText().trimmed() == "Logistician"){
        pos = 'L';
        return 1;
    }
    if(positionBox->currentText().trimmed() == "Admin"){
        pos = 'A';
        return 1;
    }
    
    QMessageBox::critical(this, tr("Błąd nadawania uprawnień"), tr("Nie udało się wybrać uprawnień:\n"));
    return 0;
}

AddUserDialog::AddUserDialog(QWidget *parent) : QDialog(parent)
{
    setWindowTitle(tr("Add New User"));
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
    if(setPosition(pos)) return;
    QString email = emailEdit->text().trimmed();
    QString name = firstNameEdit->text().trimmed();
    QString surname = lastNameEdit->text().trimmed();

    // Check for existing email
    QSqlQuery checkQuery;
    if (DB::Queries::User::CountEmail(checkQuery, email)){
        if (checkQuery.next() && checkQuery.value(0).toInt() > 0) {
            QMessageBox::warning(this, tr("Email zajęty"), tr("Ten adres email jest już zarejestrowany w bazie. Proszę podać inny."));
            return;
        }
    }   

    // Confirm dialog
    QMessageBox::StandardButton reply = QMessageBox::question(
        this,
        "Zatwierdź",
        "Czy potwierdzasz dane nowego użytkownika?",
        QMessageBox::Yes | QMessageBox::No,
        QMessageBox::No
    );

    if (reply == QMessageBox::No)
        return;

    // Insert user
    QSqlQuery insertQuery;
    if (!DB::Queries::User::Add(insertQuery, email, name, surname, passwordEdit->text().trimmed(), pos)){
        return;
    }
    else if (insertQuery.next()) {
            auto msg = "Użytkownik " % email % ", " % name % " " % surname % ", został dodany pomyślnie.";
            QMessageBox::information(this, tr("Dodano użytkownika"), msg);
        }

    accept(); // Close dialog on success
}

