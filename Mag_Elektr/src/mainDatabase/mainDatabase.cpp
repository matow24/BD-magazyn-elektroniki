#include "mainDatabase/mainDatabase.hpp"

#include "mainDatabase/attributes.hpp"
#include "mainDatabase/queries.hpp"

using namespace DB;

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

bool Queries::User::LogIn(QSqlQuery &query, QString email)
{
    query.prepare(USER_LOGIN__EMAIL);
    query.bindValue(":email", email);

    if (!query.exec())
    {
        qDebug() << "Error: Unable to execute query:" << query.lastError().text();
        return false;
    }
    return true;
}

bool Queries::User::CountEmail(QSqlQuery &query, QString email)
{
    query.prepare(USER_COUNT__EMAIL);
    query.bindValue(":email", email);

    if (!query.exec())
    {
        qDebug() << "Error: Failed to count email:\n"<< query.lastError().text();
        return false;
    }
    return true;
}

bool Queries::User::FindAdmin(QSqlQuery &query)
{
    query.prepare(USER_FIND_ADMIN);
    if (!query.exec())
    {
        qDebug() << "Error: Unable to execute query:" << query.lastError().text();
        return false;
    }
    return true;
}

bool Queries::User::Add(QSqlQuery &query, Attrb::User::Email email, Attrb::User::FirstName first_name, Attrb::User::LastName last_name, Attrb::User::Password password, Attrb::Position position)
{
    query.prepare(USER_ADD);
    query.bindValue(":email", email.m_Email);
    query.bindValue(":first_name", first_name.m_FirstName);
    query.bindValue(":last_name", last_name.m_LastName);
    query.bindValue(":password", password.m_Password);
    query.bindValue(":position", QChar(static_cast<int>(position)));

    if (!query.exec())
    {
        qDebug() << "Error: Failed to insert new user:" << query.lastError().text();
        return false;
    }
    return true;
}

bool Queries::User::Delete(QSqlQuery &query, Attrb::User::Email email)
{
    query.prepare(USER_DELETE__EMAIL);
    query.bindValue(":email", email.m_Email);

    if (!query.exec())
    {
        qDebug() << "Error: Failed to delete user:" << query.lastError().text();
        return false;
    }
    return true;
}

bool Queries::LastInsertRowID(QSqlQuery &query)
{
    query.prepare(LAST_INSERT_ROW_ID);
    if (!query.exec())
    {
        qDebug() << "Error: Unable to execute query:" << query.lastError().text();
        return false;
    }
    return true;
}

bool Queries::Variant::Add(QSqlQuery &query, Attrb::Variant::Name Name, Attrb::Variant::Type Type)
{
    query.prepare(VARIANT_ADD);
    query.bindValue(":name", Name.m_Name);
    query.bindValue(":type", Type.m_Type);

    if (!query.exec())
    {
        qDebug() << "Error: Unable to execute query:" << query.lastError().text();
        return false;
    }
    return true;
}

bool Queries::Variant::DeleteNotExists(QSqlQuery &query)
{
    query.prepare(VARIANT_DELETENOTEXISTS);
    if (!query.exec())
    {
        qDebug() << "Error: Unable to execute query:" << query.lastError().text();
        return false;
    }
    return true;
}

bool Queries::Variant::Select(QSqlQuery &query)
{
    query.prepare(VARIANT_SELECT);
    if (!query.exec())
    {
        qDebug() << "Error: Unable to execute query:" << query.lastError().text();
        return false;
    }
    return true;
}

bool Queries::Variant::GetVariantTypes(QSqlQuery &query)
{
    query.prepare(VARIANT_TYPES);
    if (!query.exec())
    {
        qDebug() << "Error: Unable to execute query:" << query.lastError().text();
        return false;
    }
    return true;
}

bool Queries::Variant::GetVariantNames(QSqlQuery &query)
{
    query.prepare(VARIANT_NAMES);
    if (!query.exec())
    {
        qDebug() << "Error: Unable to execute query:" << query.lastError().text();
        return false;
    }
    return true;
}

