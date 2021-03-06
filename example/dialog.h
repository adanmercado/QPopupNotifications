/*
 * Copyright (c) 2020 Adan Mercado
 * adanmp34@gmail.com
 * https://github.com/adanmercado
*/

#ifndef DIALOG_H
#define DIALOG_H

#include <QDialog>
#include <QMap>
#include <NotificationHandler.h>

QT_BEGIN_NAMESPACE
namespace Ui { class Dialog; }
QT_END_NAMESPACE

class Dialog : public QDialog
{
    Q_OBJECT

public:
    Dialog(QWidget *parent = nullptr);
    ~Dialog();

private:
    void addNotification();
    void removeNotification();
    void showNotifications();

private:
    Ui::Dialog *ui;
    NotificationHandler *notificationHandler;
    QMap<QString, Notification::Type> types;
};
#endif // DIALOG_H
