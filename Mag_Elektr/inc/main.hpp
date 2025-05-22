#ifndef _MAIN_HPP
#define _MAIN_HPP

#include <QDebug>
#include <QString>

#include "mainDatabase/mainDatabase.hpp"
#include "common/mainStyle.hpp"

enum UserRole
{
    Guest,
    Employee,
    Logistician,
    Admin
};

extern QString g_userEmail;
extern UserRole g_userRole;

#endif // _MAIN_HPP