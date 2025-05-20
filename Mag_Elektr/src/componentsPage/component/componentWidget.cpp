#include "componentsPage/component/componentWidget.hpp"
#include "componentsPage/component/parametersWidget.hpp"

#define QUERY_COMPONENT_GET_BY_ID                       \
    "SELECT "                                           \
    "C.ID, "                                            \
    "V.Name AS Variant_Name, "                          \
    "V.Type AS Variant_Type, "                          \
    "C.Name, "                                          \
    "C.Manufacturer, "                                  \
    "C.Symbol, "                                        \
    "C.Datasheet, "                                     \
    "C.MaksQuantity, "                                  \
    "L.Quantity AS Location_Quantity, "                 \
    "L.Rack AS Location_Rack, "                         \
    "L.Drawer AS Location_Drawer "                      \
    "FROM Component AS C "                              \
    "JOIN Variant AS V ON C.Variant_Name = V.Name "     \
    "LEFT JOIN Location AS L ON C.ID = L.Component_ID " \
    "WHERE C.ID = ?;"

#define QUERY_LOCATION_UPDATE_BY_ID \
    "UPDATE Location "              \
    "SET Quantity = ? "             \
    "WHERE Component_ID = ?;"

#define QUERY_OPERATION_INSERT \
    "INSERT INTO "             \
    "Operation (DateTime) "    \
    "VALUES (DATETIME('now'));"

#define QUERY_OPERATION_GET_ID "SELECT last_insert_rowid() AS Operation_ID;"

#define QUERY_OPERATION_CHANGEQUANTITY_INSERT                       \
    "INSERT INTO "                                                  \
    "Operation_ChangeQuantity (Operation_ID, Component_ID, Delta) " \
    "VALUES (?, ?, ?);"

int ComponentNS::ComponentWidget::getID() const
{
    return m_ID;
}

ComponentNS::ParametersWidget &ComponentNS::ComponentWidget::getParametersWidget()
{
    return *m_parametersWidget;
}

ComponentNS::QuantityWidget &ComponentNS::ComponentWidget::getQuantityWidget()
{
    return *m_quantityWidget;
}

ComponentNS::ComponentWidget::ComponentWidget(int ID, UserRole userRole, QWidget *parent) : QWidget(parent)
{
    m_ID = ID;
    m_userRole = userRole;

    this->setObjectName("Component_Component");
    this->setSizePolicy(QSizePolicy::MinimumExpanding, QSizePolicy::Preferred);
    this->setContentsMargins(5, 5, 5, 5);
    this->setAttribute(Qt::WA_StyledBackground, true);

    m_mainLayout = new QHBoxLayout(this);
    this->setLayout(m_mainLayout);
    m_mainLayout->setContentsMargins(0, 0, 0, 0);
    m_mainLayout->setSpacing(0);

    m_parametersWidget = new ComponentNS::ParametersWidget(this);
    m_mainLayout->addWidget(m_parametersWidget, 6);

    if (m_userRole == UserRole::Employee || m_userRole == UserRole::Logistician || m_userRole == UserRole::Admin)
    {
        m_spacer1 = new QWidget(this);
        m_mainLayout->addWidget(m_spacer1, 1);

        m_quantityWidget = new ComponentNS::QuantityWidget(this);
        m_mainLayout->addWidget(m_quantityWidget, 3);

        connect(m_quantityWidget, &ComponentNS::QuantityWidget::deltaConfirmed, this, &ComponentNS::ComponentWidget::deltaConfirmed);
    }

    if (m_userRole == UserRole::Logistician || m_userRole == UserRole::Admin)
    {
        m_spacer2 = new QWidget(this);
        m_mainLayout->addWidget(m_spacer2, 1);

        m_editWidget = new ComponentNS::EditWidget(this);
        m_mainLayout->addWidget(m_editWidget, 0);

        connect(m_editWidget, &ComponentNS::EditWidget::deleteComponent, this, &ComponentNS::ComponentWidget::deleteComponent);
    }
}

void ComponentNS::ComponentWidget::deltaConfirmed(int &delta)
{
    QSqlQuery query;
    query.prepare(QUERY_LOCATION_UPDATE_BY_ID);
    query.addBindValue(m_quantityWidget->getQuantity() + delta);
    query.addBindValue(m_ID);
    if (!query.exec())
    {
        qDebug() << "Error: Unable to execute query:" << query.lastError().text();
        return;
    }

    m_quantityWidget->setQuantity(m_quantityWidget->getQuantity() + delta);

    query.prepare(QUERY_OPERATION_INSERT);
    if (!query.exec())
    {
        qDebug() << "Error: Unable to execute query:" << query.lastError().text();
        return;
    }

    query.prepare(QUERY_OPERATION_GET_ID);
    if (!query.exec())
    {
        qDebug() << "Error: Unable to execute query:" << query.lastError().text();
        return;
    }
    if (!query.next())
    {
        qDebug() << "Error: Unable to get last insert row ID:" << query.lastError().text();
        return;
    }
    int operationID = query.value("Operation_ID").toInt();
    
    query.prepare(QUERY_OPERATION_CHANGEQUANTITY_INSERT);
    query.addBindValue(operationID);
    query.addBindValue(m_ID);
    query.addBindValue(delta);
    if (!query.exec())
    {
        qDebug() << "Error: Unable to execute query:" << query.lastError().text();
        return;
    }
}

void ComponentNS::ComponentWidget::deleteComponent()
{
    emit componentDeleted(this);
    this->deleteLater();
}

void ComponentNS::ComponentWidget::updateComponent()
{
    QSqlQuery query;
    query.prepare(QUERY_COMPONENT_GET_BY_ID);
    query.addBindValue(m_ID);
    if (!query.exec())
    {
        qDebug() << "Error: Unable to execute query:" << query.lastError().text();
        return;
    }

    if (query.next())
    {
        QString variantName = query.value("Variant_Name").toString();
        QString variantType = query.value("Variant_Type").toString();
        QString name = query.value("Name").toString();
        QString manufacturer = query.value("Manufacturer").toString();
        QString symbol = query.value("Symbol").toString();
        QString datasheet = query.value("Datasheet").toString();

        int maxQuantity = query.value("MaksQuantity").toInt();
        int locationQuantity = query.value("Location_Quantity").toInt();
        int locationRack = query.value("Location_Rack").toInt();
        int locationDrawer = query.value("Location_Drawer").toInt();

        if (m_parametersWidget != nullptr)
        {
            m_parametersWidget->setVariantName(variantName);
            m_parametersWidget->setVariantType(variantType);
            m_parametersWidget->setName(name);
            m_parametersWidget->setManufacturer(manufacturer);
            m_parametersWidget->setSymbol(symbol);
            m_parametersWidget->setDatasheet(datasheet);
        }

        if (m_quantityWidget != nullptr)
        {
            m_quantityWidget->setMaxQuantity(maxQuantity);
            m_quantityWidget->setQuantity(locationQuantity);
            m_quantityWidget->setRack(locationRack);
            m_quantityWidget->setDrawer(locationDrawer);
        }
    }
}

#include "componentsPage/component/moc_componentWidget.cpp"
// #include "componentsPage/component/componentWidget.moc"