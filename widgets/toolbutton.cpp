#include "toolbutton.h"

namespace QRCode {

ToolButton::ToolButton(QWidget *parent)
    : QToolButton(parent)
{
    this->setAttribute(Qt::WA_Hover, true);
}

ToolButton::~ToolButton()
{
}

void ToolButton::setIcon(const QIcon &icon)
{
    m_normalIcon = icon;

    QToolButton::setIcon(icon);
}

void ToolButton::setHoverIcon(const QIcon &icon)
{
    m_hoverIcon = icon;
}

void ToolButton::enterEvent(QEvent *event)
{
    QToolButton::setIcon(m_hoverIcon);
}

void ToolButton::leaveEvent(QEvent *event)
{
    QToolButton::setIcon(m_normalIcon);
}

} // namespace QRCode