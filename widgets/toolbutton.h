/*********************************************************************
 * \file   toolbutton.h
 * \brief  
 * 
 * \author heqingrui
 * \date   March 2024
 *********************************************************************/
#ifndef QRCODE_TOOLBUTTON_H
#define QRCODE_TOOLBUTTON_H

#include <QToolButton>
#include <QIcon>

namespace QRCode {

class ToolButton : public QToolButton
{
    Q_OBJECT

public:
    ToolButton(QWidget *parent = nullptr);
    ~ToolButton();

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

#endif // QRCODE_TOOLBUTTON_H
