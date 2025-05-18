#ifndef _COMPONENTSPAGE_HPP
#define _COMPONENTSPAGE_HPP

#include <QFrame>
#include <QHBoxLayout>
#include <QWidget>
#include <QVBoxLayout>

#include "main.hpp"

#include "componentsPage/displayComponentsSpace.hpp"
#include "componentsPage/filterTypeSpace.hpp"

class ComponentsPage : public QWidget
{
    Q_OBJECT
private:
    UserRole m_userRole;

    QHBoxLayout *m_mainLayout = nullptr;

    FilterTypeSpace *m_filterTypeSpace = nullptr;
    QFrame *m_firstSpacer = nullptr;
    DisplayComponentsSpace *m_displayComponentsSpace = nullptr;

public:
    ComponentsPage(UserRole userRole, QWidget *parent = nullptr);
};

#endif // _COMPONENTSPAGE_HPP