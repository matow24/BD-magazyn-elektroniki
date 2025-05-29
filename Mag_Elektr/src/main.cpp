#include <QApplication>
#include <QObject>

#include "main.hpp"
#include "loginWindow/loginWindow.hpp"
#include "mainWindow/mainWindow.hpp"

QString g_userEmail = "275431@student.pwr.edu.pl";
UserRole g_userRole = UserRole::Admin;
/* - dorobić aktualizację MainWindow po zalogowaniu
domyślnie powinno być na start: 
QString g_userEmail = "";
UserRole g_userRole = UserRole::Guest;
*/

int main(int argc, char *argv[])
{
    QApplication mainApp(argc, argv);

    if (argc < 2)
    {
        qDebug() << "Error: Not enough arguments";
        exit(1);
    }

    if (!DB::MainDatabase::ConnectToDatabase(argv[1]))
        exit(1);

    MainStyle::loadStyleSheets();

    MainWindow mainWindow; //!< Tworzenie instancji głównego okna aplikacji
    LoginWindow loginWindow; //!< Tworzenie instancji okna logowania aplikacji

    //login handle
    QObject::connect(&loginWindow, &LoginWindow::loginSuccessful, [&]() {
        mainWindow.onLogin();
        mainWindow.showMaximized();  //! Wyświetlenie głównego okna aplikacji
    });

    //logout handles
    /*QObject::connect(mainWindow.getMainToolBar(), &MainToolBar::logoutClicked,
                 mainWindow, &MainWindow::hide);
    QObject::connect(mainWindow.getMainToolBar(), &MainToolBar::logoutClicked,
                 loginWindow, &LoginWindow::onLogout);*/

    loginWindow.show();     //! Wyświetlenie okna logowania aplikacji

    return mainApp.exec(); //! Uruchomienie pętli zdarzeń aplikacji
}

// #include "moc_main.cpp"
// #include "main.moc"