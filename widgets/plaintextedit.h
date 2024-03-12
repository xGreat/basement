/*********************************************************************
 * \file   plaintextedit.h
 * \brief  
 * 
 * \author heqingrui
 * \date   March 2024
 *********************************************************************/
#ifndef QRCODE_PLAINTEXTEDIT_H
#define QRCODE_PLAINTEXTEDIT_H

#include <QPlainTextEdit>

class QLabel;

namespace QRCode {

class PlainTextEdit : public QPlainTextEdit
{
    Q_OBJECT

public:
    PlainTextEdit(QWidget *parent = nullptr);
    ~PlainTextEdit();

    void setMaxLength(int length);

protected:
    void resizeEvent(QResizeEvent *event) override;

private:
    QLabel *m_indicator;
    int m_maxLength;
};

}

#endif // QRCODE_PLAINTEXTEDIT_H
