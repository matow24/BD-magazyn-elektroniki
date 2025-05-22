#include "historyPage/historyPage/containerWidget.hpp"

#define COLUMN_ID "ID"
#define COLUMN_DATE "Date"
#define COLUMN_USER_EMAIL "User Email"

#define COLUMN_TYPE "Type"
#define COLUMN_COMPONENT_ID "Component ID"

#define COLUMN_DELTA "Delta"
#define COLUMN_MODIFIED_USER_EMAIL "Modified\nUser Email"
#define COLUMN_RACKNR "Rack Number"
#define COLUMN_OLD_LOCATION_RACK "Old\nLocation Rack"
#define COLUMN_OLD_LOCATION_DRAWER "Old\nLocation Drawer"
#define COLUMN_NEW_LOCATION_RACK "New\nLocation Rack"
#define COLUMN_NEW_LOCATION_DRAWER "New\nLocation Drawer"

void HistoryPageNS::ContainerWidget::setCenteredItem(int row, int column, int value)
{
    QTableWidgetItem *item = new QTableWidgetItem();
    item->setData(Qt::EditRole, value);
    item->setTextAlignment(Qt::AlignCenter);
    this->setItem(row, column, item);
}

void HistoryPageNS::ContainerWidget::setCenteredItem(int row, int column, QString text)
{
    QTableWidgetItem *item = new QTableWidgetItem(text);
    item->setTextAlignment(Qt::AlignCenter);
    this->setItem(row, column, item);
}

void HistoryPageNS::ContainerWidget::clearAll()
{
    this->setRowCount(0);
    this->setColumnHidden(m_columnIdxMap.value(COLUMN_ID), false);
    this->setColumnHidden(m_columnIdxMap.value(COLUMN_DATE), false);
    this->setColumnHidden(m_columnIdxMap.value(COLUMN_USER_EMAIL), false);
    this->setColumnHidden(m_columnIdxMap.value(COLUMN_TYPE), true);
    this->setColumnHidden(m_columnIdxMap.value(COLUMN_COMPONENT_ID), true);
    this->setColumnHidden(m_columnIdxMap.value(COLUMN_DELTA), true);
    this->setColumnHidden(m_columnIdxMap.value(COLUMN_MODIFIED_USER_EMAIL), true);
    this->setColumnHidden(m_columnIdxMap.value(COLUMN_RACKNR), true);
    this->setColumnHidden(m_columnIdxMap.value(COLUMN_OLD_LOCATION_RACK), true);
    this->setColumnHidden(m_columnIdxMap.value(COLUMN_OLD_LOCATION_DRAWER), true);
    this->setColumnHidden(m_columnIdxMap.value(COLUMN_NEW_LOCATION_RACK), true);
    this->setColumnHidden(m_columnIdxMap.value(COLUMN_NEW_LOCATION_DRAWER), true);
}

void HistoryPageNS::ContainerWidget::addOperation_ChangeComponent(int ID, QDateTime DateTime, QString User_Email, int Component_ID, QChar Type)
{
    int row = this->rowCount();
    this->insertRow(row);

    this->setCenteredItem(row, m_columnIdxMap.value(COLUMN_ID), ID);
    this->setCenteredItem(row, m_columnIdxMap.value(COLUMN_DATE), DateTime.toString("yyyy-MM-dd hh:mm:ss"));
    this->setCenteredItem(row, m_columnIdxMap.value(COLUMN_USER_EMAIL), User_Email);
    this->setCenteredItem(row, m_columnIdxMap.value(COLUMN_TYPE), Type);
    this->setCenteredItem(row, m_columnIdxMap.value(COLUMN_COMPONENT_ID), Component_ID);

    this->setColumnHidden(m_columnIdxMap.value(COLUMN_ID), false);
    this->setColumnHidden(m_columnIdxMap.value(COLUMN_DATE), false);
    this->setColumnHidden(m_columnIdxMap.value(COLUMN_USER_EMAIL), false);
    this->setColumnHidden(m_columnIdxMap.value(COLUMN_TYPE), false);
    this->setColumnHidden(m_columnIdxMap.value(COLUMN_COMPONENT_ID), false);
}

