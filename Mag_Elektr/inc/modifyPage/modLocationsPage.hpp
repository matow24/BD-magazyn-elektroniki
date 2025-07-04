#pragma once
#ifndef _MODLOCATIONSPAGE_HPP
#define _MODLOCATIONSPAGE_HPP

#include <QWidget>
#include <QSqlTableModel>
#include <QTableView>
#include <QPushButton>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QInputDialog>

#include "main.hpp"
//#include "modifyPage/LocationWithComponent.hpp"

class ModLocationsPage : public QWidget
{
    Q_OBJECT

public:
    explicit ModLocationsPage(QWidget *parent = nullptr);
    void refresh();

private slots:
    void onAddRegalClicked();
    void onRemoveRegalClicked();

private:
    QSqlTableModel *m_model;
    QTableView *m_tableView;
    QPushButton *m_addButton;
    QPushButton *m_removeButton;
    uint liczba_szuflad_w_regale;

    void setupModel();
    void setupLayout();
    bool addOperation(int, DB::Attrb::OperationType);
};

#endif