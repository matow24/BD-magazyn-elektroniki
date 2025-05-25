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

#include "main.hpp"

class LoginWindow : public QMainWindow
{
    Q_OBJECT
public:
    LoginWindow(QWidget *parent = nullptr);
private:
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