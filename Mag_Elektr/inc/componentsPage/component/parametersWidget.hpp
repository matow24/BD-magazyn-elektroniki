#ifndef _COMPONENTNS_PARAMETERSWIDGET_HPP
#define _COMPONENTNS_PARAMETERSWIDGET_HPP

#include <QColor>
#include <QGridLayout>
#include <QLabel>
#include <QString>
#include <QUrl>
#include <QWidget>

#include "main.hpp"

namespace ComponentNS
{

    class ParametersWidget : public QWidget
    {
        Q_OBJECT
    private:
        QGridLayout *m_mainLayout = nullptr;

        QLabel *m_nameParameter = nullptr;
        QLabel *m_nameValue = nullptr;

        QLabel *m_variantNameParameter = nullptr;
        QLabel *m_variantNameValue = nullptr;

        QLabel *m_variantTypeParameter = nullptr;
        QLabel *m_variantTypeValue = nullptr;

        QLabel *m_manufacturerParameter = nullptr;
        QLabel *m_manufacturerValue = nullptr;

        QLabel *m_symbolParameter = nullptr;
        QLabel *m_symbolValue = nullptr;

        QString m_cleanDatasheet;
        QLabel *m_datasheetParameter = nullptr;
        QLabel *m_datasheetValue = nullptr;

    public:
        void setName(QString &name);
        QString getName() const;

        void setVariantName(QString &variantName);
        QString getVariantName() const;

        void setVariantType(QString &variantType);
        QString getVariantType() const;

        void setManufacturer(QString &manufacturer);
        QString getManufacturer() const;

        void setSymbol(QString &symbol);
        QString getSymbol() const;

        void setDatasheet(QString &datasheet);
        QString getDatasheet() const;

        ParametersWidget(QWidget *parent = nullptr);
    };

} // namespace ComponentNS

#endif // _COMPONENTNS_PARAMETERSWIDGET_HPP