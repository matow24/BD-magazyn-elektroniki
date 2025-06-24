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
    void refresh();

private slots:
    void onAddComponentClicked();
    void onMoveComponentClicked();

private:
    QSqlTableModel *m_model;
    QTableView *m_tableView;
    QPushButton *m_addButton;
    QPushButton *m_moveButton;

    void setupModel();
    void setupLayout();
    bool addOperation(int, DB::Attrb::OperationType);
};

#endif