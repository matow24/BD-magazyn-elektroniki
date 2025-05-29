#ifndef _LOGINWINDOW_HPP
#define _LOGINWINDOW_HPP

#include <QMainWindow>
#include <QVBoxLayout>
#include <QLineEdit>
#include <QPushButton>
#include <QLabel>
#include <QSpacerItem>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <QMessageBox>

#include "mainWindow/mainWindow.hpp"

#include "main.hpp"

class LoginWindow : public QMainWindow
{
    Q_OBJECT
public:
    LoginWindow(QWidget *parent = nullptr);
signals:
    void loginSuccessful();
public slots:
    void onLogout();

private:
    QWidget *window;
    QLineEdit *emailEdit;
    QLineEdit *passwordEdit;
    QPushButton *submitButton;
    QPushButton *forgotPasswordButton;
    QPushButton *proceedWithoutLoginButton;

    void setUserRole(char dbRole);

private slots:
    void onSubmit();
    void onProceedWithoutLogin();
    void onForgotPassword();
};

#endif // _LOGINWINDOW_HPP