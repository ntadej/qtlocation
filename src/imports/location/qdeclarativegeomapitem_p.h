/****************************************************************************
**
** Copyright (C) 2011 Nokia Corporation and/or its subsidiary(-ies).
** All rights reserved.
** Contact: Nokia Corporation (qt-info@nokia.com)
**
** This file is part of the QtLocation module of the Qt Toolkit.
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

#ifndef QDECLARATIVEGEOMAPITEM_H
#define QDECLARATIVEGEOMAPITEM_H

#include <QtDeclarative/qquickitem.h>
#include <QtCore/QCoreApplication>
#include <QtCore/QPointer>

#include "qsgtexture.h"
#include "mapitem.h"
#include "qdeclarativecoordinate_p.h"
#include "qdeclarativegeomap_p.h"

QT_BEGIN_NAMESPACE

#include <private/qquickshadereffectsource_p.h>

class QDeclarativeGeoMapItem : public QQuickItem
{
    Q_OBJECT
    Q_PROPERTY(QDeclarativeCoordinate* coordinate READ coordinate WRITE setCoordinate NOTIFY coordinateChanged)
    Q_PROPERTY(QQuickItem* sourceItem READ sourceItem WRITE setSourceItem NOTIFY sourceItemChanged)
    Q_PROPERTY(double zoomLevel READ zoomLevel WRITE setZoomLevel NOTIFY zoomLevelChanged)
    //Q_PROPERTY(bool live READ live WRITE setLive NOTIFY liveChanged)

public:
    QDeclarativeGeoMapItem(QQuickItem *parent = 0);
    ~QDeclarativeGeoMapItem();

    // From QDeclarativeParserStatus
    virtual void componentComplete();

    void setCoordinate(QDeclarativeCoordinate *coordinate);
    QDeclarativeCoordinate* coordinate();

    void setSourceItem(QQuickItem* sourceItem);
    QQuickItem* sourceItem();

    void setZoomLevel(double zoomLevel);
    double zoomLevel();

    void updateItem();
    void setMap(QDeclarativeGeoMap* map);

    MapItem* mapItem();
    bool hasValidTexture();

    // from QQuickItem
    QSGNode* updatePaintNode(QSGNode* node, UpdatePaintNodeData* data);

Q_SIGNALS:
    void coordinateChanged();
    void sourceItemChanged();
    void zoomLevelChanged();

private Q_SLOTS:
    void coordinateCoordinateChanged(double);
    void textureChangedSlot();

private:
    void up();
    void down();
    QQuickShaderEffectSource* shaderSource_;
    QQuickItem* sourceItem_;
    QDeclarativeCoordinate* coordinate_;
    QDeclarativeGeoMap* map_;
    // TODO enable didnt compile
    //QPointer<QDeclarativeGeoMap*> map_;
    bool componentCompleted_;
    MapItem mapItem_;
    friend class QDeclarativeGeoMapItemNode;
    Q_DISABLE_COPY(QDeclarativeGeoMapItem);
};

QT_END_NAMESPACE

QML_DECLARE_TYPE(QT_PREPEND_NAMESPACE(QDeclarativeGeoMapItem));

#endif
