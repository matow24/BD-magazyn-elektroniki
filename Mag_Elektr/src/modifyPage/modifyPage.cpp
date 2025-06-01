#include "modifyPage/modifyPage.hpp"

ModifyPage::ModifyPage(QWidget *parent) : QWidget(parent)
{
    this->setStyleSheet(MainStyle::StyleSheets[STYLE_MODIFYPAGE_NAME]);
    this->setSizePolicy(QSizePolicy::MinimumExpanding, QSizePolicy::MinimumExpanding);

    m_mainLayout = new QVBoxLayout(this);
    this->setLayout(m_mainLayout);
    m_mainLayout->setContentsMargins(0, 0, 0, 0);
    m_mainLayout->setSpacing(0);

    m_toolbarLayout = new QHBoxLayout(this);
    m_toolbarLayout->setContentsMargins(0, 0, 0, 0);

    m_buttonComponents = new QToolButton(this);
    m_buttonComponents->setStyleSheet(MainStyle::StyleSheets[STYLE_MODIFYPAGE_NAME]);
    m_buttonComponents->setText(tr("Edytuj komponenty"));
    //m_buttonComponents->setWidth(this->width()/3);

    m_toolbarLayout->addWidget(m_buttonComponents);

    if (g_userRole == UserRole::Admin)
    {
        m_buttonUsers = new QToolButton(this);
        m_buttonUsers->setStyleSheet(MainStyle::StyleSheets[STYLE_MODIFYPAGE_NAME]);
        m_buttonUsers->setText(tr("Edytuj użytkowników"));
        //m_buttonUsers->setWidth(this->width()/3);

        m_buttonLocations = new QToolButton(this);
        m_buttonLocations->setStyleSheet(MainStyle::StyleSheets[STYLE_MODIFYPAGE_NAME]);
        m_buttonLocations->setText(tr("Edytuj regały i szuflady"));
        //m_buttonLocations->setWidth(this->width()/3);

        m_toolbarLayout->addWidget(m_buttonUsers);
        m_toolbarLayout->addWidget(m_buttonLocations);
    }

    /*
    m_stackedWidget = new QStackedWidget(this);

    QWidget *m_modComponentsPage = new QLabel("This is Page 1");
    QWidget *m_usersPage = new QLabel("This is Page 2");
    QWidget *m_locationPage = new QLabel("This is Page 3");

    m_stackedWidget->addWidget(m_modComponentsPage);
    m_stackedWidget->addWidget(m_usersPage);
    m_stackedWidget->addWidget(m_locationPage);

    connect(m_buttonComponents, &QToolButton::clicked, [m_stackedWidget]() {
        m_stackedWidget->setCurrentIndex(0);
    });
    connect(m_buttonUsers, &QToolButton::clicked, [m_stackedWidget]() {
        m_stackedWidget->setCurrentIndex(1);
    });
    connect(m_buttonLocations, &QToolButton::clicked, [m_stackedWidget]() {
        m_stackedWidget->setCurrentIndex(2);
    });
    */

    m_mainLayout->addLayout(m_toolbarLayout);
    //mainLayout->addWidget(stackedWidget);

    QLabel *label = new QLabel(this);
    m_mainLayout->addWidget(label, 0, Qt::AlignCenter);
    label->setText("TODO Modyfikuj");
    label->setStyleSheet("font-size: 24px; font-weight: bold;");

}

ModifyPage::~ModifyPage()
{
    //delete ...
}
#include "modifyPage/moc_modifyPage.cpp"
// #include "modifyPage/modifyPage.moc"