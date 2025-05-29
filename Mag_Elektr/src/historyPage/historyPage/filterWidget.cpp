#include "historyPage/historyPage/filterWidget.hpp"

HistoryPageNS::FilterWidget::FilterWidget(ContainerWidget *containerWidget, QWidget *parent) : QWidget(parent)
{
    m_containerWidget = containerWidget;
    
    this->setObjectName("HistoryPageNS_FilterWidget");
    this->setSizePolicy(QSizePolicy::MinimumExpanding, QSizePolicy::MinimumExpanding);
    this->setContentsMargins(5, 5, 5, 5);
    this->setAttribute(Qt::WA_StyledBackground, true);


    m_mainLayout = new QVBoxLayout(this);
    this->setLayout(m_mainLayout);
    m_mainLayout->setContentsMargins(10, 20, 10, 20);
    m_mainLayout->setSpacing(30);

    m_dateTimeFilterField = new QWidget(this);
    m_mainLayout->addWidget(m_dateTimeFilterField, 0);
    m_dateTimeFilterField->setContentsMargins(0, 0, 0, 0);

    m_dateTimeFilterFieldLayout = new QGridLayout(m_dateTimeFilterField);
    m_dateTimeFilterField->setLayout(m_dateTimeFilterFieldLayout);
    m_dateTimeFilterFieldLayout->setContentsMargins(0, 0, 0, 0);
    m_dateTimeFilterFieldLayout->setSpacing(5);

    m_dateTimeFilterLabel = new QLabel(this);
    m_dateTimeFilterFieldLayout->addWidget(m_dateTimeFilterLabel, 0, 0, 1, 2, Qt::AlignCenter);
    m_dateTimeFilterLabel->setObjectName("HistoryPageNS_FilterWidget_Label");
    m_dateTimeFilterLabel->setSizePolicy(QSizePolicy::MinimumExpanding, QSizePolicy::MinimumExpanding);
    m_dateTimeFilterLabel->setText(tr("Zakres czasu"));

    m_dateTimeFilterMinField = new QDateEdit(this);
    m_dateTimeFilterFieldLayout->addWidget(m_dateTimeFilterMinField, 1, 0, 1, 1);
    m_dateTimeFilterMinField->setObjectName("HistoryPageNS_FilterWidget_DateEdit");
    m_dateTimeFilterMinField->setSizePolicy(QSizePolicy::MinimumExpanding, QSizePolicy::MinimumExpanding);
    m_dateTimeFilterMinField->setDisplayFormat("dd-MM-yyyy");
    m_dateTimeFilterMinField->setCalendarPopup(true);
    m_dateTimeFilterMinField->setDate(QDate::currentDate().addDays(-1));
    m_dateTimeFilterMinField->setButtonSymbols(QAbstractSpinBox::NoButtons);

    m_dateTimeFilterMaxField = new QDateEdit(this);
    m_dateTimeFilterFieldLayout->addWidget(m_dateTimeFilterMaxField, 1, 1, 1, 1);
    m_dateTimeFilterMaxField->setObjectName("HistoryPageNS_FilterWidget_DateEdit");
    m_dateTimeFilterMaxField->setSizePolicy(QSizePolicy::MinimumExpanding, QSizePolicy::MinimumExpanding);
    m_dateTimeFilterMaxField->setDisplayFormat("dd-MM-yyyy");
    m_dateTimeFilterMaxField->setCalendarPopup(true);
    m_dateTimeFilterMaxField->setDate(QDate::currentDate());
    m_dateTimeFilterMaxField->setButtonSymbols(QAbstractSpinBox::NoButtons);

    m_userFilterField = new QWidget(this);
    m_mainLayout->addWidget(m_userFilterField, 0);
    m_userFilterField->setContentsMargins(0, 0, 0, 0);

    m_userFilterFieldLayout = new QVBoxLayout(m_userFilterField);
    m_userFilterField->setLayout(m_userFilterFieldLayout);
    m_userFilterFieldLayout->setContentsMargins(0, 0, 0, 0);
    m_userFilterFieldLayout->setSpacing(5);

    m_userFilterLabel = new QLabel(this);
    m_userFilterFieldLayout->addWidget(m_userFilterLabel, 0, Qt::AlignCenter);
    m_userFilterLabel->setObjectName("HistoryPageNS_FilterWidget_Label");
    m_userFilterLabel->setSizePolicy(QSizePolicy::MinimumExpanding, QSizePolicy::MinimumExpanding);
    m_userFilterLabel->setText(tr("Adres email"));

    m_userFilterFieldEdit = new QLineEdit(this);
    m_userFilterFieldLayout->addWidget(m_userFilterFieldEdit, 0);
    m_userFilterFieldEdit->setObjectName("HistoryPageNS_FilterWidget_LineEdit");
    m_userFilterFieldEdit->setSizePolicy(QSizePolicy::MinimumExpanding, QSizePolicy::MinimumExpanding);
    m_userFilterFieldEdit->setPlaceholderText(tr("Adres email"));

    m_userFilterFieldValidator = new QRegularExpressionValidator(QRegularExpression(R"(^[a-zA-Z0-9._%+-]+@[a-zA-Z0-9.-]+\.[a-zA-Z]{2,}$)"), this);
    m_userFilterFieldEdit->setValidator(m_userFilterFieldValidator);

    m_locationFilterField = new QWidget(this);
    m_mainLayout->addWidget(m_locationFilterField, 0);
    m_locationFilterField->setContentsMargins(0, 0, 0, 0);

    m_locationFilterFieldLayout = new QGridLayout(m_locationFilterField);
    m_locationFilterField->setLayout(m_locationFilterFieldLayout);
    m_locationFilterFieldLayout->setContentsMargins(0, 0, 0, 0);
    m_locationFilterFieldLayout->setSpacing(5);

    m_locationFilterLabel = new QLabel(this);
    m_locationFilterFieldLayout->addWidget(m_locationFilterLabel, 0, 0, 1, 2, Qt::AlignCenter);
    m_locationFilterLabel->setObjectName("HistoryPageNS_FilterWidget_Label");
    m_locationFilterLabel->setSizePolicy(QSizePolicy::MinimumExpanding, QSizePolicy::MinimumExpanding);
    m_locationFilterLabel->setText(tr("Lokalizacja"));

    m_locationFilterRackFieldEdit = new QLineEdit(this);
    m_locationFilterFieldLayout->addWidget(m_locationFilterRackFieldEdit, 1, 0, 1, 1);
    m_locationFilterRackFieldEdit->setObjectName("HistoryPageNS_FilterWidget_LineEdit");
    m_locationFilterRackFieldEdit->setSizePolicy(QSizePolicy::MinimumExpanding, QSizePolicy::MinimumExpanding);
    m_locationFilterRackFieldEdit->setPlaceholderText(tr("Regał"));

    m_locationFilterRackFieldValidator = new QIntValidator(1, INT_MAX, this);
    m_locationFilterRackFieldEdit->setValidator(m_locationFilterRackFieldValidator);

    m_locationFilterDrawerFieldEdit = new QLineEdit(this);
    m_locationFilterFieldLayout->addWidget(m_locationFilterDrawerFieldEdit, 1, 1, 1, 1);
    m_locationFilterDrawerFieldEdit->setObjectName("HistoryPageNS_FilterWidget_LineEdit");
    m_locationFilterDrawerFieldEdit->setSizePolicy(QSizePolicy::MinimumExpanding, QSizePolicy::MinimumExpanding);
    m_locationFilterDrawerFieldEdit->setPlaceholderText(tr("Szuflada"));

    m_locationFilterDrawerFieldValidator = new QIntValidator(1, INT_MAX, this);
    m_locationFilterDrawerFieldEdit->setValidator(m_locationFilterDrawerFieldValidator);

    m_componentFilterField = new QWidget(this);
    m_mainLayout->addWidget(m_componentFilterField, 0);
    m_componentFilterField->setContentsMargins(0, 0, 0, 0);

    m_componentFilterFieldLayout = new QVBoxLayout(m_componentFilterField);
    m_componentFilterField->setLayout(m_componentFilterFieldLayout);
    m_componentFilterFieldLayout->setContentsMargins(0, 0, 0, 0);
    m_componentFilterFieldLayout->setSpacing(5);

    m_componentFilterLabel = new QLabel(this);
    m_componentFilterFieldLayout->addWidget(m_componentFilterLabel, 0, Qt::AlignCenter);
    m_componentFilterLabel->setObjectName("HistoryPageNS_FilterWidget_Label");
    m_componentFilterLabel->setSizePolicy(QSizePolicy::MinimumExpanding, QSizePolicy::MinimumExpanding);
    m_componentFilterLabel->setText(tr("ID Komponentu"));

    m_componentFilterFieldEdit = new QLineEdit(this);
    m_componentFilterFieldLayout->addWidget(m_componentFilterFieldEdit, 0);
    m_componentFilterFieldEdit->setObjectName("HistoryPageNS_FilterWidget_LineEdit");
    m_componentFilterFieldEdit->setSizePolicy(QSizePolicy::MinimumExpanding, QSizePolicy::MinimumExpanding);
    m_componentFilterFieldEdit->setPlaceholderText(tr("ID Komponentu"));

    m_componentFilterFieldValidator = new QIntValidator(1, INT_MAX, this);
    m_componentFilterFieldEdit->setValidator(m_componentFilterFieldValidator);

    m_searchButton = new QPushButton(this);
    m_mainLayout->addWidget(m_searchButton, 0);
    m_searchButton->setObjectName("HistoryPageNS_FilterWidget_Button");
    m_searchButton->setContentsMargins(0, 0, 0, 0);
    m_searchButton->setSizePolicy(QSizePolicy::MinimumExpanding, QSizePolicy::MinimumExpanding);
    m_searchButton->setText(tr("Szukaj"));

    m_emptySpace = new QWidget(this);
    m_mainLayout->addWidget(m_emptySpace, 1);

    m_locationFilterDrawerFieldEdit->setEnabled(false);

    connect(m_searchButton, &QPushButton::clicked, this, &HistoryPageNS::FilterWidget::onSearchButtonClicked);
    connect(m_dateTimeFilterMinField, &QDateEdit::dateChanged, this, &HistoryPageNS::FilterWidget::onDateTimeFilterMinFieldChanged);
    connect(m_dateTimeFilterMaxField, &QDateEdit::dateChanged, this, &HistoryPageNS::FilterWidget::onDateTimeFilterMaxFieldChanged);
    connect(m_locationFilterRackFieldEdit, &QLineEdit::textChanged, this, &HistoryPageNS::FilterWidget::onLocationFilterRackFieldEditTextChanged);
}

