/*********************************************************************
 * \file   qrutils.h
 * \brief  
 * 
 * \author heqingrui
 * \date   March 2024
 *********************************************************************/
#ifndef QRCODE_UTILS_H
#define QRCODE_UTILS_H
#include <QObject>

class QWidget;

namespace QRCode {

namespace Utils {

void setDefaultStyle(const QString &style);

void centerWindow(QWidget *frame);

void centerScreen(QWidget *widget);

void fullScreen(QWidget *widget);

void fadeIn(QWidget *obj, int duration);

void fadeOut(QWidget *obj, int duration);

void bringToFront(QWidget *widget);

void openFileInExplorer(const QString &path);

void showToolTip(QWidget *target, QWidget *tooltipWidget, Qt::Alignment alignment);

}

}

#endif // QRCODE_UTILS_H
