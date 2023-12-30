/*
 * Copyright (c) 2022 by Viktor Ermolov <ermolovva@gmail.com>.
 *
 * This file is part of the RSiSed project, an editor of the alignment of forces
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

#include "../include/technicsshape.h"

#include <QPainter>
#include <QMenu>
#include <QGraphicsSceneEvent>
#include <QStyleOptionGraphicsItem>
#include <QtMath>

TechnicsShape::TechnicsShape(QGraphicsItem *parent)
    : AbstractShape(parent)
{
}

TechnicsShape::~TechnicsShape() = default;

void TechnicsShape::deleter()
{
    delete this;
}

QPolygonF TechnicsShape::basePolygon(const QRectF &rect) const
{
    qreal frontTab{rect.height() / 3};
    QPointF frontCenter{rect.center().x(), rect.top()}; // 0.0, -37.5
    QPointF frontRight{rect.right(), rect.top() + frontTab}; // 15.0, -12.5
    QPointF frontLeft{rect.left(), rect.top() + frontTab}; // -15.0, -12.5
    QPointF bottomRight{rect.bottomRight()}; // 15.0, 37.5
    QPointF bottomLeft{rect.bottomLeft()}; // -15.0, 37.5
    QPolygonF basePolygon;
    basePolygon << frontCenter << frontRight << bottomRight << bottomLeft << frontLeft;
    return basePolygon;
}

TechnicsShape *TechnicsShape::createTechnicsShape(ShapeType shapeType, QGraphicsItem *parent)
{
    TechnicsShape *p_technicsShape{nullptr};
    switch (shapeType) {
    case Base:
        p_technicsShape = new BaseShape(parent);
        break;
    case Tanker:
        p_technicsShape = new TankerShape(parent);
        break;
    case PumpHose:
        p_technicsShape = new PumpHoseShape(parent);
        break;
    case FirstAid:
        p_technicsShape = new FirstAidShape(parent);
        break;
    case Emergency:
        p_technicsShape = new EmergencyShape(parent);
        break;
    case AutoLadder:
        p_technicsShape = new AutoLadderShape(parent);
        break;
    case CrankLift:
        p_technicsShape = new CrankLiftShape(parent);
        break;
    case TelescopicLift:
        p_technicsShape = new TelescopicLiftShape(parent);
        break;
    case HoseCar:
        p_technicsShape = new HoseCarShape(parent);
        break;
    case Comm:
        p_technicsShape = new CommShape(parent);
        break;
    case TechServ:
        p_technicsShape = new TechServShape(parent);
        break;
    case SmokRem:
        p_technicsShape = new SmokRemShape(parent);
        break;
    case PumpStat:
        p_technicsShape = new PumpStatShape(parent);
        break;
    case LafetTanker:
        p_technicsShape = new LafetTankerShape(parent);
        break;
    case LafetCar:
        p_technicsShape = new LafetCarShape(parent);
        break;
    case Aerodrome:
        p_technicsShape = new AerodromeShape(parent);
        break;
    case Foam:
        p_technicsShape = new FoamShape(parent);
        break;
    case Combo:
        p_technicsShape = new ComboShape(parent);
        break;
    case Aerosol:
        p_technicsShape = new AerosolShape(parent);
        break;
    case Powder:
        p_technicsShape = new PowderShape(parent);
        break;
    case Carbon:
        p_technicsShape = new CarbonShape(parent);
        break;
    case GazWater:
        p_technicsShape = new GazWaterShape(parent);
        break;
    case Tracked:
        p_technicsShape = new TrackedShape(parent);
        break;
    case Tank:
        p_technicsShape = new TankShape(parent);
        break;
    case GDZS:
        p_technicsShape = new GdzsShape(parent);
        break;
    case Waterproof:
        p_technicsShape = new WaterproofShape(parent);
        break;
    case Laboratory:
        p_technicsShape = new LaboratoryShape(parent);
        break;
    case StaffCar:
        p_technicsShape = new StaffCarShape(parent);
        break;
    case Trailer:
        p_technicsShape = new TrailerShape(parent);
        break;
    case Ship:
        p_technicsShape = new ShipShape(parent);
        break;
    case Boat:
        p_technicsShape = new BoatShape(parent);
        break;
    case Train:
        p_technicsShape = new TrainShape(parent);
        break;
    case Plane:
        p_technicsShape = new PlaneShape(parent);
        break;
    case Seaplane:
        p_technicsShape = new SeaplaneShape(parent);
        break;
    default:
        break;
    }
    return p_technicsShape;
}

//void TechnicsShape::drawShape(QPainter *painter)
//{
//    painter->setRenderHint(QPainter::Antialiasing);
//    painter->setRenderHint(QPainter::SmoothPixmapTransform);

//    QPolygonF autoBase;
//    autoBase << QPointF(0.0, -37.5) << QPointF(15.0, -12.5) << QPointF(15.0, 37.5)
//            << QPointF(-15.0, 37.5) << QPointF(-15.0, -12.5) << QPointF(0.0, -37.5);

//    QPolygonF shipPolygon;
//    shipPolygon << QPointF(0.0, 37.5) << QPointF(15.0, 20.0) << QPointF(15.0, -20.0)
//                  << QPointF(0.0, -37.5) << QPointF(-15.0, -20.0) << QPointF(-15.0, 20.0);

//    QPainterPath planePath;
//    planePath.moveTo(-10.0, 37.5);
//    planePath.lineTo(10.0, 37.5);
//    planePath.arcTo(5.0, 27.5, 10.0, 10.0, 270.0, 180.0);
//    planePath.lineTo(5.0, 27.5);
//    planePath.lineTo(5.0, 5.0);
//    planePath.lineTo(25.0, 5.0);
//    planePath.arcTo(20.0, -5.0, 10.0, 10.0, 270.0, 180.0);
//    planePath.lineTo(5.0, -5.0);
//    planePath.lineTo(5.0, -32.0);
//    planePath.arcTo(-5.0, -37.0, 10.0, 10.0, 0.0, 180.0);
//    planePath.lineTo(-5.0, -5.0);
//    planePath.lineTo(-25.0, -5.0);
//    planePath.arcTo(-30.0, -5.0, 10.0, 10.0, 90.0, 180.0);
//    planePath.lineTo(-5.0, 5.0);
//    planePath.lineTo(-5.0, 27.5);
//    planePath.lineTo(-10.0, 27.5);
//    planePath.arcTo(-15.0, 27.5, 10.0, 10.0, 90.0, 180.0);

//    painter->setBrush(QBrush(Qt::white));
//    switch (m_shapeType) {
//    case Base: {
//        painter->setPen(QPen(Qt::red, 1));
//        painter->drawPolygon(autoBase);
//        break;
//    }
//    case Tanker: {
//        painter->setPen(QPen(Qt::red, 1));
//        painter->drawPolygon(autoBase);
//        painter->drawRoundedRect(-10.0, -12.0, 20.0, 45.0, 5.0, 5.0);
//        break;
//    }
//    case AutoPump: {
//        QPolygonF pump;
//        pump << QPointF(-10.0, 37.5) << QPointF(-10.0, 25.0) << QPointF(10.0, 25.0)
//             << QPointF(10.0, 37.5);
//        painter->setPen(QPen(Qt::red, 1));
//        painter->drawPolygon(autoBase);
//        painter->drawPolygon(pump);
//        break;
//    }
//    case FirstAid: {
//        painter->setPen(QPen(Qt::red, 1));
//        painter->drawPolygon(autoBase);
//        painter->rotate(-90);
//        painter->drawText(QPointF(-32.0, 4.0), QString("ПП"));
//        break;
//    }
//    case Emergency: {
//        painter->setPen(QPen(Qt::red, 1));
//        painter->drawPolygon(autoBase);
//        painter->rotate(-90);
//        painter->drawText(QPointF(-32.0, 4.0), QString("АС"));
//        break;
//    }
//    case AutoLadder: {
//        painter->setPen(QPen(Qt::red, 1));
//        painter->drawPolygon(autoBase);
//        QVector<QLineF> ladder;
//        ladder.append(QLineF(-10.0, 32.5, -10.0, -12.5));
//        ladder.append(QLineF(10.0, 32.5, 10.0, -12.5));
//        ladder.append(QLineF(-10.0, 25.0, 10.0, 25.0));
//        ladder.append(QLineF(-10.0, 20.0, 10.0, 20.0));
//        ladder.append(QLineF(-10.0, 15.0, 10.0, 15.0));
//        ladder.append(QLineF(-10.0, 10.0, 10.0, 10.0));
//        ladder.append(QLineF(-10.0, 5.0, 10.0, 5.0));
//        ladder.append(QLineF(-10.0, 0.0, 10.0, 0.0));
//        ladder.append(QLineF(-10.0, -5.0, 10.0, -5.0));
//        painter->drawLines(ladder);
//        break;
//    }
//    case CrankLift: {
//        painter->setPen(QPen(Qt::red, 1));
//        painter->drawPolygon(autoBase);
//        QPolygonF crank;
//        crank << QPointF(-10.0, -12.5) << QPointF(-10.0, 32.5) << QPointF(10.0, -12.5)
//              <<QPointF(10.0, 32.5);
//        painter->drawPolyline(crank);
//        break;
//    }
//    case TelescopicLift: {
//        painter->setPen(QPen(Qt::red, 1));
//        painter->drawPolygon(autoBase);
//        QVector<QLineF> telescopic;
//        telescopic.append(QLineF(-10.0, 32.5, -10.0, -12.5));
//        telescopic.append(QLineF(0.0, 20.0, 0.0, -25.0));
//        telescopic.append(QLineF(10.0, 32.5, 10.0, -12.5));
//        painter->drawLines(telescopic);
//        break;
//    }
//    case Hose: {
//        painter->setPen(QPen(Qt::red, 1));
//        painter->drawPolygon(autoBase);
//        painter->rotate(-90);
//        painter->drawText(QPointF(-20.0, 4.0), QString("Р"));
//        break;
//    }
//    case Comm: {
//        painter->setPen(QPen(Qt::red, 1));
//        painter->drawPolygon(autoBase);
//        painter->rotate(-90);
//        painter->drawText(QPointF(-20.0, 4.0), QString("CO"));
//        break;
//    }
//    case Tech_serv: {
//        painter->setPen(QPen(Qt::red, 1));
//        painter->drawPolygon(autoBase);
//        painter->rotate(-90);
//        painter->drawText(QPointF(-20.0, 4.0), QString("Т"));
//        break;
//    }
//    case Smok_rem: {
//        painter->setPen(QPen(Qt::red, 1));
//        painter->drawPolygon(autoBase);
//        painter->drawEllipse(QPointF(0.0, 10.0), 10.0, 10.0);
//        painter->drawLine(QLineF(-8.0, 15.0, 8.0, 5.0));  //inside ellipse, left bottom - right top
//        painter->drawLine(QLineF(8.0, 5.0, 2.0, 1.0));    //inside ellipse, right-right
//        painter->drawLine(QLineF(2.0, 1.0, -2.0, 19.0));  //inside ellipse, right top - left botttom
//        painter->drawLine(QLineF(-2.0, 19.0, -8.0, 15.0));    //inside ellipse, left-left
//        break;
//    }
//    case AutoPumpS: {
//        QPolygonF pump;
//        pump << QPointF(-10.0, 37.5) << QPointF(-10.0, 25.0) << QPointF(10.0, 25.0)
//             << QPointF(10.0, 37.5);
//        painter->setPen(QPen(Qt::red, 1));
//        painter->drawPolygon(autoBase);
//        painter->drawPolygon(pump);
//        painter->rotate(-90);
//        painter->drawText(QPointF(-20.0, 4.0), QString("С"));
//        break;
//    }
//    case CarriageCar_1: {
//        painter->setPen(QPen(Qt::red, 1));
//        painter->drawPolygon(autoBase);
//        painter->drawRoundedRect(-10.0, -12.0, 20.0, 45.0, 5.0, 5.0);
//        painter->drawLine(QLineF(-15.0, 37.5, -30.0, -10.0));    //barrel
//        painter->drawLine(QLineF(-32.0, -3.0, -30.0, -10.0));    //left part arrow
//        painter->drawLine(QLineF(-30.0, -10.0, -24.5, -6.0));    //right part arrow
//        painter->drawLine(QLineF(-20.0, 20.0, -15.0, 20.0));    //stand
//        break;
//    }
//    case CarriageCar_2: {
//        painter->setPen(QPen(Qt::red, 1));
//        painter->drawPolygon(autoBase);
//        painter->drawLine(QLineF(15.0, 37.5, -8.0, -10.0));    //barrel
//        painter->drawLine(QLineF(-10.0, -3.0, -8.0, -10.0));    //left part arrow
//        painter->drawLine(QLineF(-8.0, -10.0, -1.5, -7.0));    //right part arrow
//        painter->drawLine(QLineF(7.0, 20.0, 15.0, 20.0));    //stand
//        break;
//    }
//    case Aerodrome: {
//        painter->setPen(QPen(Qt::red, 1));
//        painter->drawPolygon(autoBase);
//        painter->rotate(-90);
//        painter->drawText(QPointF(-20.0, 4.0), QString("А"));
//        break;
//    }
//    case Foam: {
//        painter->setPen(QPen(Qt::red, 1));
//        painter->drawPolygon(autoBase);
//        painter->drawEllipse(QPointF(0.0, 10.0), 10.0, 10.0);
//        painter->drawLine(QLineF(-7.0, 16.5, 7.0, 3.5));  //inside ellipse, left bottom - right top
//        painter->drawLine(QLineF(-7.0, 3.5, 7.0, 16.5));  //inside ellipse, left top - right botttom
//        break;
//    }
//    case Combo: {
//        painter->setPen(QPen(Qt::red, 1));
//        painter->drawPolygon(autoBase);
//        painter->drawEllipse(QPointF(0.0, 23.0), 10.0, 10.0);
//        painter->drawLine(QLineF(-7.0, 29.5, 7.0, 16.5));  //inside ellipse, left bottom - right top
//        painter->drawLine(QLineF(-7.0, 16.5, 7.0, 29.5));  //inside ellipse, left top - right botttom
//        painter->setBrush(QBrush(Qt::red));
//        painter->drawRect(-10.0, -11.0, 20.0, 20.0);
//        break;
//    }
//    case Aerosol: {
//        painter->setPen(QPen(Qt::red, 1));
//        painter->drawPolygon(autoBase);
//        painter->setBrush(QBrush(Qt::red));
//        painter->drawEllipse(QPointF(0.0, 26.0), 7.0, 7.0);  // bottom ellipse
//        painter->drawEllipse(QPointF(0.0, 9.0), 7.0, 7.0);  // center ellipse
//        painter->drawEllipse(QPointF(0.0, -8.0), 7.0, 7.0);  // top ellipse
//        break;
//    }
//    case Powder: {
//        painter->setPen(QPen(Qt::red, 1));
//        painter->drawPolygon(autoBase);
//        painter->setBrush(QBrush(Qt::red));
//        painter->drawRect(-10.0, 13.0, 20.0, 20.0);
//        break;
//    }
//    case Carbon: {
//        painter->setPen(QPen(Qt::red, 1));
//        painter->drawPolygon(autoBase);
//        QPolygonF carbonPolygon;
//        carbonPolygon << QPointF(-10.0, 26.0) << QPointF(10.0, 26.0) << QPointF(0.0, 6.0);
//        painter->setBrush(QBrush(Qt::red));
//        painter->drawPolygon(carbonPolygon);
//        break;
//    }
//    case GazWater: {
//        painter->setPen(QPen(Qt::red, 1));
//        painter->drawPolygon(autoBase);
//        painter->rotate(-90);
//        painter->drawText(QPointF(-32.0, 4.0), QString("ГВТ"));
//        break;
//    }
//    case Tracked: {
//        painter->setPen(QPen(Qt::red, 1));
//        painter->drawPolygon(autoBase);
//        painter->drawLine(QLineF(-10.0, 37.5, -10.0, -20.5));
//        painter->drawLine(QLineF(10.0, 37.5, 10.0, -20.5));
//        break;
//    }
//    case Tank: {
//        painter->setPen(QPen(Qt::red, 1));
//        QPolygonF tankPolygon;
//        tankPolygon << QPointF(0.0, 37.5) << QPointF(18.0, 0.0) << QPointF(0.0, -37.5)
//                    << QPointF(-18.0, 0.0);
//        painter->drawPolygon(tankPolygon);
//        break;
//    }
//    case GDZS: {
//        painter->setPen(QPen(Qt::red, 1));
//        painter->drawPolygon(autoBase);
//        painter->rotate(-90);
//        painter->drawText(QPointF(-32.0, 4.0), QString("ГДЗС"));
//        break;
//    }
//    case Waterproof: {
//        painter->setPen(QPen(Qt::red, 1));
//        painter->drawPolygon(autoBase);
//        painter->rotate(-90);
//        painter->drawText(QPointF(-32.0, 4.0), QString("ВЗ"));
//        break;
//    }
//    case Laboratory: {
//        painter->setPen(QPen(Qt::red, 1));
//        painter->drawPolygon(autoBase);
//        painter->rotate(-90);
//        painter->drawText(QPointF(-32.0, 4.0), QString("ЛБ"));
//        break;
//    }
//    case StaffCar: {
//        painter->setPen(QPen(Qt::red, 1));
//        painter->drawPolygon(autoBase);
//        painter->rotate(-90);
//        painter->drawText(QPointF(-20.0, 4.0), QString("Ш"));
//        break;
//    }
//    case Trailer: {
//        painter->setPen(QPen(Qt::red, 1));
//        painter->drawLine(QLineF(-20.0, 37.0, -20.0, 29.0));    //left cartwheel
//        painter->drawLine(QLineF(-20.0, 33.0, 20.0, 33.0));    //bottom
//        painter->drawLine(QLineF(20.0, 37.0, 20.0, 29.0));    //right cartwheel
//        painter->drawLine(QLineF(-15.0, 33.0, -15.0, -12.0));    //left
//        painter->drawLine(QLineF(-15.0, -12.0, 15.0, -12.0));    //top
//        painter->drawLine(QLineF(15.0, -12.0, 15.0, 33.0));    //right
//        painter->drawLine(QLineF(0.0, -12.0, 0.0, -25.0));    //center
//        break;
//    }
//    case Ship: {
//        painter->setPen(QPen(Qt::red, 1));
//        painter->drawPolygon(shipPolygon);
//        painter->rotate(-90);
//        painter->drawText(QPointF(-5.0, 4.0), QString("С"));
//        break;
//    }
//    case Boat: {
//        painter->setPen(QPen(Qt::red, 1));
//        painter->drawPolygon(shipPolygon);
//        painter->rotate(-90);
//        painter->drawText(QPointF(-5.0, 4.0), QString("К"));
//        break;
//    }
//    case Train: {
//        QPolygonF train;
//        train << QPointF(-15.0, 25.0) << QPointF(-15.0, 10.0) << QPointF(-7.0, 10.0)
//              << QPointF(-7.0, -25.0) << QPointF(7.0, -25.0) << QPointF(7.0, 10.0)
//              << QPointF(15.0, 10.0) << QPointF(15.0, 25.0);
//        painter->setPen(QPen(Qt::red, 1));
//        painter->setBrush(QBrush(Qt::red));
//        painter->drawPolygon(train);
//        break;
//    }
//    case Plane: {
//        painter->setPen(QPen(Qt::red, 1));
//        painter->setBrush(QBrush(Qt::red));
//        painter->drawPath(planePath);
//        break;
//    }
//    case Seaplane: {
//        painter->setPen(QPen(Qt::red, 1));
//        painter->setBrush(QBrush(Qt::red));
//        painter->drawPath(planePath);
//        painter->setPen(QPen(Qt::red, 2));
//        painter->drawLine(QLineF(-20.0, 10.0, -20.0, -10.0));   //left line
//        painter->drawLine(QLineF(20.0, 10.0, 20.0, -10.0));   //right line
//        break;
//    }
//    case Helicopter: {
//        painter->setPen(QPen(Qt::red, 2));
//        painter->drawLine(QLineF(0.0, 37.5, 10.0, 27.5));    //bottom left - top right, small propeller
//        painter->drawLine(QLineF(0.0, 27.5, 10.0, 37.5));    //top left - bottom right, small propeller
//        painter->drawLine(QLineF(0.0, 27.5, 0.0, -4.0));    //tail
//        painter->drawLine(QLineF(0.0, -4.0, 24.0, -28.0));    //bottom left - top right, big propeller
//        painter->drawLine(QLineF(0.0, -28.0, 24.0, -4.0));    //top left - bottom right, big propeller
//        QRectF cabinRect(-7.5, -28.0, 14.0, 24.0);
//        int startAngle = 90 * 16;
//        int spanAngle = 180 * 16;
//        painter->drawArc(cabinRect, startAngle, spanAngle);    //cabin
//        break;
//    }
//    case MotoPump_1: {
//        painter->setPen(QPen(Qt::red, 1));
//        painter->drawRect(-20.0, -30.0, 40.0, 60.0);
//        painter->drawLine(-10.0, 30.0, -10.0, 20.0);    //left pump line
//        painter->drawLine(-10.0, 20.0, 10.0, 20.0); //horizontal pump line
//        painter->drawLine(10.0, 20.0, 10.0, 30.0); //right pump line
//        break;
//    }
//    case MotoPump_2: {
//        painter->setPen(QPen(Qt::red, 1));
//        painter->drawRect(-20.0, -30.0, 40.0, 60.0);
//        painter->drawLine(-10.0, 30.0, -10.0, 20.0);    //left pump line
//        painter->drawLine(-10.0, 20.0, 10.0, 20.0); //horizontal pump line
//        painter->drawLine(10.0, 20.0, 10.0, 30.0); //right pump line
//        painter->drawLine(-25.0, 30.0, -20.0, 30.0); //left axle
//        painter->drawLine(-25.0, 35.0, -25.0, 25.0); //left cartwheel
//        painter->drawLine(20.0, 30.0, 25.0, 30.0); //right axle
//        painter->drawLine(25.0, 35.0, 25.0, 25.0); //right cartwheel
//        break;
//    }
//    case TrailerPowder: {
//        painter->setPen(QPen(Qt::red, 1));
//        painter->drawRect(-20.0, -30.0, 40.0, 60.0);
//        painter->drawLine(-25.0, 30.0, -20.0, 30.0); //left axle
//        painter->drawLine(-25.0, 35.0, -25.0, 25.0); //left cartwheel
//        painter->drawLine(20.0, 30.0, 25.0, 30.0); //right axle
//        painter->drawLine(25.0, 35.0, 25.0, 25.0); //right cartwheel
//        painter->setBrush(QBrush(Qt::red));
//        painter->drawRect(-10.0, -10.0, 20.0, 20.0);
//        break;
//    }
//    case Adapted: {
//        painter->setPen(QPen(Qt::blue, 1));
//        painter->drawPolygon(autoBase);
//        QPolygonF adaptedPolygon;
//        adaptedPolygon << QPointF(-8.0, 36.5) << QPointF(-8.0, -22.5) << QPointF(0.0, -36.0)
//                       << QPointF(8.0, -22.5) << QPointF(8.0, 36.5);
//        painter->setPen(QPen(Qt::red, 1));
//        painter->setBrush(QBrush(Qt::red));
//        painter->drawPolygon(adaptedPolygon);
//        break;
//    }
//    case OtherAdapted: {
//        painter->setPen(QPen(Qt::blue, 1));
//        painter->drawRect(QRectF(-15.0, -10.0, 30.0, 41));
//        painter->drawLine(QLineF(0.0, -10.0, 0.0, -30.0));
//        painter->drawEllipse(QRectF(-4.0, -38.0, 8.0, 8.0));
//        painter->setPen(QPen(Qt::red, 1));
//        painter->setBrush(QBrush(Qt::red));
//        painter->drawRect(QRectF(-8.0, -9.0, 16.0, 39.0));
//        break;
//    }
//    case Ambulance: {
//        painter->setPen(QPen(Qt::black, 1));
//        painter->drawPolygon(autoBase);
//        QPolygonF ambulancePolygon;
//        ambulancePolygon << QPointF(-3.0, 9.0) << QPointF(-3.0, 3.0) << QPointF(-9.0, 3.0)
//                         << QPointF(-9.0, -3.0) << QPointF(-3.0, -3.0) << QPointF(-3.0, -9.0)
//                         << QPointF(3.0, -9.0) << QPointF(3.0, -3.0) << QPointF(9.0, -3.0)
//                         << QPointF(9.0, 3.0) << QPointF(3.0, 3.0) << QPointF(3.0, 9.0);
//        painter->setPen(QPen(Qt::red, 1));
//        painter->setBrush(QBrush(Qt::red));
//        painter->drawPolygon(ambulancePolygon);
//        break;
//    }
//    case Police: {
//        painter->setPen(QPen(Qt::black, 1));
//        painter->drawPolygon(autoBase);
//        painter->rotate(-90);
//        painter->drawText(QPointF(-32.0, 4.0), "МВД");
//        break;
//    }
//    default:
//        break;
//    }
//}

BaseShape::BaseShape(QGraphicsItem *parent)
    : TechnicsShape(parent)
    , m_baseType{Base}
    , m_baseRect{QRectF(-15.0, -37.5, 30.0, 75.0)}
    , m_baseText{nullptr}
    , m_showText{false}
{
    setFlag(ItemSendsGeometryChanges, true);
    setAcceptHoverEvents(true);
    setPen(QPen(Qt::red, 1));
    setBrush(QBrush(Qt::white));
}

void BaseShape::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(widget);

    painter->setRenderHint(QPainter::Antialiasing);
    painter->setRenderHint(QPainter::SmoothPixmapTransform);
    painter->setPen(pen());
    painter->setBrush(brush());

    painter->drawPolygon(basePolygon(rect()));

    if (m_showText)
        m_baseText->setPos(m_baseRect.right(), m_baseRect.bottom());

    if (option->state & QStyle::State_Selected)
        highlightSelected(painter, option);
}

QRectF BaseShape::boundingRect() const
{
    QRectF boundingRect{m_baseRect};
    qreal halfpw{pen().style() == Qt::NoPen ? qreal(0.0) : pen().widthF() / 2};
    if (halfpw > 0.0)
        boundingRect.adjust(-halfpw, -halfpw, halfpw, halfpw);

    return boundingRect;
}

QPainterPath BaseShape::shape() const
{
    QPainterPath path;
    path.addPolygon(basePolygon(rect()));

    return shapeFromPath(path);
}

QPixmap BaseShape::image()
{
    qreal pixmapWidth{boundingRect().width()};
    qreal pixmapHeight{boundingRect().height()};
    QPixmap pixmap(pixmapWidth, pixmapHeight);
    pixmap.fill(Qt::transparent);

    QPainter painter(&pixmap);
    painter.setPen(pen());
    painter.setBrush(brush());
    painter.translate(pixmapWidth / 2.0, pixmapHeight / 2.0);
    painter.drawPolygon(basePolygon(rect()));

    return pixmap;
}

TechnicsShape::ShapeType BaseShape::shapeType() const
{
    return m_baseType;
}

void BaseShape::setRect(const QRectF &rect)
{
    if (m_baseRect == rect)
        return;

    prepareGeometryChange();
    m_baseRect.setRect(rect.topLeft().x(), rect.topLeft().y(), rect.width(), rect.height());
    if (m_baseText != nullptr)
        m_baseText->setPos(m_baseRect.right(), m_baseRect.bottom() - m_baseRect.width() / 6);
}

QRectF BaseShape::rect() const
{
    return m_baseRect;
}

void BaseShape::setHeight(const qreal &height)
{
    if (m_baseRect.height() == height)
        return;

    qreal oldHeight{m_baseRect.height()};
    prepareGeometryChange();
    m_baseRect.setHeight(height);
    qreal dy{(m_baseRect.height() - oldHeight) / 2};
    m_baseRect.moveTo(QPointF(m_baseRect.x(), m_baseRect.y() - dy));
    update();
}

qreal BaseShape::height() const
{
    return m_baseRect.height();
}

void BaseShape::setText(const QString &text)
{
    if (m_baseText == nullptr) {
        m_baseText=new QGraphicsTextItem(this);
        m_baseText->setTextInteractionFlags(Qt::TextEditorInteraction);
        m_baseText->setRotation(-90);
    }
    m_baseText->setPlainText(text);
    m_showText = true;
}

QString BaseShape::text() const
{
    if (m_baseText == nullptr)
        return "";

    return m_baseText->toPlainText();
}

void BaseShape::mousePressEvent(QGraphicsSceneMouseEvent *mouseEvent)
{
    if (mouseEvent->buttons() == Qt::RightButton) {
        createAction();
        addActions(m_baseActionList);
        QAction menuAction{menu()->exec(mouseEvent->screenPos())};
        QString menuActionText;
        if (menuAction.parent()) {
            menuActionText = menuAction.parent()->objectName();
        }
        if ((menuActionText != "actionDeleteItem") && (menuActionText != "actionCut")) {
            removeActions(m_baseActionList);
            m_baseActionList.clear();
        }
    } else {
        AbstractShape::mousePressEvent(mouseEvent);
    }
}

void BaseShape::createAction()
{
    QString addText{m_showText ? QObject::tr("Hide text") : QObject::tr("Show text")};
    m_addTextAction.reset(new QAction(addText));
    m_addTextAction->setToolTip(QObject::tr("Show or hide text"));
    QObject::connect(m_addTextAction.get(), &QAction::triggered
                     , [this](){m_showText ? textShow(false) : textShow(true);});
    m_baseActionList.append(m_addTextAction.get());
}

void BaseShape::textShow(bool showText)
{
    if (showText) {
        if (m_baseText == nullptr) {
            m_baseText=new QGraphicsTextItem(this);
            m_baseText->setPlainText("ПА-");
            m_baseText->setTextInteractionFlags(Qt::TextEditorInteraction);
            m_baseText->setRotation(-90);
        }
        m_baseText->show();
        m_showText = true;
    } else {
        m_baseText->hide();
        m_showText = false;
    }
}

TankerShape::TankerShape(QGraphicsItem *parent)
    : TechnicsShape(parent)
    , m_tankerType{Tanker}
    , m_tankerText{nullptr}
    , m_tankerRect{QRectF(-15.0, -37.5, 30.0, 75.0)}
    , m_showPipes{false}
    , m_showCollector{false}
    , m_showText{false}
{
    setFlag(ItemSendsGeometryChanges, true);
    setAcceptHoverEvents(true);
    setPen(QPen(Qt::red, 1));
    setBrush(QBrush(Qt::white));
}

void TankerShape::drawPipes(QPainter *painter, qreal sixtWidth)
{
    painter->setPen(QPen(Qt::black, 1));
    qreal pipeY{m_tankerRect.bottom() - sixtWidth};
    QPointF rightPipeP1{m_tankerRect.right(), pipeY};
    QPointF rightPipeP2{m_tankerRect.right() + sixtWidth, pipeY};
    painter->drawLine(rightPipeP1, rightPipeP2); // Right pipe

    QPointF rightConnectP1{rightPipeP2.x(), rightPipeP2.y() + sixtWidth / 2};
    QPointF rightConnectP2{rightPipeP2.x(), rightPipeP2.y() - sixtWidth / 2};
    painter->drawLine(rightConnectP1, rightConnectP2); // Right pipe connection

    QPointF leftPipeP1{m_tankerRect.left(), pipeY};
    QPointF leftPipeP2{m_tankerRect.left() - sixtWidth, pipeY};
    painter->drawLine(leftPipeP1, leftPipeP2); // Left pipe

    QPointF leftConnectP1{leftPipeP2.x(), leftPipeP2.y() + sixtWidth / 2};
    QPointF leftConnectP2{leftPipeP2.x(), leftPipeP2.y() - sixtWidth / 2};
    painter->drawLine(leftConnectP1, leftConnectP2); // Right pipe connection
}

void TankerShape::drawCollector(QPainter *painter, qreal sixtWidth)
{
    painter->setPen(QPen(Qt::black, 1));
    qreal collectorX{m_tankerRect.center().x()};
    qreal collectorY{m_tankerRect.bottom() + sixtWidth * 2};
    qreal leftPipeX{collectorX - sixtWidth};
    QPointF leftRightPipeP1{collectorX, m_tankerRect.bottom()};
    QPointF leftPipeP2{leftPipeX, collectorY};
    painter->drawLine(leftRightPipeP1, leftPipeP2); //Left collector pipe

    qreal rightPipeX{collectorX + sixtWidth};
    QPointF rightPipeP2{rightPipeX, collectorY};
    painter->drawLine(leftRightPipeP1, rightPipeP2); //Right collector pipe

    QPointF leftConnectP1{leftPipeX - sixtWidth / 2, collectorY};
    QPointF leftConnectP2{leftPipeX + sixtWidth / 2, collectorY};
    painter->drawLine(leftConnectP1, leftConnectP2); //Left connector

    QPointF rightConnectP1{rightPipeX - sixtWidth / 2, collectorY};
    QPointF rightConnectP2{rightPipeX + sixtWidth / 2, collectorY};
    painter->drawLine(rightConnectP1, rightConnectP2);  //Right connector
}

void TankerShape::drawTankerShape(QPainter *painter)
{
    painter->drawPolygon(basePolygon(rect()));

    qreal sixthWidth{m_tankerRect.width() / 6}; // 5.0
    qreal thirdHeight{m_tankerRect.height() / 3};
    QPointF roundTopLeft{m_tankerRect.left() + sixthWidth, m_tankerRect.top() + thirdHeight}; // -10.0, -12.5
    QPointF roundBottomRight{m_tankerRect.right() - sixthWidth
                , m_tankerRect.bottom() - sixthWidth};
    painter->drawRoundedRect(QRectF(roundTopLeft, roundBottomRight), sixthWidth, sixthWidth);

    if (m_showText) {
        m_tankerText->setPos(m_tankerRect.right(), m_tankerRect.bottom() - sixthWidth * 2);
    }

    if (m_showPipes) {
        drawPipes(painter, sixthWidth);
    }

    if (m_showCollector) {
        drawCollector(painter, sixthWidth);
    }
}

void TankerShape::createAction()
{
    QString pipeActionText{m_showPipes ? QObject::tr("Hide pipes") : QObject::tr("Show pipes")};
    m_showPipeAction.reset(new QAction(pipeActionText));
    m_showPipeAction->setToolTip(QObject::tr("Show or hide the pipes"));
    QObject::connect(m_showPipeAction.get(), &QAction::triggered
                     , [this]() {m_showPipes ? setPipes(false) : setPipes(true);});
    m_tankerActionList.append(m_showPipeAction.get());

    QString collectActionText{m_showCollector ? QObject::tr("Hide collector")
                                              : QObject::tr("Show collector")};
    m_showCollectorAction.reset(new QAction(collectActionText));
    m_showCollectorAction->setToolTip(QObject::tr("Show or hide the water collector"));
    QObject::connect(m_showCollectorAction.get(), &QAction::triggered
                     , [this](){m_showCollector ? setCollector(false) : setCollector(true);});
    m_tankerActionList.append(m_showCollectorAction.get());

    QString addText{m_showText ? QObject::tr("Hide text") : QObject::tr("Show text")};
    m_addTextAction.reset(new QAction(addText));
    m_addTextAction->setToolTip(QObject::tr("Show or hide text"));
    QObject::connect(m_addTextAction.get(), &QAction::triggered
                     , [this](){m_showText ? textShow(false) : textShow(true);});
    m_tankerActionList.append(m_addTextAction.get());
}

void TankerShape::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(widget);

    painter->setRenderHint(QPainter::Antialiasing);
    painter->setRenderHint(QPainter::SmoothPixmapTransform);
    painter->setPen(pen());
    painter->setBrush(brush());

    drawTankerShape(painter);

    if (option->state & QStyle::State_Selected)
        highlightSelected(painter, option);
}

QRectF TankerShape::boundingRect() const
{
    QRectF boundingRect{m_tankerRect};
    if (m_showPipes) {
        qreal pipeLength{m_tankerRect.width() / 6};
        boundingRect.adjust(-pipeLength, 0.0, pipeLength, 0.0);
    }
    if (m_showCollector) {
        qreal collectorLength{m_tankerRect.width() / 3};
        boundingRect.adjust(0.0, 0.0, 0.0, collectorLength);
    }
    qreal halfpw{pen().style() == Qt::NoPen ? qreal(0.0) : pen().widthF() / 2};
    if (halfpw > 0.0)
        boundingRect.adjust(-halfpw, -halfpw, halfpw, halfpw);

    return boundingRect;
}

QPainterPath TankerShape::shape() const
{
    QPainterPath path;
    path.addPolygon(basePolygon(rect()));

    qreal sixthWidth{m_tankerRect.width() / 6}; // 5.0
    if (m_showPipes) {
        qreal pipeY{m_tankerRect.bottom() - sixthWidth};
        QPointF rightPipeP1{m_tankerRect.right(), pipeY};
        QPointF rightPipeP2{m_tankerRect.right() + sixthWidth, pipeY};
        // Right pipe
        path.moveTo(rightPipeP1);
        path.lineTo(rightPipeP2);

        QPointF rightConnectP1{rightPipeP2.x(), rightPipeP2.y() + sixthWidth / 2};
        QPointF rightConnectP2{rightPipeP2.x(), rightPipeP2.y() - sixthWidth / 2};
        // Right pipe connection
        path.moveTo(rightConnectP1);
        path.lineTo(rightConnectP2);

        QPointF leftPipeP1{m_tankerRect.left(), pipeY};
        QPointF leftPipeP2{m_tankerRect.left() - sixthWidth, pipeY};
        // Left pipe
        path.moveTo(leftPipeP1);
        path.lineTo(leftPipeP2);

        QPointF leftConnectP1{leftPipeP2.x(), leftPipeP2.y() + sixthWidth / 2};
        QPointF leftConnectP2{leftPipeP2.x(), leftPipeP2.y() - sixthWidth / 2};
        // Right pipe connection
        path.moveTo(leftConnectP1);
        path.lineTo(leftConnectP2);
    }

    if (m_showCollector) {
        qreal collectorX{m_tankerRect.center().x()};
        qreal collectorY{m_tankerRect.bottom() + sixthWidth * 2};
        qreal leftPipeX{collectorX - sixthWidth};
        QPointF leftRightPipeP1{collectorX, m_tankerRect.bottom()};
        QPointF leftPipeP2{leftPipeX, collectorY};
        //Left collector pipe
        path.moveTo(leftRightPipeP1);
        path.lineTo(leftPipeP2);

        qreal rightPipeX{collectorX + sixthWidth};
        QPointF rightPipeP2{rightPipeX, collectorY};
        //Right collector pipe
        path.moveTo(leftRightPipeP1);
        path.lineTo(rightPipeP2);

        QPointF leftConnectP1{leftPipeX - sixthWidth / 2, collectorY};
        QPointF leftConnectP2{leftPipeX + sixthWidth / 2, collectorY};
        //Left connector
        path.moveTo(leftConnectP1);
        path.lineTo(leftConnectP2);

        QPointF rightConnectP1{rightPipeX - sixthWidth / 2, collectorY};
        QPointF rightConnectP2{rightPipeX + sixthWidth / 2, collectorY};
        //Right connector
        path.moveTo(rightConnectP1);
        path.lineTo(rightConnectP2);
    }

    return shapeFromPath(path);
}

QPixmap TankerShape::image()
{
    qreal pixmapWidth{boundingRect().width()};
    qreal pixmapHeight{boundingRect().height()};
    QPixmap pixmap(pixmapWidth, pixmapHeight);
    pixmap.fill(Qt::transparent);

    QPainter painter(&pixmap);
    painter.setPen(pen());
    painter.setBrush(brush());
    painter.translate(pixmapWidth / 2.0, pixmapHeight / 2.0);
    drawTankerShape(&painter);

    return pixmap;
}

TechnicsShape::ShapeType TankerShape::shapeType() const
{
    return m_tankerType;
}

void TankerShape::setRect(const QRectF &rect)
{
    if (m_tankerRect == rect)
        return;

    prepareGeometryChange();
    m_tankerRect.setRect(rect.topLeft().x(), rect.topLeft().y(), rect.width(), rect.height());
    if (m_tankerText != nullptr)
        m_tankerText->setPos(m_tankerRect.right(), m_tankerRect.bottom()
                                                       - m_tankerRect.width() / 6);
    if (m_showPipes) {
        qreal pipeLength{m_tankerRect.width() / 6};
        m_tankerRect.adjust(pipeLength, 0.0, -pipeLength, 0.0);
    }
    if (m_showCollector) {
        qreal collectorLength{m_tankerRect.width() / 3};
        m_tankerRect.adjust(0.0, 0.0, 0.0, -collectorLength);
    }
    update();
}

QRectF TankerShape::rect() const
{
    return m_tankerRect;
}

void TankerShape::setHeight(const qreal &height)
{
    if (m_tankerRect.height() == height)
        return;

    qreal oldHeight{m_tankerRect.height()};
    prepareGeometryChange();
    m_tankerRect.setHeight(height);
    qreal dy{(m_tankerRect.height() - oldHeight) / 2};
    m_tankerRect.moveTo(QPointF(m_tankerRect.x(), m_tankerRect.y() - dy));
    update();
}

qreal TankerShape::height() const
{
    return m_tankerRect.height();
}

void TankerShape::setText(const QString &text)
{
    if (m_tankerText == nullptr) {
        m_tankerText=new QGraphicsTextItem(this);
        m_tankerText->setTextInteractionFlags(Qt::TextEditorInteraction);
        m_tankerText->setRotation(-90);
    }
    m_tankerText->setPlainText(text);
    m_showText = true;
}

QString TankerShape::text() const
{
    if (m_tankerText == nullptr)
        return "";

    return m_tankerText->toPlainText();
}

void TankerShape::setPipes(bool showPipes)
{
    if (m_showPipes == showPipes)
        return;

    prepareGeometryChange();
    m_showPipes = showPipes;
    setSelected(false);
    setSelected(true);
    update();
}

bool TankerShape::pipes() const
{
    return m_showPipes;
}

void TankerShape::setCollector(bool showCollector)
{
    if (m_showCollector == showCollector)
        return;

    prepareGeometryChange();
    m_showCollector = showCollector;
    setSelected(false);
    setSelected(true);
    update();
}

bool TankerShape::collector()
{
    return m_showCollector;
}

void TankerShape::textShow(bool showText)
{
    if (showText) {
        if (m_tankerText == nullptr) {
            m_tankerText=new QGraphicsTextItem(this);
            m_tankerText->setPlainText("АЦ-");
            m_tankerText->setTextInteractionFlags(Qt::TextEditorInteraction);
            m_tankerText->setRotation(-90);
        }
        m_tankerText->show();
        m_showText = true;
    } else {
        m_tankerText->hide();
        m_showText = false;
    }
}

void TankerShape::mousePressEvent(QGraphicsSceneMouseEvent *mouseEvent)
{
    if (mouseEvent->buttons() == Qt::RightButton) {
        createAction();
        addActions(m_tankerActionList);
        QAction menuAction{menu()->exec(mouseEvent->screenPos())};
        QString menuActionText;
        if (menuAction.parent()) {
            menuActionText = menuAction.parent()->objectName();
        }
        if ((menuActionText != "actionDeleteItem") && (menuActionText != "actionCut")) {
            removeActions(m_tankerActionList);
            m_tankerActionList.clear();
        }
    } else {
        AbstractShape::mousePressEvent(mouseEvent);
    }
}

PumpHoseShape::PumpHoseShape(QGraphicsItem *parent)
    :TechnicsShape(parent)
    , m_pumpHoseType{PumpHose}
    , m_pumpHoseText{nullptr}
    , m_pumpHoseRect{QRectF(-15.0, -37.5, 30.0, 75.0)}
    , m_showPipes{false}
    , m_showCollector{false}
    , m_showText{false}
{
    setFlag(ItemSendsGeometryChanges, true);
    setAcceptHoverEvents(true);
    setPen(QPen(Qt::red, 1));
    setBrush(QBrush(Qt::white));
}

void PumpHoseShape::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(widget);

    painter->setRenderHint(QPainter::Antialiasing);
    painter->setRenderHint(QPainter::SmoothPixmapTransform);
    painter->setPen(pen());
    painter->setBrush(brush());

    drawPumpHoseShape(painter);

    if (option->state & QStyle::State_Selected)
        highlightSelected(painter, option);
}

QRectF PumpHoseShape::boundingRect() const
{
    QRectF boundingRect{m_pumpHoseRect};
    if (m_showPipes) {
        qreal pipeLength{m_pumpHoseRect.width() / 6};
        boundingRect.adjust(-pipeLength, 0.0, pipeLength, 0.0);
    }
    if (m_showCollector) {
        qreal collectorLength{m_pumpHoseRect.width() / 3};
        boundingRect.adjust(0.0, 0.0, 0.0, collectorLength);
    }
    qreal halfpw{pen().style() == Qt::NoPen ? qreal(0.0) : pen().widthF() / 2};
    if (halfpw > 0.0)
        boundingRect.adjust(-halfpw, -halfpw, halfpw, halfpw);

    return boundingRect;
}

QPainterPath PumpHoseShape::shape() const
{
    QPainterPath path;
    path.addPolygon(basePolygon(rect()));

    qreal sixthWidth{m_pumpHoseRect.width() / 6}; // 5.0
    if (m_showPipes) {
        qreal pipeY{m_pumpHoseRect.bottom() - sixthWidth};
        QPointF rightPipeP1{m_pumpHoseRect.right(), pipeY};
        QPointF rightPipeP2{m_pumpHoseRect.right() + sixthWidth, pipeY};
        // Right pipe
        path.moveTo(rightPipeP1);
        path.lineTo(rightPipeP2);

        QPointF rightConnectP1{rightPipeP2.x(), rightPipeP2.y() + sixthWidth / 2};
        QPointF rightConnectP2{rightPipeP2.x(), rightPipeP2.y() - sixthWidth / 2};
        // Right pipe connection
        path.moveTo(rightConnectP1);
        path.lineTo(rightConnectP2);

        QPointF leftPipeP1{m_pumpHoseRect.left(), pipeY};
        QPointF leftPipeP2{m_pumpHoseRect.left() - sixthWidth, pipeY};
        // Left pipe
        path.moveTo(leftPipeP1);
        path.lineTo(leftPipeP2);

        QPointF leftConnectP1{leftPipeP2.x(), leftPipeP2.y() + sixthWidth / 2};
        QPointF leftConnectP2{leftPipeP2.x(), leftPipeP2.y() - sixthWidth / 2};
        // Right pipe connection
        path.moveTo(leftConnectP1);
        path.lineTo(leftConnectP2);
    }

    if (m_showCollector) {
        qreal collectorX{m_pumpHoseRect.center().x()};
        qreal collectorY{m_pumpHoseRect.bottom() + sixthWidth * 2};
        qreal leftPipeX{collectorX - sixthWidth};
        QPointF leftRightPipeP1{collectorX, m_pumpHoseRect.bottom()};
        QPointF leftPipeP2{leftPipeX, collectorY};
        //Left collector pipe
        path.moveTo(leftRightPipeP1);
        path.lineTo(leftPipeP2);

        qreal rightPipeX{collectorX + sixthWidth};
        QPointF rightPipeP2{rightPipeX, collectorY};
        //Right collector pipe
        path.moveTo(leftRightPipeP1);
        path.lineTo(rightPipeP2);

        QPointF leftConnectP1{leftPipeX - sixthWidth / 2, collectorY};
        QPointF leftConnectP2{leftPipeX + sixthWidth / 2, collectorY};
        //Left connector
        path.moveTo(leftConnectP1);
        path.lineTo(leftConnectP2);

        QPointF rightConnectP1{rightPipeX - sixthWidth / 2, collectorY};
        QPointF rightConnectP2{rightPipeX + sixthWidth / 2, collectorY};
        //Right connector
        path.moveTo(rightConnectP1);
        path.lineTo(rightConnectP2);
    }

    return shapeFromPath(path);
}

QPixmap PumpHoseShape::image()
{
    qreal pixmapWidth{boundingRect().width()};
    qreal pixmapHeight{boundingRect().height()};
    QPixmap pixmap(pixmapWidth, pixmapHeight);
    pixmap.fill(Qt::transparent);

    QPainter painter(&pixmap);
    painter.setPen(pen());
    painter.setBrush(brush());
    painter.translate(pixmapWidth / 2.0, pixmapHeight / 2.0);
    drawPumpHoseShape(&painter);

    return pixmap;
}

TechnicsShape::ShapeType PumpHoseShape::shapeType() const
{
    return m_pumpHoseType;
}

void PumpHoseShape::setRect(const QRectF &rect)
{
    if (m_pumpHoseRect == rect)
        return;

    prepareGeometryChange();
    m_pumpHoseRect.setRect(rect.topLeft().x(), rect.topLeft().y(), rect.width(), rect.height());
    if (m_pumpHoseText != nullptr)
        m_pumpHoseText->setPos(m_pumpHoseRect.right(), m_pumpHoseRect.bottom()
                                                           - m_pumpHoseRect.width() / 6);
    if (m_showPipes) {
        qreal pipeLength{m_pumpHoseRect.width() / 6};
        m_pumpHoseRect.adjust(pipeLength, 0.0, -pipeLength, 0.0);
    }
    if (m_showCollector) {
        qreal collectorLength{m_pumpHoseRect.width() / 3};
        m_pumpHoseRect.adjust(0.0, 0.0, 0.0, -collectorLength);
    }
    update();
}

QRectF PumpHoseShape::rect() const
{
    return m_pumpHoseRect;
}

void PumpHoseShape::setHeight(const qreal &height)
{
    if (m_pumpHoseRect.height() == height)
        return;

    qreal oldHeight{m_pumpHoseRect.height()};
    prepareGeometryChange();
    m_pumpHoseRect.setHeight(height);
    qreal dy{(m_pumpHoseRect.height() - oldHeight) / 2};
    m_pumpHoseRect.moveTo(QPointF(m_pumpHoseRect.x(), m_pumpHoseRect.y() - dy));
    update();
}

qreal PumpHoseShape::height() const
{
    return m_pumpHoseRect.height();
}

void PumpHoseShape::setText(const QString &text)
{
    if (m_pumpHoseText == nullptr) {
        m_pumpHoseText = new QGraphicsTextItem(this);
        m_pumpHoseText->setTextInteractionFlags(Qt::TextEditorInteraction);
        m_pumpHoseText->setRotation(-90);
    }
    m_pumpHoseText->setPlainText(text);
    m_showText = true;
}

QString PumpHoseShape::text() const
{
    if (m_pumpHoseText == nullptr)
        return "";

    return m_pumpHoseText->toPlainText();
}

void PumpHoseShape::setPipes(bool showPipes)
{
    if (m_showPipes == showPipes)
        return;

    prepareGeometryChange();
    m_showPipes = showPipes;
    setSelected(false);
    setSelected(true);
    update();
}

bool PumpHoseShape::pipes() const
{
    return m_showPipes;
}

void PumpHoseShape::setCollector(bool showCollector)
{
    if (m_showCollector == showCollector)
        return;

    prepareGeometryChange();
    m_showCollector = showCollector;
    setSelected(false);
    setSelected(true);
    update();
}

bool PumpHoseShape::collector()
{
    return m_showCollector;
}

void PumpHoseShape::mousePressEvent(QGraphicsSceneMouseEvent *mouseEvent)
{
    if (mouseEvent->buttons() == Qt::RightButton) {
        createAction();
        addActions(m_pumpHoseActionList);
        QAction menuAction{menu()->exec(mouseEvent->screenPos())};
        QString menuActionText;
        if (menuAction.parent()) {
            menuActionText = menuAction.parent()->objectName();
        }
        if ((menuActionText != "actionDeleteItem") && (menuActionText != "actionCut")) {
            removeActions(m_pumpHoseActionList);
            m_pumpHoseActionList.clear();
        }
    } else {
        AbstractShape::mousePressEvent(mouseEvent);
    }
}

void PumpHoseShape::createAction()
{
    QString pipeActionText{m_showPipes ? QObject::tr("Hide pipes") : QObject::tr("Show pipes")};
    m_showPipeAction.reset(new QAction(pipeActionText));
    m_showPipeAction->setToolTip(QObject::tr("Show or hide the pipes"));
    QObject::connect(m_showPipeAction.get(), &QAction::triggered
                     , [this]() {m_showPipes ? setPipes(false) : setPipes(true);});
    m_pumpHoseActionList.append(m_showPipeAction.get());

    QString collectActionText{m_showCollector ? QObject::tr("Hide collector")
                                              : QObject::tr("Show collector")};
    m_showCollectorAction.reset(new QAction(collectActionText));
    m_showCollectorAction->setToolTip(QObject::tr("Show or hide the water collector"));
    QObject::connect(m_showCollectorAction.get(), &QAction::triggered
                     , [this](){m_showCollector ? setCollector(false) : setCollector(true);});
    m_pumpHoseActionList.append(m_showCollectorAction.get());

    QString addText{m_showText ? QObject::tr("Hide text") : QObject::tr("Show text")};
    m_addTextAction.reset(new QAction(addText));
    m_addTextAction->setToolTip(QObject::tr("Show or hide text"));
    QObject::connect(m_addTextAction.get(), &QAction::triggered
                     , [this](){m_showText ? textShow(false) : textShow(true);});
    m_pumpHoseActionList.append(m_addTextAction.get());
}

void PumpHoseShape::textShow(bool showText)
{
    if (showText) {
        if (m_pumpHoseText == nullptr) {
            m_pumpHoseText=new QGraphicsTextItem(this);
            m_pumpHoseText->setPlainText("АНР-");
            m_pumpHoseText->setTextInteractionFlags(Qt::TextEditorInteraction);
            m_pumpHoseText->setRotation(-90);
        }
        m_pumpHoseText->show();
        m_showText = true;
    } else {
        m_pumpHoseText->hide();
        m_showText = false;
    }
}

void PumpHoseShape::drawPumpHoseShape(QPainter *painter)
{
    painter->drawPolygon(basePolygon(rect()));

    qreal sixthWidth{m_pumpHoseRect.width() / 6}; // 5.0
    qreal sixthHeight{m_pumpHoseRect.height() / 6}; //12.5
    qreal pumpLeft{m_pumpHoseRect.left() + sixthWidth};
    qreal pumpRight{m_pumpHoseRect.right() - sixthWidth};
    qreal pumpTop{m_pumpHoseRect.bottom() - sixthHeight};
    qreal pumpBottom{m_pumpHoseRect.bottom()};
    QPolygonF pump;
    pump << QPointF(pumpLeft, pumpBottom) << QPointF(pumpLeft, pumpTop)
         << QPointF(pumpRight, pumpTop) << QPointF(pumpRight, pumpBottom);
    painter->drawPolygon(pump);

    if (m_showText) {
        m_pumpHoseText->setPos(m_pumpHoseRect.right(), m_pumpHoseRect.bottom() - sixthWidth * 2);
    }

    if (m_showPipes) {
        drawPipes(painter, sixthWidth);
    }

    if (m_showCollector) {
        drawCollector(painter, sixthWidth);
    }
}

void PumpHoseShape::drawPipes(QPainter *painter, qreal sixtWidth)
{
    painter->setPen(QPen(Qt::black, 1));
    qreal pipeY{m_pumpHoseRect.bottom() - sixtWidth};
    QPointF rightPipeP1{m_pumpHoseRect.right(), pipeY};
    QPointF rightPipeP2{m_pumpHoseRect.right() + sixtWidth, pipeY};
    painter->drawLine(rightPipeP1, rightPipeP2); // Right pipe

    QPointF rightConnectP1{rightPipeP2.x(), rightPipeP2.y() + sixtWidth / 2};
    QPointF rightConnectP2{rightPipeP2.x(), rightPipeP2.y() - sixtWidth / 2};
    painter->drawLine(rightConnectP1, rightConnectP2); // Right pipe connection

    QPointF leftPipeP1{m_pumpHoseRect.left(), pipeY};
    QPointF leftPipeP2{m_pumpHoseRect.left() - sixtWidth, pipeY};
    painter->drawLine(leftPipeP1, leftPipeP2); // Left pipe

    QPointF leftConnectP1{leftPipeP2.x(), leftPipeP2.y() + sixtWidth / 2};
    QPointF leftConnectP2{leftPipeP2.x(), leftPipeP2.y() - sixtWidth / 2};
    painter->drawLine(leftConnectP1, leftConnectP2); // Right pipe connection
}

void PumpHoseShape::drawCollector(QPainter *painter, qreal sixtWidth)
{
    painter->setPen(QPen(Qt::black, 1));
    qreal collectorX{m_pumpHoseRect.center().x()};
    qreal collectorY{m_pumpHoseRect.bottom() + sixtWidth * 2};
    qreal leftPipeX{collectorX - sixtWidth};
    QPointF leftRightPipeP1{collectorX, m_pumpHoseRect.bottom()};
    QPointF leftPipeP2{leftPipeX, collectorY};
    painter->drawLine(leftRightPipeP1, leftPipeP2); //Left collector pipe

    qreal rightPipeX{collectorX + sixtWidth};
    QPointF rightPipeP2{rightPipeX, collectorY};
    painter->drawLine(leftRightPipeP1, rightPipeP2); //Right collector pipe

    QPointF leftConnectP1{leftPipeX - sixtWidth / 2, collectorY};
    QPointF leftConnectP2{leftPipeX + sixtWidth / 2, collectorY};
    painter->drawLine(leftConnectP1, leftConnectP2); //Left connector

    QPointF rightConnectP1{rightPipeX - sixtWidth / 2, collectorY};
    QPointF rightConnectP2{rightPipeX + sixtWidth / 2, collectorY};
    painter->drawLine(rightConnectP1, rightConnectP2);  //Right connector
}

FirstAidShape::FirstAidShape(QGraphicsItem *parent)
    :TechnicsShape(parent)
    , m_firstAidType{FirstAid}
    , m_firstAidText{nullptr}
    , m_firstAidRect{QRectF(-15.0, -37.5, 30.0, 75.0)}
    , m_showPipes{false}
    , m_showCollector{false}
    , m_showText{false}
{
    setFlag(ItemSendsGeometryChanges, true);
    setAcceptHoverEvents(true);
    setPen(QPen(Qt::red, 1));
    setBrush(QBrush(Qt::white));
}

void FirstAidShape::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(widget);

    painter->setRenderHint(QPainter::Antialiasing);
    painter->setRenderHint(QPainter::SmoothPixmapTransform);
    painter->setPen(pen());
    painter->setBrush(brush());

    drawFirstAidShape(painter);

    if (option->state & QStyle::State_Selected)
        highlightSelected(painter, option);
}

QRectF FirstAidShape::boundingRect() const
{
    QRectF boundingRect{m_firstAidRect};
    if (m_showPipes) {
        qreal pipeLength{m_firstAidRect.width() / 6};
        boundingRect.adjust(-pipeLength, 0.0, pipeLength, 0.0);
    }
    if (m_showCollector) {
        qreal collectorLength{m_firstAidRect.width() / 3};
        boundingRect.adjust(0.0, 0.0, 0.0, collectorLength);
    }
    qreal halfpw{pen().style() == Qt::NoPen ? qreal(0.0) : pen().widthF() / 2};
    if (halfpw > 0.0)
        boundingRect.adjust(-halfpw, -halfpw, halfpw, halfpw);

    return boundingRect;
}

QPainterPath FirstAidShape::shape() const
{
    QPainterPath path;
    path.addPolygon(basePolygon(rect()));

    qreal sixthWidth{m_firstAidRect.width() / 6}; // 5.0
    if (m_showPipes) {
        qreal pipeY{m_firstAidRect.bottom() - sixthWidth};
        QPointF rightPipeP1{m_firstAidRect.right(), pipeY};
        QPointF rightPipeP2{m_firstAidRect.right() + sixthWidth, pipeY};
        // Right pipe
        path.moveTo(rightPipeP1);
        path.lineTo(rightPipeP2);

        QPointF rightConnectP1{rightPipeP2.x(), rightPipeP2.y() + sixthWidth / 2};
        QPointF rightConnectP2{rightPipeP2.x(), rightPipeP2.y() - sixthWidth / 2};
        // Right pipe connection
        path.moveTo(rightConnectP1);
        path.lineTo(rightConnectP2);

        QPointF leftPipeP1{m_firstAidRect.left(), pipeY};
        QPointF leftPipeP2{m_firstAidRect.left() - sixthWidth, pipeY};
        // Left pipe
        path.moveTo(leftPipeP1);
        path.lineTo(leftPipeP2);

        QPointF leftConnectP1{leftPipeP2.x(), leftPipeP2.y() + sixthWidth / 2};
        QPointF leftConnectP2{leftPipeP2.x(), leftPipeP2.y() - sixthWidth / 2};
        // Right pipe connection
        path.moveTo(leftConnectP1);
        path.lineTo(leftConnectP2);
    }

    if (m_showCollector) {
        qreal collectorX{m_firstAidRect.center().x()};
        qreal collectorY{m_firstAidRect.bottom() + sixthWidth * 2};
        qreal leftPipeX{collectorX - sixthWidth};
        QPointF leftRightPipeP1{collectorX, m_firstAidRect.bottom()};
        QPointF leftPipeP2{leftPipeX, collectorY};
        //Left collector pipe
        path.moveTo(leftRightPipeP1);
        path.lineTo(leftPipeP2);

        qreal rightPipeX{collectorX + sixthWidth};
        QPointF rightPipeP2{rightPipeX, collectorY};
        //Right collector pipe
        path.moveTo(leftRightPipeP1);
        path.lineTo(rightPipeP2);

        QPointF leftConnectP1{leftPipeX - sixthWidth / 2, collectorY};
        QPointF leftConnectP2{leftPipeX + sixthWidth / 2, collectorY};
        //Left connector
        path.moveTo(leftConnectP1);
        path.lineTo(leftConnectP2);

        QPointF rightConnectP1{rightPipeX - sixthWidth / 2, collectorY};
        QPointF rightConnectP2{rightPipeX + sixthWidth / 2, collectorY};
        //Right connector
        path.moveTo(rightConnectP1);
        path.lineTo(rightConnectP2);
    }

    return shapeFromPath(path);
}

QPixmap FirstAidShape::image()
{
    qreal pixmapWidth{boundingRect().width()};
    qreal pixmapHeight{boundingRect().height()};
    QPixmap pixmap(pixmapWidth, pixmapHeight);
    pixmap.fill(Qt::transparent);

    QPainter painter(&pixmap);
    painter.setPen(pen());
    painter.setBrush(brush());
    painter.translate(pixmapWidth / 2.0, pixmapHeight / 2.0);
    drawFirstAidShape(&painter);

    return pixmap;
}

TechnicsShape::ShapeType FirstAidShape::shapeType() const
{
    return m_firstAidType;
}

void FirstAidShape::setRect(const QRectF &rect)
{
    if (m_firstAidRect == rect)
        return;

    prepareGeometryChange();
    m_firstAidRect.setRect(rect.topLeft().x(), rect.topLeft().y(), rect.width(), rect.height());
    if (m_firstAidText != nullptr)
        m_firstAidText->setPos(m_firstAidRect.right(), m_firstAidRect.bottom()
                                                           - m_firstAidRect.width() / 6);
    if (m_showPipes) {
        qreal pipeLength{m_firstAidRect.width() / 6};
        m_firstAidRect.adjust(pipeLength, 0.0, -pipeLength, 0.0);
    }
    if (m_showCollector) {
        qreal collectorLength{m_firstAidRect.width() / 3};
        m_firstAidRect.adjust(0.0, 0.0, 0.0, -collectorLength);
    }
    update();
}

QRectF FirstAidShape::rect() const
{
    return m_firstAidRect;
}

void FirstAidShape::setHeight(const qreal &height)
{
    if (m_firstAidRect.height() == height)
        return;

    qreal oldHeight{m_firstAidRect.height()};
    prepareGeometryChange();
    m_firstAidRect.setHeight(height);
    qreal dy{(m_firstAidRect.height() - oldHeight) / 2};
    m_firstAidRect.moveTo(QPointF(m_firstAidRect.x(), m_firstAidRect.y() - dy));
    update();
}

qreal FirstAidShape::height() const
{
    return m_firstAidRect.height();
}

void FirstAidShape::setText(const QString &text)
{
    if (m_firstAidText == nullptr) {
        m_firstAidText = new QGraphicsTextItem(this);
        m_firstAidText->setTextInteractionFlags(Qt::TextEditorInteraction);
        m_firstAidText->setRotation(-90);
    }
    m_firstAidText->setPlainText(text);
    m_showText = true;
}

QString FirstAidShape::text() const
{
    if (m_firstAidText == nullptr)
        return "";

    return m_firstAidText->toPlainText();
}

void FirstAidShape::setPipes(bool showPipes)
{
    if (m_showPipes == showPipes)
        return;

    prepareGeometryChange();
    m_showPipes = showPipes;
    setSelected(false);
    setSelected(true);
    update();
}

bool FirstAidShape::pipes() const
{
    return m_showPipes;
}

void FirstAidShape::setCollector(bool showCollector)
{
    if (m_showCollector == showCollector)
        return;

    prepareGeometryChange();
    m_showCollector = showCollector;
    setSelected(false);
    setSelected(true);
    update();
}

bool FirstAidShape::collector()
{
    return m_showCollector;
}

void FirstAidShape::mousePressEvent(QGraphicsSceneMouseEvent *mouseEvent)
{
    if (mouseEvent->buttons() == Qt::RightButton) {
        createAction();
        addActions(m_firstAidActionList);
        QAction menuAction{menu()->exec(mouseEvent->screenPos())};
        QString menuActionText;
        if (menuAction.parent()) {
            menuActionText = menuAction.parent()->objectName();
        }
        if ((menuActionText != "actionDeleteItem") && (menuActionText != "actionCut")) {
            removeActions(m_firstAidActionList);
            m_firstAidActionList.clear();
        }
    } else {
        AbstractShape::mousePressEvent(mouseEvent);
    }

}

void FirstAidShape::createAction()
{
    QString pipeActionText{m_showPipes ? QObject::tr("Hide pipes") : QObject::tr("Show pipes")};
    m_showPipeAction.reset(new QAction(pipeActionText));
    m_showPipeAction->setToolTip(QObject::tr("Show or hide the pipes"));
    QObject::connect(m_showPipeAction.get(), &QAction::triggered
                     , [this]() {m_showPipes ? setPipes(false) : setPipes(true);});
    m_firstAidActionList.append(m_showPipeAction.get());

    QString collectActionText{m_showCollector ? QObject::tr("Hide collector")
                                              : QObject::tr("Show collector")};
    m_showCollectorAction.reset(new QAction(collectActionText));
    m_showCollectorAction->setToolTip(QObject::tr("Show or hide the water collector"));
    QObject::connect(m_showCollectorAction.get(), &QAction::triggered
                     , [this](){m_showCollector ? setCollector(false) : setCollector(true);});
    m_firstAidActionList.append(m_showCollectorAction.get());

    QString addText{m_showText ? QObject::tr("Hide text") : QObject::tr("Show text")};
    m_addTextAction.reset(new QAction(addText));
    m_addTextAction->setToolTip(QObject::tr("Show or hide text"));
    QObject::connect(m_addTextAction.get(), &QAction::triggered
                     , [this](){m_showText ? textShow(false) : textShow(true);});
    m_firstAidActionList.append(m_addTextAction.get());
}

void FirstAidShape::textShow(bool showText)
{
    if (showText) {
        if (m_firstAidText == nullptr) {
            m_firstAidText=new QGraphicsTextItem(this);
            m_firstAidText->setPlainText("АПП-");
            m_firstAidText->setTextInteractionFlags(Qt::TextEditorInteraction);
            m_firstAidText->setRotation(-90);
        }
        m_firstAidText->show();
        m_showText = true;
    } else {
        m_firstAidText->hide();
        m_showText = false;
    }
}

void FirstAidShape::drawFirstAidShape(QPainter *painter)
{
    painter->drawPolygon(basePolygon(rect()));
    painter->translate(m_firstAidRect.center());
    painter->rotate(270);
    painter->translate(-m_firstAidRect.center());
    QTextOption textOption{Qt::AlignCenter};
    painter->drawText(m_firstAidRect, "АПП", textOption);
    painter->translate(m_firstAidRect.center());
    painter->rotate(-270);
    painter->translate(-m_firstAidRect.center());
    qreal sixthWidth{m_firstAidRect.width() / 6}; // 5.0

    if (m_showText) {
        m_firstAidText->setPos(m_firstAidRect.right(), m_firstAidRect.bottom() - sixthWidth * 2);
    }

    if (m_showPipes) {
        drawPipes(painter, sixthWidth);
    }

    if (m_showCollector) {
        drawCollector(painter, sixthWidth);
    }
}

void FirstAidShape::drawPipes(QPainter *painter, qreal sixtWidth)
{
    painter->setPen(QPen(Qt::black, 1));
    qreal pipeY{m_firstAidRect.bottom() - sixtWidth};
    QPointF rightPipeP1{m_firstAidRect.right(), pipeY};
    QPointF rightPipeP2{m_firstAidRect.right() + sixtWidth, pipeY};
    painter->drawLine(rightPipeP1, rightPipeP2); // Right pipe

    QPointF rightConnectP1{rightPipeP2.x(), rightPipeP2.y() + sixtWidth / 2};
    QPointF rightConnectP2{rightPipeP2.x(), rightPipeP2.y() - sixtWidth / 2};
    painter->drawLine(rightConnectP1, rightConnectP2); // Right pipe connection

    QPointF leftPipeP1{m_firstAidRect.left(), pipeY};
    QPointF leftPipeP2{m_firstAidRect.left() - sixtWidth, pipeY};
    painter->drawLine(leftPipeP1, leftPipeP2); // Left pipe

    QPointF leftConnectP1{leftPipeP2.x(), leftPipeP2.y() + sixtWidth / 2};
    QPointF leftConnectP2{leftPipeP2.x(), leftPipeP2.y() - sixtWidth / 2};
    painter->drawLine(leftConnectP1, leftConnectP2); // Right pipe connection
}

void FirstAidShape::drawCollector(QPainter *painter, qreal sixtWidth)
{
    painter->setPen(QPen(Qt::black, 1));
    qreal collectorX{m_firstAidRect.center().x()};
    qreal collectorY{m_firstAidRect.bottom() + sixtWidth * 2};
    qreal leftPipeX{collectorX - sixtWidth};
    QPointF leftRightPipeP1{collectorX, m_firstAidRect.bottom()};
    QPointF leftPipeP2{leftPipeX, collectorY};
    painter->drawLine(leftRightPipeP1, leftPipeP2); //Left collector pipe

    qreal rightPipeX{collectorX + sixtWidth};
    QPointF rightPipeP2{rightPipeX, collectorY};
    painter->drawLine(leftRightPipeP1, rightPipeP2); //Right collector pipe

    QPointF leftConnectP1{leftPipeX - sixtWidth / 2, collectorY};
    QPointF leftConnectP2{leftPipeX + sixtWidth / 2, collectorY};
    painter->drawLine(leftConnectP1, leftConnectP2); //Left connector

    QPointF rightConnectP1{rightPipeX - sixtWidth / 2, collectorY};
    QPointF rightConnectP2{rightPipeX + sixtWidth / 2, collectorY};
    painter->drawLine(rightConnectP1, rightConnectP2);  //Right connector
}

EmergencyShape::EmergencyShape(QGraphicsItem *parent)
    :TechnicsShape(parent)
    , m_emergencyType{Emergency}
    , m_emergencyText{nullptr}
    , m_emergencyRect{QRectF(-15.0, -37.5, 30.0, 75.0)}
    , m_showPipes{false}
    , m_showCollector{false}
    , m_showText{false}
{
    setFlag(ItemSendsGeometryChanges, true);
    setAcceptHoverEvents(true);
    setPen(QPen(Qt::red, 1));
    setBrush(QBrush(Qt::white));
}

void EmergencyShape::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(widget);

    painter->setRenderHint(QPainter::Antialiasing);
    painter->setRenderHint(QPainter::SmoothPixmapTransform);
    painter->setPen(pen());
    painter->setBrush(brush());

    drawEmergencyShape(painter);

    if (option->state & QStyle::State_Selected)
        highlightSelected(painter, option);
}

QRectF EmergencyShape::boundingRect() const
{
    QRectF boundingRect{m_emergencyRect};
    if (m_showPipes) {
        qreal pipeLength{m_emergencyRect.width() / 6};
        boundingRect.adjust(-pipeLength, 0.0, pipeLength, 0.0);
    }
    if (m_showCollector) {
        qreal collectorLength{m_emergencyRect.width() / 3};
        boundingRect.adjust(0.0, 0.0, 0.0, collectorLength);
    }
    qreal halfpw{pen().style() == Qt::NoPen ? qreal(0.0) : pen().widthF() / 2};
    if (halfpw > 0.0)
        boundingRect.adjust(-halfpw, -halfpw, halfpw, halfpw);

    return boundingRect;
}

QPainterPath EmergencyShape::shape() const
{
    QPainterPath path;
    path.addPolygon(basePolygon(rect()));

    qreal sixthWidth{m_emergencyRect.width() / 6}; // 5.0
    if (m_showPipes) {
        qreal pipeY{m_emergencyRect.bottom() - sixthWidth};
        QPointF rightPipeP1{m_emergencyRect.right(), pipeY};
        QPointF rightPipeP2{m_emergencyRect.right() + sixthWidth, pipeY};
        // Right pipe
        path.moveTo(rightPipeP1);
        path.lineTo(rightPipeP2);

        QPointF rightConnectP1{rightPipeP2.x(), rightPipeP2.y() + sixthWidth / 2};
        QPointF rightConnectP2{rightPipeP2.x(), rightPipeP2.y() - sixthWidth / 2};
        // Right pipe connection
        path.moveTo(rightConnectP1);
        path.lineTo(rightConnectP2);

        QPointF leftPipeP1{m_emergencyRect.left(), pipeY};
        QPointF leftPipeP2{m_emergencyRect.left() - sixthWidth, pipeY};
        // Left pipe
        path.moveTo(leftPipeP1);
        path.lineTo(leftPipeP2);

        QPointF leftConnectP1{leftPipeP2.x(), leftPipeP2.y() + sixthWidth / 2};
        QPointF leftConnectP2{leftPipeP2.x(), leftPipeP2.y() - sixthWidth / 2};
        // Right pipe connection
        path.moveTo(leftConnectP1);
        path.lineTo(leftConnectP2);
    }

    if (m_showCollector) {
        qreal collectorX{m_emergencyRect.center().x()};
        qreal collectorY{m_emergencyRect.bottom() + sixthWidth * 2};
        qreal leftPipeX{collectorX - sixthWidth};
        QPointF leftRightPipeP1{collectorX, m_emergencyRect.bottom()};
        QPointF leftPipeP2{leftPipeX, collectorY};
        //Left collector pipe
        path.moveTo(leftRightPipeP1);
        path.lineTo(leftPipeP2);

        qreal rightPipeX{collectorX + sixthWidth};
        QPointF rightPipeP2{rightPipeX, collectorY};
        //Right collector pipe
        path.moveTo(leftRightPipeP1);
        path.lineTo(rightPipeP2);

        QPointF leftConnectP1{leftPipeX - sixthWidth / 2, collectorY};
        QPointF leftConnectP2{leftPipeX + sixthWidth / 2, collectorY};
        //Left connector
        path.moveTo(leftConnectP1);
        path.lineTo(leftConnectP2);

        QPointF rightConnectP1{rightPipeX - sixthWidth / 2, collectorY};
        QPointF rightConnectP2{rightPipeX + sixthWidth / 2, collectorY};
        //Right connector
        path.moveTo(rightConnectP1);
        path.lineTo(rightConnectP2);
    }

    return shapeFromPath(path);
}

QPixmap EmergencyShape::image()
{
    qreal pixmapWidth{boundingRect().width()};
    qreal pixmapHeight{boundingRect().height()};
    QPixmap pixmap(pixmapWidth, pixmapHeight);
    pixmap.fill(Qt::transparent);

    QPainter painter(&pixmap);
    painter.setPen(pen());
    painter.setBrush(brush());
    painter.translate(pixmapWidth / 2.0, pixmapHeight / 2.0);
    drawEmergencyShape(&painter);

    return pixmap;
}

TechnicsShape::ShapeType EmergencyShape::shapeType() const
{
    return m_emergencyType;
}

void EmergencyShape::setRect(const QRectF &rect)
{
    if (m_emergencyRect == rect)
        return;

    prepareGeometryChange();
    m_emergencyRect.setRect(rect.topLeft().x(), rect.topLeft().y(), rect.width(), rect.height());
    if (m_emergencyText != nullptr)
        m_emergencyText->setPos(m_emergencyRect.right(), m_emergencyRect.bottom()
                                                           - m_emergencyRect.width() / 6);
    if (m_showPipes) {
        qreal pipeLength{m_emergencyRect.width() / 6};
        m_emergencyRect.adjust(pipeLength, 0.0, -pipeLength, 0.0);
    }
    if (m_showCollector) {
        qreal collectorLength{m_emergencyRect.width() / 3};
        m_emergencyRect.adjust(0.0, 0.0, 0.0, -collectorLength);
    }
    update();
}

QRectF EmergencyShape::rect() const
{
    return m_emergencyRect;
}

void EmergencyShape::setHeight(const qreal &height)
{
    if (m_emergencyRect.height() == height)
        return;

    qreal oldHeight{m_emergencyRect.height()};
    prepareGeometryChange();
    m_emergencyRect.setHeight(height);
    qreal dy{(m_emergencyRect.height() - oldHeight) / 2};
    m_emergencyRect.moveTo(QPointF(m_emergencyRect.x(), m_emergencyRect.y() - dy));
    update();
}

qreal EmergencyShape::height() const
{
    return m_emergencyRect.height();
}

void EmergencyShape::setText(const QString &text)
{
    if (m_emergencyText == nullptr) {
        m_emergencyText = new QGraphicsTextItem(this);
        m_emergencyText->setTextInteractionFlags(Qt::TextEditorInteraction);
        m_emergencyText->setRotation(-90);
    }
    m_emergencyText->setPlainText(text);
    m_showText = true;
}

QString EmergencyShape::text() const
{
    if (m_emergencyText == nullptr)
        return "";

    return m_emergencyText->toPlainText();
}

void EmergencyShape::setPipes(bool showPipes)
{
    if (m_showPipes == showPipes)
        return;

    prepareGeometryChange();
    m_showPipes = showPipes;
    setSelected(false);
    setSelected(true);
    update();
}

bool EmergencyShape::pipes() const
{
    return m_showPipes;
}

void EmergencyShape::setCollector(bool showCollector)
{
    if (m_showCollector == showCollector)
        return;

    prepareGeometryChange();
    m_showCollector = showCollector;
    setSelected(false);
    setSelected(true);
    update();
}

bool EmergencyShape::collector()
{
    return m_showCollector;
}

void EmergencyShape::mousePressEvent(QGraphicsSceneMouseEvent *mouseEvent)
{
    if (mouseEvent->buttons() == Qt::RightButton) {
        createAction();
        addActions(m_emergencyActionList);
        QAction menuAction{menu()->exec(mouseEvent->screenPos())};
        QString menuActionText;
        if (menuAction.parent()) {
            menuActionText = menuAction.parent()->objectName();
        }
        if ((menuActionText != "actionDeleteItem") && (menuActionText != "actionCut")) {
            removeActions(m_emergencyActionList);
            m_emergencyActionList.clear();
        }
    } else {
        AbstractShape::mousePressEvent(mouseEvent);
    }
}

void EmergencyShape::createAction()
{
    QString pipeActionText{m_showPipes ? QObject::tr("Hide pipes") : QObject::tr("Show pipes")};
    m_showPipeAction.reset(new QAction(pipeActionText));
    m_showPipeAction->setToolTip(QObject::tr("Show or hide the pipes"));
    QObject::connect(m_showPipeAction.get(), &QAction::triggered
                     , [this]() {m_showPipes ? setPipes(false) : setPipes(true);});
    m_emergencyActionList.append(m_showPipeAction.get());

    QString collectActionText{m_showCollector ? QObject::tr("Hide collector")
                                              : QObject::tr("Show collector")};
    m_showCollectorAction.reset(new QAction(collectActionText));
    m_showCollectorAction->setToolTip(QObject::tr("Show or hide the water collector"));
    QObject::connect(m_showCollectorAction.get(), &QAction::triggered
                     , [this](){m_showCollector ? setCollector(false) : setCollector(true);});
    m_emergencyActionList.append(m_showCollectorAction.get());

    QString addText{m_showText ? QObject::tr("Hide text") : QObject::tr("Show text")};
    m_addTextAction.reset(new QAction(addText));
    m_addTextAction->setToolTip(QObject::tr("Show or hide text"));
    QObject::connect(m_addTextAction.get(), &QAction::triggered
                     , [this](){m_showText ? textShow(false) : textShow(true);});
    m_emergencyActionList.append(m_addTextAction.get());
}

void EmergencyShape::textShow(bool showText)
{
    if (showText) {
        if (m_emergencyText == nullptr) {
            m_emergencyText=new QGraphicsTextItem(this);
            m_emergencyText->setPlainText("АСА-");
            m_emergencyText->setTextInteractionFlags(Qt::TextEditorInteraction);
            m_emergencyText->setRotation(-90);
        }
        m_emergencyText->show();
        m_showText = true;
    } else {
        m_emergencyText->hide();
        m_showText = false;
    }
}

void EmergencyShape::drawEmergencyShape(QPainter *painter)
{
    painter->drawPolygon(basePolygon(rect()));
    painter->translate(m_emergencyRect.center());
    painter->rotate(270);
    painter->translate(-m_emergencyRect.center());
    QTextOption textOption{Qt::AlignCenter};
    painter->drawText(m_emergencyRect, "АСА", textOption);
    painter->translate(m_emergencyRect.center());
    painter->rotate(-270);
    painter->translate(-m_emergencyRect.center());
    qreal sixthWidth{m_emergencyRect.width() / 6}; // 5.0

    if (m_showText) {
        m_emergencyText->setPos(m_emergencyRect.right(), m_emergencyRect.bottom()
                                                             - sixthWidth * 2);
    }

    if (m_showPipes) {
        drawPipes(painter, sixthWidth);
    }

    if (m_showCollector) {
        drawCollector(painter, sixthWidth);
    }
}

void EmergencyShape::drawPipes(QPainter *painter, qreal sixtWidth)
{
    painter->setPen(QPen(Qt::black, 1));
    qreal pipeY{m_emergencyRect.bottom() - sixtWidth};
    QPointF rightPipeP1{m_emergencyRect.right(), pipeY};
    QPointF rightPipeP2{m_emergencyRect.right() + sixtWidth, pipeY};
    painter->drawLine(rightPipeP1, rightPipeP2); // Right pipe

    QPointF rightConnectP1{rightPipeP2.x(), rightPipeP2.y() + sixtWidth / 2};
    QPointF rightConnectP2{rightPipeP2.x(), rightPipeP2.y() - sixtWidth / 2};
    painter->drawLine(rightConnectP1, rightConnectP2); // Right pipe connection

    QPointF leftPipeP1{m_emergencyRect.left(), pipeY};
    QPointF leftPipeP2{m_emergencyRect.left() - sixtWidth, pipeY};
    painter->drawLine(leftPipeP1, leftPipeP2); // Left pipe

    QPointF leftConnectP1{leftPipeP2.x(), leftPipeP2.y() + sixtWidth / 2};
    QPointF leftConnectP2{leftPipeP2.x(), leftPipeP2.y() - sixtWidth / 2};
    painter->drawLine(leftConnectP1, leftConnectP2); // Right pipe connection
}

void EmergencyShape::drawCollector(QPainter *painter, qreal sixtWidth)
{
    painter->setPen(QPen(Qt::black, 1));
    qreal collectorX{m_emergencyRect.center().x()};
    qreal collectorY{m_emergencyRect.bottom() + sixtWidth * 2};
    qreal leftPipeX{collectorX - sixtWidth};
    QPointF leftRightPipeP1{collectorX, m_emergencyRect.bottom()};
    QPointF leftPipeP2{leftPipeX, collectorY};
    painter->drawLine(leftRightPipeP1, leftPipeP2); //Left collector pipe

    qreal rightPipeX{collectorX + sixtWidth};
    QPointF rightPipeP2{rightPipeX, collectorY};
    painter->drawLine(leftRightPipeP1, rightPipeP2); //Right collector pipe

    QPointF leftConnectP1{leftPipeX - sixtWidth / 2, collectorY};
    QPointF leftConnectP2{leftPipeX + sixtWidth / 2, collectorY};
    painter->drawLine(leftConnectP1, leftConnectP2); //Left connector

    QPointF rightConnectP1{rightPipeX - sixtWidth / 2, collectorY};
    QPointF rightConnectP2{rightPipeX + sixtWidth / 2, collectorY};
    painter->drawLine(rightConnectP1, rightConnectP2);  //Right connector
}

AutoLadderShape::AutoLadderShape(QGraphicsItem *parent)
    :TechnicsShape(parent)
    , m_autoLadderType{AutoLadder}
    , m_autoLadderRect{QRectF(-15.0, -37.5, 30.0, 75.0)}
    , m_autoLadderText{nullptr}
    , m_showText{false}
{
        setFlag(ItemSendsGeometryChanges, true);
        setAcceptHoverEvents(true);
        setPen(QPen(Qt::red, 1));
        setBrush(QBrush(Qt::white));
}

void AutoLadderShape::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(widget);

    painter->setRenderHint(QPainter::Antialiasing);
    painter->setRenderHint(QPainter::SmoothPixmapTransform);
    painter->setPen(pen());
    painter->setBrush(brush());

    drawAutoLadderShape(painter);

    if (option->state & QStyle::State_Selected)
        highlightSelected(painter, option);
}

QRectF AutoLadderShape::boundingRect() const
{
    QRectF boundingRect{m_autoLadderRect};
    qreal halfpw{pen().style() == Qt::NoPen ? qreal(0.0) : pen().widthF() / 2};
    if (halfpw > 0.0)
        boundingRect.adjust(-halfpw, -halfpw, halfpw, halfpw);
    return boundingRect;
}

QPainterPath AutoLadderShape::shape() const
{
    QPainterPath path;
    path.addPolygon(basePolygon(rect()));

    return shapeFromPath(path);
}

QPixmap AutoLadderShape::image()
{
    qreal pixmapWidth{boundingRect().width()};
    qreal pixmapHeight{boundingRect().height()};
    QPixmap pixmap(pixmapWidth, pixmapHeight);
    pixmap.fill(Qt::transparent);

    QPainter painter(&pixmap);
    painter.setPen(pen());
    painter.setBrush(brush());
    painter.translate(pixmapWidth / 2.0, pixmapHeight / 2.0);
    drawAutoLadderShape(&painter);

    return pixmap;
}

TechnicsShape::ShapeType AutoLadderShape::shapeType() const
{
    return m_autoLadderType;
}

void AutoLadderShape::setRect(const QRectF &rect)
{
    if (m_autoLadderRect == rect)
        return;

    prepareGeometryChange();
    m_autoLadderRect.setRect(rect.topLeft().x(), rect.topLeft().y(), rect.width(), rect.height());
    if (m_autoLadderText != nullptr)
        m_autoLadderText->setPos(m_autoLadderRect.right(), m_autoLadderRect.bottom()
                                                         - m_autoLadderRect.width() / 6);
    update();
}

QRectF AutoLadderShape::rect() const
{
    return m_autoLadderRect;
}

void AutoLadderShape::setHeight(const qreal &height)
{
    if (m_autoLadderRect.height() == height)
        return;

    qreal oldHeight{m_autoLadderRect.height()};
    prepareGeometryChange();
    m_autoLadderRect.setHeight(height);
    qreal dy{(m_autoLadderRect.height() - oldHeight) / 2};
    m_autoLadderRect.moveTo(QPointF(m_autoLadderRect.x(), m_autoLadderRect.y() - dy));
    update();
}

qreal AutoLadderShape::height() const
{
    return m_autoLadderRect.height();
}

void AutoLadderShape::setText(const QString &text)
{
    if (m_autoLadderText == nullptr) {
        m_autoLadderText = new QGraphicsTextItem(this);
        m_autoLadderText->setTextInteractionFlags(Qt::TextEditorInteraction);
        m_autoLadderText->setRotation(-90);
    }
    m_autoLadderText->setPlainText(text);
    m_showText = true;
}

QString AutoLadderShape::text() const
{
    if (m_autoLadderText == nullptr)
        return "";

    return m_autoLadderText->toPlainText();
}

void AutoLadderShape::mousePressEvent(QGraphicsSceneMouseEvent *mouseEvent)
{
    if (mouseEvent->buttons() == Qt::RightButton) {
        createAction();
        addActions(m_autoLadderActionList);
        QAction menuAction{menu()->exec(mouseEvent->screenPos())};
        QString menuActionText;
        if (menuAction.parent()) {
            menuActionText = menuAction.parent()->objectName();
        }
        if ((menuActionText != "actionDeleteItem") && (menuActionText != "actionCut")) {
            removeActions(m_autoLadderActionList);
            m_autoLadderActionList.clear();
        }
    } else {
        AbstractShape::mousePressEvent(mouseEvent);
    }
}

void AutoLadderShape::createAction()
{
    QString addText{m_showText ? QObject::tr("Hide text") : QObject::tr("Show text")};
    m_addTextAction.reset(new QAction(addText));
    m_addTextAction->setToolTip(QObject::tr("Show or hide text"));
    QObject::connect(m_addTextAction.get(), &QAction::triggered
                     , [this](){m_showText ? textShow(false) : textShow(true);});
    m_autoLadderActionList.append(m_addTextAction.get());
}

void AutoLadderShape::textShow(bool showText)
{
    if (showText) {
        if (m_autoLadderText == nullptr) {
            m_autoLadderText=new QGraphicsTextItem(this);
            m_autoLadderText->setPlainText("АЛ-");
            m_autoLadderText->setTextInteractionFlags(Qt::TextEditorInteraction);
            m_autoLadderText->setRotation(-90);
        }
        m_autoLadderText->show();
        m_showText = true;
    } else {
        m_autoLadderText->hide();
        m_showText = false;
    }
}

void AutoLadderShape::drawAutoLadderShape(QPainter *painter)
{
    painter->drawPolygon(basePolygon(rect()));

    //Draw ladder
    qreal ladderIndent{m_autoLadderRect.width() / 5};
    qreal sixthHeight{m_autoLadderRect.height() / 6};
    QPointF leftBottomBowstring{m_autoLadderRect.left() + ladderIndent
                                , m_autoLadderRect.bottom() - ladderIndent};
    QPointF leftTopBowstring{m_autoLadderRect.left() + ladderIndent
                             , m_autoLadderRect.center().y() - sixthHeight};
    QLineF leftBowstring{leftTopBowstring, leftBottomBowstring};
    painter->drawLine(leftBowstring); //Left bowstring

    QPointF rightBottomBowstrin{m_autoLadderRect.right() - ladderIndent
                                , m_autoLadderRect.bottom() - ladderIndent};
    QPointF rightTopBowstring{m_autoLadderRect.right() - ladderIndent
                              , m_autoLadderRect.center().y() - sixthHeight};
    QLineF rightBowstring{rightTopBowstring, rightBottomBowstrin};
    painter->drawLine(rightBowstring); //Right bowstring

    qreal stepDistanse{leftBowstring.length() / 11.0};
    qreal stepY{leftBottomBowstring.y() - stepDistanse};
    for (int i = 0; i < 10; ++i) {
        QPointF leftStep{leftBottomBowstring.x(), stepY};
        QPointF rightStep{rightBottomBowstrin.x(), stepY};
        painter->drawLine(leftStep, rightStep); //Step
        stepY -= stepDistanse;
    }


    if (m_showText)
        m_autoLadderText->setPos(m_autoLadderRect.right(), m_autoLadderRect.bottom());
}

CrankLiftShape::CrankLiftShape(QGraphicsItem *parent)
    :TechnicsShape(parent)
    , m_crankLiftType{CrankLift}
    , m_crankLiftRect{QRectF(-15.0, -37.5, 30.0, 75.0)}
    , m_crankLiftText{nullptr}
    , m_showText{false}
{
    setFlag(ItemSendsGeometryChanges, true);
    setAcceptHoverEvents(true);
    setPen(QPen(Qt::red, 1));
    setBrush(QBrush(Qt::white));
}

void CrankLiftShape::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(widget);

    painter->setRenderHint(QPainter::Antialiasing);
    painter->setRenderHint(QPainter::SmoothPixmapTransform);
    painter->setPen(pen());
    painter->setBrush(brush());

    drawCrankLiftShape(painter);

    if (option->state & QStyle::State_Selected)
        highlightSelected(painter, option);
}

QRectF CrankLiftShape::boundingRect() const
{
    QRectF boundingRect{m_crankLiftRect};
    qreal halfpw{pen().style() == Qt::NoPen ? qreal(0.0) : pen().widthF() / 2};
    if (halfpw > 0.0)
        boundingRect.adjust(-halfpw, -halfpw, halfpw, halfpw);
    return boundingRect;
}

QPainterPath CrankLiftShape::shape() const
{
    QPainterPath path;
    path.addPolygon(basePolygon(rect()));

    return shapeFromPath(path);
}

QPixmap CrankLiftShape::image()
{
    qreal pixmapWidth{boundingRect().width()};
    qreal pixmapHeight{boundingRect().height()};
    QPixmap pixmap(pixmapWidth, pixmapHeight);
    pixmap.fill(Qt::transparent);

    QPainter painter(&pixmap);
    painter.setPen(pen());
    painter.setBrush(brush());
    painter.translate(pixmapWidth / 2.0, pixmapHeight / 2.0);
    drawCrankLiftShape(&painter);

    return pixmap;
}

TechnicsShape::ShapeType CrankLiftShape::shapeType() const
{
    return m_crankLiftType;
}

void CrankLiftShape::setRect(const QRectF &rect)
{
    if (m_crankLiftRect == rect)
        return;

    prepareGeometryChange();
    m_crankLiftRect.setRect(rect.topLeft().x(), rect.topLeft().y(), rect.width(), rect.height());
    if (m_crankLiftText != nullptr)
        m_crankLiftText->setPos(m_crankLiftRect.right(), m_crankLiftRect.bottom()
                                                             - m_crankLiftRect.width() / 6);
    update();
}

QRectF CrankLiftShape::rect() const
{
    return m_crankLiftRect;
}

void CrankLiftShape::setHeight(const qreal &height)
{
    if (m_crankLiftRect.height() == height)
        return;

    qreal oldHeight{m_crankLiftRect.height()};
    prepareGeometryChange();
    m_crankLiftRect.setHeight(height);
    qreal dy{(m_crankLiftRect.height() - oldHeight) / 2};
    m_crankLiftRect.moveTo(QPointF(m_crankLiftRect.x(), m_crankLiftRect.y() - dy));
    update();
}

qreal CrankLiftShape::height() const
{
    return m_crankLiftRect.height();
}

void CrankLiftShape::setText(const QString &text)
{
    if (m_crankLiftText == nullptr) {
        m_crankLiftText = new QGraphicsTextItem(this);
        m_crankLiftText->setTextInteractionFlags(Qt::TextEditorInteraction);
        m_crankLiftText->setRotation(-90);
    }
    m_crankLiftText->setPlainText(text);
    m_showText = true;
}

QString CrankLiftShape::text() const
{
    if (m_crankLiftText == nullptr)
        return "";

    return m_crankLiftText->toPlainText();
}

void CrankLiftShape::mousePressEvent(QGraphicsSceneMouseEvent *mouseEvent)
{
    if (mouseEvent->buttons() == Qt::RightButton) {
        createAction();
        addActions(m_crankLiftActionList);
        QAction menuAction{menu()->exec(mouseEvent->screenPos())};
        QString menuActionText;
        if (menuAction.parent()) {
            menuActionText = menuAction.parent()->objectName();
        }
        if ((menuActionText != "actionDeleteItem") && (menuActionText != "actionCut")) {
            removeActions(m_crankLiftActionList);
            m_crankLiftActionList.clear();
        }
    } else {
        AbstractShape::mousePressEvent(mouseEvent);
    }
}

void CrankLiftShape::createAction()
{
    QString addText{m_showText ? QObject::tr("Hide text") : QObject::tr("Show text")};
    m_addTextAction.reset(new QAction(addText));
    m_addTextAction->setToolTip(QObject::tr("Show or hide text"));
    QObject::connect(m_addTextAction.get(), &QAction::triggered
                     , [this](){m_showText ? textShow(false) : textShow(true);});
    m_crankLiftActionList.append(m_addTextAction.get());
}

void CrankLiftShape::textShow(bool showText)
{
    if (showText) {
        if (m_crankLiftText == nullptr) {
            m_crankLiftText=new QGraphicsTextItem(this);
            m_crankLiftText->setPlainText("АПК-");
            m_crankLiftText->setTextInteractionFlags(Qt::TextEditorInteraction);
            m_crankLiftText->setRotation(-90);
        }
        m_crankLiftText->show();
        m_showText = true;
    } else {
        m_crankLiftText->hide();
        m_showText = false;
    }
}

void CrankLiftShape::drawCrankLiftShape(QPainter *painter)
{
    painter->drawPolygon(basePolygon(rect()));

    //Draw ladder
    qreal sixthHeight{m_crankLiftRect.height() / 6};
    qreal crankIndent{m_crankLiftRect.width() / 5};
    QPointF leftBottomBowstring{m_crankLiftRect.left() + crankIndent
                                , m_crankLiftRect.bottom() - crankIndent};
    QPointF leftTopBowstring{m_crankLiftRect.left() + crankIndent
                             , m_crankLiftRect.center().y() - sixthHeight};
    QLineF leftBowstring{leftTopBowstring, leftBottomBowstring};
    painter->drawLine(leftBowstring); //Left bowstring

    QPointF rightBottomBowstrin{m_crankLiftRect.right() - crankIndent
                                , m_crankLiftRect.bottom() - crankIndent};
    QPointF rightTopBowstring{m_crankLiftRect.right() - crankIndent
                              , m_crankLiftRect.center().y() - sixthHeight};
    QLineF rightBowstring{rightTopBowstring, rightBottomBowstrin};
    painter->drawLine(rightBowstring); //Right bowstring

    QLineF centerBowstring{leftBottomBowstring, rightTopBowstring};
    painter->drawLine(centerBowstring); //Center bowstring


    if (m_showText)
        m_crankLiftText->setPos(m_crankLiftRect.right(), m_crankLiftRect.bottom());
}

TelescopicLiftShape::TelescopicLiftShape(QGraphicsItem *parent)
    :TechnicsShape(parent)
    , m_telescopicLiftType{TelescopicLift}
    , m_telescopicLiftRect{QRectF(-15.0, -37.5, 30.0, 75.0)}
    , m_telescopicLiftText{nullptr}
    , m_showText{false}
{
    setFlag(ItemSendsGeometryChanges, true);
    setAcceptHoverEvents(true);
    setPen(QPen(Qt::red, 1));
    setBrush(QBrush(Qt::white));
}

void TelescopicLiftShape::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(widget);

    painter->setRenderHint(QPainter::Antialiasing);
    painter->setRenderHint(QPainter::SmoothPixmapTransform);
    painter->setPen(pen());
    painter->setBrush(brush());

    drawTelescopicLiftShape(painter);

    if (option->state & QStyle::State_Selected)
        highlightSelected(painter, option);
}

QRectF TelescopicLiftShape::boundingRect() const
{
    QRectF boundingRect{m_telescopicLiftRect};
    qreal halfpw{pen().style() == Qt::NoPen ? qreal(0.0) : pen().widthF() / 2};
    if (halfpw > 0.0)
        boundingRect.adjust(-halfpw, -halfpw, halfpw, halfpw);
    return boundingRect;
}

QPainterPath TelescopicLiftShape::shape() const
{
    QPainterPath path;
    path.addPolygon(basePolygon(rect()));

    return shapeFromPath(path);
}

QPixmap TelescopicLiftShape::image()
{
    qreal pixmapWidth{boundingRect().width()};
    qreal pixmapHeight{boundingRect().height()};
    QPixmap pixmap(pixmapWidth, pixmapHeight);
    pixmap.fill(Qt::transparent);

    QPainter painter(&pixmap);
    painter.setPen(pen());
    painter.setBrush(brush());
    painter.translate(pixmapWidth / 2.0, pixmapHeight / 2.0);
    drawTelescopicLiftShape(&painter);

    return pixmap;
}

TechnicsShape::ShapeType TelescopicLiftShape::shapeType() const
{
    return m_telescopicLiftType;
}

void TelescopicLiftShape::setRect(const QRectF &rect)
{
    if (m_telescopicLiftRect == rect)
        return;

    prepareGeometryChange();
    m_telescopicLiftRect.setRect(rect.topLeft().x(), rect.topLeft().y(), rect.width()
                                 , rect.height());
    if (m_telescopicLiftText != nullptr)
        m_telescopicLiftText->setPos(m_telescopicLiftRect.right(), m_telescopicLiftRect.bottom()
                                                             - m_telescopicLiftRect.width() / 6);
    update();
}

QRectF TelescopicLiftShape::rect() const
{
    return m_telescopicLiftRect;
}

void TelescopicLiftShape::setHeight(const qreal &height)
{
    if (m_telescopicLiftRect.height() == height)
        return;

    qreal oldHeight{m_telescopicLiftRect.height()};
    prepareGeometryChange();
    m_telescopicLiftRect.setHeight(height);
    qreal dy{(m_telescopicLiftRect.height() - oldHeight) / 2};
    m_telescopicLiftRect.moveTo(QPointF(m_telescopicLiftRect.x(), m_telescopicLiftRect.y() - dy));
    update();
}

qreal TelescopicLiftShape::height() const
{
    return m_telescopicLiftRect.height();
}

void TelescopicLiftShape::setText(const QString &text)
{
    if (m_telescopicLiftText == nullptr) {
        m_telescopicLiftText = new QGraphicsTextItem(this);
        m_telescopicLiftText->setTextInteractionFlags(Qt::TextEditorInteraction);
        m_telescopicLiftText->setRotation(-90);
    }
    m_telescopicLiftText->setPlainText(text);
    m_showText = true;
}

QString TelescopicLiftShape::text() const
{
    if (m_telescopicLiftText == nullptr)
        return "";

    return m_telescopicLiftText->toPlainText();
}

void TelescopicLiftShape::mousePressEvent(QGraphicsSceneMouseEvent *mouseEvent)
{
    if (mouseEvent->buttons() == Qt::RightButton) {
        createAction();
        addActions(m_telescopicLiftActionList);
        QAction menuAction{menu()->exec(mouseEvent->screenPos())};
        QString menuActionText;
        if (menuAction.parent()) {
            menuActionText = menuAction.parent()->objectName();
        }
        if ((menuActionText != "actionDeleteItem") && (menuActionText != "actionCut")) {
            removeActions(m_telescopicLiftActionList);
            m_telescopicLiftActionList.clear();
        }
    } else {
        AbstractShape::mousePressEvent(mouseEvent);
    }
}

void TelescopicLiftShape::createAction()
{
    QString addText{m_showText ? QObject::tr("Hide text") : QObject::tr("Show text")};
    m_addTextAction.reset(new QAction(addText));
    m_addTextAction->setToolTip(QObject::tr("Show or hide text"));
    QObject::connect(m_addTextAction.get(), &QAction::triggered
                     , [this](){m_showText ? textShow(false) : textShow(true);});
    m_telescopicLiftActionList.append(m_addTextAction.get());
}

void TelescopicLiftShape::textShow(bool showText)
{
    if (showText) {
        if (m_telescopicLiftText == nullptr) {
            m_telescopicLiftText=new QGraphicsTextItem(this);
            m_telescopicLiftText->setPlainText("ТПЛ-");
            m_telescopicLiftText->setTextInteractionFlags(Qt::TextEditorInteraction);
            m_telescopicLiftText->setRotation(-90);
        }
        m_telescopicLiftText->show();
        m_showText = true;
    } else {
        m_telescopicLiftText->hide();
        m_showText = false;
    }
}

void TelescopicLiftShape::drawTelescopicLiftShape(QPainter *painter)
{
    painter->drawPolygon(basePolygon(rect()));

    //Draw ladder
    qreal sixthHeight{m_telescopicLiftRect.height() / 6};
    qreal telescopicIndent{m_telescopicLiftRect.width() / 5};
    QPointF leftBottomBowstring{m_telescopicLiftRect.left() + telescopicIndent
                                , m_telescopicLiftRect.bottom() - telescopicIndent};
    QPointF leftTopBowstring{m_telescopicLiftRect.left() + telescopicIndent
                             , m_telescopicLiftRect.center().y() - sixthHeight};
    QLineF leftBowstring{leftTopBowstring, leftBottomBowstring};
    painter->drawLine(leftBowstring); //Left bowstring

    QPointF rightBottomBowstrin{m_telescopicLiftRect.right() - telescopicIndent
                                , m_telescopicLiftRect.bottom() - telescopicIndent};
    QPointF rightTopBowstring{m_telescopicLiftRect.right() - telescopicIndent
                              , m_telescopicLiftRect.center().y() - sixthHeight};
    QLineF rightBowstring{rightTopBowstring, rightBottomBowstrin};
    painter->drawLine(rightBowstring); //Right bowstring

    QPointF centerTopBowstring{m_telescopicLiftRect.center().x()
                               , m_telescopicLiftRect.top() + sixthHeight};
    QPointF centerBottomBowstring{m_telescopicLiftRect.center().x()
                                  , centerTopBowstring.y() + leftBowstring.length()};
    QLineF centerBowstring{centerBottomBowstring, centerTopBowstring};
    painter->drawLine(centerBowstring); //Center bowstring


    if (m_showText)
        m_telescopicLiftText->setPos(m_telescopicLiftRect.right(), m_telescopicLiftRect.bottom());
}

HoseCarShape::HoseCarShape(QGraphicsItem *parent)
    :TechnicsShape(parent)
    , m_hoseCarType{HoseCar}
    , m_hoseCarRect{QRectF(-15.0, -37.5, 30.0, 75.0)}
    , m_hoseCarText{nullptr}
    , m_showText{false}
{
    setFlag(ItemSendsGeometryChanges, true);
    setAcceptHoverEvents(true);
    setPen(QPen(Qt::red, 1));
    setBrush(QBrush(Qt::white));
}

void HoseCarShape::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(widget);

    painter->setRenderHint(QPainter::Antialiasing);
    painter->setRenderHint(QPainter::SmoothPixmapTransform);
    painter->setPen(pen());
    painter->setBrush(brush());

    drawHoseCarShape(painter);

    if (option->state & QStyle::State_Selected)
        highlightSelected(painter, option);
}

QRectF HoseCarShape::boundingRect() const
{
    QRectF boundingRect{m_hoseCarRect};
    qreal halfpw{pen().style() == Qt::NoPen ? qreal(0.0) : pen().widthF() / 2};
    if (halfpw > 0.0)
        boundingRect.adjust(-halfpw, -halfpw, halfpw, halfpw);
    return boundingRect;
}

QPainterPath HoseCarShape::shape() const
{
    QPainterPath path;
    path.addPolygon(basePolygon(rect()));

    return shapeFromPath(path);
}

QPixmap HoseCarShape::image()
{
    qreal pixmapWidth{boundingRect().width()};
    qreal pixmapHeight{boundingRect().height()};
    QPixmap pixmap(pixmapWidth, pixmapHeight);
    pixmap.fill(Qt::transparent);

    QPainter painter(&pixmap);
    painter.setPen(pen());
    painter.setBrush(brush());
    painter.translate(pixmapWidth / 2.0, pixmapHeight / 2.0);
    drawHoseCarShape(&painter);

    return pixmap;
}

TechnicsShape::ShapeType HoseCarShape::shapeType() const
{
    return m_hoseCarType;
}

void HoseCarShape::setRect(const QRectF &rect)
{
    if (m_hoseCarRect == rect)
        return;

    prepareGeometryChange();
    m_hoseCarRect.setRect(rect.topLeft().x(), rect.topLeft().y(), rect.width(), rect.height());
    if (m_hoseCarText != nullptr)
        m_hoseCarText->setPos(m_hoseCarRect.right(), m_hoseCarRect.bottom()
                                                         - m_hoseCarRect.width() / 6);
    update();
}

QRectF HoseCarShape::rect() const
{
    return m_hoseCarRect;
}

void HoseCarShape::setHeight(const qreal &height)
{
    if (m_hoseCarRect.height() == height)
        return;

    qreal oldHeight{m_hoseCarRect.height()};
    prepareGeometryChange();
    m_hoseCarRect.setHeight(height);
    qreal dy{(m_hoseCarRect.height() - oldHeight) / 2};
    m_hoseCarRect.moveTo(QPointF(m_hoseCarRect.x(), m_hoseCarRect.y() - dy));
    update();
}

qreal HoseCarShape::height() const
{
    return m_hoseCarRect.height();
}

void HoseCarShape::setText(const QString &text)
{
    if (m_hoseCarText == nullptr) {
        m_hoseCarText = new QGraphicsTextItem(this);
        m_hoseCarText->setTextInteractionFlags(Qt::TextEditorInteraction);
        m_hoseCarText->setRotation(-90);
    }
    m_hoseCarText->setPlainText(text);
    m_showText = true;
}

QString HoseCarShape::text() const
{
    if (m_hoseCarText == nullptr)
        return "";

    return m_hoseCarText->toPlainText();
}

void HoseCarShape::mousePressEvent(QGraphicsSceneMouseEvent *mouseEvent)
{
    if (mouseEvent->buttons() == Qt::RightButton) {
        createAction();
        addActions(m_hoseCarActionList);
        QAction menuAction{menu()->exec(mouseEvent->screenPos())};
        QString menuActionText;
        if (menuAction.parent()) {
            menuActionText = menuAction.parent()->objectName();
        }
        if ((menuActionText != "actionDeleteItem") && (menuActionText != "actionCut")) {
            removeActions(m_hoseCarActionList);
            m_hoseCarActionList.clear();
        }
    } else {
        AbstractShape::mousePressEvent(mouseEvent);
    }
}

void HoseCarShape::createAction()
{
    QString addText{m_showText ? QObject::tr("Hide text") : QObject::tr("Show text")};
    m_addTextAction.reset(new QAction(addText));
    m_addTextAction->setToolTip(QObject::tr("Show or hide text"));
    QObject::connect(m_addTextAction.get(), &QAction::triggered
                     , [this](){m_showText ? textShow(false) : textShow(true);});
    m_hoseCarActionList.append(m_addTextAction.get());
}

void HoseCarShape::textShow(bool showText)
{
    if (showText) {
        if (m_hoseCarText == nullptr) {
            m_hoseCarText=new QGraphicsTextItem(this);
            m_hoseCarText->setPlainText("АР-");
            m_hoseCarText->setTextInteractionFlags(Qt::TextEditorInteraction);
            m_hoseCarText->setRotation(-90);
        }
        m_hoseCarText->show();
        m_showText = true;
    } else {
        m_hoseCarText->hide();
        m_showText = false;
    }
}

void HoseCarShape::drawHoseCarShape(QPainter *painter)
{
    painter->drawPolygon(basePolygon(rect()));
    painter->translate(m_hoseCarRect.center());
    painter->rotate(270);
    painter->translate(-m_hoseCarRect.center());
    QTextOption textOption{Qt::AlignCenter};
    painter->drawText(m_hoseCarRect, "АР", textOption);
    painter->translate(m_hoseCarRect.center());
    painter->rotate(-270);
    painter->translate(-m_hoseCarRect.center());

    if (m_showText)
        m_hoseCarText->setPos(m_hoseCarRect.right(), m_hoseCarRect.bottom());
}

CommShape::CommShape(QGraphicsItem *parent)
    :TechnicsShape(parent)
    , m_commType{Comm}
    , m_commRect{QRectF(-15.0, -37.5, 30.0, 75.0)}
    , m_commText{nullptr}
    , m_showText{false}
{
    setFlag(ItemSendsGeometryChanges, true);
    setAcceptHoverEvents(true);
    setPen(QPen(Qt::red, 1));
    setBrush(QBrush(Qt::white));
}

void CommShape::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(widget);

    painter->setRenderHint(QPainter::Antialiasing);
    painter->setRenderHint(QPainter::SmoothPixmapTransform);
    painter->setPen(pen());
    painter->setBrush(brush());

    drawCommShape(painter);

    if (option->state & QStyle::State_Selected)
        highlightSelected(painter, option);
}

QRectF CommShape::boundingRect() const
{
    QRectF boundingRect{m_commRect};
    qreal halfpw{pen().style() == Qt::NoPen ? qreal(0.0) : pen().widthF() / 2};
    if (halfpw > 0.0)
        boundingRect.adjust(-halfpw, -halfpw, halfpw, halfpw);
    return boundingRect;
}

QPainterPath CommShape::shape() const
{
    QPainterPath path;
    path.addPolygon(basePolygon(rect()));

    return shapeFromPath(path);
}

QPixmap CommShape::image()
{
    qreal pixmapWidth{boundingRect().width()};
    qreal pixmapHeight{boundingRect().height()};
    QPixmap pixmap(pixmapWidth, pixmapHeight);
    pixmap.fill(Qt::transparent);

    QPainter painter(&pixmap);
    painter.setPen(pen());
    painter.setBrush(brush());
    painter.translate(pixmapWidth / 2.0, pixmapHeight / 2.0);
    drawCommShape(&painter);

    return pixmap;
}

TechnicsShape::ShapeType CommShape::shapeType() const
{
    return m_commType;
}

void CommShape::setRect(const QRectF &rect)
{
    if (m_commRect == rect)
        return;

    prepareGeometryChange();
    m_commRect.setRect(rect.topLeft().x(), rect.topLeft().y(), rect.width(), rect.height());
    if (m_commText != nullptr)
        m_commText->setPos(m_commRect.right(), m_commRect.bottom() - m_commRect.width() / 6);
    update();
}

QRectF CommShape::rect() const
{
    return m_commRect;
}

void CommShape::setHeight(const qreal &height)
{
    if (m_commRect.height() == height)
        return;

    qreal oldHeight{m_commRect.height()};
    prepareGeometryChange();
    m_commRect.setHeight(height);
    qreal dy{(m_commRect.height() - oldHeight) / 2};
    m_commRect.moveTo(QPointF(m_commRect.x(), m_commRect.y() - dy));
    update();
}

qreal CommShape::height() const
{
    return m_commRect.height();
}

void CommShape::setText(const QString &text)
{
    if (m_commText == nullptr) {
        m_commText = new QGraphicsTextItem(this);
        m_commText->setTextInteractionFlags(Qt::TextEditorInteraction);
        m_commText->setRotation(-90);
    }
    m_commText->setPlainText(text);
    m_showText = true;
}

QString CommShape::text() const
{
    if (m_commText == nullptr)
        return "";

    return m_commText->toPlainText();
}

void CommShape::mousePressEvent(QGraphicsSceneMouseEvent *mouseEvent)
{
    if (mouseEvent->buttons() == Qt::RightButton) {
        createAction();
        addActions(m_commActionList);
        QAction menuAction{menu()->exec(mouseEvent->screenPos())};
        QString menuActionText;
        if (menuAction.parent()) {
            menuActionText = menuAction.parent()->objectName();
        }
        if ((menuActionText != "actionDeleteItem") && (menuActionText != "actionCut")) {
            removeActions(m_commActionList);
            m_commActionList.clear();
        }
    } else {
        AbstractShape::mousePressEvent(mouseEvent);
    }
}

void CommShape::createAction()
{
    QString addText{m_showText ? QObject::tr("Hide text") : QObject::tr("Show text")};
    m_addTextAction.reset(new QAction(addText));
    m_addTextAction->setToolTip(QObject::tr("Show or hide text"));
    QObject::connect(m_addTextAction.get(), &QAction::triggered
                     , [this](){m_showText ? textShow(false) : textShow(true);});
    m_commActionList.append(m_addTextAction.get());
}

void CommShape::textShow(bool showText)
{
    if (showText) {
        if (m_commText == nullptr) {
            m_commText=new QGraphicsTextItem(this);
            m_commText->setPlainText("АСО-");
            m_commText->setTextInteractionFlags(Qt::TextEditorInteraction);
            m_commText->setRotation(-90);
        }
        m_commText->show();
        m_showText = true;
    } else {
        m_commText->hide();
        m_showText = false;
    }
}

void CommShape::drawCommShape(QPainter *painter)
{
    painter->drawPolygon(basePolygon(rect()));
    painter->translate(m_commRect.center());
    painter->rotate(270);
    painter->translate(-m_commRect.center());
    QTextOption textOption{Qt::AlignCenter};
    painter->drawText(m_commRect, "АСО", textOption);
    painter->translate(m_commRect.center());
    painter->rotate(-270);
    painter->translate(-m_commRect.center());

    if (m_showText)
        m_commText->setPos(m_commRect.right(), m_commRect.bottom());
}

TechServShape::TechServShape(QGraphicsItem *parent)
    :TechnicsShape(parent)
    , m_techServType{TechServ}
    , m_techServRect{QRectF(-15.0, -37.5, 30.0, 75.0)}
    , m_techServText{nullptr}
    , m_showText{false}
{
    setFlag(ItemSendsGeometryChanges, true);
    setAcceptHoverEvents(true);
    setPen(QPen(Qt::red, 1));
    setBrush(QBrush(Qt::white));
}

void TechServShape::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(widget);

    painter->setRenderHint(QPainter::Antialiasing);
    painter->setRenderHint(QPainter::SmoothPixmapTransform);
    painter->setPen(pen());
    painter->setBrush(brush());

    drawTechServShape(painter);

    if (option->state & QStyle::State_Selected)
        highlightSelected(painter, option);
}

QRectF TechServShape::boundingRect() const
{
    QRectF boundingRect{m_techServRect};
    qreal halfpw{pen().style() == Qt::NoPen ? qreal(0.0) : pen().widthF() / 2};
    if (halfpw > 0.0)
        boundingRect.adjust(-halfpw, -halfpw, halfpw, halfpw);
    return boundingRect;
}

QPainterPath TechServShape::shape() const
{
    QPainterPath path;
    path.addPolygon(basePolygon(rect()));

    return shapeFromPath(path);
}

QPixmap TechServShape::image()
{
    qreal pixmapWidth{boundingRect().width()};
    qreal pixmapHeight{boundingRect().height()};
    QPixmap pixmap(pixmapWidth, pixmapHeight);
    pixmap.fill(Qt::transparent);

    QPainter painter(&pixmap);
    painter.setPen(pen());
    painter.setBrush(brush());
    painter.translate(pixmapWidth / 2.0, pixmapHeight / 2.0);
    drawTechServShape(&painter);

    return pixmap;
}

TechnicsShape::ShapeType TechServShape::shapeType() const
{
    return m_techServType;
}

void TechServShape::setRect(const QRectF &rect)
{
    if (m_techServRect == rect)
        return;

    prepareGeometryChange();
    m_techServRect.setRect(rect.topLeft().x(), rect.topLeft().y(), rect.width(), rect.height());
    if (m_techServText != nullptr)
        m_techServText->setPos(m_techServRect.right(), m_techServRect.bottom()
                                                           - m_techServRect.width() / 6);
    update();
}

QRectF TechServShape::rect() const
{
    return m_techServRect;
}

void TechServShape::setHeight(const qreal &height)
{
    if (m_techServRect.height() == height)
        return;

    qreal oldHeight{m_techServRect.height()};
    prepareGeometryChange();
    m_techServRect.setHeight(height);
    qreal dy{(m_techServRect.height() - oldHeight) / 2};
    m_techServRect.moveTo(QPointF(m_techServRect.x(), m_techServRect.y() - dy));
    update();
}

qreal TechServShape::height() const
{
    return m_techServRect.height();
}

void TechServShape::setText(const QString &text)
{
    if (m_techServText == nullptr) {
        m_techServText = new QGraphicsTextItem(this);
        m_techServText->setTextInteractionFlags(Qt::TextEditorInteraction);
        m_techServText->setRotation(-90);
    }
    m_techServText->setPlainText(text);
    m_showText = true;
}

QString TechServShape::text() const
{
    if (m_techServText == nullptr)
        return "";

    return m_techServText->toPlainText();
}

void TechServShape::mousePressEvent(QGraphicsSceneMouseEvent *mouseEvent)
{
    if (mouseEvent->buttons() == Qt::RightButton) {
        createAction();
        addActions(m_techServActionList);
        QAction menuAction{menu()->exec(mouseEvent->screenPos())};
        QString menuActionText;
        if (menuAction.parent()) {
            menuActionText = menuAction.parent()->objectName();
        }
        if ((menuActionText != "actionDeleteItem") && (menuActionText != "actionCut")) {
            removeActions(m_techServActionList);
            m_techServActionList.clear();
        }
    } else {
        AbstractShape::mousePressEvent(mouseEvent);
    }
}

void TechServShape::createAction()
{
    QString addText{m_showText ? QObject::tr("Hide text") : QObject::tr("Show text")};
    m_addTextAction.reset(new QAction(addText));
    m_addTextAction->setToolTip(QObject::tr("Show or hide text"));
    QObject::connect(m_addTextAction.get(), &QAction::triggered
                     , [this](){m_showText ? textShow(false) : textShow(true);});
    m_techServActionList.append(m_addTextAction.get());
}

void TechServShape::textShow(bool showText)
{
    if (showText) {
        if (m_techServText == nullptr) {
            m_techServText=new QGraphicsTextItem(this);
            m_techServText->setPlainText("АТ-");
            m_techServText->setTextInteractionFlags(Qt::TextEditorInteraction);
            m_techServText->setRotation(-90);
        }
        m_techServText->show();
        m_showText = true;
    } else {
        m_techServText->hide();
        m_showText = false;
    }
}

void TechServShape::drawTechServShape(QPainter *painter)
{
    painter->drawPolygon(basePolygon(rect()));
    painter->translate(m_techServRect.center());
    painter->rotate(270);
    painter->translate(-m_techServRect.center());
    QTextOption textOption{Qt::AlignCenter};
    painter->drawText(m_techServRect, "АТ", textOption);
    painter->translate(m_techServRect.center());
    painter->rotate(-270);
    painter->translate(-m_techServRect.center());

    if (m_showText)
        m_techServText->setPos(m_techServRect.right(), m_techServRect.bottom());
}

SmokRemShape::SmokRemShape(QGraphicsItem *parent)
    :TechnicsShape(parent)
    , m_smokRemType{SmokRem}
    , m_smokRemRect{QRectF(-15.0, -37.5, 30.0, 75.0)}
    , m_smokRemText{nullptr}
    , m_showText{false}
{
    setFlag(ItemSendsGeometryChanges, true);
    setAcceptHoverEvents(true);
    setPen(QPen(Qt::red, 1));
    setBrush(QBrush(Qt::white));
}

void SmokRemShape::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(widget);

    painter->setRenderHint(QPainter::Antialiasing);
    painter->setRenderHint(QPainter::SmoothPixmapTransform);
    painter->setPen(pen());
    painter->setBrush(brush());

    drawSmokRemShape(painter);

    if (option->state & QStyle::State_Selected)
        highlightSelected(painter, option);
}

QRectF SmokRemShape::boundingRect() const
{
    QRectF boundingRect{m_smokRemRect};
    qreal halfpw{pen().style() == Qt::NoPen ? qreal(0.0) : pen().widthF() / 2};
    if (halfpw > 0.0)
        boundingRect.adjust(-halfpw, -halfpw, halfpw, halfpw);
    return boundingRect;
}

QPainterPath SmokRemShape::shape() const
{
    QPainterPath path;
    path.addPolygon(basePolygon(rect()));

    return shapeFromPath(path);
}

QPixmap SmokRemShape::image()
{
    qreal pixmapWidth{boundingRect().width()};
    qreal pixmapHeight{boundingRect().height()};
    QPixmap pixmap(pixmapWidth, pixmapHeight);
    pixmap.fill(Qt::transparent);

    QPainter painter(&pixmap);
    painter.setPen(pen());
    painter.setBrush(brush());
    painter.translate(pixmapWidth / 2.0, pixmapHeight / 2.0);
    drawSmokRemShape(&painter);

    return pixmap;
}

TechnicsShape::ShapeType SmokRemShape::shapeType() const
{
    return m_smokRemType;
}

void SmokRemShape::setRect(const QRectF &rect)
{
    if (m_smokRemRect == rect)
        return;

    prepareGeometryChange();
    m_smokRemRect.setRect(rect.topLeft().x(), rect.topLeft().y(), rect.width(), rect.height());
    if (m_smokRemText != nullptr)
        m_smokRemText->setPos(m_smokRemRect.right(), m_smokRemRect.bottom()
                                                         - m_smokRemRect.width() / 6);
    update();
}

QRectF SmokRemShape::rect() const
{
    return m_smokRemRect;
}

void SmokRemShape::setHeight(const qreal &height)
{
    if (m_smokRemRect.height() == height)
        return;

    qreal oldHeight{m_smokRemRect.height()};
    prepareGeometryChange();
    m_smokRemRect.setHeight(height);
    qreal dy{(m_smokRemRect.height() - oldHeight) / 2};
    m_smokRemRect.moveTo(QPointF(m_smokRemRect.x(), m_smokRemRect.y() - dy));
    update();
}

qreal SmokRemShape::height() const
{
    return m_smokRemRect.height();
}

void SmokRemShape::setText(const QString &text)
{
    if (m_smokRemText == nullptr) {
        m_smokRemText = new QGraphicsTextItem(this);
        m_smokRemText->setTextInteractionFlags(Qt::TextEditorInteraction);
        m_smokRemText->setRotation(-90);
    }
    m_smokRemText->setPlainText(text);
    m_showText = true;
}

QString SmokRemShape::text() const
{
    if (m_smokRemText == nullptr)
        return "";

    return m_smokRemText->toPlainText();
}

void SmokRemShape::mousePressEvent(QGraphicsSceneMouseEvent *mouseEvent)
{
    if (mouseEvent->buttons() == Qt::RightButton) {
        createAction();
        addActions(m_smokRemActionList);
        QAction menuAction{menu()->exec(mouseEvent->screenPos())};
        QString menuActionText;
        if (menuAction.parent()) {
            menuActionText = menuAction.parent()->objectName();
        }
        if ((menuActionText != "actionDeleteItem") && (menuActionText != "actionCut")) {
            removeActions(m_smokRemActionList);
            m_smokRemActionList.clear();
        }
    } else {
        AbstractShape::mousePressEvent(mouseEvent);
    }
}

void SmokRemShape::createAction()
{
    QString addText{m_showText ? QObject::tr("Hide text") : QObject::tr("Show text")};
    m_addTextAction.reset(new QAction(addText));
    m_addTextAction->setToolTip(QObject::tr("Show or hide text"));
    QObject::connect(m_addTextAction.get(), &QAction::triggered
                     , [this](){m_showText ? textShow(false) : textShow(true);});
    m_smokRemActionList.append(m_addTextAction.get());
}

void SmokRemShape::textShow(bool showText)
{
    if (showText) {
        if (m_smokRemText == nullptr) {
            m_smokRemText=new QGraphicsTextItem(this);
            m_smokRemText->setPlainText("АД-");
            m_smokRemText->setTextInteractionFlags(Qt::TextEditorInteraction);
            m_smokRemText->setRotation(-90);
        }
        m_smokRemText->show();
        m_showText = true;
    } else {
        m_smokRemText->hide();
        m_showText = false;
    }
}

void SmokRemShape::drawSmokRemShape(QPainter *painter)
{
    painter->drawPolygon(basePolygon(rect()));

    //Draw exhauster
    qreal thirdWidth{m_smokRemRect.width() / 3}; // 10.0
    qreal fifthHeight{m_smokRemRect.height() / 5}; // 15.0
    qreal ellipseCenterX{m_smokRemRect.center().x()};
    qreal ellipseCenterY{m_smokRemRect.center().y() + fifthHeight}; // (0.0, 15.0)
    QPointF ellipseCenter{ellipseCenterX, ellipseCenterY};
    // Point on a circle. x = x0 + r * cos(a); y = y0 + r * sin(a)
    // Starts at 3 o'clock, direction clockwise.
    QPointF leftTop{ellipseCenterX + thirdWidth * qCos(qDegreesToRadians(250.0)),
                    ellipseCenterY + thirdWidth * qSin(qDegreesToRadians(250.0))};
    QPointF rightTop{ellipseCenterX + thirdWidth * qCos(qDegreesToRadians(20.0)),
                     ellipseCenterY + thirdWidth * qSin(qDegreesToRadians(20.0))};
    QPointF leftBottom{ellipseCenterX + thirdWidth * qCos(qDegreesToRadians(200.0)),
                       ellipseCenterY + thirdWidth * qSin(qDegreesToRadians(200.0))};
    QPointF rightBottom{ellipseCenterX + thirdWidth * qCos(qDegreesToRadians(70.0)),
                        ellipseCenterY + thirdWidth * qSin(qDegreesToRadians(70.0))};
    painter->drawEllipse(ellipseCenter, thirdWidth, thirdWidth);
    painter->drawLine(leftTop, rightBottom);
    painter->drawLine(leftBottom, rightTop);
    painter->drawLine(leftBottom, leftTop);
    painter->drawLine(rightBottom, rightTop);

    if (m_showText)
        m_smokRemText->setPos(m_smokRemRect.right(), m_smokRemRect.bottom());
}

PumpStatShape::PumpStatShape(QGraphicsItem *parent)
    :TechnicsShape(parent)
    , m_pumpStatType{PumpStat}
    , m_pumpStatText{nullptr}
    , m_pumpStatRect{QRectF(-15.0, -37.5, 30.0, 75.0)}
    , m_showPipes{false}
    , m_showCollector{false}
    , m_showText{false}
{
    setFlag(ItemSendsGeometryChanges, true);
    setAcceptHoverEvents(true);
    setPen(QPen(Qt::red, 1));
    setBrush(QBrush(Qt::white));
}

void PumpStatShape::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(widget);

    painter->setRenderHint(QPainter::Antialiasing);
    painter->setRenderHint(QPainter::SmoothPixmapTransform);
    painter->setPen(pen());
    painter->setBrush(brush());

    drawPumpStatShape(painter);

    if (option->state & QStyle::State_Selected)
        highlightSelected(painter, option);
}

QRectF PumpStatShape::boundingRect() const
{
    QRectF boundingRect{m_pumpStatRect};
    if (m_showPipes) {
        qreal pipeLength{m_pumpStatRect.width() / 6};
        boundingRect.adjust(-pipeLength, 0.0, pipeLength, 0.0);
    }
    if (m_showCollector) {
        qreal collectorLength{m_pumpStatRect.width() / 3};
        boundingRect.adjust(0.0, 0.0, 0.0, collectorLength);
    }
    qreal halfpw{pen().style() == Qt::NoPen ? qreal(0.0) : pen().widthF() / 2};
    if (halfpw > 0.0)
        boundingRect.adjust(-halfpw, -halfpw, halfpw, halfpw);

    return boundingRect;
}

QPainterPath PumpStatShape::shape() const
{
    QPainterPath path;
    path.addPolygon(basePolygon(rect()));

    qreal sixthWidth{m_pumpStatRect.width() / 6}; // 5.0
    if (m_showPipes) {
        qreal pipeY{m_pumpStatRect.bottom() - sixthWidth};
        QPointF rightPipeP1{m_pumpStatRect.right(), pipeY};
        QPointF rightPipeP2{m_pumpStatRect.right() + sixthWidth, pipeY};
        // Right pipe
        path.moveTo(rightPipeP1);
        path.lineTo(rightPipeP2);

        QPointF rightConnectP1{rightPipeP2.x(), rightPipeP2.y() + sixthWidth / 2};
        QPointF rightConnectP2{rightPipeP2.x(), rightPipeP2.y() - sixthWidth / 2};
        // Right pipe connection
        path.moveTo(rightConnectP1);
        path.lineTo(rightConnectP2);

        QPointF leftPipeP1{m_pumpStatRect.left(), pipeY};
        QPointF leftPipeP2{m_pumpStatRect.left() - sixthWidth, pipeY};
        // Left pipe
        path.moveTo(leftPipeP1);
        path.lineTo(leftPipeP2);

        QPointF leftConnectP1{leftPipeP2.x(), leftPipeP2.y() + sixthWidth / 2};
        QPointF leftConnectP2{leftPipeP2.x(), leftPipeP2.y() - sixthWidth / 2};
        // Right pipe connection
        path.moveTo(leftConnectP1);
        path.lineTo(leftConnectP2);
    }

    if (m_showCollector) {
        qreal collectorX{m_pumpStatRect.center().x()};
        qreal collectorY{m_pumpStatRect.bottom() + sixthWidth * 2};
        qreal leftPipeX{collectorX - sixthWidth};
        QPointF leftRightPipeP1{collectorX, m_pumpStatRect.bottom()};
        QPointF leftPipeP2{leftPipeX, collectorY};
        //Left collector pipe
        path.moveTo(leftRightPipeP1);
        path.lineTo(leftPipeP2);

        qreal rightPipeX{collectorX + sixthWidth};
        QPointF rightPipeP2{rightPipeX, collectorY};
        //Right collector pipe
        path.moveTo(leftRightPipeP1);
        path.lineTo(rightPipeP2);

        QPointF leftConnectP1{leftPipeX - sixthWidth / 2, collectorY};
        QPointF leftConnectP2{leftPipeX + sixthWidth / 2, collectorY};
        //Left connector
        path.moveTo(leftConnectP1);
        path.lineTo(leftConnectP2);

        QPointF rightConnectP1{rightPipeX - sixthWidth / 2, collectorY};
        QPointF rightConnectP2{rightPipeX + sixthWidth / 2, collectorY};
        //Right connector
        path.moveTo(rightConnectP1);
        path.lineTo(rightConnectP2);
    }

    return shapeFromPath(path);
}

QPixmap PumpStatShape::image()
{
    qreal pixmapWidth{boundingRect().width()};
    qreal pixmapHeight{boundingRect().height()};
    QPixmap pixmap(pixmapWidth, pixmapHeight);
    pixmap.fill(Qt::transparent);

    QPainter painter(&pixmap);
    painter.setPen(pen());
    painter.setBrush(brush());
    painter.translate(pixmapWidth / 2.0, pixmapHeight / 2.0);
    drawPumpStatShape(&painter);

    return pixmap;
}

TechnicsShape::ShapeType PumpStatShape::shapeType() const
{
    return m_pumpStatType;
}

void PumpStatShape::setRect(const QRectF &rect)
{
    if (m_pumpStatRect == rect)
        return;

    prepareGeometryChange();
    m_pumpStatRect.setRect(rect.topLeft().x(), rect.topLeft().y(), rect.width(), rect.height());
    if (m_pumpStatText != nullptr)
        m_pumpStatText->setPos(m_pumpStatRect.right(), m_pumpStatRect.bottom()
                                                           - m_pumpStatRect.width() / 6);
    if (m_showPipes) {
        qreal pipeLength{m_pumpStatRect.width() / 6};
        m_pumpStatRect.adjust(pipeLength, 0.0, -pipeLength, 0.0);
    }
    if (m_showCollector) {
        qreal collectorLength{m_pumpStatRect.width() / 3};
        m_pumpStatRect.adjust(0.0, 0.0, 0.0, -collectorLength);
    }
    update();
}

QRectF PumpStatShape::rect() const
{
    return m_pumpStatRect;
}

void PumpStatShape::setHeight(const qreal &height)
{
    if (m_pumpStatRect.height() == height)
        return;

    qreal oldHeight{m_pumpStatRect.height()};
    prepareGeometryChange();
    m_pumpStatRect.setHeight(height);
    qreal dy{(m_pumpStatRect.height() - oldHeight) / 2};
    m_pumpStatRect.moveTo(QPointF(m_pumpStatRect.x(), m_pumpStatRect.y() - dy));
    update();
}

qreal PumpStatShape::height() const
{
    return m_pumpStatRect.height();
}

void PumpStatShape::setText(const QString &text)
{
    if (m_pumpStatText == nullptr) {
        m_pumpStatText = new QGraphicsTextItem(this);
        m_pumpStatText->setTextInteractionFlags(Qt::TextEditorInteraction);
        m_pumpStatText->setRotation(-90);
    }
    m_pumpStatText->setPlainText(text);
    m_showText = true;
}

QString PumpStatShape::text() const
{
    if (m_pumpStatText == nullptr)
        return "";

    return m_pumpStatText->toPlainText();
}

void PumpStatShape::setPipes(bool showPipes)
{
    if (m_showPipes == showPipes)
        return;

    prepareGeometryChange();
    m_showPipes = showPipes;
    setSelected(false);
    setSelected(true);
    update();
}

bool PumpStatShape::pipes() const
{
    return m_showPipes;
}

void PumpStatShape::setCollector(bool showCollector)
{
    if (m_showCollector == showCollector)
        return;

    prepareGeometryChange();
    m_showCollector = showCollector;
    setSelected(false);
    setSelected(true);
    update();
}

bool PumpStatShape::collector()
{
    return m_showCollector;
}

void PumpStatShape::mousePressEvent(QGraphicsSceneMouseEvent *mouseEvent)
{
    if (mouseEvent->buttons() == Qt::RightButton) {
        createAction();
        addActions(m_pumpStatActionList);
        QAction menuAction{menu()->exec(mouseEvent->screenPos())};
        QString menuActionText;
        if (menuAction.parent()) {
            menuActionText = menuAction.parent()->objectName();
        }
        if ((menuActionText != "actionDeleteItem") && (menuActionText != "actionCut")) {
            removeActions(m_pumpStatActionList);
            m_pumpStatActionList.clear();
        }
    } else {
        AbstractShape::mousePressEvent(mouseEvent);
    }
}

void PumpStatShape::createAction()
{
    QString pipeActionText{m_showPipes ? QObject::tr("Hide pipes") : QObject::tr("Show pipes")};
    m_showPipeAction.reset(new QAction(pipeActionText));
    m_showPipeAction->setToolTip(QObject::tr("Show or hide the pipes"));
    QObject::connect(m_showPipeAction.get(), &QAction::triggered
                     , [this]() {m_showPipes ? setPipes(false) : setPipes(true);});
    m_pumpStatActionList.append(m_showPipeAction.get());

    QString collectActionText{m_showCollector ? QObject::tr("Hide collector")
                                              : QObject::tr("Show collector")};
    m_showCollectorAction.reset(new QAction(collectActionText));
    m_showCollectorAction->setToolTip(QObject::tr("Show or hide the water collector"));
    QObject::connect(m_showCollectorAction.get(), &QAction::triggered
                     , [this](){m_showCollector ? setCollector(false) : setCollector(true);});
    m_pumpStatActionList.append(m_showCollectorAction.get());

    QString addText{m_showText ? QObject::tr("Hide text") : QObject::tr("Show text")};
    m_addTextAction.reset(new QAction(addText));
    m_addTextAction->setToolTip(QObject::tr("Show or hide text"));
    QObject::connect(m_addTextAction.get(), &QAction::triggered
                     , [this](){m_showText ? textShow(false) : textShow(true);});
    m_pumpStatActionList.append(m_addTextAction.get());
}

void PumpStatShape::textShow(bool showText)
{
    if (showText) {
        if (m_pumpStatText == nullptr) {
            m_pumpStatText=new QGraphicsTextItem(this);
            m_pumpStatText->setPlainText("ПНС-");
            m_pumpStatText->setTextInteractionFlags(Qt::TextEditorInteraction);
            m_pumpStatText->setRotation(-90);
        }
        m_pumpStatText->show();
        m_showText = true;
    } else {
        m_pumpStatText->hide();
        m_showText = false;
    }
}

void PumpStatShape::drawPumpStatShape(QPainter *painter)
{
    painter->drawPolygon(basePolygon(rect()));

    // Draw pump
    qreal sixthWidth{m_pumpStatRect.width() / 6}; // 5.0
    qreal sixthHeight{m_pumpStatRect.height() / 6}; //12.5
    qreal pumpLeft{m_pumpStatRect.left() + sixthWidth};
    qreal pumpRight{m_pumpStatRect.right() - sixthWidth};
    qreal pumpTop{m_pumpStatRect.bottom() - sixthHeight};
    qreal pumpBottom{m_pumpStatRect.bottom()};
    QPolygonF pump;
    pump << QPointF(pumpLeft, pumpBottom) << QPointF(pumpLeft, pumpTop)
         << QPointF(pumpRight, pumpTop) << QPointF(pumpRight, pumpBottom);
    painter->drawPolygon(pump);

    // Draw text
    painter->translate(m_pumpStatRect.center());
    painter->rotate(270);
    painter->translate(-m_pumpStatRect.center());
    QTextOption textOption{Qt::AlignCenter};
    painter->drawText(m_pumpStatRect, "ПНС", textOption);
    painter->translate(m_pumpStatRect.center());
    painter->rotate(-270);
    painter->translate(-m_pumpStatRect.center());

    if (m_showText) {
        m_pumpStatText->setPos(m_pumpStatRect.right(), m_pumpStatRect.bottom() - sixthWidth * 2);
    }

    if (m_showPipes) {
        drawPipes(painter, sixthWidth);
    }

    if (m_showCollector) {
        drawCollector(painter, sixthWidth);
    }
}

void PumpStatShape::drawPipes(QPainter *painter, qreal sixtWidth)
{
    painter->setPen(QPen(Qt::black, 1));
    qreal pipeY{m_pumpStatRect.bottom() - sixtWidth};
    QPointF rightPipeP1{m_pumpStatRect.right(), pipeY};
    QPointF rightPipeP2{m_pumpStatRect.right() + sixtWidth, pipeY};
    painter->drawLine(rightPipeP1, rightPipeP2); // Right pipe

    QPointF rightConnectP1{rightPipeP2.x(), rightPipeP2.y() + sixtWidth / 2};
    QPointF rightConnectP2{rightPipeP2.x(), rightPipeP2.y() - sixtWidth / 2};
    painter->drawLine(rightConnectP1, rightConnectP2); // Right pipe connection

    QPointF leftPipeP1{m_pumpStatRect.left(), pipeY};
    QPointF leftPipeP2{m_pumpStatRect.left() - sixtWidth, pipeY};
    painter->drawLine(leftPipeP1, leftPipeP2); // Left pipe

    QPointF leftConnectP1{leftPipeP2.x(), leftPipeP2.y() + sixtWidth / 2};
    QPointF leftConnectP2{leftPipeP2.x(), leftPipeP2.y() - sixtWidth / 2};
    painter->drawLine(leftConnectP1, leftConnectP2); // Right pipe connection
}

void PumpStatShape::drawCollector(QPainter *painter, qreal sixtWidth)
{
    painter->setPen(QPen(Qt::black, 1));
    qreal collectorX{m_pumpStatRect.center().x()};
    qreal collectorY{m_pumpStatRect.bottom() + sixtWidth * 2};
    qreal leftPipeX{collectorX - sixtWidth};
    QPointF leftRightPipeP1{collectorX, m_pumpStatRect.bottom()};
    QPointF leftPipeP2{leftPipeX, collectorY};
    painter->drawLine(leftRightPipeP1, leftPipeP2); //Left collector pipe

    qreal rightPipeX{collectorX + sixtWidth};
    QPointF rightPipeP2{rightPipeX, collectorY};
    painter->drawLine(leftRightPipeP1, rightPipeP2); //Right collector pipe

    QPointF leftConnectP1{leftPipeX - sixtWidth / 2, collectorY};
    QPointF leftConnectP2{leftPipeX + sixtWidth / 2, collectorY};
    painter->drawLine(leftConnectP1, leftConnectP2); //Left connector

    QPointF rightConnectP1{rightPipeX - sixtWidth / 2, collectorY};
    QPointF rightConnectP2{rightPipeX + sixtWidth / 2, collectorY};
    painter->drawLine(rightConnectP1, rightConnectP2);  //Right connector
}

LafetTankerShape::LafetTankerShape(QGraphicsItem *parent)
    :TechnicsShape(parent)
    , m_lafetTankerType{LafetTanker}
    , m_lafetTankerText{nullptr}
    , m_lafetTankerRect{QRectF(-23.5, -37.5, 47.0, 75.0)}
    , m_showPipes{false}
    , m_showCollector{false}
    , m_showText{false}
{
    setFlag(ItemSendsGeometryChanges, true);
    setAcceptHoverEvents(true);
    setPen(QPen(Qt::red, 1));
    setBrush(QBrush(Qt::white));
}

void LafetTankerShape::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(widget);

    painter->setRenderHint(QPainter::Antialiasing);
    painter->setRenderHint(QPainter::SmoothPixmapTransform);
    painter->setPen(pen());
    painter->setBrush(brush());

    drawLafetTankerShape(painter);

    if (option->state & QStyle::State_Selected)
        highlightSelected(painter, option);
}

QRectF LafetTankerShape::boundingRect() const
{
    QRectF boundingRect{m_lafetTankerRect};
    if (m_showPipes) {
        qreal arrowWidth{m_lafetTankerRect.width() / 23.5}; // 2.0
        qreal baseWidth{(m_lafetTankerRect.width() - arrowWidth) / 3.0 * 2.0}; // 30.0
        qreal pipeLength{baseWidth / 6};
        boundingRect.adjust(0.0, 0.0, pipeLength, 0.0);
    }
    if (m_showCollector) {
        qreal collectorLength{m_lafetTankerRect.height() / 7.5};
        boundingRect.adjust(0.0, 0.0, 0.0, collectorLength);
    }
    qreal halfpw{pen().style() == Qt::NoPen ? qreal(0.0) : pen().widthF() / 2};
    if (halfpw > 0.0)
        boundingRect.adjust(-halfpw, -halfpw, halfpw, halfpw);

    return boundingRect;
}

QPainterPath LafetTankerShape::shape() const
{
    QPainterPath path;

    // Base
    qreal arrowWidth{m_lafetTankerRect.width() / 23.5}; // 2.0
    qreal baseWidth{(m_lafetTankerRect.width() - arrowWidth) / 3.0 * 2.0}; // 30.0
    qreal baseCenterX{m_lafetTankerRect.right() - baseWidth / 2.0}; // 8.5
    qreal baseLeft{m_lafetTankerRect.right() - baseWidth}; // -6.5
    qreal thirdHeight{m_lafetTankerRect.height() / 3.0}; // 25.0
    QPointF frontCenter{baseCenterX, m_lafetTankerRect.top()}; // 8.5, -37.5
    QPointF frontRight{m_lafetTankerRect.right(), m_lafetTankerRect.top() + thirdHeight}; // 23.5, -12.5
    QPointF frontLeft{baseLeft, m_lafetTankerRect.top() + thirdHeight}; // 8.5, -12.5
    QPointF bottomRight{m_lafetTankerRect.bottomRight()}; // 23.5, 37.5
    QPointF bottomLeft{baseLeft, m_lafetTankerRect.bottom()}; // -6.5, 37.5
    QPolygonF base;
    base << frontCenter << frontRight << bottomRight << bottomLeft << frontLeft << frontCenter;
    path.addPolygon(base);

    // Lafet
    // Barrel
    QPointF barrelP1{m_lafetTankerRect.left() + arrowWidth
                     , m_lafetTankerRect.top() + thirdHeight};
    QPointF barrelP2{baseLeft, m_lafetTankerRect.bottom()};
    QLineF barrelLine{barrelP1, barrelP2};
    path.moveTo(barrelP1);
    path.lineTo(barrelP2);
    //Stand
    QPointF standP1{barrelLine.pointAt(0.5)};
    QPointF standP2{baseLeft, standP1.y()};
    path.moveTo(standP1);
    path.lineTo(standP2);
    //Left arrow
    QLineF leftArrow;
    leftArrow.setP1(barrelP1);
    QPointF leftArrowP2{m_lafetTankerRect.left()
                        , barrelP1.y() + m_lafetTankerRect.height() / 10.0};
    leftArrow.setP2(leftArrowP2);
    path.moveTo(leftArrow.p1());
    path.lineTo(leftArrowP2);
    //Right arrow
    QLineF rightArrow;
    rightArrow.setP1(barrelP1);
    rightArrow.setLength(leftArrow.length());
    rightArrow.setAngle(barrelLine.angle() + leftArrow.angleTo(barrelLine));
    path.moveTo(rightArrow.p1());
    path.lineTo(rightArrow.p2());

    qreal sixthWidth{m_lafetTankerRect.width() / 6}; // 5.0
    if (m_showPipes) {
        qreal pipeY{m_lafetTankerRect.bottom() - sixthWidth};
        // Right pipe
        QPointF rightPipeP1{m_lafetTankerRect.right(), pipeY};
        QPointF rightPipeP2{m_lafetTankerRect.right() + sixthWidth, pipeY};
        path.moveTo(rightPipeP1);
        path.lineTo(rightPipeP2);
        // Right pipe connection
        QPointF rightConnectP1{rightPipeP2.x(), rightPipeP2.y() + sixthWidth / 2};
        QPointF rightConnectP2{rightPipeP2.x(), rightPipeP2.y() - sixthWidth / 2};
        path.moveTo(rightConnectP1);
        path.lineTo(rightConnectP2);
        // Left pipe
        QPointF leftPipeP1{baseLeft, pipeY};
        QPointF leftPipeP2{baseLeft - sixthWidth, pipeY};
        path.moveTo(leftPipeP1);
        path.lineTo(leftPipeP2);
        // Right pipe connection
        QPointF leftConnectP1{leftPipeP2.x(), leftPipeP2.y() + sixthWidth / 2};
        QPointF leftConnectP2{leftPipeP2.x(), leftPipeP2.y() - sixthWidth / 2};
        path.moveTo(leftConnectP1);
        path.lineTo(leftConnectP2);
    }

    if (m_showCollector) {
        qreal collectorX{m_lafetTankerRect.right() - baseWidth / 2.0}; // 8.5
        qreal collectorY{m_lafetTankerRect.bottom() + m_lafetTankerRect.height() / 7.5}; // 10.0
        //Left collector pipe
        qreal leftPipeX{collectorX - sixthWidth};
        QPointF leftRightPipeP1{collectorX, m_lafetTankerRect.bottom()};
        QPointF leftPipeP2{leftPipeX, collectorY};
        path.moveTo(leftRightPipeP1);
        path.lineTo(leftPipeP2);
        //Right collector pipe
        qreal rightPipeX{collectorX + sixthWidth};
        QPointF rightPipeP2{rightPipeX, collectorY};
        path.moveTo(leftRightPipeP1);
        path.lineTo(rightPipeP2);
        //Left connector
        QPointF leftConnectP1{leftPipeX - sixthWidth / 2, collectorY};
        QPointF leftConnectP2{leftPipeX + sixthWidth / 2, collectorY};
        path.moveTo(leftConnectP1);
        path.lineTo(leftConnectP2);
        //Right connector
        QPointF rightConnectP1{rightPipeX - sixthWidth / 2, collectorY};
        QPointF rightConnectP2{rightPipeX + sixthWidth / 2, collectorY};
        path.moveTo(rightConnectP1);
        path.lineTo(rightConnectP2);
    }

    return shapeFromPath(path);
}

QPixmap LafetTankerShape::image()
{
    qreal pixmapWidth{boundingRect().width()};
    qreal pixmapHeight{boundingRect().height()};
    QPixmap pixmap(pixmapWidth, pixmapHeight);
    pixmap.fill(Qt::transparent);

    QPainter painter(&pixmap);
    painter.setPen(pen());
    painter.setBrush(brush());
    painter.translate(pixmapWidth / 2.0, pixmapHeight / 2.0);
    drawLafetTankerShape(&painter);

    return pixmap;
}

TechnicsShape::ShapeType LafetTankerShape::shapeType() const
{
    return m_lafetTankerType;
}

void LafetTankerShape::setRect(const QRectF &rect)
{
    if (m_lafetTankerRect == rect)
        return;

    prepareGeometryChange();
    m_lafetTankerRect.setRect(rect.topLeft().x(), rect.topLeft().y(), rect.width(), rect.height());
    if (m_lafetTankerText != nullptr)
        m_lafetTankerText->setPos(m_lafetTankerRect.right(), m_lafetTankerRect.bottom()
                                                           - m_lafetTankerRect.width() / 6);
    if (m_showPipes) {
        qreal arrowWidth{m_lafetTankerRect.width() / 23.5}; // 2.0
        qreal baseWidth{(m_lafetTankerRect.width() - arrowWidth) / 3.0 * 2.0}; // 30.0
        qreal pipeLength{baseWidth / 6};
        m_lafetTankerRect.adjust(0.0, 0.0, -pipeLength, 0.0);
    }
    if (m_showCollector) {
        qreal collectorLength{m_lafetTankerRect.height() / 7.5};
        m_lafetTankerRect.adjust(0.0, 0.0, 0.0, -collectorLength);
    }
    update();
}

QRectF LafetTankerShape::rect() const
{
    return m_lafetTankerRect;
}

void LafetTankerShape::setHeight(const qreal &height)
{
    if (m_lafetTankerRect.height() == height)
        return;

    qreal oldHeight{m_lafetTankerRect.height()};
    prepareGeometryChange();
    m_lafetTankerRect.setHeight(height);
    qreal dy{(m_lafetTankerRect.height() - oldHeight) / 2};
    m_lafetTankerRect.moveTo(QPointF(m_lafetTankerRect.x(), m_lafetTankerRect.y() - dy));
    update();
}

qreal LafetTankerShape::height() const
{
    return m_lafetTankerRect.height();
}

void LafetTankerShape::setText(const QString &text)
{
    if (m_lafetTankerText == nullptr) {
        m_lafetTankerText = new QGraphicsTextItem(this);
        m_lafetTankerText->setTextInteractionFlags(Qt::TextEditorInteraction);
        m_lafetTankerText->setRotation(-90);
    }
    m_lafetTankerText->setPlainText(text);
    m_showText = true;
}

QString LafetTankerShape::text() const
{
    if (m_lafetTankerText == nullptr)
        return "";

    return m_lafetTankerText->toPlainText();
}

void LafetTankerShape::setPipes(bool showPipes)
{
    if (m_showPipes == showPipes)
        return;

    prepareGeometryChange();
    m_showPipes = showPipes;
    setSelected(false);
    setSelected(true);
    update();
}

bool LafetTankerShape::pipes() const
{
    return m_showPipes;
}

void LafetTankerShape::setCollector(bool showCollector)
{
    if (m_showCollector == showCollector)
        return;

    prepareGeometryChange();
    m_showCollector = showCollector;
    setSelected(false);
    setSelected(true);
    update();
}

bool LafetTankerShape::collector()
{
    return m_showCollector;
}

void LafetTankerShape::mousePressEvent(QGraphicsSceneMouseEvent *mouseEvent)
{
    if (mouseEvent->buttons() == Qt::RightButton) {
        createAction();
        addActions(m_lafetTankerActionList);
        QAction menuAction{menu()->exec(mouseEvent->screenPos())};
        QString menuActionText;
        if (menuAction.parent()) {
            menuActionText = menuAction.parent()->objectName();
        }
        if ((menuActionText != "actionDeleteItem") && (menuActionText != "actionCut")) {
            removeActions(m_lafetTankerActionList);
            m_lafetTankerActionList.clear();
        }
    } else {
        AbstractShape::mousePressEvent(mouseEvent);
    }
}

void LafetTankerShape::createAction()
{
    QString pipeActionText{m_showPipes ? QObject::tr("Hide pipes") : QObject::tr("Show pipes")};
    m_showPipeAction.reset(new QAction(pipeActionText));
    m_showPipeAction->setToolTip(QObject::tr("Show or hide the pipes"));
    QObject::connect(m_showPipeAction.get(), &QAction::triggered
                     , [this]() {m_showPipes ? setPipes(false) : setPipes(true);});
    m_lafetTankerActionList.append(m_showPipeAction.get());

    QString collectActionText{m_showCollector ? QObject::tr("Hide collector")
                                              : QObject::tr("Show collector")};
    m_showCollectorAction.reset(new QAction(collectActionText));
    m_showCollectorAction->setToolTip(QObject::tr("Show or hide the water collector"));
    QObject::connect(m_showCollectorAction.get(), &QAction::triggered
                     , [this](){m_showCollector ? setCollector(false) : setCollector(true);});
    m_lafetTankerActionList.append(m_showCollectorAction.get());

    QString addText{m_showText ? QObject::tr("Hide text") : QObject::tr("Show text")};
    m_addTextAction.reset(new QAction(addText));
    m_addTextAction->setToolTip(QObject::tr("Show or hide text"));
    QObject::connect(m_addTextAction.get(), &QAction::triggered
                     , [this](){m_showText ? textShow(false) : textShow(true);});
    m_lafetTankerActionList.append(m_addTextAction.get());
}

void LafetTankerShape::textShow(bool showText)
{
    if (showText) {
        if (m_lafetTankerText == nullptr) {
            m_lafetTankerText=new QGraphicsTextItem(this);
            m_lafetTankerText->setPlainText("АЛСС-");
            m_lafetTankerText->setTextInteractionFlags(Qt::TextEditorInteraction);
            m_lafetTankerText->setRotation(-90);
        }
        m_lafetTankerText->show();
        m_showText = true;
    } else {
        m_lafetTankerText->hide();
        m_showText = false;
    }
}

void LafetTankerShape::drawLafetTankerShape(QPainter *painter)
{
    // Draw base
    qreal arrowWidth{m_lafetTankerRect.width() / 23.5}; // 2.0
    qreal baseWidth{(m_lafetTankerRect.width() - arrowWidth) / 3.0 * 2.0}; // 30.0
    qreal baseCenterX{m_lafetTankerRect.right() - baseWidth / 2.0}; // 8.5
    qreal baseLeft{m_lafetTankerRect.right() - baseWidth}; // -6.5
    qreal thirdHeight{m_lafetTankerRect.height() / 3.0}; // 25.0
    QPointF frontCenter{baseCenterX, m_lafetTankerRect.top()}; // 8.5, -37.5
    QPointF frontRight{m_lafetTankerRect.right(), m_lafetTankerRect.top() + thirdHeight}; // 23.5, -12.5
    QPointF frontLeft{baseLeft, m_lafetTankerRect.top() + thirdHeight}; // 8.5, -12.5
    QPointF bottomRight{m_lafetTankerRect.bottomRight()}; // 23.5, 37.5
    QPointF bottomLeft{baseLeft, m_lafetTankerRect.bottom()}; // -6.5, 37.5
    QPolygonF base;
    base << frontCenter << frontRight << bottomRight << bottomLeft << frontLeft << frontCenter;
    painter->drawPolygon(base);

    // Draw tanker
    qreal sixthWidth{baseWidth / 6}; // 5.0
    QPointF roundTopLeft{baseLeft + sixthWidth, m_lafetTankerRect.top() + thirdHeight}; // -1.5, -12.5
    QPointF roundBottomRight{m_lafetTankerRect.right() - sixthWidth
                             , m_lafetTankerRect.bottom() - sixthWidth}; // 18.5, 32.5
    painter->drawRoundedRect(QRectF(roundTopLeft, roundBottomRight), sixthWidth, sixthWidth);

    // Draw lafet
    QPointF barrelP1{m_lafetTankerRect.left() + arrowWidth
                     , m_lafetTankerRect.top() + thirdHeight};
    QPointF barrelP2{baseLeft, m_lafetTankerRect.bottom()};
    QLineF barrelLine{barrelP1, barrelP2};
    painter->drawLine(barrelLine); // Draw barrel
    QPointF standP1{barrelLine.pointAt(0.5)};
    QPointF standP2{baseLeft, standP1.y()};
    painter->drawLine(QLineF(standP1, standP2));    // Draw stand
    QLineF leftArrow;
    leftArrow.setP1(barrelP1);
    QPointF leftArrowP2{m_lafetTankerRect.left()
                        , barrelP1.y() + m_lafetTankerRect.height() / 10.0};
    leftArrow.setP2(leftArrowP2);
    painter->drawLine(leftArrow);    // Draw left part arrow
    QLineF rightArrow;
    rightArrow.setP1(barrelP1);
    rightArrow.setLength(leftArrow.length());
    rightArrow.setAngle(barrelLine.angle() + leftArrow.angleTo(barrelLine));
    painter->drawLine(rightArrow);    // Draw right part arrow

    if (m_showText) {
        m_lafetTankerText->setPos(m_lafetTankerRect.right(), m_lafetTankerRect.bottom()
                                                                 - sixthWidth * 2);
    }

    if (m_showPipes) {
        drawPipes(painter, sixthWidth);
    }

    if (m_showCollector) {
        drawCollector(painter, sixthWidth);
    }
}

void LafetTankerShape::drawPipes(QPainter *painter, qreal sixthWidth)
{
    painter->setPen(QPen(Qt::black, 1));
    qreal pipeY{m_lafetTankerRect.bottom() - sixthWidth};
    QPointF rightPipeP1{m_lafetTankerRect.right(), pipeY};
    QPointF rightPipeP2{m_lafetTankerRect.right() + sixthWidth, pipeY};
    painter->drawLine(rightPipeP1, rightPipeP2); // Right pipe

    QPointF rightConnectP1{rightPipeP2.x(), rightPipeP2.y() + sixthWidth / 2};
    QPointF rightConnectP2{rightPipeP2.x(), rightPipeP2.y() - sixthWidth / 2};
    painter->drawLine(rightConnectP1, rightConnectP2); // Right pipe connection

    qreal arrowWidth{m_lafetTankerRect.width() / 23.5}; // 2.0
    qreal baseWidth{(m_lafetTankerRect.width() - arrowWidth) / 3.0 * 2.0}; // 30.0
    qreal baseLeft{m_lafetTankerRect.right() - baseWidth}; // -6.5
    QPointF leftPipeP1{baseLeft, pipeY};
    QPointF leftPipeP2{baseLeft - sixthWidth, pipeY};
    painter->drawLine(leftPipeP1, leftPipeP2); // Left pipe

    QPointF leftConnectP1{leftPipeP2.x(), leftPipeP2.y() + sixthWidth / 2};
    QPointF leftConnectP2{leftPipeP2.x(), leftPipeP2.y() - sixthWidth / 2};
    painter->drawLine(leftConnectP1, leftConnectP2); // Right pipe connection
}

void LafetTankerShape::drawCollector(QPainter *painter, qreal sixthWidth)
{
    painter->setPen(QPen(Qt::black, 1));
    qreal arrowWidth{m_lafetTankerRect.width() / 23.5}; // 2.0
    qreal baseWidth{(m_lafetTankerRect.width() - arrowWidth) / 3.0 * 2.0}; // 30.0
    qreal collectorX{m_lafetTankerRect.right() - baseWidth / 2.0}; // 8.5
    qreal collectorY{m_lafetTankerRect.bottom() + m_lafetTankerRect.height() / 7.5}; // 10.0
    qreal leftPipeX{collectorX - sixthWidth};
    QPointF leftRightPipeP1{collectorX, m_lafetTankerRect.bottom()};
    QPointF leftPipeP2{leftPipeX, collectorY};
    painter->drawLine(leftRightPipeP1, leftPipeP2); //Left collector pipe

    qreal rightPipeX{collectorX + sixthWidth};
    QPointF rightPipeP2{rightPipeX, collectorY};
    painter->drawLine(leftRightPipeP1, rightPipeP2); //Right collector pipe

    QPointF leftConnectP1{leftPipeX - sixthWidth / 2, collectorY};
    QPointF leftConnectP2{leftPipeX + sixthWidth / 2, collectorY};
    painter->drawLine(leftConnectP1, leftConnectP2); //Left connector

    QPointF rightConnectP1{rightPipeX - sixthWidth / 2, collectorY};
    QPointF rightConnectP2{rightPipeX + sixthWidth / 2, collectorY};
    painter->drawLine(rightConnectP1, rightConnectP2);  //Right connector
}

LafetCarShape::LafetCarShape(QGraphicsItem *parent)
    :TechnicsShape(parent)
    , m_lafetCarType{LafetCar}
    , m_lafetCarRect{QRectF(-15.0, -37.5, 30.0, 75.0)}
    , m_lafetCarText{nullptr}
    , m_showText{false}
{
    setFlag(ItemSendsGeometryChanges, true);
    setAcceptHoverEvents(true);
    setPen(QPen(Qt::red, 1));
    setBrush(QBrush(Qt::white));
}

void LafetCarShape::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(widget);

    painter->setRenderHint(QPainter::Antialiasing);
    painter->setRenderHint(QPainter::SmoothPixmapTransform);
    painter->setPen(pen());
    painter->setBrush(brush());

    drawLafetCarShape(painter);

    if (option->state & QStyle::State_Selected)
        highlightSelected(painter, option);
}

QRectF LafetCarShape::boundingRect() const
{
    QRectF boundingRect{m_lafetCarRect};
    qreal halfpw{pen().style() == Qt::NoPen ? qreal(0.0) : pen().widthF() / 2};
    if (halfpw > 0.0)
        boundingRect.adjust(-halfpw, -halfpw, halfpw, halfpw);
    return boundingRect;
}

QPainterPath LafetCarShape::shape() const
{
    QPainterPath path;
    path.addPolygon(basePolygon(rect()));

    return shapeFromPath(path);
}

QPixmap LafetCarShape::image()
{
    qreal pixmapWidth{boundingRect().width()};
    qreal pixmapHeight{boundingRect().height()};
    QPixmap pixmap(pixmapWidth, pixmapHeight);
    pixmap.fill(Qt::transparent);

    QPainter painter(&pixmap);
    painter.setPen(pen());
    painter.setBrush(brush());
    painter.translate(pixmapWidth / 2.0, pixmapHeight / 2.0);
    drawLafetCarShape(&painter);

    return pixmap;
}

TechnicsShape::ShapeType LafetCarShape::shapeType() const
{
    return m_lafetCarType;
}

void LafetCarShape::setRect(const QRectF &rect)
{
    if (m_lafetCarRect == rect)
        return;

    prepareGeometryChange();
    m_lafetCarRect.setRect(rect.topLeft().x(), rect.topLeft().y(), rect.width(), rect.height());
    if (m_lafetCarText != nullptr)
        m_lafetCarText->setPos(m_lafetCarRect.right(), m_lafetCarRect.bottom()
                                                         - m_lafetCarRect.width() / 6);
    update();
}

QRectF LafetCarShape::rect() const
{
    return m_lafetCarRect;
}

void LafetCarShape::setHeight(const qreal &height)
{
    if (m_lafetCarRect.height() == height)
        return;

    qreal oldHeight{m_lafetCarRect.height()};
    prepareGeometryChange();
    m_lafetCarRect.setHeight(height);
    qreal dy{(m_lafetCarRect.height() - oldHeight) / 2};
    m_lafetCarRect.moveTo(QPointF(m_lafetCarRect.x(), m_lafetCarRect.y() - dy));
    update();
}

qreal LafetCarShape::height() const
{
    return m_lafetCarRect.height();
}

void LafetCarShape::setText(const QString &text)
{
    if (m_lafetCarText == nullptr) {
        m_lafetCarText = new QGraphicsTextItem(this);
        m_lafetCarText->setTextInteractionFlags(Qt::TextEditorInteraction);
        m_lafetCarText->setRotation(-90);
    }
    m_lafetCarText->setPlainText(text);
    m_showText = true;
}

QString LafetCarShape::text() const
{
    if (m_lafetCarText == nullptr)
        return "";

    return m_lafetCarText->toPlainText();
}

void LafetCarShape::mousePressEvent(QGraphicsSceneMouseEvent *mouseEvent)
{
    if (mouseEvent->buttons() == Qt::RightButton) {
        createAction();
        addActions(m_lafetCarActionList);
        QAction menuAction{menu()->exec(mouseEvent->screenPos())};
        QString menuActionText;
        if (menuAction.parent()) {
            menuActionText = menuAction.parent()->objectName();
        }
        if ((menuActionText != "actionDeleteItem") && (menuActionText != "actionCut")) {
            removeActions(m_lafetCarActionList);
            m_lafetCarActionList.clear();
        }
    } else {
        AbstractShape::mousePressEvent(mouseEvent);
    }
}

void LafetCarShape::createAction()
{
    QString addText{m_showText ? QObject::tr("Hide text") : QObject::tr("Show text")};
    m_addTextAction.reset(new QAction(addText));
    m_addTextAction->setToolTip(QObject::tr("Show or hide text"));
    QObject::connect(m_addTextAction.get(), &QAction::triggered
                     , [this](){m_showText ? textShow(false) : textShow(true);});
    m_lafetCarActionList.append(m_addTextAction.get());
}

void LafetCarShape::textShow(bool showText)
{
    if (showText) {
        if (m_lafetCarText == nullptr) {
            m_lafetCarText=new QGraphicsTextItem(this);
            m_lafetCarText->setPlainText("АПЛС-");
            m_lafetCarText->setTextInteractionFlags(Qt::TextEditorInteraction);
            m_lafetCarText->setRotation(-90);
        }
        m_lafetCarText->show();
        m_showText = true;
    } else {
        m_lafetCarText->hide();
        m_showText = false;
    }
}

void LafetCarShape::drawLafetCarShape(QPainter *painter)
{
    painter->drawPolygon(basePolygon(rect()));

    // Draw lafet
    qreal sixthWidth{m_lafetCarRect.width() / 6}; // 5.0
    qreal thirdHeight{m_lafetCarRect.height() / 3.0}; // 25.0
    QPointF barrelP1{m_lafetCarRect.left() + sixthWidth, m_lafetCarRect.top() + thirdHeight};
    QPointF barrelP2{m_lafetCarRect.right() - sixthWidth, m_lafetCarRect.bottom() - sixthWidth};
    QLineF barrelLine{barrelP1, barrelP2};
    painter->drawLine(barrelLine); // Draw barrel
    QPointF standP1{barrelLine.pointAt(0.5)};
    QPointF standP2{barrelP2.x(), standP1.y()};
    painter->drawLine(QLineF(standP1, standP2));    // Draw stand
    QLineF leftArrow;
    leftArrow.setP1(barrelP1);
    QPointF leftArrowP2{barrelP1.x() - sixthWidth / 2
                        , barrelP1.y() + m_lafetCarRect.height() / 10.0};
    leftArrow.setP2(leftArrowP2);
    painter->drawLine(leftArrow);    // Draw left part arrow
    QLineF rightArrow;
    rightArrow.setP1(barrelP1);
    rightArrow.setLength(leftArrow.length());
    rightArrow.setAngle(barrelLine.angle() + leftArrow.angleTo(barrelLine));
    painter->drawLine(rightArrow);    // Draw right part arrow

    if (m_showText)
        m_lafetCarText->setPos(m_lafetCarRect.right(), m_lafetCarRect.bottom());
}

AerodromeShape::AerodromeShape(QGraphicsItem *parent)
    : TechnicsShape(parent)
    , m_aerodromeType(Aerodrome)
    , m_aerodromeText{nullptr}
    , m_aerodromeRect{QRectF(-15.0, -37.5, 30.0, 75.0)}
    , m_showPipes{false}
    , m_showCollector{false}
    , m_showText{false}
{

    setFlag(ItemSendsGeometryChanges, true);
    setAcceptHoverEvents(true);
    setPen(QPen(Qt::red, 1));
    setBrush(QBrush(Qt::white));
}

void AerodromeShape::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(widget);

    painter->setRenderHint(QPainter::Antialiasing);
    painter->setRenderHint(QPainter::SmoothPixmapTransform);
    painter->setPen(pen());
    painter->setBrush(brush());

    drawAerodromeShape(painter);

    if (option->state & QStyle::State_Selected)
        highlightSelected(painter, option);
}

QRectF AerodromeShape::boundingRect() const
{
    QRectF boundingRect{m_aerodromeRect};
    if (m_showPipes) {
        qreal pipeLength{m_aerodromeRect.width() / 6};
        boundingRect.adjust(-pipeLength, 0.0, pipeLength, 0.0);
    }
    if (m_showCollector) {
        qreal collectorLength{m_aerodromeRect.width() / 3};
        boundingRect.adjust(0.0, 0.0, 0.0, collectorLength);
    }
    qreal halfpw{pen().style() == Qt::NoPen ? qreal(0.0) : pen().widthF() / 2};
    if (halfpw > 0.0)
        boundingRect.adjust(-halfpw, -halfpw, halfpw, halfpw);

    return boundingRect;
}

QPainterPath AerodromeShape::shape() const
{
    QPainterPath path;
    path.addPolygon(basePolygon(rect()));

    qreal sixthWidth{m_aerodromeRect.width() / 6}; // 5.0
    if (m_showPipes) {
        qreal pipeY{m_aerodromeRect.bottom() - sixthWidth};
        QPointF rightPipeP1{m_aerodromeRect.right(), pipeY};
        QPointF rightPipeP2{m_aerodromeRect.right() + sixthWidth, pipeY};
        // Right pipe
        path.moveTo(rightPipeP1);
        path.lineTo(rightPipeP2);

        QPointF rightConnectP1{rightPipeP2.x(), rightPipeP2.y() + sixthWidth / 2};
        QPointF rightConnectP2{rightPipeP2.x(), rightPipeP2.y() - sixthWidth / 2};
        // Right pipe connection
        path.moveTo(rightConnectP1);
        path.lineTo(rightConnectP2);

        QPointF leftPipeP1{m_aerodromeRect.left(), pipeY};
        QPointF leftPipeP2{m_aerodromeRect.left() - sixthWidth, pipeY};
        // Left pipe
        path.moveTo(leftPipeP1);
        path.lineTo(leftPipeP2);

        QPointF leftConnectP1{leftPipeP2.x(), leftPipeP2.y() + sixthWidth / 2};
        QPointF leftConnectP2{leftPipeP2.x(), leftPipeP2.y() - sixthWidth / 2};
        // Right pipe connection
        path.moveTo(leftConnectP1);
        path.lineTo(leftConnectP2);
    }

    if (m_showCollector) {
        qreal collectorX{m_aerodromeRect.center().x()};
        qreal collectorY{m_aerodromeRect.bottom() + sixthWidth * 2};
        qreal leftPipeX{collectorX - sixthWidth};
        QPointF leftRightPipeP1{collectorX, m_aerodromeRect.bottom()};
        QPointF leftPipeP2{leftPipeX, collectorY};
        //Left collector pipe
        path.moveTo(leftRightPipeP1);
        path.lineTo(leftPipeP2);

        qreal rightPipeX{collectorX + sixthWidth};
        QPointF rightPipeP2{rightPipeX, collectorY};
        //Right collector pipe
        path.moveTo(leftRightPipeP1);
        path.lineTo(rightPipeP2);

        QPointF leftConnectP1{leftPipeX - sixthWidth / 2, collectorY};
        QPointF leftConnectP2{leftPipeX + sixthWidth / 2, collectorY};
        //Left connector
        path.moveTo(leftConnectP1);
        path.lineTo(leftConnectP2);

        QPointF rightConnectP1{rightPipeX - sixthWidth / 2, collectorY};
        QPointF rightConnectP2{rightPipeX + sixthWidth / 2, collectorY};
        //Right connector
        path.moveTo(rightConnectP1);
        path.lineTo(rightConnectP2);
    }

    return shapeFromPath(path);
}

QPixmap AerodromeShape::image()
{
    qreal pixmapWidth{boundingRect().width()};
    qreal pixmapHeight{boundingRect().height()};
    QPixmap pixmap(pixmapWidth, pixmapHeight);
    pixmap.fill(Qt::transparent);

    QPainter painter(&pixmap);
    painter.setPen(pen());
    painter.setBrush(brush());
    painter.translate(pixmapWidth / 2.0, pixmapHeight / 2.0);
    drawAerodromeShape(&painter);

    return pixmap;
}

TechnicsShape::ShapeType AerodromeShape::shapeType() const
{
    return m_aerodromeType;
}

void AerodromeShape::setRect(const QRectF &rect)
{
    if (m_aerodromeRect == rect)
        return;

    prepareGeometryChange();
    m_aerodromeRect.setRect(rect.topLeft().x(), rect.topLeft().y(), rect.width(), rect.height());
    if (m_aerodromeText != nullptr)
        m_aerodromeText->setPos(m_aerodromeRect.right(), m_aerodromeRect.bottom()
                                                           - m_aerodromeRect.width() / 6);
    if (m_showPipes) {
        qreal pipeLength{m_aerodromeRect.width() / 6};
        m_aerodromeRect.adjust(pipeLength, 0.0, -pipeLength, 0.0);
    }
    if (m_showCollector) {
        qreal collectorLength{m_aerodromeRect.width() / 3};
        m_aerodromeRect.adjust(0.0, 0.0, 0.0, -collectorLength);
    }
    update();
}

QRectF AerodromeShape::rect() const
{
    return m_aerodromeRect;
}

void AerodromeShape::setHeight(const qreal &height)
{
    if (m_aerodromeRect.height() == height)
        return;

    qreal oldHeight{m_aerodromeRect.height()};
    prepareGeometryChange();
    m_aerodromeRect.setHeight(height);
    qreal dy{(m_aerodromeRect.height() - oldHeight) / 2};
    m_aerodromeRect.moveTo(QPointF(m_aerodromeRect.x(), m_aerodromeRect.y() - dy));
    update();
}

qreal AerodromeShape::height() const
{
    return m_aerodromeRect.height();
}

void AerodromeShape::setText(const QString &text)
{
    if (m_aerodromeText == nullptr) {
        m_aerodromeText = new QGraphicsTextItem(this);
        m_aerodromeText->setTextInteractionFlags(Qt::TextEditorInteraction);
        m_aerodromeText->setRotation(-90);
    }
    m_aerodromeText->setPlainText(text);
    m_showText = true;
}

QString AerodromeShape::text() const
{
    if (m_aerodromeText == nullptr)
        return "";

    return m_aerodromeText->toPlainText();
}

void AerodromeShape::setPipes(bool showPipes)
{
    if (m_showPipes == showPipes)
        return;

    prepareGeometryChange();
    m_showPipes = showPipes;
    setSelected(false);
    setSelected(true);
    update();
}

bool AerodromeShape::pipes() const
{
    return m_showPipes;
}

void AerodromeShape::setCollector(bool showCollector)
{
    if (m_showCollector == showCollector)
        return;

    prepareGeometryChange();
    m_showCollector = showCollector;
    setSelected(false);
    setSelected(true);
    update();
}

bool AerodromeShape::collector()
{
    return m_showCollector;
}

void AerodromeShape::mousePressEvent(QGraphicsSceneMouseEvent *mouseEvent)
{
    if (mouseEvent->buttons() == Qt::RightButton) {
        createAction();
        addActions(m_aerodromeActionList);
        QAction menuAction{menu()->exec(mouseEvent->screenPos())};
        QString menuActionText;
        if (menuAction.parent()) {
            menuActionText = menuAction.parent()->objectName();
        }
        if ((menuActionText != "actionDeleteItem") && (menuActionText != "actionCut")) {
            removeActions(m_aerodromeActionList);
            m_aerodromeActionList.clear();
        }
    } else {
        AbstractShape::mousePressEvent(mouseEvent);
    }
}

void AerodromeShape::createAction()
{
    QString pipeActionText{m_showPipes ? QObject::tr("Hide pipes") : QObject::tr("Show pipes")};
    m_showPipeAction.reset(new QAction(pipeActionText));
    m_showPipeAction->setToolTip(QObject::tr("Show or hide the pipes"));
    QObject::connect(m_showPipeAction.get(), &QAction::triggered
                     , [this]() {m_showPipes ? setPipes(false) : setPipes(true);});
    m_aerodromeActionList.append(m_showPipeAction.get());

    QString collectActionText{m_showCollector ? QObject::tr("Hide collector")
                                              : QObject::tr("Show collector")};
    m_showCollectorAction.reset(new QAction(collectActionText));
    m_showCollectorAction->setToolTip(QObject::tr("Show or hide the water collector"));
    QObject::connect(m_showCollectorAction.get(), &QAction::triggered
                     , [this](){m_showCollector ? setCollector(false) : setCollector(true);});
    m_aerodromeActionList.append(m_showCollectorAction.get());

    QString addText{m_showText ? QObject::tr("Hide text") : QObject::tr("Show text")};
    m_addTextAction.reset(new QAction(addText));
    m_addTextAction->setToolTip(QObject::tr("Show or hide text"));
    QObject::connect(m_addTextAction.get(), &QAction::triggered
                     , [this](){m_showText ? textShow(false) : textShow(true);});
    m_aerodromeActionList.append(m_addTextAction.get());
}

void AerodromeShape::textShow(bool showText)
{
    if (showText) {
        if (m_aerodromeText == nullptr) {
            m_aerodromeText=new QGraphicsTextItem(this);
            m_aerodromeText->setPlainText("АА-");
            m_aerodromeText->setTextInteractionFlags(Qt::TextEditorInteraction);
            m_aerodromeText->setRotation(-90);
        }
        m_aerodromeText->show();
        m_showText = true;
    } else {
        m_aerodromeText->hide();
        m_showText = false;
    }
}

void AerodromeShape::drawAerodromeShape(QPainter *painter)
{
    painter->drawPolygon(basePolygon(rect()));
    painter->translate(m_aerodromeRect.center());
    painter->rotate(270);
    painter->translate(-m_aerodromeRect.center());
    QTextOption textOption{Qt::AlignCenter};
    painter->drawText(m_aerodromeRect, "АА", textOption);
    painter->translate(m_aerodromeRect.center());
    painter->rotate(-270);
    painter->translate(-m_aerodromeRect.center());
    qreal sixthWidth{m_aerodromeRect.width() / 6}; // 5.0

    if (m_showText) {
        m_aerodromeText->setPos(m_aerodromeRect.right(), m_aerodromeRect.bottom()
                                                             - sixthWidth * 2);
    }

    if (m_showPipes) {
        drawPipes(painter, sixthWidth);
    }

    if (m_showCollector) {
        drawCollector(painter, sixthWidth);
    }
}

void AerodromeShape::drawPipes(QPainter *painter, qreal sixtWidth)
{
        painter->setPen(QPen(Qt::black, 1));
        qreal pipeY{m_aerodromeRect.bottom() - sixtWidth};
        QPointF rightPipeP1{m_aerodromeRect.right(), pipeY};
        QPointF rightPipeP2{m_aerodromeRect.right() + sixtWidth, pipeY};
        painter->drawLine(rightPipeP1, rightPipeP2); // Right pipe

        QPointF rightConnectP1{rightPipeP2.x(), rightPipeP2.y() + sixtWidth / 2};
        QPointF rightConnectP2{rightPipeP2.x(), rightPipeP2.y() - sixtWidth / 2};
        painter->drawLine(rightConnectP1, rightConnectP2); // Right pipe connection

        QPointF leftPipeP1{m_aerodromeRect.left(), pipeY};
        QPointF leftPipeP2{m_aerodromeRect.left() - sixtWidth, pipeY};
        painter->drawLine(leftPipeP1, leftPipeP2); // Left pipe

        QPointF leftConnectP1{leftPipeP2.x(), leftPipeP2.y() + sixtWidth / 2};
        QPointF leftConnectP2{leftPipeP2.x(), leftPipeP2.y() - sixtWidth / 2};
        painter->drawLine(leftConnectP1, leftConnectP2); // Right pipe connection
}

void AerodromeShape::drawCollector(QPainter *painter, qreal sixtWidth)
{
        painter->setPen(QPen(Qt::black, 1));
        qreal collectorX{m_aerodromeRect.center().x()};
        qreal collectorY{m_aerodromeRect.bottom() + sixtWidth * 2};
        qreal leftPipeX{collectorX - sixtWidth};
        QPointF leftRightPipeP1{collectorX, m_aerodromeRect.bottom()};
        QPointF leftPipeP2{leftPipeX, collectorY};
        painter->drawLine(leftRightPipeP1, leftPipeP2); //Left collector pipe

        qreal rightPipeX{collectorX + sixtWidth};
        QPointF rightPipeP2{rightPipeX, collectorY};
        painter->drawLine(leftRightPipeP1, rightPipeP2); //Right collector pipe

        QPointF leftConnectP1{leftPipeX - sixtWidth / 2, collectorY};
        QPointF leftConnectP2{leftPipeX + sixtWidth / 2, collectorY};
        painter->drawLine(leftConnectP1, leftConnectP2); //Left connector

        QPointF rightConnectP1{rightPipeX - sixtWidth / 2, collectorY};
        QPointF rightConnectP2{rightPipeX + sixtWidth / 2, collectorY};
        painter->drawLine(rightConnectP1, rightConnectP2);  //Right connector
}

FoamShape::FoamShape(QGraphicsItem *parent)
    : TechnicsShape(parent)
    , m_foamType(Foam)
    , m_foamText{nullptr}
    , m_foamRect{QRectF(-15.0, -37.5, 30.0, 75.0)}
    , m_showPipes{false}
    , m_showCollector{false}
    , m_showText{false}
{
    setFlag(ItemSendsGeometryChanges, true);
    setAcceptHoverEvents(true);
    setPen(QPen(Qt::red, 1));
    setBrush(QBrush(Qt::white));
}

void FoamShape::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(widget);

    painter->setRenderHint(QPainter::Antialiasing);
    painter->setRenderHint(QPainter::SmoothPixmapTransform);
    painter->setPen(pen());
    painter->setBrush(brush());

    drawFoamShape(painter);

    if (option->state & QStyle::State_Selected)
        highlightSelected(painter, option);
}

QRectF FoamShape::boundingRect() const
{
    QRectF boundingRect{m_foamRect};
    if (m_showPipes) {
        qreal pipeLength{m_foamRect.width() / 6};
        boundingRect.adjust(-pipeLength, 0.0, pipeLength, 0.0);
    }
    if (m_showCollector) {
        qreal collectorLength{m_foamRect.width() / 3};
        boundingRect.adjust(0.0, 0.0, 0.0, collectorLength);
    }
    qreal halfpw{pen().style() == Qt::NoPen ? qreal(0.0) : pen().widthF() / 2};
    if (halfpw > 0.0)
        boundingRect.adjust(-halfpw, -halfpw, halfpw, halfpw);

    return boundingRect;
}

QPainterPath FoamShape::shape() const
{
    QPainterPath path;
    path.addPolygon(basePolygon(rect()));

    qreal sixthWidth{m_foamRect.width() / 6}; // 5.0
    if (m_showPipes) {
        qreal pipeY{m_foamRect.bottom() - sixthWidth};
        QPointF rightPipeP1{m_foamRect.right(), pipeY};
        QPointF rightPipeP2{m_foamRect.right() + sixthWidth, pipeY};
        // Right pipe
        path.moveTo(rightPipeP1);
        path.lineTo(rightPipeP2);

        QPointF rightConnectP1{rightPipeP2.x(), rightPipeP2.y() + sixthWidth / 2};
        QPointF rightConnectP2{rightPipeP2.x(), rightPipeP2.y() - sixthWidth / 2};
        // Right pipe connection
        path.moveTo(rightConnectP1);
        path.lineTo(rightConnectP2);

        QPointF leftPipeP1{m_foamRect.left(), pipeY};
        QPointF leftPipeP2{m_foamRect.left() - sixthWidth, pipeY};
        // Left pipe
        path.moveTo(leftPipeP1);
        path.lineTo(leftPipeP2);

        QPointF leftConnectP1{leftPipeP2.x(), leftPipeP2.y() + sixthWidth / 2};
        QPointF leftConnectP2{leftPipeP2.x(), leftPipeP2.y() - sixthWidth / 2};
        // Right pipe connection
        path.moveTo(leftConnectP1);
        path.lineTo(leftConnectP2);
    }

    if (m_showCollector) {
        qreal collectorX{m_foamRect.center().x()};
        qreal collectorY{m_foamRect.bottom() + sixthWidth * 2};
        qreal leftPipeX{collectorX - sixthWidth};
        QPointF leftRightPipeP1{collectorX, m_foamRect.bottom()};
        QPointF leftPipeP2{leftPipeX, collectorY};
        //Left collector pipe
        path.moveTo(leftRightPipeP1);
        path.lineTo(leftPipeP2);

        qreal rightPipeX{collectorX + sixthWidth};
        QPointF rightPipeP2{rightPipeX, collectorY};
        //Right collector pipe
        path.moveTo(leftRightPipeP1);
        path.lineTo(rightPipeP2);

        QPointF leftConnectP1{leftPipeX - sixthWidth / 2, collectorY};
        QPointF leftConnectP2{leftPipeX + sixthWidth / 2, collectorY};
        //Left connector
        path.moveTo(leftConnectP1);
        path.lineTo(leftConnectP2);

        QPointF rightConnectP1{rightPipeX - sixthWidth / 2, collectorY};
        QPointF rightConnectP2{rightPipeX + sixthWidth / 2, collectorY};
        //Right connector
        path.moveTo(rightConnectP1);
        path.lineTo(rightConnectP2);
    }

    return shapeFromPath(path);
}

QPixmap FoamShape::image()
{
    qreal pixmapWidth{boundingRect().width()};
    qreal pixmapHeight{boundingRect().height()};
    QPixmap pixmap(pixmapWidth, pixmapHeight);
    pixmap.fill(Qt::transparent);

    QPainter painter(&pixmap);
    painter.setPen(pen());
    painter.setBrush(brush());
    painter.translate(pixmapWidth / 2.0, pixmapHeight / 2.0);
    drawFoamShape(&painter);

    return pixmap;
}

TechnicsShape::ShapeType FoamShape::shapeType() const
{
        return m_foamType;
}

void FoamShape::setRect(const QRectF &rect)
{
    if (m_foamRect == rect)
        return;

    prepareGeometryChange();
    m_foamRect.setRect(rect.topLeft().x(), rect.topLeft().y(), rect.width(), rect.height());
    if (m_foamText != nullptr)
        m_foamText->setPos(m_foamRect.right(), m_foamRect.bottom()
                                                   - m_foamRect.width() / 6);
    if (m_showPipes) {
        qreal pipeLength{m_foamRect.width() / 6};
        m_foamRect.adjust(pipeLength, 0.0, -pipeLength, 0.0);
    }
    if (m_showCollector) {
        qreal collectorLength{m_foamRect.width() / 3};
        m_foamRect.adjust(0.0, 0.0, 0.0, -collectorLength);
    }
    update();
}

QRectF FoamShape::rect() const
{
        return m_foamRect;
}

void FoamShape::setHeight(const qreal &height)
{
    if (m_foamRect.height() == height)
        return;

    qreal oldHeight{m_foamRect.height()};
    prepareGeometryChange();
    m_foamRect.setHeight(height);
    qreal dy{(m_foamRect.height() - oldHeight) / 2};
    m_foamRect.moveTo(QPointF(m_foamRect.x(), m_foamRect.y() - dy));
    update();
}

qreal FoamShape::height() const
{
        return m_foamRect.height();
}

void FoamShape::setText(const QString &text)
{
    if (m_foamText == nullptr) {
        m_foamText = new QGraphicsTextItem(this);
        m_foamText->setTextInteractionFlags(Qt::TextEditorInteraction);
        m_foamText->setRotation(-90);
    }
    m_foamText->setPlainText(text);
    m_showText = true;
}

QString FoamShape::text() const
{
    if (m_foamText == nullptr)
        return "";

    return m_foamText->toPlainText();
}

void FoamShape::setPipes(bool showPipes)
{
    if (m_showPipes == showPipes)
        return;

    prepareGeometryChange();
    m_showPipes = showPipes;
    setSelected(false);
    setSelected(true);
    update();
}

bool FoamShape::pipes() const
{
        return m_showPipes;
}

void FoamShape::setCollector(bool showCollector)
{
    if (m_showCollector == showCollector)
        return;

    prepareGeometryChange();
    m_showCollector = showCollector;
    setSelected(false);
    setSelected(true);
    update();
}

bool FoamShape::collector()
{
        return m_showCollector;
}

void FoamShape::mousePressEvent(QGraphicsSceneMouseEvent *mouseEvent)
{
    if (mouseEvent->buttons() == Qt::RightButton) {
        createAction();
        addActions(m_foamActionList);
        QAction menuAction{menu()->exec(mouseEvent->screenPos())};
        QString menuActionText;
        if (menuAction.parent()) {
            menuActionText = menuAction.parent()->objectName();
        }
        if ((menuActionText != "actionDeleteItem") && (menuActionText != "actionCut")) {
            removeActions(m_foamActionList);
            m_foamActionList.clear();
        }
    } else {
        AbstractShape::mousePressEvent(mouseEvent);
    }
}

void FoamShape::createAction()
{
    QString pipeActionText{m_showPipes ? QObject::tr("Hide pipes") : QObject::tr("Show pipes")};
    m_showPipeAction.reset(new QAction(pipeActionText));
    m_showPipeAction->setToolTip(QObject::tr("Show or hide the pipes"));
    QObject::connect(m_showPipeAction.get(), &QAction::triggered
                     , [this]() {m_showPipes ? setPipes(false) : setPipes(true);});
    m_foamActionList.append(m_showPipeAction.get());

    QString collectActionText{m_showCollector ? QObject::tr("Hide collector")
                                              : QObject::tr("Show collector")};
    m_showCollectorAction.reset(new QAction(collectActionText));
    m_showCollectorAction->setToolTip(QObject::tr("Show or hide the water collector"));
    QObject::connect(m_showCollectorAction.get(), &QAction::triggered
                     , [this](){m_showCollector ? setCollector(false) : setCollector(true);});
    m_foamActionList.append(m_showCollectorAction.get());

    QString addText{m_showText ? QObject::tr("Hide text") : QObject::tr("Show text")};
    m_addTextAction.reset(new QAction(addText));
    m_addTextAction->setToolTip(QObject::tr("Show or hide text"));
    QObject::connect(m_addTextAction.get(), &QAction::triggered
                     , [this](){m_showText ? textShow(false) : textShow(true);});
    m_foamActionList.append(m_addTextAction.get());
}

void FoamShape::textShow(bool showText)
{
    if (showText) {
        if (m_foamText == nullptr) {
            m_foamText=new QGraphicsTextItem(this);
            m_foamText->setPlainText("АПТ-");
            m_foamText->setTextInteractionFlags(Qt::TextEditorInteraction);
            m_foamText->setRotation(-90);
        }
        m_foamText->show();
        m_showText = true;
    } else {
        m_foamText->hide();
        m_showText = false;
    }
}

void FoamShape::drawFoamShape(QPainter *painter)
{
    painter->drawPolygon(basePolygon(rect()));

    //Draw foam icon
    qreal thirdWidth{m_foamRect.width() / 3}; // 10.0
    qreal fifthHeight{m_foamRect.height() / 5}; // 15.0
    qreal ellipseCenterX{m_foamRect.center().x()};
    qreal ellipseCenterY{m_foamRect.center().y() + fifthHeight}; // (0.0, 15.0)
    QPointF ellipseCenter{ellipseCenterX, ellipseCenterY};
    // Point on a circle. x = x0 + r * cos(a); y = y0 + r * sin(a)
    // Starts at 3 o'clock, direction clockwise.
    QPointF leftTop{ellipseCenterX + thirdWidth * qCos(qDegreesToRadians(225.0)),
                    ellipseCenterY + thirdWidth * qSin(qDegreesToRadians(225.0))};
    QPointF rightTop{ellipseCenterX + thirdWidth * qCos(qDegreesToRadians(315.0)),
                     ellipseCenterY + thirdWidth * qSin(qDegreesToRadians(315.0))};
    QPointF leftBottom{ellipseCenterX + thirdWidth * qCos(qDegreesToRadians(135.0)),
                       ellipseCenterY + thirdWidth * qSin(qDegreesToRadians(135.0))};
    QPointF rightBottom{ellipseCenterX + thirdWidth * qCos(qDegreesToRadians(45.0)),
                        ellipseCenterY + thirdWidth * qSin(qDegreesToRadians(45.0))};
    painter->drawEllipse(ellipseCenter, thirdWidth, thirdWidth);
    painter->drawLine(leftTop, rightBottom);
    painter->drawLine(leftBottom, rightTop);

    if (m_showText) {
        m_foamText->setPos(m_foamRect.right(), m_foamRect.bottom() - thirdWidth);
    }
    qreal sixthWidth{m_foamRect.width() / 6}; // 5.0
    if (m_showPipes) {
        drawPipes(painter, sixthWidth);
    }

    if (m_showCollector) {
        drawCollector(painter, sixthWidth);
    }
}

void FoamShape::drawPipes(QPainter *painter, qreal sixtWidth)
{
    painter->setPen(QPen(Qt::black, 1));
    qreal pipeY{m_foamRect.bottom() - sixtWidth};
    QPointF rightPipeP1{m_foamRect.right(), pipeY};
    QPointF rightPipeP2{m_foamRect.right() + sixtWidth, pipeY};
    painter->drawLine(rightPipeP1, rightPipeP2); // Right pipe

    QPointF rightConnectP1{rightPipeP2.x(), rightPipeP2.y() + sixtWidth / 2};
    QPointF rightConnectP2{rightPipeP2.x(), rightPipeP2.y() - sixtWidth / 2};
    painter->drawLine(rightConnectP1, rightConnectP2); // Right pipe connection

    QPointF leftPipeP1{m_foamRect.left(), pipeY};
    QPointF leftPipeP2{m_foamRect.left() - sixtWidth, pipeY};
    painter->drawLine(leftPipeP1, leftPipeP2); // Left pipe

    QPointF leftConnectP1{leftPipeP2.x(), leftPipeP2.y() + sixtWidth / 2};
    QPointF leftConnectP2{leftPipeP2.x(), leftPipeP2.y() - sixtWidth / 2};
    painter->drawLine(leftConnectP1, leftConnectP2); // Right pipe connection
}

void FoamShape::drawCollector(QPainter *painter, qreal sixtWidth)
{
    painter->setPen(QPen(Qt::black, 1));
    qreal collectorX{m_foamRect.center().x()};
    qreal collectorY{m_foamRect.bottom() + sixtWidth * 2};
    qreal leftPipeX{collectorX - sixtWidth};
    QPointF leftRightPipeP1{collectorX, m_foamRect.bottom()};
    QPointF leftPipeP2{leftPipeX, collectorY};
    painter->drawLine(leftRightPipeP1, leftPipeP2); //Left collector pipe

    qreal rightPipeX{collectorX + sixtWidth};
    QPointF rightPipeP2{rightPipeX, collectorY};
    painter->drawLine(leftRightPipeP1, rightPipeP2); //Right collector pipe

    QPointF leftConnectP1{leftPipeX - sixtWidth / 2, collectorY};
    QPointF leftConnectP2{leftPipeX + sixtWidth / 2, collectorY};
    painter->drawLine(leftConnectP1, leftConnectP2); //Left connector

    QPointF rightConnectP1{rightPipeX - sixtWidth / 2, collectorY};
    QPointF rightConnectP2{rightPipeX + sixtWidth / 2, collectorY};
    painter->drawLine(rightConnectP1, rightConnectP2);  //Right connector
}

ComboShape::ComboShape(QGraphicsItem *parent)
    : TechnicsShape(parent)
    , m_comboType(Combo)
    , m_comboText{nullptr}
    , m_comboRect{QRectF(-15.0, -37.5, 30.0, 75.0)}
    , m_showPipes{false}
    , m_showCollector{false}
    , m_showText{false}
{
    setFlag(ItemSendsGeometryChanges, true);
    setAcceptHoverEvents(true);
    setPen(QPen(Qt::red, 1));
    setBrush(QBrush(Qt::white));
}

void ComboShape::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(widget);

    painter->setRenderHint(QPainter::Antialiasing);
    painter->setRenderHint(QPainter::SmoothPixmapTransform);
    painter->setPen(pen());
    painter->setBrush(brush());

    drawComboShape(painter);

    if (option->state & QStyle::State_Selected)
        highlightSelected(painter, option);
}

QRectF ComboShape::boundingRect() const
{
    QRectF boundingRect{m_comboRect};
    if (m_showPipes) {
        qreal pipeLength{m_comboRect.width() / 6};
        boundingRect.adjust(-pipeLength, 0.0, pipeLength, 0.0);
    }
    if (m_showCollector) {
        qreal collectorLength{m_comboRect.width() / 3};
        boundingRect.adjust(0.0, 0.0, 0.0, collectorLength);
    }
    qreal halfpw{pen().style() == Qt::NoPen ? qreal(0.0) : pen().widthF() / 2};
    if (halfpw > 0.0)
        boundingRect.adjust(-halfpw, -halfpw, halfpw, halfpw);

    return boundingRect;
}

QPainterPath ComboShape::shape() const
{
    QPainterPath path;
    path.addPolygon(basePolygon(rect()));

    qreal sixthWidth{m_comboRect.width() / 6}; // 5.0
    if (m_showPipes) {
        qreal pipeY{m_comboRect.bottom() - sixthWidth};
        QPointF rightPipeP1{m_comboRect.right(), pipeY};
        QPointF rightPipeP2{m_comboRect.right() + sixthWidth, pipeY};
        // Right pipe
        path.moveTo(rightPipeP1);
        path.lineTo(rightPipeP2);

        QPointF rightConnectP1{rightPipeP2.x(), rightPipeP2.y() + sixthWidth / 2};
        QPointF rightConnectP2{rightPipeP2.x(), rightPipeP2.y() - sixthWidth / 2};
        // Right pipe connection
        path.moveTo(rightConnectP1);
        path.lineTo(rightConnectP2);

        QPointF leftPipeP1{m_comboRect.left(), pipeY};
        QPointF leftPipeP2{m_comboRect.left() - sixthWidth, pipeY};
        // Left pipe
        path.moveTo(leftPipeP1);
        path.lineTo(leftPipeP2);

        QPointF leftConnectP1{leftPipeP2.x(), leftPipeP2.y() + sixthWidth / 2};
        QPointF leftConnectP2{leftPipeP2.x(), leftPipeP2.y() - sixthWidth / 2};
        // Right pipe connection
        path.moveTo(leftConnectP1);
        path.lineTo(leftConnectP2);
    }

    if (m_showCollector) {
        qreal collectorX{m_comboRect.center().x()};
        qreal collectorY{m_comboRect.bottom() + sixthWidth * 2};
        qreal leftPipeX{collectorX - sixthWidth};
        QPointF leftRightPipeP1{collectorX, m_comboRect.bottom()};
        QPointF leftPipeP2{leftPipeX, collectorY};
        //Left collector pipe
        path.moveTo(leftRightPipeP1);
        path.lineTo(leftPipeP2);

        qreal rightPipeX{collectorX + sixthWidth};
        QPointF rightPipeP2{rightPipeX, collectorY};
        //Right collector pipe
        path.moveTo(leftRightPipeP1);
        path.lineTo(rightPipeP2);

        QPointF leftConnectP1{leftPipeX - sixthWidth / 2, collectorY};
        QPointF leftConnectP2{leftPipeX + sixthWidth / 2, collectorY};
        //Left connector
        path.moveTo(leftConnectP1);
        path.lineTo(leftConnectP2);

        QPointF rightConnectP1{rightPipeX - sixthWidth / 2, collectorY};
        QPointF rightConnectP2{rightPipeX + sixthWidth / 2, collectorY};
        //Right connector
        path.moveTo(rightConnectP1);
        path.lineTo(rightConnectP2);
    }

    return shapeFromPath(path);
}

QPixmap ComboShape::image()
{
    qreal pixmapWidth{boundingRect().width()};
    qreal pixmapHeight{boundingRect().height()};
    QPixmap pixmap(pixmapWidth, pixmapHeight);
    pixmap.fill(Qt::transparent);

    QPainter painter(&pixmap);
    painter.setPen(pen());
    painter.setBrush(brush());
    painter.translate(pixmapWidth / 2.0, pixmapHeight / 2.0);
    drawComboShape(&painter);

    return pixmap;
}

TechnicsShape::ShapeType ComboShape::shapeType() const
{
    return m_comboType;
}

void ComboShape::setRect(const QRectF &rect)
{
    if (m_comboRect == rect)
        return;

    prepareGeometryChange();
    m_comboRect.setRect(rect.topLeft().x(), rect.topLeft().y(), rect.width(), rect.height());
    if (m_comboText != nullptr)
        m_comboText->setPos(m_comboRect.right(), m_comboRect.bottom()
                                                   - m_comboRect.width() / 6);
    if (m_showPipes) {
        qreal pipeLength{m_comboRect.width() / 6};
        m_comboRect.adjust(pipeLength, 0.0, -pipeLength, 0.0);
    }
    if (m_showCollector) {
        qreal collectorLength{m_comboRect.width() / 3};
        m_comboRect.adjust(0.0, 0.0, 0.0, -collectorLength);
    }
    update();
}

QRectF ComboShape::rect() const
{
    return m_comboRect;
}

void ComboShape::setHeight(const qreal &height)
{
    if (m_comboRect.height() == height)
        return;

    qreal oldHeight{m_comboRect.height()};
    prepareGeometryChange();
    m_comboRect.setHeight(height);
    qreal dy{(m_comboRect.height() - oldHeight) / 2};
    m_comboRect.moveTo(QPointF(m_comboRect.x(), m_comboRect.y() - dy));
    update();
}

qreal ComboShape::height() const
{
    return m_comboRect.height();
}

void ComboShape::setText(const QString &text)
{
    if (m_comboText == nullptr) {
        m_comboText = new QGraphicsTextItem(this);
        m_comboText->setTextInteractionFlags(Qt::TextEditorInteraction);
        m_comboText->setRotation(-90);
    }
    m_comboText->setPlainText(text);
    m_showText = true;
}

QString ComboShape::text() const
{
    if (m_comboText == nullptr)
        return "";

    return m_comboText->toPlainText();
}

void ComboShape::setPipes(bool showPipes)
{
    if (m_showPipes == showPipes)
        return;

    prepareGeometryChange();
    m_showPipes = showPipes;
    setSelected(false);
    setSelected(true);
    update();
}

bool ComboShape::pipes() const
{
    return m_showPipes;
}

void ComboShape::setCollector(bool showCollector)
{
    if (m_showCollector == showCollector)
        return;

    prepareGeometryChange();
    m_showCollector = showCollector;
    setSelected(false);
    setSelected(true);
    update();
}

bool ComboShape::collector()
{
    return m_showCollector;
}

void ComboShape::mousePressEvent(QGraphicsSceneMouseEvent *mouseEvent)
{
    if (mouseEvent->buttons() == Qt::RightButton) {
        createAction();
        addActions(m_comboActionList);
        QAction menuAction{menu()->exec(mouseEvent->screenPos())};
        QString menuActionText;
        if (menuAction.parent()) {
            menuActionText = menuAction.parent()->objectName();
        }
        if ((menuActionText != "actionDeleteItem") && (menuActionText != "actionCut")) {
            removeActions(m_comboActionList);
            m_comboActionList.clear();
        }
    } else {
        AbstractShape::mousePressEvent(mouseEvent);
    }
}

void ComboShape::createAction()
{
    QString pipeActionText{m_showPipes ? QObject::tr("Hide pipes") : QObject::tr("Show pipes")};
    m_showPipeAction.reset(new QAction(pipeActionText));
    m_showPipeAction->setToolTip(QObject::tr("Show or hide the pipes"));
    QObject::connect(m_showPipeAction.get(), &QAction::triggered
                     , [this]() {m_showPipes ? setPipes(false) : setPipes(true);});
    m_comboActionList.append(m_showPipeAction.get());

    QString collectActionText{m_showCollector ? QObject::tr("Hide collector")
                                              : QObject::tr("Show collector")};
    m_showCollectorAction.reset(new QAction(collectActionText));
    m_showCollectorAction->setToolTip(QObject::tr("Show or hide the water collector"));
    QObject::connect(m_showCollectorAction.get(), &QAction::triggered
                     , [this](){m_showCollector ? setCollector(false) : setCollector(true);});
    m_comboActionList.append(m_showCollectorAction.get());

    QString addText{m_showText ? QObject::tr("Hide text") : QObject::tr("Show text")};
    m_addTextAction.reset(new QAction(addText));
    m_addTextAction->setToolTip(QObject::tr("Show or hide text"));
    QObject::connect(m_addTextAction.get(), &QAction::triggered
                     , [this](){m_showText ? textShow(false) : textShow(true);});
    m_comboActionList.append(m_addTextAction.get());
}

void ComboShape::textShow(bool showText)
{
    if (showText) {
        if (m_comboText == nullptr) {
            m_comboText=new QGraphicsTextItem(this);
            m_comboText->setPlainText("АКТ-");
            m_comboText->setTextInteractionFlags(Qt::TextEditorInteraction);
            m_comboText->setRotation(-90);
        }
        m_comboText->show();
        m_showText = true;
    } else {
        m_comboText->hide();
        m_showText = false;
    }
}

void ComboShape::drawComboShape(QPainter *painter)
{
    painter->drawPolygon(basePolygon(rect()));

    //Draw foam icon
    qreal thirdWidth{m_comboRect.width() / 3}; // 10.0
    qreal fifthHeight{m_comboRect.height() / 5}; // 15.0
    qreal ellipseCenterX{m_comboRect.center().x()};
    qreal ellipseCenterY{m_comboRect.bottom() - fifthHeight}; // (0.0, 22.5)
    QPointF ellipseCenter{ellipseCenterX, ellipseCenterY};
    // Point on a circle. x = x0 + r * cos(a); y = y0 + r * sin(a)
    // Starts at 3 o'clock, direction clockwise.
    QPointF leftTop{ellipseCenterX + thirdWidth * qCos(qDegreesToRadians(225.0)),
                    ellipseCenterY + thirdWidth * qSin(qDegreesToRadians(225.0))};
    QPointF rightTop{ellipseCenterX + thirdWidth * qCos(qDegreesToRadians(315.0)),
                     ellipseCenterY + thirdWidth * qSin(qDegreesToRadians(315.0))};
    QPointF leftBottom{ellipseCenterX + thirdWidth * qCos(qDegreesToRadians(135.0)),
                       ellipseCenterY + thirdWidth * qSin(qDegreesToRadians(135.0))};
    QPointF rightBottom{ellipseCenterX + thirdWidth * qCos(qDegreesToRadians(45.0)),
                        ellipseCenterY + thirdWidth * qSin(qDegreesToRadians(45.0))};
    painter->drawEllipse(ellipseCenter, thirdWidth, thirdWidth);
    painter->drawLine(leftTop, rightBottom);
    painter->drawLine(leftBottom, rightTop);

    //Draw powder icon
    painter->setBrush(QBrush(Qt::red));
    qreal sixthWidth{m_comboRect.width() / 6}; // 5.0
    qreal thirdHeight{height() / 3}; // 25.0
    qreal powderX{m_comboRect.left() + sixthWidth};
    qreal powderY{m_comboRect.top() + thirdHeight};
    qreal powderWidth{m_comboRect.width() - (sixthWidth * 2)};
    qreal powderHeight{height() / 3.75}; // 20.0
    QRectF powderRect{powderX, powderY, powderWidth, powderHeight};
    painter->drawRect(powderRect);
    painter->setBrush(brush());

    if (m_showText) {
        m_comboText->setPos(m_comboRect.right(), m_comboRect.bottom() - thirdWidth);
    }
    if (m_showPipes) {
        drawPipes(painter, sixthWidth);
    }

    if (m_showCollector) {
        drawCollector(painter, sixthWidth);
    }
}

void ComboShape::drawPipes(QPainter *painter, qreal sixtWidth)
{
    painter->setPen(QPen(Qt::black, 1));
    qreal pipeY{m_comboRect.bottom() - sixtWidth};
    QPointF rightPipeP1{m_comboRect.right(), pipeY};
    QPointF rightPipeP2{m_comboRect.right() + sixtWidth, pipeY};
    painter->drawLine(rightPipeP1, rightPipeP2); // Right pipe

    QPointF rightConnectP1{rightPipeP2.x(), rightPipeP2.y() + sixtWidth / 2};
    QPointF rightConnectP2{rightPipeP2.x(), rightPipeP2.y() - sixtWidth / 2};
    painter->drawLine(rightConnectP1, rightConnectP2); // Right pipe connection

    QPointF leftPipeP1{m_comboRect.left(), pipeY};
    QPointF leftPipeP2{m_comboRect.left() - sixtWidth, pipeY};
    painter->drawLine(leftPipeP1, leftPipeP2); // Left pipe

    QPointF leftConnectP1{leftPipeP2.x(), leftPipeP2.y() + sixtWidth / 2};
    QPointF leftConnectP2{leftPipeP2.x(), leftPipeP2.y() - sixtWidth / 2};
    painter->drawLine(leftConnectP1, leftConnectP2); // Right pipe connection
}

void ComboShape::drawCollector(QPainter *painter, qreal sixtWidth)
{
    painter->setPen(QPen(Qt::black, 1));
    qreal collectorX{m_comboRect.center().x()};
    qreal collectorY{m_comboRect.bottom() + sixtWidth * 2};
    qreal leftPipeX{collectorX - sixtWidth};
    QPointF leftRightPipeP1{collectorX, m_comboRect.bottom()};
    QPointF leftPipeP2{leftPipeX, collectorY};
    painter->drawLine(leftRightPipeP1, leftPipeP2); //Left collector pipe

    qreal rightPipeX{collectorX + sixtWidth};
    QPointF rightPipeP2{rightPipeX, collectorY};
    painter->drawLine(leftRightPipeP1, rightPipeP2); //Right collector pipe

    QPointF leftConnectP1{leftPipeX - sixtWidth / 2, collectorY};
    QPointF leftConnectP2{leftPipeX + sixtWidth / 2, collectorY};
    painter->drawLine(leftConnectP1, leftConnectP2); //Left connector

    QPointF rightConnectP1{rightPipeX - sixtWidth / 2, collectorY};
    QPointF rightConnectP2{rightPipeX + sixtWidth / 2, collectorY};
    painter->drawLine(rightConnectP1, rightConnectP2);  //Right connector
}

AerosolShape::AerosolShape(QGraphicsItem *parent)
    : TechnicsShape(parent)
    , m_aerosolType{Aerosol}
    , m_aerosolRect{-15.0, -37.5, 30.0, 75.0}
    , m_aerosolText{nullptr}
    , m_showText{false}
{
    setFlag(ItemSendsGeometryChanges, true);
    setAcceptHoverEvents(true);
    setPen(QPen(Qt::red, 1));
    setBrush(QBrush(Qt::white));
}

void AerosolShape::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(widget);

    painter->setRenderHint(QPainter::Antialiasing);
    painter->setRenderHint(QPainter::SmoothPixmapTransform);
    painter->setPen(pen());
    painter->setBrush(brush());

    drawAerosolShape(painter);

    if (option->state & QStyle::State_Selected)
        highlightSelected(painter, option);
}

QRectF AerosolShape::boundingRect() const
{
    QRectF boundingRect{m_aerosolRect};
    qreal halfpw{pen().style() == Qt::NoPen ? qreal(0.0) : pen().widthF() / 2};
    if (halfpw > 0.0)
        boundingRect.adjust(-halfpw, -halfpw, halfpw, halfpw);
    return boundingRect;
}

QPainterPath AerosolShape::shape() const
{
    QPainterPath path;
    path.addPolygon(basePolygon(rect()));

    return shapeFromPath(path);
}

QPixmap AerosolShape::image()
{
    qreal pixmapWidth{boundingRect().width()};
    qreal pixmapHeight{boundingRect().height()};
    QPixmap pixmap(pixmapWidth, pixmapHeight);
    pixmap.fill(Qt::transparent);

    QPainter painter(&pixmap);
    painter.setPen(pen());
    painter.setBrush(brush());
    painter.translate(pixmapWidth / 2.0, pixmapHeight / 2.0);
    drawAerosolShape(&painter);

    return pixmap;
}

TechnicsShape::ShapeType AerosolShape::shapeType() const
{
    return m_aerosolType;
}

void AerosolShape::setRect(const QRectF &rect)
{
    if (m_aerosolRect == rect)
        return;

    prepareGeometryChange();
    m_aerosolRect.setRect(rect.topLeft().x(), rect.topLeft().y(), rect.width(), rect.height());
    if (m_aerosolText != nullptr)
        m_aerosolText->setPos(m_aerosolRect.right(), m_aerosolRect.bottom()
                                                           - m_aerosolRect.width() / 6);
    update();
}

QRectF AerosolShape::rect() const
{
    return m_aerosolRect;
}

void AerosolShape::setHeight(const qreal &height)
{
    if (m_aerosolRect.height() == height)
        return;

    qreal oldHeight{m_aerosolRect.height()};
    prepareGeometryChange();
    m_aerosolRect.setHeight(height);
    qreal dy{(m_aerosolRect.height() - oldHeight) / 2};
    m_aerosolRect.moveTo(QPointF(m_aerosolRect.x(), m_aerosolRect.y() - dy));
    update();
}

qreal AerosolShape::height() const
{
    return m_aerosolRect.height();
}

void AerosolShape::setText(const QString &text)
{
    if (m_aerosolText == nullptr) {
        m_aerosolText = new QGraphicsTextItem(this);
        m_aerosolText->setTextInteractionFlags(Qt::TextEditorInteraction);
        m_aerosolText->setRotation(-90);
    }
    m_aerosolText->setPlainText(text);
    m_showText = true;
}

QString AerosolShape::text() const
{
    if (m_aerosolText == nullptr)
        return "";

    return m_aerosolText->toPlainText();
}

void AerosolShape::mousePressEvent(QGraphicsSceneMouseEvent *mouseEvent)
{
    if (mouseEvent->buttons() == Qt::RightButton) {
        createAction();
        addActions(m_aerosolActionList);
        QAction menuAction{menu()->exec(mouseEvent->screenPos())};
        QString menuActionText;
        if (menuAction.parent()) {
            menuActionText = menuAction.parent()->objectName();
        }
        if ((menuActionText != "actionDeleteItem") && (menuActionText != "actionCut")) {
            removeActions(m_aerosolActionList);
            m_aerosolActionList.clear();
        }
    } else {
        AbstractShape::mousePressEvent(mouseEvent);
    }
}

void AerosolShape::createAction()
{
    QString addText{m_showText ? QObject::tr("Hide text") : QObject::tr("Show text")};
    m_addTextAction.reset(new QAction(addText));
    m_addTextAction->setToolTip(QObject::tr("Show or hide text"));
    QObject::connect(m_addTextAction.get(), &QAction::triggered
                     , [this](){m_showText ? textShow(false) : textShow(true);});
    m_aerosolActionList.append(m_addTextAction.get());
}

void AerosolShape::textShow(bool showText)
{
    if (showText) {
        if (m_aerosolText == nullptr) {
            m_aerosolText=new QGraphicsTextItem(this);
            m_aerosolText->setPlainText("АВТ-");
            m_aerosolText->setTextInteractionFlags(Qt::TextEditorInteraction);
            m_aerosolText->setRotation(-90);
        }
        m_aerosolText->show();
        m_showText = true;
    } else {
        m_aerosolText->hide();
        m_showText = false;
    }
}

void AerosolShape::drawAerosolShape(QPainter *painter)
{
    painter->drawPolygon(basePolygon(rect()));

    // Draw aerosol icon
    qreal fifteenthHeight{m_aerosolRect.height() / 15.0}; // 5.0
    qreal ellipseX{m_aerosolRect.center().x()};
    qreal topEllipseY{m_aerosolRect.bottom() - fifteenthHeight * 2.0};
    qreal centerEllipseY{topEllipseY - fifteenthHeight * 3.0};
    qreal bottomEllipseY{centerEllipseY - fifteenthHeight * 3.0};
    QPointF topEllipse{ellipseX, topEllipseY};
    QPointF centerEllipse{ellipseX, centerEllipseY};
    QPointF bottomEllipse{ellipseX, bottomEllipseY};
    painter->setBrush(QBrush(Qt::red));
    painter->drawEllipse(topEllipse, fifteenthHeight, fifteenthHeight);
    painter->drawEllipse(centerEllipse, fifteenthHeight, fifteenthHeight);
    painter->drawEllipse(bottomEllipse, fifteenthHeight, fifteenthHeight);
    painter->setBrush(brush());

    if (m_showText)
        m_aerosolText->setPos(m_aerosolRect.right(), m_aerosolRect.bottom());
}

PowderShape::PowderShape(QGraphicsItem *parent)
    : TechnicsShape(parent)
    , m_powderType{Powder}
    , m_powderRect{-15.0, -37.5, 30.0, 75.0}
    , m_powderText{nullptr}
    , m_showText{false}
{
    setFlag(ItemSendsGeometryChanges, true);
    setAcceptHoverEvents(true);
    setPen(QPen(Qt::red, 1));
    setBrush(QBrush(Qt::white));
}

void PowderShape::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(widget);

    painter->setRenderHint(QPainter::Antialiasing);
    painter->setRenderHint(QPainter::SmoothPixmapTransform);
    painter->setPen(pen());
    painter->setBrush(brush());

    drawPowderShape(painter);

    if (option->state & QStyle::State_Selected)
        highlightSelected(painter, option);
}

QRectF PowderShape::boundingRect() const
{
    QRectF boundingRect{m_powderRect};
    qreal halfpw{pen().style() == Qt::NoPen ? qreal(0.0) : pen().widthF() / 2};
    if (halfpw > 0.0)
        boundingRect.adjust(-halfpw, -halfpw, halfpw, halfpw);
    return boundingRect;
}

QPainterPath PowderShape::shape() const
{
    QPainterPath path;
    path.addPolygon(basePolygon(rect()));

    return shapeFromPath(path);
}

QPixmap PowderShape::image()
{
    qreal pixmapWidth{boundingRect().width()};
    qreal pixmapHeight{boundingRect().height()};
    QPixmap pixmap(pixmapWidth, pixmapHeight);
    pixmap.fill(Qt::transparent);

    QPainter painter(&pixmap);
    painter.setPen(pen());
    painter.setBrush(brush());
    painter.translate(pixmapWidth / 2.0, pixmapHeight / 2.0);
    drawPowderShape(&painter);

    return pixmap;
}

TechnicsShape::ShapeType PowderShape::shapeType() const
{
    return m_powderType;
}

void PowderShape::setRect(const QRectF &rect)
{
    if (m_powderRect == rect)
        return;

    prepareGeometryChange();
    m_powderRect.setRect(rect.topLeft().x(), rect.topLeft().y(), rect.width(), rect.height());
    if (m_powderText != nullptr)
        m_powderText->setPos(m_powderRect.right(), m_powderRect.bottom()
                                                         - m_powderRect.width() / 6);
    update();
}

QRectF PowderShape::rect() const
{
    return m_powderRect;
}

void PowderShape::setHeight(const qreal &height)
{
    if (m_powderRect.height() == height)
        return;

    qreal oldHeight{m_powderRect.height()};
    prepareGeometryChange();
    m_powderRect.setHeight(height);
    qreal dy{(m_powderRect.height() - oldHeight) / 2};
    m_powderRect.moveTo(QPointF(m_powderRect.x(), m_powderRect.y() - dy));
    update();
}

qreal PowderShape::height() const
{
    return m_powderRect.height();
}

void PowderShape::setText(const QString &text)
{
    if (m_powderText == nullptr) {
        m_powderText = new QGraphicsTextItem(this);
        m_powderText->setTextInteractionFlags(Qt::TextEditorInteraction);
        m_powderText->setRotation(-90);
    }
    m_powderText->setPlainText(text);
    m_showText = true;
}

QString PowderShape::text() const
{
    if (m_powderText == nullptr)
        return "";

    return m_powderText->toPlainText();
}

void PowderShape::mousePressEvent(QGraphicsSceneMouseEvent *mouseEvent)
{
    if (mouseEvent->buttons() == Qt::RightButton) {
        createAction();
        addActions(m_powderActionList);
        QAction menuAction{menu()->exec(mouseEvent->screenPos())};
        QString menuActionText;
        if (menuAction.parent()) {
            menuActionText = menuAction.parent()->objectName();
        }
        if ((menuActionText != "actionDeleteItem") && (menuActionText != "actionCut")) {
            removeActions(m_powderActionList);
            m_powderActionList.clear();
        }
    } else {
        AbstractShape::mousePressEvent(mouseEvent);
    }
}

void PowderShape::createAction()
{
    QString addText{m_showText ? QObject::tr("Hide text") : QObject::tr("Show text")};
    m_addTextAction.reset(new QAction(addText));
    m_addTextAction->setToolTip(QObject::tr("Show or hide text"));
    QObject::connect(m_addTextAction.get(), &QAction::triggered
                     , [this](){m_showText ? textShow(false) : textShow(true);});
    m_powderActionList.append(m_addTextAction.get());
}

void PowderShape::textShow(bool showText)
{
    if (showText) {
        if (m_powderText == nullptr) {
            m_powderText=new QGraphicsTextItem(this);
            m_powderText->setPlainText("АП-");
            m_powderText->setTextInteractionFlags(Qt::TextEditorInteraction);
            m_powderText->setRotation(-90);
        }
        m_powderText->show();
        m_showText = true;
    } else {
        m_powderText->hide();
        m_showText = false;
    }
}

void PowderShape::drawPowderShape(QPainter *painter)
{
    painter->drawPolygon(basePolygon(rect()));

    //Draw powder icon
    painter->setBrush(QBrush(Qt::red));
    qreal sixthWidth{m_powderRect.width() / 6}; // 5.0
    qreal thirdHeight{height() / 3}; // 25.0
    qreal powderX{m_powderRect.left() + sixthWidth};
    qreal powderY{m_powderRect.bottom() - thirdHeight};
    qreal powderWidth{m_powderRect.width() - (sixthWidth * 2)};
    qreal powderHeight{height() / 3.75}; // 20.0
    QRectF powderRect{powderX, powderY, powderWidth, powderHeight};
    painter->drawRect(powderRect);
    painter->setBrush(brush());

    if (m_showText)
        m_powderText->setPos(m_powderRect.right(), m_powderRect.bottom());
}

CarbonShape::CarbonShape(QGraphicsItem *parent)
    : TechnicsShape(parent)
    , m_carbonType{Carbon}
    , m_carbonRect{-15.0, -37.5, 30.0, 75.0}
    , m_carbonText{nullptr}
    , m_showText{false}
{
    setFlag(ItemSendsGeometryChanges, true);
    setAcceptHoverEvents(true);
    setPen(QPen(Qt::red, 1));
    setBrush(QBrush(Qt::white));
}

void CarbonShape::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(widget);

    painter->setRenderHint(QPainter::Antialiasing);
    painter->setRenderHint(QPainter::SmoothPixmapTransform);
    painter->setPen(pen());
    painter->setBrush(brush());

    drawCarbonShape(painter);

    if (option->state & QStyle::State_Selected)
        highlightSelected(painter, option);
}

QRectF CarbonShape::boundingRect() const
{
    QRectF boundingRect{m_carbonRect};
    qreal halfpw{pen().style() == Qt::NoPen ? qreal(0.0) : pen().widthF() / 2};
    if (halfpw > 0.0)
        boundingRect.adjust(-halfpw, -halfpw, halfpw, halfpw);
    return boundingRect;
}

QPainterPath CarbonShape::shape() const
{
    QPainterPath path;
    path.addPolygon(basePolygon(rect()));

    return shapeFromPath(path);
}

QPixmap CarbonShape::image()
{
    qreal pixmapWidth{boundingRect().width()};
    qreal pixmapHeight{boundingRect().height()};
    QPixmap pixmap(pixmapWidth, pixmapHeight);
    pixmap.fill(Qt::transparent);

    QPainter painter(&pixmap);
    painter.setPen(pen());
    painter.setBrush(brush());
    painter.translate(pixmapWidth / 2.0, pixmapHeight / 2.0);
    drawCarbonShape(&painter);

    return pixmap;
}

TechnicsShape::ShapeType CarbonShape::shapeType() const
{
    return m_carbonType;
}

void CarbonShape::setRect(const QRectF &rect)
{
    if (m_carbonRect == rect)
        return;

    prepareGeometryChange();
    m_carbonRect.setRect(rect.topLeft().x(), rect.topLeft().y(), rect.width(), rect.height());
    if (m_carbonText != nullptr)
        m_carbonText->setPos(m_carbonRect.right(), m_carbonRect.bottom()
                                                       - m_carbonRect.width() / 6);
    update();
}

QRectF CarbonShape::rect() const
{
    return m_carbonRect;
}

void CarbonShape::setHeight(const qreal &height)
{
    if (m_carbonRect.height() == height)
        return;

    qreal oldHeight{m_carbonRect.height()};
    prepareGeometryChange();
    m_carbonRect.setHeight(height);
    qreal dy{(m_carbonRect.height() - oldHeight) / 2};
    m_carbonRect.moveTo(QPointF(m_carbonRect.x(), m_carbonRect.y() - dy));
    update();
}

qreal CarbonShape::height() const
{
    return m_carbonRect.height();
}

void CarbonShape::setText(const QString &text)
{
    if (m_carbonText == nullptr) {
        m_carbonText = new QGraphicsTextItem(this);
        m_carbonText->setTextInteractionFlags(Qt::TextEditorInteraction);
        m_carbonText->setRotation(-90);
    }
    m_carbonText->setPlainText(text);
    m_showText = true;
}

QString CarbonShape::text() const
{
    if (m_carbonText == nullptr)
        return "";

    return m_carbonText->toPlainText();
}

void CarbonShape::mousePressEvent(QGraphicsSceneMouseEvent *mouseEvent)
{
    if (mouseEvent->buttons() == Qt::RightButton) {
        createAction();
        addActions(m_carbonActionList);
        QAction menuAction{menu()->exec(mouseEvent->screenPos())};
        QString menuActionText;
        if (menuAction.parent()) {
            menuActionText = menuAction.parent()->objectName();
        }
        if ((menuActionText != "actionDeleteItem") && (menuActionText != "actionCut")) {
            removeActions(m_carbonActionList);
            m_carbonActionList.clear();
        }
    } else {
        AbstractShape::mousePressEvent(mouseEvent);
    }
}

void CarbonShape::createAction()
{
    QString addText{m_showText ? QObject::tr("Hide text") : QObject::tr("Show text")};
    m_addTextAction.reset(new QAction(addText));
    m_addTextAction->setToolTip(QObject::tr("Show or hide text"));
    QObject::connect(m_addTextAction.get(), &QAction::triggered
                     , [this](){m_showText ? textShow(false) : textShow(true);});
    m_carbonActionList.append(m_addTextAction.get());
}

void CarbonShape::textShow(bool showText)
{
    if (showText) {
        if (m_carbonText == nullptr) {
            m_carbonText=new QGraphicsTextItem(this);
            m_carbonText->setPlainText("АГТ-");
            m_carbonText->setTextInteractionFlags(Qt::TextEditorInteraction);
            m_carbonText->setRotation(-90);
        }
        m_carbonText->show();
        m_showText = true;
    } else {
        m_carbonText->hide();
        m_showText = false;
    }
}

void CarbonShape::drawCarbonShape(QPainter *painter)
{
    painter->drawPolygon(basePolygon(rect()));

    //Draw carbon icon
    painter->setBrush(QBrush(Qt::red));
    qreal sixthWidth{m_carbonRect.width() / 6}; // 5.0
    qreal thirdHeight{height() / 3}; // 25.0
    qreal fifteenthHeight{m_carbonRect.height() / 15.0}; // 5.0
    qreal carbonBottom{m_carbonRect.bottom() - fifteenthHeight};
    QPointF carbonTop{m_carbonRect.center().x(), m_carbonRect.bottom() - thirdHeight};
    QPointF carbonLeftBottom{m_carbonRect.left() + sixthWidth, carbonBottom};
    QPointF carbonRightBottom{m_carbonRect.right() - sixthWidth, carbonBottom};
    QPainterPath carbonPath;
    carbonPath.moveTo(carbonTop);
    carbonPath.lineTo(carbonRightBottom);
    carbonPath.lineTo(carbonLeftBottom);
    carbonPath.lineTo(carbonTop);
    painter->drawPath(carbonPath);
    painter->setBrush(brush());

    if (m_showText)
        m_carbonText->setPos(m_carbonRect.right(), m_carbonRect.bottom());
}

GazWaterShape::GazWaterShape(QGraphicsItem *parent)
    : TechnicsShape(parent)
    , m_gazWaterType{GazWater}
    , m_gazWaterRect{-15.0, -37.5, 30.0, 75.0}
    , m_gazWaterText{nullptr}
    , m_showText{false}
{
    setFlag(ItemSendsGeometryChanges, true);
    setAcceptHoverEvents(true);
    setPen(QPen(Qt::red, 1));
    setBrush(QBrush(Qt::white));
}

void GazWaterShape::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(widget);

    painter->setRenderHint(QPainter::Antialiasing);
    painter->setRenderHint(QPainter::SmoothPixmapTransform);
    painter->setPen(pen());
    painter->setBrush(brush());

    drawGazWaterShape(painter);

    if (option->state & QStyle::State_Selected)
        highlightSelected(painter, option);
}

QRectF GazWaterShape::boundingRect() const
{
    QRectF boundingRect{m_gazWaterRect};
    qreal halfpw{pen().style() == Qt::NoPen ? qreal(0.0) : pen().widthF() / 2};
    if (halfpw > 0.0)
        boundingRect.adjust(-halfpw, -halfpw, halfpw, halfpw);

    return boundingRect;
}

QPainterPath GazWaterShape::shape() const
{
    QPainterPath path;
    path.addPolygon(basePolygon(rect()));

    return shapeFromPath(path);
}

QPixmap GazWaterShape::image()
{
    qreal pixmapWidth{boundingRect().width()};
    qreal pixmapHeight{boundingRect().height()};
    QPixmap pixmap(pixmapWidth, pixmapHeight);
    pixmap.fill(Qt::transparent);

    QPainter painter(&pixmap);
    painter.setPen(pen());
    painter.setBrush(brush());
    painter.translate(pixmapWidth / 2.0, pixmapHeight / 2.0);
    drawGazWaterShape(&painter);

    return pixmap;
}

TechnicsShape::ShapeType GazWaterShape::shapeType() const
{
    return m_gazWaterType;
}

void GazWaterShape::setRect(const QRectF &rect)
{
    if (m_gazWaterRect == rect)
        return;

    prepareGeometryChange();
    m_gazWaterRect.setRect(rect.topLeft().x(), rect.topLeft().y(), rect.width(), rect.height());
    if (m_gazWaterText != nullptr)
        m_gazWaterText->setPos(m_gazWaterRect.right(), m_gazWaterRect.bottom()
                                                       - m_gazWaterRect.width() / 6);
    update();
}

QRectF GazWaterShape::rect() const
{
    return m_gazWaterRect;
}

void GazWaterShape::setHeight(const qreal &height)
{
    if (m_gazWaterRect.height() == height)
        return;

    qreal oldHeight{m_gazWaterRect.height()};
    prepareGeometryChange();
    m_gazWaterRect.setHeight(height);
    qreal dy{(m_gazWaterRect.height() - oldHeight) / 2};
    m_gazWaterRect.moveTo(QPointF(m_gazWaterRect.x(), m_gazWaterRect.y() - dy));
    update();
}

qreal GazWaterShape::height() const
{
    return m_gazWaterRect.height();
}

void GazWaterShape::setText(const QString &text)
{
    if (m_gazWaterText == nullptr) {
        m_gazWaterText = new QGraphicsTextItem(this);
        m_gazWaterText->setTextInteractionFlags(Qt::TextEditorInteraction);
        m_gazWaterText->setRotation(-90);
    }
    m_gazWaterText->setPlainText(text);
    m_showText = true;
}

QString GazWaterShape::text() const
{
    if (m_gazWaterText == nullptr)
        return "";

    return m_gazWaterText->toPlainText();
}

void GazWaterShape::mousePressEvent(QGraphicsSceneMouseEvent *mouseEvent)
{
    if (mouseEvent->buttons() == Qt::RightButton) {
        createAction();
        addActions(m_gazWaterActionList);
        QAction menuAction{menu()->exec(mouseEvent->screenPos())};
        QString menuActionText;
        if (menuAction.parent()) {
            menuActionText = menuAction.parent()->objectName();
        }
        if ((menuActionText != "actionDeleteItem") && (menuActionText != "actionCut")) {
            removeActions(m_gazWaterActionList);
            m_gazWaterActionList.clear();
        }
    } else {
        AbstractShape::mousePressEvent(mouseEvent);
    }
}

void GazWaterShape::createAction()
{
    QString addText{m_showText ? QObject::tr("Hide text") : QObject::tr("Show text")};
    m_addTextAction.reset(new QAction(addText));
    m_addTextAction->setToolTip(QObject::tr("Show or hide text"));
    QObject::connect(m_addTextAction.get(), &QAction::triggered
                     , [this](){m_showText ? textShow(false) : textShow(true);});
    m_gazWaterActionList.append(m_addTextAction.get());
}

void GazWaterShape::textShow(bool showText)
{
    if (showText) {
        if (m_gazWaterText == nullptr) {
            m_gazWaterText=new QGraphicsTextItem(this);
            m_gazWaterText->setPlainText("АГВТ-");
            m_gazWaterText->setTextInteractionFlags(Qt::TextEditorInteraction);
            m_gazWaterText->setRotation(-90);
        }
        m_gazWaterText->show();
        m_showText = true;
    } else {
        m_gazWaterText->hide();
        m_showText = false;
    }
}

void GazWaterShape::drawGazWaterShape(QPainter *painter)
{
    painter->drawPolygon(basePolygon(rect()));
    painter->translate(m_gazWaterRect.center());
    painter->rotate(270);
    painter->translate(-m_gazWaterRect.center());
    QTextOption textOption{Qt::AlignCenter};
    painter->drawText(m_gazWaterRect, "АГВТ", textOption);
    painter->translate(m_gazWaterRect.center());
    painter->rotate(-270);
    painter->translate(-m_gazWaterRect.center());

    if (m_showText)
        m_gazWaterText->setPos(m_gazWaterRect.right(), m_gazWaterRect.bottom());
}

TrackedShape::TrackedShape(QGraphicsItem *parent)
    : TechnicsShape(parent)
    , m_trackedType{Tracked}
    , m_trackedRect{-15.0, -37.5, 30.0, 75.0}
    , m_trackedText{nullptr}
    , m_showText{false}
{
    setFlag(ItemSendsGeometryChanges, true);
    setAcceptHoverEvents(true);
    setPen(QPen(Qt::red, 1));
    setBrush(QBrush(Qt::white));
}

void TrackedShape::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(widget);

    painter->setRenderHint(QPainter::Antialiasing);
    painter->setRenderHint(QPainter::SmoothPixmapTransform);
    painter->setPen(pen());
    painter->setBrush(brush());

    drawTrackedShape(painter);

    if (option->state & QStyle::State_Selected)
        highlightSelected(painter, option);
}

QRectF TrackedShape::boundingRect() const
{
    QRectF boundingRect{m_trackedRect};
    qreal halfpw{pen().style() == Qt::NoPen ? qreal(0.0) : pen().widthF() / 2};
    if (halfpw > 0.0)
        boundingRect.adjust(-halfpw, -halfpw, halfpw, halfpw);

    return boundingRect;
}

QPainterPath TrackedShape::shape() const
{
    QPainterPath path;
    path.addPolygon(basePolygon(rect()));

    return shapeFromPath(path);
}

QPixmap TrackedShape::image()
{
    qreal pixmapWidth{boundingRect().width()};
    qreal pixmapHeight{boundingRect().height()};
    QPixmap pixmap(pixmapWidth, pixmapHeight);
    pixmap.fill(Qt::transparent);

    QPainter painter(&pixmap);
    painter.setPen(pen());
    painter.setBrush(brush());
    painter.translate(pixmapWidth / 2.0, pixmapHeight / 2.0);
    drawTrackedShape(&painter);

    return pixmap;
}

TechnicsShape::ShapeType TrackedShape::shapeType() const
{
    return m_trackedType;
}

void TrackedShape::setRect(const QRectF &rect)
{
    if (m_trackedRect == rect)
        return;

    prepareGeometryChange();
    m_trackedRect.setRect(rect.topLeft().x(), rect.topLeft().y(), rect.width(), rect.height());
    if (m_trackedText != nullptr)
        m_trackedText->setPos(m_trackedRect.right(), m_trackedRect.bottom()
                                                       - m_trackedRect.width() / 6);

    update();
}

QRectF TrackedShape::rect() const
{
    return m_trackedRect;
}

void TrackedShape::setHeight(const qreal &height)
{
    if (m_trackedRect.height() == height)
        return;

    qreal oldHeight{m_trackedRect.height()};
    prepareGeometryChange();
    m_trackedRect.setHeight(height);
    qreal dy{(m_trackedRect.height() - oldHeight) / 2};
    m_trackedRect.moveTo(QPointF(m_trackedRect.x(), m_trackedRect.y() - dy));
    update();
}

qreal TrackedShape::height() const
{
    return m_trackedRect.height();
}

void TrackedShape::setText(const QString &text)
{
    if (m_trackedText == nullptr) {
        m_trackedText = new QGraphicsTextItem(this);
        m_trackedText->setTextInteractionFlags(Qt::TextEditorInteraction);
        m_trackedText->setRotation(-90);
    }
    m_trackedText->setPlainText(text);
    m_showText = true;
}

QString TrackedShape::text() const
{
    if (m_trackedText == nullptr)
        return "";

    return m_trackedText->toPlainText();
}

void TrackedShape::mousePressEvent(QGraphicsSceneMouseEvent *mouseEvent)
{
    if (mouseEvent->buttons() == Qt::RightButton) {
        createAction();
        addActions(m_trackedActionList);
        QAction menuAction{menu()->exec(mouseEvent->screenPos())};
        QString menuActionText;
        if (menuAction.parent()) {
            menuActionText = menuAction.parent()->objectName();
        }
        if ((menuActionText != "actionDeleteItem") && (menuActionText != "actionCut")) {
            removeActions(m_trackedActionList);
            m_trackedActionList.clear();
        }
    } else {
        AbstractShape::mousePressEvent(mouseEvent);
    }
}

void TrackedShape::createAction()
{
    QString addText{m_showText ? QObject::tr("Hide text") : QObject::tr("Show text")};
    m_addTextAction.reset(new QAction(addText));
    m_addTextAction->setToolTip(QObject::tr("Show or hide text"));
    QObject::connect(m_addTextAction.get(), &QAction::triggered
                     , [this](){m_showText ? textShow(false) : textShow(true);});
    m_trackedActionList.append(m_addTextAction.get());
}

void TrackedShape::textShow(bool showText)
{
    if (showText) {
        if (m_trackedText == nullptr) {
            m_trackedText=new QGraphicsTextItem(this);
            m_trackedText->setPlainText("ГПМ-");
            m_trackedText->setTextInteractionFlags(Qt::TextEditorInteraction);
            m_trackedText->setRotation(-90);
        }
        m_trackedText->show();
        m_showText = true;
    } else {
        m_trackedText->hide();
        m_showText = false;
    }
}

void TrackedShape::drawTrackedShape(QPainter *painter)
{
    painter->drawPolygon(basePolygon(rect()));

    // Draw track
    qreal frontTab{m_trackedRect.height() / 3};
    QPointF frontCenter{m_trackedRect.center().x(), m_trackedRect.top()}; // 0.0, -37.5
    QPointF frontRight{m_trackedRect.right(), m_trackedRect.top() + frontTab}; // 15.0, -12.5
    QPointF frontLeft{m_trackedRect.left(), m_trackedRect.top() + frontTab}; // -15.0, -12.5
    QLineF leftTopLine{frontLeft, frontCenter};
    QLineF rightTopLine{frontRight, frontCenter};
    qreal sixthWidth{m_trackedRect.width() / 6}; // 5.0
    qreal trackLeft{m_trackedRect.left() + sixthWidth};
    QPointF intersectLeftBottom{trackLeft, m_trackedRect.bottom()};
    QPointF intersectLeftTop{trackLeft, m_trackedRect.top()};
    QLineF leftIntersectLine{intersectLeftBottom, intersectLeftTop};
    QPointF leftTrackTop{};
    leftTopLine.intersects(leftIntersectLine, &leftTrackTop);
    QPointF leftTrackBottom{trackLeft, m_trackedRect.bottom()};
    QLineF leftTrack{leftTrackBottom, leftTrackTop};
    painter->drawLine(leftTrack);
    qreal trackRight{m_trackedRect.right() - sixthWidth};
    QPointF intersectRightBottom{trackRight, m_trackedRect.bottom()};
    QPointF intersectRightTop{trackRight, m_trackedRect.top()};
    QLineF rightIntersectLine{intersectRightBottom, intersectRightTop};
    QPointF rightTrackTop{};
    rightTopLine.intersects(rightIntersectLine, &rightTrackTop);
    QPointF rightTrackBottom{trackRight, m_trackedRect.bottom()};
    QLineF rightTrack{rightTrackBottom, rightTrackTop};
    painter->drawLine(rightTrack);

    if (m_showText)
        m_trackedText->setPos(m_trackedRect.right(), m_trackedRect.bottom());
}

TankShape::TankShape(QGraphicsItem *parent)
    : TechnicsShape(parent)
    , m_tankType{Tank}
    , m_tankRect{-18.0, -37.5, 36.0, 75.0}
    , m_tankText{nullptr}
    , m_showText{false}
{
    setFlag(ItemSendsGeometryChanges, true);
    setAcceptHoverEvents(true);
    setPen(QPen(Qt::red, 1));
    setBrush(QBrush(Qt::white));
}

void TankShape::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(widget);

    painter->setRenderHint(QPainter::Antialiasing);
    painter->setRenderHint(QPainter::SmoothPixmapTransform);
    painter->setPen(pen());
    painter->setBrush(brush());

    drawTankShape(painter);

    if (option->state & QStyle::State_Selected)
        highlightSelected(painter, option);
}

QRectF TankShape::boundingRect() const
{
    QRectF boundingRect{m_tankRect};
    qreal halfpw{pen().style() == Qt::NoPen ? qreal(0.0) : pen().widthF() / 2};
    if (halfpw > 0.0)
        boundingRect.adjust(-halfpw, -halfpw, halfpw, halfpw);

    return boundingRect;
}

QPainterPath TankShape::shape() const
{
    QPainterPath path;
    path.addPolygon(tankPolygon(rect()));

    return shapeFromPath(path);
}

QPixmap TankShape::image()
{
    qreal pixmapWidth{boundingRect().width()};
    qreal pixmapHeight{boundingRect().height()};
    QPixmap pixmap(pixmapWidth, pixmapHeight);
    pixmap.fill(Qt::transparent);

    QPainter painter(&pixmap);
    painter.setPen(pen());
    painter.setBrush(brush());
    painter.translate(pixmapWidth / 2.0, pixmapHeight / 2.0);
    drawTankShape(&painter);

    return pixmap;
}

TechnicsShape::ShapeType TankShape::shapeType() const
{
    return m_tankType;
}

void TankShape::setRect(const QRectF &rect)
{
    if (m_tankRect == rect)
        return;

    prepareGeometryChange();
    m_tankRect.setRect(rect.topLeft().x(), rect.topLeft().y(), rect.width(), rect.height());
    if (m_tankText != nullptr)
        m_tankText->setPos(m_tankRect.right(), m_tankRect.bottom() - m_tankRect.width() / 6);

    update();
}

QRectF TankShape::rect() const
{
    return m_tankRect;
}

void TankShape::setHeight(const qreal &height)
{
    if (m_tankRect.height() == height)
        return;

    qreal oldHeight{m_tankRect.height()};
    prepareGeometryChange();
    m_tankRect.setHeight(height);
    qreal dy{(m_tankRect.height() - oldHeight) / 2};
    m_tankRect.moveTo(QPointF(m_tankRect.x(), m_tankRect.y() - dy));
    update();
}

qreal TankShape::height() const
{
    return m_tankRect.height();
}

void TankShape::setText(const QString &text)
{
    if (m_tankText == nullptr) {
        m_tankText = new QGraphicsTextItem(this);
        m_tankText->setTextInteractionFlags(Qt::TextEditorInteraction);
        m_tankText->setRotation(-90);
    }
    m_tankText->setPlainText(text);
    m_showText = true;
}

QString TankShape::text() const
{
    if (m_tankText == nullptr)
        return "";

    return m_tankText->toPlainText();
}

void TankShape::mousePressEvent(QGraphicsSceneMouseEvent *mouseEvent)
{
    if (mouseEvent->buttons() == Qt::RightButton) {
        createAction();
        addActions(m_tankActionList);
        QAction menuAction{menu()->exec(mouseEvent->screenPos())};
        QString menuActionText;
        if (menuAction.parent()) {
            menuActionText = menuAction.parent()->objectName();
        }
        if ((menuActionText != "actionDeleteItem") && (menuActionText != "actionCut")) {
            removeActions(m_tankActionList);
            m_tankActionList.clear();
        }
    } else {
        AbstractShape::mousePressEvent(mouseEvent);
    }
}

void TankShape::createAction()
{
    QString addText{m_showText ? QObject::tr("Hide text") : QObject::tr("Show text")};
    m_addTextAction.reset(new QAction(addText));
    m_addTextAction->setToolTip(QObject::tr("Show or hide text"));
    QObject::connect(m_addTextAction.get(), &QAction::triggered
                     , [this](){m_showText ? textShow(false) : textShow(true);});
    m_tankActionList.append(m_addTextAction.get());
}

void TankShape::textShow(bool showText)
{
    if (showText) {
        if (m_tankText == nullptr) {
            m_tankText=new QGraphicsTextItem(this);
            m_tankText->setPlainText("Танк-");
            m_tankText->setTextInteractionFlags(Qt::TextEditorInteraction);
            m_tankText->setRotation(-90);
        }
        m_tankText->show();
        m_showText = true;
    } else {
        m_tankText->hide();
        m_showText = false;
    }
}

void TankShape::drawTankShape(QPainter *painter)
{
    painter->drawPolygon(tankPolygon(rect()));

    if (m_showText)
        m_tankText->setPos(m_tankRect.right(), m_tankRect.bottom());
}

QPolygonF TankShape::tankPolygon(const QRectF &rect) const
{
    QPointF top{rect.center().x(), rect.top()}; // 0.0, -37.5
    QPointF right{rect.right(), rect.center().y()}; // 18.0, 0.0
    QPointF left{rect.left(), rect.center().y()}; // -18.0, 0.0
    QPointF bottom{rect.center().x(), rect.bottom()}; // 0.0, 37.5

    QPolygonF tankPolygon;
    tankPolygon << bottom << left << top << right;

    return tankPolygon;
}

GdzsShape::GdzsShape(QGraphicsItem *parent)
    : TechnicsShape(parent)
    , m_gdzsType{GDZS}
    , m_gdzsRect{-15.0, -37.5, 30.0, 75.0}
    , m_gdzsText{nullptr}
    , m_showText{false}
{
    setFlag(ItemSendsGeometryChanges, true);
    setAcceptHoverEvents(true);
    setPen(QPen(Qt::red, 1));
    setBrush(QBrush(Qt::white));
}

void GdzsShape::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(widget);

    painter->setRenderHint(QPainter::Antialiasing);
    painter->setRenderHint(QPainter::SmoothPixmapTransform);
    painter->setPen(pen());
    painter->setBrush(brush());

    drawGdzsShape(painter);

    if (option->state & QStyle::State_Selected)
        highlightSelected(painter, option);
}

QRectF GdzsShape::boundingRect() const
{
    QRectF boundingRect{m_gdzsRect};
    qreal halfpw{pen().style() == Qt::NoPen ? qreal(0.0) : pen().widthF() / 2};
    if (halfpw > 0.0)
        boundingRect.adjust(-halfpw, -halfpw, halfpw, halfpw);

    return boundingRect;
}

QPainterPath GdzsShape::shape() const
{
    QPainterPath path;
    path.addPolygon(basePolygon(rect()));

    return shapeFromPath(path);
}

QPixmap GdzsShape::image()
{
    qreal pixmapWidth{boundingRect().width()};
    qreal pixmapHeight{boundingRect().height()};
    QPixmap pixmap(pixmapWidth, pixmapHeight);
    pixmap.fill(Qt::transparent);

    QPainter painter(&pixmap);
    painter.setPen(pen());
    painter.setBrush(brush());
    painter.translate(pixmapWidth / 2.0, pixmapHeight / 2.0);
    drawGdzsShape(&painter);

    return pixmap;
}

TechnicsShape::ShapeType GdzsShape::shapeType() const
{
    return m_gdzsType;
}

void GdzsShape::setRect(const QRectF &rect)
{
    if (m_gdzsRect == rect)
        return;

    prepareGeometryChange();
    m_gdzsRect.setRect(rect.topLeft().x(), rect.topLeft().y(), rect.width(), rect.height());
    if (m_gdzsText != nullptr)
        m_gdzsText->setPos(m_gdzsRect.right(), m_gdzsRect.bottom() - m_gdzsRect.width() / 6);

    update();
}

QRectF GdzsShape::rect() const
{
    return m_gdzsRect;
}

void GdzsShape::setHeight(const qreal &height)
{
    if (m_gdzsRect.height() == height)
        return;

    qreal oldHeight{m_gdzsRect.height()};
    prepareGeometryChange();
    m_gdzsRect.setHeight(height);
    qreal dy{(m_gdzsRect.height() - oldHeight) / 2};
    m_gdzsRect.moveTo(QPointF(m_gdzsRect.x(), m_gdzsRect.y() - dy));
    update();
}

qreal GdzsShape::height() const
{
    return m_gdzsRect.height();
}

void GdzsShape::setText(const QString &text)
{
    if (m_gdzsText == nullptr) {
        m_gdzsText = new QGraphicsTextItem(this);
        m_gdzsText->setTextInteractionFlags(Qt::TextEditorInteraction);
        m_gdzsText->setRotation(-90);
    }
    m_gdzsText->setPlainText(text);
    m_showText = true;
}

QString GdzsShape::text() const
{
    if (m_gdzsText == nullptr)
        return "";

    return m_gdzsText->toPlainText();
}

void GdzsShape::mousePressEvent(QGraphicsSceneMouseEvent *mouseEvent)
{
    if (mouseEvent->buttons() == Qt::RightButton) {
        createAction();
        addActions(m_gdzsActionList);
        QAction menuAction{menu()->exec(mouseEvent->screenPos())};
        QString menuActionText;
        if (menuAction.parent()) {
            menuActionText = menuAction.parent()->objectName();
        }
        if ((menuActionText != "actionDeleteItem") && (menuActionText != "actionCut")) {
            removeActions(m_gdzsActionList);
            m_gdzsActionList.clear();
        }
    } else {
        AbstractShape::mousePressEvent(mouseEvent);
    }
}

void GdzsShape::createAction()
{
    QString addText{m_showText ? QObject::tr("Hide text") : QObject::tr("Show text")};
    m_addTextAction.reset(new QAction(addText));
    m_addTextAction->setToolTip(QObject::tr("Show or hide text"));
    QObject::connect(m_addTextAction.get(), &QAction::triggered
                     , [this](){m_showText ? textShow(false) : textShow(true);});
    m_gdzsActionList.append(m_addTextAction.get());
}

void GdzsShape::textShow(bool showText)
{
    if (showText) {
        if (m_gdzsText == nullptr) {
            m_gdzsText=new QGraphicsTextItem(this);
            m_gdzsText->setPlainText("ГДЗ-");
            m_gdzsText->setTextInteractionFlags(Qt::TextEditorInteraction);
            m_gdzsText->setRotation(-90);
        }
        m_gdzsText->show();
        m_showText = true;
    } else {
        m_gdzsText->hide();
        m_showText = false;
    }
}

void GdzsShape::drawGdzsShape(QPainter *painter)
{
    painter->drawPolygon(basePolygon(rect()));
    painter->translate(m_gdzsRect.center());
    painter->rotate(270);
    painter->translate(-m_gdzsRect.center());
    QTextOption textOption{Qt::AlignCenter};
    painter->drawText(m_gdzsRect, "ГДЗ", textOption);
    painter->translate(m_gdzsRect.center());
    painter->rotate(-270);
    painter->translate(-m_gdzsRect.center());

    if (m_showText)
        m_gdzsText->setPos(m_gdzsRect.right(), m_gdzsRect.bottom());
}

WaterproofShape::WaterproofShape(QGraphicsItem *parent)
    : TechnicsShape(parent)
    , m_waterproofType{Waterproof}
    , m_waterproofRect{-15.0, -37.5, 30.0, 75.0}
    , m_waterproofText{nullptr}
    , m_showText{false}
{
    setFlag(ItemSendsGeometryChanges, true);
    setAcceptHoverEvents(true);
    setPen(QPen(Qt::red, 1));
    setBrush(QBrush(Qt::white));
}

void WaterproofShape::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(widget);

    painter->setRenderHint(QPainter::Antialiasing);
    painter->setRenderHint(QPainter::SmoothPixmapTransform);
    painter->setPen(pen());
    painter->setBrush(brush());

    drawWaterproofShape(painter);

    if (option->state & QStyle::State_Selected)
        highlightSelected(painter, option);
}

QRectF WaterproofShape::boundingRect() const
{
    QRectF boundingRect{m_waterproofRect};
    qreal halfpw{pen().style() == Qt::NoPen ? qreal(0.0) : pen().widthF() / 2};
    if (halfpw > 0.0)
        boundingRect.adjust(-halfpw, -halfpw, halfpw, halfpw);

    return boundingRect;
}

QPainterPath WaterproofShape::shape() const
{
    QPainterPath path;
    path.addPolygon(basePolygon(rect()));

    return shapeFromPath(path);
}

QPixmap WaterproofShape::image()
{
    qreal pixmapWidth{boundingRect().width()};
    qreal pixmapHeight{boundingRect().height()};
    QPixmap pixmap(pixmapWidth, pixmapHeight);
    pixmap.fill(Qt::transparent);

    QPainter painter(&pixmap);
    painter.setPen(pen());
    painter.setBrush(brush());
    painter.translate(pixmapWidth / 2.0, pixmapHeight / 2.0);
    drawWaterproofShape(&painter);

    return pixmap;
}

TechnicsShape::ShapeType WaterproofShape::shapeType() const
{
    return m_waterproofType;
}

void WaterproofShape::setRect(const QRectF &rect)
{
    if (m_waterproofRect == rect)
        return;

    prepareGeometryChange();
    m_waterproofRect.setRect(rect.topLeft().x(), rect.topLeft().y(), rect.width(), rect.height());
    if (m_waterproofText != nullptr)
        m_waterproofText->setPos(m_waterproofRect.right(), m_waterproofRect.bottom() - m_waterproofRect.width() / 6);

    update();
}

QRectF WaterproofShape::rect() const
{
    return m_waterproofRect;
}

void WaterproofShape::setHeight(const qreal &height)
{
    if (m_waterproofRect.height() == height)
        return;

    qreal oldHeight{m_waterproofRect.height()};
    prepareGeometryChange();
    m_waterproofRect.setHeight(height);
    qreal dy{(m_waterproofRect.height() - oldHeight) / 2};
    m_waterproofRect.moveTo(QPointF(m_waterproofRect.x(), m_waterproofRect.y() - dy));
    update();
}

qreal WaterproofShape::height() const
{
    return m_waterproofRect.height();
}

void WaterproofShape::setText(const QString &text)
{
    if (m_waterproofText == nullptr) {
        m_waterproofText = new QGraphicsTextItem(this);
        m_waterproofText->setTextInteractionFlags(Qt::TextEditorInteraction);
        m_waterproofText->setRotation(-90);
    }
    m_waterproofText->setPlainText(text);
    m_showText = true;
}

QString WaterproofShape::text() const
{
    if (m_waterproofText == nullptr)
        return "";

    return m_waterproofText->toPlainText();
}

void WaterproofShape::mousePressEvent(QGraphicsSceneMouseEvent *mouseEvent)
{
    if (mouseEvent->buttons() == Qt::RightButton) {
        createAction();
        addActions(m_waterproofActionList);
        QAction menuAction{menu()->exec(mouseEvent->screenPos())};
        QString menuActionText;
        if (menuAction.parent()) {
            menuActionText = menuAction.parent()->objectName();
        }
        if ((menuActionText != "actionDeleteItem") && (menuActionText != "actionCut")) {
            removeActions(m_waterproofActionList);
            m_waterproofActionList.clear();
        }
    } else {
        AbstractShape::mousePressEvent(mouseEvent);
    }
}

void WaterproofShape::createAction()
{
    QString addText{m_showText ? QObject::tr("Hide text") : QObject::tr("Show text")};
    m_addTextAction.reset(new QAction(addText));
    m_addTextAction->setToolTip(QObject::tr("Show or hide text"));
    QObject::connect(m_addTextAction.get(), &QAction::triggered
                     , [this](){m_showText ? textShow(false) : textShow(true);});
    m_waterproofActionList.append(m_addTextAction.get());
}

void WaterproofShape::textShow(bool showText)
{
    if (showText) {
        if (m_waterproofText == nullptr) {
            m_waterproofText=new QGraphicsTextItem(this);
            m_waterproofText->setPlainText("АВЗ-");
            m_waterproofText->setTextInteractionFlags(Qt::TextEditorInteraction);
            m_waterproofText->setRotation(-90);
        }
        m_waterproofText->show();
        m_showText = true;
    } else {
        m_waterproofText->hide();
        m_showText = false;
    }
}

void WaterproofShape::drawWaterproofShape(QPainter *painter)
{
    painter->drawPolygon(basePolygon(rect()));
    painter->translate(m_waterproofRect.center());
    painter->rotate(270);
    painter->translate(-m_waterproofRect.center());
    QTextOption textOption{Qt::AlignCenter};
    painter->drawText(m_waterproofRect, "ВЗ", textOption);
    painter->translate(m_waterproofRect.center());
    painter->rotate(-270);
    painter->translate(-m_waterproofRect.center());

    if (m_showText)
        m_waterproofText->setPos(m_waterproofRect.right(), m_waterproofRect.bottom());
}

LaboratoryShape::LaboratoryShape(QGraphicsItem *parent)
    : TechnicsShape(parent)
    , m_laboratoryType{Laboratory}
    , m_laboratoryRect{-15.0, -37.5, 30.0, 75.0}
    , m_laboratoryText{nullptr}
    , m_showText{false}
{
    setFlag(ItemSendsGeometryChanges, true);
    setAcceptHoverEvents(true);
    setPen(QPen(Qt::red, 1));
    setBrush(QBrush(Qt::white));
}

void LaboratoryShape::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(widget);

    painter->setRenderHint(QPainter::Antialiasing);
    painter->setRenderHint(QPainter::SmoothPixmapTransform);
    painter->setPen(pen());
    painter->setBrush(brush());

    drawLaboratoryShape(painter);

    if (option->state & QStyle::State_Selected)
        highlightSelected(painter, option);
}

QRectF LaboratoryShape::boundingRect() const
{
    QRectF boundingRect{m_laboratoryRect};
    qreal halfpw{pen().style() == Qt::NoPen ? qreal(0.0) : pen().widthF() / 2};
    if (halfpw > 0.0)
        boundingRect.adjust(-halfpw, -halfpw, halfpw, halfpw);

    return boundingRect;
}

QPainterPath LaboratoryShape::shape() const
{
    QPainterPath path;
    path.addPolygon(basePolygon(rect()));

    return shapeFromPath(path);
}

QPixmap LaboratoryShape::image()
{
    qreal pixmapWidth{boundingRect().width()};
    qreal pixmapHeight{boundingRect().height()};
    QPixmap pixmap(pixmapWidth, pixmapHeight);
    pixmap.fill(Qt::transparent);

    QPainter painter(&pixmap);
    painter.setPen(pen());
    painter.setBrush(brush());
    painter.translate(pixmapWidth / 2.0, pixmapHeight / 2.0);
    drawLaboratoryShape(&painter);

    return pixmap;
}

TechnicsShape::ShapeType LaboratoryShape::shapeType() const
{
    return m_laboratoryType;
}

void LaboratoryShape::setRect(const QRectF &rect)
{
    if (m_laboratoryRect == rect)
        return;

    prepareGeometryChange();
    m_laboratoryRect.setRect(rect.topLeft().x(), rect.topLeft().y(), rect.width(), rect.height());
    if (m_laboratoryText != nullptr)
        m_laboratoryText->setPos(m_laboratoryRect.right(), m_laboratoryRect.bottom() - m_laboratoryRect.width() / 6);

    update();
}

QRectF LaboratoryShape::rect() const
{
    return m_laboratoryRect;
}

void LaboratoryShape::setHeight(const qreal &height)
{
    if (m_laboratoryRect.height() == height)
        return;

    qreal oldHeight{m_laboratoryRect.height()};
    prepareGeometryChange();
    m_laboratoryRect.setHeight(height);
    qreal dy{(m_laboratoryRect.height() - oldHeight) / 2};
    m_laboratoryRect.moveTo(QPointF(m_laboratoryRect.x(), m_laboratoryRect.y() - dy));
    update();
}

qreal LaboratoryShape::height() const
{
    return m_laboratoryRect.height();
}

void LaboratoryShape::setText(const QString &text)
{
    if (m_laboratoryText == nullptr) {
        m_laboratoryText = new QGraphicsTextItem(this);
        m_laboratoryText->setTextInteractionFlags(Qt::TextEditorInteraction);
        m_laboratoryText->setRotation(-90);
    }
    m_laboratoryText->setPlainText(text);
    m_showText = true;
}

QString LaboratoryShape::text() const
{
    if (m_laboratoryText == nullptr)
        return "";

    return m_laboratoryText->toPlainText();
}

void LaboratoryShape::mousePressEvent(QGraphicsSceneMouseEvent *mouseEvent)
{
    if (mouseEvent->buttons() == Qt::RightButton) {
        createAction();
        addActions(m_laboratoryActionList);
        QAction menuAction{menu()->exec(mouseEvent->screenPos())};
        QString menuActionText;
        if (menuAction.parent()) {
            menuActionText = menuAction.parent()->objectName();
        }
        if ((menuActionText != "actionDeleteItem") && (menuActionText != "actionCut")) {
            removeActions(m_laboratoryActionList);
            m_laboratoryActionList.clear();
        }
    } else {
        AbstractShape::mousePressEvent(mouseEvent);
    }
}

void LaboratoryShape::createAction()
{
    QString addText{m_showText ? QObject::tr("Hide text") : QObject::tr("Show text")};
    m_addTextAction.reset(new QAction(addText));
    m_addTextAction->setToolTip(QObject::tr("Show or hide text"));
    QObject::connect(m_addTextAction.get(), &QAction::triggered
                     , [this](){m_showText ? textShow(false) : textShow(true);});
    m_laboratoryActionList.append(m_addTextAction.get());
}

void LaboratoryShape::textShow(bool showText)
{
    if (showText) {
        if (m_laboratoryText == nullptr) {
            m_laboratoryText=new QGraphicsTextItem(this);
            m_laboratoryText->setPlainText("АЛП-");
            m_laboratoryText->setTextInteractionFlags(Qt::TextEditorInteraction);
            m_laboratoryText->setRotation(-90);
        }
        m_laboratoryText->show();
        m_showText = true;
    } else {
        m_laboratoryText->hide();
        m_showText = false;
    }
}

void LaboratoryShape::drawLaboratoryShape(QPainter *painter)
{
    painter->drawPolygon(basePolygon(rect()));
    painter->translate(m_laboratoryRect.center());
    painter->rotate(270);
    painter->translate(-m_laboratoryRect.center());
    QTextOption textOption{Qt::AlignCenter};
    painter->drawText(m_laboratoryRect, "ЛБ", textOption);
    painter->translate(m_laboratoryRect.center());
    painter->rotate(-270);
    painter->translate(-m_laboratoryRect.center());

    if (m_showText)
        m_laboratoryText->setPos(m_laboratoryRect.right(), m_laboratoryRect.bottom());
}

StaffCarShape::StaffCarShape(QGraphicsItem *parent)
    : TechnicsShape(parent)
    , m_staffCarType{StaffCar}
    , m_staffCarRect{-15.0, -37.5, 30.0, 75.0}
    , m_staffCarText{nullptr}
    , m_showText{false}
{
    setFlag(ItemSendsGeometryChanges, true);
    setAcceptHoverEvents(true);
    setPen(QPen(Qt::red, 1));
    setBrush(QBrush(Qt::white));
}

void StaffCarShape::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(widget);

    painter->setRenderHint(QPainter::Antialiasing);
    painter->setRenderHint(QPainter::SmoothPixmapTransform);
    painter->setPen(pen());
    painter->setBrush(brush());

    drawStaffCarShape(painter);

    if (option->state & QStyle::State_Selected)
        highlightSelected(painter, option);
}

QRectF StaffCarShape::boundingRect() const
{
    QRectF boundingRect{m_staffCarRect};
    qreal halfpw{pen().style() == Qt::NoPen ? qreal(0.0) : pen().widthF() / 2};
    if (halfpw > 0.0)
        boundingRect.adjust(-halfpw, -halfpw, halfpw, halfpw);

    return boundingRect;
}

QPainterPath StaffCarShape::shape() const
{
    QPainterPath path;
    path.addPolygon(basePolygon(rect()));

    return shapeFromPath(path);
}

QPixmap StaffCarShape::image()
{
    qreal pixmapWidth{boundingRect().width()};
    qreal pixmapHeight{boundingRect().height()};
    QPixmap pixmap(pixmapWidth, pixmapHeight);
    pixmap.fill(Qt::transparent);

    QPainter painter(&pixmap);
    painter.setPen(pen());
    painter.setBrush(brush());
    painter.translate(pixmapWidth / 2.0, pixmapHeight / 2.0);
    drawStaffCarShape(&painter);

    return pixmap;
}

TechnicsShape::ShapeType StaffCarShape::shapeType() const
{
    return m_staffCarType;
}

void StaffCarShape::setRect(const QRectF &rect)
{
    if (m_staffCarRect == rect)
        return;

    prepareGeometryChange();
    m_staffCarRect.setRect(rect.topLeft().x(), rect.topLeft().y(), rect.width(), rect.height());
    if (m_staffCarText != nullptr)
        m_staffCarText->setPos(m_staffCarRect.right(), m_staffCarRect.bottom() - m_staffCarRect.width() / 6);

    update();
}

QRectF StaffCarShape::rect() const
{
    return m_staffCarRect;
}

void StaffCarShape::setHeight(const qreal &height)
{
    if (m_staffCarRect.height() == height)
        return;

    qreal oldHeight{m_staffCarRect.height()};
    prepareGeometryChange();
    m_staffCarRect.setHeight(height);
    qreal dy{(m_staffCarRect.height() - oldHeight) / 2};
    m_staffCarRect.moveTo(QPointF(m_staffCarRect.x(), m_staffCarRect.y() - dy));
    update();
}

qreal StaffCarShape::height() const
{
    return m_staffCarRect.height();
}

void StaffCarShape::setText(const QString &text)
{
    if (m_staffCarText == nullptr) {
        m_staffCarText = new QGraphicsTextItem(this);
        m_staffCarText->setTextInteractionFlags(Qt::TextEditorInteraction);
        m_staffCarText->setRotation(-90);
    }
    m_staffCarText->setPlainText(text);
    m_showText = true;
}

QString StaffCarShape::text() const
{
    if (m_staffCarText == nullptr)
        return "";

    return m_staffCarText->toPlainText();
}

void StaffCarShape::mousePressEvent(QGraphicsSceneMouseEvent *mouseEvent)
{
    if (mouseEvent->buttons() == Qt::RightButton) {
        createAction();
        addActions(m_staffCarActionList);
        QAction menuAction{menu()->exec(mouseEvent->screenPos())};
        QString menuActionText;
        if (menuAction.parent()) {
            menuActionText = menuAction.parent()->objectName();
        }
        if ((menuActionText != "actionDeleteItem") && (menuActionText != "actionCut")) {
            removeActions(m_staffCarActionList);
            m_staffCarActionList.clear();
        }
    } else {
        AbstractShape::mousePressEvent(mouseEvent);
    }
}

void StaffCarShape::createAction()
{
    QString addText{m_showText ? QObject::tr("Hide text") : QObject::tr("Show text")};
    m_addTextAction.reset(new QAction(addText));
    m_addTextAction->setToolTip(QObject::tr("Show or hide text"));
    QObject::connect(m_addTextAction.get(), &QAction::triggered
                     , [this](){m_showText ? textShow(false) : textShow(true);});
    m_staffCarActionList.append(m_addTextAction.get());
}

void StaffCarShape::textShow(bool showText)
{
    if (showText) {
        if (m_staffCarText == nullptr) {
            m_staffCarText=new QGraphicsTextItem(this);
            m_staffCarText->setPlainText("АШ-");
            m_staffCarText->setTextInteractionFlags(Qt::TextEditorInteraction);
            m_staffCarText->setRotation(-90);
        }
        m_staffCarText->show();
        m_showText = true;
    } else {
        m_staffCarText->hide();
        m_showText = false;
    }
}

void StaffCarShape::drawStaffCarShape(QPainter *painter)
{
    painter->drawPolygon(basePolygon(rect()));
    painter->translate(m_staffCarRect.center());
    painter->rotate(270);
    painter->translate(-m_staffCarRect.center());
    QTextOption textOption{Qt::AlignCenter};
    painter->drawText(m_staffCarRect, "Ш", textOption);
    painter->translate(m_staffCarRect.center());
    painter->rotate(-270);
    painter->translate(-m_staffCarRect.center());

    if (m_showText)
        m_staffCarText->setPos(m_staffCarRect.right(), m_staffCarRect.bottom());
}

TrailerShape::TrailerShape(QGraphicsItem *parent)
    : TechnicsShape(parent)
    , m_trailerType{Trailer}
    , m_trailerRect{-20.0, -31.0, 40.0, 62.0}
    , m_trailerText{nullptr}
    , m_showText{false}
{
    setFlag(ItemSendsGeometryChanges, true);
    setAcceptHoverEvents(true);
    setPen(QPen(Qt::red, 1));
    setBrush(QBrush(Qt::white));
}

void TrailerShape::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(widget);

    painter->setRenderHint(QPainter::Antialiasing);
    painter->setRenderHint(QPainter::SmoothPixmapTransform);
    painter->setPen(pen());
    painter->setBrush(brush());

    drawTrailerShape(painter);

    if (option->state & QStyle::State_Selected)
        highlightSelected(painter, option);
}

QRectF TrailerShape::boundingRect() const
{
    QRectF boundingRect{m_trailerRect};
    qreal halfpw{pen().style() == Qt::NoPen ? qreal(0.0) : pen().widthF() / 2};
    if (halfpw > 0.0)
        boundingRect.adjust(-halfpw, -halfpw, halfpw, halfpw);

    return boundingRect;
}

QPainterPath TrailerShape::shape() const
{
    return shapeFromPath(trailerPath());
}

QPixmap TrailerShape::image()
{
    qreal pixmapWidth{boundingRect().width()};
    qreal pixmapHeight{boundingRect().height()};
    QPixmap pixmap(pixmapWidth, pixmapHeight);
    pixmap.fill(Qt::transparent);

    QPainter painter(&pixmap);
    painter.setPen(pen());
    painter.setBrush(brush());
    painter.translate(pixmapWidth / 2.0, pixmapHeight / 2.0);
    drawTrailerShape(&painter);

    return pixmap;
}

TechnicsShape::ShapeType TrailerShape::shapeType() const
{
    return m_trailerType;
}

void TrailerShape::setRect(const QRectF &rect)
{
    if (m_trailerRect == rect)
        return;

    prepareGeometryChange();
    m_trailerRect.setRect(rect.topLeft().x(), rect.topLeft().y(), rect.width(), rect.height());
    if (m_trailerText != nullptr)
        m_trailerText->setPos(m_trailerRect.right(), m_trailerRect.bottom() - m_trailerRect.width() / 6);

    update();
}

QRectF TrailerShape::rect() const
{
    return m_trailerRect;
}

void TrailerShape::setHeight(const qreal &height)
{
    if (m_trailerRect.height() == height)
        return;

    qreal oldHeight{m_trailerRect.height()};
    prepareGeometryChange();
    m_trailerRect.setHeight(height);
    qreal dy{(m_trailerRect.height() - oldHeight) / 2};
    m_trailerRect.moveTo(QPointF(m_trailerRect.x(), m_trailerRect.y() - dy));
    update();
}

qreal TrailerShape::height() const
{
    return m_trailerRect.height();
}

void TrailerShape::setText(const QString &text)
{
    if (m_trailerText == nullptr) {
        m_trailerText = new QGraphicsTextItem(this);
        m_trailerText->setTextInteractionFlags(Qt::TextEditorInteraction);
        m_trailerText->setRotation(-90);
    }
    m_trailerText->setPlainText(text);
    m_showText = true;
}

QString TrailerShape::text() const
{
    if (m_trailerText == nullptr)
        return "";

    return m_trailerText->toPlainText();
}

void TrailerShape::mousePressEvent(QGraphicsSceneMouseEvent *mouseEvent)
{
    if (mouseEvent->buttons() == Qt::RightButton) {
        createAction();
        addActions(m_trailerActionList);
        QAction menuAction{menu()->exec(mouseEvent->screenPos())};
        QString menuActionText;
        if (menuAction.parent()) {
            menuActionText = menuAction.parent()->objectName();
        }
        if ((menuActionText != "actionDeleteItem") && (menuActionText != "actionCut")) {
            removeActions(m_trailerActionList);
            m_trailerActionList.clear();
        }
    } else {
        AbstractShape::mousePressEvent(mouseEvent);
    }
}

void TrailerShape::createAction()
{
    QString addText{m_showText ? QObject::tr("Hide text") : QObject::tr("Show text")};
    m_addTextAction.reset(new QAction(addText));
    m_addTextAction->setToolTip(QObject::tr("Show or hide text"));
    QObject::connect(m_addTextAction.get(), &QAction::triggered
                     , [this](){m_showText ? textShow(false) : textShow(true);});
    m_trailerActionList.append(m_addTextAction.get());
}

void TrailerShape::textShow(bool showText)
{
    if (showText) {
        if (m_trailerText == nullptr) {
            m_trailerText=new QGraphicsTextItem(this);
            m_trailerText->setPlainText("Прицеп-");
            m_trailerText->setTextInteractionFlags(Qt::TextEditorInteraction);
            m_trailerText->setRotation(-90);
        }
        m_trailerText->show();
        m_showText = true;
    } else {
        m_trailerText->hide();
        m_showText = false;
    }
}

void TrailerShape::drawTrailerShape(QPainter *painter)
{
    painter->drawPath(trailerPath());

    if (m_showText)
        m_trailerText->setPos(m_trailerRect.right(), m_trailerRect.bottom());
}

QPainterPath TrailerShape::trailerPath() const
{
    QPainterPath curentPath;
    qreal fifteenthHeight{height() / 15.5}; //4.0
    qreal eighthWidth{m_trailerRect.width() / 8}; //5.0
    qreal wheelTop{m_trailerRect. bottom() - (fifteenthHeight * 2)}; // 23.0
    qreal bodyTop{m_trailerRect.top() + (fifteenthHeight * 3.0)}; //-19.0
    qreal bodyBotoom{m_trailerRect.bottom() - fifteenthHeight}; //27.0
    qreal bodyLeft{m_trailerRect.left() + eighthWidth}; //-15.0
    qreal bodyRight{m_trailerRect.right() - eighthWidth}; //15.0
    //left wheel
    curentPath.moveTo(m_trailerRect.left(), m_trailerRect.bottom()); //-20.0, 31.0
    curentPath.lineTo(m_trailerRect.left(), wheelTop); //-20.0, 23.0
    //body bottom
    curentPath.moveTo(m_trailerRect.left(), bodyBotoom); //-20.0, 27.0
    curentPath.lineTo(m_trailerRect.right(), bodyBotoom); //20.o, 27.0
    //right wheel
    curentPath.moveTo(m_trailerRect.right(), m_trailerRect.bottom()); //20.0, 31.0
    curentPath.lineTo(m_trailerRect.right(), wheelTop); //20.0, 23.0
    //body left
    curentPath.moveTo(bodyLeft, bodyBotoom); //-15.0, 27.0
    curentPath.lineTo(bodyLeft, bodyTop); //-15.0, -19.0
    //body top
    curentPath.lineTo(bodyRight, bodyTop); //15.0, -19.0
    //body right
    curentPath.lineTo(bodyRight, bodyBotoom); //15.0, 27.0
    //driver
    curentPath.moveTo(m_trailerRect.center().x(), bodyTop); //0.0, -19.0
    curentPath.lineTo(m_trailerRect.center().x(), m_trailerRect.top()); //0.0, -31.0

    return curentPath;
}

ShipShape::ShipShape(QGraphicsItem *parent)
    : TechnicsShape(parent)
    , m_shipType{Ship}
    , m_shipRect{-15.0, -37.5, 30.0, 75.0}
    , m_shipText{nullptr}
    , m_showText{false}
{
    setFlag(ItemSendsGeometryChanges, true);
    setAcceptHoverEvents(true);
    setPen(QPen(Qt::red, 1));
    setBrush(QBrush(Qt::white));
}

void ShipShape::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(widget);

    painter->setRenderHint(QPainter::Antialiasing);
    painter->setRenderHint(QPainter::SmoothPixmapTransform);
    painter->setPen(pen());
    painter->setBrush(brush());

    drawShipShape(painter);

    if (option->state & QStyle::State_Selected)
        highlightSelected(painter, option);
}

QRectF ShipShape::boundingRect() const
{
    QRectF boundingRect{m_shipRect};
    qreal halfpw{pen().style() == Qt::NoPen ? qreal(0.0) : pen().widthF() / 2};
    if (halfpw > 0.0)
        boundingRect.adjust(-halfpw, -halfpw, halfpw, halfpw);

    return boundingRect;
}

QPainterPath ShipShape::shape() const
{
    QPainterPath path;
    path.addPolygon(shipPolygon(rect()));

    return shapeFromPath(path);
}

QPixmap ShipShape::image()
{
    qreal pixmapWidth{boundingRect().width()};
    qreal pixmapHeight{boundingRect().height()};
    QPixmap pixmap(pixmapWidth, pixmapHeight);
    pixmap.fill(Qt::transparent);

    QPainter painter(&pixmap);
    painter.setPen(pen());
    painter.setBrush(brush());
    painter.translate(pixmapWidth / 2.0, pixmapHeight / 2.0);
    drawShipShape(&painter);

    return pixmap;
}

TechnicsShape::ShapeType ShipShape::shapeType() const
{
    return m_shipType;
}

void ShipShape::setRect(const QRectF &rect)
{
    if (m_shipRect == rect)
        return;

    prepareGeometryChange();
    m_shipRect.setRect(rect.topLeft().x(), rect.topLeft().y(), rect.width(), rect.height());
    if (m_shipText != nullptr)
        m_shipText->setPos(m_shipRect.right(), m_shipRect.bottom() - m_shipRect.width() / 6);

    update();
}

QRectF ShipShape::rect() const
{
    return m_shipRect;
}

void ShipShape::setHeight(const qreal &height)
{
    if (m_shipRect.height() == height)
        return;

    qreal oldHeight{m_shipRect.height()};
    prepareGeometryChange();
    m_shipRect.setHeight(height);
    qreal dy{(m_shipRect.height() - oldHeight) / 2};
    m_shipRect.moveTo(QPointF(m_shipRect.x(), m_shipRect.y() - dy));
    update();
}

qreal ShipShape::height() const
{
    return m_shipRect.height();
}

void ShipShape::setText(const QString &text)
{
    if (m_shipText == nullptr) {
        m_shipText = new QGraphicsTextItem(this);
        m_shipText->setTextInteractionFlags(Qt::TextEditorInteraction);
        m_shipText->setRotation(-90);
    }
    m_shipText->setPlainText(text);
    m_showText = true;
}

QString ShipShape::text() const
{
    if (m_shipText == nullptr)
        return "";

    return m_shipText->toPlainText();
}

void ShipShape::mousePressEvent(QGraphicsSceneMouseEvent *mouseEvent)
{
    if (mouseEvent->buttons() == Qt::RightButton) {
        createAction();
        addActions(m_shipActionList);
        QAction menuAction{menu()->exec(mouseEvent->screenPos())};
        QString menuActionText;
        if (menuAction.parent()) {
            menuActionText = menuAction.parent()->objectName();
        }
        if ((menuActionText != "actionDeleteItem") && (menuActionText != "actionCut")) {
            removeActions(m_shipActionList);
            m_shipActionList.clear();
        }
    } else {
        AbstractShape::mousePressEvent(mouseEvent);
    }
}

void ShipShape::createAction()
{
    QString addText{m_showText ? QObject::tr("Hide text") : QObject::tr("Show text")};
    m_addTextAction.reset(new QAction(addText));
    m_addTextAction->setToolTip(QObject::tr("Show or hide text"));
    QObject::connect(m_addTextAction.get(), &QAction::triggered
                     , [this](){m_showText ? textShow(false) : textShow(true);});
    m_shipActionList.append(m_addTextAction.get());
}

void ShipShape::textShow(bool showText)
{
    if (showText) {
        if (m_shipText == nullptr) {
            m_shipText=new QGraphicsTextItem(this);
            m_shipText->setPlainText("СП-");
            m_shipText->setTextInteractionFlags(Qt::TextEditorInteraction);
            m_shipText->setRotation(-90);
        }
        m_shipText->show();
        m_showText = true;
    } else {
        m_shipText->hide();
        m_showText = false;
    }
}

void ShipShape::drawShipShape(QPainter *painter)
{
    painter->drawPolygon(shipPolygon(rect()));

    painter->translate(m_shipRect.center());
    painter->rotate(270);
    painter->translate(-m_shipRect.center());
    QTextOption textOption{Qt::AlignCenter};
    painter->drawText(m_shipRect, "C", textOption);
    painter->translate(m_shipRect.center());
    painter->rotate(-270);
    painter->translate(-m_shipRect.center());

    if (m_showText)
        m_shipText->setPos(m_shipRect.right(), m_shipRect.bottom());
}

QPolygonF ShipShape::shipPolygon(const QRectF &rect) const
{
    QPointF centerBottom{rect.center().x(), rect.bottom()}; //0.0, 37.5
    qreal fourthHeight{rect.height() / 4}; //18.75
    QPointF leftBottom{rect.left(), rect.bottom() - fourthHeight}; //-15.0, 18.75
    QPointF leftTop{rect.left(), rect.top() + fourthHeight}; // -15.0, -18.75
    QPointF centerTop{rect.center().x(), rect.top()}; //0.0, -37.5
    QPointF rightTop{rect.right(), rect.top() +fourthHeight}; //15.0, -18.75
    QPointF rightBottom{rect.right(), rect.bottom() - fourthHeight}; //15.0, 18.75
    QPolygonF shipPolygon;
    shipPolygon << centerBottom << leftBottom << leftTop << centerTop << rightTop << rightBottom;

    return shipPolygon;
}

BoatShape::BoatShape(QGraphicsItem *parent)
    : TechnicsShape(parent)
    , m_boatType{Boat}
    , m_boatRect{-15.0, -37.5, 30.0, 75.0}
    , m_boatText{nullptr}
    , m_showText{false}
{
    setFlag(ItemSendsGeometryChanges, true);
    setAcceptHoverEvents(true);
    setPen(QPen(Qt::red, 1));
    setBrush(QBrush(Qt::white));
}

void BoatShape::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(widget);

    painter->setRenderHint(QPainter::Antialiasing);
    painter->setRenderHint(QPainter::SmoothPixmapTransform);
    painter->setPen(pen());
    painter->setBrush(brush());

    drawBoatShape(painter);

    if (option->state & QStyle::State_Selected)
        highlightSelected(painter, option);
}

QRectF BoatShape::boundingRect() const
{
    QRectF boundingRect{m_boatRect};
    qreal halfpw{pen().style() == Qt::NoPen ? qreal(0.0) : pen().widthF() / 2};
    if (halfpw > 0.0)
        boundingRect.adjust(-halfpw, -halfpw, halfpw, halfpw);

    return boundingRect;
}

QPainterPath BoatShape::shape() const
{
    QPainterPath path;
    path.addPolygon(boatPolygon(rect()));

    return shapeFromPath(path);
}

QPixmap BoatShape::image()
{
    qreal pixmapWidth{boundingRect().width()};
    qreal pixmapHeight{boundingRect().height()};
    QPixmap pixmap(pixmapWidth, pixmapHeight);
    pixmap.fill(Qt::transparent);

    QPainter painter(&pixmap);
    painter.setPen(pen());
    painter.setBrush(brush());
    painter.translate(pixmapWidth / 2.0, pixmapHeight / 2.0);
    drawBoatShape(&painter);

    return pixmap;
}

TechnicsShape::ShapeType BoatShape::shapeType() const
{
    return m_boatType;
}

void BoatShape::setRect(const QRectF &rect)
{
    if (m_boatRect == rect)
        return;

    prepareGeometryChange();
    m_boatRect.setRect(rect.topLeft().x(), rect.topLeft().y(), rect.width(), rect.height());
    if (m_boatText != nullptr)
        m_boatText->setPos(m_boatRect.right(), m_boatRect.bottom() - m_boatRect.width() / 6);

    update();
}

QRectF BoatShape::rect() const
{
    return m_boatRect;
}

void BoatShape::setHeight(const qreal &height)
{
    if (m_boatRect.height() == height)
        return;

    qreal oldHeight{m_boatRect.height()};
    prepareGeometryChange();
    m_boatRect.setHeight(height);
    qreal dy{(m_boatRect.height() - oldHeight) / 2};
    m_boatRect.moveTo(QPointF(m_boatRect.x(), m_boatRect.y() - dy));
    update();
}

qreal BoatShape::height() const
{
    return m_boatRect.height();
}

void BoatShape::setText(const QString &text)
{
    if (m_boatText == nullptr) {
        m_boatText = new QGraphicsTextItem(this);
        m_boatText->setTextInteractionFlags(Qt::TextEditorInteraction);
        m_boatText->setRotation(-90);
    }
    m_boatText->setPlainText(text);
    m_showText = true;
}

QString BoatShape::text() const
{
    if (m_boatText == nullptr)
        return "";

    return m_boatText->toPlainText();
}

void BoatShape::mousePressEvent(QGraphicsSceneMouseEvent *mouseEvent)
{
    if (mouseEvent->buttons() == Qt::RightButton) {
        createAction();
        addActions(m_boatActionList);
        QAction menuAction{menu()->exec(mouseEvent->screenPos())};
        QString menuActionText;
        if (menuAction.parent()) {
            menuActionText = menuAction.parent()->objectName();
        }
        if ((menuActionText != "actionDeleteItem") && (menuActionText != "actionCut")) {
            removeActions(m_boatActionList);
            m_boatActionList.clear();
        }
    } else {
        AbstractShape::mousePressEvent(mouseEvent);
    }
}

void BoatShape::createAction()
{
    QString addText{m_showText ? QObject::tr("Hide text") : QObject::tr("Show text")};
    m_addTextAction.reset(new QAction(addText));
    m_addTextAction->setToolTip(QObject::tr("Show or hide text"));
    QObject::connect(m_addTextAction.get(), &QAction::triggered
                     , [this](){m_showText ? textShow(false) : textShow(true);});
    m_boatActionList.append(m_addTextAction.get());
}

void BoatShape::textShow(bool showText)
{
    if (showText) {
        if (m_boatText == nullptr) {
            m_boatText=new QGraphicsTextItem(this);
            m_boatText->setPlainText("К-");
            m_boatText->setTextInteractionFlags(Qt::TextEditorInteraction);
            m_boatText->setRotation(-90);
        }
        m_boatText->show();
        m_showText = true;
    } else {
        m_boatText->hide();
        m_showText = false;
    }
}

void BoatShape::drawBoatShape(QPainter *painter)
{
    painter->drawPolygon(boatPolygon(rect()));

    painter->translate(m_boatRect.center());
    painter->rotate(270);
    painter->translate(-m_boatRect.center());
    QTextOption textOption{Qt::AlignCenter};
    painter->drawText(m_boatRect, "К", textOption);
    painter->translate(m_boatRect.center());
    painter->rotate(-270);
    painter->translate(-m_boatRect.center());

    if (m_showText)
        m_boatText->setPos(m_boatRect.right(), m_boatRect.bottom());
}

QPolygonF BoatShape::boatPolygon(const QRectF &rect) const
{
    QPointF centerBottom{rect.center().x(), rect.bottom()}; //0.0, 37.5
    qreal fourthHeight{rect.height() / 4}; //18.75
    QPointF leftBottom{rect.left(), rect.bottom() - fourthHeight}; //-15.0, 18.75
    QPointF leftTop{rect.left(), rect.top() + fourthHeight}; // -15.0, -18.75
    QPointF centerTop{rect.center().x(), rect.top()}; //0.0, -37.5
    QPointF rightTop{rect.right(), rect.top() +fourthHeight}; //15.0, -18.75
    QPointF rightBottom{rect.right(), rect.bottom() - fourthHeight}; //15.0, 18.75
    QPolygonF boatPolygon;
    boatPolygon << centerBottom << leftBottom << leftTop << centerTop << rightTop << rightBottom;

    return boatPolygon;
}

TrainShape::TrainShape(QGraphicsItem *parent)
    : TechnicsShape(parent)
    , m_trainType{Train}
    , m_trainRect{-15.0, -25.0, 30.0, 50.0}
    , m_trainText{nullptr}
    , m_showText{false}
{
    setFlag(ItemSendsGeometryChanges, true);
    setAcceptHoverEvents(true);
    setPen(QPen(Qt::red, 1));
    setBrush(QBrush(Qt::red));
}

void TrainShape::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(widget);

    painter->setRenderHint(QPainter::Antialiasing);
    painter->setRenderHint(QPainter::SmoothPixmapTransform);
    painter->setPen(pen());
    painter->setBrush(brush());

    drawTrainShape(painter);

    if (option->state & QStyle::State_Selected)
        highlightSelected(painter, option);
}

QRectF TrainShape::boundingRect() const
{
    QRectF boundingRect{m_trainRect};
    qreal halfpw{pen().style() == Qt::NoPen ? qreal(0.0) : pen().widthF() / 2};
    if (halfpw > 0.0)
        boundingRect.adjust(-halfpw, -halfpw, halfpw, halfpw);

    return boundingRect;
}

QPainterPath TrainShape::shape() const
{
    QPainterPath path;
    path.addPolygon(trainPolygon(rect()));

    return shapeFromPath(path);
}

QPixmap TrainShape::image()
{
    qreal pixmapWidth{boundingRect().width()};
    qreal pixmapHeight{boundingRect().height()};
    QPixmap pixmap(pixmapWidth, pixmapHeight);
    pixmap.fill(Qt::transparent);

    QPainter painter(&pixmap);
    painter.setPen(pen());
    painter.setBrush(brush());
    painter.translate(pixmapWidth / 2.0, pixmapHeight / 2.0);
    drawTrainShape(&painter);

    return pixmap;
}

TechnicsShape::ShapeType TrainShape::shapeType() const
{
    return m_trainType;
}

void TrainShape::setRect(const QRectF &rect)
{
    if (m_trainRect == rect)
        return;

    prepareGeometryChange();
    m_trainRect.setRect(rect.topLeft().x(), rect.topLeft().y(), rect.width(), rect.height());
    if (m_trainText != nullptr)
        m_trainText->setPos(m_trainRect.right(), m_trainRect.bottom() - m_trainRect.width() / 6);

    update();
}

QRectF TrainShape::rect() const
{
    return m_trainRect;
}

void TrainShape::setHeight(const qreal &height)
{
    if (m_trainRect.height() == height)
        return;

    qreal oldHeight{m_trainRect.height()};
    prepareGeometryChange();
    m_trainRect.setHeight(height);
    qreal dy{(m_trainRect.height() - oldHeight) / 2};
    m_trainRect.moveTo(QPointF(m_trainRect.x(), m_trainRect.y() - dy));
    update();
}

qreal TrainShape::height() const
{
    return m_trainRect.height();
}

void TrainShape::setText(const QString &text)
{
    if (m_trainText == nullptr) {
        m_trainText = new QGraphicsTextItem(this);
        m_trainText->setTextInteractionFlags(Qt::TextEditorInteraction);
        m_trainText->setRotation(-90);
    }
    m_trainText->setPlainText(text);
    m_showText = true;
}

QString TrainShape::text() const
{
    if (m_trainText == nullptr)
        return "";

    return m_trainText->toPlainText();
}

void TrainShape::mousePressEvent(QGraphicsSceneMouseEvent *mouseEvent)
{
    if (mouseEvent->buttons() == Qt::RightButton) {
        createAction();
        addActions(m_trainActionList);
        QAction menuAction{menu()->exec(mouseEvent->screenPos())};
        QString menuActionText;
        if (menuAction.parent()) {
            menuActionText = menuAction.parent()->objectName();
        }
        if ((menuActionText != "actionDeleteItem") && (menuActionText != "actionCut")) {
            removeActions(m_trainActionList);
            m_trainActionList.clear();
        }
    } else {
        AbstractShape::mousePressEvent(mouseEvent);
    }
}

void TrainShape::createAction()
{
    QString addText{m_showText ? QObject::tr("Hide text") : QObject::tr("Show text")};
    m_addTextAction.reset(new QAction(addText));
    m_addTextAction->setToolTip(QObject::tr("Show or hide text"));
    QObject::connect(m_addTextAction.get(), &QAction::triggered
                     , [this](){m_showText ? textShow(false) : textShow(true);});
    m_trainActionList.append(m_addTextAction.get());
}

void TrainShape::textShow(bool showText)
{
    if (showText) {
        if (m_trainText == nullptr) {
            m_trainText=new QGraphicsTextItem(this);
            m_trainText->setPlainText("Поезд-");
            m_trainText->setTextInteractionFlags(Qt::TextEditorInteraction);
            m_trainText->setRotation(-90);
        }
        m_trainText->show();
        m_showText = true;
    } else {
        m_trainText->hide();
        m_showText = false;
    }
}

void TrainShape::drawTrainShape(QPainter *painter)
{
    painter->drawPolygon(trainPolygon(rect()));

    if (m_showText)
        m_trainText->setPos(m_trainRect.right(), m_trainRect.bottom());
}

QPolygonF TrainShape::trainPolygon(const QRectF &rect) const
{
    qreal fourthWidth{rect.width() / 4.0}; //7.5
    qreal centerY{rect.bottom() - (rect.height() / 10.0 * 3.0)}; //10.0
    QPointF bottomLeft{rect.bottomLeft()}; //-15.0, 25.0
    QPointF centerLeft{rect.left(), centerY}; //-15.0, 10.0
    QPointF centerLeftR{rect.left() + fourthWidth, centerY}; //-7.5, 10.0
    QPointF topLeft{rect.left() + fourthWidth, rect.top()}; //-7.5, -25.0
    QPointF topRight{rect.right() - fourthWidth, rect.top()}; //7.5, -25.0
    QPointF centerRightL{rect.right() - fourthWidth, centerY}; //7.5, 10.0
    QPointF centerRight{rect.right(), centerY}; //15.0, 10.0
    QPointF bottomRight{rect.bottomRight()}; // 15.0, 25.0
    QPolygonF trainPolygon;
    trainPolygon << bottomLeft << centerLeft << centerLeftR << topLeft << topRight
                 << centerRightL << centerRight << bottomRight;

    return trainPolygon;
}

PlaneShape::PlaneShape(QGraphicsItem *parent)
    : TechnicsShape(parent)
    , m_planeType{Plane}
    , m_planeRect{-30.0, -37.5, 60.0, 75.0}
    , m_planeText{nullptr}
    , m_showText{false}
{
    setFlag(ItemSendsGeometryChanges, true);
    setAcceptHoverEvents(true);
    setPen(QPen(Qt::red, 1));
    setBrush(QBrush(Qt::red));
}

void PlaneShape::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(widget);

    painter->setRenderHint(QPainter::Antialiasing);
    painter->setRenderHint(QPainter::SmoothPixmapTransform);
    painter->setPen(pen());
    painter->setBrush(brush());

    drawPlaneShape(painter);

    if (option->state & QStyle::State_Selected)
        highlightSelected(painter, option);
}

QRectF PlaneShape::boundingRect() const
{
    QRectF boundingRect{m_planeRect};
    qreal halfpw{pen().style() == Qt::NoPen ? qreal(0.0) : pen().widthF() / 2};
    if (halfpw > 0.0)
        boundingRect.adjust(-halfpw, -halfpw, halfpw, halfpw);

    return boundingRect;
}

QPainterPath PlaneShape::shape() const
{
    return shapeFromPath(planePath());
}

QPixmap PlaneShape::image()
{
    qreal pixmapWidth{boundingRect().width()};
    qreal pixmapHeight{boundingRect().height()};
    QPixmap pixmap(pixmapWidth, pixmapHeight);
    pixmap.fill(Qt::transparent);

    QPainter painter(&pixmap);
    painter.setPen(pen());
    painter.setBrush(brush());
    painter.translate(pixmapWidth / 2.0, pixmapHeight / 2.0);
    drawPlaneShape(&painter);

    return pixmap;
}

TechnicsShape::ShapeType PlaneShape::shapeType() const
{
    return m_planeType;
}

void PlaneShape::setRect(const QRectF &rect)
{
    if (m_planeRect == rect)
        return;

    prepareGeometryChange();
    m_planeRect.setRect(rect.topLeft().x(), rect.topLeft().y(), rect.width(), rect.height());
    if (m_planeText != nullptr)
        m_planeText->setPos(m_planeRect.right(), m_planeRect.bottom() - m_planeRect.width() / 6);

    update();
}

QRectF PlaneShape::rect() const
{
    return m_planeRect;
}

void PlaneShape::setHeight(const qreal &height)
{
    if (m_planeRect.height() == height)
        return;

    qreal oldHeight{m_planeRect.height()};
    prepareGeometryChange();
    m_planeRect.setHeight(height);
    qreal dy{(m_planeRect.height() - oldHeight) / 2};
    m_planeRect.moveTo(QPointF(m_planeRect.x(), m_planeRect.y() - dy));
    update();
}

qreal PlaneShape::height() const
{
    return m_planeRect.height();
}

void PlaneShape::setText(const QString &text)
{
    if (m_planeText == nullptr) {
        m_planeText = new QGraphicsTextItem(this);
        m_planeText->setTextInteractionFlags(Qt::TextEditorInteraction);
        m_planeText->setRotation(-90);
    }
    m_planeText->setPlainText(text);
    m_showText = true;
}

QString PlaneShape::text() const
{
    if (m_planeText == nullptr)
        return "";

    return m_planeText->toPlainText();
}

void PlaneShape::mousePressEvent(QGraphicsSceneMouseEvent *mouseEvent)
{
    if (mouseEvent->buttons() == Qt::RightButton) {
        createAction();
        addActions(m_planeActionList);
        QAction menuAction{menu()->exec(mouseEvent->screenPos())};
        QString menuActionText;
        if (menuAction.parent()) {
            menuActionText = menuAction.parent()->objectName();
        }
        if ((menuActionText != "actionDeleteItem") && (menuActionText != "actionCut")) {
            removeActions(m_planeActionList);
            m_planeActionList.clear();
        }
    } else {
        AbstractShape::mousePressEvent(mouseEvent);
    }
}

void PlaneShape::createAction()
{
    QString addText{m_showText ? QObject::tr("Hide text") : QObject::tr("Show text")};
    m_addTextAction.reset(new QAction(addText));
    m_addTextAction->setToolTip(QObject::tr("Show or hide text"));
    QObject::connect(m_addTextAction.get(), &QAction::triggered
                     , [this](){m_showText ? textShow(false) : textShow(true);});
    m_planeActionList.append(m_addTextAction.get());
}

void PlaneShape::textShow(bool showText)
{
    if (showText) {
        if (m_planeText == nullptr) {
            m_planeText=new QGraphicsTextItem(this);
            m_planeText->setPlainText("СА-");
            m_planeText->setTextInteractionFlags(Qt::TextEditorInteraction);
            m_planeText->setRotation(-90);
        }
        m_planeText->show();
        m_showText = true;
    } else {
        m_planeText->hide();
        m_showText = false;
    }
}

void PlaneShape::drawPlaneShape(QPainter *painter)
{
    painter->drawPath(planePath());

    if (m_showText)
        m_planeText->setPos(m_planeRect.right(), m_planeRect.bottom());
}

QPainterPath PlaneShape::planePath() const
{
    QPainterPath currentPath;

    qreal fuselageWidth{m_planeRect.width() / 6.0}; //10.0 X
    qreal wingArcIndent{fuselageWidth / 2.0}; //5.0 X
    qreal wingHeight{m_planeRect.height() / 7.5}; //10.0 Y
    qreal fuselageArcIndent{wingHeight / 2.0}; //5.0 Y

    qreal fuselageRight{m_planeRect.center().x() + wingArcIndent}; //5.0 X
    qreal fuselageLeft{m_planeRect.center().x() - wingArcIndent}; //-5.0 X

    qreal wingLeft{m_planeRect.left() + wingArcIndent}; //-25.0 X
    qreal wingTop{m_planeRect.center().y() - fuselageArcIndent}; //-5.0 Y
    qreal wingRight{m_planeRect.right() - wingArcIndent}; //25.0 X
    qreal wingBottom{m_planeRect.center().y() + fuselageArcIndent}; //5.0 Y

    qreal thirdWidht{m_planeRect.width() / 3.0}; //20.0
    qreal tailLeft{m_planeRect.left() + thirdWidht}; //-10.0 X
    qreal tailTop{m_planeRect.bottom() - wingHeight}; //27.5 Y
    qreal tailRight{m_planeRect.right() - thirdWidht}; //10.0  X

    qreal sweepLenght{180.0};
    qreal startAngle{270.0};

    //tail
    currentPath.moveTo(tailLeft, m_planeRect.bottom()); //-10.0, 37.5
    currentPath.lineTo(tailRight, m_planeRect.bottom()); //10.0, 37.5
    currentPath.arcTo(tailRight - wingArcIndent, tailTop, fuselageWidth, wingHeight, startAngle
                      , sweepLenght); //5.0, 27.5
    currentPath.lineTo(fuselageRight, tailTop); //5.0, 27.5

    //fuselage
    currentPath.lineTo(fuselageRight, wingBottom); //5.0, 5.0

    //right wing
    currentPath.lineTo(wingRight, wingBottom); //25.0, 5.0
    currentPath.arcTo(wingRight - wingArcIndent, wingTop, fuselageWidth, wingHeight
                      , startAngle, sweepLenght); //20.0, -5.0
    currentPath.lineTo(fuselageRight, wingTop); //5.0, -5.0

    //fuselage
    currentPath.lineTo(fuselageRight, m_planeRect.top() + fuselageArcIndent); // 5.0, -32.0? or -32.5
    startAngle = 0.0;
    currentPath.arcTo(fuselageLeft, m_planeRect.top(), fuselageWidth, wingHeight, startAngle
                      , sweepLenght); // -5.0, -37.0? or -37.5
    currentPath.lineTo(fuselageLeft, wingTop); // -5.0, -5.0

    //left wing
    currentPath.lineTo(wingLeft, wingTop); //-25.0, -5.0
    startAngle = 90.0;
    currentPath.arcTo(m_planeRect.left(), wingTop, fuselageWidth, wingHeight, startAngle
                      , sweepLenght); //-30.0, -5.0
    currentPath.lineTo(fuselageLeft, wingBottom); //-5.0, 5.0

    //fuselage
    currentPath.lineTo(fuselageLeft, tailTop); //-5.0, 27.5

    //tail
    currentPath.lineTo(tailLeft, tailTop); //-10.0, 27.5
    currentPath.arcTo(tailLeft - wingArcIndent, tailTop, fuselageWidth, wingHeight
                      , startAngle, sweepLenght); //-15.0, 27.5

    return currentPath;
}


SeaplaneShape::SeaplaneShape(QGraphicsItem *parent)
    : TechnicsShape(parent)
    , m_seaplaneType{Seaplane}
    , m_seaplaneRect{-30.0, -37.5, 60.0, 75.0}
    , m_seaplaneText{nullptr}
    , m_showText{false}
{
    setFlag(ItemSendsGeometryChanges, true);
    setAcceptHoverEvents(true);
    setPen(QPen(Qt::red, 1));
    setBrush(QBrush(Qt::red));
}

void SeaplaneShape::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(widget);

    painter->setRenderHint(QPainter::Antialiasing);
    painter->setRenderHint(QPainter::SmoothPixmapTransform);
    painter->setPen(pen());
    painter->setBrush(brush());

    drawSeaplaneShape(painter);

    if (option->state & QStyle::State_Selected)
        highlightSelected(painter, option);
}

QRectF SeaplaneShape::boundingRect() const
{
    QRectF boundingRect{m_seaplaneRect};
    qreal halfpw{pen().style() == Qt::NoPen ? qreal(0.0) : pen().widthF() / 2};
    if (halfpw > 0.0)
        boundingRect.adjust(-halfpw, -halfpw, halfpw, halfpw);

    return boundingRect;
}

QPainterPath SeaplaneShape::shape() const
{
    return shapeFromPath(seaplanePath());
}

QPixmap SeaplaneShape::image()
{
    qreal pixmapWidth{boundingRect().width()};
    qreal pixmapHeight{boundingRect().height()};
    QPixmap pixmap(pixmapWidth, pixmapHeight);
    pixmap.fill(Qt::transparent);

    QPainter painter(&pixmap);
    painter.setPen(pen());
    painter.setBrush(brush());
    painter.translate(pixmapWidth / 2.0, pixmapHeight / 2.0);
    drawSeaplaneShape(&painter);

    return pixmap;
}

TechnicsShape::ShapeType SeaplaneShape::shapeType() const
{
    return m_seaplaneType;
}

void SeaplaneShape::setRect(const QRectF &rect)
{
    if (m_seaplaneRect == rect)
        return;

    prepareGeometryChange();
    m_seaplaneRect.setRect(rect.topLeft().x(), rect.topLeft().y(), rect.width(), rect.height());
    if (m_seaplaneText != nullptr)
        m_seaplaneText->setPos(m_seaplaneRect.right(), m_seaplaneRect.bottom() - m_seaplaneRect.width() / 6);

    update();
}

QRectF SeaplaneShape::rect() const
{
    return m_seaplaneRect;
}

void SeaplaneShape::setHeight(const qreal &height)
{
    if (m_seaplaneRect.height() == height)
        return;

    qreal oldHeight{m_seaplaneRect.height()};
    prepareGeometryChange();
    m_seaplaneRect.setHeight(height);
    qreal dy{(m_seaplaneRect.height() - oldHeight) / 2};
    m_seaplaneRect.moveTo(QPointF(m_seaplaneRect.x(), m_seaplaneRect.y() - dy));
    update();
}

qreal SeaplaneShape::height() const
{
    return m_seaplaneRect.height();
}

void SeaplaneShape::setText(const QString &text)
{
    if (m_seaplaneText == nullptr) {
        m_seaplaneText = new QGraphicsTextItem(this);
        m_seaplaneText->setTextInteractionFlags(Qt::TextEditorInteraction);
        m_seaplaneText->setRotation(-90);
    }
    m_seaplaneText->setPlainText(text);
    m_showText = true;
}

QString SeaplaneShape::text() const
{
    if (m_seaplaneText == nullptr)
        return "";

    return m_seaplaneText->toPlainText();
}

void SeaplaneShape::mousePressEvent(QGraphicsSceneMouseEvent *mouseEvent)
{
    if (mouseEvent->buttons() == Qt::RightButton) {
        createAction();
        addActions(m_seaplaneActionList);
        QAction menuAction{menu()->exec(mouseEvent->screenPos())};
        QString menuActionText;
        if (menuAction.parent()) {
            menuActionText = menuAction.parent()->objectName();
        }
        if ((menuActionText != "actionDeleteItem") && (menuActionText != "actionCut")) {
            removeActions(m_seaplaneActionList);
            m_seaplaneActionList.clear();
        }
    } else {
        AbstractShape::mousePressEvent(mouseEvent);
    }
}

void SeaplaneShape::createAction()
{
    QString addText{m_showText ? QObject::tr("Hide text") : QObject::tr("Show text")};
    m_addTextAction.reset(new QAction(addText));
    m_addTextAction->setToolTip(QObject::tr("Show or hide text"));
    QObject::connect(m_addTextAction.get(), &QAction::triggered
                     , [this](){m_showText ? textShow(false) : textShow(true);});
    m_seaplaneActionList.append(m_addTextAction.get());
}

void SeaplaneShape::textShow(bool showText)
{
    if (showText) {
        if (m_seaplaneText == nullptr) {
            m_seaplaneText=new QGraphicsTextItem(this);
            m_seaplaneText->setPlainText("ГСА-");
            m_seaplaneText->setTextInteractionFlags(Qt::TextEditorInteraction);
            m_seaplaneText->setRotation(-90);
        }
        m_seaplaneText->show();
        m_showText = true;
    } else {
        m_seaplaneText->hide();
        m_showText = false;
    }
}

void SeaplaneShape::drawSeaplaneShape(QPainter *painter)
{
    painter->drawPath(seaplanePath());

    if (m_showText)
        m_seaplaneText->setPos(m_seaplaneRect.right(), m_seaplaneRect.bottom());
}

QPainterPath SeaplaneShape::seaplanePath() const
{
    QPainterPath currentPath;

    qreal fuselageWidth{m_seaplaneRect.width() / 6.0}; //10.0 X
    qreal wingArcIndent{fuselageWidth / 2.0}; //5.0 X
    qreal wingHeight{m_seaplaneRect.height() / 7.5}; //10.0 Y
    qreal fuselageArcIndent{wingHeight / 2.0}; //5.0 Y

    qreal fuselageRight{m_seaplaneRect.center().x() + wingArcIndent}; //5.0 X
    qreal fuselageLeft{m_seaplaneRect.center().x() - wingArcIndent}; //-5.0 X

    qreal wingLeft{m_seaplaneRect.left() + wingArcIndent}; //-25.0 X
    qreal wingTop{m_seaplaneRect.center().y() - fuselageArcIndent}; //-5.0 Y
    qreal wingRight{m_seaplaneRect.right() - wingArcIndent}; //25.0 X
    qreal wingBottom{m_seaplaneRect.center().y() + fuselageArcIndent}; //5.0 Y

    qreal thirdWidht{m_seaplaneRect.width() / 3.0}; //20.0
    qreal tailLeft{m_seaplaneRect.left() + thirdWidht}; //-10.0 X
    qreal tailTop{m_seaplaneRect.bottom() - wingHeight}; //27.5 Y
    qreal tailRight{m_seaplaneRect.right() - thirdWidht}; //10.0  X

    qreal sweepLenght{180.0};
    qreal startAngle{270.0};

    //tail
    currentPath.moveTo(tailLeft, m_seaplaneRect.bottom()); //-10.0, 37.5
    currentPath.lineTo(tailRight, m_seaplaneRect.bottom()); //10.0, 37.5
    currentPath.arcTo(tailRight - wingArcIndent, tailTop, fuselageWidth, wingHeight, startAngle
                      , sweepLenght); //5.0, 27.5
    currentPath.lineTo(fuselageRight, tailTop); //5.0, 27.5

    //fuselage
    currentPath.lineTo(fuselageRight, wingBottom); //5.0, 5.0

    //right wing
    currentPath.lineTo(wingRight, wingBottom); //25.0, 5.0
    currentPath.arcTo(wingRight - wingArcIndent, wingTop, fuselageWidth, wingHeight
                      , startAngle, sweepLenght); //20.0, -5.0
    currentPath.lineTo(fuselageRight, wingTop); //5.0, -5.0

    //fuselage
    currentPath.lineTo(fuselageRight, m_seaplaneRect.top() + fuselageArcIndent); // 5.0, -32.0? or -32.5
    startAngle = 0.0;
    currentPath.arcTo(fuselageLeft, m_seaplaneRect.top(), fuselageWidth, wingHeight, startAngle
                      , sweepLenght); // -5.0, -37.0? or -37.5
    currentPath.lineTo(fuselageLeft, wingTop); // -5.0, -5.0

    //left wing
    currentPath.lineTo(wingLeft, wingTop); //-25.0, -5.0
    startAngle = 90.0;
    currentPath.arcTo(m_seaplaneRect.left(), wingTop, fuselageWidth, wingHeight, startAngle
                      , sweepLenght); //-30.0, -5.0
    currentPath.lineTo(fuselageLeft, wingBottom); //-5.0, 5.0

    //fuselage
    currentPath.lineTo(fuselageLeft, tailTop); //-5.0, 27.5

    //tail
    currentPath.lineTo(tailLeft, tailTop); //-10.0, 27.5
    currentPath.arcTo(tailLeft - wingArcIndent, tailTop, fuselageWidth, wingHeight
                      , startAngle, sweepLenght); //-15.0, 27.5

    //left lending gear
    currentPath.moveTo(wingLeft + wingArcIndent, wingBottom + fuselageArcIndent); //-20.0, 10.0
    currentPath.lineTo(wingLeft + wingArcIndent, wingTop - fuselageArcIndent); //-20.0, -10.0

    //right landing gear
    currentPath.moveTo(wingRight - wingArcIndent, wingBottom + fuselageArcIndent); //20.0, 10.0
    currentPath.lineTo(wingRight - wingArcIndent, wingTop - fuselageArcIndent); //20.0, -10.0

    return currentPath;
}
