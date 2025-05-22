#ifndef _MAINTOOLBAR_HPP
#define _MAINTOOLBAR_HPP

#include <QAction>
#include <QActionGroup>
#include <QButtonGroup>
#include <QObject>
#include <QToolBar>
#include <QToolButton>

#include "main.hpp"
#include "mainWindow/mainToolButton.hpp"

enum Page
{
    Components,
    History,
    Modify
};

class MainToolBar : public QToolBar
{
    Q_OBJECT
private:
    QButtonGroup *m_buttonsPages = nullptr;
    MainToolButton *m_buttonComponents = nullptr;
    MainToolButton *m_buttonHistory = nullptr;
    MainToolButton *m_buttonModify = nullptr;

    MainToolButton *m_buttonLogout = nullptr;

public:
    void checkPageButton(Page page);

    MainToolBar(QWidget *parent = nullptr);

private slots:
    void pageButtonClicked(QAbstractButton *button);
    void logoutButtonClicked();

signals:
    void pageChanged(Page &newPage);
    void logoutClicked();
};

#endif // _MAINTOOLBAR_HPP