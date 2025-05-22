#ifndef _HISTORYPAGE_HPP
#define _HISTORYPAGE_HPP

#include <QHBoxLayout>
#include <QLabel>
#include <QWidget>
#include <QVBoxLayout>

#include "main.hpp"

class HistoryPage : public QWidget
{
    Q_OBJECT
private:

    QVBoxLayout *m_mainLayout = nullptr;

public:
    HistoryPage(QWidget *parent = nullptr);
};

#endif // _HISTORYPAGE_HPP