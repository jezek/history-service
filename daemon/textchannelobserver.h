/*
 * Copyright (C) 2012-2016 Canonical, Ltd.
 *
 * Authors:
 *  Gustavo Pichorim Boiko <gustavo.boiko@canonical.com>
 *
 * This file is part of history-service.
 *
 * history-service is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; version 3.
 *
 * history-service is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef TEXTCHANNELOBSERVER_H
#define TEXTCHANNELOBSERVER_H

#include <QObject>
#include <TelepathyQt/TextChannel>
#include <TelepathyQt/ReceivedMessage>

class TextChannelObserver : public QObject
{
    Q_OBJECT
public:
    explicit TextChannelObserver(QObject *parent = 0);

public Q_SLOTS:
    void onTextChannelAvailable(Tp::TextChannelPtr textChannel);

Q_SIGNALS:
    void channelAvailable(const Tp::TextChannelPtr textChannel);
    void textChannelInvalidated(const Tp::TextChannelPtr textChannel);
    void messageReceived(const Tp::TextChannelPtr textChannel, const Tp::ReceivedMessage &message);
    void messageSent(const Tp::TextChannelPtr textChannel, const Tp::Message &message, const QString &messageToken);

protected:
    void showNotificationForMessage(const Tp::ReceivedMessage &message);
    Tp::TextChannelPtr channelFromPath(const QString &path);

protected Q_SLOTS:
    void onTextChannelInvalidated();
    void onMessageReceived(const Tp::ReceivedMessage &message);
    void onMessageSent(const Tp::Message &message, Tp::MessageSendingFlags flags, const QString &sentMessageToken);

private:
    QList<Tp::TextChannelPtr> mChannels;
};

#endif // TEXTCHANNELOBSERVER_H
