#include "componentsPage/component/componentWidget.hpp"
#include "componentsPage/component/parametersWidget.hpp"

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

ComponentNS::ComponentWidget::ComponentWidget(int ID, QWidget *parent) : QWidget(parent)
{
    m_ID = ID;

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

    if (g_userRole != UserRole::Guest)
    {
        m_spacer1 = new QWidget(this);
        m_mainLayout->addWidget(m_spacer1, 1);

        m_quantityWidget = new ComponentNS::QuantityWidget(this);
        m_mainLayout->addWidget(m_quantityWidget, 3);

        connect(m_quantityWidget, &ComponentNS::QuantityWidget::deltaConfirmed, this, &ComponentNS::ComponentWidget::deltaConfirmed);
    }

    if (g_userRole == UserRole::Logistician || g_userRole == UserRole::Admin)
    {
        m_spacer2 = new QWidget(this);
        m_mainLayout->addWidget(m_spacer2, 1);

        m_editWidget = new ComponentNS::EditWidget(this);
        m_mainLayout->addWidget(m_editWidget, 0);

        connect(m_editWidget, &ComponentNS::EditWidget::deleteComponent, this, &ComponentNS::ComponentWidget::deleteComponent);
        connect(m_editWidget, &ComponentNS::EditWidget::statisticsComponent, this, &ComponentNS::ComponentWidget::statisticsComponent);
    }
}

void ComponentNS::ComponentWidget::deltaConfirmed(int &delta)
{
    QSqlQuery query;
    if (!DB::Func::changeQuantity(query, m_ID, delta))
        return;
    this->updateComponent();
}

void ComponentNS::ComponentWidget::deleteComponent()
{
    QSqlQuery query;
    if (!DB::Func::deleteComponent(query, m_ID))
        return;
    emit componentDeleted(this);
    this->deleteLater();
}

void ComponentNS::ComponentWidget::statisticsComponent()
{
}

void ComponentNS::ComponentWidget::updateComponent()
{
    QSqlQuery query;
    DB::Attrb::Component::ID queryID(m_ID);
    if (!DB::Queries::Component::SelectWhere(query, queryID))
        return;

    if (query.next())
    {
        QString variantName = query.value("Variant_Name").toString();
        QString variantType = query.value("Variant_Type").toString();
        QString name = query.value("Name").toString();
        QString manufacturer = query.value("Manufacturer").toString();
        QString symbol = query.value("Symbol").toString();
        QString datasheet = query.value("Datasheet").toString();

        int maxQuantity = query.value("MaxQuantity").toInt();
        int locationQuantity = query.value("Location_Quantity").toInt();
        int locationRack = query.value("Location_Rack").toInt();
        int locationDrawer = query.value("Location_Drawer").toInt();

        if (m_parametersWidget != nullptr)
        {
            m_parametersWidget->setID(m_ID);
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