#include "clickablelabel.h"

namespace QRCode {

ClickableLabel::ClickableLabel(QWidget *parent, Qt::WindowFlags f)
    : QLabel(parent)
{
}

ClickableLabel::~ClickableLabel() {}

void ClickableLabel::mousePressEvent(QMouseEvent *event)
{
    emit clicked();
}

}
