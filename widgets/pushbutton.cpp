#include "pushbutton.h"

namespace QRCode {

PushButton::PushButton(QWidget *parent)
    : QPushButton(parent)
{
    this->setAttribute(Qt::WA_Hover, true);
}

PushButton::~PushButton()
{
}

void PushButton::setIcon(const QIcon &icon)
{
    m_normalIcon = icon;

    QPushButton::setIcon(icon);
}

void PushButton::setHoverIcon(const QIcon &icon)
{
    m_hoverIcon = icon;
}

void PushButton::enterEvent(QEvent *event)
{
    QPushButton::setIcon(m_hoverIcon);
}

void PushButton::leaveEvent(QEvent *event)
{
    QPushButton::setIcon(m_normalIcon);
}

}
