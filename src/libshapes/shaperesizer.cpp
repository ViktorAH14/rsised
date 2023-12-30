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
        if (TankerShape *p_tankerShape = dynamic_cast<TankerShape *>(item))
            p_tankerShape->setRect(value.toRectF());
        break;
    }
    case BaseShape::Type: {
        if (BaseShape *p_baseShape = dynamic_cast<BaseShape *>(item))
            p_baseShape->setRect(value.toRectF());
        break;
    }
    case PumpHoseShape::Type: {
        if (PumpHoseShape *p_pumpHoseShape = dynamic_cast<PumpHoseShape *>(item))
            p_pumpHoseShape->setRect(value.toRectF());
        break;
    }
    case FirstAidShape::Type: {
        if (FirstAidShape *p_firstAidShape = dynamic_cast<FirstAidShape *>(item))
            p_firstAidShape->setRect(value.toRectF());
        break;
    }
    case EmergencyShape::Type: {
        if (EmergencyShape *p_emergencyShape = dynamic_cast<EmergencyShape *>(item))
            p_emergencyShape->setRect(value.toRectF());
        break;
    }
    case AutoLadderShape::Type: {
        if (AutoLadderShape *p_autoLadderShape = dynamic_cast<AutoLadderShape *>(item))
            p_autoLadderShape->setRect(value.toRectF());
        break;
    }
    case CrankLiftShape::Type: {
        if (CrankLiftShape *p_crankLiftShape = dynamic_cast<CrankLiftShape *>(item))
            p_crankLiftShape->setRect(value.toRectF());
        break;
    }
    case TelescopicLiftShape::Type: {
        if (TelescopicLiftShape *p_telescopicLiftShape = dynamic_cast<TelescopicLiftShape *>(item))
            p_telescopicLiftShape->setRect(value.toRectF());
        break;
    }
    case HoseCarShape::Type: {
        if (HoseCarShape *p_hoseCarShape = dynamic_cast<HoseCarShape *>(item))
            p_hoseCarShape->setRect(value.toRectF());
        break;
    }
    case CommShape::Type: {
        if (CommShape *p_commShape = dynamic_cast<CommShape *>(item))
            p_commShape->setRect(value.toRectF());
        break;
    }
    case TechServShape::Type: {
        if (TechServShape *p_techServShape = dynamic_cast<TechServShape *>(item))
            p_techServShape->setRect(value.toRectF());
        break;
    }
    case SmokRemShape::Type: {
        if (SmokRemShape *p_smokRemShape = dynamic_cast<SmokRemShape *>(item))
            p_smokRemShape->setRect(value.toRectF());
        break;
    }
    case PumpStatShape::Type: {
        if (PumpStatShape *p_pumpStatShape = dynamic_cast<PumpStatShape *>(item))
            p_pumpStatShape->setRect(value.toRectF());
        break;
    }
    case LafetTankerShape::Type: {
        if (LafetTankerShape *p_lafetTankerShape = dynamic_cast<LafetTankerShape *>(item))
            p_lafetTankerShape->setRect(value.toRectF());
        break;
    }
    case LafetCarShape::Type: {
        if (LafetCarShape *p_lafetCarShape = dynamic_cast<LafetCarShape *>(item))
            p_lafetCarShape->setRect(value.toRectF());
        break;
    }
    case AerodromeShape::Type: {
        if (AerodromeShape *p_aerodromeShape = dynamic_cast<AerodromeShape *>(item))
            p_aerodromeShape->setRect(value.toRectF());
        break;
    }
    case FoamShape::Type: {
        if (FoamShape *p_foamShape = dynamic_cast<FoamShape *>(item))
            p_foamShape->setRect(value.toRectF());
        break;
    }
    case ComboShape::Type: {
        if (ComboShape *p_comboShape = dynamic_cast<ComboShape *>(item))
            p_comboShape->setRect(value.toRectF());
        break;
    }
    case AerosolShape::Type: {
        if (AerosolShape *p_aerosolShape = dynamic_cast<AerosolShape *>(item))
            p_aerosolShape->setRect(value.toRectF());
        break;
    }
    case PowderShape::Type: {
        if (PowderShape *p_powderShape = dynamic_cast<PowderShape *>(item))
            p_powderShape->setRect(value.toRectF());
        break;
    }
    case CarbonShape::Type: {
        if (CarbonShape *p_carbonShape = dynamic_cast<CarbonShape *>(item))
            p_carbonShape->setRect(value.toRectF());
        break;
    }
    case GazWaterShape::Type: {
        if (GazWaterShape *p_gazWaterShape = dynamic_cast<GazWaterShape *>(item))
            p_gazWaterShape->setRect(value.toRectF());
        break;
    }
    case TrackedShape::Type: {
        if (TrackedShape *p_trackedShape = dynamic_cast<TrackedShape *>(item))
            p_trackedShape->setRect(value.toRectF());
        break;
    }
    case TankShape::Type: {
        if (TankShape *p_tankShape = dynamic_cast<TankShape *>(item))
            p_tankShape->setRect(value.toRectF());
        break;
    }
    case GdzsShape::Type: {
        if (GdzsShape *p_gdzsShape = dynamic_cast<GdzsShape *>(item))
            p_gdzsShape->setRect(value.toRectF());
        break;
    }
    case WaterproofShape::Type: {
        if (WaterproofShape *p_waterproofShape = dynamic_cast<WaterproofShape *>(item))
            p_waterproofShape->setRect(value.toRectF());
        break;
    }
    case LaboratoryShape::Type: {
        if (LaboratoryShape *p_laboratoryShape = dynamic_cast<LaboratoryShape *>(item))
            p_laboratoryShape->setRect(value.toRectF());
        break;
    }
    case StaffCarShape::Type: {
        if (StaffCarShape *p_staffCarShape = dynamic_cast<StaffCarShape *>(item))
            p_staffCarShape->setRect(value.toRectF());
        break;
    }
    case TrailerShape::Type: {
        if (TrailerShape *p_trailerShape = dynamic_cast<TrailerShape *>(item))
            p_trailerShape->setRect(value.toRectF());
        break;
    }
    case ShipShape::Type: {
        if (ShipShape *p_shipShape = dynamic_cast<ShipShape *>(item))
            p_shipShape->setRect(value.toRectF());
        break;
    }
    case BoatShape::Type: {
        if (BoatShape *p_boatShape = dynamic_cast<BoatShape *>(item))
            p_boatShape->setRect(value.toRectF());
        break;
    }
    case TrainShape::Type: {
        if (TrainShape *p_trainShape = dynamic_cast<TrainShape *>(item))
            p_trainShape->setRect(value.toRectF());
        break;
    }
    case PlaneShape::Type: {
        if (PlaneShape *p_planeShape = dynamic_cast<PlaneShape *>(item))
            p_planeShape->setRect(value.toRectF());
        break;
    }
    case SeaplaneShape::Type: {
        if (SeaplaneShape *seaplaneShape = dynamic_cast<SeaplaneShape *>(item))
            seaplaneShape->setRect(value.toRectF());
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
