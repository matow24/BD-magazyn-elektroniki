#ifndef _COMPONENTSPAGE_TREEFILTERWIDGET_HPP
#define _COMPONENTSPAGE_TREEFILTERWIDGET_HPP

#include <QMap>
#include <QTreeWidget>
#include <QTreeWidgetItem>
#include <QSet>
#include <QString>

#include "main.hpp"

#include "componentsPage/componentsPage/containerWidget.hpp"

namespace ComponentsPageNS
{

    class TreeFilterWidget : public QTreeWidget
    {
        Q_OBJECT
    private:
        bool m_fromDataBaseFlag = true;
        bool m_treeRecurrencyFlag = false;

        UserRole m_userRole = UserRole::Guest;

        ContainerWidget *m_containerWidget = nullptr;

        void addByVariantName(QString variantName);
        void removeByVariantName(QString variantName);

        void addByVariantType(QString variantType);
        void removeByVariantType(QString variantType);

        void hideInContainerByVariantName(QString variantName);
        void showInContainerByVariantName(QString variantName);

        void hideInContainerByVariantType(QString variantType);
        void showInContainerByVariantType(QString variantType);

        void addFromDatabaseByVariantName(QString variantName);
        void removeFromDatabaseByVariantName(QString variantName);

        void addFromDatabaseByVariantType(QString variantType);
        void removeFromDatabaseByVariantType(QString variantType);

    public:
        void setFromDataBaseFlag(bool fromDataBaseFlag);

        void enableTreeWidgetItem(QString variantType, QString variantName);

        void disableAll();

        void resetVariants();

        TreeFilterWidget(ContainerWidget *containerWidget, UserRole userRole, QWidget *parent = nullptr);

    private slots:
        void itemChanged(QTreeWidgetItem *item, int column);

    public slots:
        void rescanVariants();
    };
} // namespace ComponentsPageNS

#endif // _COMPONENTSPAGE_TREEFILTERWIDGET_HPP