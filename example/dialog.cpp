/*
 * Copyright (c) 2020 Adan Mercado
 * adanmp34@gmail.com
 * https://github.com/adanmercado
*/

#include "dialog.h"
#include "ui_dialog.h"

Dialog::Dialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::Dialog)
{
    ui->setupUi(this);
    connect(ui->pushButton, &QPushButton::clicked, this, &Dialog::showNotifications);

    notificationHandler = NotificationHandler::instance();
    notificationHandler->setMaxVisibleNotifications(2);
    notificationHandler->setLifespan(2000);
    notificationHandler->setNotificationsPos(NotificationHandler::BottomRight);
    notificationHandler->setNotifcationsSpacing(10);
}

Dialog::~Dialog()
{
    notificationHandler->clearNotificationList();
    delete ui;
}

void Dialog::showNotifications()
{
    notificationHandler->addMessage("This is an informative notification", Notification::Information);
    notificationHandler->addMessage("This is a warning notification", Notification::Warning);
    notificationHandler->addMessage("This is an error notification", Notification::Error);
    notificationHandler->addMessage("This is an informative notification", Notification::Information);
}

