#pragma once
#ifndef _DB_LOCATIONWITHCOMPONENT_HPP
#define _DB_LOCATIONWITHCOMPONENT_HPP

#include <QSqlQuery>
#include <QSqlError>
#include <QDebug>

namespace DB {
namespace Queries {
namespace Location {

bool CreateLocationWithComponentView() {
    QSqlQuery query;
    QString createViewSQL = R"(
        CREATE VIEW IF NOT EXISTS LocationWithComponent AS
        SELECT
            Location.Rack,
            Location.Drawer,
            Component.Name,
            Location.Quantity
        FROM
            Location
        LEFT JOIN
            Component ON Location.Component_ID = Component.ID
    )";

    if (!query.exec(createViewSQL)) {
        qDebug() << "Error creating view LocationWithComponent:" << query.lastError().text();
        return false;
    }

    return true;
}

bool DropLocationWithComponentView() {
    QSqlQuery query;
    if (!query.exec("DROP VIEW IF EXISTS LocationWithComponent")) {
        qDebug() << "Error dropping view LocationWithComponent:" << query.lastError().text();
        return false;
    }
    return true;
}
bool RefreshLocationWithComponentView() {
    return( DropLocationWithComponentView() && CreateLocationWithComponentView() );
}

} // namespace Location
} // namespace Queries
} // namespace DB

#endif