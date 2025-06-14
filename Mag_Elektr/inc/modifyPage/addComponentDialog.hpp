#ifndef _ADDCOMPONENTDIALOG_HPP
#define _ADDCOMPONENTDIALOG_HPP

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

class AddComponentDialog : public QDialog
{
    Q_OBJECT

public:
    explicit AddComponentDialog(QWidget *parent = nullptr);

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

    bool isNameUnique(const QString &name);
    bool isSymbolUnique(const QString &symbol);
};

#endif