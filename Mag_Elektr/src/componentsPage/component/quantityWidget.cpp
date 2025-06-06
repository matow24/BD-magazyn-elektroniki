#include "componentsPage/component/quantityWidget.hpp"

#define ICON_ADD ":/icons/add.png"
#define ICON_CHECK ":/icons/check.png"
#define ICON_MINUS ":/icons/minus.png"

void ComponentNS::QuantityWidget::setQuantity(int quantity)
{
    m_quantity = quantity;
    m_quantityValueLabel->setText(QString::number(m_quantity));
    m_editField->setText("0");
    m_editFieldValidator->setRange(-1 * m_quantity, m_maxQuantity - m_quantity);
}

int ComponentNS::QuantityWidget::getQuantity() const
{
    return m_quantity;
}

void ComponentNS::QuantityWidget::setMaxQuantity(int maxQuantity)
{
    m_maxQuantity = maxQuantity;
    m_editField->setText("0");
    m_editFieldValidator->setRange(-1 * m_quantity, m_maxQuantity - m_quantity);
}

int ComponentNS::QuantityWidget::getMaxQuantity() const
{
    return m_maxQuantity;
}

void ComponentNS::QuantityWidget::setRack(int rack)
{
    m_rack = rack;
    m_rackValueLabel->setText(QString::number(m_rack));
}

int ComponentNS::QuantityWidget::getRack() const
{
    return m_rack;
}

void ComponentNS::QuantityWidget::setDrawer(int drawer)
{
    m_drawer = drawer;
    m_drawerValueLabel->setText(QString::number(m_drawer));
}

int ComponentNS::QuantityWidget::getDrawer() const
{
    return m_drawer;
}

ComponentNS::QuantityWidget::QuantityWidget(QWidget *parent) : QWidget(parent)
{
    this->setObjectName("Component_QuantityWidget");
    this->setSizePolicy(QSizePolicy::MinimumExpanding, QSizePolicy::MinimumExpanding);
    this->setContentsMargins(0, 0, 0, 0);

    m_mainLayout = new QVBoxLayout(this);
    this->setLayout(m_mainLayout);
    m_mainLayout->setContentsMargins(0, 0, 0, 0);
    m_mainLayout->setSpacing(10);

    m_infoWidget = new QWidget(this);
    m_mainLayout->addWidget(m_infoWidget, 0);
    m_infoWidget->setObjectName("Component_QuantityWidget_InfoWidget");
    m_infoWidget->setSizePolicy(QSizePolicy::MinimumExpanding, QSizePolicy::MinimumExpanding);
    m_infoWidget->setContentsMargins(0, 0, 0, 0);
    m_infoWidget->setAttribute(Qt::WA_StyledBackground, true);

    m_infoLayout = new QGridLayout(m_infoWidget);
    m_infoWidget->setLayout(m_infoLayout);
    m_infoLayout->setContentsMargins(0, 0, 0, 0);
    m_infoLayout->setSpacing(0);

    m_quantityNameLabel = new QLabel(tr("Stan Magazynowy"), this);
    m_infoLayout->addWidget(m_quantityNameLabel, 0, 0, Qt::AlignCenter);
    m_quantityNameLabel->setObjectName("Component_QuantityWidget_NameLabel");

    m_quantityValueLabel = new QLabel(QString::number(m_quantity), this);
    m_infoLayout->addWidget(m_quantityValueLabel, 1, 0, Qt::AlignCenter);
    m_quantityValueLabel->setObjectName("Component_QuantityWidget_ValueLabel");

    m_rackNameLabel = new QLabel(tr("Regał"), this);
    m_infoLayout->addWidget(m_rackNameLabel, 0, 1, Qt::AlignCenter);
    m_rackNameLabel->setObjectName("Component_QuantityWidget_NameLabel");

    m_rackValueLabel = new QLabel(QString::number(m_rack), this);
    m_infoLayout->addWidget(m_rackValueLabel, 1, 1, Qt::AlignCenter);
    m_rackValueLabel->setObjectName("Component_QuantityWidget_ValueLabel");

    m_drawerNameLabel = new QLabel(tr("Szuflada"), this);
    m_infoLayout->addWidget(m_drawerNameLabel, 0, 2, Qt::AlignCenter);
    m_drawerNameLabel->setObjectName("Component_QuantityWidget_NameLabel");

    m_drawerValueLabel = new QLabel(QString::number(m_drawer), this);
    m_infoLayout->addWidget(m_drawerValueLabel, 1, 2, Qt::AlignCenter);
    m_drawerValueLabel->setObjectName("Component_QuantityWidget_ValueLabel");

    m_spacer = new QWidget(this);
    m_mainLayout->addWidget(m_spacer, 1);

    if (g_userRole == UserRole::Employee)
        m_editLabel = new QLabel(tr("Pobierana ilość elementów"), this);
    else
        m_editLabel = new QLabel(tr("Zmiana ilości elementów"), this);
    m_mainLayout->addWidget(m_editLabel, 0, Qt::AlignCenter);
    m_editLabel->setObjectName("Component_QuantityWidget_EditLabel");

    m_editWidget = new QWidget(this);
    m_mainLayout->addWidget(m_editWidget, 0);
    m_editWidget->setSizePolicy(QSizePolicy::MinimumExpanding, QSizePolicy::MinimumExpanding);
    m_editWidget->setContentsMargins(0, 0, 0, 0);

    m_editLayout = new QHBoxLayout(m_editWidget);
    m_editWidget->setLayout(m_editLayout);
    m_editLayout->setContentsMargins(0, 0, 0, 0);
    m_editLayout->setSpacing(0);

    m_substractButton = new QPushButton(this);
    m_editLayout->addWidget(m_substractButton, 0);
    m_substractButton->setObjectName("Component_QuantityWidget_Button");
    m_substractButton->setIcon(QIcon(ICON_MINUS));

    m_editField = new QLineEdit(this);
    m_editLayout->addWidget(m_editField, 1);
    m_editField->setObjectName("Component_QuantityWidget_EditField");
    m_editField->setSizePolicy(QSizePolicy::MinimumExpanding, QSizePolicy::MinimumExpanding);

    m_editFieldValidator = new QIntValidator(-1 * m_quantity, m_maxQuantity - m_quantity, this);
    m_editField->setValidator(m_editFieldValidator);
    m_editField->setText("0");
    m_editField->setAlignment(Qt::AlignCenter);

    m_addButton = new QPushButton(this);
    m_editLayout->addWidget(m_addButton, 0);
    m_addButton->setObjectName("Component_QuantityWidget_Button");
    m_addButton->setIcon(QIcon(ICON_ADD));

    m_confirmButton = new QPushButton(this);
    m_editLayout->addWidget(m_confirmButton, 0);
    m_confirmButton->setObjectName("Component_QuantityWidget_Button");
    m_confirmButton->setIcon(QIcon(ICON_CHECK));
    m_confirmButton->setEnabled(false);

    connect(m_substractButton, &QPushButton::clicked, this, &ComponentNS::QuantityWidget::substractButtonClicked);
    connect(m_addButton, &QPushButton::clicked, this, &ComponentNS::QuantityWidget::addButtonClicked);
    connect(m_confirmButton, &QPushButton::clicked, this, &ComponentNS::QuantityWidget::confirmButtonClicked);
    connect(m_editField, &QLineEdit::textChanged, this, &ComponentNS::QuantityWidget::editTextChanged);
}

