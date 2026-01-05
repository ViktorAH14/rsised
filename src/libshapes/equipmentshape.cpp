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

#include "../include/equipmentshape.h"

#include <QPainter>
#include <QStyleOptionGraphicsItem>
#include <QGraphicsSceneEvent>
#include <QMenu>
#include <QDebug>

// # define M_PIl 3.141592653589793238462643383279502884L /* pi */
#include <cmath>

EquipmentShape::EquipmentShape(QGraphicsItem *parent) : AbstractShape(parent)
{
}

EquipmentShape::~EquipmentShape() = default;

void EquipmentShape::deleter()
{
    delete this;
}

EquipmentShape *EquipmentShape::createEquipmentShape(ShapeType shapeType, QGraphicsItem *parent)
{
    EquipmentShape *p_equipmentShape{nullptr};
    switch (shapeType) {
    case Nosepiece:
        p_equipmentShape = new NosepieceShape(parent);
        break;
    default:
        break;
    }
    return p_equipmentShape;
}

// void EquipmentShape::drawShape(QPainter *painter)
// {
//     painter->setRenderHint(QPainter::Antialiasing);
//     painter->setRenderHint(QPainter::SmoothPixmapTransform);
//     painter->setPen(QPen(Qt::black, 3));
//     painter->setBrush(QBrush(Qt::white));

