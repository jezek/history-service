/*
 * Copyright (C) 2013 Canonical, Ltd.
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

#ifndef CALLCHANNELOBSERVER_H
#define CALLCHANNELOBSERVER_H

#include <QObject>
#include <TelepathyQt/CallChannel>

class CallChannelObserver : public QObject
{
    Q_OBJECT
public:
    explicit CallChannelObserver(QObject *parent = 0);
    
public Q_SLOTS:
    void onCallChannelAvailable(Tp::CallChannelPtr callChannel);

Q_SIGNALS:
    void callEnded(Tp::CallChannelPtr callChannel, bool missed);

protected Q_SLOTS:
    void onCallStateChanged(Tp::CallState state);

private:
    QList<Tp::CallChannelPtr> mChannels;
    QMap<Tp::CallChannel*,Tp::CallState> mCallStates;
};

#endif // CALLCHANNELOBSERVER_H
