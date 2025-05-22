#ifndef _COMPONENTNS_COMPONENTWIDGET_HPP
#define _COMPONENTNS_COMPONENTWIDGET_HPP

#include <QHBoxLayout>
#include <QString>
#include <QWidget>

#include "main.hpp"

#include "componentsPage/component/editWidget.hpp"
#include "componentsPage/component/parametersWidget.hpp"
#include "componentsPage/component/quantityWidget.hpp"

namespace ComponentNS
{

    class ComponentWidget : public QWidget
    {
        Q_OBJECT
    private:
        int m_ID = -1;

        QHBoxLayout *m_mainLayout = nullptr;

        ParametersWidget *m_parametersWidget = nullptr;
        QWidget *m_spacer1 = nullptr;
        QuantityWidget *m_quantityWidget = nullptr;
        QWidget *m_spacer2 = nullptr;
        EditWidget *m_editWidget = nullptr;

    public:
        int getID() const;
        ParametersWidget &getParametersWidget();
        QuantityWidget &getQuantityWidget();

        ComponentWidget(int ID, QWidget *parent = nullptr);

    signals:
        void componentDeleted(ComponentWidget *component);

    private slots:
        void deltaConfirmed(int &delta);
        void deleteComponent();
        void statisticsComponent();

    public slots:
        void updateComponent();
    };

} // namespace ComponentNS

#endif // _COMPONENTNS_COMPONENTWIDGET_HPP