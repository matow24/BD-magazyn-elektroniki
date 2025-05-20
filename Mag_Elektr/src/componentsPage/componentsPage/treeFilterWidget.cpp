#include "componentsPage/componentsPage/treeFilterWidget.hpp"

#define QUERY_VARIANT_ALL "SELECT * FROM Variant"

#define QUERY_COMPONENT_ALL_RELATED_BY_VARIANT_NAME     \
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
    "WHERE V.Name = ?;"

#define QUERY_COMPONENT_ALL_RELATED_BY_VARIANT_TYPE     \
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
    "WHERE V.Type = ?;"

void ComponentsPageNS::TreeFilterWidget::addByVariantName(QString variantName)
{
    if (m_fromDataBaseFlag)
        this->addFromDatabaseByVariantName(variantName);
    else
        this->showInContainerByVariantName(variantName);
}

void ComponentsPageNS::TreeFilterWidget::removeByVariantName(QString variantName)
{
    if (m_fromDataBaseFlag)
        this->removeFromDatabaseByVariantName(variantName);
    else
        this->hideInContainerByVariantName(variantName);
}

void ComponentsPageNS::TreeFilterWidget::addByVariantType(QString variantType)
{
    if (m_fromDataBaseFlag)
        this->addFromDatabaseByVariantType(variantType);
    else
        this->showInContainerByVariantType(variantType);
}

void ComponentsPageNS::TreeFilterWidget::removeByVariantType(QString variantType)
{
    if (m_fromDataBaseFlag)
        this->removeFromDatabaseByVariantType(variantType);
    else
        this->hideInContainerByVariantType(variantType);
}

void ComponentsPageNS::TreeFilterWidget::hideInContainerByVariantName(QString variantName)
{
    for (auto it = m_containerWidget->getComponentWidgets().begin(); it != m_containerWidget->getComponentWidgets().end();)
    {
        if (it.value()->getParametersWidget().getVariantName() == variantName)
            m_containerWidget->hideComponentWidget(it.value());
        else
            ++it;
    }
}

void ComponentsPageNS::TreeFilterWidget::showInContainerByVariantName(QString variantName)
{
    for (auto it = m_containerWidget->getComponentWidgets().begin(); it != m_containerWidget->getComponentWidgets().end();)
    {
        if (it.value()->getParametersWidget().getVariantName() == variantName)
            m_containerWidget->showComponentWidget(it.value());
        else
            ++it;
    }
}

void ComponentsPageNS::TreeFilterWidget::hideInContainerByVariantType(QString variantType)
{
    for (auto it = m_containerWidget->getComponentWidgets().begin(); it != m_containerWidget->getComponentWidgets().end();)
    {
        if (it.value()->getParametersWidget().getVariantType() == variantType)
            m_containerWidget->hideComponentWidget(it.value());
        else
            ++it;
    }
}

void ComponentsPageNS::TreeFilterWidget::showInContainerByVariantType(QString variantType)
{
    for (auto it = m_containerWidget->getComponentWidgets().begin(); it != m_containerWidget->getComponentWidgets().end();)
    {
        if (it.value()->getParametersWidget().getVariantType() == variantType)
            m_containerWidget->showComponentWidget(it.value());
        else
            ++it;
    }
}

void ComponentsPageNS::TreeFilterWidget::addFromDatabaseByVariantName(QString variantName)
{
    QSqlQuery query;
    query.prepare(QUERY_COMPONENT_ALL_RELATED_BY_VARIANT_NAME);
    query.addBindValue(variantName);

    if (!query.exec())
    {
        qDebug() << "Error: Unable to execute query:" << query.lastError().text();
        return;
    }

    while (query.next())
    {
        int ID = query.value("ID").toInt();
        if (m_containerWidget->getComponentWidgets().contains(ID))
            continue;

        // QString variantName = query.value("Variant_Name").toString();
        QString variantType = query.value("Variant_Type").toString();
        QString name = query.value("Name").toString();
        QString manufacturer = query.value("Manufacturer").toString();
        QString symbol = query.value("Symbol").toString();
        QString datasheet = query.value("Datasheet").toString();

        int maxQuantity = query.value("MaksQuantity").toInt();
        int locationQuantity = query.value("Location_Quantity").toInt();
        int locationRack = query.value("Location_Rack").toInt();
        int locationDrawer = query.value("Location_Drawer").toInt();

        ComponentNS::ComponentWidget *componentWidget = new ComponentNS::ComponentWidget(ID, m_userRole, m_containerWidget);

        componentWidget->getParametersWidget().setVariantName(variantName);
        componentWidget->getParametersWidget().setVariantType(variantType);
        componentWidget->getParametersWidget().setName(name);
        componentWidget->getParametersWidget().setManufacturer(manufacturer);
        componentWidget->getParametersWidget().setSymbol(symbol);
        componentWidget->getParametersWidget().setDatasheet(datasheet);

        componentWidget->getQuantityWidget().setMaxQuantity(maxQuantity);
        componentWidget->getQuantityWidget().setQuantity(locationQuantity);
        componentWidget->getQuantityWidget().setRack(locationRack);
        componentWidget->getQuantityWidget().setDrawer(locationDrawer);

        m_containerWidget->addComponentWidget(componentWidget);

        connect(componentWidget, &ComponentNS::ComponentWidget::componentDeleted, this, &ComponentsPageNS::TreeFilterWidget::rescanVariants);
    }
}

