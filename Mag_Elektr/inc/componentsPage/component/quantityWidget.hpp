#ifndef _COMPONENTNS_QUANTITYWIDGET_HPP
#define _COMPONENTNS_QUANTITYWIDGET_HPP

#include <QHBoxLayout>
#include <QIntValidator>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QWidget>
#include <QVBoxLayout>

#include "main.hpp"

namespace ComponentNS
{

    class QuantityWidget : public QWidget
    {
        Q_OBJECT
    private:
        int m_quantity = 0;
        int m_rack = 0;
        int m_drawer = 0;
        int m_maxQuantity = INT_MAX;    

        QVBoxLayout *m_mainLayout = nullptr;

        QWidget *m_infoWidget = nullptr;
        QGridLayout *m_infoLayout = nullptr;

        QLabel *m_quantityNameLabel = nullptr;
        QLabel *m_quantityValueLabel = nullptr;
        QLabel *m_rackNameLabel = nullptr;
        QLabel *m_rackValueLabel = nullptr;
        QLabel *m_drawerNameLabel = nullptr;
        QLabel *m_drawerValueLabel = nullptr;

        QWidget *m_spacer = nullptr;

        QLabel *m_editLabel = nullptr;

        QWidget *m_editWidget = nullptr;
        QHBoxLayout *m_editLayout;
        QPushButton *m_substractButton = nullptr;
        QLineEdit *m_editField = nullptr;
        QIntValidator *m_editFieldValidator = nullptr;
        QPushButton *m_addButton = nullptr;
        QPushButton *m_confirmButton = nullptr;

    public:
        void setQuantity(int quantity);
        int getQuantity() const;

        void setMaxQuantity(int maxQuantity);
        int getMaxQuantity() const;

        void setRack(int rack);
        int getRack() const;

        void setDrawer(int drawer);
        int getDrawer() const;

        QuantityWidget(QWidget *parent = nullptr);

    signals:
        void deltaConfirmed(int &delta);

    private slots:
        void substractButtonClicked();
        void addButtonClicked();
        void confirmButtonClicked();
        void editTextChanged(const QString &text);
    };

} // namespace ComponentNS

#endif // _COMPONENTNS_QUANTITYWIDGET_HPP