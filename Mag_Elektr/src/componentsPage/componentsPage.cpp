#include "componentsPage/componentsPage.hpp"

ComponentsPage::ComponentsPage(UserRole userRole, QWidget *parent) : QWidget(parent)
{
    m_userRole = userRole;

    this->setStyleSheet(MainStyle::StyleSheets[STYLE_COMPONENTSPAGE_NAME]);
    this->setSizePolicy(QSizePolicy::MinimumExpanding, QSizePolicy::MinimumExpanding);
    this->setContentsMargins(0, 0, 0, 0);

    m_mainLayout = new QHBoxLayout(this); //!< @note temporary
    this->setLayout(m_mainLayout);
    m_mainLayout->setContentsMargins(0, 0, 0, 0);
    m_mainLayout->setSpacing(0);

    m_filterPanel = new QWidget(this);
    m_mainLayout->addWidget(m_filterPanel, 0);
    m_filterPanel->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Minimum);
    m_filterPanel->setContentsMargins(0, 0, 0, 0);

    m_filterPanelLayout = new QVBoxLayout(m_filterPanel);
    m_filterPanel->setLayout(m_filterPanelLayout);
    m_filterPanelLayout->setContentsMargins(0, 10, 0, 10);
    m_filterPanelLayout->setSpacing(10);

    m_mainFrame = new QFrame(this);
    m_mainLayout->addWidget(m_mainFrame, 0);
    m_mainFrame->setObjectName("ComponentsPage_Frame");
    m_mainFrame->setFrameShape(QFrame::VLine);

    m_containerWidget = new ComponentsPageNS::ContainerWidget(this);
    m_mainLayout->addWidget(m_containerWidget, 1);

    m_treeFilterWidget = new ComponentsPageNS::TreeFilterWidget(m_containerWidget, m_userRole, this);

    m_filterPanelFrame = new QFrame(this);
    m_filterPanelFrame->setObjectName("ComponentsPage_Frame");
    m_filterPanelFrame->setFrameShape(QFrame::HLine);

    m_filterWidget = new ComponentsPageNS::FilterWidget(m_containerWidget, m_treeFilterWidget, m_userRole, this);

    m_filterPanelLayout->addWidget(m_filterWidget, 0);
    m_filterPanelLayout->addWidget(m_filterPanelFrame, 0);
    m_filterPanelLayout->addWidget(m_treeFilterWidget, 1);

    m_treeFilterWidget->resetVariants();
}

#include "componentsPage/moc_componentsPage.cpp"
// #include "componentsPage/componentsPage.moc"