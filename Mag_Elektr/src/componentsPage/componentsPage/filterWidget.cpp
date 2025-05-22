#include "componentsPage/componentsPage/filterWidget.hpp"

#define ICON_LOCATION ":/icons/location.png"
#define ICON_SEARCH ":/icons/search.png"
#define ICON_UNDO ":/icons/undo.png"

ComponentsPageNS::FilterWidget::FilterWidget(ContainerWidget *containerWidget, TreeFilterWidget *treeFilterWidget, QWidget *parent) : QWidget(parent)
{
    m_containerWidget = containerWidget;
    m_treeFilterWidget = treeFilterWidget;

    this->setObjectName("ComponentsPageNS_FilterWidget");
    this->setSizePolicy(QSizePolicy::MinimumExpanding, QSizePolicy::MinimumExpanding);
    this->setContentsMargins(5, 5, 5, 5);

    m_mainLayout = new QVBoxLayout(this);
    this->setLayout(m_mainLayout);
    m_mainLayout->setContentsMargins(0, 0, 0, 0);
    m_mainLayout->setSpacing(10);

    m_enableButtons = new QWidget(this);
    m_mainLayout->addWidget(m_enableButtons);

    m_enableButtonsLayout = new QHBoxLayout(m_enableButtons);
    m_enableButtons->setLayout(m_enableButtonsLayout);
    m_enableButtonsLayout->setContentsMargins(0, 0, 0, 0);
    m_enableButtonsLayout->setSpacing(5);

    if (g_userRole != UserRole::Guest)
    {
        m_enableLocationButton = new QPushButton(this);
        m_enableButtonsLayout->addWidget(m_enableLocationButton, 0);
        m_enableLocationButton->setObjectName("ComponentsPageNS_FilterWidget_Button");
        m_enableLocationButton->setCheckable(true);
        m_enableLocationButton->setChecked(false);
        m_enableLocationButton->setSizePolicy(QSizePolicy::MinimumExpanding, QSizePolicy::MinimumExpanding);
        m_enableLocationButton->setIcon(QIcon(ICON_LOCATION));
    }

    m_enableButtonsFiller = new QWidget(this);
    m_enableButtonsLayout->addWidget(m_enableButtonsFiller, 1);
    m_enableButtonsFiller->setSizePolicy(QSizePolicy::MinimumExpanding, QSizePolicy::MinimumExpanding);

    m_enableSearchButton = new QPushButton(this);
    m_enableButtonsLayout->addWidget(m_enableSearchButton, 0);
    m_enableSearchButton->setObjectName("ComponentsPageNS_FilterWidget_Button");
    m_enableSearchButton->setCheckable(true);
    m_enableSearchButton->setChecked(false);
    m_enableSearchButton->setSizePolicy(QSizePolicy::MinimumExpanding, QSizePolicy::MinimumExpanding);
    m_enableSearchButton->setIcon(QIcon(ICON_SEARCH));

    m_resetButton = new QPushButton(this);
    m_enableButtonsLayout->addWidget(m_resetButton, 0);
    m_resetButton->setObjectName("ComponentsPageNS_FilterWidget_Button");
    m_resetButton->setSizePolicy(QSizePolicy::MinimumExpanding, QSizePolicy::MinimumExpanding);
    m_resetButton->setIcon(QIcon(ICON_UNDO));

    if (g_userRole != UserRole::Guest)
    {
        m_locationField = new QWidget(this);
        m_mainLayout->addWidget(m_locationField);

        m_locationFieldLayout = new QHBoxLayout(m_locationField);
        m_locationField->setLayout(m_locationFieldLayout);
        m_locationFieldLayout->setContentsMargins(0, 0, 0, 0);
        m_locationFieldLayout->setSpacing(5);

        m_locationFieldRack = new QLineEdit(this);
        m_locationFieldLayout->addWidget(m_locationFieldRack, 1);
        m_locationFieldRack->setObjectName("ComponentsPageNS_FilterWidget_LineEdit");
        m_locationFieldRack->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::MinimumExpanding);
        m_locationFieldRack->setPlaceholderText(tr("Półka"));

        m_locationFieldRackValidator = new QIntValidator(1, INT_MAX, this);
        m_locationFieldRack->setValidator(m_locationFieldRackValidator);

        m_locationFieldDrawer = new QLineEdit(this);
        m_locationFieldLayout->addWidget(m_locationFieldDrawer, 1);
        m_locationFieldDrawer->setObjectName("ComponentsPageNS_FilterWidget_LineEdit");
        m_locationFieldDrawer->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::MinimumExpanding);
        m_locationFieldDrawer->setPlaceholderText(tr("Regał"));

        m_locationFieldDrawerValidator = new QIntValidator(1, INT_MAX, this);
        m_locationFieldDrawer->setValidator(m_locationFieldDrawerValidator);

        m_locationFieldButton = new QPushButton(this);
        m_locationFieldLayout->addWidget(m_locationFieldButton, 0);
        m_locationFieldButton->setObjectName("ComponentsPageNS_FilterWidget_Button");
        m_locationFieldButton->setSizePolicy(QSizePolicy::MinimumExpanding, QSizePolicy::MinimumExpanding);
        m_locationFieldButton->setText(tr("Szukaj"));
        m_locationFieldButton->setEnabled(false);

        m_locationField->setVisible(false);
    }

    m_searchField = new QWidget(this);
    m_mainLayout->addWidget(m_searchField);

    QHBoxLayout *searchFieldLayout = new QHBoxLayout(m_searchField);
    m_searchField->setLayout(searchFieldLayout);
    searchFieldLayout->setContentsMargins(0, 0, 0, 0);
    searchFieldLayout->setSpacing(5);

    m_searchFieldText = new QLineEdit(this);
    searchFieldLayout->addWidget(m_searchFieldText, 1);
    m_searchFieldText->setObjectName("ComponentsPageNS_FilterWidget_LineEdit");
    m_searchFieldText->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::MinimumExpanding);
    m_searchFieldText->setPlaceholderText(tr("Nazwa"));

    m_searchFieldValidator = new QRegularExpressionValidator(QRegularExpression("[a-zA-Z0-9_]+"), this);
    m_searchFieldText->setValidator(m_searchFieldValidator);

    m_searchFieldButton = new QPushButton(this);
    searchFieldLayout->addWidget(m_searchFieldButton, 0);
    m_searchFieldButton->setObjectName("ComponentsPageNS_FilterWidget_Button");
    m_searchFieldButton->setSizePolicy(QSizePolicy::MinimumExpanding, QSizePolicy::MinimumExpanding);
    m_searchFieldButton->setText(tr("Szukaj"));
    m_searchFieldButton->setEnabled(false);

    m_searchField->setVisible(false);

    if (g_userRole != UserRole::Guest)
    {
        connect(m_enableLocationButton, &QPushButton::toggled, this, &ComponentsPageNS::FilterWidget::toggleLocationField);
        connect(m_locationFieldRack, &QLineEdit::textEdited, this, &ComponentsPageNS::FilterWidget::locationTextChanged);
        connect(m_locationFieldDrawer, &QLineEdit::textEdited, this, &ComponentsPageNS::FilterWidget::locationTextChanged);
    }

    connect(m_enableSearchButton, &QPushButton::toggled, this, &ComponentsPageNS::FilterWidget::toggleSearchField);
    connect(m_searchFieldText, &QLineEdit::textEdited, this, &ComponentsPageNS::FilterWidget::searchTextChanged);

    connect(m_resetButton, &QPushButton::clicked, this, &ComponentsPageNS::FilterWidget::resetAll);
    connect(m_locationFieldButton, &QPushButton::clicked, this, &ComponentsPageNS::FilterWidget::findByLocation);
    connect(m_searchFieldButton, &QPushButton::clicked, this, &ComponentsPageNS::FilterWidget::findByName);
}

