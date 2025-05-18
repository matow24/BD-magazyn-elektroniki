#include "componentsPage/filterTypeSpace.hpp"

#define ICON_SEARCH ":/icons/search.png"
#define ICON_LOCATION ":/icons/location.png"

void FilterTypeSpace::scanVariants()
{
    m_treeWidget->clear();

    QSqlQuery query;
    query.prepare("SELECT * FROM Variant");

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
        for (int i = 0; i < m_treeWidget->topLevelItemCount(); ++i)
        {
            if (m_treeWidget->topLevelItem(i)->text(0) == typeText)
            {
                typeTreeNode = m_treeWidget->topLevelItem(i);
                break;
            }
        }

        if (typeTreeNode == nullptr)
        {
            typeTreeNode = new QTreeWidgetItem(m_treeWidget);
            m_treeWidget->addTopLevelItem(typeTreeNode);
            typeTreeNode->setText(0, typeText);
            typeTreeNode->setFlags(typeTreeNode->flags() | Qt::ItemIsUserCheckable);
            typeTreeNode->setCheckState(0, Qt::Unchecked);
        }

        QTreeWidgetItem *nameTreeNode = new QTreeWidgetItem(typeTreeNode);
        nameTreeNode->setText(0, nameText);
        nameTreeNode->setFlags(nameTreeNode->flags() | Qt::ItemIsUserCheckable);
        nameTreeNode->setCheckState(0, Qt::Unchecked);
    }

    m_treeWidget->sortItems(0, Qt::AscendingOrder);
}

FilterTypeSpace::FilterTypeSpace(UserRole userRole, QWidget *parent) : QWidget(parent)
{
    m_userRole = userRole;

    this->setStyleSheet(MainStyle::StyleSheets[STYLE_COMPONENTSPAGE_NAME]);

    m_mainLayout = new QVBoxLayout(this);
    this->setLayout(m_mainLayout);
    m_mainLayout->setContentsMargins(0, 0, 0, 0);
    m_mainLayout->setSpacing(0);
    m_mainLayout->setAlignment(Qt::AlignTop);
    m_mainLayout->setSizeConstraint(QLayout::SetMinimumSize);

    m_enableButtons = new QWidget(this);
    m_mainLayout->addWidget(m_enableButtons);
    QHBoxLayout *enableButtonsLayout = new QHBoxLayout(m_enableButtons);
    m_enableButtons->setLayout(enableButtonsLayout);
    enableButtonsLayout->setContentsMargins(10, 10, 10, 10);
    enableButtonsLayout->setSpacing(10);

    if (m_userRole != UserRole::Guest)
    {
        m_enableLocationButton = new QPushButton(this);
        enableButtonsLayout->addWidget(m_enableLocationButton);
        m_enableLocationButton->setCheckable(true);
        m_enableLocationButton->setChecked(false);
        m_enableLocationButton->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Minimum);
        m_enableLocationButton->setIcon(QIcon(ICON_LOCATION));
        m_enableLocationButton->setIconSize(QSize(24, 24));

        connect(m_enableLocationButton, &QPushButton::toggled, this, &FilterTypeSpace::toggleLocationField);
    }

    m_enableButtonsFiller = new QWidget(this);
    enableButtonsLayout->addWidget(m_enableButtonsFiller);
    m_enableButtonsFiller->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Minimum);
    m_enableButtonsFiller->setStyleSheet("background-color: transparent;");

    m_enableSearchButton = new QPushButton(this);
    enableButtonsLayout->addWidget(m_enableSearchButton);
    m_enableSearchButton->setCheckable(true);
    m_enableSearchButton->setChecked(false);
    m_enableSearchButton->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Minimum);
    m_enableSearchButton->setIcon(QIcon(ICON_SEARCH));
    m_enableSearchButton->setIconSize(QSize(24, 24));

    connect(m_enableSearchButton, &QPushButton::toggled, this, &FilterTypeSpace::toggleSearchField);

    if (m_userRole != UserRole::Guest)
    {
        m_locationField = new QWidget(this);
        m_mainLayout->addWidget(m_locationField);
        QHBoxLayout *locationFieldLayout = new QHBoxLayout(m_locationField);
        m_locationField->setLayout(locationFieldLayout);
        locationFieldLayout->setContentsMargins(10, 10, 10, 10);
        locationFieldLayout->setSpacing(10);
        m_locationField->setVisible(false);

        m_locationFieldRack = new QLineEdit(this);
        m_locationField->layout()->addWidget(m_locationFieldRack);
        m_locationFieldRack->setPlaceholderText(tr("Nr. Regału"));
        m_locationFieldRack->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Minimum);
        m_locationFieldRack->setMinimumHeight(30);

        m_locationFieldShelf = new QLineEdit(this);
        m_locationField->layout()->addWidget(m_locationFieldShelf);
        m_locationFieldShelf->setPlaceholderText(tr("Nr. Półki"));
        m_locationFieldShelf->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Minimum);
        m_locationFieldShelf->setMinimumHeight(30);

        m_locationFieldButton = new QPushButton(this);
        m_locationField->layout()->addWidget(m_locationFieldButton);
        m_locationFieldButton->setText(tr("Szukaj"));
        m_locationFieldButton->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Minimum);
        m_locationFieldButton->setMinimumHeight(30);
    }

    m_searchField = new QWidget(this);
    m_mainLayout->addWidget(m_searchField);
    QHBoxLayout *searchFieldLayout = new QHBoxLayout(m_searchField);
    m_searchField->setLayout(searchFieldLayout);
    searchFieldLayout->setContentsMargins(10, 10, 10, 10);
    searchFieldLayout->setSpacing(10);
    m_searchField->setVisible(false);

    m_searchFieldText = new QLineEdit(this);
    m_searchField->layout()->addWidget(m_searchFieldText);
    m_searchFieldText->setPlaceholderText(tr("Szukaj"));
    m_searchFieldText->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Minimum);
    m_searchFieldText->setMinimumHeight(30);

    m_searchFieldButton = new QPushButton(this);
    m_searchField->layout()->addWidget(m_searchFieldButton);
    m_searchFieldButton->setText(tr("Szukaj"));
    m_searchFieldButton->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Minimum);
    m_searchFieldButton->setMinimumHeight(30);

    m_separator = new QFrame(this);
    m_mainLayout->addWidget(m_separator);
    m_separator->setFrameShape(QFrame::HLine);

    m_signaledVariants = new QMap<QString, QVector<QString>>();

    m_treeWidget = new QTreeWidget(this);
    m_mainLayout->addWidget(m_treeWidget);
    m_treeWidget->setHeaderHidden(true);
    this->scanVariants();
    connect(m_treeWidget, &QTreeWidget::itemChanged, this, &FilterTypeSpace::treeWidgetItemChanged);
}

