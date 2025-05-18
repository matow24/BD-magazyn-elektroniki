#ifndef _FILTERTYPESPACE_HPP
#define _FILTERTYPESPACE_HPP

#include <QWidget>
#include <QVBoxLayout>

#include "main.hpp"

class FilterTypeSpace : public QWidget
{
    Q_OBJECT
private:
    UserRole m_userRole;

    QVBoxLayout *m_mainLayout = nullptr;

public:
    FilterTypeSpace(UserRole userRole, QWidget *parent = nullptr);
};

#endif // _FILTERTYPESPACE_HPP