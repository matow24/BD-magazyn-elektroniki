#include "common/mainDatabase.hpp"

#define DATABASE_TYPE "QSQLITE"

QSqlDatabase MainDatabase::DataBase;

bool MainDatabase::ConnectToDatabase(const QString &dbPath)
{
    QFileInfo dbFileInfo(dbPath);
    if (!dbFileInfo.exists() || !dbFileInfo.isFile())
    {
        qDebug() << "Error: Database file does not exist:" << dbPath;
        return false;
    }

    if (dbFileInfo.size() == 0)
    {
        qDebug() << "Error: Database file is empty:" << dbPath;
        return false;
    }

    MainDatabase::DataBase = QSqlDatabase::addDatabase(DATABASE_TYPE);
    MainDatabase::DataBase.setDatabaseName(dbPath);

    if (!MainDatabase::DataBase.open())
    {
        qDebug() << "Error: Unable to open database:" << dbPath;
        return false;
    }

    return true;
}

#include "common/moc_mainDatabase.cpp"
// #include "common/mainDatabase.moc"