bool Queries::Variant::GetTypeByName(QSqlQuery &query, Attrb::Variant::Name Name)
{
    query.prepare(VARIANT_TYPE__NAME);
    query.bindValue(":name", Name.m_Name);
    if (!query.exec())
    {
        qDebug() << "Error: Unable to execute query:" << query.lastError().text();
        return false;
    }
    return true;
}

bool Queries::Component::Add(QSqlQuery &query, Attrb::Variant::Name Variant_Name, Attrb::Component::Name Name, Attrb::Component::Manufacturer Manufacturer, Attrb::Component::Symbol Symbol, Attrb::Component::Datasheet Datasheet, Attrb::Component::MaxQuantity MaxQuantity){
    query.prepare(COMPONENT_ADD);
    query.bindValue(":variant", Variant_Name.m_Name);
    query.bindValue(":name", Name.m_Name);
    query.bindValue(":manuf", Manufacturer.m_Manufacturer);
    query.bindValue(":symbol", Symbol.m_Symbol);
    query.bindValue(":sheet", Datasheet.m_Datasheet);
    query.bindValue(":max", MaxQuantity.m_MaxQuantity);

    if (!query.exec())
    {
        qDebug() << "Error: Unable to execute query:" << query.lastError().text();
        return false;
    }
    return true;
}

bool Queries::Component::Delete(QSqlQuery &query, Attrb::Component::ID ID)
{
    query.prepare(COMPONENT_DELETE__ID);
    query.bindValue(":ID", ID.m_ID);

    if (!query.exec())
    {
        qDebug() << "Error: Unable to execute query:" << query.lastError().text();
        return false;
    }
    return true;
}

bool Queries::Component::Delete(QSqlQuery &query, Attrb::Component::Name Name)
{
    query.prepare(COMPONENT_DELETE__NAME);
    query.bindValue(":Name", Name.m_Name);

    if (!query.exec())
    {
        qDebug() << "Error: Unable to execute query:" << query.lastError().text();
        return false;
    }
    return true;
}

bool Queries::Component::CountNameSymbol(QSqlQuery &query, Attrb::Component::Name Name, Attrb::Component::Symbol Symbol){
    query.prepare(COMPONENT_COUNT__NAME_SYMBOL);
    query.bindValue(":symbol", Symbol.m_Symbol);
    query.bindValue(":name", Name.m_Name);

    if (!query.exec())
    {
        qDebug() << "Error: Unable to execute query:" << query.lastError().text();
        return false;
    }
    return true;
}

bool Queries::Component::GetNewestID(QSqlQuery &query)
{
    query.prepare(COMPONENT_NEWEST_ID);
    if (!query.exec())
    {
        qDebug() << "Error: Unable to execute query:" << query.lastError().text();
        return false;
    }
    return true;
}

bool Queries::Component::SelectWhere(QSqlQuery &query, Attrb::Component::ID ID)
{
    query.prepare(COMPONENT_SELECTWHERE__ID);
    query.bindValue(":ID", ID.m_ID);

    if (!query.exec())
    {
        qDebug() << "Error: Unable to execute query:" << query.lastError().text();
        return false;
    }
    return true;
}

bool Queries::Component::SelectWhere(QSqlQuery &query, Attrb::Variant::Name Name)
{
    query.prepare(COMPONENT_SELECTWHERE__VARIANT_NAME);
    query.bindValue(":Variant_Name", Name.m_Name);

    if (!query.exec())
    {
        qDebug() << "Error: Unable to execute query:" << query.lastError().text();
        return false;
    }
    return true;
}

bool Queries::Component::SelectWhere(QSqlQuery &query, Attrb::Variant::Type Type)
{
    query.prepare(COMPONENT_SELECTWHERE__VARIANT_TYPE);
    query.bindValue(":Variant_Type", Type.m_Type);

    if (!query.exec())
    {
        qDebug() << "Error: Unable to execute query:" << query.lastError().text();
        return false;
    }
    return true;
}

bool Queries::Component::SelectWhere(QSqlQuery &query, Attrb::Location::Rack Rack, Attrb::Location::Drawer Drawer)
{
    query.prepare(COMPONENT_SELECTWHERE__RACK_DRAWER);
    query.bindValue(":Location_Rack", Rack.m_Rack);
    query.bindValue(":Location_Drawer", Drawer.m_Drawer);

    if (!query.exec())
    {
        qDebug() << "Error: Unable to execute query:" << query.lastError().text();
        return false;
    }
    return true;
}

