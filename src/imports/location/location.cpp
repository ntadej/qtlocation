/****************************************************************************
**
** Copyright (C) 2010 Nokia Corporation and/or its subsidiary(-ies).
** All rights reserved.
** Contact: Nokia Corporation (qt-info@nokia.com)
**
** This file is part of the plugins of the Qt Toolkit.
**
** $QT_BEGIN_LICENSE:LGPL$
** No Commercial Usage
** This file contains pre-release code and may not be distributed.
** You may use this file in accordance with the terms and conditions
** contained in the Technology Preview License Agreement accompanying
** this package.
**
** GNU Lesser General Public License Usage
** Alternatively, this file may be used under the terms of the GNU Lesser
** General Public License version 2.1 as published by the Free Software
** Foundation and appearing in the file LICENSE.LGPL included in the
** packaging of this file.  Please review the following information to
** ensure the GNU Lesser General Public License version 2.1 requirements
** will be met: http://www.gnu.org/licenses/old-licenses/lgpl-2.1.html.
**
** In addition, as a special exception, Nokia gives you certain additional
** rights.  These rights are described in the Nokia Qt LGPL Exception
** version 1.1, included in the file LGPL_EXCEPTION.txt in this package.
**
** If you have questions regarding the use of this file, please contact
** Nokia at qt-info@nokia.com.
**
**
**
**
**
**
**
**
** $QT_END_LICENSE$
**
****************************************************************************/

#include "qdeclarativepositionsource_p.h"
#include "qdeclarativeposition_p.h"
#include "qdeclarativelandmark_p.h"
#include "qdeclarativelandmarkcategory_p.h"
#include "qdeclarativelandmarkmodel_p.h"
#include "qdeclarativelandmarkcategorymodel_p.h"

#include "qgeomapobject.h"
#include "qdeclarativegeoboundingbox_p.h"
#include "qdeclarativegeoboundingcircle_p.h"
#include "qdeclarativegeoaddress_p.h"
#include "qdeclarativegeoplace_p.h"
#include "qdeclarativecoordinate_p.h"

#include "qdeclarativegeoserviceprovider_p.h"
#include "qdeclarativegraphicsgeomap_p.h"
#include "qdeclarative3dgraphicsgeomap_p.h"
#include "qdeclarativegeomapgroupobject_p.h"
#include "qdeclarativegeomapobjectborder_p.h"
#include "qdeclarativegeomapcircleobject_p.h"
#include "qdeclarativegeomappixmapobject_p.h"
#include "qdeclarativegeomappolygonobject_p.h"
#include "qdeclarativegeomappolylineobject_p.h"
#include "qdeclarativegeomaprectangleobject_p.h"
#include "qdeclarativegeomaptextobject_p.h"

#include "qdeclarativegeomapmousearea_p.h"
#include "qdeclarativegeomapmouseevent_p.h"

#include "qdeclarativegeoroute_p.h"
#include "qdeclarativegeomaprouteobject_p.h"
#include "qdeclarativegeoroutemodel_p.h"
#include "qdeclarativegeocodemodel_p.h"
#include "qdeclarativegeomaneuver_p.h"

#include <QtDeclarative/qdeclarativeextensionplugin.h>
#include <QtDeclarative/qdeclarative.h>
#include <QDebug>

QT_BEGIN_NAMESPACE
QTM_USE_NAMESPACE

