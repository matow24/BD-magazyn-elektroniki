#ifndef _ADDCOMPONENTDIALOG_HPP
#define _ADDCOMPONENTDIALOG_HPP

#include <QDialog>
#include <QVBoxLayout>
#include <QFormLayout>
#include <QLineEdit>
#include <QComboBox>
#include <QInputDialog>
#include <QPushButton>
#include <QMessageBox>
#include <QSqlQuery>
#include <QSqlError>
#include <QDebug>

#include "main.hpp"

class AddComponentDialog : public QDialog
{
    Q_OBJECT

public:
    explicit AddComponentDialog(QWidget *parent = nullptr);

private slots:
    void validateForm();
    void onAddClicked();
    void onVariantNameChanged(const QString &name);
    void onRegalNumberChanged(const QString &name);
    void onAddVariantNameClicked();
    void onAddVariantTypeClicked();

private:
    QComboBox *variantTypeEdit;
    QComboBox *variantNameEdit;
    QLineEdit *nameEdit;
    QLineEdit *manufacturerEdit;
    QLineEdit *symbolEdit;
    QLineEdit *datasheetEdit;
    QLineEdit *maxQuantityEdit;
    QComboBox *regalEdit;
    QComboBox *szufladaEdit;
    QPushButton *addButton;
    QPushButton *addVariantNameButton;
    QPushButton *addVariantTypeButton;

    bool areNameAndSymbolUnique();
    void setup_variantNameEdit();
    void setup_variantTypeEdit();
    void setup_RegalSzufladaEdit();
};

#endif