//     switch (m_shapeType) {
//     case Barrel_0: {
//         painter->setPen(QPen(Qt::black, 2));
//         painter->drawLine(QLineF(-4.0, 21.0, 4.0, 21.0));   //bottom line
//         painter->drawLine(QLineF(0.0, 19.0, 0.0, -9.0));    //center line
//         painter->drawLine(QLineF(-6.0, -5.0, 0.0, -11.0));  //left part of the arrow
//         painter->drawLine(QLineF(0.0, -11.0, 6.0, -5.0));   //right part of the arrow
//         break;
//     }
//     case Barrel_1: {
//         painter->setPen(QPen(Qt::black, 2));
//         painter->drawLine(QLineF(-4.0, 21.0, 4.0, 21.0));   //bottom line
//         painter->drawLine(QLineF(0.0, 19.0, 0.0, -9.0));    //center line
//         painter->drawLine(QLineF(-6.0, -5.0, 0.0, -11.0));  //left part of the arrow
//         painter->drawLine(QLineF(0.0, -11.0, 6.0, -5.0));   //right part of the arrow
//         painter->setBrush(QBrush(Qt::black));
//         painter->drawEllipse(QPointF(0.0, -18.0), 3.0, 3.0);
//         break;
//     }
//     case Barrel_2: {
//         painter->setPen(QPen(Qt::black, 2));
//         painter->drawLine(QLineF(-4.0, 24.5, 4.0, 24.5));   //bottom line
//         painter->drawLine(QLineF(0.0, 22.5, 0.0, -5.5));    //center line
//         painter->drawLine(QLineF(-6.0, -1.5, 0.0, -7.5));   //left part of the arrow
//         painter->drawLine(QLineF(0.0, -7.5, 6.0, -1.5));    //right part of the arrow
//         painter->setBrush(QBrush(Qt::black));
//         painter->drawEllipse(QPointF(0.0, -13.5), 3.0, 3.0);
//         painter->drawEllipse(QPointF(0.0, -21.5), 3.0, 3.0 );
//         break;
//     }
//     case Barrel_3: {
//         painter->setPen(QPen(Qt::black, 2));
//         painter->drawLine(QLineF(-4.0, 24.5, 4.0, 24.5));   //bottom line
//         painter->drawLine(QLineF(0.0, 22.5, 0.0, -5.5));    //center line
//         painter->drawLine(QLineF(-6.0, -1.5, 0.0, -7.5));   //left part of the arrow
//         painter->drawLine(QLineF(0.0, -7.5, 6.0, -1.5));    //right part of the arrow
//         painter->setBrush(QBrush(Qt::black));
//         painter->drawEllipse(QPointF(0.0, -13.5), 3.0, 3.0);
//         painter->drawEllipse(QPointF(0.0, -21.5), 3.0, 3.0 );
//         painter->drawEllipse(QPointF(0.0, -29.5), 3.0, 3.0);
//         break;
//     }
//     case Barrel_4: {
//         painter->setPen(QPen(Qt::black, 2));
//         painter->drawLine(QLineF(-4.0, 24.5, 4.0, 24.5));   //bottom line
//         painter->drawLine(QLineF(0.0, 22.5, 0.0, -5.5));    //center line
//         painter->drawLine(QLineF(-6.0, -1.5, 0.0, -7.5));   //left part of the arrow
//         painter->drawLine(QLineF(0.0, -7.5, 6.0, -1.5));    //right part of the arrow
//         painter->setPen(QPen(Qt::black, 1));
//         painter->drawEllipse(QPointF(0.0, -14.5), 5.0, 5.0);
//         painter->drawLine(QLineF(-3.5, -11.0, 3.5, -18.0)); //inside ellipse, left bottom - right top
//         painter->drawLine(QLineF(-3.5, -18.0, 3.5, -11.0)); //inside ellipse, left top - right botttom
//         break;
//     }
//     case Barrel_5: {
//         painter->setPen(QPen(Qt::black, 2));
//         painter->drawLine(QLineF(-4.0, 24.5, 4.0, 24.5));   //bottom line
//         painter->drawLine(QLineF(0.0, 22.5, 0.0, -5.5));    //center line
//         painter->drawLine(QLineF(-6.0, -1.5, 0.0, -7.5));   //left part of the arrow
//         painter->drawLine(QLineF(0.0, -7.5, 6.0, -1.5));    //right part of the arrow
//         painter->setPen(QPen(Qt::black, 1));
//         painter->drawEllipse(QPointF(0.0, -14.5), 5.0, 5.0);
//         painter->drawEllipse(QPointF(0.0, -25.5), 5.0, 5.0);
//         painter->drawLine(QLineF(-3.5, -11.0, 3.5, -18.0)); //inside ellipse 1, left bottom - right top
//         painter->drawLine(QLineF(-3.5, -18.0, 3.5, -11.0)); //inside ellipse 1, left top - right botttom
//         painter->drawLine(QLineF(-3.5, -22.0, 3.5, -29.0)); //inside ellipse 2, left bottom - right top
//         painter->drawLine(QLineF(-3.5, -29.0, 3.5, -22.0)); //inside ellipse 2, left top - right botttom
//         break;
//     }
//     case Barrel_6: {
//         painter->setPen(QPen(Qt::black, 2));
//         painter->drawLine(QLineF(-4.0, 21.0, 4.0, 21.0));   //bottom line
//         painter->drawLine(QLineF(0.0, 19.0, 0.0, -9.0));    //center line
//         painter->drawLine(QLineF(-6.0, -5.0, 0.0, -11.0));  //left part of the arrow
//         painter->drawLine(QLineF(0.0, -11.0, 6.0, -5.0));   //right part of the arrow
//         painter->setBrush(QBrush(Qt::black));
//         painter->drawEllipse(QPointF(0.0, -18.0), 3.0, 3.0);
//         painter->drawLine(QLineF(-4.5, -14.5, 4.5, -21.5)); //inside ellipse, left bottom - right top
//         painter->drawLine(QLineF(-4.5, -21.5, 4.5, -14.5)); //inside ellipse, left top - right botttom
//         break;
//     }
//     case Carriage_1:{
//         painter->setPen(QPen(Qt::black, 2));
//         painter->drawLine(QLineF(-4.0, 28.0, 4.0, 28.0));   //bottom line
//         painter->drawLine(QLineF(0.0, 26.0, 0.0, -9.0));    //center line
//         painter->drawLine(QLineF(-6.0, 10.0, 0.0, 10.0));    //stand
//         painter->drawLine(QLineF(-6.0, -5.0, 0.0, -11.0));  //left part of the arrow
//         painter->drawLine(QLineF(0.0, -11.0, 6.0, -5.0));   //right part of the arrow
//         painter->setBrush(QBrush(Qt::black));
//         painter->drawEllipse(QPointF(0.0, -18.0), 3.0, 3.0);
//         break;
//     }
//     case Carriage_2: {
//         painter->setPen(QPen(Qt::black, 2));
//         painter->drawLine(QLineF(-4.0, 28.0, 4.0, 28.0));   //bottom line
//         painter->drawLine(QLineF(0.0, 26.0, 0.0, -9.0));    //center line
//         painter->drawLine(QLineF(-6.0, 12.0, 0.0, 12.0));    //stand_1
//         painter->drawLine(QLineF(-6.0, 8.0, 0.0, 8.0));    //stand_2
//         painter->drawLine(QLineF(-6.0, -5.0, 0.0, -11.0));  //left part of the arrow
//         painter->drawLine(QLineF(0.0, -11.0, 6.0, -5.0));   //right part of the arrow
//         painter->setBrush(QBrush(Qt::black));
//         painter->drawEllipse(QPointF(0.0, -18.0), 3.0, 3.0);
//         break;
//     }
//     case Carriage_3:{
//         painter->setPen(QPen(Qt::black, 2));
//         painter->drawLine(QLineF(-4.0, 28.0, 4.0, 28.0));   //bottom line
//         painter->drawLine(QLineF(0.0, 26.0, 0.0, -9.0));    //center line
//         painter->drawLine(QLineF(-6.0, 12.0, 0.0, 12.0));    //stand_1
//         painter->drawLine(QLineF(-6.0, 8.0, 0.0, 8.0));    //stand_2
//         painter->drawLine(QLineF(-6.0, -5.0, 0.0, -11.0));  //left part of the arrow
//         painter->drawLine(QLineF(0.0, -11.0, 6.0, -5.0));   //right part of the arrow
//         painter->setBrush(QBrush(Qt::black));
//         painter->drawRect(QRectF(-4.0, -22.0, 8.0, 8.0));
//         break;
//     }
//     case Carriage_4: {
//         painter->setPen(QPen(Qt::black, 2));
//         painter->drawLine(QLineF(-4.0, 28.0, 4.0, 28.0));   //bottom line
//         painter->drawLine(QLineF(0.0, 26.0, 0.0, -9.0));    //center line
//         painter->drawLine(QLineF(-6.0, 12.0, 0.0, 12.0));    //stand_1
//         painter->drawLine(QLineF(-6.0, 8.0, 0.0, 8.0));    //stand_2
//         painter->drawLine(QLineF(-6.0, -5.0, 0.0, -11.0));  //left part of the arrow
//         painter->drawLine(QLineF(0.0, -11.0, 6.0, -5.0));   //right part of the arrow
//         painter->setPen(QPen(Qt::black, 1));
//         painter->drawEllipse(QPointF(0.0, -18.5), 5.0, 5.0);
//         painter->drawLine(QLineF(-3.5, -15.0, 3.5, -22.0)); //inside ellipse, left bottom - right top
//         painter->drawLine(QLineF(-3.5, -22.0, 3.5, -15.0)); //inside ellipse, left top - right botttom
//         break;
//     }
//     case Carriage_5: {
//         painter->setPen(QPen(Qt::black, 2));
//         painter->drawLine(QLineF(-15.0, 15.0, 15.0, 15.0));   //bottom line
//         painter->drawLine(QLineF(-15.0, 25.0, -15.0, 5.0));  //left line
//         painter->drawLine(QLineF(15.0, 25.0, 15.0, 5.0));  //right line
//         painter->drawLine(QLineF(0.0, 13.0, 0.0, -23.0));    //center line
//         painter->drawLine(QLineF(-6.0, -18.0, 0.0, -24.0));  //left part of the arrow
//         painter->drawLine(QLineF(0.0, -24.0, 6.0, -18.0));   //right part of the arrow
//         painter->setPen(QPen(Qt::black, 3));
//         painter->drawLine(QLineF(-6.0, -4.0, -2.0, -4.0));    //stand
//         break;
//     }
//     case Branches_2: {
//         painter->drawLine(QLineF(-4.0, 16.0, 4.0, 16.0));   //bottom line
//         painter->drawLine(QLineF(0.0, 14.0, 0.0, 4.0));   //center line
//         painter->drawLine(QLineF(-10.0, 4.0, 10.0, 4.0));   //central horizontal line
//         painter->drawLine(QLineF(-10.0, 4.0, -10.0, -14.0));    //vertical line 1
//         painter->drawLine(QLineF(-14.0, -16.0, -6.0, -16.0));  //top line 1
//         painter->drawLine(QLineF(10.0, 4.0, 10.0, -14.0));  //vertical line 3
//         painter->drawLine(QLineF(6.0, -16.0, 14.0, -16.0));    //top line 3
//         break;
//     }
//     case Branches_3: {
//         painter->drawLine(QLineF(-4.0, 16.0, 4.0, 16.0));   //bottom line
//         painter->drawLine(QLineF(0.0, 14.0, 0.0, -14.0));   //center line
//         painter->drawLine(QLineF(-16.0, 4.0, 16.0, 4.0));   //central horizontal line
//         painter->drawLine(QLineF(-16.0, 4.0, -16.0, -14.0));    //vertical line 1
//         painter->drawLine(QLineF(-20.0, -16.0, -12.0, -16.0));  //top line 1
//         painter->drawLine(QLineF(-4.0, -16.0, 4.0, -16.0)); //top line 2
//         painter->drawLine(QLineF(16.0, 4.0, 16.0, -14.0));  //vertical line 3
//         painter->drawLine(QLineF(12.0, -16.0, 20.0, -16.0));    //top line3
//         break;
//     }
//     case Branches_4: {
//         painter->drawLine(QLineF(-4.0, 16.0, 4.0, 16.0));   //bottom line
//         painter->drawLine(QLineF(0.0, 14.0, 0.0, 4.0));     //center line
//         painter->drawLine(QLineF(-24.0, 4.0, 24.0, 4.0));   //central horizontal line
//         painter->drawLine(QLineF(-24.0, 4.0, -24.0, -14.0));    //vertical line 1
//         painter->drawLine(QLineF(-28.0, -16.0, -20.0, -16.0));  //top line 1
//         painter->drawLine(QLineF(-8.0, 4.0, -8.0, -14.0));  //vertical line 2
//         painter->drawLine(QLineF(-12.0, -16.0, -4.0, -16.0));   //top line 2
//         painter->drawLine(QLineF(8.0, 4.0, 8.0, -14.0));    //vertical line 3
//         painter->drawLine(QLineF(12.0, -16.0, 4.0, -16.0)); //top line 3
//         painter->drawLine(QLineF(24.0, 4.0, 24.0, -14.0));  //vertical line 4
//         painter->drawLine(QLineF(20.0, -16.0, 28.0, -16.0));    //top line 4
//         break;
//     }
//     case Ladder_1: {
//         painter->setPen(QPen(Qt::black, 1));
//         painter->drawLine(QLineF(-15.0, 25.0, -15.0, -25.0));   //left line
//         painter->drawLine(QLineF(15.0, 25.0, 15.0, -25.0)); //right line
//         painter->drawLine(QLineF(-14.0, 20.0, 14.0, 25.0)); //step 1
//         painter->drawLine(QLineF(-14.0, 15.0, 14.0, 20.0)); //step 2
//         painter->drawLine(QLineF(-14.0, 10.0, 14.0, 15.0)); //step 3
//         painter->drawLine(QLineF(-14.0, 5.0, 14.0, 10.0)); //step 4
//         painter->drawLine(QLineF(-14.0, 0.0, 14.0, 5.0)); //step 5
//         painter->drawLine(QLineF(-14.0, -5.0, 14.0, 0.0)); //step 6
//         painter->drawLine(QLineF(-14.0, -10.0, 14.0, -5.0)); //step 7
//         painter->drawLine(QLineF(-14.0, -15.0, 14.0, -10.0)); //step 8
//         painter->drawLine(QLineF(-14.0, -20.0, 14.0, -15.0)); //step 9
//         painter->drawLine(QLineF(-14.0, -25.0, 14.0, -20.0)); //step 10
//         break;
//     }
//     case Ladder_2: {
//         painter->setPen(QPen(Qt::black, 1));
//         painter->drawLine(QLineF(-15.0, 40.0, -15.0, -15.0));   //left line
//         painter->drawLine(QLineF(0.0, -10.0, 0.0, -30.0));   //center line
//         painter->drawLine(QLineF(15.0, 40.0, 15.0, -15.0)); //right line
//         painter->drawLine(QLineF(-14.0, 35.0, 14.0, 35.0)); //step 1
//         painter->drawLine(QLineF(-14.0, 30.0, 14.0, 30.0)); //step 2
//         painter->drawLine(QLineF(-14.0, 25.0, 14.0, 25.0)); //step 3
//         painter->drawLine(QLineF(-14.0, 20.0, 14.0, 20.0)); //step 4
//         painter->drawLine(QLineF(-14.0, 15.0, 14.0, 15.0)); //step 5
//         painter->drawLine(QLineF(-14.0, 10.0, 14.0, 10.0)); //step 6
//         painter->drawLine(QLineF(-14.0, 5.0, 14.0, 5.0)); //step 7
//         painter->drawLine(QLineF(-14.0, 0.0, 14.0, 0.0)); //step 8
//         painter->drawLine(QLineF(-14.0, -5.0, 14.0, -5.0)); //step 9
//         painter->drawLine(QLineF(-14.0, -10.0, 14.0, -10.0)); //step 10
//         break;
//     }
//     case Ladder_3: {
//         painter->setPen(QPen(Qt::black, 1));
//         painter->drawLine(QLineF(-15.0, 40.0, -15.0, -15.0));   //left line 1
//         painter->drawLine(QLineF(15.0, 40.0, 15.0, -15.0)); //right line 1
//         painter->drawLine(QLineF(-14.0, 35.0, 14.0, 35.0)); //step 1
//         painter->drawLine(QLineF(-14.0, 30.0, 14.0, 30.0)); //step 2
//         painter->drawLine(QLineF(-14.0, 25.0, 14.0, 25.0)); //step 3
//         painter->drawLine(QLineF(-14.0, 20.0, 14.0, 20.0)); //step 4
//         painter->drawLine(QLineF(-14.0, 15.0, 14.0, 15.0)); //step 5
//         painter->drawLine(QLineF(-14.0, 10.0, 14.0, 10.0)); //step 6
//         painter->drawLine(QLineF(-14.0, 5.0, 14.0, 5.0)); //step 7
//         painter->drawLine(QLineF(-14.0, 0.0, 14.0, 0.0)); //step 8
//         painter->drawLine(QLineF(-14.0, -5.0, 14.0, -5.0)); //step 9
//         painter->drawLine(QLineF(-14.0, -10.0, 14.0, -10.0)); //step 10
//         painter->drawLine(QLineF(-10.0, -10.0, -10.0, -43.0));  //left line 2
//         painter->drawLine(QLineF(10.0, -10.0, 10.0, -43.0));  //right line 2
//         painter->drawLine(QLineF(-9.0, -13.0, 9.0, -13.0));  //step 11
//         painter->drawLine(QLineF(-9.0, -16.0, 9.0, -16.0));  //step 12
//         painter->drawLine(QLineF(-9.0, -19.0, 9.0, -19.0));  //step 13
//         painter->drawLine(QLineF(-9.0, -22.0, 9.0, -22.0));  //step 14
//         painter->drawLine(QLineF(-9.0, -25.0, 9.0, -25.0));  //step 15
//         painter->drawLine(QLineF(-9.0, -28.0, 9.0, -28.0));  //step 16
//         painter->drawLine(QLineF(-9.0, -31.0, 9.0, -31.0));  //step 17
//         painter->drawLine(QLineF(-9.0, -34.0, 9.0, -34.0));  //step 18
//         painter->drawLine(QLineF(-9.0, -37.0, 9.0, -37.0));  //step 19
//         painter->drawLine(QLineF(-9.0, -40.0, 9.0, -40.0));  //step 20
//         break;
//     }
//     case Collector: {
//         painter->drawLine(QLineF(-4.0, 16.0, 4.0, 16.0));   //bottom line
//         painter->drawLine(QLineF(0.0, 14.0, 0.0, -2.0));    //center line
//         painter->drawLine(QLineF(0.0, -2.0, -12.0, -14.0)); //left line
//         painter->drawLine(QLineF(0.0, -2.0, 12.0, -14.0));  //right line
//         painter->drawLine(QLineF(-17.0, -11.0, -8.0, -17.0));   //left top
//         painter->drawLine(QLineF(17.0, -11.0, 8.0, -17.0)); //right top
//         break;
//     }
//     case Bridge: {
//         painter->setPen(QPen(Qt::black, 2));
//         painter->drawLine(QLineF(-28.0, 10.0, -14.0, -10.0));   //left line
//         painter->drawLine(QLineF(-14.0, -10.0, 14.0, -10.0));     //horizontal center line
//         painter->drawLine(QLineF(14.0, -10.0, 28.0, 10.0));     //right line
//         break;
//     }
//     case Reel: {
//         painter->setPen(QPen(Qt::black, 2));
//         painter->drawLine(QLineF(-28.0, 10.0, -28.0, -10.0));   //left line
//         painter->drawLine(QLineF(-28.0, 0.0, 28.0, 0.0));   //horizontal center line
//         painter->drawLine(QLineF(28.0, 10.0, 28.0, -10.0)); //right line
//         break;
//     }
//     case Reel_mobile: {
//         painter->setPen(QPen(Qt::black, 2));
//         painter->drawLine(QLineF(-28.0, 10.0, -28.0, -10.0));   //left line
//         painter->drawLine(QLineF(-28.0, 0.0, 28.0, 0.0));   //horizontal center line
//         painter->drawLine(QLineF(0.0, 0.0, 0.0, -10.0));    //vertical center line
//         painter->drawLine(QLineF(28.0, 10.0, 28.0, -10.0)); //righ line
//         break;
//     }
//     case HydrElevator: {
//         painter->setPen(QPen(Qt::black, 1));
//         painter->setBrush(QBrush(Qt::white));
//         painter->drawLine(QLineF(-28.0, 0.0, 28.0, 0.0));   //center line
//         painter->drawLine(QLineF(28.0, 4.0, 28.0, -4.0));   //vertical line 3
//         painter->drawEllipse(QPointF(19.0, 0.0), 5.0, 5.0);
//         painter->drawLine(QLineF(19.0, -5.0, 19.0, -10.0)); //vertical line 2
//         painter->drawLine(QLineF(15.0, -10.0, 23.0, -10.0));    //right horizontal top line
//         painter->drawLine(QLineF(-18.0, 10.0, -18.0, -10.0));   //vertical line 1
//         painter->drawLine(QLineF(-18.0, -10.0, 14.0, -2.0));    //left horizontal top line
//         painter->drawLine(QLineF(-18.0, 10.0, 14.0, 2.0));  //bottom line
//         break;
//     }
//     case Foam_mix: {
//         painter->setPen(QPen(Qt::black, 1));
//         painter->setBrush(QBrush(Qt::white));
//         painter->drawLine(QLineF(-28.0, 0.0, 28.0, 0.0));   //center line
//         painter->drawLine(QLineF(28.0, 4.0, 28.0, -4.0));   //vertical line 3
//         painter->drawEllipse(QPointF(19.0, 0.0), 5.0, 5.0);
//         painter->drawLine(QLineF(19.0, -5.0, 19.0, -10.0)); //vertical line 2
//         painter->drawLine(QLineF(15.0, -10.0, 23.0, -10.0));    //right horizontal top line
//         painter->drawLine(QLineF(-18.0, 10.0, -18.0, -10.0));   //vertical line 1
//         painter->drawLine(QLineF(-18.0, -10.0, 14.0, -2.0));    //left horizontal top line
//         painter->drawLine(QLineF(-18.0, 10.0, 14.0, 2.0));  //bottom line
//         painter->drawEllipse(QPointF(-9.0, 0.0), 5.0, 5.0);
//         painter->drawLine(QLineF(-12.5, 3.5, -5.5, -3.5)); //inside ellipse, left bottom - right top
//         painter->drawLine(QLineF(-12.5, -3.5, -5.5, 3.5)); //inside ellipse, left top - right botttom
//         break;
//     }
//     case Column: {
//         painter->drawLine(QLineF(0.0, 20.0, 0.0, -20.0));    //center line
//         painter->drawLine(QLineF(-18.0, -10.0, 0.0, -21.0));  //left part of the arrow
//         painter->drawLine(QLineF(0.0, -21.0, 18.0, -10.0));   //right part of the arrow
//         painter->drawLine(QLineF(-19.5, -12.0, -16.5, -8.0));    //left connection
//         painter->drawLine(QLineF(16.5, -8.0, 19.5, -12.0));  //right connection
//         break;
//     }
//     case SmokePump_1: {
//         painter->setPen(QPen(Qt::black, 1));
//         painter->drawEllipse(QPointF(0.0, 0.0), 15.0, 15.0);
//         painter->drawLine(QLineF(-12.0, 8.0, 12.0, -8.0));  //inside ellipse, left bottom - right top
//         painter->drawLine(QLineF(12.0, -8.0, -2.0, -14.0));  //inside ellipse top
//         painter->drawLine(QLineF(-2.0, -14.0, 2.0, 14.0));  //inside ellipse, left top - right bottom
//         painter->drawLine(QLineF(2.0, 14.0, -12.0, 8.0));  //inside ellipse bottom
//         break;
//     }
//     case SmokePump_2: {
//         painter->setPen(QPen(Qt::black, 1));
//         painter->drawEllipse(QPointF(0.0, 0.0), 15.0, 15.0);
//         painter->drawLine(QLineF(-12.0, 8.0, 12.0, -8.0));  //inside ellipse, left bottom - right top
//         painter->drawLine(QLineF(12.0, -8.0, -2.0, -14.0));  //inside ellipse top
//         painter->drawLine(QLineF(-2.0, -14.0, 2.0, 14.0));  //inside ellipse, left top - right bottom
//         painter->drawLine(QLineF(2.0, 14.0, -12.0, 8.0));  //inside ellipse bottom
//         painter->drawLine(QLineF(-16.0, 15.0, -16.0, -15.0));  //left line
//         painter->drawLine(QLineF(16.0, 15.0, 16.0, -15.0));  //right line
//         break;
//     }
//     case Hose: {
//         painter->setPen(QPen(Qt::black, 2));
//         painter->drawLine(QLineF(0.0, 45.0, 0.0, -40.0));   //center line
//         painter->drawLine(QLineF(-4.0, 40.0, 4.0, 40.0));   //line 1
//         painter->drawLine(QLineF(-4.0, 35.0, 4.0, 35.0));   //line 2
//         painter->drawLine(QLineF(-4.0, 30.0, 4.0, 30.0));   //line 3
//         painter->drawLine(QLineF(-4.0, 25.0, 4.0, 25.0));   //line 4
//         painter->drawLine(QLineF(-4.0, 20.0, 4.0, 20.0));   //line 5
//         painter->drawLine(QLineF(-4.0, 15.0, 4.0, 15.0));   //line 6
//         painter->drawLine(QLineF(-4.0, 10.0, 4.0, 10.0));   //line 7
//         painter->drawLine(QLineF(-4.0, 5.0, 4.0, 5.0));   //line 8
//         painter->drawLine(QLineF(-4.0, 0.0, 4.0, 0.0));   //line 9
//         painter->drawLine(QLineF(-4.0, -5.0, 4.0, -5.0));   //line 10
//         painter->drawLine(QLineF(-4.0, -10.0, 4.0, -10.0));   //line 11
//         painter->drawLine(QLineF(-4.0, -15.0, 4.0, -15.0));   //line 12
//         painter->drawLine(QLineF(-4.0, -20.0, 4.0, -20.0));   //line 13
//         painter->drawLine(QLineF(-4.0, -25.0, 4.0, -25.0));   //line 14
//         painter->drawLine(QLineF(-4.0, -30.0, 4.0, -30.0));   //line 15
//         painter->drawLine(QLineF(-4.0, -35.0, 4.0, -35.0));   //line 16
//         painter->drawLine(QLineF(-4.0, -40.0, 4.0, -40.0));   //line 17
//         break;
//     }
//     case FoamLift_1: {
//         painter->setPen(QPen(Qt::black, 2));
//         painter->drawLine(QLineF(14.0, 40.0, 22.0, 40.0));   //botoom line
//         QPainterPath arcPath;
//         arcPath.moveTo(18.0, 40.0);
//         arcPath.quadTo(20.0, -28.0, -10.0, -20.0);
//         painter->drawPath(arcPath);
//         painter->drawLine(QLineF(13.0, 11.0, 20.0, 10.0));   //center line
//         painter->setPen(QPen(Qt::black, 1));
//         painter->drawEllipse(QPointF(-15.0, -20.0), 5.0, 5.0);
//         painter->drawLine(QLineF(-18.5, -16.5, -11.5, -23.5)); //inside ellipse, left bottom - right top
//         painter->drawLine(QLineF(-18.5, -23.5, -11.5, -16.5)); //inside ellipse, left top - right botttom
//         break;
//     }
//     case FoamLift_2: {
//         painter->setPen(QPen(Qt::black, 1));
//         painter->drawEllipse(QPointF(-25.0, -36.0), 5.0, 5.0);
//         painter->drawLine(QLineF(-28.5, -32.5, -21.5, -39.5));  //inside ellipse 1, left bottom - right top
//         painter->drawLine(QLineF(-28.5, -39.5, -21.5, -32.5));  //inside ellipse 1, left top - right botttom
//         painter->drawEllipse(QPointF(-25.0, -25.0), 5.0, 5.0);
//         painter->drawLine(QLineF(-28.5, -21.5, -21.5, -28.5));  //inside ellipse 2, left bottom - right top
//         painter->drawLine(QLineF(-28.5, -28.5, -21.5, -21.5));  //inside ellipse 2, left top - right botttom
//         painter->drawEllipse(QPointF(25.0, -36.0), 5.0, 5.0);
//         painter->drawLine(QLineF(21.5, -32.5, 28.5, -39.5));    //inside ellipse 3, left bottom - right top
//         painter->drawLine(QLineF(21.5, -39.5, 28.5, -32.5));    //inside ellipse 3, left top - right botttom
//         painter->drawEllipse(QPointF(25.0, -25.0), 5.0, 5.0);
//         painter->drawLine(QLineF(21.5, -21.5, 28.5, -28.5));    //inside ellipse 4, left bottom - right top
//         painter->drawLine(QLineF(21.5, -28.5, 28.5, -21.5));    //inside ellipse 4, left top - right botttom
//         painter->setPen(QPen(Qt::black, 2));
//         painter->drawLine(QLineF(-25.0, -20.0, -25.0, 0.0));    //left branch
//         painter->drawLine(QLineF(-31.0, -14.0, -25.0, -20.0));  //left branch, left part of the arrow
//         painter->drawLine(QLineF(-25.0, -20.0, -19.0, -14.0));   //left branch, right part of the arrow
//         painter->drawLine(QLineF(25.0, -20.0, 25.0, 0.0));   //right branch
//         painter->drawLine(QLineF(19.0, -14.0, 25.0, -20.0));   //right branch, left part of the arrow
//         painter->drawLine(QLineF(25.0, -20.0, 31.0, -14.0));   //right branch, right part of the arrow
//         painter->drawLine(QLineF(-25.0, 0.0, 25.0, 0.0));   //horizontal central line
//         painter->drawLine(QLineF(0.0, 0.0, -25.0, 40.0));   //vertical central line
//         painter->drawLine(QLineF(-29.0, 38.0, -21.0, 42.0));   //bottom line
//         painter->drawLine(QLineF(-19.5, 23.0, -11.5, 27.0));   //stand
//         break;
//     }
//     default:
//         break;
//     }
// }

