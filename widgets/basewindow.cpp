#include "basewindow.h"
#include "qprogressindicator.h"
#include <qpainter.h>
#include <qdrawutil.h>

#ifdef Q_OS_WIN
#include <qt_windows.h>
#include <Windowsx.h>
#include <dwmapi.h>

#pragma comment(lib, "dwmapi.lib")
#endif

/**
 * .BaseWindow
 */
BaseWindow::BaseWindow(QWidget *parent)
    : QDialog(parent)
    , m_dropShadow(":/box-shadow.png")
{
    setAttribute(Qt::WA_TranslucentBackground);
    setAttribute(Qt::WA_StyledBackground);
    setShowDropShadow(true);
}

BaseWindow::~BaseWindow()
{
}

void BaseWindow::setResizable(bool resizable)
{
    m_resizable = resizable;

#ifdef Q_OS_WIN
    if (m_resizable) {
        setWindowFlags(windowFlags() | Qt::WindowMaximizeButtonHint);

        //this line will get titlebar/thick frame/Aero back, which is exactly what we want
        //we will get rid of titlebar and thick frame again in nativeEvent() later
        HWND hwnd = (HWND) this->winId();
        DWORD style = ::GetWindowLong(hwnd, GWL_STYLE);
        ::SetWindowLongPtr(hwnd, GWL_STYLE, style | WS_THICKFRAME | WS_MAXIMIZEBOX | WS_CAPTION);
    } else {
        setWindowFlags(windowFlags() & ~Qt::WindowMaximizeButtonHint);

        HWND hwnd = (HWND) this->winId();
        DWORD style = ::GetWindowLong(hwnd, GWL_STYLE);
        ::SetWindowLongPtr(hwnd, GWL_STYLE, style & ~WS_MAXIMIZEBOX & ~WS_CAPTION);
    }

    DwmEnableComposition(DWM_EC_ENABLECOMPOSITION); // windows7 need disable.
    ////we better left 1 piexl width of border untouch, so OS can draw nice shadow around it
    const MARGINS shadow = {1, 1, 1, 1};
    DwmExtendFrameIntoClientArea(HWND(this->winId()), &shadow);
#endif
}

void BaseWindow::setShowDropShadow(bool shadow)
{
    m_useShadow = shadow;
}

void BaseWindow::setBorderWidth(int borderWidth)
{
    m_borderWidth = borderWidth;
}

void BaseWindow::BaseWindow::setTitleBar(QWidget *titleBar)
{
    m_titleBar = titleBar;
}

void BaseWindow::paintEvent(QPaintEvent *event)
{
    if (m_useShadow) {
        QPainter painter(this);

        QMargins margins{ 10, 10, 10, 10};
        qDrawBorderPixmap(&painter, rect(), margins, m_dropShadow);
    }

    QDialog::paintEvent(event);
}

bool BaseWindow::event(QEvent *event)
{
    switch (event->type()) {
    case QEvent::MouseButtonPress:
        handleMousePressEvent(static_cast<QMouseEvent *>(event));
        return true;
    case QEvent::MouseButtonDblClick:
        handleMouseDoubleClickEvent(static_cast<QMouseEvent *>(event));
        return true;
    case QEvent::KeyPress:
        handleKeyPressEvent(static_cast<QKeyEvent *>(event));
        return true;
    }
    return QDialog::event(event);
}

