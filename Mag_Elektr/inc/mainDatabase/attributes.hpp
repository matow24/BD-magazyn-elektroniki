#ifndef _DB_ATTRIBUTES_HPP
#define _DB_ATTRIBUTES_HPP

#include <QDateTime>
#include <QString>
#include <QVariant>

namespace DB
{
    namespace Attrb
    {
        enum OperationType
        {
            Add = 'A',
            Modify = 'M',
            Remove = 'R'
        };

        enum Position
        {
            Employee = 'E',
            Logistician = 'L',
            Admin = 'A'
        };

        namespace Variant
        {
            struct Name
            {
                QVariant m_Name;
                explicit Name(QString arg_Name) : m_Name(arg_Name) {};
            };

            struct Type
            {
                QVariant m_Type;
                explicit Type(QString arg_Type) : m_Type(arg_Type) {};
            };
        } // namespace Variant

        namespace Component
        {
            struct ID
            {
                QVariant m_ID;
                explicit ID(int arg_ID) : m_ID(arg_ID) {};
            };

            struct Variant_Name
            {
                QVariant m_Variant_Name;
                explicit Variant_Name(QString arg_Variant_Name) : m_Variant_Name(arg_Variant_Name) {};
            };

            struct Name
            {
                QVariant m_Name;
                explicit Name(QString arg_Name) : m_Name(arg_Name) {};
            };

            struct Manufacturer
            {
                QVariant m_Manufacturer;
                explicit Manufacturer(QString arg_Manufacturer) : m_Manufacturer(arg_Manufacturer) {};
            };

            struct Symbol
            {
                QVariant m_Symbol;
                explicit Symbol(QString arg_Symbol) : m_Symbol(arg_Symbol) {};
            };

            struct Datasheet
            {
                QVariant m_Datasheet;
                explicit Datasheet() : m_Datasheet() {};
                explicit Datasheet(QString arg_Datasheet) : m_Datasheet(arg_Datasheet) {};
            };

            struct MaxQuantity
            {
                QVariant m_MaxQuantity;
                explicit MaxQuantity(int arg_MaxQuantity) : m_MaxQuantity(arg_MaxQuantity) {};
            };
        } // namespace Component

        namespace Location
        {
            struct Rack
            {
                QVariant m_Rack;
                explicit Rack(int arg_Rack) : m_Rack(arg_Rack) {};
            };

            struct Drawer
            {
                QVariant m_Drawer;
                explicit Drawer(int arg_Drawer) : m_Drawer(arg_Drawer) {};
            };

            struct Component_ID
            {
                QVariant m_Component_ID;
                explicit Component_ID() : m_Component_ID() {};
                explicit Component_ID(int arg_Component_ID) : m_Component_ID(arg_Component_ID) {};
            };

            struct Quantity
            {
                QVariant m_Quantity;
                explicit Quantity(int arg_Quantity) : m_Quantity(arg_Quantity) {};
            };
        } // namespace Location

        namespace Operation
        {
            struct ID
            {
                QVariant m_ID;
                explicit ID(int arg_ID) : m_ID(arg_ID) {};
            };

            struct DateTime
            {
                QVariant m_DateTime;
                explicit DateTime(QDateTime arg_DateTime) : m_DateTime(arg_DateTime.toString("yyyy-MM-dd HH:mm:ss")) {};
            };

            struct User_Email
            {
                QVariant m_User_Email;
                explicit User_Email(QString arg_User_Email) : m_User_Email(arg_User_Email) {};
            };
        } // namespace Operation

        namespace Operation_ChangeComponent
        {
            struct Operation_ID
            {
                QVariant m_Operation_ID;
                explicit Operation_ID(int arg_Operation_ID) : m_Operation_ID(arg_Operation_ID) {};
            };

            struct Component_ID
            {
                QVariant m_Component_ID;
                explicit Component_ID(int arg_Component_ID) : m_Component_ID(arg_Component_ID) {};
            };

            struct Type
            {
                QVariant m_Type;
                explicit Type(Attrb::OperationType arg_Type) : m_Type(static_cast<char>(arg_Type)) {};
            };
        } // namespace Operation_ChangeComponent

        namespace Operation_ChangeQuantity
        {
            struct Operation_ID
            {
                QVariant m_Operation_ID;
                explicit Operation_ID(int arg_Operation_ID) : m_Operation_ID(arg_Operation_ID) {};
            };

