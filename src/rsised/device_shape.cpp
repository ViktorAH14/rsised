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

#include "device_shape.h"

#include <QPainter>

DeviceShape::DeviceShape(QMenu *contextMenu, ShapeType shapeType, QGraphicsItem *parent)
    : AbstractShape(contextMenu, parent)
    , m_shapeType{shapeType}
{
    setFlag(ItemSendsGeometryChanges, true);
    setAcceptHoverEvents(true);
}

void DeviceShape::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(option);
    Q_UNUSED(widget);

    drawShape(painter);
}

QRectF DeviceShape::boundingRect() const
{
    qreal penWidth {2.0};

    return QRectF(-32.0 - penWidth / 2.0, -45.0 - penWidth / 2.0
                  , 64.0 + penWidth, 90.0 + penWidth);
}

QPixmap DeviceShape::image()
{
    QPixmap pixmap(boundingRect().width(), boundingRect().height());
    pixmap.fill(Qt::transparent);
    QPainter painter(&pixmap);
    painter.translate(boundingRect().width() / 2.0, boundingRect().height() / 2.0);
    drawShape(&painter);

    return pixmap;
}

DeviceShape::ShapeType DeviceShape::shapeType() const
{
    return m_shapeType;
}

void DeviceShape::drawShape(QPainter *painter)
{
    painter->setRenderHint(QPainter::Antialiasing);
    painter->setRenderHint(QPainter::SmoothPixmapTransform);
    painter->setPen(QPen(Qt::black, 3));
    painter->setBrush(QBrush(Qt::white));

    switch (m_shapeType) {
    case Barrel_0: {
        painter->setPen(QPen(Qt::black, 2));
        painter->drawLine(QLineF(-4.0, 21.0, 4.0, 21.0));   //bottom line
        painter->drawLine(QLineF(0.0, 19.0, 0.0, -9.0));    //center line
        painter->drawLine(QLineF(-6.0, -5.0, 0.0, -11.0));  //left part of the arrow
        painter->drawLine(QLineF(0.0, -11.0, 6.0, -5.0));   //right part of the arrow
        break;
    }
    case Barrel_1: {
        painter->setPen(QPen(Qt::black, 2));
        painter->drawLine(QLineF(-4.0, 21.0, 4.0, 21.0));   //bottom line
        painter->drawLine(QLineF(0.0, 19.0, 0.0, -9.0));    //center line
        painter->drawLine(QLineF(-6.0, -5.0, 0.0, -11.0));  //left part of the arrow
        painter->drawLine(QLineF(0.0, -11.0, 6.0, -5.0));   //right part of the arrow
        painter->setBrush(QBrush(Qt::black));
        painter->drawEllipse(QPointF(0.0, -18.0), 3.0, 3.0);
        break;
    }
    case Barrel_2: {
        painter->setPen(QPen(Qt::black, 2));
        painter->drawLine(QLineF(-4.0, 24.5, 4.0, 24.5));   //bottom line
        painter->drawLine(QLineF(0.0, 22.5, 0.0, -5.5));    //center line
        painter->drawLine(QLineF(-6.0, -1.5, 0.0, -7.5));   //left part of the arrow
        painter->drawLine(QLineF(0.0, -7.5, 6.0, -1.5));    //right part of the arrow
        painter->setBrush(QBrush(Qt::black));
        painter->drawEllipse(QPointF(0.0, -13.5), 3.0, 3.0);
        painter->drawEllipse(QPointF(0.0, -21.5), 3.0, 3.0 );
        break;
    }
    case Barrel_3: {
        painter->setPen(QPen(Qt::black, 2));
        painter->drawLine(QLineF(-4.0, 24.5, 4.0, 24.5));   //bottom line
        painter->drawLine(QLineF(0.0, 22.5, 0.0, -5.5));    //center line
        painter->drawLine(QLineF(-6.0, -1.5, 0.0, -7.5));   //left part of the arrow
        painter->drawLine(QLineF(0.0, -7.5, 6.0, -1.5));    //right part of the arrow
        painter->setBrush(QBrush(Qt::black));
        painter->drawEllipse(QPointF(0.0, -13.5), 3.0, 3.0);
        painter->drawEllipse(QPointF(0.0, -21.5), 3.0, 3.0 );
        painter->drawEllipse(QPointF(0.0, -29.5), 3.0, 3.0);
        break;
    }
    case Barrel_4: {
        painter->setPen(QPen(Qt::black, 2));
        painter->drawLine(QLineF(-4.0, 24.5, 4.0, 24.5));   //bottom line
        painter->drawLine(QLineF(0.0, 22.5, 0.0, -5.5));    //center line
        painter->drawLine(QLineF(-6.0, -1.5, 0.0, -7.5));   //left part of the arrow
        painter->drawLine(QLineF(0.0, -7.5, 6.0, -1.5));    //right part of the arrow
        painter->setPen(QPen(Qt::black, 1));
        painter->drawEllipse(QPointF(0.0, -14.5), 5.0, 5.0);
        painter->drawLine(QLineF(-3.5, -11.0, 3.5, -18.0)); //inside ellipse, left bottom - right top
        painter->drawLine(QLineF(-3.5, -18.0, 3.5, -11.0)); //inside ellipse, left top - right botttom
        break;
    }
    case Barrel_5: {
        painter->setPen(QPen(Qt::black, 2));
        painter->drawLine(QLineF(-4.0, 24.5, 4.0, 24.5));   //bottom line
        painter->drawLine(QLineF(0.0, 22.5, 0.0, -5.5));    //center line
        painter->drawLine(QLineF(-6.0, -1.5, 0.0, -7.5));   //left part of the arrow
        painter->drawLine(QLineF(0.0, -7.5, 6.0, -1.5));    //right part of the arrow
        painter->setPen(QPen(Qt::black, 1));
        painter->drawEllipse(QPointF(0.0, -14.5), 5.0, 5.0);
        painter->drawEllipse(QPointF(0.0, -25.5), 5.0, 5.0);
        painter->drawLine(QLineF(-3.5, -11.0, 3.5, -18.0)); //inside ellipse 1, left bottom - right top
        painter->drawLine(QLineF(-3.5, -18.0, 3.5, -11.0)); //inside ellipse 1, left top - right botttom
        painter->drawLine(QLineF(-3.5, -22.0, 3.5, -29.0)); //inside ellipse 2, left bottom - right top
        painter->drawLine(QLineF(-3.5, -29.0, 3.5, -22.0)); //inside ellipse 2, left top - right botttom
        break;
    }
    case Barrel_6: {
        painter->setPen(QPen(Qt::black, 2));
        painter->drawLine(QLineF(-4.0, 21.0, 4.0, 21.0));   //bottom line
        painter->drawLine(QLineF(0.0, 19.0, 0.0, -9.0));    //center line
        painter->drawLine(QLineF(-6.0, -5.0, 0.0, -11.0));  //left part of the arrow
        painter->drawLine(QLineF(0.0, -11.0, 6.0, -5.0));   //right part of the arrow
        painter->setBrush(QBrush(Qt::black));
        painter->drawEllipse(QPointF(0.0, -18.0), 3.0, 3.0);
        painter->drawLine(QLineF(-4.5, -14.5, 4.5, -21.5)); //inside ellipse, left bottom - right top
        painter->drawLine(QLineF(-4.5, -21.5, 4.5, -14.5)); //inside ellipse, left top - right botttom
        break;
    }
    case Carriage_1:{
        painter->setPen(QPen(Qt::black, 2));
        painter->drawLine(QLineF(-4.0, 28.0, 4.0, 28.0));   //bottom line
        painter->drawLine(QLineF(0.0, 26.0, 0.0, -9.0));    //center line
        painter->drawLine(QLineF(-6.0, 10.0, 0.0, 10.0));    //stand
        painter->drawLine(QLineF(-6.0, -5.0, 0.0, -11.0));  //left part of the arrow
        painter->drawLine(QLineF(0.0, -11.0, 6.0, -5.0));   //right part of the arrow
        painter->setBrush(QBrush(Qt::black));
        painter->drawEllipse(QPointF(0.0, -18.0), 3.0, 3.0);
        break;
    }
    case Carriage_2: {
        painter->setPen(QPen(Qt::black, 2));
        painter->drawLine(QLineF(-4.0, 28.0, 4.0, 28.0));   //bottom line
        painter->drawLine(QLineF(0.0, 26.0, 0.0, -9.0));    //center line
        painter->drawLine(QLineF(-6.0, 12.0, 0.0, 12.0));    //stand_1
        painter->drawLine(QLineF(-6.0, 8.0, 0.0, 8.0));    //stand_2
        painter->drawLine(QLineF(-6.0, -5.0, 0.0, -11.0));  //left part of the arrow
        painter->drawLine(QLineF(0.0, -11.0, 6.0, -5.0));   //right part of the arrow
        painter->setBrush(QBrush(Qt::black));
        painter->drawEllipse(QPointF(0.0, -18.0), 3.0, 3.0);
        break;
    }
    case Carriage_3:{
        painter->setPen(QPen(Qt::black, 2));
        painter->drawLine(QLineF(-4.0, 28.0, 4.0, 28.0));   //bottom line
        painter->drawLine(QLineF(0.0, 26.0, 0.0, -9.0));    //center line
        painter->drawLine(QLineF(-6.0, 12.0, 0.0, 12.0));    //stand_1
        painter->drawLine(QLineF(-6.0, 8.0, 0.0, 8.0));    //stand_2
        painter->drawLine(QLineF(-6.0, -5.0, 0.0, -11.0));  //left part of the arrow
        painter->drawLine(QLineF(0.0, -11.0, 6.0, -5.0));   //right part of the arrow
        painter->setBrush(QBrush(Qt::black));
        painter->drawRect(QRectF(-4.0, -22.0, 8.0, 8.0));
        break;
    }
    case Carriage_4: {
        painter->setPen(QPen(Qt::black, 2));
        painter->drawLine(QLineF(-4.0, 28.0, 4.0, 28.0));   //bottom line
        painter->drawLine(QLineF(0.0, 26.0, 0.0, -9.0));    //center line
        painter->drawLine(QLineF(-6.0, 12.0, 0.0, 12.0));    //stand_1
        painter->drawLine(QLineF(-6.0, 8.0, 0.0, 8.0));    //stand_2
        painter->drawLine(QLineF(-6.0, -5.0, 0.0, -11.0));  //left part of the arrow
        painter->drawLine(QLineF(0.0, -11.0, 6.0, -5.0));   //right part of the arrow
        painter->setPen(QPen(Qt::black, 1));
        painter->drawEllipse(QPointF(0.0, -18.5), 5.0, 5.0);
        painter->drawLine(QLineF(-3.5, -15.0, 3.5, -22.0)); //inside ellipse, left bottom - right top
        painter->drawLine(QLineF(-3.5, -22.0, 3.5, -15.0)); //inside ellipse, left top - right botttom
        break;
    }
    case Carriage_5: {
        painter->setPen(QPen(Qt::black, 2));
        painter->drawLine(QLineF(-15.0, 15.0, 15.0, 15.0));   //bottom line
        painter->drawLine(QLineF(-15.0, 25.0, -15.0, 5.0));  //left line
        painter->drawLine(QLineF(15.0, 25.0, 15.0, 5.0));  //right line
        painter->drawLine(QLineF(0.0, 13.0, 0.0, -23.0));    //center line
        painter->drawLine(QLineF(-6.0, -18.0, 0.0, -24.0));  //left part of the arrow
        painter->drawLine(QLineF(0.0, -24.0, 6.0, -18.0));   //right part of the arrow
        painter->setPen(QPen(Qt::black, 3));
        painter->drawLine(QLineF(-6.0, -4.0, -2.0, -4.0));    //stand
        break;
    }
    case Branches_2: {
        painter->drawLine(QLineF(-4.0, 16.0, 4.0, 16.0));   //bottom line
        painter->drawLine(QLineF(0.0, 14.0, 0.0, 4.0));   //center line
        painter->drawLine(QLineF(-10.0, 4.0, 10.0, 4.0));   //central horizontal line
        painter->drawLine(QLineF(-10.0, 4.0, -10.0, -14.0));    //vertical line 1
        painter->drawLine(QLineF(-14.0, -16.0, -6.0, -16.0));  //top line 1
        painter->drawLine(QLineF(10.0, 4.0, 10.0, -14.0));  //vertical line 3
        painter->drawLine(QLineF(6.0, -16.0, 14.0, -16.0));    //top line 3
        break;
    }
    case Branches_3: {
        painter->drawLine(QLineF(-4.0, 16.0, 4.0, 16.0));   //bottom line
        painter->drawLine(QLineF(0.0, 14.0, 0.0, -14.0));   //center line
        painter->drawLine(QLineF(-16.0, 4.0, 16.0, 4.0));   //central horizontal line
        painter->drawLine(QLineF(-16.0, 4.0, -16.0, -14.0));    //vertical line 1
        painter->drawLine(QLineF(-20.0, -16.0, -12.0, -16.0));  //top line 1
        painter->drawLine(QLineF(-4.0, -16.0, 4.0, -16.0)); //top line 2
        painter->drawLine(QLineF(16.0, 4.0, 16.0, -14.0));  //vertical line 3
        painter->drawLine(QLineF(12.0, -16.0, 20.0, -16.0));    //top line3
        break;
    }
    case Branches_4: {
        painter->drawLine(QLineF(-4.0, 16.0, 4.0, 16.0));   //bottom line
        painter->drawLine(QLineF(0.0, 14.0, 0.0, 4.0));     //center line
        painter->drawLine(QLineF(-24.0, 4.0, 24.0, 4.0));   //central horizontal line
        painter->drawLine(QLineF(-24.0, 4.0, -24.0, -14.0));    //vertical line 1
        painter->drawLine(QLineF(-28.0, -16.0, -20.0, -16.0));  //top line 1
        painter->drawLine(QLineF(-8.0, 4.0, -8.0, -14.0));  //vertical line 2
        painter->drawLine(QLineF(-12.0, -16.0, -4.0, -16.0));   //top line 2
        painter->drawLine(QLineF(8.0, 4.0, 8.0, -14.0));    //vertical line 3
        painter->drawLine(QLineF(12.0, -16.0, 4.0, -16.0)); //top line 3
        painter->drawLine(QLineF(24.0, 4.0, 24.0, -14.0));  //vertical line 4
        painter->drawLine(QLineF(20.0, -16.0, 28.0, -16.0));    //top line 4
        break;
    }
    case Ladder_1: {
        painter->setPen(QPen(Qt::black, 1));
        painter->drawLine(QLineF(-15.0, 25.0, -15.0, -25.0));   //left line
        painter->drawLine(QLineF(15.0, 25.0, 15.0, -25.0)); //right line
        painter->drawLine(QLineF(-14.0, 20.0, 14.0, 25.0)); //step 1
        painter->drawLine(QLineF(-14.0, 15.0, 14.0, 20.0)); //step 2
        painter->drawLine(QLineF(-14.0, 10.0, 14.0, 15.0)); //step 3
        painter->drawLine(QLineF(-14.0, 5.0, 14.0, 10.0)); //step 4
        painter->drawLine(QLineF(-14.0, 0.0, 14.0, 5.0)); //step 5
        painter->drawLine(QLineF(-14.0, -5.0, 14.0, 0.0)); //step 6
        painter->drawLine(QLineF(-14.0, -10.0, 14.0, -5.0)); //step 7
        painter->drawLine(QLineF(-14.0, -15.0, 14.0, -10.0)); //step 8
        painter->drawLine(QLineF(-14.0, -20.0, 14.0, -15.0)); //step 9
        painter->drawLine(QLineF(-14.0, -25.0, 14.0, -20.0)); //step 10
        break;
    }
    case Ladder_2: {
        painter->setPen(QPen(Qt::black, 1));
        painter->drawLine(QLineF(-15.0, 40.0, -15.0, -15.0));   //left line
        painter->drawLine(QLineF(0.0, -10.0, 0.0, -30.0));   //center line
        painter->drawLine(QLineF(15.0, 40.0, 15.0, -15.0)); //right line
        painter->drawLine(QLineF(-14.0, 35.0, 14.0, 35.0)); //step 1
        painter->drawLine(QLineF(-14.0, 30.0, 14.0, 30.0)); //step 2
        painter->drawLine(QLineF(-14.0, 25.0, 14.0, 25.0)); //step 3
        painter->drawLine(QLineF(-14.0, 20.0, 14.0, 20.0)); //step 4
        painter->drawLine(QLineF(-14.0, 15.0, 14.0, 15.0)); //step 5
        painter->drawLine(QLineF(-14.0, 10.0, 14.0, 10.0)); //step 6
        painter->drawLine(QLineF(-14.0, 5.0, 14.0, 5.0)); //step 7
        painter->drawLine(QLineF(-14.0, 0.0, 14.0, 0.0)); //step 8
        painter->drawLine(QLineF(-14.0, -5.0, 14.0, -5.0)); //step 9
        painter->drawLine(QLineF(-14.0, -10.0, 14.0, -10.0)); //step 10
        break;
    }
    case Ladder_3: {
        painter->setPen(QPen(Qt::black, 1));
        painter->drawLine(QLineF(-15.0, 40.0, -15.0, -15.0));   //left line 1
        painter->drawLine(QLineF(15.0, 40.0, 15.0, -15.0)); //right line 1
        painter->drawLine(QLineF(-14.0, 35.0, 14.0, 35.0)); //step 1
        painter->drawLine(QLineF(-14.0, 30.0, 14.0, 30.0)); //step 2
        painter->drawLine(QLineF(-14.0, 25.0, 14.0, 25.0)); //step 3
        painter->drawLine(QLineF(-14.0, 20.0, 14.0, 20.0)); //step 4
        painter->drawLine(QLineF(-14.0, 15.0, 14.0, 15.0)); //step 5
        painter->drawLine(QLineF(-14.0, 10.0, 14.0, 10.0)); //step 6
        painter->drawLine(QLineF(-14.0, 5.0, 14.0, 5.0)); //step 7
        painter->drawLine(QLineF(-14.0, 0.0, 14.0, 0.0)); //step 8
        painter->drawLine(QLineF(-14.0, -5.0, 14.0, -5.0)); //step 9
        painter->drawLine(QLineF(-14.0, -10.0, 14.0, -10.0)); //step 10
        painter->drawLine(QLineF(-10.0, -10.0, -10.0, -43.0));  //left line 2
        painter->drawLine(QLineF(10.0, -10.0, 10.0, -43.0));  //right line 2
        painter->drawLine(QLineF(-9.0, -13.0, 9.0, -13.0));  //step 11
        painter->drawLine(QLineF(-9.0, -16.0, 9.0, -16.0));  //step 12
        painter->drawLine(QLineF(-9.0, -19.0, 9.0, -19.0));  //step 13
        painter->drawLine(QLineF(-9.0, -22.0, 9.0, -22.0));  //step 14
        painter->drawLine(QLineF(-9.0, -25.0, 9.0, -25.0));  //step 15
        painter->drawLine(QLineF(-9.0, -28.0, 9.0, -28.0));  //step 16
        painter->drawLine(QLineF(-9.0, -31.0, 9.0, -31.0));  //step 17
        painter->drawLine(QLineF(-9.0, -34.0, 9.0, -34.0));  //step 18
        painter->drawLine(QLineF(-9.0, -37.0, 9.0, -37.0));  //step 19
        painter->drawLine(QLineF(-9.0, -40.0, 9.0, -40.0));  //step 20
        break;
    }
    case Collector: {
        painter->drawLine(QLineF(-4.0, 16.0, 4.0, 16.0));   //bottom line
        painter->drawLine(QLineF(0.0, 14.0, 0.0, -2.0));    //center line
        painter->drawLine(QLineF(0.0, -2.0, -12.0, -14.0)); //left line
        painter->drawLine(QLineF(0.0, -2.0, 12.0, -14.0));  //right line
        painter->drawLine(QLineF(-17.0, -11.0, -8.0, -17.0));   //left top
        painter->drawLine(QLineF(17.0, -11.0, 8.0, -17.0)); //right top
        break;
    }
    case Bridge: {
        painter->setPen(QPen(Qt::black, 2));
        painter->drawLine(QLineF(-28.0, 10.0, -14.0, -10.0));   //left line
        painter->drawLine(QLineF(-14.0, -10.0, 14.0, -10.0));     //horizontal center line
        painter->drawLine(QLineF(14.0, -10.0, 28.0, 10.0));     //right line
        break;
    }
    case Reel: {
        painter->setPen(QPen(Qt::black, 2));
        painter->drawLine(QLineF(-28.0, 10.0, -28.0, -10.0));   //left line
        painter->drawLine(QLineF(-28.0, 0.0, 28.0, 0.0));   //horizontal center line
        painter->drawLine(QLineF(28.0, 10.0, 28.0, -10.0)); //right line
        break;
    }
    case Reel_mobile: {
        painter->setPen(QPen(Qt::black, 2));
        painter->drawLine(QLineF(-28.0, 10.0, -28.0, -10.0));   //left line
        painter->drawLine(QLineF(-28.0, 0.0, 28.0, 0.0));   //horizontal center line
        painter->drawLine(QLineF(0.0, 0.0, 0.0, -10.0));    //vertical center line
        painter->drawLine(QLineF(28.0, 10.0, 28.0, -10.0)); //righ line
        break;
    }
    case HydrElevator: {
        painter->setPen(QPen(Qt::black, 1));
        painter->setBrush(QBrush(Qt::white));
        painter->drawLine(QLineF(-28.0, 0.0, 28.0, 0.0));   //center line
        painter->drawLine(QLineF(28.0, 4.0, 28.0, -4.0));   //vertical line 3
        painter->drawEllipse(QPointF(19.0, 0.0), 5.0, 5.0);
        painter->drawLine(QLineF(19.0, -5.0, 19.0, -10.0)); //vertical line 2
        painter->drawLine(QLineF(15.0, -10.0, 23.0, -10.0));    //right horizontal top line
        painter->drawLine(QLineF(-18.0, 10.0, -18.0, -10.0));   //vertical line 1
        painter->drawLine(QLineF(-18.0, -10.0, 14.0, -2.0));    //left horizontal top line
        painter->drawLine(QLineF(-18.0, 10.0, 14.0, 2.0));  //bottom line
        break;
    }
    case Foam_mix: {
        painter->setPen(QPen(Qt::black, 1));
        painter->setBrush(QBrush(Qt::white));
        painter->drawLine(QLineF(-28.0, 0.0, 28.0, 0.0));   //center line
        painter->drawLine(QLineF(28.0, 4.0, 28.0, -4.0));   //vertical line 3
        painter->drawEllipse(QPointF(19.0, 0.0), 5.0, 5.0);
        painter->drawLine(QLineF(19.0, -5.0, 19.0, -10.0)); //vertical line 2
        painter->drawLine(QLineF(15.0, -10.0, 23.0, -10.0));    //right horizontal top line
        painter->drawLine(QLineF(-18.0, 10.0, -18.0, -10.0));   //vertical line 1
        painter->drawLine(QLineF(-18.0, -10.0, 14.0, -2.0));    //left horizontal top line
        painter->drawLine(QLineF(-18.0, 10.0, 14.0, 2.0));  //bottom line
        painter->drawEllipse(QPointF(-9.0, 0.0), 5.0, 5.0);
        painter->drawLine(QLineF(-12.5, 3.5, -5.5, -3.5)); //inside ellipse, left bottom - right top
        painter->drawLine(QLineF(-12.5, -3.5, -5.5, 3.5)); //inside ellipse, left top - right botttom
        break;
    }
    case Column: {
        painter->drawLine(QLineF(0.0, 20.0, 0.0, -20.0));    //center line
        painter->drawLine(QLineF(-18.0, -10.0, 0.0, -21.0));  //left part of the arrow
        painter->drawLine(QLineF(0.0, -21.0, 18.0, -10.0));   //right part of the arrow
        painter->drawLine(QLineF(-19.5, -12.0, -16.5, -8.0));    //left connection
        painter->drawLine(QLineF(16.5, -8.0, 19.5, -12.0));  //right connection
        break;
    }
    case SmokePump_1: {
        painter->setPen(QPen(Qt::black, 1));
        painter->drawEllipse(QPointF(0.0, 0.0), 15.0, 15.0);
        painter->drawLine(QLineF(-12.0, 8.0, 12.0, -8.0));  //inside ellipse, left bottom - right top
        painter->drawLine(QLineF(12.0, -8.0, -2.0, -14.0));  //inside ellipse top
        painter->drawLine(QLineF(-2.0, -14.0, 2.0, 14.0));  //inside ellipse, left top - right bottom
        painter->drawLine(QLineF(2.0, 14.0, -12.0, 8.0));  //inside ellipse bottom
        break;
    }
    case SmokePump_2: {
        painter->setPen(QPen(Qt::black, 1));
        painter->drawEllipse(QPointF(0.0, 0.0), 15.0, 15.0);
        painter->drawLine(QLineF(-12.0, 8.0, 12.0, -8.0));  //inside ellipse, left bottom - right top
        painter->drawLine(QLineF(12.0, -8.0, -2.0, -14.0));  //inside ellipse top
        painter->drawLine(QLineF(-2.0, -14.0, 2.0, 14.0));  //inside ellipse, left top - right bottom
        painter->drawLine(QLineF(2.0, 14.0, -12.0, 8.0));  //inside ellipse bottom
        painter->drawLine(QLineF(-16.0, 15.0, -16.0, -15.0));  //left line
        painter->drawLine(QLineF(16.0, 15.0, 16.0, -15.0));  //right line
        break;
    }
    case Hose: {
        painter->setPen(QPen(Qt::black, 2));
        painter->drawLine(QLineF(0.0, 45.0, 0.0, -40.0));   //center line
        painter->drawLine(QLineF(-4.0, 40.0, 4.0, 40.0));   //line 1
        painter->drawLine(QLineF(-4.0, 35.0, 4.0, 35.0));   //line 2
        painter->drawLine(QLineF(-4.0, 30.0, 4.0, 30.0));   //line 3
        painter->drawLine(QLineF(-4.0, 25.0, 4.0, 25.0));   //line 4
        painter->drawLine(QLineF(-4.0, 20.0, 4.0, 20.0));   //line 5
        painter->drawLine(QLineF(-4.0, 15.0, 4.0, 15.0));   //line 6
        painter->drawLine(QLineF(-4.0, 10.0, 4.0, 10.0));   //line 7
        painter->drawLine(QLineF(-4.0, 5.0, 4.0, 5.0));   //line 8
        painter->drawLine(QLineF(-4.0, 0.0, 4.0, 0.0));   //line 9
        painter->drawLine(QLineF(-4.0, -5.0, 4.0, -5.0));   //line 10
        painter->drawLine(QLineF(-4.0, -10.0, 4.0, -10.0));   //line 11
        painter->drawLine(QLineF(-4.0, -15.0, 4.0, -15.0));   //line 12
        painter->drawLine(QLineF(-4.0, -20.0, 4.0, -20.0));   //line 13
        painter->drawLine(QLineF(-4.0, -25.0, 4.0, -25.0));   //line 14
        painter->drawLine(QLineF(-4.0, -30.0, 4.0, -30.0));   //line 15
        painter->drawLine(QLineF(-4.0, -35.0, 4.0, -35.0));   //line 16
        painter->drawLine(QLineF(-4.0, -40.0, 4.0, -40.0));   //line 17
        break;
    }
    case FoamLift_1: {
        painter->setPen(QPen(Qt::black, 2));
        painter->drawLine(QLineF(14.0, 40.0, 22.0, 40.0));   //botoom line
        QPainterPath arcPath;
        arcPath.moveTo(18.0, 40.0);
        arcPath.quadTo(20.0, -28.0, -10.0, -20.0);
        painter->drawPath(arcPath);
        painter->drawLine(QLineF(13.0, 11.0, 20.0, 10.0));   //center line
        painter->setPen(QPen(Qt::black, 1));
        painter->drawEllipse(QPointF(-15.0, -20.0), 5.0, 5.0);
        painter->drawLine(QLineF(-18.5, -16.5, -11.5, -23.5)); //inside ellipse, left bottom - right top
        painter->drawLine(QLineF(-18.5, -23.5, -11.5, -16.5)); //inside ellipse, left top - right botttom
        break;
    }
    case FoamLift_2: {
        painter->setPen(QPen(Qt::black, 1));
        painter->drawEllipse(QPointF(-25.0, -36.0), 5.0, 5.0);
        painter->drawLine(QLineF(-28.5, -32.5, -21.5, -39.5));  //inside ellipse 1, left bottom - right top
        painter->drawLine(QLineF(-28.5, -39.5, -21.5, -32.5));  //inside ellipse 1, left top - right botttom
        painter->drawEllipse(QPointF(-25.0, -25.0), 5.0, 5.0);
        painter->drawLine(QLineF(-28.5, -21.5, -21.5, -28.5));  //inside ellipse 2, left bottom - right top
        painter->drawLine(QLineF(-28.5, -28.5, -21.5, -21.5));  //inside ellipse 2, left top - right botttom
        painter->drawEllipse(QPointF(25.0, -36.0), 5.0, 5.0);
        painter->drawLine(QLineF(21.5, -32.5, 28.5, -39.5));    //inside ellipse 3, left bottom - right top
        painter->drawLine(QLineF(21.5, -39.5, 28.5, -32.5));    //inside ellipse 3, left top - right botttom
        painter->drawEllipse(QPointF(25.0, -25.0), 5.0, 5.0);
        painter->drawLine(QLineF(21.5, -21.5, 28.5, -28.5));    //inside ellipse 4, left bottom - right top
        painter->drawLine(QLineF(21.5, -28.5, 28.5, -21.5));    //inside ellipse 4, left top - right botttom
        painter->setPen(QPen(Qt::black, 2));
        painter->drawLine(QLineF(-25.0, -20.0, -25.0, 0.0));    //left branch
        painter->drawLine(QLineF(-31.0, -14.0, -25.0, -20.0));  //left branch, left part of the arrow
        painter->drawLine(QLineF(-25.0, -20.0, -19.0, -14.0));   //left branch, right part of the arrow
        painter->drawLine(QLineF(25.0, -20.0, 25.0, 0.0));   //right branch
        painter->drawLine(QLineF(19.0, -14.0, 25.0, -20.0));   //right branch, left part of the arrow
        painter->drawLine(QLineF(25.0, -20.0, 31.0, -14.0));   //right branch, right part of the arrow
        painter->drawLine(QLineF(-25.0, 0.0, 25.0, 0.0));   //horizontal central line
        painter->drawLine(QLineF(0.0, 0.0, -25.0, 40.0));   //vertical central line
        painter->drawLine(QLineF(-29.0, 38.0, -21.0, 42.0));   //bottom line
        painter->drawLine(QLineF(-19.5, 23.0, -11.5, 27.0));   //stand
        break;
    }
    default:
        break;
    }
}