NosepieceShape::NosepieceShape(QGraphicsItem *parent)
    : EquipmentShape(parent)
    , m_equipmentType(Nosepiece)
    , m_nosepieceRect{QRectF(-6.0, -16.0, 12.0, 32.0)}
    , m_nominalDiameter{nullptr}
    , m_nosepieceConsumption{nullptr}
    , m_showDN{false}
    , m_showConsumption{false}
    , m_substanceType{SubstanceType::NoneSubstance}
{
    setFlag(ItemSendsGeometryChanges, true);
    setAcceptHoverEvents(true);
    setPen(QPen(Qt::black, 1));
}

void NosepieceShape::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(widget);

    painter->setRenderHint(QPainter::Antialiasing);
    painter->setRenderHint(QPainter::SmoothPixmapTransform);
    painter->setPen(pen());
    painter->setBrush(brush());

    drawNosepiece(painter);

    if (option->state & QStyle::State_Selected)
        highlightSelected(painter, option);
}

QRectF NosepieceShape::boundingRect() const
{
    QRectF boundingRect{m_nosepieceRect};
    const qreal topAdjust = calculateTopAdjust();
    // Increase the size of the boundingRect by the size of the substance type
    boundingRect.adjust(0, -topAdjust, 0, 0);
    adjustForPenWidth(boundingRect);

    return boundingRect;
}

