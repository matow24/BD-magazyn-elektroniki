#ifndef _FIRST2COLUMNSLOCKEDTABLEVIEW_HPP
#define _FIRST2COLUMNSLOCKEDTABLEVIEW_HPP

#include <QSqlTableModel>

class First2ColumnsLockedTableModel : public QSqlTableModel {
public:
    using QSqlTableModel::QSqlTableModel; // inherit constructors

    Qt::ItemFlags flags(const QModelIndex &index) const override {
        Qt::ItemFlags defaultFlags = QSqlTableModel::flags(index);

        if (!index.isValid())
            return Qt::NoItemFlags;

        // Make first 2 columns non-editable
        if (index.column() < 2)
            return defaultFlags & ~Qt::ItemIsEditable;

        return defaultFlags; // editable otherwise
    }
};

#endif