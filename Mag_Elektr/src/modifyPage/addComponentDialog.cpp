#include "modifyPage/addComponentDialog.hpp"

AddComponentDialog::AddComponentDialog(QWidget *parent) : QDialog(parent)
{
    setWindowTitle(tr("Dodaj nowy komponent"));
    this->setStyleSheet(MainStyle::StyleSheets[STYLE_MODIFYPAGE_NAME]);

    QVBoxLayout *mainLayout = new QVBoxLayout(this);
    QFormLayout *formLayout = new QFormLayout();

    variantNameEdit = new QComboBox();
    variantTypeEdit = new QComboBox();
    setup_variantNameEdit();
    setup_variantTypeEdit();

    nameEdit        = new QLineEdit();
    symbolEdit      = new QLineEdit();
    manufacturerEdit = new QLineEdit();
    datasheetEdit   = new QLineEdit();
    maxQuantityEdit = new QLineEdit();
    regalEdit       = new QComboBox();
    szufladaEdit    = new QComboBox();
    setup_RegalSzufladaEdit();

    formLayout->addRow(tr("Wariant:"),          variantNameEdit);
    formLayout->addRow(tr("Rodzaj:"),           variantTypeEdit);
    formLayout->addRow(tr("Nazwa:"),            nameEdit);
    formLayout->addRow(tr("Producent:"),        manufacturerEdit);
    formLayout->addRow(tr("Symbol:"),           symbolEdit);
    formLayout->addRow(tr("Dane techniczne:"),  datasheetEdit);
    formLayout->addRow(tr("Maksymalna liczba elmentów w szufladzie:"), maxQuantityEdit);
    formLayout->addRow(tr("Numer regału:"),     regalEdit);
    formLayout->addRow(tr("Numer szuflady:"),   szufladaEdit);

    mainLayout->addLayout(formLayout);

    addButton = new QPushButton(tr("Dodaj komponent"));
    addButton->setEnabled(false); // Start disabled
    mainLayout->addWidget(addButton, 0, Qt::AlignRight);

    addVariantNameButton = new QPushButton(tr("Dodaj wariant"));
    mainLayout->addWidget(addVariantNameButton, 0, Qt::AlignRight);

    addVariantTypeButton = new QPushButton(tr("Dodaj rodzaj"));
    mainLayout->addWidget(addVariantTypeButton, 0, Qt::AlignRight);

    connect(variantNameEdit, &QComboBox::currentTextChanged, this, &AddComponentDialog::onVariantNameChanged);
    connect(regalEdit, &QComboBox::currentTextChanged, this, &AddComponentDialog::onRegalNumberChanged);
    connect(addVariantNameButton, &QPushButton::clicked, this, &AddComponentDialog::onAddVariantNameClicked);
    connect(addVariantTypeButton, &QPushButton::clicked, this, &AddComponentDialog::onAddVariantTypeClicked);
    connect(addButton, &QPushButton::clicked, this, &AddComponentDialog::onAddClicked);

    // Validate form inputs
    auto validateFields = [this]() { validateForm(); };
    for (auto *edit : { nameEdit, symbolEdit, manufacturerEdit, datasheetEdit, maxQuantityEdit }) {
        connect(edit, &QLineEdit::textChanged, this, validateFields);
    }
    connect(variantTypeEdit, &QComboBox::currentTextChanged, this, validateFields);
}

void AddComponentDialog::onVariantNameChanged(const QString &name) {
    QSqlQuery query;
    DB::Attrb::Variant::Name vname(name);
    if(DB::Queries::Variant::GetTypeByName(query, vname)){
        if (query.next()) {
            variantTypeEdit->clear();
            variantTypeEdit->addItem(query.value(0).toString());
        }
    }
}

void AddComponentDialog::onRegalNumberChanged(const QString &regal) {
    szufladaEdit->clear();

    QSqlQuery query;
    DB::Attrb::Location::Rack lrack(regal.toInt());
    if(DB::Queries::Location::GetEmptyDrawersInRack(query, lrack)){
        while (query.next()) {
            szufladaEdit->addItem(query.value(0).toString());
        }
    }
}

