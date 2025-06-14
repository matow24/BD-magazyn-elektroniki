#pragma once
#ifndef _MODLOCATIONSPAGE_HPP
#define _MODLOCATIONSPAGE_HPP

#include <QWidget>
#include <QSqlTableModel>
#include <QTableView>
#include <QPushButton>
#include <QVBoxLayout>
#include <QHBoxLayout>

#include "main.hpp"

class ModLocationsPage : public QWidget
{
    Q_OBJECT

public:
    explicit ModLocationsPage(QWidget *parent = nullptr);

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