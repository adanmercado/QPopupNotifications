/*
 * Copyright (c) 2020 Adan Mercado
 * adanmp34@gmail.com
 * https://github.com/adanmercado
 *
 * This file is part of the QPopupNotifications library, which is published under the Apache 2.0 license,
 * you can read a copy at the following link https://www.apache.org/licenses/LICENSE-2.0
*/

#ifndef NOTIFICATIONHANDLER_H
#define NOTIFICATIONHANDLER_H

#include <QList>
#include <Notification.h>

class NotificationHandler
{
public:
    enum Theme {
        Light,
        Dark
    };

    enum Position {
        TopLeft,
        TopRight,
        BottomLeft,
        BottomRight
    };

    static NotificationHandler *instance();

private:
    NotificationHandler();
    ~NotificationHandler();

    NotificationHandler(NotificationHandler const&);
    NotificationHandler &operator=(NotificationHandler const&);

public:
    void setMaxVisibleNotifications(const int &max);
    void setLifespan(const int &msec);

    void setActiveTheme(Theme theme);
    Theme activeTheme() const;

    void setNotificationsPos(Position pos);
    Position notificationPos() const;

    void setNotificationsMargin(const int &margin);
    int notificationsMargin() const;

    void setNotifcationsSpacing(const int &spacing);
    int notificationSpacing() const;

    void addMessage(const QString &msg, Notification::Type type);
    void clearNotificationList();

private:
    void updateVisiblePopups();

private:
    QList<Notification*> m_notificationList;

    int m_maxVisibleNotifications;
    int m_activeNotifications;
    int m_lifespan;

    Theme m_activeTheme;
    Position m_notificationsPos;

    int m_notificationsMargin;
    int m_notificationsSpacing;
};

#endif // NOTIFICATIONHANDLER_H