void ComponentsPageNS::FilterWidget::toggleLocationField(bool checked)
{
    if (checked)
    {
        m_locationField->show();
        m_locationFieldRack->setText("");
        m_locationFieldDrawer->setText("");
        m_enableSearchButton->setEnabled(false);
    }
    else
    {
        m_locationField->hide();
        m_enableSearchButton->setEnabled(true);
    }
}

void ComponentsPageNS::FilterWidget::toggleSearchField(bool checked)
{
    if (checked)
    {
        m_searchField->show();
        m_searchFieldText->setText("");
        m_enableLocationButton->setEnabled(false);
    }
    else
    {
        m_searchField->hide();
        m_enableLocationButton->setEnabled(true);
    }
}

void ComponentsPageNS::FilterWidget::findByLocation()
{
    if (m_locationFieldRack->hasAcceptableInput() && m_locationFieldDrawer->hasAcceptableInput())
    {
        QString rack = m_locationFieldRack->text();
        QString drawer = m_locationFieldDrawer->text();

        m_treeFilterWidget->setFromDataBaseFlag(true);
        m_treeFilterWidget->resetVariants();
        m_treeFilterWidget->disableAll();

        QSqlQuery query;
        DB::Attrb::Location::Rack queryRack(rack.toInt());
        DB::Attrb::Location::Drawer queryDrawer(drawer.toInt());
        if (!DB::Queries::Component::SelectWhere(query, queryRack, queryDrawer))
            return;

        while (query.next())
        {
            QString variantName = query.value("Variant_Name").toString();
            QString variantType = query.value("Variant_Type").toString();
            QString name = query.value("Name").toString();
            QString manufacturer = query.value("Manufacturer").toString();
            QString symbol = query.value("Symbol").toString();
            QString datasheet = query.value("Datasheet").toString();

            int ID = query.value("ID").toInt();
            int maxQuantity = query.value("MaxQuantity").toInt();
            int locationQuantity = query.value("Location_Quantity").toInt();
            int locationRack = query.value("Location_Rack").toInt();
            int locationDrawer = query.value("Location_Drawer").toInt();

            ComponentNS::ComponentWidget *componentWidget = new ComponentNS::ComponentWidget(ID, m_containerWidget);

            componentWidget->getParametersWidget().setID(ID);
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

            m_treeFilterWidget->enableTreeWidgetItem(variantType, variantName);
        }
    }
}

