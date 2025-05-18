#include "componentsPage/componentsPage.hpp"

ComponentsPage::ComponentsPage(UserRole userRole, QWidget *parent) : QWidget(parent)
{
    m_userRole = userRole;

    this->setStyleSheet(MainStyle::StyleSheets[STYLE_COMPONENTSPAGE_NAME]);
    this->setSizePolicy(QSizePolicy::MinimumExpanding, QSizePolicy::MinimumExpanding);

    m_mainLayout = new QHBoxLayout(this); //!< @note temporary
    this->setLayout(m_mainLayout);
    m_mainLayout->setContentsMargins(0, 0, 0, 0);
    m_mainLayout->setSpacing(0);

    m_filterTypeSpace = new FilterTypeSpace(m_userRole, this);
    m_mainLayout->addWidget(m_filterTypeSpace, 0, Qt::AlignLeft);
    m_filterTypeSpace->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::MinimumExpanding);

    QFrame *firstSpacer = new QFrame(this);
    m_mainLayout->addWidget(firstSpacer, 0, Qt::AlignLeft);
    firstSpacer->setFrameShape(QFrame::VLine);
    firstSpacer->setObjectName("Spacer");
    firstSpacer->setStyleSheet(this->styleSheet());

    m_displayComponentsSpace = new DisplayComponentsSpace(m_userRole, this);
    m_mainLayout->addWidget(m_displayComponentsSpace, 1, Qt::AlignRight);
    m_displayComponentsSpace->setSizePolicy(QSizePolicy::MinimumExpanding, QSizePolicy::MinimumExpanding);
}

#include "componentsPage/moc_componentsPage.cpp"
// #include "componentsPage/componentsPage.moc"