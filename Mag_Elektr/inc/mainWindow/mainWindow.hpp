#ifndef _MAINWINDOW_HPP
#define _MAINWINDOW_HPP

#include <QMainWindow>

#include "main.hpp"

class MainWindow : public QMainWindow
{
    Q_OBJECT
public:
    MainWindow(UserRole userRole, QWidget *parent = nullptr) : QMainWindow(parent) {};
};

#endif // _MAINWINDOW_HPP