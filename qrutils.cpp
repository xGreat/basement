#include "stdafx.h"
#include "qrutils.h"
#include <QPropertyAnimation>
#include <QDesktopWidget>

namespace QRCode {

namespace Utils {

class ApplicationStyle : public QProxyStyle
{
public:
    void drawPrimitive(PrimitiveElement pe,
                       const QStyleOption *opt,
                       QPainter *p,
                       const QWidget *widget = 0) const Q_DECL_OVERRIDE
    {
        if (QStyle::PE_FrameFocusRect == pe)
            return;
        else
            QProxyStyle::drawPrimitive(pe, opt, p, widget);
    }

    int styleHint(StyleHint hint,
                  const QStyleOption *option,
                  const QWidget *widget,
                  QStyleHintReturn *returnData) const Q_DECL_OVERRIDE
    {
        if (hint == QStyle::SH_ToolTip_WakeUpDelay)
            return 0;
        else if (hint == QStyle::SH_ToolTip_FallAsleepDelay)
            return 0;

        return QProxyStyle::styleHint(hint, option, widget, returnData);
    }
};

void setDefaultStyle(const QString &style)
{
    qApp->setStyleSheet(style);
    qApp->setStyle(new ApplicationStyle);
}

void centerWindow(QWidget *window)
{
    if (!window)
        return;

    QDesktopWidget *desk = QApplication::desktop();
    int screen = desk->screenNumber(QCursor::pos());
    window->setGeometry(
        QStyle::alignedRect(
            Qt::LeftToRight,
            Qt::AlignCenter,
            window->size(),
            qApp->desktop()->availableGeometry(screen)));
}

void centerScreen(QWidget *window)
{
    if (!window)
        return;

    QDesktopWidget *m = QApplication::desktop();
    QRect desk_rect = m->screenGeometry(m->screenNumber(QCursor::pos()));
    int desk_x = desk_rect.width();
    int desk_y = desk_rect.height();
    int x = window->width();
    int y = window->height();
    window->move(desk_x / 2 - x / 2 + desk_rect.left(), desk_y / 2 - y / 2 + desk_rect.top());
}

void fullScreen(QWidget *window)
{
    if (!window)
        return;

    QDesktopWidget *desk = qApp->desktop();
    int screen = desk->screenNumber(window);
    window->setGeometry(desk->availableGeometry(screen));
}

void fadeIn(QWidget *obj, int duration)
{
    QGraphicsOpacityEffect *fade_effect = new QGraphicsOpacityEffect(obj);
    obj->setGraphicsEffect(fade_effect);
    QPropertyAnimation *animation = new QPropertyAnimation(fade_effect, "opacity");
    animation->setEasingCurve(QEasingCurve::InOutQuad);
    animation->setDuration(duration);
    animation->setStartValue(0.01);
    animation->setEndValue(1.0);
    animation->start(QPropertyAnimation::DeleteWhenStopped);
}

void fadeOut(QWidget *obj, int duration)
{
    QGraphicsOpacityEffect *fade_effect = new QGraphicsOpacityEffect(obj);
    obj->setGraphicsEffect(fade_effect);
    QPropertyAnimation *animation = new QPropertyAnimation(fade_effect, "opacity");
    animation->setEasingCurve(QEasingCurve::InOutQuad);
    animation->setDuration(duration);
    animation->setStartValue(1.0);
    animation->setEndValue(0.01);
    animation->start(QPropertyAnimation::DeleteWhenStopped);

    QObject::connect(animation, SIGNAL(finished()), obj, SLOT(animationFinished()));
}

void bringToFront(QWidget *window)
{
    if (window->isMinimized()) {
        window->showNormal();
    }
#ifdef Q_OS_WIN
    HWND hWnd = HWND(window->winId());
    HWND hForeWnd = GetForegroundWindow();
    DWORD dwForeID = GetWindowThreadProcessId(hForeWnd, NULL);
    DWORD dwCurID = GetCurrentThreadId();
    AttachThreadInput(dwCurID, dwForeID, TRUE);
    ShowWindow(hWnd, SW_SHOWNORMAL);
    SetWindowPos(hWnd, HWND_TOPMOST, 0, 0, 0, 0, SWP_NOSIZE | SWP_NOMOVE);
    SetWindowPos(hWnd, HWND_NOTOPMOST, 0, 0, 0, 0, SWP_NOSIZE | SWP_NOMOVE);
    SetForegroundWindow(hWnd);
    AttachThreadInput(dwCurID, dwForeID, FALSE);
#endif
    window->show();
    window->activateWindow();
}

void openFileInExplorer(const QString &path)
{
#ifdef Q_OS_WIN
    QStringList args;

    args << "/select," << QDir::toNativeSeparators(path);

    QSharedPointer<QProcess> process(new QProcess());
    process->startDetached("explorer.exe", args);
#else
    QFileInfo fi(path);
    QDesktopServices::openUrl(QUrl::fromLocalFile(fi.absolutePath()));
#endif
}

void showToolTip(QWidget *target, QWidget *tooltipWidget, Qt::Alignment alignment)
{
    QPoint pos;
    switch (alignment) {
    case Qt::AlignTop:
        pos = QPoint(-(tooltipWidget->width() - target->width()) / 2, -tooltipWidget->height());
        break;
    case Qt::AlignBottom:
        pos = QPoint(-(tooltipWidget->width() - target->width()) / 2, target->height());
        break;
    default:
        break;
    }

    pos = target->mapToGlobal(pos);
    tooltipWidget->move(pos);
    tooltipWidget->show();
}

} // namespace Utils

} // namespace QRCode
