#ifndef _HISTORYPAGE_FILTERWIDGET_HPP
#define _HISTORYPAGE_FILTERWIDGET_HPP

#include <QCalendarWidget>
#include <QDateEdit>
#include <QDateTime>
#include <QFrame>
#include <QGridLayout>
#include <QHBoxLayout>
#include <QIntValidator>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QRegularExpression>
#include <QRegularExpressionValidator>
#include <QSpacerItem>
#include <QTime>
#include <QWidget>
#include <QVBoxLayout>

#include "main.hpp"

#include "historyPage/historyPage/containerWidget.hpp"

namespace HistoryPageNS
{
    class FilterWidget : public QWidget
    {
        Q_OBJECT
    private:
        QVBoxLayout *m_mainLayout = nullptr;

        QWidget *m_dateTimeFilterField = nullptr;
        QGridLayout *m_dateTimeFilterFieldLayout = nullptr;
        QLabel *m_dateTimeFilterLabel = nullptr;
        QDateEdit *m_dateTimeFilterMinField = nullptr;
        QDateEdit *m_dateTimeFilterMaxField = nullptr;

        QWidget *m_userFilterField = nullptr;
        QVBoxLayout *m_userFilterFieldLayout = nullptr;
        QLabel *m_userFilterLabel = nullptr;
        QLineEdit *m_userFilterFieldEdit = nullptr;
        QRegularExpressionValidator *m_userFilterFieldValidator = nullptr;

        QWidget *m_locationFilterField = nullptr;
        QGridLayout *m_locationFilterFieldLayout = nullptr;
        QLabel *m_locationFilterLabel = nullptr;
        QLineEdit *m_locationFilterRackFieldEdit = nullptr;
        QIntValidator *m_locationFilterRackFieldValidator = nullptr;
        QLineEdit *m_locationFilterDrawerFieldEdit = nullptr;
        QIntValidator *m_locationFilterDrawerFieldValidator = nullptr;

        QWidget *m_componentFilterField = nullptr;
        QVBoxLayout *m_componentFilterFieldLayout = nullptr;
        QLabel *m_componentFilterLabel = nullptr;
        QLineEdit *m_componentFilterFieldEdit = nullptr;
        QIntValidator *m_componentFilterFieldValidator = nullptr;

        QPushButton *m_searchButton = nullptr;

        QWidget *m_emptySpace = nullptr;

        ContainerWidget *m_containerWidget = nullptr;

    public:
        FilterWidget(ContainerWidget *containerWidget, QWidget *parent = nullptr);

    private slots:
        void onSearchButtonClicked();
        void onDateTimeFilterMinFieldChanged(const QDate &date);
        void onDateTimeFilterMaxFieldChanged(const QDate &date);
        void onLocationFilterRackFieldEditTextChanged(const QString &text);
    };
} // namespace HistoryPageNS

#endif // _HISTORYPAGE_FILTERWIDGET_HPP