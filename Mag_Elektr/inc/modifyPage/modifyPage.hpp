#ifndef _MODIFYPAGE_HPP
#define _MODIFYPAGE_HPP

#include <QHBoxLayout>
#include <QLabel>
#include <QWidget>
#include <QVBoxLayout>

#include "main.hpp"

class ModifyPage : public QWidget
{
    Q_OBJECT
private:
    QVBoxLayout *m_mainLayout = nullptr;

public:
    ModifyPage(QWidget *parent = nullptr);
};

#endif // _MODIFYPAGE_HPP