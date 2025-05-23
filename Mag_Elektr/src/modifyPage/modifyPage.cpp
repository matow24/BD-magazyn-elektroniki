#include "modifyPage/modifyPage.hpp"

ModifyPage::ModifyPage(QWidget *parent) : QWidget(parent)
{
    this->setStyleSheet(MainStyle::StyleSheets[STYLE_MODIFYPAGE_NAME]);
    this->setSizePolicy(QSizePolicy::MinimumExpanding, QSizePolicy::MinimumExpanding);

    m_mainLayout = new QVBoxLayout(this); //!< @note temporary
    this->setLayout(m_mainLayout);
    m_mainLayout->setContentsMargins(0, 0, 0, 0);
    m_mainLayout->setSpacing(0);

    QLabel *label = new QLabel(this);
    m_mainLayout->addWidget(label, 0, Qt::AlignCenter);
    label->setText("TODO Modyfikuj");
    label->setStyleSheet("font-size: 24px; font-weight: bold;");

}

#include "modifyPage/moc_modifyPage.cpp"
// #include "modifyPage/modifyPage.moc"