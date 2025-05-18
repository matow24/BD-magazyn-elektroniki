#include "componentsPage/displayComponentsSpace.hpp"

DisplayComponentsSpace::DisplayComponentsSpace(UserRole userRole, QWidget *parent)
{
    m_userRole = userRole;

    this->setStyleSheet(MainStyle::StyleSheets[STYLE_COMPONENTSPAGE_NAME]);
}

#include "componentsPage/moc_displayComponentsSpace.cpp"
// #include "componentsPage/displayComponentsSpace.moc"