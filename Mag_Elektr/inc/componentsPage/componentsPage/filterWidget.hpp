#ifndef _COMPONENTSPAGE_FILTERWIDGET_HPP
#define _COMPONENTSPAGE_FILTERWIDGET_HPP

#include <QHBoxLayout>
#include <QIntValidator>
#include <QLineEdit>
#include <QMap>
#include <QPushButton>
#include <QRegularExpression>
#include <QRegularExpressionValidator>
#include <QString>
#include <QTreeWidget>
#include <QTreeWidgetItem>
#include <QWidget>
#include <QVBoxLayout>
#include <QVector>

#include "main.hpp"
#include "componentsPage/componentsPage/containerWidget.hpp"
#include "componentsPage/componentsPage/treeFilterWidget.hpp"

namespace ComponentsPageNS
{
    class FilterWidget : public QWidget
    {
        Q_OBJECT
    private:
        bool m_treeRecurrencyFlag = false;

        ContainerWidget *m_containerWidget = nullptr;
        TreeFilterWidget *m_treeFilterWidget = nullptr;

        QVBoxLayout *m_mainLayout = nullptr;

        QWidget *m_enableButtons = nullptr;
        QHBoxLayout *m_enableButtonsLayout = nullptr;

        QPushButton *m_enableLocationButton = nullptr;
        QWidget *m_enableButtonsFiller = nullptr;
        QPushButton *m_enableSearchButton = nullptr;
        QPushButton *m_resetButton = nullptr;

        QWidget *m_locationField = nullptr;
        QHBoxLayout *m_locationFieldLayout = nullptr;

        QLineEdit *m_locationFieldRack = nullptr;
        QIntValidator *m_locationFieldRackValidator = nullptr;
        QLineEdit *m_locationFieldDrawer = nullptr;
        QIntValidator *m_locationFieldDrawerValidator = nullptr;
        QPushButton *m_locationFieldButton = nullptr;

        QWidget *m_searchField = nullptr;
        QHBoxLayout *m_searchFieldLayout = nullptr;
        QLineEdit *m_searchFieldText = nullptr;
        QRegularExpressionValidator *m_searchFieldValidator = nullptr;
        QPushButton *m_searchFieldButton = nullptr;

    public:
        FilterWidget(ContainerWidget *containerWidget, TreeFilterWidget *treeFilterWidget, QWidget *parent = nullptr);

    private slots:
        void toggleLocationField(bool checked);
        void toggleSearchField(bool checked);
        void resetAll();
        void findByLocation();
        void findByName();
        void locationTextChanged(const QString &text);
        void searchTextChanged(const QString &text);
    };
} // namespace ComponentsPageNS

#endif // _COMPONENTSPAGE_FILTERWIDGET_HPP