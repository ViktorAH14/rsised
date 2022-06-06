/*
 * Copyright (c) 2022 by Viktor Ermolov <ermolovva@gmail.com>.
 *
 * This file is part of the RSiSed project, a editor of the alignment of forces
 * and means in extinguishing a fire. (RSiSed)
 *
 * RSiSed is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * RSiSed is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <https://www.gnu.org/licenses/>.
 */

#include "item_resizer.h"
#include "rectshape.h"
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
    case RectShape::Type: {
        RectShape *rectShape = dynamic_cast<RectShape *>(item);
        if (rectShape) {
            QRectF shapeRect = value.toRectF();
            rectShape->setRect(shapeRect);
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
            technicsShape->scaleShape(value.toRectF());
        }
        break;
    }
    case DeviceShape::Type: {
        DeviceShape *deviceShape = dynamic_cast<DeviceShape *>(item);
        if (deviceShape) {
            deviceShape->scaleShape(value.toRectF());
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