void ComponentsPageNS::TreeFilterWidget::removeFromDatabaseByVariantName(QString variantName)
{
    for (auto it = m_containerWidget->getComponentWidgets().begin(); it != m_containerWidget->getComponentWidgets().end();)
    {
        if (it.value()->getParametersWidget().getVariantName() == variantName)
        {
            m_containerWidget->removeComponentWidget(it.value());
            it = m_containerWidget->getComponentWidgets().begin(); //!< @todo fix this
        }
        else
            ++it;
    }
}

void ComponentsPageNS::TreeFilterWidget::addFromDatabaseByVariantType(QString variantType)
{
    QSqlQuery query;
    query.prepare(QUERY_COMPONENT_ALL_RELATED_BY_VARIANT_TYPE);
    query.addBindValue(variantType);

    if (!query.exec())
    {
        qDebug() << "Error: Unable to execute query:" << query.lastError().text();
        return;
    }

    while (query.next())
    {
        int ID = query.value("ID").toInt();
        if (m_containerWidget->getComponentWidgets().contains(ID))
            continue;

        QString variantName = query.value("Variant_Name").toString();
        // QString variantType = query.value("Variant_Type").toString();
        QString name = query.value("Name").toString();
        QString manufacturer = query.value("Manufacturer").toString();
        QString symbol = query.value("Symbol").toString();
        QString datasheet = query.value("Datasheet").toString();

        int maxQuantity = query.value("MaksQuantity").toInt();
        int locationQuantity = query.value("Location_Quantity").toInt();
        int locationRack = query.value("Location_Rack").toInt();
        int locationDrawer = query.value("Location_Drawer").toInt();

        ComponentNS::ComponentWidget *componentWidget = new ComponentNS::ComponentWidget(ID, m_userRole, m_containerWidget);

        componentWidget->getParametersWidget().setVariantName(variantName);
        componentWidget->getParametersWidget().setVariantType(variantType);
        componentWidget->getParametersWidget().setName(name);
        componentWidget->getParametersWidget().setManufacturer(manufacturer);
        componentWidget->getParametersWidget().setSymbol(symbol);
        componentWidget->getParametersWidget().setDatasheet(datasheet);

        componentWidget->getQuantityWidget().setMaxQuantity(maxQuantity);
        componentWidget->getQuantityWidget().setQuantity(locationQuantity);
        componentWidget->getQuantityWidget().setRack(locationRack);
        componentWidget->getQuantityWidget().setDrawer(locationDrawer);

        m_containerWidget->addComponentWidget(componentWidget);

        connect(componentWidget, &ComponentNS::ComponentWidget::componentDeleted, this, &ComponentsPageNS::TreeFilterWidget::rescanVariants);
    }
}

void ComponentsPageNS::TreeFilterWidget::removeFromDatabaseByVariantType(QString variantType)
{
    for (auto it = m_containerWidget->getComponentWidgets().begin(); it != m_containerWidget->getComponentWidgets().end();)
    {
        if (it.value()->getParametersWidget().getVariantType() == variantType)
        {
            m_containerWidget->removeComponentWidget(it.value());
            it = m_containerWidget->getComponentWidgets().begin(); //!< @todo fix this
        }
        else
            ++it;
    }
}

void ComponentsPageNS::TreeFilterWidget::setFromDataBaseFlag(bool fromDataBaseFlag)
{
    m_fromDataBaseFlag = fromDataBaseFlag;
}

void ComponentsPageNS::TreeFilterWidget::enableTreeWidgetItem(QString variantType, QString variantName)
{
    m_treeRecurrencyFlag = true;
    for (int i = 0; i < this->topLevelItemCount(); ++i)
    {
        if (this->topLevelItem(i)->text(0) != variantType)
            continue;

        QTreeWidgetItem *typeTreeNode = this->topLevelItem(i);
        typeTreeNode->setDisabled(false);
        for (int j = 0; j < typeTreeNode->childCount(); ++j)
        {
            if (typeTreeNode->child(j)->text(0) != variantName)
                continue;

            QTreeWidgetItem *nameTreeNode = typeTreeNode->child(j);
            nameTreeNode->setDisabled(false);
        }
    }
    m_treeRecurrencyFlag = false;
}

void ComponentsPageNS::TreeFilterWidget::disableAll()
{
    m_treeRecurrencyFlag = true;
    for (int i = 0; i < this->topLevelItemCount(); ++i)
    {
        QTreeWidgetItem *typeTreeNode = this->topLevelItem(i);
        typeTreeNode->setDisabled(true);
        for (int j = 0; j < typeTreeNode->childCount(); ++j)
        {
            QTreeWidgetItem *nameTreeNode = typeTreeNode->child(j);
            nameTreeNode->setDisabled(true);
        }
    }
    m_treeRecurrencyFlag = false;
}

