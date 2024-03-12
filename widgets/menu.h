/*********************************************************************
 * \file   menu.h
 * \brief  
 * 
 * \author heqingrui
 * \date   March 2024
 *********************************************************************/
#ifndef QRCODE_MENU_H
#define QRCODE_MENU_H

#include <QMenu>

namespace QRCode {

class Menu : public QMenu
{
    Q_OBJECT

public:
    Menu(QWidget *parent = nullptr);
    explicit Menu(const QString &title, QWidget *parent = nullptr);
    ~Menu();
};

}

#endif // QRCODE_MENU_H
