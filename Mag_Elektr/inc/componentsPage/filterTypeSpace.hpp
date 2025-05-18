#ifndef _FILTERTYPESPACE_HPP
#define _FILTERTYPESPACE_HPP

#include <QButtonGroup>
#include <QFrame>
#include <QHBoxLayout>
#include <QLineEdit>
#include <QMap>
#include <QPushButton>
#include <QToolBar>
#include <QToolButton>
#include <QTreeWidget>
#include <QTreeWidgetItem>
#include <QWidget>
#include <QVBoxLayout>
#include <QVector>

#include "main.hpp"

class FilterTypeSpace : public QWidget
{
    Q_OBJECT
private:
    UserRole m_userRole;

    QVBoxLayout *m_mainLayout = nullptr;

    QWidget *m_enableButtons = nullptr;
    QPushButton *m_enableLocationButton = nullptr;
    QWidget *m_enableButtonsFiller = nullptr;
    QPushButton *m_enableSearchButton = nullptr;

    QWidget *m_locationField = nullptr;
    QLineEdit *m_locationFieldRack = nullptr;
    QLineEdit *m_locationFieldShelf = nullptr;
    QPushButton *m_locationFieldButton = nullptr;

    QWidget *m_searchField = nullptr;
    QLineEdit *m_searchFieldText = nullptr;
    QPushButton *m_searchFieldButton = nullptr;

    QFrame *m_separator = nullptr;

    QTreeWidget *m_treeWidget = nullptr;

    bool m_recurrencyFlag = false;
    QMap<QString, QVector<QString>> *m_signaledVariants;

    void scanVariants();

public:
    FilterTypeSpace(UserRole userRole, QWidget *parent = nullptr);

signals:
    void variantItemChanged(QMap<QString, QVector<QString>>, bool checked);

private slots:
    void toggleLocationField(bool checked);
    void toggleSearchField(bool checked);

    void treeWidgetItemChanged(QTreeWidgetItem *item, int column);
};

#endif // _FILTERTYPESPACE_HPP