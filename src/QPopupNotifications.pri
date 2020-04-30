#
# Copyright (c) 2020 Adan Mercado
# adanmp34@gmail.com
# https://github.com/adanmercado
#
# This file is part of the QPopupNotifications library, which is published under the Apache 2.0 license,
# you can read a copy at the following link https://www.apache.org/licenses/LICENSE-2.0
#

QT += core gui widgets
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

FORMS += \
    $$PWD/Notification.ui

HEADERS += \
    $$PWD/Notification.h \
    $$PWD/NotificationHandler.h

SOURCES += \
    $$PWD/Notification.cpp \
    $$PWD/NotificationHandler.cpp

INCLUDEPATH += $$PWD
