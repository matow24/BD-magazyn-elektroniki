#include "componentsPage/component/parametersWidget.hpp"

void ComponentNS::ParametersWidget::setName(QString &name)
{
    m_nameValue->setText(name);
}

QString ComponentNS::ParametersWidget::getName() const
{
    return m_nameValue->text();
}

void ComponentNS::ParametersWidget::setVariantName(QString &variantName)
{
    m_variantNameValue->setText(variantName);
}

QString ComponentNS::ParametersWidget::getVariantName() const
{
    return m_variantNameValue->text();
}

void ComponentNS::ParametersWidget::setVariantType(QString &variantType)
{
    m_variantTypeValue->setText(variantType);
}

QString ComponentNS::ParametersWidget::getVariantType() const
{
    return m_variantTypeValue->text();
}

void ComponentNS::ParametersWidget::setManufacturer(QString &manufacturer)
{
    m_manufacturerValue->setText(manufacturer);
}

QString ComponentNS::ParametersWidget::getManufacturer() const
{
    return m_manufacturerValue->text();
}

void ComponentNS::ParametersWidget::setSymbol(QString &symbol)
{
    m_symbolValue->setText(symbol);
}

QString ComponentNS::ParametersWidget::getSymbol() const
{
    return m_symbolValue->text();
}

void ComponentNS::ParametersWidget::setDatasheet(QString &datasheet)
{
    m_cleanDatasheet = datasheet;
    QUrl datasheetUrl(m_cleanDatasheet);
    QString datasheetDomain = datasheetUrl.host();
    QColor labelColor = m_datasheetValue->palette().color(QPalette::ButtonText);

    QString linkHTML = QString(
                           "<a href=\"%1\" style=\"color: %2; text-decoration: underline;\">%3</a>")
                           .arg(datasheetUrl.toString(), labelColor.name(), datasheetDomain);
    m_datasheetValue->setText(linkHTML);
}

QString ComponentNS::ParametersWidget::getDatasheet() const
{
    return m_datasheetValue->text();
}

ComponentNS::ParametersWidget::ParametersWidget(QWidget *parent) : QWidget(parent)
{
    this->setObjectName("Component_ParametersWidget");
    this->setSizePolicy(QSizePolicy::MinimumExpanding, QSizePolicy::MinimumExpanding);
    this->setContentsMargins(0, 0, 0, 0);
    this->setAttribute(Qt::WA_StyledBackground, true);

    m_mainLayout = new QGridLayout(this);
    this->setLayout(m_mainLayout);
    m_mainLayout->setContentsMargins(0, 0, 0, 0);
    m_mainLayout->setSpacing(0);

    m_nameParameter = new QLabel(tr("Nazwa") + QString(": "), this);
    m_mainLayout->addWidget(m_nameParameter, 0, 0);
    m_nameParameter->setObjectName("Component_ParametersWidget_NameLabel");
    m_nameValue = new QLabel("", this);
    m_mainLayout->addWidget(m_nameValue, 0, 1);
    m_nameValue->setObjectName("Component_ParametersWidget_ValueLabel");

    m_variantNameParameter = new QLabel(tr("Rodzaj") + QString(": "), this);
    m_mainLayout->addWidget(m_variantNameParameter, 1, 0);
    m_variantNameParameter->setObjectName("Component_ParametersWidget_NameLabel");
    m_variantNameValue = new QLabel("", this);
    m_mainLayout->addWidget(m_variantNameValue, 1, 1);
    m_variantNameValue->setObjectName("Component_ParametersWidget_ValueLabel");

    m_variantTypeParameter = new QLabel(tr("Typ") + QString(": "), this);
    m_mainLayout->addWidget(m_variantTypeParameter, 2, 0);
    m_variantTypeParameter->setObjectName("Component_ParametersWidget_NameLabel");
    m_variantTypeValue = new QLabel("", this);
    m_mainLayout->addWidget(m_variantTypeValue, 2, 1);
    m_variantTypeValue->setObjectName("Component_ParametersWidget_ValueLabel");

    m_manufacturerParameter = new QLabel(tr("Producent") + QString(": "), this);
    m_mainLayout->addWidget(m_manufacturerParameter, 3, 0);
    m_manufacturerParameter->setObjectName("Component_ParametersWidget_NameLabel");
    m_manufacturerValue = new QLabel("", this);
    m_mainLayout->addWidget(m_manufacturerValue, 3, 1);
    m_manufacturerValue->setObjectName("Component_ParametersWidget_ValueLabel");

    m_symbolParameter = new QLabel(tr("Symbol") + QString(": "), this);
    m_mainLayout->addWidget(m_symbolParameter, 4, 0);
    m_symbolParameter->setObjectName("Component_ParametersWidget_NameLabel");
    m_symbolValue = new QLabel("", this);
    m_mainLayout->addWidget(m_symbolValue, 4, 1);
    m_symbolValue->setObjectName("Component_ParametersWidget_ValueLabel");

    m_datasheetParameter = new QLabel(tr("Karta Katalogowa") + QString(": "), this);
    m_mainLayout->addWidget(m_datasheetParameter, 5, 0);
    m_datasheetParameter->setObjectName("Component_ParametersWidget_NameLabel");
    m_datasheetValue = new QLabel("", this);
    m_mainLayout->addWidget(m_datasheetValue, 5, 1);
    m_datasheetValue->setObjectName("Component_ParametersWidget_ValueLabel");
    m_datasheetValue->setTextFormat(Qt::RichText);
    m_datasheetValue->setTextInteractionFlags(Qt::TextBrowserInteraction);
    m_datasheetValue->setOpenExternalLinks(true);
}

#include "componentsPage/component/moc_parametersWidget.cpp"
// #include "componentsPage/component/parametersWidget.moc"