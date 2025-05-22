#ifndef _DB_QUERIES_HPP
#define _DB_QUERIES_HPP

#define DATABASE_TYPE "QSQLITE"

#define LAST_INSERT_ROW_ID "SELECT last_insert_rowid() AS ID;"

#define VARIANT_SELECT "SELECT * FROM Variant;"

#define VARIANT_DELETENOTEXISTS                       \
    "DELETE FROM Variant "                            \
    "WHERE NOT EXISTS ( "                             \
    "   SELECT 1 "                                    \
    "   FROM Component "                              \
    "   WHERE Component.Variant_Name = Variant.Name " \
    ");"

#define COMPONENT_DELETE__ID \
    "DELETE FROM Component " \
    "WHERE ID = :ID;"

#define COMPONENT_SELECTWHERE__ID                       \
    "SELECT "                                           \
    "   C.ID, "                                         \
    "   V.Name AS Variant_Name, "                       \
    "   V.Type AS Variant_Type, "                       \
    "   C.Name, "                                       \
    "   C.Manufacturer, "                               \
    "   C.Symbol, "                                     \
    "   C.Datasheet, "                                  \
    "   C.MaxQuantity, "                                \
    "   L.Quantity AS Location_Quantity, "              \
    "   L.Rack AS Location_Rack, "                      \
    "   L.Drawer AS Location_Drawer "                   \
    "FROM Component AS C "                              \
    "JOIN Variant AS V ON C.Variant_Name = V.Name "     \
    "LEFT JOIN Location AS L ON C.ID = L.Component_ID " \
    "WHERE C.ID = :ID;"

#define COMPONENT_SELECTWHERE__VARIANT_NAME             \
    "SELECT "                                           \
    "   C.ID, "                                         \
    "   V.Name AS Variant_Name, "                       \
    "   V.Type AS Variant_Type, "                       \
    "   C.Name, "                                       \
    "   C.Manufacturer, "                               \
    "   C.Symbol, "                                     \
    "   C.Datasheet, "                                  \
    "   C.MaxQuantity, "                                \
    "   L.Quantity AS Location_Quantity, "              \
    "   L.Rack AS Location_Rack, "                      \
    "   L.Drawer AS Location_Drawer "                   \
    "FROM Component AS C "                              \
    "JOIN Variant AS V ON C.Variant_Name = V.Name "     \
    "LEFT JOIN Location AS L ON C.ID = L.Component_ID " \
    "WHERE V.Name = :Variant_Name;"

#define COMPONENT_SELECTWHERE__VARIANT_TYPE             \
    "SELECT "                                           \
    "   C.ID, "                                         \
    "   V.Name AS Variant_Name, "                       \
    "   V.Type AS Variant_Type, "                       \
    "   C.Name, "                                       \
    "   C.Manufacturer, "                               \
    "   C.Symbol, "                                     \
    "   C.Datasheet, "                                  \
    "   C.MaxQuantity, "                                \
    "   L.Quantity AS Location_Quantity, "              \
    "   L.Rack AS Location_Rack, "                      \
    "   L.Drawer AS Location_Drawer "                   \
    "FROM Component AS C "                              \
    "JOIN Variant AS V ON C.Variant_Name = V.Name "     \
    "LEFT JOIN Location AS L ON C.ID = L.Component_ID " \
    "WHERE V.Type = :Variant_Type;"

#define COMPONENT_SELECTWHERE__RACK_DRAWER              \
    "SELECT "                                           \
    "   C.ID, "                                         \
    "   V.Name AS Variant_Name, "                       \
    "   V.Type AS Variant_Type, "                       \
    "   C.Name, "                                       \
    "   C.Manufacturer, "                               \
    "   C.Symbol, "                                     \
    "   C.Datasheet, "                                  \
    "   C.MaxQuantity, "                                \
    "   L.Quantity AS Location_Quantity, "              \
    "   L.Rack AS Location_Rack, "                      \
    "   L.Drawer AS Location_Drawer "                   \
    "FROM Component AS C "                              \
    "JOIN Variant AS V ON C.Variant_Name = V.Name "     \
    "LEFT JOIN Location AS L ON C.ID = L.Component_ID " \
    "WHERE L.Rack = :Location_Rack AND L.Drawer = :Location_Drawer;"