void HistoryPageNS::ContainerWidget::addOperation_ChangeQuantity(int ID, QDateTime DateTime, QString User_Email, int Component_ID, int Delta)
{
    int row = this->rowCount();
    this->insertRow(row);

    this->setCenteredItem(row, m_columnIdxMap.value(COLUMN_ID), ID);
    this->setCenteredItem(row, m_columnIdxMap.value(COLUMN_DATE), (DateTime.toString("yyyy-MM-dd hh:mm:ss")));
    this->setCenteredItem(row, m_columnIdxMap.value(COLUMN_USER_EMAIL), User_Email);
    this->setCenteredItem(row, m_columnIdxMap.value(COLUMN_COMPONENT_ID), Component_ID);
    this->setCenteredItem(row, m_columnIdxMap.value(COLUMN_DELTA), Delta);

    this->setColumnHidden(m_columnIdxMap.value(COLUMN_ID), false);
    this->setColumnHidden(m_columnIdxMap.value(COLUMN_DATE), false);
    this->setColumnHidden(m_columnIdxMap.value(COLUMN_USER_EMAIL), false);
    this->setColumnHidden(m_columnIdxMap.value(COLUMN_COMPONENT_ID), false);
    this->setColumnHidden(m_columnIdxMap.value(COLUMN_DELTA), false);
}

void HistoryPageNS::ContainerWidget::addOperation_ChangeRack(int ID, QDateTime DateTime, QString User_Email, int RackNr, QChar Type)
{
    int row = this->rowCount();
    this->insertRow(row);

    this->setCenteredItem(row, m_columnIdxMap.value(COLUMN_ID), ID);
    this->setCenteredItem(row, m_columnIdxMap.value(COLUMN_DATE), DateTime.toString("yyyy-MM-dd hh:mm:ss"));
    this->setCenteredItem(row, m_columnIdxMap.value(COLUMN_USER_EMAIL), User_Email);
    this->setCenteredItem(row, m_columnIdxMap.value(COLUMN_TYPE), Type);
    this->setCenteredItem(row, m_columnIdxMap.value(COLUMN_RACKNR), RackNr);

    this->setColumnHidden(m_columnIdxMap.value(COLUMN_ID), false);
    this->setColumnHidden(m_columnIdxMap.value(COLUMN_DATE), false);
    this->setColumnHidden(m_columnIdxMap.value(COLUMN_USER_EMAIL), false);
    this->setColumnHidden(m_columnIdxMap.value(COLUMN_TYPE), false);
    this->setColumnHidden(m_columnIdxMap.value(COLUMN_RACKNR), false);
}

void HistoryPageNS::ContainerWidget::addOperation_ChangeUser(int ID, QDateTime DateTime, QString User_Email, QString Mod_User_Email, QChar Type)
{
    int row = this->rowCount();
    this->insertRow(row);

    this->setCenteredItem(row, m_columnIdxMap.value(COLUMN_ID), ID);
    this->setCenteredItem(row, m_columnIdxMap.value(COLUMN_DATE), DateTime.toString("yyyy-MM-dd hh:mm:ss"));
    this->setCenteredItem(row, m_columnIdxMap.value(COLUMN_USER_EMAIL), User_Email);
    this->setCenteredItem(row, m_columnIdxMap.value(COLUMN_TYPE), Type);
    this->setCenteredItem(row, m_columnIdxMap.value(COLUMN_MODIFIED_USER_EMAIL), Mod_User_Email);

    this->setColumnHidden(m_columnIdxMap.value(COLUMN_ID), false);
    this->setColumnHidden(m_columnIdxMap.value(COLUMN_DATE), false);
    this->setColumnHidden(m_columnIdxMap.value(COLUMN_USER_EMAIL), false);
    this->setColumnHidden(m_columnIdxMap.value(COLUMN_TYPE), false);
    this->setColumnHidden(m_columnIdxMap.value(COLUMN_MODIFIED_USER_EMAIL), false);
}

