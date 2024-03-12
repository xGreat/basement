#include "combobox.h"
#include <QStylePainter>
#include <QListView>
#include <QWheelEvent>

namespace QRCode {

ComboBox::ComboBox(QWidget *parent)
    : QComboBox(parent)
{
    this->setView(new QListView());
    this->setFocusPolicy(Qt::StrongFocus);

    QWidget *container = static_cast<QWidget *>(this->view()->parent()); // QComboBoxPrivateContainer
    container->setWindowFlag(Qt::NoDropShadowWindowHint);

    this->view()->window()->setWindowFlags(Qt::Popup | Qt::FramelessWindowHint | Qt::NoDropShadowWindowHint);
    this->view()->window()->setAttribute(Qt::WA_TranslucentBackground);
}

ComboBox::~ComboBox()
{
}

void ComboBox::wheelEvent(QWheelEvent *e)
{
    e->ignore();
    return;

    if (hasFocus())
        QComboBox::wheelEvent(e);
    else
        e->ignore();
}

void ComboBox::keyPressEvent(QKeyEvent *e)
{
    if (hasFocus())
        QComboBox::keyPressEvent(e);
}

void ComboBox::paintEvent(QPaintEvent *e)
{
    QStylePainter painter(this);
    painter.setPen(palette().color(QPalette::Text));

    // draw the combobox frame, focusrect and selected etc.
    QStyleOptionComboBox opt;
    initStyleOption(&opt);
    QRect textRect = style()->subControlRect(QStyle::CC_ComboBox, &opt, QStyle::SC_ComboBoxEditField, this);
    QFontMetrics fontMetric(painter.font());
    const QString elidedText = QAbstractItemDelegate::elidedText(fontMetric, textRect.width(), Qt::ElideRight, this->currentText());
    opt.currentText = elidedText;
    painter.drawComplexControl(QStyle::CC_ComboBox, opt);

    // draw the icon and text
    painter.drawControl(QStyle::CE_ComboBoxLabel, opt);
}

} // namespace QRCode