bool Queries::Component::SelectLike(QSqlQuery &query, Attrb::Component::Name substr_Name)
{
    query.prepare(COMPONENT_SELECTLIKE_NAME);
    query.bindValue(":substr_Name", substr_Name.m_Name);

    if (!query.exec())
    {
        qDebug() << "Error: Unable to execute query:" << query.lastError().text();
        return false;
    }
    return true;
}

bool Queries::Location::Add(QSqlQuery &query, Attrb::Location::Rack Rack, Attrb::Location::Drawer Drawer)
{
    query.prepare(LOCATION_ADD__RACK_DRAWER);
    query.bindValue(":Rack", Rack.m_Rack);
    query.bindValue(":Drawer", Drawer.m_Drawer);

    if (!query.exec())
    {
        qDebug() << "Error: Unable to execute query:" << query.lastError().text();
        return false;
    }
    return true;
}

bool Queries::Location::DeleteRack(QSqlQuery &query, Attrb::Location::Rack Rack)
{
    query.prepare(LOCATION_REMOVE__RACK);
    query.bindValue(":Rack", Rack.m_Rack);
    if (!query.exec())
    {
        qDebug() << "Error: Unable to execute query:" << query.lastError().text();
        return false;
    }
    return true;
}

bool Queries::Location::CountEmptyDrawers(QSqlQuery &query)
{
    query.prepare(LOCATION_COUNT_EMPTY_DRAWERS);
    if (!query.exec())
    {
        qDebug() << "Error: Unable to execute query:" << query.lastError().text();
        return false;
    }
    return true;
}

bool Queries::Location::CountNonemptyDrawersInRack(QSqlQuery &query, Attrb::Location::Rack Rack)
{
    query.prepare(LOCATION_COUNT_NONEMPTY_DRAWERS__RACK);
    query.bindValue(":Rack", Rack.m_Rack);
    if (!query.exec())
    {
        qDebug() << "Error: Unable to execute query:" << query.lastError().text();
        return false;
    }
    return true;
}

bool Queries::Location::IsRackInDatabase(QSqlQuery &query, Attrb::Location::Rack Rack)
{
    query.prepare(LOCATION_COUNT__RACK);
    query.bindValue(":Rack", Rack.m_Rack);
    if (!query.exec())
    {
        qDebug() << "Error: Unable to execute query:" << query.lastError().text();
        return false;
    }
    return true;
}

bool Queries::Location::GetEmptyDrawersInRack(QSqlQuery &query, Attrb::Location::Rack Rack)
{
    query.prepare(LOCATION_SELECT_EMPTY_DRAWERS__RACK);
    query.bindValue(":Rack", Rack.m_Rack);
    if (!query.exec())
    {
        qDebug() << "Error: Unable to execute query:" << query.lastError().text();
        return false;
    }
    return true;
}

bool Queries::Location::GetEmptyDrawers(QSqlQuery &query)
{
    query.prepare(LOCATION_SELECT_EMPTY_DRAWERS);
    if (!query.exec())
    {
        qDebug() << "Error: Unable to execute query:" << query.lastError().text();
        return false;
    }
    return true;
}

bool Queries::Location::FindNextRackNumber(QSqlQuery &query)
{
    query.prepare(LOCATION_FIND_NEXT_RACK_NO);
    if (!query.exec())
    {
        qDebug() << "Error: Unable to execute query:" << query.lastError().text();
        return false;
    }
    return true;
}

bool Queries::Location::SelectWhere(QSqlQuery &query, Attrb::Location::Rack Rack, Attrb::Location::Drawer Drawer)
{
    query.prepare(LOCATION_SELECTWHERE__RACK_DRAWER);
    query.bindValue(":Rack", Rack.m_Rack);
    query.bindValue(":Drawer", Drawer.m_Drawer);

    if (!query.exec())
    {
        qDebug() << "Error: Unable to execute query:" << query.lastError().text();
        return false;
    }
    return true;
}

