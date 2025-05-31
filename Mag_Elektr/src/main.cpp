#include <QApplication>
#include <QObject>

#include "main.hpp"
#include "loginWindow/loginWindow.hpp"
#include "mainWindow/mainWindow.hpp"

QString g_userEmail = "";
UserRole g_userRole = UserRole::Guest;

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

    LoginWindow loginWindow; //!< Tworzenie instancji okna logowania aplikacji  
    QScopedPointer<MainWindow> mainWindow; //!< Tworzenie instancji głównego okna aplikacji

    loginWindow.show();     //! Wyświetlenie okna logowania aplikacji

    QObject::connect(&loginWindow, &LoginWindow::loginSuccessful, [&]() {
        mainWindow.reset(new MainWindow());
        QObject::connect(mainWindow.get(), &MainWindow::logoutRequested, [&]() {
            loginWindow.onLogout();
            mainWindow->close();
            mainWindow.reset(); 
        });
        mainWindow->show();
        loginWindow.hide();
    });


    return mainApp.exec(); //! Uruchomienie pętli zdarzeń aplikacji
}

// #include "moc_main.cpp"
// #include "main.moc"