#define COMPONENT_SELECTLIKE_NAME                       \
    "SELECT "                                           \
    "   C.ID, "                                         \
    "   V.Name AS Variant_Name, "                       \
    "   V.Type AS Variant_Type, "                       \
    "   C.Name, "                                       \
    "   C.Manufacturer, "                               \
    "   C.Symbol, "                                     \
    "   C.Datasheet, "                                  \
    "   C.MaxQuantity, "                                \
    "   L.Quantity AS Location_Quantity, "              \
    "   L.Rack AS Location_Rack, "                      \
    "   L.Drawer AS Location_Drawer "                   \
    "FROM Component AS C "                              \
    "JOIN Variant AS V ON C.Variant_Name = V.Name "     \
    "LEFT JOIN Location AS L ON C.ID = L.Component_ID " \
    "WHERE C.Name LIKE '%' || :substr_Name || '%';"

#define LOCATION_SELECTWHERE__RACK_DRAWER \
    "SELECT * "                           \
    "FROM Location "                      \
    "WHERE Rack = :Rack AND Drawer = :Drawer;"

#define LOCATION_SELECTWHERE__COMPONENT_ID \
    "SELECT * "                            \
    "FROM Location "                       \
    "WHERE Component_ID = :Component_ID;"

#define LOCATION_UPDATESET_QUANTITY__COMPONENT_ID \
    "UPDATE Location "                            \
    "SET Quantity = :Quantity "                   \
    "WHERE Component_ID = :Component_ID;"

#define LOCATION_UPDATESET_COMPONENT_ID__COMPONENT_ID \
    "UPDATE Location "                                \
    "SET Component_ID = :New_Component_ID "           \
    "WHERE Component_ID = :Old_Component_ID;"

#define LOCATION_UPDATESET_COMPONENT_ID__RACK_DRAWER \
    "UPDATE Location "                               \
    "SET Component_ID = :Component_ID "              \
    "WHERE Rack = :Rack AND Drawer = :Drawer;"

#define OPERATION_INSERTOPERATION       \
    "INSERT INTO "                      \
    "Operation (DateTime, User_Email) " \
    "VALUES (DATETIME('now'), :User_Email);"

#define OPERATION_INSERTCHANGECOMPONENT                             \
    "INSERT INTO "                                                  \
    "Operation_ChangeComponent (Operation_ID, Component_ID, Type) " \
    "VALUES (:Operation_ID, :Component_ID, :Type);"

#define OPERATION_INSERTCHANGEQUANTITY                              \
    "INSERT INTO "                                                  \
    "Operation_ChangeQuantity (Operation_ID, Component_ID, Delta) " \
    "VALUES (:Operation_ID, :Component_ID, :Delta);"

#define OPERATION_INSERTMOVECOMPONENT                                                                                                       \
    "INSERT INTO "                                                                                                                          \
    "Operation_MoveComponent (Operation_ID, Component_ID, Old_Location_Rack, Old_Location_Drawer, New_Location_Rack, New_Location_Drawer) " \
    "VALUES (:Operation_ID, :Component_ID, :Old_Location_Rack, :Old_Location_Drawer, :New_Location_Rack, :New_Location_Drawer);"

#define OPERATION_SELECTWHERECHANGECOMPONENT__NOT_NULL            \
    "SELECT "                                                     \
    "  O.ID, "                                                    \
    "  O.DateTime, "                                              \
    "  O.User_Email, "                                            \
    "  O_CC.Component_ID, "                                       \
    "  O_CC.Type "                                                \
    "FROM Operation_ChangeComponent AS O_CC "                     \
    "JOIN Operation AS O ON O_CC.Operation_ID = O.ID "            \
    "WHERE (:DateTimeMin IS NULL OR O.DateTime >= :DateTimeMin) " \
    "  AND (:DateTimeMax IS NULL OR O.DateTime <= :DateTimeMax) " \
    "  AND (:User_Email IS NULL OR O.User_Email = :User_Email) "  \
    "  AND (:Component_ID IS NULL OR O_CC.Component_ID = :Component_ID);"

