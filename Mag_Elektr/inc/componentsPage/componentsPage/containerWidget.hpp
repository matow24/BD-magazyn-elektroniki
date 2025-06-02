#ifndef _COMPONENTSPAGE_CONTAINERWIDGET_HPP
#define _COMPONENTSPAGE_CONTAINERWIDGET_HPP

#include <QMap>
#include <QScrollArea>
#include <QWidget>
#include <QVBoxLayout>

#include "main.hpp"
#include "componentsPage/component/componentWidget.hpp"

namespace ComponentsPageNS
{

    class ContainerWidget : public QScrollArea
    {
        Q_OBJECT
    private:
        QWidget *m_container = nullptr;
        QVBoxLayout *m_containerLayout = nullptr;

        QMap<int, ComponentNS::ComponentWidget *> m_componentWidgets;

    public:
        const QMap<int, ComponentNS::ComponentWidget *> &getComponentWidgets() const;

        bool addComponentWidget(ComponentNS::ComponentWidget *componentWidget);

        bool removeComponentWidget(int ID);
        bool removeComponentWidget(ComponentNS::ComponentWidget *componentWidget);

        bool hideComponentWidget(ComponentNS::ComponentWidget *componentWidget);

        bool showComponentWidget(ComponentNS::ComponentWidget *componentWidget);

        void resetContainer();

        ContainerWidget(QWidget *parent = nullptr);

    private slots:
        void componentDeleted(ComponentNS::ComponentWidget *component);
    };
}

#endif // _COMPONENTSPAGE_CONTAINERWIDGET_HPP