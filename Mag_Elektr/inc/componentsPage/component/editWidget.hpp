#ifndef _COMPONENTWIDGET_EDIT_WIDGET_HPP
#define _COMPONENTWIDGET_EDIT_WIDGET_HPP

#include <QPushButton>
#include <QWidget>
#include <QVBoxLayout>

#include <main.hpp>

namespace ComponentNS
{
    enum EditButton
    {
        STATISTICS,
        EDIT,
        DELETE
    };

    class EditWidget : public QWidget
    {
        Q_OBJECT
    private:
        QVBoxLayout *m_mainLayout = nullptr;

        QPushButton *m_statisticsButton = nullptr;
        QPushButton *m_editButton = nullptr;
        QPushButton *m_deleteButton = nullptr;

    public:
        EditWidget(QWidget *parent = nullptr);

    signals:
        void deleteComponent();
        void statisticsComponent();

    private slots:
        void deleteButtonClicked();
        void statisticsButtonClicked();
    };
} // namespace ComponentNS

#endif // _COMPONENTWIDGET_EDIT_WIDGET_HPP