bool Queries::Location::SelectWhere(QSqlQuery &query, Attrb::Location::Component_ID Component_ID)
{
    query.prepare(LOCATION_SELECTWHERE__COMPONENT_ID);
    query.bindValue(":Component_ID", Component_ID.m_Component_ID);

    if (!query.exec())
    {
        qDebug() << "Error: Unable to execute query:" << query.lastError().text();
        return false;
    }
    return true;
}

bool Queries::Location::UpdateSetQuantity(QSqlQuery &query, Attrb::Location::Component_ID Component_ID, Attrb::Location::Quantity Quantity)
{
    query.prepare(LOCATION_UPDATESET_QUANTITY__COMPONENT_ID);
    query.bindValue(":Component_ID", Component_ID.m_Component_ID);
    query.bindValue(":Quantity", Quantity.m_Quantity);

    if (!query.exec())
    {
        qDebug() << "Error: Unable to execute query:" << query.lastError().text();
        return false;
    }
    return true;
}

bool Queries::Location::UpdateSetComponentID(QSqlQuery &query, Attrb::Location::Component_ID new_Component_ID, Attrb::Location::Component_ID old_Component_ID)
{
    query.prepare(LOCATION_UPDATESET_COMPONENT_ID__COMPONENT_ID);
    query.bindValue(":New_Component_ID", new_Component_ID.m_Component_ID);
    query.bindValue(":Old_Component_ID", old_Component_ID.m_Component_ID);

    if (!query.exec())
    {
        qDebug() << "Error: Unable to execute query:" << query.lastError().text();
        return false;
    }
    return true;
}

bool Queries::Location::UpdateSetComponentID(QSqlQuery &query, Attrb::Location::Component_ID new_Component_ID, Attrb::Location::Rack Rack, Attrb::Location::Drawer Drawer)
{
    query.prepare(LOCATION_UPDATESET_COMPONENT_ID__RACK_DRAWER);
    query.bindValue(":Component_ID", new_Component_ID.m_Component_ID);
    query.bindValue(":Rack", Rack.m_Rack);
    query.bindValue(":Drawer", Drawer.m_Drawer);

    if (!query.exec())
    {
        qDebug() << "Error: Unable to execute query:" << query.lastError().text();
        return false;
    }
    return true;
}

bool Queries::Operation::InsertOperation(QSqlQuery &query, Attrb::Operation::User_Email User_Email)
{
    query.prepare(OPERATION_INSERTOPERATION);
    query.bindValue(":User_Email", User_Email.m_User_Email);

    if (!query.exec())
    {
        qDebug() << "Error: Unable to execute query:" << query.lastError().text();
        return false;
    }
    return true;
}

bool Queries::Operation::GetNewestID(QSqlQuery &query)
{
    query.prepare(OPERATION_NEWEST_ID);

    if (!query.exec())
    {
        qDebug() << "Error: Unable to execute query:" << query.lastError().text();
        return false;
    }
    return true;
}

bool Queries::Operation::InsertChangeUser(QSqlQuery &query, Attrb::Operation_ChangeUser::Operation_ID Operation_ID,
                        Attrb::Operation_ChangeUser::User_Email User_Email, Attrb::OperationType Type)
{
    query.prepare(OPERATION_INSERTCHANGEUSER);
    query.bindValue(":Operation_ID", Operation_ID.m_Operation_ID);
    query.bindValue(":User_Email", User_Email.m_User_Email);
    query.bindValue(":Type", QChar(static_cast<int>(Type)));
    if (!query.exec())
    {
        qDebug() << "Error: Unable to execute query:" << query.lastError().text();
        return false;
    }
    return true;
}               

bool Queries::Operation::InsertChangeRack(QSqlQuery &query, Attrb::Operation_ChangeRack::Operation_ID Operation_ID,
                                          Attrb::Operation_ChangeRack::RackNr RackNr, Attrb::OperationType Type)
{
    query.prepare(OPERATION_INSERTCHANGERACK);
    query.bindValue(":Operation_ID", Operation_ID.m_Operation_ID);
    query.bindValue(":RackNr", RackNr.m_Rack);
    query.bindValue(":Type", QChar(static_cast<int>(Type)));
    if (!query.exec())
    {
        qDebug() << "Error: Unable to execute query:" << query.lastError().text();
        return false;
    }
    return true;
}

