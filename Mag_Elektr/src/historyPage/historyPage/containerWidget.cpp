#include "historyPage/historyPage/containerWidget.hpp"

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
    this->setColumnHidden(m_columnIdxMap.value(tr("Rodzaj Operacji")), false);
    this->setColumnHidden(m_columnIdxMap.value(tr("Data")), false);
    this->setColumnHidden(m_columnIdxMap.value(tr("Email Użytkownika")), false);
    this->setColumnHidden(m_columnIdxMap.value(tr("Typ")), true);
    this->setColumnHidden(m_columnIdxMap.value(tr("ID Komponentu")), true);
    this->setColumnHidden(m_columnIdxMap.value(tr("Zmiana Ilości")), true);
    this->setColumnHidden(m_columnIdxMap.value(tr("Adres Email Modyfikowany")), true);
    this->setColumnHidden(m_columnIdxMap.value(tr("Nr Regału")), true);
    this->setColumnHidden(m_columnIdxMap.value(tr("Stary Regał")), true);
    this->setColumnHidden(m_columnIdxMap.value(tr("Stara Szuflada")), true);
    this->setColumnHidden(m_columnIdxMap.value(tr("Nowy Regał")), true);
    this->setColumnHidden(m_columnIdxMap.value(tr("Nowa Szuflada")), true);
}

void HistoryPageNS::ContainerWidget::addOperation_ChangeComponent(int ID, QDateTime DateTime, QString User_Email, int Component_ID, QChar Type)
{
    int row = this->rowCount();
    this->insertRow(row);

    this->setCenteredItem(row, m_columnIdxMap.value(tr("Rodzaj Operacji")), tr("Zmiana Komponent"));
    this->setCenteredItem(row, m_columnIdxMap.value(tr("Data")), DateTime.toString("yyyy-MM-dd hh:mm:ss"));
    this->setCenteredItem(row, m_columnIdxMap.value(tr("Email Użytkownika")), User_Email);
    this->setCenteredItem(row, m_columnIdxMap.value(tr("Typ")), Type);
    this->setCenteredItem(row, m_columnIdxMap.value(tr("ID Komponentu")), Component_ID);

    this->setColumnHidden(m_columnIdxMap.value(tr("Rodzaj Operacji")), false);
    this->setColumnHidden(m_columnIdxMap.value(tr("Data")), false);
    this->setColumnHidden(m_columnIdxMap.value(tr("Email Użytkownika")), false);
    this->setColumnHidden(m_columnIdxMap.value(tr("Typ")), false);
    this->setColumnHidden(m_columnIdxMap.value(tr("ID Komponentu")), false);
}

void HistoryPageNS::ContainerWidget::addOperation_ChangeQuantity(int ID, QDateTime DateTime, QString User_Email, int Component_ID, int Delta)
{
    int row = this->rowCount();
    this->insertRow(row);

    this->setCenteredItem(row, m_columnIdxMap.value(tr("Rodzaj Operacji")), tr("Zmiana Ilości"));
    this->setCenteredItem(row, m_columnIdxMap.value(tr("Data")), (DateTime.toString("yyyy-MM-dd hh:mm:ss")));
    this->setCenteredItem(row, m_columnIdxMap.value(tr("Email Użytkownika")), User_Email);
    this->setCenteredItem(row, m_columnIdxMap.value(tr("ID Komponentu")), Component_ID);
    this->setCenteredItem(row, m_columnIdxMap.value(tr("Zmiana Ilości")), Delta);

    this->setColumnHidden(m_columnIdxMap.value(tr("Rodzaj Operacji")), false);
    this->setColumnHidden(m_columnIdxMap.value(tr("Data")), false);
    this->setColumnHidden(m_columnIdxMap.value(tr("Email Użytkownika")), false);
    this->setColumnHidden(m_columnIdxMap.value(tr("ID Komponentu")), false);
    this->setColumnHidden(m_columnIdxMap.value(tr("Zmiana Ilości")), false);
}

void HistoryPageNS::ContainerWidget::addOperation_ChangeRack(int ID, QDateTime DateTime, QString User_Email, int RackNr, QChar Type)
{
    int row = this->rowCount();
    this->insertRow(row);

    this->setCenteredItem(row, m_columnIdxMap.value(tr("Rodzaj Operacji")), tr("Zmiana Regał"));
    this->setCenteredItem(row, m_columnIdxMap.value(tr("Data")), DateTime.toString("yyyy-MM-dd hh:mm:ss"));
    this->setCenteredItem(row, m_columnIdxMap.value(tr("Email Użytkownika")), User_Email);
    this->setCenteredItem(row, m_columnIdxMap.value(tr("Typ")), Type);
    this->setCenteredItem(row, m_columnIdxMap.value(tr("Nr Regału")), RackNr);

    this->setColumnHidden(m_columnIdxMap.value(tr("Rodzaj Operacji")), false);
    this->setColumnHidden(m_columnIdxMap.value(tr("Data")), false);
    this->setColumnHidden(m_columnIdxMap.value(tr("Email Użytkownika")), false);
    this->setColumnHidden(m_columnIdxMap.value(tr("Typ")), false);
    this->setColumnHidden(m_columnIdxMap.value(tr("Nr Regału")), false);
}

