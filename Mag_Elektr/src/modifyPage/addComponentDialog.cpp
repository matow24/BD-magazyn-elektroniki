#include "modifyPage/addComponentDialog.hpp"

bool AddComponentDialog::isNameUnique(const QString &name)
{
    QSqlQuery query;
    query.prepare("SELECT COUNT(*) FROM Component WHERE Name = :name");
    query.bindValue(":name", name);
    if (query.exec() && query.next()) {
        return query.value(0).toInt() == 0;
    }
    return false;
}

bool AddComponentDialog::isSymbolUnique(const QString &symbol)
{
    QSqlQuery query;
    query.prepare("SELECT COUNT(*) FROM Component WHERE Symbol = :symbol");
    query.bindValue(":symbol", symbol);
    if (query.exec() && query.next()) {
        return query.value(0).toInt() == 0;
    }
    return false;
}