bool Queries::Operation::InsertChangeComponent(QSqlQuery &query, Attrb::Operation_ChangeComponent::Operation_ID Operation_ID,
                                               Attrb::Operation_ChangeComponent::Component_ID Component_ID, Attrb::OperationType Type)
{
    query.prepare(OPERATION_INSERTCHANGECOMPONENT);
    query.bindValue(":Operation_ID", Operation_ID.m_Operation_ID);
    query.bindValue(":Component_ID", Component_ID.m_Component_ID);
    query.bindValue(":Type", QChar(static_cast<int>(Type)));
    if (!query.exec())
    {
        qDebug() << "Error: Unable to execute query:" << query.lastError().text();
        return false;
    }
    return true;
}

bool Queries::Operation::InsertChangeQuantity(QSqlQuery &query, Attrb::Operation_ChangeQuantity::Operation_ID Operation_ID,
                                              Attrb::Operation_ChangeQuantity::Component_ID Component_ID, Attrb::Operation_ChangeQuantity::Delta Delta)
{
    query.prepare(OPERATION_INSERTCHANGEQUANTITY);
    query.bindValue(":Operation_ID", Operation_ID.m_Operation_ID);
    query.bindValue(":Component_ID", Component_ID.m_Component_ID);
    query.bindValue(":Delta", Delta.m_Delta);
    if (!query.exec())
    {
        qDebug() << "Error: Unable to execute query:" << query.lastError().text();
        return false;
    }
    return true;
}

bool Queries::Operation::InsertMoveComponent(QSqlQuery &query, Attrb::Operation_MoveComponent::Operation_ID Operation_ID,
                                             Attrb::Operation_MoveComponent::Component_ID Component_ID,
                                             Attrb::Operation_MoveComponent::Old_Location_Rack Old_Location_Rack,
                                             Attrb::Operation_MoveComponent::Old_Location_Drawer Old_Location_Drawer,
                                             Attrb::Operation_MoveComponent::New_Location_Rack New_Location_Rack,
                                             Attrb::Operation_MoveComponent::New_Location_Drawer New_Location_Drawer)
{
    query.prepare(OPERATION_INSERTMOVECOMPONENT);
    query.bindValue(":Operation_ID", Operation_ID.m_Operation_ID);
    query.bindValue(":Component_ID", Component_ID.m_Component_ID);
    query.bindValue(":Old_Location_Rack", Old_Location_Rack.m_Old_Location_Rack);
    query.bindValue(":Old_Location_Drawer", Old_Location_Drawer.m_Old_Location_Drawer);
    query.bindValue(":New_Location_Rack", New_Location_Rack.m_New_Location_Rack);
    query.bindValue(":New_Location_Drawer", New_Location_Drawer.m_New_Location_Drawer);

    if (!query.exec())
    {
        qDebug() << "Error: Unable to execute query:" << query.lastError().text();
        return false;
    }
    return true;
}

bool Queries::Operation::InsertMoveComponentAdd(QSqlQuery &query, Attrb::Operation_MoveComponent::Operation_ID Operation_ID,
                                        Attrb::Operation_MoveComponent::Component_ID Component_ID,
                                        Attrb::Operation_MoveComponent::New_Location_Rack New_Location_Rack,
                                        Attrb::Operation_MoveComponent::New_Location_Drawer New_Location_Drawer)
{
    query.prepare(OPERATION_INSERTMOVECOMPONENT_ADD_COMPONENT);
    query.bindValue(":Operation_ID", Operation_ID.m_Operation_ID);
    query.bindValue(":Component_ID", Component_ID.m_Component_ID);
    query.bindValue(":New_Location_Rack", New_Location_Rack.m_New_Location_Rack);
    query.bindValue(":New_Location_Drawer", New_Location_Drawer.m_New_Location_Drawer);

    if (!query.exec())
    {
        qDebug() << "Error: Unable to execute query:" << query.lastError().text();
        return false;
    }
    return true;
}

