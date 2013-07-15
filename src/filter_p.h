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

#ifndef HISTORY_FILTER_P_H
#define HISTORY_FILTER_P_H

#include <QString>
#include <QVariant>
#include "types.h"

namespace History
{

class FilterPrivate
{

public:
    FilterPrivate();
    FilterPrivate(const QString &theFilterProperty,
                         const QVariant &theFilterValue,
                         MatchFlags theMatchFlags);
    virtual ~FilterPrivate();


    QString filterProperty;
    QVariant filterValue;
    MatchFlags matchFlags;
};

}

#endif // HISTORY_FILTER_P_H