#ifndef _MAINTOOLBUTTON_HPP
#define _MAINTOOLBUTTON_HPP

#include <QToolButton>

#include "main.hpp"

class MainToolButton : public QToolButton
{
    Q_OBJECT
public:
    MainToolButton(QWidget *parent = nullptr);
};

#endif // _MAINTOOLBUTTON_HPP