QPainterPath NosepieceShape::shape() const
{
    QPainterPath path;

    // Nosepiece shape
    path.moveTo(m_nosepieceRect.bottomLeft());
    path.lineTo(m_nosepieceRect.bottomRight());

    path.moveTo(m_nosepieceRect.center().x(), m_nosepieceRect.bottom());
    path.lineTo(m_nosepieceRect.center().x(), m_nosepieceRect.top());

    path.moveTo(m_nosepieceRect.left(), m_nosepieceRect.top() + m_nosepieceRect.height() / 6.0);
    path.lineTo(m_nosepieceRect.center().x(), m_nosepieceRect.top());
    path.lineTo(m_nosepieceRect.right(), m_nosepieceRect.top() + m_nosepieceRect.height() / 6.0);

    //Sunctance shape
    const qreal width = m_nosepieceRect.width();
    const qreal centerX = m_nosepieceRect.center().x();
    const qreal topY = m_nosepieceRect.top();

    auto addCircleAt = [&](qreal y, qreal radius) {
        path.addEllipse(QPointF(centerX, y), radius, radius);
    };

    auto addSquareAt = [&](qreal y) {
        QRectF rect(m_nosepieceRect.left(), y, width, width);
        path.addRect(rect);
    };

    auto addTriangleAt = [&](qreal y) {
        qreal gasBottom{y - 3.0};
        QPolygonF gasPolygon;
        gasPolygon << QPointF(m_nosepieceRect.right(), gasBottom)
                   << QPointF(m_nosepieceRect.left(), gasBottom)
                   << QPointF(centerX, y - width);
        path.addPolygon(gasPolygon);
    };

    struct SubstancePattern {
        QVector<std::pair<qreal, qreal>> circles; //(y_offset_multiplier, radius_multiplier)
        bool isSquare = false;
        bool isTriangle = false;
    };

    static const QHash<SubstanceType, SubstancePattern> s_substancePatterns = {
        {SubstanceType::CompactWater, {{{0.5, 0.25}}}},
        {SubstanceType::SprayedWater, {{{0.5, 0.25}, {1.25, 0.25}}}},
        {SubstanceType::ThinlySprayedWater, {{{0.5, 0.25}, {1.25, 0.25}, {2.0, 0.25}}}},
        {SubstanceType::LowFoam, {{{0.5, 0.5}}}},
        {SubstanceType::MiddleFoam, {{{0.5, 0.5}, {1.5, 0.5}}}},
        {SubstanceType::HighFoam, {{{0.5, 0.5}, {1.5, 0.5}, {2.5, 0.5}}}},
        {SubstanceType::WaterFoam, {{{0.5, 0.5}, {1.5, 0.5}}}},
        {SubstanceType::WaterAdditives, {{{0.5, 0.5}}}},
        {SubstanceType::Powder, {{}, true}},
        {SubstanceType::Powder_BC, {{}, true}},
        {SubstanceType::Powder_ABC, {{}, true}},
        {SubstanceType::Chladon, {{}, false, true}},
        {SubstanceType::CarbonDioxide, {{}, false, true}},
        {SubstanceType::WaterVapor, {{}, false, true}},
        {SubstanceType::Gas, {{}, false, true}}
    };

    auto it = s_substancePatterns.find(m_substanceType);
    if (it != s_substancePatterns.end()) {
        const auto& pattern = it.value();
        if (pattern.isSquare) {
            addSquareAt(topY - width);
        } else if (pattern.isTriangle) {
            addTriangleAt(topY);
        } else {
            for (const auto& [offset, radMult] : pattern.circles) {
                addCircleAt(topY - width * offset, width * radMult);
            }
        }
    }

    return shapeFromPath(path);
}

