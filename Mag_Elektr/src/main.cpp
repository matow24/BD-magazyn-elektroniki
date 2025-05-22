#include <QApplication>
#include <QObject>

#include "main.hpp"
#include "mainWindow/mainWindow.hpp"

QString g_userEmail = "275431@student.pwr.edu.pl";
UserRole g_userRole = UserRole::Admin;

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

    mainWindow.show();     //! Wyświetlenie głównego okna aplikacji
    return mainApp.exec(); //! Uruchomienie pętli zdarzeń aplikacji
}

// #include "moc_main.cpp"
// #include "main.moc"