bool BaseWindow::nativeEvent(const QByteArray &eventType, void *message, long *result)
{
    Q_UNUSED(eventType)

#if defined(Q_OS_WIN)
    MSG *nativeMessage = static_cast<MSG *>(message);

    switch (nativeMessage->message) {
    case WM_NCCALCSIZE: {
        *result = 0;
        return true;
    }

    case WM_NCHITTEST: {
        if (!m_resizable || isMaximized()) {
            return false;
        }

        *result = 0;
        RECT winrect;
        GetWindowRect((HWND) winId(), &winrect);

        long x = GET_X_LPARAM(nativeMessage->lParam);
        long y = GET_Y_LPARAM(nativeMessage->lParam);

        bool resizeWidth = minimumWidth() != maximumWidth();
        bool resizeHeight = minimumHeight() != maximumHeight();
        if (resizeWidth) {
            //left border
            if (x >= winrect.left && x <= winrect.left + m_borderWidth) {
                *result = HTLEFT;
            }
            //right border
            if (x <= winrect.right && x >= winrect.right - m_borderWidth) {
                *result = HTRIGHT;
            }
        }
        if (resizeHeight) {
            //bottom border
            if (y <= winrect.bottom && y >= winrect.bottom - m_borderWidth) {
                *result = HTBOTTOM;
            }
            //top border
            if (y >= winrect.top && y <= winrect.top + m_borderWidth) {
                *result = HTTOP;
            }
        }
        if (resizeWidth && resizeHeight) {
            //bottom left corner
            if (x >= winrect.left && x <= winrect.left + m_borderWidth && y <= winrect.bottom && y >= winrect.bottom - m_borderWidth) {
                *result = HTBOTTOMLEFT;
            }
            //bottom right corner
            if (x <= winrect.right && x >= winrect.right - m_borderWidth && y <= winrect.bottom && y >= winrect.bottom - m_borderWidth) {
                *result = HTBOTTOMRIGHT;
            }
            //top left corner
            if (x >= winrect.left && x <= winrect.left + m_borderWidth && y >= winrect.top && y <= winrect.top + m_borderWidth) {
                *result = HTTOPLEFT;
            }
            //top right corner
            if (x <= winrect.right && x >= winrect.right - m_borderWidth && y >= winrect.top && y <= winrect.top + m_borderWidth) {
                *result = HTTOPRIGHT;
            }
        }

        if (*result == 0)
            return QDialog::nativeEvent(eventType, message, result);

        return true;
    } //end case WM_NCHITTEST

    }
 #endif

    return false;
}

void BaseWindow::handleMousePressEvent(QMouseEvent *event)
{
    if(event->button() != Qt::LeftButton)
        return;

    if(this->isMaximized()) {
        QDialog::mousePressEvent(event);
        return;
    }

    if(m_titleBar && m_titleBar->underMouse()) {
        if(m_resizable && event->y() < m_borderWidth) {
            QDialog::mousePressEvent(event);
        } else {
#if defined(Q_OS_WIN)
            ReleaseCapture();
            SendMessage(HWND(winId()), WM_SYSCOMMAND, SC_MOVE + HTCAPTION, 0);
#endif
        }
    }
}

void BaseWindow::handleMouseDoubleClickEvent(QMouseEvent *event)
{
    if(event->button() != Qt::LeftButton)
        return;

    if(!m_resizable)
        return;

    if(m_titleBar && m_titleBar->underMouse()) {
        isMaximized() ? showNormal() : showMaximized();
    }
}

void BaseWindow::handleKeyPressEvent(QKeyEvent *event)
{
    if ((event->key() == Qt::Key_Enter) || (event->key() == Qt::Key_Return)) {
        return;
    } else if (event->key() == Qt::Key_Escape) {
        done(QDialog::Rejected);
        return;
    }

    return QDialog::keyPressEvent(event);
}

/**
 * .BaseDialog
 */
BaseDialog::BaseDialog(QWidget *parent)
        : BaseWindow(parent)
{
    setWindowFlags(Qt::Dialog | Qt::FramelessWindowHint | Qt::NoDropShadowWindowHint);
}

BaseDialog::~BaseDialog()
{
}

void BaseDialog::keyPressEvent(QKeyEvent *event)
{
    if((event->key() == Qt::Key_Enter) || (event->key() == Qt::Key_Return)) {
        // TODO
    } else if(event->key() == Qt::Key_Escape) {
        done(QDialog::Rejected);
        return;
    }

    return BaseWindow::keyPressEvent(event);
}

/**
 * .BaseMainWindow
 */
