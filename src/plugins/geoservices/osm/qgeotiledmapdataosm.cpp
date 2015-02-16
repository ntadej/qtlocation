/****************************************************************************
**
** Copyright (C) 2015 Aaron McCarthy <mccarthy.aaron@gmail.com>
** Contact: http://www.qt.io/licensing/
**
** This file is part of the QtLocation module of the Qt Toolkit.
**
** $QT_BEGIN_LICENSE:LGPL21$
** Commercial License Usage
** Licensees holding valid commercial Qt licenses may use this file in
** accordance with the commercial license agreement provided with the
** Software or, alternatively, in accordance with the terms contained in
** a written agreement between you and Digia. For licensing terms and
** conditions see http://qt.digia.com/licensing. For further information
** use the contact form at http://qt.digia.com/contact-us.
**
** GNU Lesser General Public License Usage
** Alternatively, this file may be used under the terms of the GNU Lesser
** General Public License version 2.1 or version 3 as published by the Free
** Software Foundation and appearing in the file LICENSE.LGPLv21 and
** LICENSE.LGPLv3 included in the packaging of this file. Please review the
** following information to ensure the GNU Lesser General Public License
** requirements will be met: https://www.gnu.org/licenses/lgpl.html and
** http://www.gnu.org/licenses/old-licenses/lgpl-2.1.html.
**
** In addition, as a special exception, Digia gives you certain additional
** rights. These rights are described in the Digia Qt LGPL Exception
** version 1.1, included in the file LGPL_EXCEPTION.txt in this package.
**
** $QT_END_LICENSE$
**
****************************************************************************/

#include "qgeotiledmapdataosm.h"
#include "qgeotiledmappingmanagerengineosm.h"

#include <QtLocation/private/qgeotilespec_p.h>

QT_BEGIN_NAMESPACE

QGeoTiledMapDataOsm::QGeoTiledMapDataOsm(QGeoTiledMappingManagerEngineOsm *engine, QObject *parent)
:   QGeoTiledMapData(engine, parent), m_mapId(-1)
{
}

QGeoTiledMapDataOsm::~QGeoTiledMapDataOsm()
{
}

void QGeoTiledMapDataOsm::evaluateCopyrights(const QSet<QGeoTileSpec> &visibleTiles)
{
    if (visibleTiles.isEmpty())
        return;

    QGeoTileSpec tile = *visibleTiles.constBegin();
    if (tile.mapId() == m_mapId)
        return;

    m_mapId = tile.mapId();

    QString copyrights;
    switch (m_mapId) {
    case 1:
    case 2:
        // set attribution to Map Quest
        copyrights = tr("Tiles Courtesy of <a href='http://www.mapquest.com/'>MapQuest</a><br/>Data \u00a9 <a href='http://www.openstreetmap.org/copyright'>OpenStreetMap</a> contributors");
        break;
    case 3:
    case 4:
    case 5:
    case 6:
    case 7:
        // set attribution to Thunder Forest
        copyrights = tr("Maps \u00a9 <a href='http://www.thunderforest.com/'>Thunderforest</a><br/>Data \u00a9 <a href='http://www.openstreetmap.org/copyright'>OpenStreetMap</a> contributors");
        break;
    default:
        // set attribution to OSM
        copyrights = tr("\u00a9 <a href='http://www.openstreetmap.org/copyright'>OpenStreetMap</a> contributors");
    }

    emit copyrightsChanged(copyrights);
}

QT_END_NAMESPACE
