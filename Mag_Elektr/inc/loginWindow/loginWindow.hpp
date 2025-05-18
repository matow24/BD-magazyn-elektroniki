#ifndef _LOGINWINDOW_HPP
#define _LOGINWINDOW_HPP

#include <QMainWindow>

#include "main.hpp"

class LoginWindow : public QMainWindow
{
    Q_OBJECT
public:
    LoginWindow(QWidget *parent = nullptr) : QMainWindow(parent) {};
};

#endif // _LOGINWINDOW_HPP