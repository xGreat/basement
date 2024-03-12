/*********************************************************************
 * \file   clickablelabel .h
 * \brief  
 * 
 * \author heqingrui
 * \date   March 2024
 *********************************************************************/
#ifndef QRCODE_CLICKABLELABEL_H
#define QRCODE_CLICKABLELABEL_H

#include <QLabel>
#include <QWidget>
#include <Qt>

namespace QRCode {

class ClickableLabel : public QLabel
{
    Q_OBJECT

public:
    explicit ClickableLabel(QWidget *parent = Q_NULLPTR, Qt::WindowFlags f = Qt::WindowFlags());
    ~ClickableLabel();

signals:
    void clicked();

protected:
    void mousePressEvent(QMouseEvent *event);
};

}

#endif // QRCODE_CLICKABLELABEL_H
