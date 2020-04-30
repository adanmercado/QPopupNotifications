/*
 * Copyright (c) 2020 Adan Mercado
 * adanmp34@gmail.com
 * https://github.com/adanmercado
 *
 * This file is part of the QPopupNotifications library, which is published under the Apache 2.0 license,
 * you can read a copy at the following link https://www.apache.org/licenses/LICENSE-2.0
*/

#include <Notification.h>
#include <NotificationHandler.h>

#include "ui_Notification.h"

#include <QStyle>
#include <QScreen>


Notification::Notification(QWidget *parent, const int &number) :
    QDialog(parent),
    ui(new Ui::Notification)
{
    ui->setupUi(this);

    setAttribute(Qt::WA_ShowWithoutActivating);
    setWindowFlags(Qt::FramelessWindowHint | Qt::WindowDoesNotAcceptFocus | Qt::WindowStaysOnTopHint);

    m_status = Pending;
    m_number = number;
}

Notification::~Notification()
{
    delete ui;
}

void Notification::setData(const QString &msg, Type type)
{
    ui->message->setText(msg);
    QIcon icon;
    switch(type) {
        case Information:
            icon = qApp->style()->standardIcon(QStyle::SP_MessageBoxInformation);
            break;
        case Warning:
            icon = qApp->style()->standardIcon(QStyle::SP_MessageBoxWarning);
            break;
        case Error:
            icon = qApp->style()->standardIcon(QStyle::SP_MessageBoxCritical);
    }
    ui->icon->setPixmap(icon.pixmap(QSize(64, 64)));
}

void Notification::showNotification()
{
    setPosition();
    m_status = Started;
    show();
    emit started();
}

void Notification::closeNotification()
{
    m_status = Finished;
    close();
    emit finished(m_number);
}

Notification::Status Notification::status() const
{
    return m_status;
}

void Notification::setNotificationNumber(const int &number)
{
    m_number = number;
    if(m_status == Started)
        setPosition();
}

void Notification::setPosition()
{
    NotificationHandler *handler = NotificationHandler::instance();

    QRect position;
    int posY;
    switch(handler->notificationPos()) {
        case NotificationHandler::TopLeft:
            position = QStyle::alignedRect(Qt::LeftToRight, Qt::AlignTop | Qt::AlignLeft, size(), qApp->primaryScreen()->availableGeometry());
            posY = position.y() + handler->notificationsMargin() + (m_number * height()) + (m_number * handler->notificationSpacing());
            position.moveTo(position.x() + handler->notificationsMargin(), posY);
            break;
        case NotificationHandler::TopRight:
            position = QStyle::alignedRect(Qt::LeftToRight, Qt::AlignTop | Qt::AlignRight, size(), qApp->primaryScreen()->availableGeometry());
            posY = position.y() + handler->notificationsMargin() + (m_number * height()) + (m_number * handler->notificationSpacing());
            position.moveTo(position.x() - handler->notificationsMargin(), posY);
            break;
        case NotificationHandler::BottomLeft:
            position = QStyle::alignedRect(Qt::LeftToRight, Qt::AlignBottom | Qt::AlignLeft, size(), qApp->primaryScreen()->availableGeometry());
            posY = position.y() - handler->notificationsMargin() - (m_number * height()) - (m_number * handler->notificationSpacing());
            position.moveTo(position.x() + handler->notificationsMargin(), posY);
            break;
        case NotificationHandler::BottomRight:
            position = QStyle::alignedRect(Qt::LeftToRight, Qt::AlignBottom | Qt::AlignRight, size(), qApp->primaryScreen()->availableGeometry());
            posY = position.y() - handler->notificationsMargin() - (m_number * height()) - (m_number * handler->notificationSpacing());
            position.moveTo(position.x() - handler->notificationsMargin(), posY);
    }
    setGeometry(position);
}