void ComponentsPageNS::TreeFilterWidget::rescanVariants()
{
    QSqlQuery query;
    query.prepare(QUERY_VARIANT_ALL);

    if (!query.exec())
    {
        qDebug() << "Error: Unable to execute query:" << query.lastError().text();
        return;
    }

    QMap<QString, QSet<QString>> actualVariants;

    while (query.next())
    {
        QString nameText = query.value("Name").toString();
        QString typeText = query.value("Type").toString();

        if (!actualVariants.contains(typeText))
            actualVariants[typeText] = QSet<QString>();

        actualVariants[typeText].insert(nameText);
    }

    for (int i = 0; i < this->topLevelItemCount(); ++i)
    {
        QTreeWidgetItem *typeTreeNode = this->topLevelItem(i);
        if (!actualVariants.contains(typeTreeNode->text(0)))
        {
            while (typeTreeNode->childCount() > 0)
            {
                QTreeWidgetItem *nameTreeNode = typeTreeNode->takeChild(0);
                delete nameTreeNode;
            }
            this->takeTopLevelItem(i);
            delete typeTreeNode;
        }
        else
        {
            for (int j = 0; j < typeTreeNode->childCount(); ++j)
            {
                if (!actualVariants[typeTreeNode->text(0)].contains(typeTreeNode->child(j)->text(0)))
                {
                    QTreeWidgetItem *nameTreeNode = typeTreeNode->takeChild(j);
                    delete nameTreeNode;
                }
            }
        }
    }
}

void ComponentsPageNS::TreeFilterWidget::resetVariants()
{
    this->clear();
    m_containerWidget->resetContainer();

    QSqlQuery query;
    query.prepare(QUERY_VARIANT_ALL);

    if (!query.exec())
    {
        qDebug() << "Error: Unable to execute query:" << query.lastError().text();
        return;
    }

    while (query.next())
    {
        QString nameText = query.value("Name").toString();
        QString typeText = query.value("Type").toString();

        QTreeWidgetItem *typeTreeNode = nullptr;
        for (int i = 0; i < this->topLevelItemCount(); ++i)
        {
            if (this->topLevelItem(i)->text(0) == typeText)
            {
                typeTreeNode = this->topLevelItem(i);
                break;
            }
        }

        if (typeTreeNode == nullptr)
        {
            typeTreeNode = new QTreeWidgetItem(this);
            this->addTopLevelItem(typeTreeNode);
            typeTreeNode->setText(0, typeText);
            typeTreeNode->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled | Qt::ItemIsUserCheckable);
            typeTreeNode->setCheckState(0, Qt::Unchecked);
        }

        QTreeWidgetItem *nameTreeNode = new QTreeWidgetItem(typeTreeNode);
        nameTreeNode->setText(0, nameText);
        nameTreeNode->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled | Qt::ItemIsUserCheckable);
        nameTreeNode->setCheckState(0, Qt::Unchecked);
    }

    this->sortItems(0, Qt::AscendingOrder);
}

ComponentsPageNS::TreeFilterWidget::TreeFilterWidget(ContainerWidget *containerWidget, UserRole userRole, QWidget *parent) : QTreeWidget(parent)
{
    m_userRole = userRole;
    m_containerWidget = containerWidget;

    this->setObjectName("ComponentsPageNS_TreeFilterWidget");
    this->setSizePolicy(QSizePolicy::MinimumExpanding, QSizePolicy::MinimumExpanding);
    this->setContentsMargins(5, 5, 5, 5);
    this->setHeaderHidden(true);

    connect(this, &QTreeWidget::itemChanged, this, &ComponentsPageNS::TreeFilterWidget::itemChanged);
}

void ComponentsPageNS::TreeFilterWidget::itemChanged(QTreeWidgetItem *item, int column)
{
    if (item == nullptr)
        return;

    if (m_treeRecurrencyFlag)
        return;

    Qt::CheckState checkState = item->checkState(column);
    bool isTypeNode = (item->parent() == nullptr);
    if (isTypeNode)
    {
        m_treeRecurrencyFlag = true;
        if (checkState == Qt::Checked)
            this->addByVariantType(item->text(0));
        else if (checkState == Qt::Unchecked)
            this->removeByVariantType(item->text(0));
        for (int i = 0; i < item->childCount(); i++)
        {
            QTreeWidgetItem *childItem = item->child(i);
            if (childItem->checkState(0) != checkState)
                childItem->setCheckState(0, checkState);
        }
        m_treeRecurrencyFlag = false;
    }
    else
    {
        if (checkState == Qt::Checked)
            this->addByVariantName(item->text(0));
        else if (checkState == Qt::Unchecked)
            this->removeByVariantName(item->text(0));
    }
}

#include "componentsPage/componentsPage/moc_treeFilterWidget.cpp"
// #include "componentsPage/componentsPage/treeFilterWidget.moc"