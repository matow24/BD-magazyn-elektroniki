#include "mainWindow/mainWindow.hpp"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent)
{
    switch (g_userRole)
    {
    case UserRole::Guest:
        g_userRoleName = new QString(tr("Gość"));
        break;
    case UserRole::Employee:
        g_userRoleName = new QString(tr("Pracownik"));
        break;
    case UserRole::Logistician:
        g_userRoleName = new QString(tr("Logistyk"));
        break;
    case UserRole::Admin:
        g_userRoleName = new QString(tr("Administrator"));
        break;
    }

    this->setWindowTitle(tr("Magazyn Elektroniki") + " - " + *g_userRoleName);
    this->setMinimumSize(1280, 720);
    this->setStyleSheet(MainStyle::StyleSheets[STYLE_MAINWINDOW_NAME]);

    if (g_userRole != UserRole::Guest)
    {
        m_mainToolBar = new MainToolBar(this);
        this->addToolBar(m_mainToolBar);
    }

    if (g_userRole != UserRole::Guest && g_userRole != UserRole::Employee)
    {
        m_stackedWidget = new QStackedWidget(this);
        this->setCentralWidget(m_stackedWidget);
        m_stackedWidget->setSizePolicy(QSizePolicy::MinimumExpanding, QSizePolicy::MinimumExpanding);

        m_componentsPage = new ComponentsPage(this);
        m_stackedWidget->addWidget(m_componentsPage);
        m_componentsPage->setSizePolicy(QSizePolicy::MinimumExpanding, QSizePolicy::MinimumExpanding);

        m_historyPage = new HistoryPage(this);
        m_stackedWidget->addWidget(m_historyPage);
        m_historyPage->setSizePolicy(QSizePolicy::MinimumExpanding, QSizePolicy::MinimumExpanding);

        m_modifyPage = new ModifyPage(this);
        m_stackedWidget->addWidget(m_modifyPage);
        m_modifyPage->setSizePolicy(QSizePolicy::MinimumExpanding, QSizePolicy::MinimumExpanding);

        connect(m_mainToolBar, &MainToolBar::pageChanged, this, &MainWindow::changePage);

        m_stackedWidget->setCurrentWidget(m_componentsPage);
        m_mainToolBar->checkPageButton(Page::Components);
    }
    else
    {
        m_componentsPage = new ComponentsPage(this);
        this->setCentralWidget(m_componentsPage);
        m_componentsPage->setSizePolicy(QSizePolicy::MinimumExpanding, QSizePolicy::MinimumExpanding);
    }
};

void MainWindow::changePage(Page &newPage)
{
    if (m_stackedWidget == nullptr)
        return;

    if (g_userRole == UserRole::Guest || g_userRole == UserRole::Employee)
        return;

    switch (newPage)
    {
    case Page::Components:
        m_stackedWidget->setCurrentWidget(m_componentsPage);
        break;
    case Page::History:
        m_stackedWidget->setCurrentWidget(m_historyPage);
        break;
    case Page::Modify:
        m_stackedWidget->setCurrentWidget(m_modifyPage);
        break;
    }
    m_mainToolBar->checkPageButton(newPage);
}

#include "mainWindow/moc_mainWindow.cpp"
// #include "mainWindow/mainWindow.moc"