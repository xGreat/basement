/*********************************************************************
 * \file   elidedlabel.h
 * \brief  
 * 
 * \author heqingrui
 * \date   March 2024
 *********************************************************************/
#ifndef QRCODE_ELIDEDLABEL_H
#define QRCODE_ELIDEDLABEL_H

#include <QLabel>
#include <QString>

namespace QRCode {

class ElidedLabel : public QLabel
{
    Q_OBJECT
    Q_PROPERTY(QString text READ text WRITE setText)
    Q_PROPERTY(bool isElided READ isElided)

public:
    explicit ElidedLabel(QWidget *parent = 0);
    explicit ElidedLabel(const QString &text, QWidget *parent = nullptr);

    void setText(const QString &text);
    const QString &text() const { return content; }
    bool isElided() const { return elided; }

protected:
    void paintEvent(QPaintEvent *event) override;

signals:
    void elisionChanged(bool elided);

private:
    bool elided;
    QString content;
};

}

#endif // QRCODE_ELIDEDLABEL_H