BaseMainWindow::BaseMainWindow(const QString &title, QWidget *parent)
    : BaseWindow(parent)
{
    setWindowFlags(Qt::Dialog | Qt::FramelessWindowHint | Qt::WindowSystemMenuHint | Qt::WindowMinMaxButtonsHint);
    setWindowTitle(title);
    setResizable(true);

    m_busyIcon = new QProgressIndicator(this);

    m_trayIcon = new QSystemTrayIcon(this);
    QObject::connect(m_trayIcon, SIGNAL(activated(QSystemTrayIcon::ActivationReason)),
        this, SLOT(onSystemTrayIconActivated(QSystemTrayIcon::ActivationReason)));
}

BaseMainWindow::~BaseMainWindow()
{
    delete m_trayIcon;
}

void BaseMainWindow::initTrayIcon(const QIcon &icon, QMenu *menu)
{
    m_trayIcon->setIcon(icon);
    m_trayIcon->setContextMenu(menu);
    m_trayIcon->setToolTip(windowTitle());
    m_trayIcon->show();
}

void BaseMainWindow::showTrayMessage(const QString &msg)
{
    if(msg.isEmpty()) {
        m_trayIcon->showMessage("", "", QSystemTrayIcon::Information, 0);
        return;
    }

    m_trayIcon->showMessage(windowTitle(), msg, QSystemTrayIcon::Information, 5000);
}

void BaseMainWindow::showLoading(bool bShow)
{
    if(bShow) {
        m_busyIcon->show();
        m_busyIcon->startAnimation();
    } else {
        m_busyIcon->stopAnimation();
        m_busyIcon->hide();
    }
}

void BaseMainWindow::resetLoadingPosition()
{
    int sx = (this->width() - m_busyIcon->width()) / 2;
    int sy = (this->height() - m_busyIcon->height()) / 2;
    m_busyIcon->move(sx, sy);
}

void BaseMainWindow::on_btnMin_clicked()
{
    showMinimized();
}

void BaseMainWindow::on_btnMax_clicked(bool checked)
{
    if(checked)
        showMaximized();
    else {
        showNormal();
    }
}

void BaseMainWindow::on_btnClose_clicked()
{
    hide();
}

void BaseMainWindow::onSystemTrayIconActivated(QSystemTrayIcon::ActivationReason reason)
{
    switch(reason) {
    case QSystemTrayIcon::Trigger:
        this->setWindowState(Qt::WindowActive);
        this->activateWindow();
        break;

    case QSystemTrayIcon::DoubleClick:
        if(this->isHidden()) {
            this->show();
            this->setWindowState(Qt::WindowActive);
            this->activateWindow();
        } else {
            this->hide();
        }
        break;

    default:
        break;
    }
}

void BaseMainWindow::showEvent(QShowEvent *event)
{
    BaseWindow::showEvent(event);

    resetLoadingPosition();
}

void BaseMainWindow::resizeEvent(QResizeEvent *event)
{
    BaseWindow::resizeEvent(event);

    resetLoadingPosition();
}

void BaseMainWindow::mouseDoubleClickEvent(QMouseEvent *event)
{
    event->ignore();
}

bool BaseMainWindow::nativeEvent(const QByteArray &eventType, void *message, long *result)
{
    Q_UNUSED(eventType)
    Q_UNUSED(result)

#if defined(Q_OS_WIN)
    const MSG *msg(static_cast<MSG *>(message));

    if (msg->message == WM_SYSCOMMAND) {
        if (SC_CLOSE == msg->wParam) {
            // 禁止任务栏"关闭窗口"
            return true;
        } if (61587 == msg->wParam) {
            // 禁用单击
            return true;
        } else if (61539 == msg->wParam) {
            // 禁用双击
            return true;
        } else if (WM_THEMECHANGED == msg->wParam) {
            // emit widgetStyleChanged();
        }
    }
#endif
    return BaseWindow::nativeEvent(eventType, message, result);
}