bool Queries::Operation::SelectWhereChangeComponent(QSqlQuery &query,
                                                    QVariant DateTimeMin,
                                                    QVariant DateTimeMax,
                                                    QVariant User_Email,
                                                    QVariant Component_ID)
{
    query.prepare(OPERATION_SELECTWHERECHANGECOMPONENT__NOT_NULL);
    query.bindValue(":DateTimeMin", DateTimeMin);
    query.bindValue(":DateTimeMax", DateTimeMax);
    query.bindValue(":User_Email", User_Email);
    query.bindValue(":Component_ID", Component_ID);
    if (!query.exec())
    {
        qDebug() << query.lastError().text();
        return false;
    }
    return true;
}

bool Queries::Operation::SelectWhereChangeQuantity(QSqlQuery &query,
                                                   QVariant DateTimeMin,
                                                   QVariant DateTimeMax,
                                                   QVariant User_Email,
                                                   QVariant Component_ID)
{
    query.prepare(OPERATION_SELECTWHERECHANGEQUANTITY__NOT_NULL);
    query.bindValue(":DateTimeMin", DateTimeMin);
    query.bindValue(":DateTimeMax", DateTimeMax);
    query.bindValue(":User_Email", User_Email);
    query.bindValue(":Component_ID", Component_ID);
    if (!query.exec())
    {
        qDebug() << query.lastError().text();
        return false;
    }
    return true;
}

bool Queries::Operation::SelectWhereChangeRack(QSqlQuery &query,
                                               QVariant DateTimeMin,
                                               QVariant DateTimeMax,
                                               QVariant User_Email,
                                               QVariant RackNr)
{
    query.prepare(OPERATION_SELECTWHERECHANGERACK__NOT_NULL);
    query.bindValue(":DateTimeMin", DateTimeMin);
    query.bindValue(":DateTimeMax", DateTimeMax);
    query.bindValue(":User_Email", User_Email);
    query.bindValue(":RackNr", RackNr);
    if (!query.exec())
    {
        qDebug() << query.lastError().text();
        return false;
    }
    return true;
}

bool Queries::Operation::SelectWhereChangeUser(QSqlQuery &query,
                                               QVariant DateTimeMin,
                                               QVariant DateTimeMax,
                                               QVariant User_Email)
{
    query.prepare(OPERATION_SELECTWHERECHANGEUSER__NOT_NULL);
    query.bindValue(":DateTimeMin", DateTimeMin);
    query.bindValue(":DateTimeMax", DateTimeMax);
    query.bindValue(":User_Email", User_Email);
    if (!query.exec())
    {
        qDebug() << query.lastError().text();
        return false;
    }
    return true;
}

bool Queries::Operation::SelectWhereMoveComponent(QSqlQuery &query,
                                                  QVariant DateTimeMin,
                                                  QVariant DateTimeMax,
                                                  QVariant User_Email,
                                                  QVariant Component_ID,
                                                  QVariant Location_Rack,
                                                  QVariant Location_Drawer)
{
    query.prepare(OPERATION_SELECTWHEREMOVECOMPONENT__NOT_NULL);
    query.bindValue(":DateTimeMin", DateTimeMin);
    query.bindValue(":DateTimeMax", DateTimeMax);
    query.bindValue(":User_Email", User_Email);
    query.bindValue(":Component_ID", Component_ID);
    query.bindValue(":Location_Rack", Location_Rack);
    query.bindValue(":Location_Drawer", Location_Drawer);
    if (!query.exec())
    {
        qDebug() << query.lastError().text();
        return false;
    }
    return true;
}

bool Func::changeQuantity(QSqlQuery &query, int componentID, int delta)
{
    Attrb::Location::Component_ID Location_Component_ID(componentID);
    if (!Queries::Location::SelectWhere(query, Location_Component_ID))
        return false;

    if (!query.next())
        return false;

    int oldQuantity = query.value("Quantity").toInt();
    Attrb::Location::Quantity Quantity(oldQuantity + delta);

    if (!Queries::Location::UpdateSetQuantity(query, Location_Component_ID, Quantity))
        return false;

    DB::Attrb::Operation::User_Email User_Email(g_userEmail);
    if (!Queries::Operation::InsertOperation(query, User_Email))
        return false;

    if (!Queries::LastInsertRowID(query))
        return false;

    if (!query.next())
        return false;

    int tmp_operationID = query.value(0).toInt();
    Attrb::Operation_ChangeQuantity::Operation_ID Operation_ID(tmp_operationID);
    Attrb::Operation_ChangeQuantity::Component_ID Op_ChQ_Component_ID(componentID);
    Attrb::Operation_ChangeQuantity::Delta Op_ChQ_Delta(delta);

    if (!Queries::Operation::InsertChangeQuantity(query, Operation_ID, Op_ChQ_Component_ID, Op_ChQ_Delta))
        return false;
    return true;
}