QPixmap NosepieceShape::image()
{
    qreal pixmapWidth{boundingRect().width()};
    qreal pixmapHeight{boundingRect().height()};
    QPixmap pixmap(pixmapWidth, pixmapHeight);
    pixmap.fill(Qt::transparent);

    QPainter painter(&pixmap);
    painter.setPen(pen());
    painter.setBrush(brush());
    painter.translate(pixmapWidth / 2.0, pixmapHeight / 2.0);
    drawNosepiece(&painter);

    return pixmap;
}

void NosepieceShape::setRect(const QRectF &rect)
{
    if (m_nosepieceRect == rect)
        return;

    // The size of the nosepiece excluding the size of the substance type
    const qreal topAdjust = calculateTopAdjust();
    QRectF nosepieceRect{rect};
    nosepieceRect.adjust(0, topAdjust, 0, 0);

    prepareGeometryChange();
    m_nosepieceRect = nosepieceRect;
    updateConsumptionPosition();
    update();
}

QRectF NosepieceShape::rect() const
{
    return m_nosepieceRect;
}

void NosepieceShape::setHeight(const qreal &height)
{
    if (m_nosepieceRect.height() == height)
        return;

    qreal oldHeight{m_nosepieceRect.height()};
    prepareGeometryChange();
    m_nosepieceRect.setHeight(height);
    qreal dy{(m_nosepieceRect.height() - oldHeight) / 2};
    m_nosepieceRect.moveTo(QPointF(m_nosepieceRect.x(), m_nosepieceRect.y() - dy));
    update();
}

