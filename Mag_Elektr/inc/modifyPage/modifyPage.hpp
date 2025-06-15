#ifndef _MODIFYPAGE_HPP
#define _MODIFYPAGE_HPP

#include <QToolButton>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QWidget>
#include <QStackedWidget>

#include "main.hpp"

#include "modifyPage/modUserPage.hpp"
#include "modifyPage/modComponentsPage.hpp"
#include "modifyPage/modLocationsPage.hpp"

enum ModPage
{
    ModComponents,
    Users,
    Locations
};

class ModifyPage : public QWidget
{
    Q_OBJECT
private:
    QVBoxLayout *m_mainLayout = nullptr;

    QHBoxLayout *m_toolbarLayout = nullptr;
    QToolButton *m_buttonComponents = nullptr;
    QToolButton *m_buttonUsers = nullptr;
    QToolButton *m_buttonLocations = nullptr;

    ModUserPage       *m_userPage = nullptr;
    ModComponentsPage *m_modComponentsPage = nullptr;
    ModLocationsPage  *m_locationPage = nullptr;
    QStackedWidget *m_stackedWidget = nullptr;

public:
    ModifyPage(QWidget *parent = nullptr);
};

#endif // _MODIFYPAGE_HPP