void HistoryPageNS::FilterWidget::onSearchButtonClicked()
{
    // QDateTime dateTimeMin(m_dateTimeFilterMinField->date(), QTime(0, 0, 0));
    // QDateTime dateTimeMax(m_dateTimeFilterMaxField->date(), QTime(23, 59, 59));
    // QString userFilter = m_userFilterFieldEdit->text();
    // QString locationFilterRack;

    QVariant sql_dateTimeMin;
    QVariant sql_dateTimeMax;
    QVariant sql_userFilter;
    QVariant sql_locationFilterRack;
    QVariant sql_locationFilterDrawer;
    QVariant sql_componentFilter;

    if (m_dateTimeFilterMinField->date().isValid())
        sql_dateTimeMin = QDateTime(m_dateTimeFilterMinField->date(), QTime(0, 0, 0));
    else
        sql_dateTimeMin = QVariant();

    if (m_dateTimeFilterMaxField->date().isValid())
        sql_dateTimeMax = QDateTime(m_dateTimeFilterMaxField->date(), QTime(23, 59, 59));
    else
        sql_dateTimeMax = QVariant();

    if (sql_dateTimeMin.isValid() && sql_dateTimeMax.isValid() && sql_dateTimeMin.toDate() > sql_dateTimeMax.toDate())
    {
        sql_dateTimeMin = QVariant();
        sql_dateTimeMax = QVariant();
        m_dateTimeFilterMinField->setDate(QDate::currentDate().addDays(-1));
        m_dateTimeFilterMaxField->setDate(QDate::currentDate());
    }

    if (m_userFilterFieldEdit->hasAcceptableInput())
        sql_userFilter = m_userFilterFieldEdit->text();
    else
        sql_userFilter = QVariant();

    if (m_locationFilterRackFieldEdit->hasAcceptableInput())
        sql_locationFilterRack = m_locationFilterRackFieldEdit->text().toInt();
    else
        sql_locationFilterRack = QVariant();

    if (m_locationFilterRackFieldEdit->hasAcceptableInput() && m_locationFilterDrawerFieldEdit->hasAcceptableInput())
        sql_locationFilterDrawer = m_locationFilterDrawerFieldEdit->text().toInt();
    else
        sql_locationFilterDrawer = QVariant();

    if (m_componentFilterFieldEdit->hasAcceptableInput())
        sql_componentFilter = m_componentFilterFieldEdit->text().toInt();
    else
        sql_componentFilter = QVariant();

    m_containerWidget->clearAll();

    bool isValid = false;
    isValid |= sql_dateTimeMin.isValid();
    isValid |= sql_dateTimeMax.isValid();
    isValid |= sql_userFilter.isValid();
    isValid |= sql_locationFilterRack.isValid();
    isValid |= sql_locationFilterDrawer.isValid();
    isValid |= sql_componentFilter.isValid();

    if (!isValid)
        return;

    QSqlQuery query;

    if (!(sql_locationFilterRack.isValid() || sql_locationFilterDrawer.isValid()))
    {
        if (!DB::Queries::Operation::SelectWhereChangeComponent(
                query,
                sql_dateTimeMin,
                sql_dateTimeMax,
                sql_userFilter,
                sql_componentFilter))
            return;
        while (query.next())
        {
            int ID = query.value(0).toInt();
            QDateTime DateTime = query.value(1).toDateTime();
            QString User_Email = query.value(2).toString();
            int Component_ID = query.value(3).toInt();
            QChar Type = query.value(4).toString().at(0);

            m_containerWidget->addOperation_ChangeComponent(ID, DateTime, User_Email, Component_ID, Type);
        }
    }

    if (!(sql_locationFilterRack.isValid() || sql_locationFilterDrawer.isValid()))
    {
        if (!DB::Queries::Operation::SelectWhereChangeQuantity(
                query,
                sql_dateTimeMin,
                sql_dateTimeMax,
                sql_userFilter,
                sql_componentFilter))
            return;

        while (query.next())
        {
            int ID = query.value(0).toInt();
            QDateTime DateTime = query.value(1).toDateTime();
            QString User_Email = query.value(2).toString();
            int Component_ID = query.value(3).toInt();
            int Delta = query.value(4).toInt();

            m_containerWidget->addOperation_ChangeQuantity(ID, DateTime, User_Email, Component_ID, Delta);
        }
    }

    if (!(sql_locationFilterDrawer.isValid() || sql_componentFilter.isValid()))
    {
        if (!DB::Queries::Operation::SelectWhereChangeRack(
                query,
                sql_dateTimeMin,
                sql_dateTimeMax,
                sql_userFilter,
                sql_locationFilterRack))
            return;
        while (query.next())
        {
            int ID = query.value(0).toInt();
            QDateTime DateTime = query.value(1).toDateTime();
            QString User_Email = query.value(2).toString();
            int RackNr = query.value(3).toInt();
            QChar Type = query.value(4).toString().at(0);

            m_containerWidget->addOperation_ChangeRack(ID, DateTime, User_Email, RackNr, Type);
        }
    }

    if (!(sql_locationFilterRack.isValid() || sql_locationFilterDrawer.isValid() || sql_componentFilter.isValid()))
    {
        if (!DB::Queries::Operation::SelectWhereChangeUser(
                query,
                sql_dateTimeMin,
                sql_dateTimeMax,
                sql_userFilter))
            return;
        while (query.next())
        {
            int ID = query.value(0).toInt();
            QDateTime DateTime = query.value(1).toDateTime();
            QString User_Email = query.value(2).toString();
            QString Mod_User_Email = query.value(3).toString();
            QChar Type = query.value(4).toString().at(0);

            m_containerWidget->addOperation_ChangeUser(ID, DateTime, User_Email, Mod_User_Email, Type);
        }
    }

    if (!DB::Queries::Operation::SelectWhereMoveComponent(
            query,
            sql_dateTimeMin,
            sql_dateTimeMax,
            sql_userFilter,
            sql_componentFilter,
            sql_locationFilterRack,
            sql_locationFilterDrawer))
        return;
    while (query.next())
    {
        int ID = query.value(0).toInt();
        QDateTime DateTime = query.value(1).toDateTime();
        QString User_Email = query.value(2).toString();
        int Component_ID = query.value(3).toInt();
        QString OldRack = query.value(4).toString();
        QString OldDrawer = query.value(5).toString();
        QString NewRack = query.value(6).toString();
        QString NewDrawer = query.value(7).toString();

        m_containerWidget->addOperation_MoveComponent(ID, DateTime, User_Email, Component_ID, OldRack, OldDrawer, NewRack, NewDrawer);
    }
}

void HistoryPageNS::FilterWidget::onDateTimeFilterMinFieldChanged(const QDate &date)
{
    m_dateTimeFilterMaxField->setMinimumDate(date);
}

void HistoryPageNS::FilterWidget::onDateTimeFilterMaxFieldChanged(const QDate &date)
{
    m_dateTimeFilterMinField->setMaximumDate(date);
}

void HistoryPageNS::FilterWidget::onLocationFilterRackFieldEditTextChanged(const QString &text)
{
    if (m_locationFilterRackFieldEdit->hasAcceptableInput())
        m_locationFilterDrawerFieldEdit->setEnabled(true);
    else
    {
        m_locationFilterDrawerFieldEdit->setEnabled(false);
        m_locationFilterDrawerFieldEdit->setText("");
    }
}

#include "historyPage/historyPage/moc_filterWidget.cpp"
// #include "historyPage/historyPage/filterWidget.moc"