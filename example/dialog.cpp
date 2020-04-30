/*
 * Copyright (c) 2020 Adan Mercado
 * adanmp34@gmail.com
 * https://github.com/adanmercado
*/

#include "dialog.h"
#include "ui_dialog.h"

#include <QTableWidgetItem>

Dialog::Dialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::Dialog)
{
    ui->setupUi(this);
    connect(ui->showNotificationsButton, &QPushButton::clicked, this, &Dialog::showNotifications);
    connect(ui->addNotificationButton, &QPushButton::clicked, this, &Dialog::addNotification);
    connect(ui->removeNotificationButton, &QPushButton::clicked, this, &Dialog::removeNotification);

    ui->notificationsTable->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);

    types.insert("Information", Notification::Information);
    types.insert("Warning", Notification::Warning);
    types.insert("Error", Notification::Error);

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

void Dialog::addNotification()
{
    QString msg = ui->messageTextEdit->toPlainText().trimmed();
    if(msg.isEmpty()) {
        notificationHandler->addMessage("Enter a message to add it to the table", Notification::Error);
        return;
    }

    int type = ui->notificationTypeCombo->currentIndex();
    if(!type) {
        notificationHandler->addMessage("Specify a valid notification type", Notification::Error);
        return;
    }

    QTableWidgetItem *msgItem = new QTableWidgetItem(msg);
    QTableWidgetItem *typeItem = new QTableWidgetItem(ui->notificationTypeCombo->currentText());
    int row = ui->notificationsTable->rowCount();
    ui->notificationsTable->insertRow(row);
    ui->notificationsTable->setItem(row, 0, msgItem);
    ui->notificationsTable->setItem(row, 1, typeItem);
    ui->messageTextEdit->clear();
    ui->messageTextEdit->setFocus();
}

void Dialog::removeNotification()
{
    QModelIndexList selection = ui->notificationsTable->selectionModel()->selectedIndexes();
    if(selection.isEmpty()) {
        notificationHandler->addMessage("Select the notification to remove", Notification::Error);
        return;
    }

    int row = selection.first().row();
    ui->notificationsTable->removeRow(row);
    ui->messageTextEdit->setFocus();
}

void Dialog::showNotifications()
{
    QAbstractItemModel *model = ui->notificationsTable->model();
    if(!model->rowCount())
        return;

    QString msg;
    Notification::Type type = Notification::Information;
    for(int row = 0; row < model->rowCount(); row++) {
        msg = model->index(row, 0).data().toString();
        type = types.value(model->index(row, 1).data().toString());
        notificationHandler->addMessage(msg, type);
    }
}

