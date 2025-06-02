#include "componentsPage/componentsPage/containerWidget.hpp"

const QMap<int, ComponentNS::ComponentWidget *> &ComponentsPageNS::ContainerWidget::getComponentWidgets() const
{
    return m_componentWidgets;
}

bool ComponentsPageNS::ContainerWidget::addComponentWidget(ComponentNS::ComponentWidget *componentWidget)
{
    if (componentWidget == nullptr)
        return false;

    int ID = componentWidget->getID();
    if (m_componentWidgets.contains(ID))
    {
        qDebug() << "ComponentNS widget with ID" << ID << "already exists.";
        return false;
    }
    componentWidget->setSizePolicy(QSizePolicy::MinimumExpanding, QSizePolicy::Fixed);
    m_containerLayout->addWidget(componentWidget);
    componentWidget->setParent(m_container);
    m_componentWidgets[ID] = componentWidget;

    connect(componentWidget, &ComponentNS::ComponentWidget::componentDeleted, this, &ComponentsPageNS::ContainerWidget::componentDeleted);

    m_containerLayout->invalidate();
    m_containerLayout->activate();

    return true;
}

bool ComponentsPageNS::ContainerWidget::removeComponentWidget(int ID)
{
    auto it = m_componentWidgets.find(ID);
    if (it == m_componentWidgets.end())
    {
        qDebug() << "ComponentNS widget with ID" << ID << "not found.";
        return false;
    }
    m_containerLayout->removeWidget(it.value());
    it.value()->hide();
    it.value()->setParent(nullptr);
    it.value()->deleteLater();
    m_componentWidgets.erase(it);

    m_containerLayout->invalidate();
    m_containerLayout->activate();

    return true;
}

bool ComponentsPageNS::ContainerWidget::removeComponentWidget(ComponentNS::ComponentWidget *componentWidget)
{
    if (componentWidget == nullptr)
        return false;

    int ID = componentWidget->getID();
    return removeComponentWidget(ID);
}

bool ComponentsPageNS::ContainerWidget::hideComponentWidget(ComponentNS::ComponentWidget *componentWidget)
{
    if (componentWidget == nullptr)
        return false;

    componentWidget->hide();
    return true;
}

bool ComponentsPageNS::ContainerWidget::showComponentWidget(ComponentNS::ComponentWidget *componentWidget)
{
    if (componentWidget == nullptr)
        return false;

    componentWidget->show();
    return true;
}

void ComponentsPageNS::ContainerWidget::resetContainer()
{
    auto it = m_componentWidgets.begin();
    while (it != m_componentWidgets.end())
    {
        m_containerLayout->removeWidget(it.value());
        it.value()->setParent(nullptr);
        it.value()->deleteLater();
        it = m_componentWidgets.erase(it);
    }

    m_containerLayout->invalidate();
    m_containerLayout->activate();
}

ComponentsPageNS::ContainerWidget::ContainerWidget(QWidget *parent) : QScrollArea(parent)
{
    this->setObjectName("ComponentsPageNS_ContainerWidget");
    this->setSizePolicy(QSizePolicy::MinimumExpanding, QSizePolicy::Minimum);
    this->setContentsMargins(0, 0, 0, 0);

    m_container = new QWidget(this);
    this->setWidget(m_container);
    m_container->setSizePolicy(QSizePolicy::MinimumExpanding, QSizePolicy::Minimum);
    m_container->setContentsMargins(0, 0, 0, 0);
    this->setWidgetResizable(true);

    m_containerLayout = new QVBoxLayout(m_container);
    m_container->setLayout(m_containerLayout);
    m_containerLayout->setContentsMargins(20, 20, 20, 20);
    m_containerLayout->setSpacing(20);
    m_containerLayout->setSizeConstraint(QLayout::SetMinAndMaxSize);
}

void ComponentsPageNS::ContainerWidget::componentDeleted(ComponentNS::ComponentWidget *component)
{
    m_containerLayout->removeWidget(component);
    m_containerLayout->invalidate();
    m_containerLayout->activate();
    m_componentWidgets.remove(component->getID());
}

#include "componentsPage/componentsPage/moc_containerWidget.cpp"
// #include "componentsPage/componentsPage/containerWidget.moc"