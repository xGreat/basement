/*********************************************************************
 * \file   pushbutton.h
 * \brief  
 * 
 * \author heqingrui
 * \date   March 2024
 *********************************************************************/
#ifndef QRCODE_PUSHBUTTON_H
#define QRCODE_PUSHBUTTON_H

#include <QPushButton>
#include <QIcon>

namespace QRCode {

class PushButton : public QPushButton
{
    Q_OBJECT

public:
    PushButton(QWidget *parent = nullptr);
    ~PushButton();

    void setIcon(const QIcon &icon);
    void setHoverIcon(const QIcon &icon);

protected:
    void enterEvent(QEvent *event) override;
    void leaveEvent(QEvent *event) override;

private:
    QIcon m_hoverIcon;
    QIcon m_normalIcon;
};

}

#endif // QRCODE_PUSHBUTTON_H
