#ifndef _MODUSERPAGE_HPP
#define _MODUSERPAGE_HPP

#include <QWidget>
#include <QTableView>
#include <QSqlTableModel>
#include <QPushButton>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QSqlDatabase>
#include <QSqlError>
#include <QDebug>

#include "main.hpp"
#include "modifyPage/addUserDialog.hpp"

class ModUserPage : public QWidget
{
    Q_OBJECT

public:
    ModUserPage(QWidget *parent = nullptr);

private slots:
    void addUser();

private:
    QSqlTableModel *m_model;
};

#endif