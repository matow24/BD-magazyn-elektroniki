#include "mainWindow/mainWindow.hpp"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent)
{
    setWindowName();
    this->hide();
    this->setStyleSheet(MainStyle::StyleSheets[STYLE_MAINWINDOW_NAME]);

    m_mainToolBar = new MainToolBar(this);
    this->addToolBar(m_mainToolBar);

    m_componentsPage = new ComponentsPage(this);
    m_componentsPage->setSizePolicy(QSizePolicy::MinimumExpanding, QSizePolicy::MinimumExpanding);

    if (g_userRole == UserRole::Admin || g_userRole == UserRole::Logistician)
    {
        m_stackedWidget = new QStackedWidget(this);
        this->setCentralWidget(m_stackedWidget);
        m_stackedWidget->setSizePolicy(QSizePolicy::MinimumExpanding, QSizePolicy::MinimumExpanding);

        m_stackedWidget->addWidget(m_componentsPage);

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
        this->setCentralWidget(m_componentsPage);
    }

    //logout handle
    QObject::connect(m_mainToolBar, &MainToolBar::logoutClicked,
                 this, &MainWindow::onLogoutClicked);
};

MainWindow::~MainWindow(){
    if(m_historyPage!=nullptr) delete m_historyPage;
    if(m_modifyPage!=nullptr) delete m_modifyPage;
    if(m_stackedWidget!=nullptr) delete m_stackedWidget;
    delete g_userRoleName;
}

void MainWindow::onLogoutClicked(){
    if(g_userRole==UserRole::Guest){
        this->hide();
        emit logoutRequested();
        return;
    }

    QMessageBox::StandardButton reply;
    reply = QMessageBox::question(this, tr("Próba wylogowania"), tr("Czy na pewno chcesz się wylogować?"), QMessageBox::Yes | QMessageBox::No, QMessageBox::No);
    if (reply == QMessageBox::Yes) {
        this->hide();
        emit logoutRequested();
    } else
        return;
};

void MainWindow::setWindowName(){
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
}

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
        m_modifyPage->refreshModComponentsPage();
        m_stackedWidget->setCurrentWidget(m_modifyPage);
        break;
    }
    m_mainToolBar->checkPageButton(newPage);
}

#include "mainWindow/moc_mainWindow.cpp"
// #include "mainWindow/mainWindow.moc"