#define OPERATION_SELECTWHERECHANGEQUANTITY__NOT_NULL             \
    "SELECT "                                                     \
    "  O.ID, "                                                    \
    "  O.DateTime, "                                              \
    "  O.User_Email, "                                            \
    "  O_CQ.Component_ID, "                                       \
    "  O_CQ.Delta "                                               \
    "FROM Operation_ChangeQuantity AS O_CQ "                      \
    "JOIN Operation AS O ON O_CQ.Operation_ID = O.ID "            \
    "WHERE (:DateTimeMin IS NULL OR O.DateTime >= :DateTimeMin) " \
    "  AND (:DateTimeMax IS NULL OR O.DateTime <= :DateTimeMax) " \
    "  AND (:User_Email IS NULL OR O.User_Email = :User_Email) "  \
    "  AND (:Component_ID IS NULL OR O_CQ.Component_ID = :Component_ID);"

#define OPERATION_SELECTWHERECHANGERACK__NOT_NULL                 \
    "SELECT "                                                     \
    "  O.ID, "                                                    \
    "  O.DateTime, "                                              \
    "  O.User_Email, "                                            \
    "  O_CR.RackNr, "                                             \
    "  O_CR.Type "                                                \
    "FROM Operation_ChangeRack AS O_CR "                          \
    "JOIN Operation AS O ON O_CR.Operation_ID = O.ID "            \
    "WHERE (:DateTimeMin IS NULL OR O.DateTime >= :DateTimeMin) " \
    "  AND (:DateTimeMax IS NULL OR O.DateTime <= :DateTimeMax) " \
    "  AND (:User_Email IS NULL OR O.User_Email = :User_Email) "  \
    "  AND (:RackNr IS NULL OR O_CR.RackNr = :RackNr);"

#define OPERATION_SELECTWHERECHANGEUSER__NOT_NULL                 \
    "SELECT "                                                     \
    "  O.ID, "                                                    \
    "  O.DateTime, "                                              \
    "  O.User_Email, "                                            \
    "  O_CU.User_Email AS Modified_User_Email, "                  \
    "  O_CU.Type "                                                \
    "FROM Operation_ChangeUser AS O_CU "                          \
    "JOIN Operation AS O ON O_CU.Operation_ID = O.ID "            \
    "WHERE (:DateTimeMin IS NULL OR O.DateTime >= :DateTimeMin) " \
    "  AND (:DateTimeMax IS NULL OR O.DateTime <= :DateTimeMax) " \
    "  AND (:User_Email IS NULL OR O.User_Email = :User_Email OR O_CU.User_Email = :User_Email);"

#define OPERATION_SELECTWHEREMOVECOMPONENT__NOT_NULL                                                                        \
    "SELECT "                                                                                                               \
    "  O.ID, "                                                                                                              \
    "  O.DateTime, "                                                                                                        \
    "  O.User_Email, "                                                                                                      \
    "  O_MC.Component_ID, "                                                                                                 \
    "  O_MC.Old_Location_Rack, "                                                                                            \
    "  O_MC.Old_Location_Drawer, "                                                                                          \
    "  O_MC.New_Location_Rack, "                                                                                            \
    "  O_MC.New_Location_Drawer "                                                                                           \
    "FROM Operation_MoveComponent AS O_MC "                                                                                 \
    "JOIN Operation AS O ON O_MC.Operation_ID = O.ID "                                                                      \
    "WHERE (:DateTimeMin IS NULL OR O.DateTime >= :DateTimeMin) "                                                           \
    "  AND (:DateTimeMax IS NULL OR O.DateTime <= :DateTimeMax) "                                                           \
    "  AND (:User_Email IS NULL OR O.User_Email = :User_Email) "                                                            \
    "  AND (:Component_ID IS NULL OR O_MC.Component_ID = :Component_ID) "                                                   \
    "  AND (:Location_Rack IS NULL OR O_MC.Old_Location_Rack = :Location_Rack OR O_MC.New_Location_Rack = :Location_Rack) " \
    "  AND (:Location_Drawer IS NULL OR O_MC.Old_Location_Drawer = :Location_Drawer OR O_MC.New_Location_Drawer = :Location_Drawer);"

#endif // _DB_QUERIES_HPP