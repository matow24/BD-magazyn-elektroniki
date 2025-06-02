#include "loginWindow/loginWindow.hpp"

LoginWindow::LoginWindow(QWidget *parent) : QMainWindow(parent)
{
    this->setWindowTitle(tr("Magazyn Elektroniki - Logowanie"));
    this->setMinimumSize(1280, 720);
    this->showMaximized();
    this->setStyleSheet(MainStyle::StyleSheets[STYLE_LOGINWINDOW_NAME]);

    window = new QWidget;
    window->setMinimumSize(720, 720);
    window->setMaximumSize(this->width(), this->height());

    emailEdit = new QLineEdit(this);
    emailEdit->setPlaceholderText("Email");

    passwordEdit = new QLineEdit(this);
    passwordEdit->setPlaceholderText("Hasło");
    passwordEdit->setEchoMode(QLineEdit::Password);

    submitButton = new QPushButton("Zaloguj", this);
    proceedWithoutLoginButton = new QPushButton("Przejdź dalej bez logowania", this);
    forgotPasswordButton = new QPushButton("Nie pamiętam hasła", this);
    forgotPasswordButton->setFlat(true); // Makes it look like a link

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

    window->setLayout(layout);    
    setCentralWidget(window);
}

void LoginWindow::onLogout(){
    emailEdit->clear();
    passwordEdit->clear();

    g_userRole = UserRole::Guest;
    //reset g_userEmail

    this->show();  
    this->raise();  
    this->activateWindow();
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

    QSqlQuery query;
    QString queryEmail(email);
    if (!DB::Queries::User::LogIn(query, queryEmail))
        QMessageBox::warning(this, "Błąd logowania", "Niepoprawne hasło.");
    else{
        if (query.next()) {
            QString dbPassword = query.value(0).toString();
            char dbRole        = query.value(1).toString().at(0).toLatin1();
            
            if (dbPassword == password) {
                g_userEmail = email;
                setUserRole(dbRole);

                emit loginSuccessful(); 
                close();
            } else {
                QMessageBox::warning(this, "Błąd logowania", "Niepoprawne hasło.");
            }
        } else {
            QMessageBox::warning(this, "Błąd logowania", "Nie znaleziono adresu email.");
        }
    }
}

void LoginWindow::onForgotPassword() {
    QSqlQuery query;
    QString adminFirstName ="";
    QString adminLastName ="";
    QString adminEmail ="";

    if (DB::Queries::User::FindAdmin(query)){
        if(query.next()){
            adminFirstName = query.value(0).toString();
            adminLastName = query.value(1).toString();
            adminEmail = query.value(2).toString();
        }
    } else QMessageBox::information(this, "Zapytaj admina o nowe hasło", "A nie, nie ma admina XD");

    auto msg = "Jeśli nie pamiętasz hasła, zgłoś się do administratora bazy danych, którym jest " % adminFirstName % " " % adminLastName % ", " % adminEmail;
    QMessageBox::information(this, "Zapytaj admina o nowe hasło", msg);
}

void LoginWindow::onProceedWithoutLogin() {
    g_userRole = UserRole::Guest;
    g_userEmail = "Szacowny gość";

    emit loginSuccessful(); 
    close();
}

#include "loginWindow/moc_loginWindow.cpp"
// #include "loginWindow/loginWindow.moc"