#include "componentsPage/filterTypeSpace.hpp"

FilterTypeSpace::FilterTypeSpace(UserRole userRole, QWidget *parent) : QWidget(parent)
{
    m_userRole = userRole;

    this->setStyleSheet(MainStyle::StyleSheets[STYLE_COMPONENTSPAGE_NAME]);
}

#include "componentsPage/moc_filterTypeSpace.cpp"
// #include "componentsPage/filterTypeSpace.moc"