void ComponentsPageNS::FilterWidget::findByName()
{
    if (m_searchFieldText->hasAcceptableInput())
    {
        QString substr_Name = m_searchFieldText->text();

        m_treeFilterWidget->setFromDataBaseFlag(true);
        m_treeFilterWidget->resetVariants();
        m_treeFilterWidget->disableAll();

        QSqlQuery query;
        DB::Attrb::Component::Name queryName(substr_Name);
        if (!DB::Queries::Component::SelectLike(query, queryName))
            return;

        while (query.next())
        {
            QString variantName = query.value("Variant_Name").toString();
            QString variantType = query.value("Variant_Type").toString();
            QString name = query.value("Name").toString();
            QString manufacturer = query.value("Manufacturer").toString();
            QString symbol = query.value("Symbol").toString();
            QString datasheet = query.value("Datasheet").toString();

            int ID = query.value("ID").toInt();
            int maxQuantity = query.value("MaxQuantity").toInt();
            int locationQuantity = query.value("Location_Quantity").toInt();
            int locationRack = query.value("Location_Rack").toInt();
            int locationDrawer = query.value("Location_Drawer").toInt();

            ComponentNS::ComponentWidget *componentWidget = new ComponentNS::ComponentWidget(ID, m_containerWidget);

            componentWidget->getParametersWidget().setID(ID);
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

            m_treeFilterWidget->enableTreeWidgetItem(variantType, variantName);
        }
    }
}

void ComponentsPageNS::FilterWidget::resetAll()
{
    if (g_userRole != UserRole::Guest)
    {
        m_locationFieldRack->setText("");
        m_locationFieldDrawer->setText("");
        m_enableLocationButton->setChecked(false);
        m_enableLocationButton->setEnabled(true);
        m_locationField->setVisible(false);
    }

    m_searchFieldText->setText("");
    m_enableSearchButton->setChecked(false);
    m_enableSearchButton->setEnabled(true);
    m_searchField->setVisible(false);

    m_treeFilterWidget->resetVariants();
    m_containerWidget->resetContainer();
}

void ComponentsPageNS::FilterWidget::locationTextChanged(const QString &text)
{
    if (m_locationFieldRack->hasAcceptableInput() && m_locationFieldDrawer->hasAcceptableInput())
        m_locationFieldButton->setEnabled(true);
    else
        m_locationFieldButton->setEnabled(false);
}

void ComponentsPageNS::FilterWidget::searchTextChanged(const QString &text)
{
    if (m_searchFieldText->hasAcceptableInput())
        m_searchFieldButton->setEnabled(true);
    else
        m_searchFieldButton->setEnabled(false);
}

#include "componentsPage/componentsPage/moc_filterWidget.cpp"
// #include "componentsPage/componentsPage/filterWidget.moc"