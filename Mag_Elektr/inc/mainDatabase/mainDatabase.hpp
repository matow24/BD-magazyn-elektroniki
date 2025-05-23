#ifndef _MAINDATABASE_HPP
#define _MAINDATABASE_HPP

#include <QChar>
#include <QFile>
#include <QFileInfo>
#include <QMetaType>
#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>
#include <QSqlRecord>
#include <QString>

#include "main.hpp"
#include "mainDatabase/attributes.hpp"

namespace DB
{

     class MainDatabase
     {
     public:
          static QSqlDatabase DataBase;
          static bool ConnectToDatabase(const QString &dbPath);
     };

     namespace Queries
     {

          bool LastInsertRowID(QSqlQuery &query);

          namespace Variant
          {
               bool DeleteNotExists(QSqlQuery &query);

               bool Select(QSqlQuery &query);
          } // namespace Variant

          namespace Component
          {
               bool Delete(QSqlQuery &query, Attrb::Component::ID ID);

               bool SelectWhere(QSqlQuery &query, Attrb::Component::ID ID);

               bool SelectWhere(QSqlQuery &query, Attrb::Variant::Name Name);

               bool SelectWhere(QSqlQuery &query, Attrb::Variant::Type Type);

               bool SelectWhere(QSqlQuery &query, Attrb::Location::Rack Rack, Attrb::Location::Drawer Drawer);

               bool SelectLike(QSqlQuery &query, Attrb::Component::Name substr_Name);
          } // namespace Component

          namespace Location
          {
               bool SelectWhere(QSqlQuery &query, Attrb::Location::Rack Rack, Attrb::Location::Drawer Drawer);

               bool SelectWhere(QSqlQuery &query, Attrb::Location::Component_ID Component_ID);

               bool UpdateSetQuantity(QSqlQuery &query, Attrb::Location::Component_ID Component_ID, Attrb::Location::Quantity Quantity);

               bool UpdateSetComponentID(QSqlQuery &query, Attrb::Location::Component_ID new_Component_ID,
                                         Attrb::Location::Component_ID old_Component_ID);

               bool UpdateSetComponentID(QSqlQuery &query, Attrb::Location::Component_ID new_Component_ID,
                                         Attrb::Location::Rack Rack, Attrb::Location::Drawer Drawer);
          } // namespace Location

          namespace Operation
          {
               bool InsertOperation(QSqlQuery &query, Attrb::Operation::User_Email User_Email);

               bool InsertChangeComponent(QSqlQuery &query, Attrb::Operation_ChangeComponent::Operation_ID Operation_ID,
                                          Attrb::Operation_ChangeComponent::Component_ID Component_ID, Attrb::OperationType Type);

               bool InsertChangeQuantity(QSqlQuery &query, Attrb::Operation_ChangeQuantity::Operation_ID Operation_ID,
                                         Attrb::Operation_ChangeQuantity::Component_ID Component_ID, Attrb::Operation_ChangeQuantity::Delta Delta);

               bool InsertMoveComponent(QSqlQuery &query, Attrb::Operation_MoveComponent::Operation_ID Operation_ID,
                                        Attrb::Operation_MoveComponent::Component_ID Component_ID,
                                        Attrb::Operation_MoveComponent::Old_Location_Rack Old_Location_Rack,
                                        Attrb::Operation_MoveComponent::Old_Location_Drawer Old_Location_Drawer,
                                        Attrb::Operation_MoveComponent::New_Location_Rack New_Location_Rack,
                                        Attrb::Operation_MoveComponent::New_Location_Drawer New_Location_Drawer);

               bool SelectWhereChangeComponent(QSqlQuery &query, QVariant DateTimeMin, QVariant DateTimeMax,
                                               QVariant User_Email, QVariant Component_ID);

               bool SelectWhereChangeQuantity(QSqlQuery &query, QVariant DateTimeMin, QVariant DateTimeMax, QVariant User_Email,
                                              QVariant Component_ID);

               bool SelectWhereChangeRack(QSqlQuery &query, QVariant DateTimeMin, QVariant DateTimeMax, QVariant User_Email,
                                          QVariant RackNr);

               bool SelectWhereChangeUser(QSqlQuery &query, QVariant DateTimeMin, QVariant DateTimeMax, QVariant User_Email);

               bool SelectWhereMoveComponent(QSqlQuery &query, QVariant DateTimeMin, QVariant DateTimeMax, QVariant User_Email,
                                             QVariant Component_ID, QVariant Location_Rack, QVariant Location_Drawer);

          } // namespace Operation

     } // namespace Queries

     namespace Func
     {
          bool changeQuantity(QSqlQuery &query, int componentID, int delta);

          bool deleteComponent(QSqlQuery &query, int componentID);

     } // namespace Func

} // namespace DB

#endif // _MAINDATABASE_HPP