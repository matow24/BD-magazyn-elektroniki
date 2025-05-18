#ifndef _MAINSTYLE_HPP
#define _MAINSTYLE_HPP

#define STYLE_COMPONENTSPAGE_NAME "ComponentsPage"
#define STYLE_HISTORYPAGE_NAME "HistoryPage"
#define STYLE_LOGINWINDOW_NAME "LoginWindow"
#define STYLE_MAINWINDOW_NAME "MainWindow"
#define STYLE_MODIFYPAGE_NAME "ModifyPage"

#include <QFile>
#include <QMap>
#include <QString>

#include "main.hpp"

class MainStyle
{
public:
    static QMap<QString, QString> StyleSheets; //!< Mapa przechowywująca arkusze stylów

    static void loadStyleSheets();
};

#endif // _MAINSTYLE_HPP