qreal NosepieceShape::height() const
{
    return m_nosepieceRect.height();
}

void NosepieceShape::setTextItem(TextItemType textItemType, const QString &value)
{
    if (textItemType == NominalDiameter) {
        if (m_nominalDiameter == nullptr) {
            m_nominalDiameter = new QGraphicsTextItem(this);
            m_nominalDiameter->setTextInteractionFlags(Qt::TextEditorInteraction);
            m_nominalDiameter->setRotation(-90);
        }
        m_nominalDiameter->setPlainText(value);
        m_showDN = true;
    } else {
        if (m_nosepieceConsumption == nullptr) {
            m_nosepieceConsumption = new QGraphicsTextItem(this);
            m_nosepieceConsumption->setTextInteractionFlags(Qt::TextEditorInteraction);
            m_nosepieceConsumption->setRotation(-90);
        }
        m_nosepieceConsumption->setPlainText(value);
        m_showConsumption = true;
    }
}

QString NosepieceShape::nominalDiameter() const
{
    if (m_nominalDiameter == nullptr)
        return "";

    return m_nominalDiameter->toPlainText();
}

QString NosepieceShape::consumption() const
{
    if (m_nosepieceConsumption == nullptr)
        return "";

    return m_nosepieceConsumption->toPlainText();
}

void NosepieceShape::setSubstanceType(SubstanceType newSubstanceType)
{
    m_substanceType = newSubstanceType;
}

NosepieceShape::SubstanceType NosepieceShape::substanceType()
{
    return m_substanceType;
}

void NosepieceShape::mousePressEvent(QGraphicsSceneMouseEvent *mouseEvent)
{
    if (mouseEvent->buttons() == Qt::RightButton) {
        QMenu *substanceMenu = new QMenu("Substance");
        substanceMenu->setToolTipsVisible(true);
        createActions();
        createSubstanceActions();
        addActions(m_nosepieceActionList);
        substanceMenu->addActions(m_substanceActionList);
        addSubstanceMenu(substanceMenu);
        QAction menuAction{menu()->exec(mouseEvent->screenPos())};
        QString menuActionText;
        if (menuAction.parent()) {
            menuActionText = menuAction.parent()->objectName();
        }
        if ((menuActionText != "actionDeleteItem") && (menuActionText != "actionCut")) {
            removeActions(m_substanceActionList);
            m_substanceActionList.clear();
            removeActions(m_nosepieceActionList);
            m_nosepieceActionList.clear();
        }
    } else {
        AbstractShape::mousePressEvent(mouseEvent);
    }
}

void NosepieceShape::updateDNPosition()
{
    if (m_showDN) {
        QRectF ndRect{m_nominalDiameter->boundingRect()};
        qreal posX{m_nosepieceRect.center().x() - ndRect.height()};
        qreal posY{m_nosepieceRect.center().y() + ndRect.width() / 2.0};
        m_nominalDiameter->setPos(posX, posY);
    }
}

const QHash<NosepieceShape::SubstanceType, qreal> &NosepieceShape::adjustFactors() const
{
    static const QHash<SubstanceType, qreal> factors = {
        {SubstanceType::CompactWater, 0.75},
        {SubstanceType::SprayedWater, 1.5},
        {SubstanceType::ThinlySprayedWater, 2.25},
        {SubstanceType::LowFoam, 1.0},
        {SubstanceType::MiddleFoam, 2.0},
        {SubstanceType::HighFoam, 3.0},
        {SubstanceType::WaterFoam, 2.0},
        {SubstanceType::WaterAdditives, 1.0},
        {SubstanceType::Powder, 1.0},
        {SubstanceType::Powder_BC, 1.0},
        {SubstanceType::Powder_ABC, 1.0},
        {SubstanceType::Chladon, 1.0},
        {SubstanceType::CarbonDioxide, 1.0},
        {SubstanceType::WaterVapor, 1.0},
        {SubstanceType::Gas, 1.0}
    };
    return factors;
}

