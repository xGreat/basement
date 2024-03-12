/*********************************************************************
 * \file   flowlayout.h
 * \brief  
 * 
 * \author heqingrui
 * \date   March 2024
 *********************************************************************/
#ifndef QRCODE_FLOWLAYOUT_H
#define QRCODE_FLOWLAYOUT_H

#include <QLayout>
#include <QRect>
#include <QStyle>

namespace QRCode {

class FlowLayout : public QLayout
{
public:
    explicit FlowLayout(QWidget *parent, int margin = -1, int hSpacing = -1, int vSpacing = -1);
    explicit FlowLayout(QWidget *parent, int margin_left, int margin_top, int margin_right, int margin_bottom, int hSpacing = -1, int vSpacing = -1);
    explicit FlowLayout(int margin = -1, int hSpacing = -1, int vSpacing = -1);
    ~FlowLayout();

    void addItem(QLayoutItem *item) override;
    int horizontalSpacing() const;
    int verticalSpacing() const;
    Qt::Orientations expandingDirections() const override;
    bool hasHeightForWidth() const override;
    int heightForWidth(int) const override;
    int count() const override;
    QLayoutItem *itemAt(int index) const override;
    QSize minimumSize() const override;
    void setGeometry(const QRect &rect) override;
    QSize sizeHint() const override;
    QLayoutItem *takeAt(int index) override;
    QList<QWidget *> allWidgets();

private:
    int doLayout(const QRect &rect, bool testOnly) const;
    int smartSpacing(QStyle::PixelMetric pm) const;

    QList<QLayoutItem *> itemList;
    int m_hSpace;
    int m_vSpace;
};


}


#endif // QRCODE_FLOWLAYOUT_H
