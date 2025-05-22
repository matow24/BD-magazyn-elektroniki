#include "historyPage/historyPage.hpp"

HistoryPage::HistoryPage(QWidget *parent) : QWidget(parent)
{
    this->setStyleSheet(MainStyle::StyleSheets[STYLE_HISTORYPAGE_NAME]);
    this->setSizePolicy(QSizePolicy::MinimumExpanding, QSizePolicy::MinimumExpanding);

    m_mainLayout = new QVBoxLayout(this); //!< @note temporary
    this->setLayout(m_mainLayout);
    m_mainLayout->setContentsMargins(0, 0, 0, 0);
    m_mainLayout->setSpacing(0);

    QLabel *label = new QLabel(this);
    m_mainLayout->addWidget(label, 0, Qt::AlignCenter);
    label->setText("TODO Historia");
    label->setStyleSheet("font-size: 24px; font-weight: bold;");

}

#include "historyPage/moc_historyPage.cpp"
// #include "historyPage/historyPage.moc"