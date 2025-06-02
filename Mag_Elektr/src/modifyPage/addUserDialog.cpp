#include "modifyPage/addUserDialog.hpp"

explicit AddUserDialog::AddUserDialog(QWidget *parent = nullptr)
    : QDialog(parent)
{
    setWindowTitle(tr("Add New User"));
    this->setStyleSheet(MainStyle::StyleSheets[STYLE_MODIFYPAGE_NAME]);

    QVBoxLayout *mainLayout = new QVBoxLayout(this);
    QFormLayout *formLayout = new QFormLayout();

    firstNameEdit = new QLineEdit();
    lastNameEdit = new QLineEdit();
    emailEdit = new QLineEdit();
    positionBox = new QComboBox();

    positionBox->addItems({"Employee", "Logistician", "Admin"});

    formLayout->addRow("First Name:", firstNameEdit);
    formLayout->addRow("Last Name:", lastNameEdit);
    formLayout->addRow("Email:", emailEdit);
    formLayout->addRow("Position:", positionBox);

    mainLayout->addLayout(formLayout);

    addButton = new QPushButton("Add");
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
    QString email = emailEdit->text().trimmed();

    // Check for existing email
    QSqlQuery checkQuery;
    checkQuery.prepare("SELECT COUNT(*) FROM User WHERE Email = :email");
    checkQuery.bindValue(":email", email);

    if (!checkQuery.exec()) {
        QMessageBox::critical(this, "Database Error", "Failed to validate email:\n" + checkQuery.lastError().text());
        return;
    }

    if (checkQuery.next() && checkQuery.value(0).toInt() > 0) {
        QMessageBox::warning(this, "Email Exists", "The email address is already in use. Please choose another.");
        return;
    }

    // Confirm dialog
    QMessageBox::StandardButton reply = QMessageBox::question(
        this,
        "Confirm",
        "Do you confirm new user's data?",
        QMessageBox::Yes | QMessageBox::No,
        QMessageBox::No
    );

    if (reply == QMessageBox::No)
        return;

    // Insert user
    QSqlQuery insertQuery;
    insertQuery.prepare(R"(
        INSERT INTO User (FirstName, LastName, Email, Position)
        VALUES (:firstName, :lastName, :email, :position)
    )");

    insertQuery.bindValue(":firstName", firstNameEdit->text().trimmed());
    insertQuery.bindValue(":lastName", lastNameEdit->text().trimmed());
    insertQuery.bindValue(":email", email);
    insertQuery.bindValue(":position", positionBox->currentText());

    if (!insertQuery.exec()) {
        QMessageBox::warning(this, "Error", "Failed to insert new user:\n" + insertQuery.lastError().text());
        return;
    }

    accept(); // Close dialog on success
}

