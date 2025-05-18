#ifndef _COMPONENTSPAGE_HPP
#define _COMPONENTSPAGE_HPP

#include <QHBoxLayout>
#include <QLabel>
#include <QWidget>
#include <QVBoxLayout>

#include "main.hpp"

class ComponentsPage : public QWidget
{
    Q_OBJECT
private:
    UserRole m_userRole;

    QVBoxLayout *m_mainLayout = nullptr;

public:
    ComponentsPage(UserRole userRole, QWidget *parent = nullptr);
};

#endif // _COMPONENTSPAGE_HPP