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

#include "../include/technicsshape.h"

#include <QPainter>
#include <QMenu>
#include <QGraphicsSceneEvent>
#include <QStyleOptionGraphicsItem>

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
    case Tanker:
        p_technicsShape = new TankerShape(parent);
        break;
    case Base:
        p_technicsShape = new BaseShape(parent);
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

void TankerShape::drawPipes(qreal roundRadius, QPainter *painter)
{
    painter->setPen(QPen(Qt::black, 1));
    qreal pipeY{m_tankerRect.bottom() - roundRadius};
    QPointF rightPipeP1{m_tankerRect.right(), pipeY};
    QPointF rightPipeP2{m_tankerRect.right() + roundRadius, pipeY};
    painter->drawLine(rightPipeP1, rightPipeP2); // Right pipe

    QPointF rightConnectP1{rightPipeP2.x(), rightPipeP2.y() + roundRadius / 2};
    QPointF rightConnectP2{rightPipeP2.x(), rightPipeP2.y() - roundRadius / 2};
    painter->drawLine(rightConnectP1, rightConnectP2); // Right pipe connection

    QPointF leftPipeP1{m_tankerRect.left(), pipeY};
    QPointF leftPipeP2{m_tankerRect.left() - roundRadius, pipeY};
    painter->drawLine(leftPipeP1, leftPipeP2); // Left pipe

    QPointF leftConnectP1{leftPipeP2.x(), leftPipeP2.y() + roundRadius / 2};
    QPointF leftConnectP2{leftPipeP2.x(), leftPipeP2.y() - roundRadius / 2};
    painter->drawLine(leftConnectP1, leftConnectP2); // Right pipe connection
}

void TankerShape::drawCollector(QPainter *painter, qreal roundRadius)
{
    painter->setPen(QPen(Qt::black, 1));
    qreal collectorX{m_tankerRect.center().x()};
    qreal collectorY{m_tankerRect.bottom() + roundRadius * 2};
    qreal leftPipeX{collectorX - roundRadius};
    QPointF leftRightPipeP1{collectorX, m_tankerRect.bottom()};
    QPointF leftPipeP2{leftPipeX, collectorY};
    painter->drawLine(leftRightPipeP1, leftPipeP2); //Left collector pipe

    qreal rightPipeX{collectorX + roundRadius};
    QPointF rightPipeP2{rightPipeX, collectorY};
    painter->drawLine(leftRightPipeP1, rightPipeP2); //Right collector pipe

    QPointF leftConnectP1{leftPipeX - roundRadius / 2, collectorY};
    QPointF leftConnectP2{leftPipeX + roundRadius / 2, collectorY};
    painter->drawLine(leftConnectP1, leftConnectP2); //Left connector

    QPointF rightConnectP1{rightPipeX - roundRadius / 2, collectorY};
    QPointF rightConnectP2{rightPipeX + roundRadius / 2, collectorY};
    painter->drawLine(rightConnectP1, rightConnectP2);  //Right connector
}

