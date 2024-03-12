/*********************************************************************
 * \file   combobox.h
 * \brief  
 * 
 * \author heqingrui
 * \date   March 2024
 *********************************************************************/
#ifndef QRCODE_COMBOBOX_H
#define QRCODE_COMBOBOX_H

#include <QComboBox>

namespace QRCode {

class ComboBox : public QComboBox
{
    Q_OBJECT

public:
    ComboBox(QWidget *parent = 0);
    ~ComboBox();

protected:
    virtual void wheelEvent(QWheelEvent *e) Q_DECL_OVERRIDE;
    virtual void keyPressEvent(QKeyEvent *e) Q_DECL_OVERRIDE;
    virtual void paintEvent(QPaintEvent *e) Q_DECL_OVERRIDE;

private:
};

}

#endif // QRCODE_COMBOBOX_H
