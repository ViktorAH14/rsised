#include "item_resizer.h"
#include "rectangle.h"
#include "ellipse.h"
#include "curve.h"
#include "polyline.h"
#include "pixmapitem.h"
#include "technics_shape.h"
#include "device_shape.h"
#include "buildingstruct.h"

#include <QPainterPath>

Q_DECLARE_METATYPE(QPainterPath)

void ItemResizer::operator()(QGraphicsItem *item, const QVariant &value)
{
    switch (item->type()) {
    case Rectangle::Type: {
        Rectangle *rectItem = dynamic_cast<Rectangle *>(item);
        if (rectItem) {
            QRectF itemRect = value.toRectF();
            rectItem->setRect(itemRect);
        }
        break;
    }
    case Ellipse::Type: {
        Ellipse *ellipseItem = dynamic_cast<Ellipse *>(item);
        if (ellipseItem) {
            QRectF itemRect = value.toRectF();
            ellipseItem->setRect(itemRect);
        }
        break;
    }
    case Curve::Type: {
        Curve *curveItem = dynamic_cast<Curve *>(item);
        if (curveItem) {
            QPainterPath itemPath = value.value<QPainterPath>();
            curveItem->setPath(itemPath);
        }
        break;
    }
    case Polyline::Type: {
        Polyline *polylineItem = dynamic_cast<Polyline *>(item);
        if (polylineItem) {
            QPainterPath itemPath = value.value<QPainterPath>();
            polylineItem->setPath(itemPath);
        }
        break;
    }
    case PixmapItem::Type: {
        PixmapItem *pixmapItem = dynamic_cast<PixmapItem *>(item);
        if (pixmapItem) {
            pixmapItem->scalePixmap(value.toRectF());
        }
        break;
    }
    case TechnicsShape::Type: {
        TechnicsShape *technicsShape = dynamic_cast<TechnicsShape *>(item);
        if (technicsShape) {
            technicsShape->scaleTechnicsShape(value.toRectF());
        }
        break;
    }
    case DeviceShape::Type: {
        DeviceShape *deviceShape = dynamic_cast<DeviceShape *>(item);
        if (deviceShape) {
            deviceShape->scaleDeviceShape(value.toRectF());
        }
        break;
    }
    case BuildingStruct::Type: {
        BuildingStruct *buildingItem = dynamic_cast<BuildingStruct *>(item);
        if (buildingItem) {
            QRectF itemRect = value.toRectF();
            buildingItem->setRect(itemRect);
        }
    }
    default:
        break;
    }
}
