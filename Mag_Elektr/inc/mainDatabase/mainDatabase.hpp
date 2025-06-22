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
               bool Add(QSqlQuery &query, Attrb::Variant::Name Name, Attrb::Variant::Type Type);

               bool DeleteNotExists(QSqlQuery &query);

               bool Select(QSqlQuery &query);

               bool GetVariantTypes(QSqlQuery &query);

               bool GetVariantNames(QSqlQuery &query);

               bool GetTypeByName(QSqlQuery &query, Attrb::Variant::Name Name);
          } // namespace Variant

          namespace Component
          {
               bool Add(QSqlQuery &query, Attrb::Variant::Name Variant_Name, Attrb::Component::Name Name, Attrb::Component::Manufacturer Manufacturer, Attrb::Component::Symbol Symbol, Attrb::Component::Datasheet Datasheet, Attrb::Component::MaxQuantity MaxQuantity);

               bool Delete(QSqlQuery &query, Attrb::Component::ID ID);

               bool Delete(QSqlQuery &query, Attrb::Component::Name Name);

               bool CountNameSymbol(QSqlQuery &query, Attrb::Component::Name Name, Attrb::Component::Symbol Symbol);

               bool GetNewestID(QSqlQuery &query);

               bool SelectWhere(QSqlQuery &query, Attrb::Component::ID ID);

               bool SelectWhere(QSqlQuery &query, Attrb::Variant::Name Name);

               bool SelectWhere(QSqlQuery &query, Attrb::Variant::Type Type);

               bool SelectWhere(QSqlQuery &query, Attrb::Location::Rack Rack, Attrb::Location::Drawer Drawer);

               bool SelectLike(QSqlQuery &query, Attrb::Component::Name substr_Name);
          } // namespace Component

          namespace Location
          {
               bool Add(QSqlQuery &query, Attrb::Location::Rack Rack, Attrb::Location::Drawer Drawer);

               bool DeleteRack(QSqlQuery &query, Attrb::Location::Rack Rack);

               bool CountEmptyDrawers(QSqlQuery &query);

               bool GetEmptyDrawersInRack(QSqlQuery &query, Attrb::Location::Rack Rack);

               bool GetEmptyDrawers(QSqlQuery &query);

               bool CountNonemptyDrawersInRack(QSqlQuery &query, Attrb::Location::Rack Rack);

               bool IsRackInDatabase(QSqlQuery &query, Attrb::Location::Rack Rack);

               bool FindNextRackNumber(QSqlQuery &query);

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

               bool GetNewestID(QSqlQuery &query);

               bool InsertChangeUser(QSqlQuery &query, Attrb::Operation_ChangeUser::Operation_ID Operation_ID,
                                          Attrb::Operation_ChangeUser::User_Email User_Email, Attrb::OperationType Type);

               bool InsertChangeRack(QSqlQuery &query, Attrb::Operation_ChangeRack::Operation_ID Operation_ID,
                                          Attrb::Operation_ChangeRack::RackNr RackNr, Attrb::OperationType Type);

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

               bool InsertMoveComponentAdd(QSqlQuery &query, Attrb::Operation_MoveComponent::Operation_ID Operation_ID,
                                        Attrb::Operation_MoveComponent::Component_ID Component_ID,
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

          namespace User
          {
               bool LogIn(QSqlQuery &query, QString email);

               bool FindAdmin(QSqlQuery &query);

               bool Add(QSqlQuery &query, Attrb::User::Email email, Attrb::User::FirstName first_name, Attrb::User::LastName last_name, Attrb::User::Password password, Attrb::Position position);

               bool CountEmail(QSqlQuery &query, QString email);

          } // namespace User

     } // namespace Queries

     namespace Func
     {
          bool changeQuantity(QSqlQuery &query, int componentID, int delta);

          bool deleteComponent(QSqlQuery &query, int componentID);

     } // namespace Func

} // namespace DB

#endif // _MAINDATABASE_HPP