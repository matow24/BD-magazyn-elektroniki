#ifndef _DISPLAYCOMPONENTSSPACE_HPP
#define _DISPLAYCOMPONENTSSPACE_HPP

#include <QGridLayout>
#include <QLayout>
#include <QWidget>
#include <QVBoxLayout>

#include "main.hpp"

class DisplayComponentsSpace : public QWidget
{
    Q_OBJECT
private:
    UserRole m_userRole;

public:
    DisplayComponentsSpace(UserRole userRole, QWidget *parent = nullptr);
};

#endif // _DISPLAYCOMPONENTSSPACE_HPP