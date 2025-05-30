#include "mainWindow/mainToolBar.hpp"

void MainToolBar::checkPageButton(Page page)
{
    if (g_userRole == UserRole::Guest || g_userRole == UserRole::Employee)
        return;

    for (auto &button : m_buttonsPages->buttons())
        button->setChecked(false);

    switch (page)
    {
    case Page::Components:
        m_buttonComponents->setChecked(true);
        break;
    case Page::History:
        m_buttonHistory->setChecked(true);
        break;
    case Page::Modify:
        m_buttonModify->setChecked(true);
        break;
    }
}

MainToolBar::~MainToolBar(){
    delete m_buttonComponents;
    delete m_buttonHistory;
    delete m_buttonLogout;
    delete m_buttonModify;
    delete m_buttonsPages;
}

MainToolBar::MainToolBar(QWidget *parent) : QToolBar(parent)
{
    this->setStyleSheet(MainStyle::StyleSheets[STYLE_MAINWINDOW_NAME]);
    this->setMovable(false);
    this->setFloatable(false);
    this->setSizePolicy(QSizePolicy::MinimumExpanding, QSizePolicy::Minimum);
    this->setOrientation(Qt::Horizontal);

    if (g_userRole != UserRole::Guest && g_userRole != UserRole::Employee)
    {
        m_buttonsPages = new QButtonGroup(this);
        m_buttonsPages->setExclusive(true);

        m_buttonComponents = new MainToolButton(this);
        m_buttonsPages->addButton(m_buttonComponents, Page::Components);
        this->addWidget(m_buttonComponents);
        m_buttonComponents->setText(tr("Komponenty"));

        m_buttonHistory = new MainToolButton(this);
        m_buttonsPages->addButton(m_buttonHistory, Page::History);
        this->addWidget(m_buttonHistory);
        m_buttonHistory->setText(tr("Historia"));

        m_buttonModify = new MainToolButton(this);
        m_buttonsPages->addButton(m_buttonModify, Page::Modify);
        this->addWidget(m_buttonModify);
        m_buttonModify->setText(tr("Modyfikacja"));

        connect(m_buttonsPages, &QButtonGroup::buttonClicked, this, &MainToolBar::pageButtonClicked);
    }

    m_buttonLogout = new MainToolButton(this);
    this->addWidget(m_buttonLogout);
    m_buttonLogout->setText(tr("Wyloguj"));
    m_buttonLogout->setCheckable(false);
    m_buttonLogout->setChecked(false);

    connect(m_buttonLogout, &QToolButton::clicked, this, &MainToolBar::logoutButtonClicked);
}

void MainToolBar::pageButtonClicked(QAbstractButton *button)
{
    if (g_userRole == UserRole::Guest || g_userRole == UserRole::Employee)
        return;

    Page page = static_cast<Page>(m_buttonsPages->id(button));
    emit pageChanged(page);
}

void MainToolBar::logoutButtonClicked()
{
    emit logoutClicked();
}

#include "mainWindow/moc_mainToolBar.cpp"
// #include "mainWindow/mainToolBar.moc"