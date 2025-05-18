#include <QApplication>
#include <QObject>
#include <QString>

#include "main.hpp"
#include "common/mainWindow.hpp"

int main(int argc, char *argv[])
{
    QApplication mainApp(argc, argv);

    MainWindow mainWindow; //!< Tworzenie instancji głównego okna aplikacji

    mainWindow.show();     //! Wyświetlenie głównego okna aplikacji
    return mainApp.exec(); //! Uruchomienie pętli zdarzeń aplikacji
}

// #include "moc_main.cpp"
// #include "main.moc"