class QLocationDeclarativeModule: public QDeclarativeExtensionPlugin
{
    Q_OBJECT

public:
    virtual void registerTypes(const char* uri) {
        if (QLatin1String(uri) == QLatin1String("QtMobility.location")) {
            // Elements available since Qt mobility 1.1:
            qmlRegisterType<QDeclarativePosition>(uri, 1, 1, "Position");
            qmlRegisterType<QDeclarativePositionSource>(uri, 1, 1, "PositionSource");
            qmlRegisterType<QDeclarativeLandmark>(uri, 1, 1, "Landmark");
            qmlRegisterType<QDeclarativeLandmarkModel>(uri, 1, 1, "LandmarkModel");
            qmlRegisterType<QDeclarativeLandmarkNameFilter>(uri, 1, 1, "LandmarkNameFilter");
            qmlRegisterType<QDeclarativeLandmarkCategoryFilter>(uri, 1, 1, "LandmarkCategoryFilter");
            qmlRegisterType<QDeclarativeLandmarkBoxFilter>(uri, 1, 1, "LandmarkBoxFilter");
            qmlRegisterType<QDeclarativeLandmarkProximityFilter>(uri, 1, 1, "LandmarkProximityFilter");
            qmlRegisterType<QDeclarativeLandmarkUnionFilter>(uri, 1, 1, "LandmarkUnionFilter");
            qmlRegisterType<QDeclarativeLandmarkIntersectionFilter>(uri, 1, 1, "LandmarkIntersectionFilter");
            qmlRegisterType<QDeclarativeLandmarkCategory>(uri, 1, 1, "LandmarkCategory");
            qmlRegisterType<QDeclarativeLandmarkCategoryModel>(uri, 1, 1, "LandmarkCategoryModel");
            qmlRegisterUncreatableType<QDeclarativeLandmarkFilterBase>(uri, 1, 1, "LandmarkFilterBase", QDeclarativeLandmarkFilterBase::tr("LandmarkFilterBase is an abstract class"));
            qmlRegisterUncreatableType<QDeclarativeLandmarkAbstractModel>(uri, 1, 1, "LandmarkAbstractModel", QDeclarativeLandmarkAbstractModel::tr("LandmarkAbstractModel is an abstract class"));
            qmlRegisterType<QDeclarativeCoordinate>(uri, 1, 1, "Coordinate");
            qmlRegisterType<QDeclarativeGeoBoundingBox>(uri, 1, 1, "BoundingBox");
            qmlRegisterType<QDeclarativeGeoPlace>(uri, 1, 1, "Place");
            qmlRegisterType<QDeclarativeGeoAddress>(uri, 1, 1, "Address");

            qmlRegisterType<QDeclarativeGeoServiceProvider>(uri, 1, 2, "Plugin");
            qmlRegisterType<QDeclarativeGeoServiceProviderParameter>(uri, 1, 2, "PluginParameter");
            qmlRegisterType<QDeclarativeGraphicsGeoMap>(uri, 1, 2, "Map");
            qmlRegisterType<QDeclarativeGeoMapObjectBorder>(); // used as grouped property
            qmlRegisterType<QGeoMapObject>(uri, 1, 2, "QGeoMapObject");
            qmlRegisterType<QDeclarativeGeoMapObject>(uri, 1, 2, "MapObject");
            qmlRegisterType<QDeclarativeGeoMapObjectView>(uri, 1, 2, "MapObjectView");
            qmlRegisterType<QDeclarativeGeoMapGroupObject>(uri, 1, 2, "MapGroup");
            qmlRegisterType<QDeclarativeGeoMapCircleObject>(uri, 1, 2, "MapCircle");
            qmlRegisterType<QDeclarativeGeoMapPolygonObject>(uri, 1, 2, "MapPolygon");
            qmlRegisterType<QDeclarativeGeoMapPolylineObject>(uri, 1, 2, "MapPolyline");
            qmlRegisterType<QDeclarativeGeoMapRectangleObject>(uri, 1, 2, "MapRectangle");
            qmlRegisterType<QDeclarativeGeoMapTextObject>(uri, 1, 2, "MapText");
            qmlRegisterType<QDeclarativeGeoMapPixmapObject>(uri, 1, 2, "MapImage");
            qmlRegisterType<QDeclarativeGeoMapMouseArea>(uri, 1, 2, "MapMouseArea");
            qmlRegisterType<QDeclarativeGeoMapMouseEvent>(uri, 1, 2, "MapMouseEvent");

        } else if (QLatin1String(uri) == QLatin1String("Qt.location")) {
            // This version numbering is not correct. It is just something to get going
            // until the proper versioning scheme of QML plugins in Qt5 is agreed upon.
            qmlRegisterType<QDeclarativePosition>(uri, 5, 0, "Position");
            qmlRegisterType<QDeclarativePositionSource>(uri, 5, 0, "PositionSource");
            qmlRegisterType<QDeclarativeLandmark>(uri, 5, 0, "Landmark");
            qmlRegisterType<QDeclarativeLandmarkModel>(uri, 5, 0, "LandmarkModel");
            qmlRegisterType<QDeclarativeLandmarkNameFilter>(uri, 5, 0, "LandmarkNameFilter");
            qmlRegisterType<QDeclarativeLandmarkCategoryFilter>(uri, 5, 0, "LandmarkCategoryFilter");
            qmlRegisterType<QDeclarativeLandmarkBoxFilter>(uri, 5, 0, "LandmarkBoxFilter");
            qmlRegisterType<QDeclarativeLandmarkProximityFilter>(uri, 5, 0, "LandmarkProximityFilter");
            qmlRegisterType<QDeclarativeLandmarkUnionFilter>(uri, 5, 0, "LandmarkUnionFilter");
            qmlRegisterType<QDeclarativeLandmarkIntersectionFilter>(uri, 5, 0, "LandmarkIntersectionFilter");
            qmlRegisterType<QDeclarativeLandmarkCategory>(uri, 5, 0, "LandmarkCategory");
            qmlRegisterType<QDeclarativeLandmarkCategoryModel>(uri, 5, 0, "LandmarkCategoryModel");
            qmlRegisterUncreatableType<QDeclarativeLandmarkFilterBase>(uri, 5, 0, "LandmarkFilterBase", QDeclarativeLandmarkFilterBase::tr("LandmarkFilterBase is an abstract class"));
            qmlRegisterUncreatableType<QDeclarativeLandmarkAbstractModel>(uri, 5, 0, "LandmarkAbstractModel", QDeclarativeLandmarkAbstractModel::tr("LandmarkAbstractModel is an abstract class"));
            qmlRegisterType<QDeclarativeCoordinate>(uri, 5, 0, "Coordinate");
            qmlRegisterType<QDeclarativeGeoBoundingBox>(uri, 5, 0, "BoundingBox");
            qmlRegisterType<QDeclarativeGeoPlace>(uri, 5, 0, "Place");
            qmlRegisterType<QDeclarativeGeoAddress>(uri, 5, 0, "Address");

            qmlRegisterType<QDeclarativeGeoServiceProvider>(uri, 5, 0, "Plugin");
            qmlRegisterType<QDeclarativeGeoServiceProviderParameter>(uri, 5, 0, "PluginParameter");
            qmlRegisterType<QDeclarative3DGraphicsGeoMap>(uri, 5, 0, "Map3D");
            qmlRegisterType<QDeclarativeGeoMapObjectBorder>(); // used as grouped property
            qmlRegisterType<QGeoMapObject>(uri, 5, 0, "QGeoMapObject");
            qmlRegisterType<QDeclarativeGeoMapObject>(uri, 5, 0, "MapObject");
            qmlRegisterType<QDeclarativeGeoMapObjectView>(uri, 5, 0, "MapObjectView");
            qmlRegisterType<QDeclarativeGeoMapGroupObject>(uri, 5, 0, "MapGroup");
            qmlRegisterType<QDeclarativeGeoMapCircleObject>(uri, 5, 0, "MapCircle");
            qmlRegisterType<QDeclarativeGeoMapPolygonObject>(uri, 5, 0, "MapPolygon");
            qmlRegisterType<QDeclarativeGeoMapPolylineObject>(uri, 5, 0, "MapPolyline");
            qmlRegisterType<QDeclarativeGeoMapRectangleObject>(uri, 5, 0, "MapRectangle");
            qmlRegisterType<QDeclarativeGeoMapTextObject>(uri, 5, 0, "MapText");
            qmlRegisterType<QDeclarativeGeoMapPixmapObject>(uri, 5, 0, "MapImage");
            qmlRegisterType<QDeclarativeGeoMapMouseArea>(uri, 5, 0, "MapMouseArea");
            qmlRegisterType<QDeclarativeGeoMapMouseEvent>(uri, 5, 0, "MapMouseEvent");

            qmlRegisterType<QDeclarativeGeocodeModel>(uri, 5, 0, "GeocodeModel"); // geocoding and reverse geocoding
            qmlRegisterType<QDeclarativeGeoRouteModel>(uri, 5, 0, "RouteModel");
            qmlRegisterType<QDeclarativeGeoRouteQuery>(uri, 5, 0, "RouteQuery");
            qmlRegisterType<QDeclarativeGeoRoute>(uri, 5, 0, "Route"); // data type
            qmlRegisterType<QDeclarativeGeoMapRouteObject>(uri, 5, 0, "MapRoute");   // graphical presentation
            qmlRegisterType<QDeclarativeGeoRouteSegment>(uri, 5, 0, "RouteSegment");
            qmlRegisterType<QDeclarativeGeoManeuver>(uri, 5, 0, "RouteManeuver");
            qmlRegisterType<QDeclarativeGeoBoundingCircle>(uri, 5, 0, "BoundingCircle");
        } else {
            qDebug() << "Unsupported URI given to load location QML plugin: " << QLatin1String(uri);
        }
    }
};

QT_END_NAMESPACE
#include "location.moc"

Q_EXPORT_PLUGIN2(declarative_location, QT_PREPEND_NAMESPACE(QLocationDeclarativeModule));