void AddComponentDialog::onAddVariantNameClicked() {
    QString newVariant = QInputDialog::getText(this, tr("Nowy wariant"), tr("Podaj nowy wariant:"));
    if (newVariant.isEmpty()) return;

    if (variantNameEdit->findText(newVariant) == -1) {
        variantNameEdit->addItem(newVariant);
    }
    variantNameEdit->setCurrentText(newVariant);
    addVariantTypeButton->setEnabled(true);
    variantTypeEdit->setEnabled(true);
}

void AddComponentDialog::onAddVariantTypeClicked() {
    QString newType = QInputDialog::getText(this, tr("Nowy rodzaj"), tr("Podaj nowy rodzaj:"));
    if (newType.isEmpty()) return;

    if (variantTypeEdit->findText(newType) == -1) {
        variantTypeEdit->addItem(newType);
    }
    variantTypeEdit->setCurrentText(newType);
}

void AddComponentDialog::setup_variantNameEdit() {
    QSqlQuery query;
    if(DB::Queries::Variant::GetVariantNames(query)){
        while(query.next()){
            variantNameEdit->addItem(query.value(0).toString());
        }
    }
}

void AddComponentDialog::setup_variantTypeEdit() {
    variantTypeEdit->clear();
    variantTypeEdit->setEnabled(false);

    QSqlQuery query;
    if(DB::Queries::Variant::GetVariantTypes(query)){
        while(query.next()){
            variantTypeEdit->addItem(query.value(0).toString());
        }
    }
}

void AddComponentDialog::setup_RegalSzufladaEdit() {
    regalEdit->clear();
    szufladaEdit->clear();

    QSqlQuery query;
    if(DB::Queries::Location::GetEmptyDrawers(query)){
        while(query.next()){
            regalEdit->addItem(query.value(0).toString());
        }
    }
    onRegalNumberChanged(regalEdit->currentText());
}

void AddComponentDialog::validateForm()
{
    bool filled = !variantNameEdit->currentText().isEmpty() &&
                  !variantTypeEdit->currentText().isEmpty() &&
                  !nameEdit->text().isEmpty() &&
                  !manufacturerEdit->text().isEmpty() &&
                  !symbolEdit->text().isEmpty() &&
                  !datasheetEdit->text().isEmpty() &&
                  !maxQuantityEdit->text().isEmpty();// &&
                  !regalEdit->currentText().isEmpty() &&
                  !szufladaEdit->currentText().isEmpty();

    addButton->setEnabled(filled);

}

bool AddComponentDialog::areNameAndSymbolUnique()
{
    QSqlQuery query;
    DB::Attrb::Component::Name name(nameEdit->text().trimmed());
    DB::Attrb::Component::Symbol symbol(symbolEdit->text().trimmed());
    if(DB::Queries::Component::CountNameSymbol(query, name, symbol)){
        if(query.next()) 
            return query.value(0).toInt() == 0;
    }
    return false; 
}

bool AddComponentDialog::updateLocation(int newestID)
{
    QSqlQuery updateLocation;
    DB::Attrb::Location::Drawer Drawer(szufladaEdit->currentText().toInt());
    DB::Attrb::Location::Rack Rack(regalEdit->currentText().toInt());
    DB::Attrb::Location::Component_ID new_Component_ID(newestID);
    if(!DB::Queries::Location::UpdateSetComponentID(updateLocation, new_Component_ID, Rack, Drawer)) {
        QMessageBox::warning(this, tr("Nie pykło"), tr("Nie udało się przyporządkować komponentu do szuflady."));
        return 1;
    }
    return 0;
}