            struct Component_ID
            {
                QVariant m_Component_ID;
                explicit Component_ID(int arg_Component_ID) : m_Component_ID(arg_Component_ID) {};
            };

            struct Delta
            {
                QVariant m_Delta;
                explicit Delta(int arg_Delta) : m_Delta(arg_Delta) {};
            };
        } // namespace Operation_ChangeQuantity

        namespace Operation_ChangeRack
        {
            struct Operation_ID
            {
                QVariant m_Operation_ID;
                explicit Operation_ID(int arg_Operation_ID) : m_Operation_ID(arg_Operation_ID) {};
            };

            struct RackNr
            {
                QVariant m_Rack;
                explicit RackNr(int arg_Rack) : m_Rack(arg_Rack) {};
            };

            struct Type
            {
                QVariant m_Type;
                explicit Type(Attrb::OperationType arg_Type) : m_Type(static_cast<char>(arg_Type)) {};
            };
        } // namespace Operation_ChangeRack

        namespace Operation_ChangeUser
        {
            struct Operation_ID
            {
                QVariant m_Operation_ID;
                explicit Operation_ID(int arg_Operation_ID) : m_Operation_ID(arg_Operation_ID) {};
            };

            struct User_Email
            {
                QVariant m_User_Email;
                explicit User_Email(QString arg_User_Email) : m_User_Email(arg_User_Email) {};
            };

            struct Type
            {
                QVariant m_Type;
                explicit Type(Attrb::OperationType arg_Type) : m_Type(static_cast<char>(arg_Type)) {};
            };
        } // namespace Operation_ChangeUser

        namespace Operation_MoveComponent
        {
            struct Operation_ID
            {
                QVariant m_Operation_ID;
                explicit Operation_ID(int arg_Operation_ID) : m_Operation_ID(arg_Operation_ID) {};
            };

            struct Component_ID
            {
                QVariant m_Component_ID;
                explicit Component_ID(int arg_Component_ID) : m_Component_ID(arg_Component_ID) {};
            };

            struct Old_Location_Rack
            {
                QVariant m_Old_Location_Rack;
                explicit Old_Location_Rack() : m_Old_Location_Rack() {};
                explicit Old_Location_Rack(int arg_Old_Location_Rack) : m_Old_Location_Rack(arg_Old_Location_Rack) {};
            };

            struct Old_Location_Drawer
            {
                QVariant m_Old_Location_Drawer;
                explicit Old_Location_Drawer() : m_Old_Location_Drawer() {};
                explicit Old_Location_Drawer(int arg_Old_Location_Drawer) : m_Old_Location_Drawer(arg_Old_Location_Drawer) {};
            };

            struct New_Location_Rack
            {
                QVariant m_New_Location_Rack;
                explicit New_Location_Rack() : m_New_Location_Rack() {};
                explicit New_Location_Rack(int arg_New_Location_Rack) : m_New_Location_Rack(arg_New_Location_Rack) {};
            };

            struct New_Location_Drawer
            {
                QVariant m_New_Location_Drawer;
                explicit New_Location_Drawer() : m_New_Location_Drawer() {};
                explicit New_Location_Drawer(int arg_New_Location_Drawer) : m_New_Location_Drawer(arg_New_Location_Drawer) {};
            };
        } // namespace Operation_MoveComponent

        namespace User
        {
            struct Email
            {
                QVariant m_Email;
                explicit Email(QString arg_Email) : m_Email(arg_Email) {};
            };

            struct FirstName
            {
                QVariant m_FirstName;
                explicit FirstName(QString arg_FirstName) : m_FirstName(arg_FirstName) {};
            };

            struct LastName
            {
                QVariant m_LastName;
                explicit LastName(QString arg_LastName) : m_LastName(arg_LastName) {};
            };

            struct Password
            {
                QVariant m_Password;
                explicit Password(QString arg_Password) : m_Password(arg_Password) {};
            };

            struct Position
            {
                QVariant m_Position;
                explicit Position(Attrb::Position arg_Position) : m_Position(static_cast<char>(arg_Position)) {};
            };
        }

    } // namespace Attrb
} // namespace DB

#endif // _DB_ATTRIBUTES_HPP