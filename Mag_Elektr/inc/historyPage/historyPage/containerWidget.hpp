#ifndef _HISTORYPAGE_CONTAINERWIDGET_HPP
#define _HISTORYPAGE_CONTAINERWIDGET_HPP

#include <QDateTime>
#include <QHeaderView>
#include <QMap>
#include <QString>
#include <QTableWidget>
#include <QTimer>
#include <QWidget>

#include "main.hpp"

namespace HistoryPageNS
{
    class ContainerWidget : public QTableWidget
    {
        Q_OBJECT
    private:
        void setCenteredItem(int row, int column, int value);
        void setCenteredItem(int row, int column, QString text);

        QMap<QString, int> m_columnIdxMap;

    public:
        void clearAll();

        void addOperation_ChangeComponent(int ID, QDateTime DateTime, QString User_Email, int Component_ID, QChar Type);

        void addOperation_ChangeQuantity(int ID, QDateTime DateTime, QString User_Email, int Component_ID, int Delta);

        void addOperation_ChangeRack(int ID, QDateTime DateTime, QString User_Email, int RackNr, QChar Type);

        void addOperation_ChangeUser(int ID, QDateTime DateTime, QString User_Email, QString Mod_User_Email, QChar Type);

        void addOperation_MoveComponent(int ID, QDateTime DateTime, QString User_Email, int Component_ID, QString Old_Rack, QString Old_Drawer, QString New_Rack, QString New_Drawer);

        ContainerWidget(QWidget *parent = nullptr);
    };
}

#endif // _HISTORYPAGE_CONTAINERWIDGET_HPP