// Insert variant, if not present, and component 
bool AddComponentDialog::addVariant_Component()
{
    QString variantName = variantNameEdit->currentText();
    QString variantType = variantTypeEdit->currentText();
    QString name = nameEdit->text();
    QString symbol = symbolEdit->text();
    QString manufacturer = manufacturerEdit->text();
    QString datasheet = datasheetEdit->text();
    uint maxQty = maxQuantityEdit->text().toUInt();

    QSqlQuery variantInsert;
    DB::Attrb::Variant::Name Variant_Name(variantName);
    DB::Attrb::Variant::Type vType(variantType);
    if(!DB::Queries::Variant::Add(variantInsert, Variant_Name, vType)){
        QMessageBox::warning(this, tr("Nie pykło"), tr("Nie udało się dodać nowego wariantu komponentu."));
        return 1;
    }
    QSqlQuery insert;
    DB::Attrb::Component::Name Name(name);
    DB::Attrb::Component::Manufacturer Manufacturer(manufacturer);
    DB::Attrb::Component::Symbol Symbol(symbol);
    DB::Attrb::Component::Datasheet Datasheet(datasheet);
    DB::Attrb::Component::MaxQuantity MaxQuantity(maxQty);
    if(!DB::Queries::Component::Add(insert, Variant_Name, Name, Manufacturer, Symbol, Datasheet, MaxQuantity)){
        QMessageBox::warning(this, tr("Nie pykło"), tr("Nie udało się dodać komponentu."));
        return 1;
    } 

    return 0;
}

void AddComponentDialog::onAddClicked()
{
    // Check for unique name and symbol
    if(!areNameAndSymbolUnique()){
        QMessageBox::critical(this, tr("Błędna nazwa lub symbol"), tr("Komponent o tej nazwie lub symbolu już istnieje w bazie."));
        return;
    }
    
    // Insert variant, if not present, and component 
    if(addVariant_Component()) return;

    // Add operation in history
    QSqlQuery insertOperation;
    DB::Attrb::Operation::User_Email User_Email(g_userEmail);
    if(!DB::Queries::Operation::InsertOperation(insertOperation, User_Email)) {
        QMessageBox::warning(this, tr("Nie pykło"), tr("Nie udało się dodać operacji."));
        return;
    }

    // Get IDs of Component and Operation
    QSqlQuery newestoperationIDquery;
    if(!DB::Queries::Operation::GetNewestID(newestoperationIDquery)){
        QMessageBox::warning(this, tr("Nie pykło"), tr("Nie udało się odczytać ID operacji."));
        return;
    }
    QSqlQuery newestIDquery;
    if(!DB::Queries::Component::GetNewestID(newestIDquery)){
        QMessageBox::warning(this, tr("Nie pykło"), tr("Nie udało się odczytać ID komponentu."));
        return;
    }

    if(newestIDquery.next()) {
        // Update location
       if(updateLocation(newestIDquery.value(0).toInt())) return;

       if(newestoperationIDquery.next()) 
       {
            // Add ChangeComponent operation
            QSqlQuery insertChangeComponentOperation;
            DB::Attrb::Operation_ChangeComponent::Operation_ID Operation_ID(newestoperationIDquery.value(0).toInt());
            DB::Attrb::Operation_ChangeComponent::Component_ID Component_ID(newestIDquery.value(0).toInt());
            if(!DB::Queries::Operation::InsertChangeComponent(insertChangeComponentOperation, Operation_ID, Component_ID, DB::Attrb::OperationType::Add)) {
                QMessageBox::warning(this, tr("Nie pykło"), tr("Nie udało się dodać operacji zmiany komponentu."));
                return;
            }

            // Add MoveComponent operation
            QSqlQuery insertMoveComponentOperation;
            DB::Attrb::Operation_MoveComponent::Operation_ID MoveOperation_ID(newestoperationIDquery.value(0).toInt());
            DB::Attrb::Operation_MoveComponent::Component_ID MoveComponent_ID(newestIDquery.value(0).toInt());
            DB::Attrb::Operation_MoveComponent::New_Location_Rack New_Location_Rack(regalEdit->currentText().toInt());
            DB::Attrb::Operation_MoveComponent::New_Location_Drawer New_Location_Drawer(szufladaEdit->currentText().toInt());
            if(!DB::Queries::Operation::InsertMoveComponentAdd(insertChangeComponentOperation, MoveOperation_ID, MoveComponent_ID, New_Location_Rack, New_Location_Drawer)) {
                QMessageBox::warning(this, tr("Nie pykło"), tr("Nie udało się dodać operacji przeniesienia komponentu."));
                return;
            }
        }
    }
    


    
    


    accept();

}

#include "modifyPage/moc_addComponentDialog.cpp"
// #include "modifyPage/addComponentDialog.moc"
