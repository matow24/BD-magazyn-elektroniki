#include "componentsPage/component/editWidget.hpp"

#define ICON_CHART ":/icons/chart.png"
#define ICON_EDIT ":/icons/edit.png"
#define ICON_TRASH ":/icons/trash.png"

ComponentNS::EditWidget::EditWidget(QWidget *parent) : QWidget(parent)
{
    this->setObjectName("Component_EditWidget");
    this->setSizePolicy(QSizePolicy::MinimumExpanding, QSizePolicy::MinimumExpanding);
    this->setContentsMargins(0, 0, 0, 0);
    this->setAttribute(Qt::WA_StyledBackground, true);

    m_mainLayout = new QVBoxLayout(this);
    this->setLayout(m_mainLayout);
    m_mainLayout->setContentsMargins(0, 0, 0, 0);
    m_mainLayout->setSpacing(0);

    m_statisticsButton = new QPushButton(this);
    m_mainLayout->addWidget(m_statisticsButton, 1, Qt::AlignCenter);
    m_statisticsButton->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Minimum);
    m_statisticsButton->setIcon(QIcon(ICON_CHART));
    m_statisticsButton->setObjectName("Component_EditWidget_Button");

    m_editButton = new QPushButton(this);
    m_mainLayout->addWidget(m_editButton, 1, Qt::AlignCenter);
    m_editButton->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Minimum);
    m_editButton->setIcon(QIcon(ICON_EDIT));
    m_editButton->setObjectName("Component_EditWidget_Button");

    m_deleteButton = new QPushButton(this);
    m_mainLayout->addWidget(m_deleteButton, 1, Qt::AlignCenter);
    m_deleteButton->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Minimum);
    m_deleteButton->setIcon(QIcon(ICON_TRASH));
    m_deleteButton->setObjectName("Component_EditWidget_Button");

    connect(m_deleteButton, &QPushButton::clicked, this, &ComponentNS::EditWidget::deleteButtonClicked);
}

void ComponentNS::EditWidget::deleteButtonClicked()
{
    emit deleteComponent();
}

#include "componentsPage/component/moc_editWidget.cpp"
// #include "componentsPage/component/editWidget.moc"