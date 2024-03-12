/*********************************************************************
 * \file   basepopup.h
 * \brief  
 * 
 * \author heqingrui
 * \date   March 2024
 *********************************************************************/
#ifndef QRCODE_BASEPOPUP_H
#define QRCODE_BASEPOPUP_H
#include <QFrame>
#include <QShowEvent>
#include <QFocusEvent>

namespace QRCode {

class BasePopup : public QFrame
{
    Q_OBJECT
public:
    explicit BasePopup(QWidget *parent = nullptr);
    ~BasePopup();

    void popup();
signals:
    void showSignal();
    void hideSignal();

protected:
    virtual bool event(QEvent *event);
    virtual void showEvent(QShowEvent *event);
    virtual void hideEvent(QHideEvent *event);
    void hoverEnter(QEvent *event);
    void hoverLeave(QEvent *event);
    void hoverMove(QEvent *event);
};

}

#endif // QRCODE_BASEPOPUP_H
