#include "notification.h"
#include <QDesktopWidget>
#include <QAPPlication>
#include <QTimer>

namespace QRCode {

Notification::Notification(QWidget *parent, bool autoClose)
    : QWidget(parent)
    , m_autoClose(autoClose)
    , m_animation(0)
{
    setWindowFlag(Qt::FramelessWindowHint);

    m_desktop = QApplication::desktop();
}

Notification::~Notification()
{
}

void Notification::showAnimation()
{
    if (!m_animation) {
        m_animation = new QPropertyAnimation(this, "pos");
        m_animation->setDuration(500);
    };
    m_animation->setStartValue(QPoint(this->x(), this->y()));
    m_animation->setEndValue(QPoint((m_desktop->screenGeometry().width() - this->width()),
                                    (m_desktop->availableGeometry().height() - this->height())));
    m_animation->start();

    if (m_autoClose) {
        m_remainTimer = new QTimer();
        connect(m_remainTimer, SIGNAL(timeout()), this, SLOT(stopAnimation()));
        m_remainTimer->start(1 * 60 * 1000);
    }
}

void Notification::stopAnimation()
{
    if (!m_animation)
        return;

    if (m_autoClose) {
        m_remainTimer->stop();
        disconnect(m_remainTimer, SIGNAL(timeout()), this, SLOT(close()));
        delete m_remainTimer;
        m_remainTimer = 0;
    }

    m_animation->setStartValue(QPoint(this->x(), this->y()));
    m_animation->setEndValue(QPoint((m_desktop->screenGeometry().width() - this->width()),
                                    m_desktop->screenGeometry().height()));
    m_animation->start();

    connect(m_animation, SIGNAL(finished()), this, SLOT(clear()));
}

void Notification::clear()
{
    if (!m_animation)
        return;

    disconnect(m_animation, SIGNAL(finished()), this, SLOT(clear()));
    delete m_animation;
    m_animation = 0;
}

} // namespace QRCode