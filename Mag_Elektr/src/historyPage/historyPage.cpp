#include "historyPage/historyPage.hpp"

HistoryPage::HistoryPage(QWidget *parent) : QWidget(parent)
{
    this->setStyleSheet(MainStyle::StyleSheets[STYLE_HISTORYPAGE_NAME]);
    this->setSizePolicy(QSizePolicy::MinimumExpanding, QSizePolicy::MinimumExpanding);
    this->setContentsMargins(0, 0, 0, 0);

    m_mainLayout = new QHBoxLayout(this); //!< @note temporary
    this->setLayout(m_mainLayout);
    m_mainLayout->setContentsMargins(0, 0, 0, 0);
    m_mainLayout->setSpacing(0);

    m_containerWidget = new HistoryPageNS::ContainerWidget(this);

    m_mainFrame = new QFrame(this);
    m_mainFrame->setObjectName("HistoryPage_Frame");
    m_mainFrame->setFrameShape(QFrame::VLine);

    m_filterWidget = new HistoryPageNS::FilterWidget(m_containerWidget, this);

    m_mainLayout->addWidget(m_filterWidget, 0);
    m_mainLayout->addWidget(m_mainFrame, 0);
    m_mainLayout->addWidget(m_containerWidget, 1);
}
/*
HistoryPage::~HistoryPage(){
    delete m_containerWidget;
    delete m_filterWidget;
    delete m_mainFrame;
    delete m_mainLayout;
}*/

#include "historyPage/moc_historyPage.cpp"
// #include "historyPage/historyPage.moc"