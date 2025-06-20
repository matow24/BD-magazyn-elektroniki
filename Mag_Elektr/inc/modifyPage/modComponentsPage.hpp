#pragma once
#ifndef _MODCOMPONENTSPAGE_HPP
#define _MODCOMPONENTSPAGE_HPP

#include <QWidget>
#include <QTableView>
#include <QPushButton>
#include <QVBoxLayout>
#include <QHBoxLayout>

#include "main.hpp"
#include "modifyPage/addComponentDialog.hpp"
#include "modifyPage/first2ColumnsLockedTableView.hpp"

class ModComponentsPage : public QWidget
{
    Q_OBJECT

public:
    explicit ModComponentsPage(QWidget *parent = nullptr);

private slots:
    void onAddComponentClicked();

private:
    QSqlTableModel *m_model;
    QTableView *m_tableView;
    QPushButton *m_addButton;

    void setupModel();
    void setupLayout();
};

#endif