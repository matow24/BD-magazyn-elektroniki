#ifndef _MAINWINDOW_HPP
#define _MAINWINDOW_HPP

#include <QMainWindow>

class MainWindow : public QMainWindow
{
    Q_OBJECT
public:
    MainWindow(QWidget *parent = nullptr) : QMainWindow(parent) {};
};

#endif // _MAINWINDOW_HPP