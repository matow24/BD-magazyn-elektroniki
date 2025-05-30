#ifndef _COMPONENTSPAGE_HPP
#define _COMPONENTSPAGE_HPP

#include <QFrame>
#include <QHBoxLayout>
#include <QMap>
#include <QWidget>
#include <QVBoxLayout>

#include "main.hpp"

#include "componentsPage/componentsPage/containerWidget.hpp"
#include "componentsPage/componentsPage/filterWidget.hpp"
#include "componentsPage/componentsPage/treeFilterWidget.hpp"

class ComponentsPage : public QWidget
{
    Q_OBJECT
private:
    QHBoxLayout *m_mainLayout = nullptr;
    QFrame *m_mainFrame = nullptr;

    QWidget *m_filterPanel = nullptr;
    QVBoxLayout *m_filterPanelLayout = nullptr;
    QFrame *m_filterPanelFrame = nullptr;

    ComponentsPageNS::ContainerWidget *m_containerWidget = nullptr;
    ComponentsPageNS::FilterWidget *m_filterWidget = nullptr;
    ComponentsPageNS::TreeFilterWidget *m_treeFilterWidget = nullptr;

public:
    ComponentsPage(QWidget *parent = nullptr);
};

#endif // _COMPONENTSPAGE_HPP