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
    basePolygon << frontCenter << frontRight << bottomRight << bottomLeft << frontLeft
                            << frontCenter;
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

//    QPolygonF vesselPolygon;
//    vesselPolygon << QPointF(0.0, 37.5) << QPointF(15.0, 20.0) << QPointF(15.0, -20.0)
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
//    case Vessel: {
//        painter->setPen(QPen(Qt::red, 1));
//        painter->drawPolygon(vesselPolygon);
//        painter->rotate(-90);
//        painter->drawText(QPointF(-5.0, 4.0), QString("С"));
//        break;
//    }
//    case Boat: {
//        painter->setPen(QPen(Qt::red, 1));
//        painter->drawPolygon(vesselPolygon);
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

    if (m_showText) {
        qreal sixthWidth{m_baseRect.width() / 6}; // 5.0
        m_baseText->setPos(m_baseRect.right(), m_baseRect.bottom() - sixthWidth * 2);
    }

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
            m_baseText->setPlainText(QObject::tr("Insert text"));
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

    qreal sixthWidth{m_autoLadderRect.width() / 6}; // 5.0

    if (m_showText) {
        m_autoLadderText->setPos(m_autoLadderRect.right(), m_autoLadderRect.bottom()
                                                               - sixthWidth * 2);
        }
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
    qreal sixthWidth{m_crankLiftRect.width() / 6}; // 5.0
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


    if (m_showText) {
        m_crankLiftText->setPos(m_crankLiftRect.right(), m_crankLiftRect.bottom()
                                                               - sixthWidth * 2);
    }
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
    qreal sixthWidth{m_telescopicLiftRect.width() / 6}; // 5.0
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


    if (m_showText) {
        m_telescopicLiftText->setPos(m_telescopicLiftRect.right(), m_telescopicLiftRect.bottom()
                                                                       - sixthWidth * 2);
    }
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
    qreal sixthWidth{m_hoseCarRect.width() / 6}; // 5.0

    if (m_showText) {
        m_hoseCarText->setPos(m_hoseCarRect.right(), m_hoseCarRect.bottom() - sixthWidth * 2);
    }
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
    qreal sixthWidth{m_commRect.width() / 6}; // 5.0

    if (m_showText) {
        m_commText->setPos(m_commRect.right(), m_commRect.bottom() - sixthWidth * 2);
    }
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
    qreal sixthWidth{m_techServRect.width() / 6}; // 5.0

    if (m_showText) {
        m_techServText->setPos(m_techServRect.right(), m_techServRect.bottom() - sixthWidth * 2);
    }
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

    if (m_showText) {
        m_smokRemText->setPos(m_smokRemRect.right(), m_smokRemRect.bottom() - thirdWidth);
    }
}
