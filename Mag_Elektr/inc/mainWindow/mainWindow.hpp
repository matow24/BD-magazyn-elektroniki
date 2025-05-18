#ifndef _MAINWINDOW_HPP
#define _MAINWINDOW_HPP

#include <QApplication>
#include <QMainWindow>
#include <QSize>
#include <QSizePolicy>
#include <QStackedWidget>
#include <QString>

#include "main.hpp"

#include "mainWindow/mainToolBar.hpp"

#include "componentsPage/componentsPage.hpp"
#include "historyPage/historyPage.hpp"
#include "modifyPage/modifyPage.hpp"

class MainWindow : public QMainWindow
{
    Q_OBJECT
private:
    UserRole m_userRole;
    QString *m_userRoleName = nullptr;

    MainToolBar *m_mainToolBar = nullptr;

    ComponentsPage *m_componentsPage = nullptr;
    HistoryPage *m_historyPage = nullptr;
    ModifyPage *m_modifyPage = nullptr;

    QStackedWidget *m_stackedWidget = nullptr;

public:
    MainWindow(UserRole userRole, QWidget *parent = nullptr);

private slots:
    void changePage(Page &newPage);
};

#endif // _MAINWINDOW_HPP