bool Func::deleteComponent(QSqlQuery &query, int componentID)
{
    Attrb::Location::Component_ID Location_Component_ID(componentID);

    if (!Queries::Location::SelectWhere(query, Location_Component_ID))
        return false;

    if (!query.next())
        return false;

    int oldQuantity = query.value("Quantity").toInt();
    int oldRack = query.value("Rack").toInt();
    int oldDrawer = query.value("Drawer").toInt();

    if (oldQuantity != 0)
    {
        Attrb::Location::Quantity Quantity(0);

        if (!Queries::Location::UpdateSetQuantity(query, Location_Component_ID, Quantity))
            return false;

        DB::Attrb::Operation::User_Email User_Email(g_userEmail);
        if (!Queries::Operation::InsertOperation(query, User_Email))
            return false;

        if (!Queries::LastInsertRowID(query))
            return false;

        if (!query.next())
            return false;

        int operationID = query.value(0).toInt();
        Attrb::Operation_ChangeQuantity::Operation_ID ChQ_Operation_ID(operationID);
        Attrb::Operation_ChangeQuantity::Component_ID ChQ_Component_ID(componentID);
        Attrb::Operation_ChangeQuantity::Delta ChQ_Delta(-oldQuantity);

        if (!Queries::Operation::InsertChangeQuantity(query, ChQ_Operation_ID, ChQ_Component_ID, ChQ_Delta))
            return false;
    }

    Attrb::Location::Component_ID New_Location_Component_ID;
    Attrb::Location::Component_ID Old_Location_Component_ID(componentID);

    if (!Queries::Location::UpdateSetComponentID(query, New_Location_Component_ID, Old_Location_Component_ID))
        return false;

    Attrb::Operation_MoveComponent::Component_ID MC_Component_ID(componentID);
    Attrb::Operation_MoveComponent::Old_Location_Rack MC_Old_Location_Rack(oldRack);
    Attrb::Operation_MoveComponent::Old_Location_Drawer MC_Old_Location_Drawer(oldDrawer);
    Attrb::Operation_MoveComponent::New_Location_Rack MC_New_Location_Rack;
    Attrb::Operation_MoveComponent::New_Location_Drawer MC_New_Location_Drawer;

    DB::Attrb::Operation::User_Email User_Email(g_userEmail);
    if (!Queries::Operation::InsertOperation(query, User_Email))
        return false;

    if (!Queries::LastInsertRowID(query))
        return false;

    if (!query.next())
        return false;

    int operationID = query.value(0).toInt();

    Attrb::Operation_MoveComponent::Operation_ID MC_Operation_ID(operationID);

    if (!Queries::Operation::InsertMoveComponent(query, MC_Operation_ID, MC_Component_ID, MC_Old_Location_Rack, MC_Old_Location_Drawer, MC_New_Location_Rack, MC_New_Location_Drawer))
        return false;

    Attrb::Component::ID Component_Component_ID(componentID);
    if (!Queries::Component::Delete(query, Component_Component_ID))
        return false;

    if (!Queries::Operation::InsertOperation(query, User_Email))
        return false;

    if (!Queries::LastInsertRowID(query))
        return false;

    if (!query.next())
        return false;

    operationID = query.value(0).toInt();

    Attrb::Operation_ChangeComponent::Operation_ID ChC_Operation_ID(operationID);
    Attrb::Operation_ChangeComponent::Component_ID ChC_Component_ID(componentID);
    Attrb::OperationType ChC_Type(Attrb::OperationType::Remove);

    if (!Queries::Operation::InsertChangeComponent(query, ChC_Operation_ID, ChC_Component_ID, ChC_Type))
        return false;

    if (!Queries::Variant::DeleteNotExists(query))
        return false;
    return true;
}

#include "mainDatabase/moc_mainDatabase.cpp"
// #include "mainDatabase/mainDatabase.moc"