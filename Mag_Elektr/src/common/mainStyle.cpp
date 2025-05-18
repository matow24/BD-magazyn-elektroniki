#include "common/mainStyle.hpp"

#define STYLE_COMPONENTSPAGE_PATH ":/stylesheets/componentsPage.qss"
#define STYLE_HISTORYPAGE_PATH ":/stylesheets/historyPage.qss"
#define STYLE_LOGINWINDOW_PATH ":/stylesheets/loginWindow.qss"
#define STYLE_MAINWINDOW_PATH ":/stylesheets/mainWindow.qss"
#define STYLE_MODIFYPAGE_PATH ":/stylesheets/modifyPage.qss"

QMap<QString, QString> MainStyle::StyleSheets;

//! @brief Wczytuje arkusze stylów z plików .qss
//!
//! @details Wczytuje arkusze stylów z plików .qss i zapisuje je w mapie StyleSheets.

void MainStyle::loadStyleSheets()
{
    QFile fileStyle_componentsPage(STYLE_COMPONENTSPAGE_PATH);
    if (fileStyle_componentsPage.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        MainStyle::StyleSheets[STYLE_COMPONENTSPAGE_NAME] = fileStyle_componentsPage.readAll();
        fileStyle_componentsPage.close();
    }
    else
        qWarning("Failed to load ComponentsPage style sheet");

    QFile fileStyle_historyPage(STYLE_HISTORYPAGE_PATH);
    if (fileStyle_historyPage.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        MainStyle::StyleSheets[STYLE_HISTORYPAGE_NAME] = fileStyle_historyPage.readAll();
        fileStyle_historyPage.close();
    }
    else
        qWarning("Failed to load HistoryPage style sheet");

    QFile fileStyle_loginWindow(STYLE_LOGINWINDOW_PATH);
    if (fileStyle_loginWindow.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        MainStyle::StyleSheets[STYLE_LOGINWINDOW_NAME] = fileStyle_loginWindow.readAll();
        fileStyle_loginWindow.close();
    }
    else
        qWarning("Failed to load LoginWindow style sheet");

    QFile fileStyle_mainWindow(STYLE_MAINWINDOW_PATH);
    if (fileStyle_mainWindow.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        MainStyle::StyleSheets[STYLE_MAINWINDOW_NAME] = fileStyle_mainWindow.readAll();
        fileStyle_mainWindow.close();
    }
    else
        qWarning("Failed to load MainWindow stylesheet");

    QFile fileStyle_modifyPage(STYLE_MODIFYPAGE_PATH);
    if (fileStyle_modifyPage.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        MainStyle::StyleSheets[STYLE_MODIFYPAGE_NAME] = fileStyle_modifyPage.readAll();
        fileStyle_modifyPage.close();
    }
    else
        qWarning("Failed to load ModifyPage style sheet");
}

// #include "common/moc_mainStyle.cpp"
// #include "common/mainStyle.moc"