void FilterTypeSpace::toggleLocationField(bool checked)
{
    if (checked)
    {
        m_locationField->show();
        m_enableLocationButton->setChecked(true);
        m_enableSearchButton->setCheckable(false);
    }
    else
    {
        m_locationField->hide();
        m_enableLocationButton->setChecked(false);
        m_enableSearchButton->setCheckable(true);
    }
}

void FilterTypeSpace::toggleSearchField(bool checked)
{
    if (checked)
    {
        m_searchField->show();
        m_enableSearchButton->setChecked(true);
        m_enableLocationButton->setCheckable(false);
    }
    else
    {
        m_searchField->hide();
        m_enableSearchButton->setChecked(false);
        m_enableLocationButton->setCheckable(true);
    }
}

void FilterTypeSpace::treeWidgetItemChanged(QTreeWidgetItem *item, int column)
{
    Qt::CheckState checkState = item->checkState(column);
    bool isTypeNode = (item->parent() == nullptr);
    if (isTypeNode)
    {
        m_recurrencyFlag = true;
        m_signaledVariants->clear();
        for (int i = 0; i < item->childCount(); i++)
        {
            QTreeWidgetItem *nameNode = item->child(i);
            if (nameNode->checkState(0) != checkState)
                nameNode->setCheckState(0, checkState);
        }
        if (m_signaledVariants->size() > 0)
        {
            emit variantItemChanged(*m_signaledVariants, checkState == Qt::Checked);
            m_signaledVariants->clear();
        }
        m_recurrencyFlag = false;
    }
    else
    {
        (*m_signaledVariants)[item->parent()->text(0)].append(item->text(0));
        if (!m_recurrencyFlag)
        {
            emit variantItemChanged(*m_signaledVariants, checkState == Qt::Checked);
            m_signaledVariants->clear();
        }
    }
}

#include "componentsPage/moc_filterTypeSpace.cpp"
// #include "componentsPage/filterTypeSpace.moc"