void HistoryPageNS::ContainerWidget::addOperation_MoveComponent(int ID, QDateTime DateTime, QString User_Email, int Component_ID, QString Old_Rack, QString Old_Drawer, QString New_Rack, QString New_Drawer)
{
    int row = this->rowCount();
    this->insertRow(row);

    this->setCenteredItem(row, m_columnIdxMap.value(COLUMN_ID), ID);
    this->setCenteredItem(row, m_columnIdxMap.value(COLUMN_DATE), DateTime.toString("yyyy-MM-dd hh:mm:ss"));
    this->setCenteredItem(row, m_columnIdxMap.value(COLUMN_USER_EMAIL), User_Email);
    this->setCenteredItem(row, m_columnIdxMap.value(COLUMN_COMPONENT_ID), Component_ID);
    this->setCenteredItem(row, m_columnIdxMap.value(COLUMN_OLD_LOCATION_RACK), Old_Rack);
    this->setCenteredItem(row, m_columnIdxMap.value(COLUMN_OLD_LOCATION_DRAWER), Old_Drawer);
    this->setCenteredItem(row, m_columnIdxMap.value(COLUMN_NEW_LOCATION_RACK), New_Rack);
    this->setCenteredItem(row, m_columnIdxMap.value(COLUMN_NEW_LOCATION_DRAWER), New_Drawer);

    this->setColumnHidden(m_columnIdxMap.value(COLUMN_ID), false);
    this->setColumnHidden(m_columnIdxMap.value(COLUMN_DATE), false);
    this->setColumnHidden(m_columnIdxMap.value(COLUMN_USER_EMAIL), false);
    this->setColumnHidden(m_columnIdxMap.value(COLUMN_COMPONENT_ID), false);
    this->setColumnHidden(m_columnIdxMap.value(COLUMN_OLD_LOCATION_RACK), false);
    this->setColumnHidden(m_columnIdxMap.value(COLUMN_OLD_LOCATION_DRAWER), false);
    this->setColumnHidden(m_columnIdxMap.value(COLUMN_NEW_LOCATION_RACK), false);
    this->setColumnHidden(m_columnIdxMap.value(COLUMN_NEW_LOCATION_DRAWER), false);
}

HistoryPageNS::ContainerWidget::ContainerWidget(QWidget *parent)
    : QTableWidget(parent)
{
    this->setObjectName("HistoryPageNS_ContainerWidget");
    this->setSizePolicy(QSizePolicy::MinimumExpanding, QSizePolicy::Minimum);
    this->setContentsMargins(0, 0, 0, 0);

    this->setSortingEnabled(true);
    this->horizontalHeader()->setSectionsMovable(false);
    this->horizontalHeader()->setStretchLastSection(false);
    this->verticalHeader()->setVisible(false);

    m_columnIdxMap.insert(COLUMN_ID, 0);
    m_columnIdxMap.insert(COLUMN_DATE, 1);
    m_columnIdxMap.insert(COLUMN_USER_EMAIL, 2);
    m_columnIdxMap.insert(COLUMN_TYPE, 3);
    m_columnIdxMap.insert(COLUMN_COMPONENT_ID, 4);
    m_columnIdxMap.insert(COLUMN_DELTA, 5);
    m_columnIdxMap.insert(COLUMN_MODIFIED_USER_EMAIL, 6);
    m_columnIdxMap.insert(COLUMN_RACKNR, 7);
    m_columnIdxMap.insert(COLUMN_OLD_LOCATION_RACK, 8);
    m_columnIdxMap.insert(COLUMN_OLD_LOCATION_DRAWER, 9);
    m_columnIdxMap.insert(COLUMN_NEW_LOCATION_RACK, 10);
    m_columnIdxMap.insert(COLUMN_NEW_LOCATION_DRAWER, 11);

    this->setColumnCount(m_columnIdxMap.size());
    this->setRowCount(0);

    for (auto it = m_columnIdxMap.constBegin(); it != m_columnIdxMap.constEnd(); ++it)
        this->setHorizontalHeaderItem(it.value(), new QTableWidgetItem(it.key()));

    clearAll();

    this->horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);
    this->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
}

#include "historyPage/historyPage/moc_containerWidget.cpp"
// #include "historyPage/historyPage/containerWidget.moc"