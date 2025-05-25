#include "loginWindow/loginWindow.hpp"

LoginWindow::LoginWindow(QWidget *parent) : QMainWindow(parent)
{
    this->setWindowTitle(tr("Magazyn Elektroniki") + " - Logowanie");
    this->setMinimumSize(1280, 720);
    this->showMaximized();
    this->setStyleSheet(MainStyle::StyleSheets[STYLE_LOGINWINDOW_NAME]);

    emailEdit = new QLineEdit(this);
    emailEdit->setPlaceholderText("Email");

    passwordEdit = new QLineEdit(this);
    passwordEdit->setPlaceholderText("Hasło");
    passwordEdit->setEchoMode(QLineEdit::Password);

    submitButton = new QPushButton("Zaloguj", this);
    proceedWithoutLoginButton = new QPushButton("Przejdź dalej bez logowania", this);
    forgotPasswordButton = new QPushButton("Nie pamiętm hasła", this);
    forgotPasswordButton->setFlat(true); // Makes it look like a link

    // Connect slots (implement later if needed)
    connect(submitButton, &QPushButton::clicked, this, &LoginWindow::onSubmit);
    connect(forgotPasswordButton, &QPushButton::clicked, this, &LoginWindow::onForgotPassword);
    connect(proceedWithoutLoginButton, &QPushButton::clicked, this, &LoginWindow::onProceedWithoutLogin);

    // Layout setup
    QVBoxLayout *layout = new QVBoxLayout(this);
    layout->addWidget(emailEdit);
    layout->addWidget(passwordEdit);
    layout->addWidget(submitButton);
    layout->addWidget(forgotPasswordButton); 
    layout->addSpacing(20);  // Bigger space between the buttons
    layout->addWidget(proceedWithoutLoginButton);

    setLayout(layout);
}

void LoginWindow::setUserRole(char dbRole){
    switch(dbRole){
        case 'A':
            g_userRole = UserRole::Admin;
            break;
        case 'L':
            g_userRole = UserRole::Logistician;
            break;
        case 'E':
            g_userRole = UserRole::Employee;
            break;
    }
}

void LoginWindow::onSubmit() {
    QString email = emailEdit->text().trimmed();
    QString password = passwordEdit->text();

    if (email.isEmpty() || password.isEmpty()) {
        QMessageBox::warning(this, "Błąd danych wejściowych", "Należy podać tak email, jak i hasło.");
        return;
    }

    // Connect to SQLite database
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("TestDatabase.db");

    if (!db.open()) {
        QMessageBox::critical(this, "Błąd bazy danych", "Nie udało się połączyć z bazą.");
        qDebug() << "DB Error:" << db.lastError().text();
        return;
    }

    QSqlQuery query;
    query.prepare("SELECT Password, Position FROM User WHERE email = :email");
    query.bindValue(":email", email);

    if (!query.exec()) {
        QMessageBox::critical(this, "Błąd zapytania", "Nie udało się pozyskać danych z bazy.");
        qDebug() << "Query Error:" << query.lastError().text();
        return;
    }

    if (query.next()) {
        /*
        DB::Attrb::User::Email queryEmail(email);
        DB::Attrb::User::Password queryPassword(password);
        if (!DB::Queries::Component::LogIn(query, queryEmail, queryPassword))
            QMessageBox::warning(this, "Błąd logowania", "Niepoprawne hasło.");
        else{
            QMessageBox::information(this, "Zalogowano pomyślnie", "Witamy!");
            // przejdź do mainWindow
        }
        */

        QString dbPassword = query.value(0).toString();
        char dbRole        = query.value(1).toString().at(0).toLatin1();
        if (dbPassword == password) {
            g_userEmail = email;
            setUserRole(dbRole);

            QMessageBox::information(this, "Zalogowano pomyślnie", "Witamy!");
            // przejdź do mainWindow - sygnał ALBO zamknij loginWindow
        } else {
            QMessageBox::warning(this, "Błąd logowania", "Niepoprawne hasło.");
        }
    } else {
        QMessageBox::warning(this, "Błąd logowania", "Nie znaleziono adresu email.");
    }

    db.close();
}


void LoginWindow::onForgotPassword() {
    // Handle password change logic here
}

void LoginWindow::onProceedWithoutLogin() {
    // Handle skip login logic here
    g_userRole = UserRole::Guest;
    g_userEmail = "Szacowny gość";
}

#include "loginWindow/moc_loginWindow.cpp"
// #include "loginWindow/loginWindow.moc"