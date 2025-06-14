#include "modifyPage/addComponentDialog.hpp"

AddComponentDialog::AddComponentDialog(QWidget *parent) : QDialog(parent)
{
    setWindowTitle(tr("Add New User"));
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

    variantTypeEdit->setEnabled(false); // Start disabled

    formLayout->addRow(tr("Wariant:"),          variantNameEdit);
    formLayout->addRow(tr("Rodzaj:"),           variantTypeEdit);
    formLayout->addRow(tr("Nazwa:"),            nameEdit);
    formLayout->addRow(tr("Producent:"),        manufacturerEdit);
    formLayout->addRow(tr("Symbol:"),           symbolEdit);
    formLayout->addRow(tr("Dane techniczne:"),  datasheetEdit);
    formLayout->addRow(tr("Maksymalna liczba elmentów w szufladzie:"), maxQuantityEdit);

    mainLayout->addLayout(formLayout);

    addButton = new QPushButton(tr("Dodaj komponent"));
    addButton->setEnabled(false); // Start disabled
    mainLayout->addWidget(addButton, 0, Qt::AlignRight);

    addVariantNameButton = new QPushButton(tr("Dodaj wariant"));
    mainLayout->addWidget(addVariantNameButton, 0, Qt::AlignRight);

    addVariantTypeButton = new QPushButton(tr("Dodaj rodzaj"));
    addVariantTypeButton->setEnabled(false); // Start disabled
    mainLayout->addWidget(addVariantTypeButton, 0, Qt::AlignRight);

    connect(variantNameEdit, &QComboBox::currentTextChanged, this, &AddComponentDialog::onVariantNameChanged);
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
    if (name == "Add new variant") {
        addVariantTypeButton->setEnabled(true);
        variantTypeEdit->setEnabled(true);
        variantTypeEdit->clear();
        return;
    }

    QSqlQuery query;
    query.prepare("SELECT Type FROM Variant WHERE Name = :name");
    query.bindValue(":name", name);
    if (query.exec() && query.next()) {
        variantTypeEdit->clear();
        variantTypeEdit->addItem(query.value(0).toString());
    }
}

void AddComponentDialog::onAddVariantNameClicked() {
    QString newVariant = QInputDialog::getText(this, "New Variant", "Enter variant name:");
    if (newVariant.isEmpty()) return;

    if (variantNameEdit->findText(newVariant) == -1) {
        variantNameEdit->addItem(newVariant);
    }
    variantNameEdit->setCurrentText(newVariant);
    addVariantTypeButton->setEnabled(true);
    variantTypeEdit->setEnabled(true);
}

void AddComponentDialog::onAddVariantTypeClicked() {
    QString newType = QInputDialog::getText(this, "New Type", "Enter variant type:");
    if (newType.isEmpty()) return;

    if (variantTypeEdit->findText(newType) == -1) {
        variantTypeEdit->addItem(newType);
    }
    variantTypeEdit->setCurrentText(newType);
}

void AddComponentDialog::setup_variantNameEdit() {
    QSqlQuery query;
    query.prepare("SELECT Name FROM Variant");
    while(query.next()){
        variantNameEdit->addItem(query.value(0).toString());
    }
    variantNameEdit->addItem("Add new variant");
}

void AddComponentDialog::setup_variantTypeEdit() {
    QSqlQuery query;
    query.prepare("SELECT Type FROM Variant GROUP BY Type");
    while(query.next()){
        variantTypeEdit->addItem(query.value(0).toString());
    }
    variantTypeEdit->addItem("Dodaj nowy rodzaj");
}

void AddComponentDialog::validateForm()
{
    bool filled = !variantNameEdit->currentText().isEmpty() &&
                  !variantTypeEdit->currentText().isEmpty() &&
                  !nameEdit->text().isEmpty() &&
                  !manufacturerEdit->text().isEmpty() &&
                  !symbolEdit->text().isEmpty() &&
                  !datasheetEdit->text().isEmpty() &&
                  !maxQuantityEdit->text().isEmpty();

    addButton->setEnabled(filled);

}

bool AddComponentDialog::areNameAndSymbolUnique()
{
    QString symbol = symbolEdit->text().trimmed();
    QString name = nameEdit->text().trimmed();
    QSqlQuery query;
    query.prepare("SELECT COUNT(*) FROM Component WHERE Symbol = :symbol OR Name = :name");
    query.bindValue(":symbol", symbol);
    query.bindValue(":name", name);
    if (query.exec() && query.next()) {
        return query.value(0).toInt() == 0;
    }
    return false;
}

void AddComponentDialog::onAddClicked()
{
    // Check for unique name and symbol
    if(!areNameAndSymbolUnique()){
        QMessageBox::critical(this, tr("Błędna nazwa lub symbol"), tr("Komponent o tej nazwie lub symbolu już istnieje w bazie."));
        return;
    }

    // Confirm dialog
    QMessageBox::StandardButton reply = QMessageBox::question(
        this,
        tr("Zatwierdź"),
        tr("Czy potwierdzasz dane nowego komponentu?"),
        QMessageBox::Yes | QMessageBox::No,
        QMessageBox::No
    );

    if (reply == QMessageBox::No)
        return;

    QString variantName = variantNameEdit->currentText();
    QString variantType = variantTypeEdit->currentText();
    QString name = nameEdit->text();
    QString symbol = symbolEdit->text();
    QString manufacturer = manufacturerEdit->text();
    QString datasheet = datasheetEdit->text();
    uint maxQty = maxQuantityEdit->text().toUInt();

    // Check for duplicates
    QSqlQuery check;
    check.prepare("SELECT COUNT(*) FROM Component WHERE Name = :name OR Symbol = :symbol");
    check.bindValue(":name", name);
    check.bindValue(":symbol", symbol);
    if (!check.exec() || (check.next() && check.value(0).toInt() > 0)) {
        QMessageBox::warning(this, "Duplicate", "Name or Symbol already exists.");
        return;
    }
    
    // Insert variant if not present
    QSqlQuery variantInsert;
    variantInsert.prepare("INSERT OR IGNORE INTO Variant (Name, Type) VALUES (:name, :type)");
    variantInsert.bindValue(":name", variantName);
    variantInsert.bindValue(":type", variantType);

    // Insert component   
    QSqlQuery insert;
    insert.prepare(R"(
        INSERT INTO Component (Variant_Name, Name, Manufacturer, Symbol, Datasheet, MaxQuantity)
        VALUES (:variant, :name, :manuf, :symbol, :sheet, :max)
    )");
    insert.bindValue(":variant", variantName);
    insert.bindValue(":name", name);
    insert.bindValue(":manuf", manufacturer);
    insert.bindValue(":symbol", symbol);
    insert.bindValue(":sheet", datasheet);
    insert.bindValue(":max", maxQty);

    if (!insert.exec()) {
        QMessageBox::critical(this, "Insert Failed", insert.lastError().text());
    } else {
        QMessageBox::information(this, "Success", tr("Component added."));
        accept();
    }
}

#include "modifyPage/moc_addComponentDialog.cpp"
// #include "modifyPage/addComponentDialog.moc"
