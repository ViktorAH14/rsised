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

#include "../include/shaperesizer.h"
#include "../include/rectshape.h"
#include "../include/ellipseshape.h"
#include "../include/curve.h"
#include "../include/polylineshape.h"
#include "../include/pixmapshape.h"
#include "../include/technicsshape.h"
#include "../include/deviceshape.h"
#include "../include/buildingshape.h"

#include <QPainterPath>

Q_DECLARE_METATYPE(QPainterPath)

void ShapeResizer::operator()(QGraphicsItem *item, const QVariant &value)
{
    switch (item->type()) {
    case RectShape::Type: {
        if (RectShape *p_rectShape = dynamic_cast<RectShape *>(item))
            p_rectShape->setRect(value.toRectF());
        break;
    }
    case EllipseShape::Type: {
        if (EllipseShape *p_ellipseShape = dynamic_cast<EllipseShape *>(item)) {
            p_ellipseShape->setRect(value.toRectF());
        }
        break;
    }
    case Curve::Type: {
        if (Curve *p_curveShape = dynamic_cast<Curve *>(item))
            p_curveShape->setPath(value.value<QPainterPath>());
        break;
    }
    case PolylineShape::Type: {
        if (PolylineShape *polylineShape = dynamic_cast<PolylineShape *>(item))
            polylineShape->setPath(value.value<QPainterPath>());
        break;
    }
    case PixmapShape::Type: {
        if (PixmapShape *pixmapShape = dynamic_cast<PixmapShape *>(item))
            pixmapShape->scalePixmap(value.toRectF());
        break;
    }
    case TankerShape::Type: {
        if (TankerShape *tankerShape = dynamic_cast<TankerShape *>(item))
            tankerShape->setRect(value.toRectF());
        break;
    }
    case BaseShape::Type: {
        if (BaseShape *baseShape = dynamic_cast<BaseShape *>(item))
            baseShape->setRect(value.toRectF());
        break;
    }
    case PumpHoseShape::Type: {
        if (PumpHoseShape *pumpHoseShape = dynamic_cast<PumpHoseShape *>(item))
            pumpHoseShape->setRect(value.toRectF());
        break;
    }
    case FirstAidShape::Type: {
        if (FirstAidShape *firstAidShape = dynamic_cast<FirstAidShape *>(item))
            firstAidShape->setRect(value.toRectF());
        break;
    }
    case EmergencyShape::Type: {
        if (EmergencyShape *emergencyShape = dynamic_cast<EmergencyShape *>(item))
            emergencyShape->setRect(value.toRectF());
        break;
    }
    case AutoLadderShape::Type: {
        if (AutoLadderShape *autoLadderShape = dynamic_cast<AutoLadderShape *>(item))
            autoLadderShape->setRect(value.toRectF());
        break;
    }
    case CrankLiftShape::Type: {
        if (CrankLiftShape *crankLiftShape = dynamic_cast<CrankLiftShape *>(item))
            crankLiftShape->setRect(value.toRectF());
        break;
    }
    case TelescopicLiftShape::Type: {
        if (TelescopicLiftShape *telescopicLiftShape = dynamic_cast<TelescopicLiftShape *>(item))
            telescopicLiftShape->setRect(value.toRectF());
        break;
    }
    case HoseCarShape::Type: {
        if (HoseCarShape *hoseCarShape = dynamic_cast<HoseCarShape *>(item))
            hoseCarShape->setRect(value.toRectF());
        break;
    }
    case CommShape::Type: {
        if (CommShape *commShape = dynamic_cast<CommShape *>(item))
            commShape->setRect(value.toRectF());
        break;
    }
    case DeviceShape::Type: {
        if (DeviceShape *deviceShape = dynamic_cast<DeviceShape *>(item))
            deviceShape->scaleShape(value.toRectF());
        break;
    }
    case WallShape::Type: {
        if (WallShape *wallShape = dynamic_cast<WallShape *>(item))
            wallShape->setRect(value.toRectF());
        break;
    }
    case DoorShape::Type: {
        if (DoorShape *p_doorShape = dynamic_cast<DoorShape *>(item))
            p_doorShape->setRect(value.toRectF());
        break;
    }
    case WindowShape::Type: {
        if (WindowShape *p_windowShape = dynamic_cast<WindowShape *>(item))
            p_windowShape->setRect(value.toRectF());
        break;
    }
    case OpenShape::Type: {
        if (OpenShape *p_openShape = dynamic_cast<OpenShape *>(item))
            p_openShape->setRect(value.toRectF());
        break;
    }
    case StairwellShape::Type: {
        if (StairwellShape *p_stairwellShape = dynamic_cast<StairwellShape *>(item))
            p_stairwellShape->setRect(value.toRectF());
        break;
    }
    case StairsShape::Type: {
        if (StairsShape *p_stairsShape = dynamic_cast<StairsShape *>(item))
            p_stairsShape->setRect(value.toRectF());
        break;
    }
    default:
        break;
    }
}
