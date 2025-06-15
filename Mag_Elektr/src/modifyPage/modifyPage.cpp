#include "modifyPage/modifyPage.hpp"

ModifyPage::ModifyPage(QWidget *parent) : QWidget(parent)
{
    this->setStyleSheet(MainStyle::StyleSheets[STYLE_MODIFYPAGE_NAME]);
    this->setSizePolicy(QSizePolicy::MinimumExpanding, QSizePolicy::MinimumExpanding);

    m_mainLayout = new QVBoxLayout(this);
    this->setLayout(m_mainLayout);
    m_mainLayout->setContentsMargins(0, 0, 0, 0);
    m_mainLayout->setSpacing(0);

    m_stackedWidget = new QStackedWidget(this);
    
    m_modComponentsPage = new ModComponentsPage(this);
    m_modComponentsPage->setSizePolicy(QSizePolicy::MinimumExpanding, QSizePolicy::MinimumExpanding);
    m_stackedWidget->addWidget(m_modComponentsPage);

    if (g_userRole == UserRole::Admin)
    {
        m_toolbarLayout = new QHBoxLayout(this);
        m_toolbarLayout->setContentsMargins(0, 0, 0, 0);

        m_buttonComponents = new QToolButton(this);
        m_buttonComponents->setStyleSheet(MainStyle::StyleSheets[STYLE_MODIFYPAGE_NAME]);
        m_buttonComponents->setText(tr("Edytuj komponenty"));

        m_buttonUsers = new QToolButton(this);
        m_buttonUsers->setStyleSheet(MainStyle::StyleSheets[STYLE_MODIFYPAGE_NAME]);
        m_buttonUsers->setText(tr("Edytuj użytkowników"));

        m_buttonLocations = new QToolButton(this);
        m_buttonLocations->setStyleSheet(MainStyle::StyleSheets[STYLE_MODIFYPAGE_NAME]);
        m_buttonLocations->setText(tr("Edytuj regały i szuflady"));

        m_userPage = new ModUserPage(this);
        m_stackedWidget->addWidget(m_userPage);
        m_userPage->setSizePolicy(QSizePolicy::MinimumExpanding, QSizePolicy::MinimumExpanding);

        m_locationPage = new ModLocationsPage(this);
        m_stackedWidget->addWidget(m_locationPage);
        m_locationPage->setSizePolicy(QSizePolicy::MinimumExpanding, QSizePolicy::MinimumExpanding);

        m_toolbarLayout->addWidget(m_buttonComponents);
        m_toolbarLayout->addWidget(m_buttonUsers);
        m_toolbarLayout->addWidget(m_buttonLocations);

        connect(m_buttonComponents, &QToolButton::clicked, [this]() {
            m_stackedWidget->setCurrentIndex(ModComponents);
        });
        connect(m_buttonUsers, &QToolButton::clicked, [this]() {
            m_stackedWidget->setCurrentIndex(Users);
        });
        connect(m_buttonLocations, &QToolButton::clicked, [this]() {
            m_stackedWidget->setCurrentIndex(Locations);
        });

        m_mainLayout->addLayout(m_toolbarLayout);
    }

    m_mainLayout->addWidget(m_stackedWidget);
}

#include "modifyPage/moc_modifyPage.cpp"
// #include "modifyPage/modifyPage.moc"