void NosepieceShape::addSubstanceMenu(QMenu *contextSubMenu)
{
    QMenu *contextMenu = menu();
    contextMenu->addMenu(contextSubMenu);
}

void NosepieceShape::createSubstanceActions()
{
    // Create action group to manage exclusive selection
    m_substanceActionGroup.reset(new QActionGroup(nullptr));

    // Localized names for all substance types
    const std::array<QString, SubstanceType::Count> substanceNamesArray = {
        QObject::tr("None"),
        QObject::tr("Compact water"),
        QObject::tr("Sprayed water"),
        QObject::tr("Thinly sprayed water"),
        QObject::tr("Low foam"),
        QObject::tr("Middle foam"),
        QObject::tr("High foam"),
        QObject::tr("Water foam"),
        QObject::tr("Water additives"),
        QObject::tr("Powder"),
        QObject::tr("Powder BC"),
        QObject::tr("Powder ABC"),
        QObject::tr("Chladon"),
        QObject::tr("Carbon dioxide"),
        QObject::tr("Water vapor"),
        QObject::tr("Gas")
    };

    // Create mapping between substance types and their display names
    QMap <SubstanceType, QString> substanceTypeNameMap;
    for (int i = 0; i < SubstanceType::Count; ++i) {
        substanceTypeNameMap[static_cast<SubstanceType>(i)] = substanceNamesArray[i];
    }

    // Create actions for each substance type
    for (auto key : substanceTypeNameMap.keys()) {
        QAction *action(new QAction(substanceTypeNameMap.value(key)));
        action->setCheckable(true);

        // Create tooltip explaining the action's purpose
        QString names{substanceTypeNameMap.value(key)};
        QString toolTip{QObject::tr("Set ") + names.toLower() + QObject::tr(" subctance.")};
        action->setToolTip(toolTip);

        // Connect action to set the corresponding substance type
        auto showSubstance{[this, key]() { setSubstanceType(key);}};
        QObject::connect(action, &QAction::triggered, showSubstance);

        // Add to action group and store reference
        m_substanceActionGroup->addAction(action);
        m_substanceActionList.append(action);

        // Preselect current substance type
        if (key == m_substanceType) {
            action->setChecked(true);
        }
    }
}

void NosepieceShape::nominalDiameterShow(bool showDN)
{
    if (showDN) {
        if (m_nominalDiameter == nullptr) {
            m_nominalDiameter = new QGraphicsTextItem(this);
            m_nominalDiameter->setPlainText("50");
            m_nominalDiameter->setTextInteractionFlags(Qt::TextEditorInteraction);
            m_nominalDiameter->setRotation(-90);
        }
        m_nominalDiameter->show();
        m_showDN = true;
    } else {
        m_nominalDiameter->hide();
        m_showDN = false;
    }
}

void NosepieceShape::createActions()
{
    QString addDN{m_showDN ? QObject::tr("Hide DN") : QObject::tr("Show DN")};
    m_addDNAction.reset(new QAction(addDN));
    m_addDNAction->setToolTip(QObject::tr("Show or hide nominal diameter (DN)"));
    //Allows you to use QObject::connect without inheriting a class from QObject.
    auto showDN{[&](){m_showDN ? nominalDiameterShow(false) : nominalDiameterShow(true);}};
    QObject::connect(m_addDNAction.get(), &QAction::triggered, showDN);
    m_nosepieceActionList.append(m_addDNAction.get());

    QString addConsumption{m_showConsumption ? QObject::tr("Hide consumption") : QObject::tr("Show consumption")};
    m_addConsumptionAction.reset(new QAction(addConsumption));
    m_addConsumptionAction->setToolTip(QObject::tr("Show or hide consumption"));
    //Allows you to use QObject::connect without inheriting a class from QObject.
    auto showConsumption{[&](){m_showConsumption ? consumptionShow(false) : consumptionShow(true);}};
    QObject::connect(m_addConsumptionAction.get(), &QAction::triggered, showConsumption);
    m_nosepieceActionList.append(m_addConsumptionAction.get());

    m_separatorAction.reset(new QAction());
    m_separatorAction->setSeparator(true);
    m_nosepieceActionList.append(m_separatorAction.get());
}

void NosepieceShape::consumptionShow(bool showConsumption)
{
    if (showConsumption) {
        if (m_nosepieceConsumption == nullptr) {
            m_nosepieceConsumption = new QGraphicsTextItem(this);
            m_nosepieceConsumption->setPlainText("2,7");
            m_nosepieceConsumption->setTextInteractionFlags(Qt::TextEditorInteraction);
            m_nosepieceConsumption->setRotation(-90);
        }
        m_nosepieceConsumption->show();
        m_showConsumption = true;
    } else {
        m_nosepieceConsumption->hide();
        m_showConsumption = false;
    }
}

void NosepieceShape::updateConsumptionPosition()
{
    if (m_showConsumption) {
        QRectF cbRect = m_nosepieceConsumption->boundingRect();
        qreal posX{m_nosepieceRect.center().x()};
        qreal posY{m_nosepieceRect.center().y() + cbRect.width() / 2.0};
        m_nosepieceConsumption->setPos(posX, posY);
    }
}

void NosepieceShape::drawNosepiece(QPainter *painter)
{
    painter->setPen(QPen(Qt::black, 2));
    painter->drawLine(m_nosepieceRect.bottomLeft(), m_nosepieceRect.bottomRight()); //-6.0, 16.0; 6.0, 16.0
    painter->drawLine(m_nosepieceRect.center().x(), m_nosepieceRect.bottom(),
                      m_nosepieceRect.center().x(), m_nosepieceRect.top()); //0.0, 16.0; 0.0, -16.0
    painter->drawLine(m_nosepieceRect.left(), m_nosepieceRect.top() + (m_nosepieceRect.height() / 6.0),
                      m_nosepieceRect.center().x(), m_nosepieceRect.top()); //-6.0, -10.66; 0.0, -16.0
    painter->drawLine(m_nosepieceRect.center().x(), m_nosepieceRect.top(),
                      m_nosepieceRect.right(), m_nosepieceRect.top() + (m_nosepieceRect.height() / 6.0)); //0.0, -16; 6.0, -10.66

    if (m_showDN) {
        updateDNPosition();
    }

    if (m_showConsumption) {
        updateConsumptionPosition();
    }

    if (m_substanceType != SubstanceType::NoneSubstance) {
        drawSubstance(painter);
    }
}

