/*********************************************************************
 * \file   notification.h
 * \brief  
 * 
 * \author heqingrui
 * \date   March 2024
 *********************************************************************/
#ifndef QRCODE_NOTIFICATION_H
#define QRCODE_NOTIFICATION_H

#include <QWidget>
#include <QPropertyAnimation>

class QDesktopWidget;

namespace QRCode {

class Notification : public QWidget
{
    Q_OBJECT

public:
    Notification(QWidget *parent = 0, bool autoClose = false);
    ~Notification();

public slots:
    void showAnimation();
    void stopAnimation();
    void clear();

public:
    QDesktopWidget *m_desktop;

private:
    QPropertyAnimation *m_animation;
    bool m_autoClose;
    QTimer *m_remainTimer;
};

}

#endif // NOTIFICATION_H
