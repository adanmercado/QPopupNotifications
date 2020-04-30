/*
 * Copyright (c) 2020 Adan Mercado
 * adanmp34@gmail.com
 * https://github.com/adanmercado
 *
 * This file is part of the QPopupNotifications library, which is published under the Apache 2.0 license,
 * you can read a copy at the following link https://www.apache.org/licenses/LICENSE-2.0
*/

#include <NotificationHandler.h>
#include <QTimer>

NotificationHandler *NotificationHandler::instance()
{
    static NotificationHandler instance;
    return &instance;
}

NotificationHandler::NotificationHandler()
{
    m_activeNotifications = 0;
    m_maxVisibleNotifications = 3;
    m_lifespan = 3000;
    m_activeTheme = Light;
    m_notificationsPos = TopRight;
    m_notificationsMargin = 10;
    m_notificationsSpacing = 6;
}

NotificationHandler::~NotificationHandler()
{
}

void NotificationHandler::setMaxVisibleNotifications(const int &max)
{
    m_maxVisibleNotifications = max;
}

void NotificationHandler::setLifespan(const int &msec)
{
    m_lifespan = msec;
}

void NotificationHandler::setActiveTheme(NotificationHandler::Theme theme)
{
    m_activeTheme = theme;
}

NotificationHandler::Theme NotificationHandler::activeTheme() const
{
    return m_activeTheme;
}

void NotificationHandler::setNotificationsPos(NotificationHandler::Position pos)
{
    m_notificationsPos = pos;
}

NotificationHandler::Position NotificationHandler::notificationPos() const
{
    return m_notificationsPos;
}

void NotificationHandler::setNotificationsMargin(const int &margin)
{
    m_notificationsMargin = margin;
}

int NotificationHandler::notificationsMargin() const
{
    return m_notificationsMargin;
}

void NotificationHandler::setNotifcationsSpacing(const int &spacing)
{
    m_notificationsSpacing = spacing;
}

int NotificationHandler::notificationSpacing() const
{
    return m_notificationsSpacing;
}

void NotificationHandler::addMessage(const QString &msg, Notification::Type type)
{
    Notification *popup = new Notification(nullptr, m_activeNotifications);
    popup->setData(msg, type);

    QObject::connect(popup, &Notification::started, [&]() {
        m_activeNotifications++;
    });
    QObject::connect(popup, &Notification::finished, [&](const int &index) {
        m_activeNotifications--;
        m_notificationList.removeAt(index);
        updateVisiblePopups();
    });
    QObject::connect(popup, &Notification::finished, popup, &Notification::deleteLater);
    m_notificationList.append(popup);

    if(m_activeNotifications < m_maxVisibleNotifications) {
        popup->showNotification();
        QTimer::singleShot(m_lifespan, popup, &Notification::closeNotification);
    }
}

void NotificationHandler::clearNotificationList()
{
    if(!m_notificationList.isEmpty()) {
        foreach(Notification *popup, m_notificationList)
            popup->deleteLater();
        m_notificationList.clear();
    }
}

void NotificationHandler::updateVisiblePopups()
{
    if(!m_notificationList.isEmpty()) {
        Notification *popup = nullptr;
        for(int i = 0; i < m_notificationList.size(); i++) {
            popup = m_notificationList.at(i);
            if(popup->status() == Notification::Pending && m_activeNotifications < m_maxVisibleNotifications) {
                popup->showNotification();
                QTimer::singleShot(m_lifespan, popup, &Notification::closeNotification);
            }
            popup->setNotificationNumber(i);
        }
    }
}
