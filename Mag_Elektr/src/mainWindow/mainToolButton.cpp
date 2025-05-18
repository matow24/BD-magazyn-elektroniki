#include "mainWindow/mainToolButton.hpp"

MainToolButton::MainToolButton(QWidget *parent) : QToolButton(parent)
{
    this->setStyleSheet(MainStyle::StyleSheets[STYLE_MAINWINDOW_NAME]);
    this->setToolButtonStyle(Qt::ToolButtonTextOnly);
    this->setSizePolicy(QSizePolicy::MinimumExpanding, QSizePolicy::Minimum);
    this->setCheckable(true);
    this->setChecked(false);
}

#include "mainWindow/moc_mainToolButton.cpp"
// #include "mainWindow/mainToolButton.moc"