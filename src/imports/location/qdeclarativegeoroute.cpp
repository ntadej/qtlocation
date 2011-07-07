/****************************************************************************
**
** Copyright (C) 2010 Nokia Corporation and/or its subsidiary(-ies).
** All rights reserved.
** Contact: Nokia Corporation (qt-info@nokia.com)
**
** This file is part of the Qt Mobility Components.
**
** $QT_BEGIN_LICENSE:LGPL$
** GNU Lesser General Public License Usage
** This file may be used under the terms of the GNU Lesser General Public
** License version 2.1 as published by the Free Software Foundation and
** appearing in the file LICENSE.LGPL included in the packaging of this
** file. Please review the following information to ensure the GNU Lesser
** General Public License version 2.1 requirements will be met:
** http://www.gnu.org/licenses/old-licenses/lgpl-2.1.html.
**
** In addition, as a special exception, Nokia gives you certain additional
** rights. These rights are described in the Nokia Qt LGPL Exception
** version 1.1, included in the file LGPL_EXCEPTION.txt in this package.
**
** GNU General Public License Usage
** Alternatively, this file may be used under the terms of the GNU General
** Public License version 3.0 as published by the Free Software Foundation
** and appearing in the file LICENSE.GPL included in the packaging of this
** file. Please review the following information to ensure the GNU General
** Public License version 3.0 requirements will be met:
** http://www.gnu.org/copyleft/gpl.html.
**
** Other Usage
** Alternatively, this file may be used in accordance with the terms and
** conditions contained in a signed written agreement between you and Nokia.
**
**
**
**
**
** $QT_END_LICENSE$
**
****************************************************************************/

#include "qdeclarativegeoroute_p.h"

QT_BEGIN_NAMESPACE

QDeclarativeGeoRoute::QDeclarativeGeoRoute(QObject *parent)
    : QObject(parent)
{
    this->init();
}

QDeclarativeGeoRoute::QDeclarativeGeoRoute(const QGeoRoute &route, QObject *parent)
    : QObject(parent),
      route_(route)
{
    this->init();
}

QDeclarativeGeoRoute::~QDeclarativeGeoRoute() {}


void QDeclarativeGeoRoute::init()
{
    bounds_ = new QDeclarativeGeoBoundingBox(route_.bounds(), this);

    for (int i = 0; i < route_.path().size(); ++i)
        path_.append(new QDeclarativeCoordinate(route_.path().at(i), this));

    QGeoRouteSegment segment = route_.firstRouteSegment();
    while (segment.isValid()) {
        segments_.append(new QDeclarativeGeoRouteSegment(segment, this));
        segment = segment.nextRouteSegment();
    }
}

QDeclarativeGeoBoundingBox* QDeclarativeGeoRoute::bounds() const
{
    return bounds_;
}

int QDeclarativeGeoRoute::travelTime() const
{
    return route_.travelTime();
}

qreal QDeclarativeGeoRoute::distance() const
{
    return route_.distance();
}

QDeclarativeListProperty<QDeclarativeCoordinate> QDeclarativeGeoRoute::path()
{
    return QDeclarativeListProperty<QDeclarativeCoordinate>(this,
                                                            0,
                                                            path_append,
                                                            path_count,
                                                            path_at,
                                                            path_clear);
}

void QDeclarativeGeoRoute::path_append(QDeclarativeListProperty<QDeclarativeCoordinate> *prop, QDeclarativeCoordinate *coordinate)
{
    static_cast<QDeclarativeGeoRoute*>(prop->object)->path_.append(coordinate);
}

int QDeclarativeGeoRoute::path_count(QDeclarativeListProperty<QDeclarativeCoordinate> *prop)
{
    return static_cast<QDeclarativeGeoRoute*>(prop->object)->path_.count();
}

QDeclarativeCoordinate* QDeclarativeGeoRoute::path_at(QDeclarativeListProperty<QDeclarativeCoordinate> *prop, int index)
{
    return static_cast<QDeclarativeGeoRoute*>(prop->object)->path_.at(index);
}

void QDeclarativeGeoRoute::path_clear(QDeclarativeListProperty<QDeclarativeCoordinate> *prop)
{
    static_cast<QDeclarativeGeoRoute*>(prop->object)->path_.clear();
}

QDeclarativeListProperty<QDeclarativeGeoRouteSegment> QDeclarativeGeoRoute::segments()
{
    return QDeclarativeListProperty<QDeclarativeGeoRouteSegment>(this,
                                                                 0,
                                                                 segments_append,
                                                                 segments_count,
                                                                 segments_at,
                                                                 segments_clear);
}

void QDeclarativeGeoRoute::segments_append(QDeclarativeListProperty<QDeclarativeGeoRouteSegment> *prop, QDeclarativeGeoRouteSegment *segment)
{
    static_cast<QDeclarativeGeoRoute*>(prop->object)->segments_.append(segment);
}

int QDeclarativeGeoRoute::segments_count(QDeclarativeListProperty<QDeclarativeGeoRouteSegment> *prop)
{
    return static_cast<QDeclarativeGeoRoute*>(prop->object)->segments_.count();
}

QDeclarativeGeoRouteSegment* QDeclarativeGeoRoute::segments_at(QDeclarativeListProperty<QDeclarativeGeoRouteSegment> *prop, int index)
{
    return static_cast<QDeclarativeGeoRoute*>(prop->object)->segments_.at(index);
}

void QDeclarativeGeoRoute::segments_clear(QDeclarativeListProperty<QDeclarativeGeoRouteSegment> *prop)
{
    static_cast<QDeclarativeGeoRoute*>(prop->object)->segments_.clear();
}

#include "moc_qdeclarativegeoroute_p.cpp"

QT_END_NAMESPACE
