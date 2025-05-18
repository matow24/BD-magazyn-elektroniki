#ifndef _MAINDATABASE_HPP
#define _MAINDATABASE_HPP

#include <QFile>
#include <QFileInfo>
#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>
#include <QString>

#include "main.hpp"

class MainDatabase
{
public:
    static QSqlDatabase DataBase;

    static bool ConnectToDatabase(const QString &dbPath);
};

#endif // _MAINDATABASE_HPP