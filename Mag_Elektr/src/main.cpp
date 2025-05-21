#include <QApplication>
#include <QObject>
#include <QString>

#include "main.hpp"
#include "mainWindow/mainWindow.hpp"

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

    MainWindow mainWindow(UserRole::Admin); //!< Tworzenie instancji głównego okna aplikacji

    mainWindow.show();     //! Wyświetlenie głównego okna aplikacji
    return mainApp.exec(); //! Uruchomienie pętli zdarzeń aplikacji
}

// #include "moc_main.cpp"
// #include "main.moc"