#ifndef _ADDUSERDIALOG_HPP
#define _ADDUSERDIALOG_HPP

#include <QDialog>
#include <QVBoxLayout>
#include <QFormLayout>
#include <QLineEdit>
#include <QComboBox>
#include <QPushButton>
#include <QMessageBox>
#include <QSqlQuery>
#include <QSqlError>
#include <QDebug>

#include "main.hpp"

class AddUserDialog : public QDialog
{
    Q_OBJECT

public:
    explicit AddUserDialog(QWidget *parent = nullptr);

private slots:
    void validateForm();
    void onAddClicked();
    bool setPosition(char& );

private:
    QLineEdit *firstNameEdit;
    QLineEdit *lastNameEdit;
    QLineEdit *emailEdit;
    QComboBox *positionBox;
    QLineEdit *passwordEdit;
    QPushButton *addButton;
    char pos;
};

#endif