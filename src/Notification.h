/*
 * Copyright (c) 2020 Adan Mercado
 * adanmp34@gmail.com
 * https://github.com/adanmercado
 *
 * This file is part of the QPopupNotifications library, which is published under the Apache 2.0 license,
 * you can read a copy at the following link https://www.apache.org/licenses/LICENSE-2.0
*/

#ifndef NOTIFICATION_H
#define NOTIFICATION_H

#include <QDialog>

namespace Ui {
class Notification;
}

class Notification : public QDialog
{
    Q_OBJECT

public:
    enum Type {
        Information,
        Warning,
        Error
    };

    enum Status {
        Started,
        Pending,
        Finished
    };

public:
    Notification(QWidget *parent = nullptr, const int &number = 1);
    ~Notification();

    void setData(const QString &msg, Type type);
    void showNotification();
    void closeNotification();
    Status status() const;

    void setNotificationNumber(const int &number);
    void setPosition();

signals:
    void started();
    void finished(const int &number);

private:
    Ui::Notification *ui;
    Status m_status;
    int m_number;
};

#endif // NOTIFICATION_H
