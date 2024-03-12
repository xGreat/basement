#include "menu.h"

namespace QRCode {

Menu::Menu(QWidget *parent)
    : QMenu(parent)
{
    setFixedWidth(130);
    setWindowFlags(windowFlags() | Qt::FramelessWindowHint | Qt::NoDropShadowWindowHint);
    setAttribute(Qt::WA_TranslucentBackground);
}

Menu::Menu(const QString &title, QWidget *parent)
    : QMenu(title, parent)
{
    setFixedWidth(130);
    setWindowFlags(windowFlags() | Qt::FramelessWindowHint | Qt::NoDropShadowWindowHint);
    setAttribute(Qt::WA_TranslucentBackground);
}

Menu::~Menu()
{
}

} // namespace QRCode