void NosepieceShape::drawSubstance(QPainter *painter)
{
    constexpr unsigned int COMPACT_WATER_COUNT = 1;
    constexpr unsigned int SPRAYED_WATER_COUNT = 2;
    constexpr unsigned int THINLY_SPRAYED_WATER_COUNT = 3;
    constexpr double CROSS_ANGLE = M_PI_4;
    constexpr double WATER_SYMBOL_MULTIPLIER = 4.0;
    constexpr double FOAM_MIDDLE_MULTIPLIER = 3.0;
    constexpr double FOAM_HIGH_MULTIPLIER = 5.0;

    const qreal width{m_nosepieceRect.width()};
    const qreal centerX{m_nosepieceRect.center().x()};
    const qreal baseY{m_nosepieceRect.top()};
    const qreal halfWidth{width / 2.0};
    const qreal centerY{baseY - halfWidth};
    const QPen defaultPen(Qt::black, 1);
    const QPointF centerLow(centerX, centerY);
    const QPointF centerMiddle(centerX, baseY - FOAM_MIDDLE_MULTIPLIER * halfWidth);
    const QPointF centerHigh(centerX, baseY - FOAM_HIGH_MULTIPLIER * halfWidth);

    auto drawCross = [&](QPointF center, double radius) {
        const qreal offset{radius * std::cos(CROSS_ANGLE)};
        const QPointF crossTopLeft{center - QPointF(offset, offset)};
        const QPointF crossBottomRight{center + QPointF(offset, offset)};
        const QPointF crossBottomLeft{QPointF(center.x() - offset, center.y() + offset)};
        const QPointF crossTopRight{QPointF(center.x() + offset, center.y() - offset)};
        painter->drawLine(crossTopLeft, crossBottomRight);
        painter->drawLine(crossBottomLeft, crossTopRight);
    };

    auto drawWaterSymbol = [&](int count) {
        painter->setBrush(Qt::black);
        const qreal radius = width / WATER_SYMBOL_MULTIPLIER;
        for(int i = 0; i < count; ++i) {
            const qreal yPos = baseY - width * (0.5 + i * 0.75);
            painter->drawEllipse(QPointF(centerX, yPos), radius, radius);
        }
    };

    auto drawFoamSymbol = [&](QPointF center, double radius) {
        painter->setPen(defaultPen);
        painter->drawEllipse(center, radius, radius);
        drawCross(center, radius);
    };

    auto drawPowderSymbol = [&](bool withCross, bool filled) {
        painter->setPen(defaultPen);
        painter->setBrush(filled ? QBrush(Qt::black) : Qt::NoBrush);
        qreal rectLeft{m_nosepieceRect.left()};
        qreal rectTop{baseY - width - painter->pen().widthF()};
        QRectF rect(rectLeft, rectTop, width, width);
        painter->drawRect(rect);
        if(withCross) {
            drawCross(rect.center(), halfWidth);
        }
    };

    auto drawGasSymbol = [&](bool filled, bool withCenterLine) {
        painter->setPen(defaultPen);
        painter->setBrush(filled ? QBrush(Qt::black) : Qt::NoBrush);
        qreal gasBottom{baseY - 3.0};
        QPolygonF gasPolygon;
        gasPolygon << QPointF(m_nosepieceRect.right(), gasBottom)
                   << QPointF(m_nosepieceRect.left(), gasBottom)
                   << QPointF(centerX, baseY - width);
        painter->drawPolygon(gasPolygon);
        if (withCenterLine) {
            painter->drawLine(QPointF(centerX, gasBottom), QPointF(centerX, baseY - width));
        }
    };

    auto drawWaterVaporSymbol = [&]() {
        painter->setPen(Qt::NoPen);
        painter->setBrush(QBrush(Qt::black));
        qreal waterVaporBottom{baseY - 3.0};
        QPolygonF waterVaporPolygon;
        waterVaporPolygon << QPointF(m_nosepieceRect.right(), waterVaporBottom)
                          << QPointF(centerX, waterVaporBottom)
                          << QPointF(centerX, baseY - width);
        painter->drawPolygon(waterVaporPolygon);
    };

    switch (m_substanceType) {
    case SubstanceType::NoneSubstance:
        break;
    case SubstanceType::CompactWater:
        drawWaterSymbol(COMPACT_WATER_COUNT);
        break;
    case SubstanceType::SprayedWater:
        drawWaterSymbol(SPRAYED_WATER_COUNT);
        break;
    case SubstanceType::ThinlySprayedWater:
        drawWaterSymbol(THINLY_SPRAYED_WATER_COUNT);
        break;
    case SubstanceType::LowFoam:
        drawFoamSymbol(centerLow, halfWidth);
        break;
    case SubstanceType::MiddleFoam: {
        drawFoamSymbol(centerLow, halfWidth);
        drawFoamSymbol(centerMiddle, halfWidth);
        break;
    }
    case SubstanceType::HighFoam: {
        drawFoamSymbol(centerLow, halfWidth);
        drawFoamSymbol(centerMiddle, halfWidth);
        drawFoamSymbol(centerHigh, halfWidth);
        break;
    }
    case SubstanceType::WaterFoam:
        painter->setPen(defaultPen);
        painter->setBrush(Qt::black);
        painter->drawEllipse(centerLow, halfWidth, halfWidth);
        painter->setBrush(Qt::NoBrush);
        painter->drawEllipse(centerMiddle,halfWidth, halfWidth);
        drawCross(centerMiddle, halfWidth);
        break;
    case SubstanceType::WaterAdditives: {
        painter->setPen(defaultPen);
        painter->setBrush(QBrush(Qt::black, Qt::Dense5Pattern));
        painter->drawEllipse(centerLow, halfWidth, halfWidth);
        drawCross(centerLow, halfWidth);
        break;
    }
    case SubstanceType::Powder:
        drawPowderSymbol(false, false);
        break;
    case SubstanceType::Powder_BC:
        drawPowderSymbol(true, false);
        break;
    case SubstanceType::Powder_ABC:
        drawPowderSymbol(false, true);
        break;
    case SubstanceType::Chladon:
        drawGasSymbol(false, true);
        break;
    case SubstanceType::CarbonDioxide:
        drawGasSymbol(true, false);
        break;
    case SubstanceType::WaterVapor:
        drawGasSymbol(false, false);
        drawWaterVaporSymbol();
        break;
    case SubstanceType::Gas:
        drawGasSymbol(false, false);
        break;
    default:
        qWarning() << "Unknown substance type:" << static_cast<int>(m_substanceType);
        break;
    }
}

qreal NosepieceShape::calculateTopAdjust() const
{
    auto it = adjustFactors().find(m_substanceType);
    return (it != adjustFactors().end()) ? m_nosepieceRect.width() * it.value() : 0.0;
}

void NosepieceShape::adjustForPenWidth(QRectF &rect) const
{
    const qreal halfpw = (pen().style() == Qt::NoPen) ? 0.0 : pen().widthF() / 2;
    if (halfpw > 0.0) {
        rect.adjust(-halfpw, -halfpw, halfpw, halfpw);
    }
}

EquipmentShape::ShapeType NosepieceShape::shapeType() const
{
    return m_equipmentType;
}