void ComponentNS::QuantityWidget::substractButtonClicked()
{
    int quantity = m_editField->text().toInt();
    quantity -= 1;
    m_editField->setText(QString::number(quantity));
}

void ComponentNS::QuantityWidget::addButtonClicked()
{
    int quantity = m_editField->text().toInt();
    quantity += 1;
    m_editField->setText(QString::number(quantity));
}

void ComponentNS::QuantityWidget::confirmButtonClicked()
{
    int quantity = m_editField->text().toInt();
    if (g_userRole == UserRole::Employee)
        quantity *= -1; // Employees can only take, so we reverse the logic (positive quantity means negative delta)
    emit deltaConfirmed(quantity);
    m_editField->setText("0");
}

void ComponentNS::QuantityWidget::editTextChanged(const QString &text)
{
    if (m_editField->hasAcceptableInput() && text.toInt() != 0)
        m_confirmButton->setEnabled(true);
    else
        m_confirmButton->setEnabled(false);
    int quantity = text.toInt();
    if (g_userRole == UserRole::Employee) // Employees can only take, also logic reversed (positive quantity means negative delta)
    {
        if (quantity > m_quantity)
            m_editField->setText(QString::number(m_quantity));
        if (quantity >= m_quantity)
            m_addButton->setEnabled(false);
        else
            m_addButton->setEnabled(true);

        if (quantity < 0)
            m_editField->setText(QString::number(0));
        if (quantity <= 0)
            m_substractButton->setEnabled(false);
        else
            m_substractButton->setEnabled(true);
    }

    else // Admins can add and take, logic is normal (positive quantity means positive delta)
    {
        if (quantity < (-1 * m_quantity))
            m_editField->setText(QString::number(-1 * m_quantity));
        if (quantity <= (-1 * m_quantity))
            m_substractButton->setEnabled(false);
        else
            m_substractButton->setEnabled(true);

        if (quantity > (m_maxQuantity - m_quantity))
            m_editField->setText(QString::number(m_maxQuantity - m_quantity));
        if (quantity >= (m_maxQuantity - m_quantity))
            m_addButton->setEnabled(false);
        else
            m_addButton->setEnabled(true);
    }
}

#include "componentsPage/component/moc_quantityWidget.cpp"
// // #include "componentsPage/component/quantityWidget.moc"