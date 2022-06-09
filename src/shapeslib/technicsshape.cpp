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

TechnicsShape::TechnicsShape(QMenu *contextMenu, ShapeType shapeType, QGraphicsItem *parent)
    : AbstractShape(contextMenu, parent)
    , m_shapeType{shapeType}
{
    setFlag(ItemSendsGeometryChanges, true);
    setAcceptHoverEvents(true);
}

void TechnicsShape::paint(QPainter *painter, const QStyleOptionGraphicsItem *option
                          , QWidget *widget)
{
    Q_UNUSED(option);
    Q_UNUSED(widget);

    drawShape(painter);
}

QRectF TechnicsShape::boundingRect() const
{
    qreal penWidth {1.0};
    return QRectF(-32.0 - penWidth / 2.0, -37.5 - penWidth / 2.0
                  , 64.0 + penWidth, 75.0 + penWidth);
}

void TechnicsShape::drawShape(QPainter *painter)
{
    painter->setRenderHint(QPainter::Antialiasing);
    painter->setRenderHint(QPainter::SmoothPixmapTransform);

    QPolygonF autoBase;
    autoBase << QPointF(0.0, -37.5) << QPointF(15.0, -12.5) << QPointF(15.0, 37.5)
            << QPointF(-15.0, 37.5) << QPointF(-15.0, -12.5) << QPointF(0.0, -37.5);

    QPolygonF vesselPolygon;
    vesselPolygon << QPointF(0.0, 37.5) << QPointF(15.0, 20.0) << QPointF(15.0, -20.0)
                  << QPointF(0.0, -37.5) << QPointF(-15.0, -20.0) << QPointF(-15.0, 20.0);

    QPainterPath planePath;
    planePath.moveTo(-10.0, 37.5);
    planePath.lineTo(10.0, 37.5);
    planePath.arcTo(5.0, 27.5, 10.0, 10.0, 270.0, 180.0);
    planePath.lineTo(5.0, 27.5);
    planePath.lineTo(5.0, 5.0);
    planePath.lineTo(25.0, 5.0);
    planePath.arcTo(20.0, -5.0, 10.0, 10.0, 270.0, 180.0);
    planePath.lineTo(5.0, -5.0);
    planePath.lineTo(5.0, -32.0);
    planePath.arcTo(-5.0, -37.0, 10.0, 10.0, 0.0, 180.0);
    planePath.lineTo(-5.0, -5.0);
    planePath.lineTo(-25.0, -5.0);
    planePath.arcTo(-30.0, -5.0, 10.0, 10.0, 90.0, 180.0);
    planePath.lineTo(-5.0, 5.0);
    planePath.lineTo(-5.0, 27.5);
    planePath.lineTo(-10.0, 27.5);
    planePath.arcTo(-15.0, 27.5, 10.0, 10.0, 90.0, 180.0);

    painter->setBrush(QBrush(Qt::white));
    switch (m_shapeType) {
    case Base: {
        painter->setPen(QPen(Qt::red, 1));
        painter->drawPolygon(autoBase);
        break;
    }
    case Tanker: {
        painter->setPen(QPen(Qt::red, 1));
        painter->drawPolygon(autoBase);
        painter->drawRoundedRect(-10.0, -12.0, 20.0, 45.0, 5.0, 5.0);
        break;
    }
    case AutoPump: {
        QPolygonF pump;
        pump << QPointF(-10.0, 37.5) << QPointF(-10.0, 25.0) << QPointF(10.0, 25.0)
             << QPointF(10.0, 37.5);
        painter->setPen(QPen(Qt::red, 1));
        painter->drawPolygon(autoBase);
        painter->drawPolygon(pump);
        break;
    }
    case FirstAid: {
        painter->setPen(QPen(Qt::red, 1));
        painter->drawPolygon(autoBase);
        painter->rotate(-90);
        painter->drawText(QPointF(-32.0, 4.0), QString("ПП"));
        break;
    }
    case Emergency: {
        painter->setPen(QPen(Qt::red, 1));
        painter->drawPolygon(autoBase);
        painter->rotate(-90);
        painter->drawText(QPointF(-32.0, 4.0), QString("АС"));
        break;
    }
    case AutoLadder: {
        painter->setPen(QPen(Qt::red, 1));
        painter->drawPolygon(autoBase);
        QVector<QLineF> ladder;
        ladder.append(QLineF(-10.0, 32.5, -10.0, -12.5));
        ladder.append(QLineF(10.0, 32.5, 10.0, -12.5));
        ladder.append(QLineF(-10.0, 25.0, 10.0, 25.0));
        ladder.append(QLineF(-10.0, 20.0, 10.0, 20.0));
        ladder.append(QLineF(-10.0, 15.0, 10.0, 15.0));
        ladder.append(QLineF(-10.0, 10.0, 10.0, 10.0));
        ladder.append(QLineF(-10.0, 5.0, 10.0, 5.0));
        ladder.append(QLineF(-10.0, 0.0, 10.0, 0.0));
        ladder.append(QLineF(-10.0, -5.0, 10.0, -5.0));
        painter->drawLines(ladder);
        break;
    }
    case CrankLift: {
        painter->setPen(QPen(Qt::red, 1));
        painter->drawPolygon(autoBase);
        QPolygonF crank;
        crank << QPointF(-10.0, -12.5) << QPointF(-10.0, 32.5) << QPointF(10.0, -12.5)
              <<QPointF(10.0, 32.5);
        painter->drawPolyline(crank);
        break;
    }
    case TelescopicLift: {
        painter->setPen(QPen(Qt::red, 1));
        painter->drawPolygon(autoBase);
        QVector<QLineF> telescopic;
        telescopic.append(QLineF(-10.0, 32.5, -10.0, -12.5));
        telescopic.append(QLineF(0.0, 20.0, 0.0, -25.0));
        telescopic.append(QLineF(10.0, 32.5, 10.0, -12.5));
        painter->drawLines(telescopic);
        break;
    }
    case Hose: {
        painter->setPen(QPen(Qt::red, 1));
        painter->drawPolygon(autoBase);
        painter->rotate(-90);
        painter->drawText(QPointF(-20.0, 4.0), QString("Р"));
        break;
    }
    case Comm: {
        painter->setPen(QPen(Qt::red, 1));
        painter->drawPolygon(autoBase);
        painter->rotate(-90);
        painter->drawText(QPointF(-20.0, 4.0), QString("CO"));
        break;
    }
    case Tech_serv: {
        painter->setPen(QPen(Qt::red, 1));
        painter->drawPolygon(autoBase);
        painter->rotate(-90);
        painter->drawText(QPointF(-20.0, 4.0), QString("Т"));
        break;
    }
    case Smok_rem: {
        painter->setPen(QPen(Qt::red, 1));
        painter->drawPolygon(autoBase);
        painter->drawEllipse(QPointF(0.0, 10.0), 10.0, 10.0);
        painter->drawLine(QLineF(-8.0, 15.0, 8.0, 5.0));  //inside ellipse, left bottom - right top
        painter->drawLine(QLineF(8.0, 5.0, 2.0, 1.0));    //inside ellipse, right-right
        painter->drawLine(QLineF(2.0, 1.0, -2.0, 19.0));  //inside ellipse, right top - left botttom
        painter->drawLine(QLineF(-2.0, 19.0, -8.0, 15.0));    //inside ellipse, left-left
        break;
    }
    case AutoPumpS: {
        QPolygonF pump;
        pump << QPointF(-10.0, 37.5) << QPointF(-10.0, 25.0) << QPointF(10.0, 25.0)
             << QPointF(10.0, 37.5);
        painter->setPen(QPen(Qt::red, 1));
        painter->drawPolygon(autoBase);
        painter->drawPolygon(pump);
        painter->rotate(-90);
        painter->drawText(QPointF(-20.0, 4.0), QString("С"));
        break;
    }
    case CarriageCar_1: {
        painter->setPen(QPen(Qt::red, 1));
        painter->drawPolygon(autoBase);
        painter->drawRoundedRect(-10.0, -12.0, 20.0, 45.0, 5.0, 5.0);
        painter->drawLine(QLineF(-15.0, 37.5, -30.0, -10.0));    //barrel
        painter->drawLine(QLineF(-32.0, -3.0, -30.0, -10.0));    //left part arrow
        painter->drawLine(QLineF(-30.0, -10.0, -24.5, -6.0));    //right part arrow
        painter->drawLine(QLineF(-20.0, 20.0, -15.0, 20.0));    //stand
        break;
    }
    case CarriageCar_2: {
        painter->setPen(QPen(Qt::red, 1));
        painter->drawPolygon(autoBase);
        painter->drawLine(QLineF(15.0, 37.5, -8.0, -10.0));    //barrel
        painter->drawLine(QLineF(-10.0, -3.0, -8.0, -10.0));    //left part arrow
        painter->drawLine(QLineF(-8.0, -10.0, -1.5, -7.0));    //right part arrow
        painter->drawLine(QLineF(7.0, 20.0, 15.0, 20.0));    //stand
        break;
    }
    case Aerodrome: {
        painter->setPen(QPen(Qt::red, 1));
        painter->drawPolygon(autoBase);
        painter->rotate(-90);
        painter->drawText(QPointF(-20.0, 4.0), QString("А"));
        break;
    }
    case Foam: {
        painter->setPen(QPen(Qt::red, 1));
        painter->drawPolygon(autoBase);
        painter->drawEllipse(QPointF(0.0, 10.0), 10.0, 10.0);
        painter->drawLine(QLineF(-7.0, 16.5, 7.0, 3.5));  //inside ellipse, left bottom - right top
        painter->drawLine(QLineF(-7.0, 3.5, 7.0, 16.5));  //inside ellipse, left top - right botttom
        break;
    }
    case Combo: {
        painter->setPen(QPen(Qt::red, 1));
        painter->drawPolygon(autoBase);
        painter->drawEllipse(QPointF(0.0, 23.0), 10.0, 10.0);
        painter->drawLine(QLineF(-7.0, 29.5, 7.0, 16.5));  //inside ellipse, left bottom - right top
        painter->drawLine(QLineF(-7.0, 16.5, 7.0, 29.5));  //inside ellipse, left top - right botttom
        painter->setBrush(QBrush(Qt::red));
        painter->drawRect(-10.0, -11.0, 20.0, 20.0);
        break;
    }
    case Aerosol: {
        painter->setPen(QPen(Qt::red, 1));
        painter->drawPolygon(autoBase);
        painter->setBrush(QBrush(Qt::red));
        painter->drawEllipse(QPointF(0.0, 26.0), 7.0, 7.0);  // bottom ellipse
        painter->drawEllipse(QPointF(0.0, 9.0), 7.0, 7.0);  // center ellipse
        painter->drawEllipse(QPointF(0.0, -8.0), 7.0, 7.0);  // top ellipse
        break;
    }
    case Powder: {
        painter->setPen(QPen(Qt::red, 1));
        painter->drawPolygon(autoBase);
        painter->setBrush(QBrush(Qt::red));
        painter->drawRect(-10.0, 13.0, 20.0, 20.0);
        break;
    }
    case Carbon: {
        painter->setPen(QPen(Qt::red, 1));
        painter->drawPolygon(autoBase);
        QPolygonF carbonPolygon;
        carbonPolygon << QPointF(-10.0, 26.0) << QPointF(10.0, 26.0) << QPointF(0.0, 6.0);
        painter->setBrush(QBrush(Qt::red));
        painter->drawPolygon(carbonPolygon);
        break;
    }
    case GazWater: {
        painter->setPen(QPen(Qt::red, 1));
        painter->drawPolygon(autoBase);
        painter->rotate(-90);
        painter->drawText(QPointF(-32.0, 4.0), QString("ГВТ"));
        break;
    }
    case Tracked: {
        painter->setPen(QPen(Qt::red, 1));
        painter->drawPolygon(autoBase);
        painter->drawLine(QLineF(-10.0, 37.5, -10.0, -20.5));
        painter->drawLine(QLineF(10.0, 37.5, 10.0, -20.5));
        break;
    }
    case Tank: {
        painter->setPen(QPen(Qt::red, 1));
        QPolygonF tankPolygon;
        tankPolygon << QPointF(0.0, 37.5) << QPointF(18.0, 0.0) << QPointF(0.0, -37.5)
                    << QPointF(-18.0, 0.0);
        painter->drawPolygon(tankPolygon);
        break;
    }
    case GDZS: {
        painter->setPen(QPen(Qt::red, 1));
        painter->drawPolygon(autoBase);
        painter->rotate(-90);
        painter->drawText(QPointF(-32.0, 4.0), QString("ГДЗС"));
        break;
    }
    case Waterproof: {
        painter->setPen(QPen(Qt::red, 1));
        painter->drawPolygon(autoBase);
        painter->rotate(-90);
        painter->drawText(QPointF(-32.0, 4.0), QString("ВЗ"));
        break;
    }
    case Laboratory: {
        painter->setPen(QPen(Qt::red, 1));
        painter->drawPolygon(autoBase);
        painter->rotate(-90);
        painter->drawText(QPointF(-32.0, 4.0), QString("ЛБ"));
        break;
    }
    case StaffCar: {
        painter->setPen(QPen(Qt::red, 1));
        painter->drawPolygon(autoBase);
        painter->rotate(-90);
        painter->drawText(QPointF(-20.0, 4.0), QString("Ш"));
        break;
    }
    case Trailer: {
        painter->setPen(QPen(Qt::red, 1));
        painter->drawLine(QLineF(-20.0, 37.0, -20.0, 29.0));    //left cartwheel
        painter->drawLine(QLineF(-20.0, 33.0, 20.0, 33.0));    //bottom
        painter->drawLine(QLineF(20.0, 37.0, 20.0, 29.0));    //right cartwheel
        painter->drawLine(QLineF(-15.0, 33.0, -15.0, -12.0));    //left
        painter->drawLine(QLineF(-15.0, -12.0, 15.0, -12.0));    //top
        painter->drawLine(QLineF(15.0, -12.0, 15.0, 33.0));    //right
        painter->drawLine(QLineF(0.0, -12.0, 0.0, -25.0));    //center
        break;
    }
    case Vessel: {
        painter->setPen(QPen(Qt::red, 1));
        painter->drawPolygon(vesselPolygon);
        painter->rotate(-90);
        painter->drawText(QPointF(-5.0, 4.0), QString("С"));
        break;
    }
    case Boat: {
        painter->setPen(QPen(Qt::red, 1));
        painter->drawPolygon(vesselPolygon);
        painter->rotate(-90);
        painter->drawText(QPointF(-5.0, 4.0), QString("К"));
        break;
    }
    case Train: {
        QPolygonF train;
        train << QPointF(-15.0, 25.0) << QPointF(-15.0, 10.0) << QPointF(-7.0, 10.0)
              << QPointF(-7.0, -25.0) << QPointF(7.0, -25.0) << QPointF(7.0, 10.0)
              << QPointF(15.0, 10.0) << QPointF(15.0, 25.0);
        painter->setPen(QPen(Qt::red, 1));
        painter->setBrush(QBrush(Qt::red));
        painter->drawPolygon(train);
        break;
    }
    case Plane: {
        painter->setPen(QPen(Qt::red, 1));
        painter->setBrush(QBrush(Qt::red));
        painter->drawPath(planePath);
        break;
    }
    case Seaplane: {
        painter->setPen(QPen(Qt::red, 1));
        painter->setBrush(QBrush(Qt::red));
        painter->drawPath(planePath);
        painter->setPen(QPen(Qt::red, 2));
        painter->drawLine(QLineF(-20.0, 10.0, -20.0, -10.0));   //left line
        painter->drawLine(QLineF(20.0, 10.0, 20.0, -10.0));   //right line
        break;
    }
    case Helicopter: {
        painter->setPen(QPen(Qt::red, 2));
        painter->drawLine(QLineF(0.0, 37.5, 10.0, 27.5));    //bottom left - top right, small propeller
        painter->drawLine(QLineF(0.0, 27.5, 10.0, 37.5));    //top left - bottom right, small propeller
        painter->drawLine(QLineF(0.0, 27.5, 0.0, -4.0));    //tail
        painter->drawLine(QLineF(0.0, -4.0, 24.0, -28.0));    //bottom left - top right, big propeller
        painter->drawLine(QLineF(0.0, -28.0, 24.0, -4.0));    //top left - bottom right, big propeller
        QRectF cabinRect(-7.5, -28.0, 14.0, 24.0);
        int startAngle = 90 * 16;
        int spanAngle = 180 * 16;
        painter->drawArc(cabinRect, startAngle, spanAngle);    //cabin
        break;
    }
    case MotoPump_1: {
        painter->setPen(QPen(Qt::red, 1));
        painter->drawRect(-20.0, -30.0, 40.0, 60.0);
        painter->drawLine(-10.0, 30.0, -10.0, 20.0);    //left pump line
        painter->drawLine(-10.0, 20.0, 10.0, 20.0); //horizontal pump line
        painter->drawLine(10.0, 20.0, 10.0, 30.0); //right pump line
        break;
    }
    case MotoPump_2: {
        painter->setPen(QPen(Qt::red, 1));
        painter->drawRect(-20.0, -30.0, 40.0, 60.0);
        painter->drawLine(-10.0, 30.0, -10.0, 20.0);    //left pump line
        painter->drawLine(-10.0, 20.0, 10.0, 20.0); //horizontal pump line
        painter->drawLine(10.0, 20.0, 10.0, 30.0); //right pump line
        painter->drawLine(-25.0, 30.0, -20.0, 30.0); //left axle
        painter->drawLine(-25.0, 35.0, -25.0, 25.0); //left cartwheel
        painter->drawLine(20.0, 30.0, 25.0, 30.0); //right axle
        painter->drawLine(25.0, 35.0, 25.0, 25.0); //right cartwheel
        break;
    }
    case TrailerPowder: {
        painter->setPen(QPen(Qt::red, 1));
        painter->drawRect(-20.0, -30.0, 40.0, 60.0);
        painter->drawLine(-25.0, 30.0, -20.0, 30.0); //left axle
        painter->drawLine(-25.0, 35.0, -25.0, 25.0); //left cartwheel
        painter->drawLine(20.0, 30.0, 25.0, 30.0); //right axle
        painter->drawLine(25.0, 35.0, 25.0, 25.0); //right cartwheel
        painter->setBrush(QBrush(Qt::red));
        painter->drawRect(-10.0, -10.0, 20.0, 20.0);
        break;
    }
    case Adapted: {
        painter->setPen(QPen(Qt::blue, 1));
        painter->drawPolygon(autoBase);
        QPolygonF adaptedPolygon;
        adaptedPolygon << QPointF(-8.0, 36.5) << QPointF(-8.0, -22.5) << QPointF(0.0, -36.0)
                       << QPointF(8.0, -22.5) << QPointF(8.0, 36.5);
        painter->setPen(QPen(Qt::red, 1));
        painter->setBrush(QBrush(Qt::red));
        painter->drawPolygon(adaptedPolygon);
        break;
    }
    case OtherAdapted: {
        painter->setPen(QPen(Qt::blue, 1));
        painter->drawRect(QRectF(-15.0, -10.0, 30.0, 41));
        painter->drawLine(QLineF(0.0, -10.0, 0.0, -30.0));
        painter->drawEllipse(QRectF(-4.0, -38.0, 8.0, 8.0));
        painter->setPen(QPen(Qt::red, 1));
        painter->setBrush(QBrush(Qt::red));
        painter->drawRect(QRectF(-8.0, -9.0, 16.0, 39.0));
        break;
    }
    case Ambulance: {
        painter->setPen(QPen(Qt::black, 1));
        painter->drawPolygon(autoBase);
        QPolygonF ambulancePolygon;
        ambulancePolygon << QPointF(-3.0, 9.0) << QPointF(-3.0, 3.0) << QPointF(-9.0, 3.0)
                         << QPointF(-9.0, -3.0) << QPointF(-3.0, -3.0) << QPointF(-3.0, -9.0)
                         << QPointF(3.0, -9.0) << QPointF(3.0, -3.0) << QPointF(9.0, -3.0)
                         << QPointF(9.0, 3.0) << QPointF(3.0, 3.0) << QPointF(3.0, 9.0);
        painter->setPen(QPen(Qt::red, 1));
        painter->setBrush(QBrush(Qt::red));
        painter->drawPolygon(ambulancePolygon);
        break;
    }
    case Police: {
        painter->setPen(QPen(Qt::black, 1));
        painter->drawPolygon(autoBase);
        painter->rotate(-90);
        painter->drawText(QPointF(-32.0, 4.0), "МВД");
        break;
    }
    default:
        break;
    }
}

QPixmap TechnicsShape::image()
{
    QPixmap pixmap(boundingRect().width(), boundingRect().height());
    pixmap.fill(Qt::transparent);
    QPainter painter(&pixmap);
    painter.translate(boundingRect().width() / 2.0, boundingRect().height() / 2.0);
    drawShape(&painter);

    return pixmap;
}

TechnicsShape::ShapeType TechnicsShape::shapeType() const
{
    return m_shapeType;
}
