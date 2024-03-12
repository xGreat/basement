#include "basepopup.h"

namespace QRCode {

BasePopup::BasePopup(QWidget *parent)
    : QFrame(parent)
{
    // Qt::Popup is not suit
    this->setWindowFlags(Qt::Tool | Qt::FramelessWindowHint /* | Qt::NoDropShadowWindowHint*/);
    this->setAttribute(Qt::WA_TranslucentBackground);
    this->setAttribute(Qt::WA_Hover);
    this->setAutoFillBackground(true);
    this->setMouseTracking(true);
    this->setFrameStyle(QFrame::NoFrame);
}

BasePopup::~BasePopup()
{
}

void BasePopup::popup()
{
    this->show();
    this->activateWindow();
    this->setFocus(Qt::PopupFocusReason);
}

bool BasePopup::event(QEvent *event)
{
    switch (event->type()) {
    case QEvent::HoverEnter:
        hoverEnter(static_cast<QHoverEvent *>(event));
        return true;
        break;
    case QEvent::HoverLeave:
        hoverLeave(static_cast<QHoverEvent *>(event));
        return true;
        break;
    case QEvent::HoverMove:
        hoverMove(static_cast<QHoverEvent *>(event));
        return true;
        break;
    default:
        break;
    }
    return QFrame::event(event);
}

void BasePopup::hoverEnter(QEvent *event)
{
}

void BasePopup::hoverLeave(QEvent *event)
{
    this->hide();
    QFrame::leaveEvent(event);
}

void BasePopup::hoverMove(QEvent *event)
{
}

void BasePopup::showEvent(QShowEvent *event)
{
    emit showSignal();
    QFrame::showEvent(event);
}

void BasePopup::hideEvent(QHideEvent *event)
{
    emit hideSignal();
    QFrame::hideEvent(event);
}

} // namespace QRCode