void TankerShape::drawTankerShape(QPainter *painter)
{
    qreal frontTab{m_tankerRect.height() / 3};
    qreal roundRadius{m_tankerRect.width() / 6}; // 5.0
    QPointF roundTopLeft{m_tankerRect.left() + roundRadius, m_tankerRect.top() + frontTab}; // -10.0, -12.5
    QPointF roundBottomRight{m_tankerRect.right() - roundRadius
                , m_tankerRect.bottom() - roundRadius};

    painter->drawPolygon(basePolygon(rect()));
    painter->drawRoundedRect(QRectF(roundTopLeft, roundBottomRight), roundRadius, roundRadius);

    if (m_showPipes) {
        drawPipes(roundRadius, painter);
    }

    if (m_showCollector) {
        drawCollector(painter, roundRadius);
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

    qreal roundRadius{m_tankerRect.width() / 6}; // 5.0
    if (m_showPipes) {
        qreal pipeY{m_tankerRect.bottom() - roundRadius};
        QPointF rightPipeP1{m_tankerRect.right(), pipeY};
        QPointF rightPipeP2{m_tankerRect.right() + roundRadius, pipeY};
        // Right pipe
        path.moveTo(rightPipeP1);
        path.lineTo(rightPipeP2);

        QPointF rightConnectP1{rightPipeP2.x(), rightPipeP2.y() + roundRadius / 2};
        QPointF rightConnectP2{rightPipeP2.x(), rightPipeP2.y() - roundRadius / 2};
        // Right pipe connection
        path.moveTo(rightConnectP1);
        path.lineTo(rightConnectP2);

        QPointF leftPipeP1{m_tankerRect.left(), pipeY};
        QPointF leftPipeP2{m_tankerRect.left() - roundRadius, pipeY};
        // Left pipe
        path.moveTo(leftPipeP1);
        path.lineTo(leftPipeP2);

        QPointF leftConnectP1{leftPipeP2.x(), leftPipeP2.y() + roundRadius / 2};
        QPointF leftConnectP2{leftPipeP2.x(), leftPipeP2.y() - roundRadius / 2};
        // Right pipe connection
        path.moveTo(leftConnectP1);
        path.lineTo(leftConnectP2);
    }

    if (m_showCollector) {
        qreal collectorX{m_tankerRect.center().x()};
        qreal collectorY{m_tankerRect.bottom() + roundRadius * 2};
        qreal leftPipeX{collectorX - roundRadius};
        QPointF leftRightPipeP1{collectorX, m_tankerRect.bottom()};
        QPointF leftPipeP2{leftPipeX, collectorY};
        //Left collector pipe
        path.moveTo(leftRightPipeP1);
        path.lineTo(leftPipeP2);

        qreal rightPipeX{collectorX + roundRadius};
        QPointF rightPipeP2{rightPipeX, collectorY};
        //Right collector pipe
        path.moveTo(leftRightPipeP1);
        path.lineTo(rightPipeP2);

        QPointF leftConnectP1{leftPipeX - roundRadius / 2, collectorY};
        QPointF leftConnectP2{leftPipeX + roundRadius / 2, collectorY};
        //Left connector
        path.moveTo(leftConnectP1);
        path.lineTo(leftConnectP2);

        QPointF rightConnectP1{rightPipeX - roundRadius / 2, collectorY};
        QPointF rightConnectP2{rightPipeX + roundRadius / 2, collectorY};
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
        m_tankerText->setPos(m_tankerRect.right(), m_tankerRect.bottom() - m_tankerRect.width() / 6);
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
        m_tankerText->setPos(m_tankerRect.right(), m_tankerRect.bottom() - m_tankerRect.width() / 6);
        m_tankerText->setRotation(-90);
    }
    m_tankerText->setPlainText(text);
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
            m_tankerText->setPos(m_tankerRect.right(), m_tankerRect.bottom() - m_tankerRect.width() / 6);
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

BaseShape::BaseShape(QGraphicsItem *parent)
    : TechnicsShape(parent)
    , m_baseType{Base}
    , m_baseRect{QRectF(-15.0, -37.7, 30.0, 75.0)}
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
        m_baseText->setPos(m_baseRect.right(), m_baseRect.bottom() - m_baseRect.width() / 6);
        m_baseText->setRotation(-90);
    }
    m_baseText->setPlainText(text);
}

QString BaseShape::text() const
{
    if (m_baseText == nullptr)
        return "";

    return m_baseText->toPlainText();
}

void BaseShape::textShow(bool showText)
{
    if (showText) {
        if (m_baseText == nullptr) {
            m_baseText=new QGraphicsTextItem(this);
//            m_tankerText->setPlainText("АЦ-");
            m_baseText->setTextInteractionFlags(Qt::TextEditorInteraction);
            m_baseText->setPos(m_baseRect.right(), m_baseRect.bottom() - m_baseRect.width() / 6);
            m_baseText->setRotation(-90);
        }
        m_baseText->show();
        m_showText = true;
    } else {
        m_baseText->hide();
        m_showText = false;
    }
}