void HistoryPageNS::ContainerWidget::addOperation_ChangeUser(int ID, QDateTime DateTime, QString User_Email, QString Mod_User_Email, QChar Type)
{
    int row = this->rowCount();
    this->insertRow(row);

    this->setCenteredItem(row, m_columnIdxMap.value(tr("Rodzaj Operacji")), tr("Zmiana Użytkownik"));
    this->setCenteredItem(row, m_columnIdxMap.value(tr("Data")), DateTime.toString("yyyy-MM-dd hh:mm:ss"));
    this->setCenteredItem(row, m_columnIdxMap.value(tr("Email Użytkownika")), User_Email);
    this->setCenteredItem(row, m_columnIdxMap.value(tr("Typ")), Type);
    this->setCenteredItem(row, m_columnIdxMap.value(tr("Adres Email Modyfikowany")), Mod_User_Email);

    this->setColumnHidden(m_columnIdxMap.value(tr("Rodzaj Operacji")), false);
    this->setColumnHidden(m_columnIdxMap.value(tr("Data")), false);
    this->setColumnHidden(m_columnIdxMap.value(tr("Email Użytkownika")), false);
    this->setColumnHidden(m_columnIdxMap.value(tr("Typ")), false);
    this->setColumnHidden(m_columnIdxMap.value(tr("Adres Email Modyfikowany")), false);
}

void HistoryPageNS::ContainerWidget::addOperation_MoveComponent(int ID, QDateTime DateTime, QString User_Email, int Component_ID, QString Old_Rack, QString Old_Drawer, QString New_Rack, QString New_Drawer)
{
    int row = this->rowCount();
    this->insertRow(row);

    this->setCenteredItem(row, m_columnIdxMap.value(tr("Rodzaj Operacji")), tr("Przeniesienie Komponentu"));
    this->setCenteredItem(row, m_columnIdxMap.value(tr("Data")), DateTime.toString("yyyy-MM-dd hh:mm:ss"));
    this->setCenteredItem(row, m_columnIdxMap.value(tr("Email Użytkownika")), User_Email);
    this->setCenteredItem(row, m_columnIdxMap.value(tr("ID Komponentu")), Component_ID);
    this->setCenteredItem(row, m_columnIdxMap.value(tr("Stary Regał")), Old_Rack);
    this->setCenteredItem(row, m_columnIdxMap.value(tr("Stara Szuflada")), Old_Drawer);
    this->setCenteredItem(row, m_columnIdxMap.value(tr("Nowy Regał")), New_Rack);
    this->setCenteredItem(row, m_columnIdxMap.value(tr("Nowa Szuflada")), New_Drawer);

    this->setColumnHidden(m_columnIdxMap.value(tr("Rodzaj Operacji")), false);
    this->setColumnHidden(m_columnIdxMap.value(tr("Data")), false);
    this->setColumnHidden(m_columnIdxMap.value(tr("Email Użytkownika")), false);
    this->setColumnHidden(m_columnIdxMap.value(tr("ID Komponentu")), false);
    this->setColumnHidden(m_columnIdxMap.value(tr("Stary Regał")), false);
    this->setColumnHidden(m_columnIdxMap.value(tr("Stara Szuflada")), false);
    this->setColumnHidden(m_columnIdxMap.value(tr("Nowy Regał")), false);
    this->setColumnHidden(m_columnIdxMap.value(tr("Nowa Szuflada")), false);
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

    m_columnIdxMap.insert(tr("Rodzaj Operacji"), 0);
    m_columnIdxMap.insert(tr("Data"), 1);
    m_columnIdxMap.insert(tr("Email Użytkownika"), 2);
    m_columnIdxMap.insert(tr("Typ"), 3);
    m_columnIdxMap.insert(tr("ID Komponentu"), 4);
    m_columnIdxMap.insert(tr("Zmiana Ilości"), 5);
    m_columnIdxMap.insert(tr("Adres Email Modyfikowany"), 6);
    m_columnIdxMap.insert(tr("Nr Regału"), 7);
    m_columnIdxMap.insert(tr("Stary Regał"), 8);
    m_columnIdxMap.insert(tr("Stara Szuflada"), 9);
    m_columnIdxMap.insert(tr("Nowy Regał"), 10);
    m_columnIdxMap.insert(tr("Nowa Szuflada"), 11);

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