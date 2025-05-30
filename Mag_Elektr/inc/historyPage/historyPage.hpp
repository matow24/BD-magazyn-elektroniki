#ifndef _HISTORYPAGE_HPP
#define _HISTORYPAGE_HPP

#include <QHBoxLayout>
#include <QLabel>
#include <QWidget>
#include <QVBoxLayout>

#include "main.hpp"

#include "historyPage/historyPage/containerWidget.hpp"
#include "historyPage/historyPage/filterWidget.hpp"

class HistoryPage : public QWidget
{
    Q_OBJECT
private:
    QHBoxLayout *m_mainLayout = nullptr;
    QFrame *m_mainFrame = nullptr;

    HistoryPageNS::ContainerWidget *m_containerWidget = nullptr;
    HistoryPageNS::FilterWidget *m_filterWidget = nullptr;

public:
    HistoryPage(QWidget *parent = nullptr);
    //~HistoryPage();
};

#endif // _HISTORYPAGE_HPP