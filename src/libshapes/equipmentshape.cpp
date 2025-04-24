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

/*!
 * Constructs a EquipmentShape. The constructor is declared protected because
 * creating an abstract class is prohibited.
 *
 * \param parent[in] A pointer to the parent object is passed to the AbtractShape
 * constructor. This is part of the memory management strategy used in
 * Qt-Framework.
 */
EquipmentShape::EquipmentShape(QGraphicsItem *parent) : AbstractShape(parent)
{
}

/*!
 * Destoys the EquipmentShape. Protected purely virtual destructor.
 * Defined as default.
 */
EquipmentShape::~EquipmentShape() = default;

/*!
 * The remover method is declared protected. This prevents the client from
 * calling deleter() directly and thus reduces the likelihood of errors
 * associated with deleting an object. Deleting objects involves the use of
 * the EquipmentShapeDeleter deleter class and is oriented towards the use of
 * smart pointers.
 *
 * \sa EquipmentShapeDeleter::cleanup()
 */
void EquipmentShape::deleter()
{
    delete this;
}

/*!
 * This method creates a new object of the specified type and returns a pointer
 * to it cast to the EquipmentShape type.
 *
 * \param shapeType[in] The type of object being created.
 * \param parent[in] A pointer to the parent object is passed to the
 * AbtractShape constructor. This is part of the memory management strategy used
 * in Qt-Framework.
 * \return Returns a pointer to the created object cast to the EquipmentShape
 *  type
 */
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

/*!
 * Constructs a NosepieceShape class.
 *
 * \param parent[in] A pointer to the parent object is passed to the
 * QGraphicsItem constructor. This is part of the memory management strategy
 * used in Qt-Framework.
 */
NosepieceShape::NosepieceShape(QGraphicsItem *parent)
    : EquipmentShape(parent)
    , m_equipmentType(Nosepiece)
    , m_nosepieceType(NosepieceShape::NosepieceType::Hand)
    , m_nosepieceRect{QRectF(-6.0, -16.0, 12.0, 32.0)}
    , m_nosepieceConsumption{nullptr}
    , m_showConsumption{false}
{
    setFlag(ItemSendsGeometryChanges, true);
    setAcceptHoverEvents(true);
    setPen(QPen(Qt::black, 1));
}

/*!
 * Reimplements: QGraphicsItem::paint(). This function, which is usually called
 * by QGraphicsView, paints the contents of an item in local coordinates.
 *
 * \param painter[in] The pointer to used painter.
 * \param option[in] This option provides style options for the item, such as
 * its state, exposed area and its level-of-detail hints.
 * \param widget[in] The argument is optional. If provided, it points to the
 * widget that is being painted on; otherwise, it is 0. For cached painting,
 * widget is always 0.
 */
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

/*!
 * Reimplements: QGraphicsItem::boundingRect().
 * This function defines the outer bounds of the item as a rectangle. All
 * painting restricted to inside an item's bounding rect. QGraphicsView uses
 * this to determine whether the item requires redrawing. Although the item's
 * shape can be arbitrary, the bounding rect is always rectangular, and it is
 * unaffected by the items' transformation. For change the item's bounding
 * rectangle, must first call prepareGeometryChange(). This notifies the scene
 * of the imminent change, so that it can update its item geometry index.
 * Otherwise, the scene will be unaware of the item's new geometry, and the
 * results are undefined (typically, rendering artifacts are left within the
 * view). Half the pen width include in the bounding rect.
 *
 * \return Returns the outer bounds of the nosepiece as a rectangle.
 *
 * \sa shape(), contains().
 */
QRectF NosepieceShape::boundingRect() const
{
    QRectF boundingRect{m_nosepieceRect};
    qreal halfpw{pen().style() == Qt::NoPen ? qreal(0.0) : pen().widthF() / 2};
    if (halfpw > 0.0)
        boundingRect.adjust(-halfpw, -halfpw, halfpw, halfpw);

    return boundingRect;
}

/*!
 * Reimplements: QGraphicsItem::shape().
 * The shape is used for many things, including collision detection, hit tests,
 * and for the QGraphicsScene::items() functions. This function is called by
 * the default implementations of contains() and collidesWithPath(). The
 * stairwell outline is included in the element shape.
 *
 * \return Returns the shape of this item as a QPainterPath in local coordinates.
 *
 *  \sa boundingRect(), contains().
 */
QPainterPath NosepieceShape::shape() const
{
    QPainterPath path;
    path.moveTo(m_nosepieceRect.bottomLeft());
    path.lineTo(m_nosepieceRect.bottomRight());
    path.moveTo(m_nosepieceRect.center().x(), m_nosepieceRect.bottom());
    path.lineTo(m_nosepieceRect.center().x(), m_nosepieceRect.top());
    path.moveTo(m_nosepieceRect.left(), m_nosepieceRect.top() + (m_nosepieceRect.height() / 6.0));
    path.lineTo(m_nosepieceRect.center().x(), m_nosepieceRect.top());
    path.lineTo(m_nosepieceRect.right(), m_nosepieceRect.top() + (m_nosepieceRect.height() / 6.0));

    return shapeFromPath(path);
}

/*!
 * Reimplements: EquipmentShape::image().
 * Required to create a shape icon in ShapeToolBox. Used by the
 * MainWindow::createEquipmentShapeCellWidget() method to create a nosepiece
 * icon in the ShapeToolBox.
 *
 * \return Returns a QPixmap object containing the shape image.
 */
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

/*!
 * Reimplements: EquipmentShape::setRect().
 * This method is used to set the size of the shape.
 *
 * \param rect[in] Sets the shape's size to be the given  rectangle.
 * \sa rect().
 */
void NosepieceShape::setRect(const QRectF &rect)
{
    if (m_nosepieceRect == rect)
        return;

    prepareGeometryChange();
    m_nosepieceRect.setRect(rect.topLeft().x(), rect.topLeft().y(), rect.width()
                            , rect.height());
    if (m_nosepieceConsumption != nullptr) {
        qreal consumptionWidth{m_nosepieceConsumption->boundingRect().width()};
        qreal consumptionHeight{m_nosepieceConsumption->boundingRect().height()};
        m_nosepieceConsumption->setPos(m_nosepieceRect.center().x() - consumptionWidth
                                       , m_nosepieceRect.top() + m_nosepieceRect.height() / 6.0 + consumptionHeight);
    }
    update();
}

/*!
 * Reimplements: EquipmentShape::rect().
 * This is the outer bounds shape whitout pen width.
 *
 * \return Returns the shape's rectangle.
 * \sa setRect().
 */
QRectF NosepieceShape::rect() const
{
    return m_nosepieceRect;
}

/*!
 * Reimplements: EquipmentShape::setHeight().
 * Sets the height of the shape.
 *
 * \param height[in] Sets the height of the shape to the given height.
 * \sa height().
 */
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

/*!
 * Reimplements: EquipmentShape::height().
 *
 * \return Returns the shape's height.
 * \sa setHeight().
 */
qreal NosepieceShape::height() const
{
    return m_nosepieceRect.height();
}

/*!
 * The method sets the consumption of the nosepiece.
 *
 * \param consumption[in] The consumption of the nosepiece will be established in
 * accordance with this parameter.
 * \sa consumption().
 */
void NosepieceShape::setConsumption(const QString &consumption)
{
    if (m_nosepieceConsumption == nullptr) {
        m_nosepieceConsumption = new QGraphicsTextItem(this);
        m_nosepieceConsumption->setTextInteractionFlags(Qt::TextEditorInteraction);
        m_nosepieceConsumption->setRotation(-90);
    }
    m_nosepieceConsumption->setPlainText(consumption);
    m_showConsumption = true;
}

/*!
 * Returns the consumption of the nosepiece.
 *
 * \return Returns the consumption of the nosepiece.
 *
 * \sa setConsumption()
 */
QString NosepieceShape::consumption() const
{
    if (m_nosepieceConsumption == nullptr)
        return "";

    return m_nosepieceConsumption->toPlainText();
}

/*!
 * Reimplements: AbstractShape::mousePressEvent().
 * If the right mouse button is pressed, this method is used to create a nosepiece
 * context menu.
 *
 * \param mouseEvent[in] Pointer to the QGraphicsSceneMouseEvent class.
 */
void NosepieceShape::mousePressEvent(QGraphicsSceneMouseEvent *mouseEvent)
{
    if (mouseEvent->buttons() == Qt::RightButton) {
        createAction();
        addActions(m_nosepieceActionList);
        QAction menuAction{menu()->exec(mouseEvent->screenPos())};
        QString menuActionText;
        if (menuAction.parent()) {
            menuActionText = menuAction.parent()->objectName();
        }
        if ((menuActionText != "actionDeleteItem") && (menuActionText != "actionCut")) {
            removeActions(m_nosepieceActionList);
            m_nosepieceActionList.clear();
        }
    } else {
        AbstractShape::mousePressEvent(mouseEvent);
    }
}

/*
 * Create action "Hide consumption" or "Show consumption".
 */
void NosepieceShape::createAction()
{
    QString addConsumption{m_showConsumption ? QObject::tr("Hide consumption") : QObject::tr("Show consumption")};
    m_addConsumptionAction.reset(new QAction(addConsumption));
    m_addConsumptionAction->setToolTip(QObject::tr("Show or hide consumption"));
    //Allows you to use QObject::connect without inheriting a class from QObject.
    auto showConsumption{[&](){m_showConsumption ? consumptionShow(false) : consumptionShow(true);}};
    QObject::connect(m_addConsumptionAction.get(), &QAction::triggered, showConsumption);
    m_nosepieceActionList.append(m_addConsumptionAction.get());
}

/*
 * This method shows or hides the consumption of the nosepiece in the drawing
 */
void NosepieceShape::consumptionShow(bool showConsumption)
{
    if (showConsumption) {
            if (m_nosepieceConsumption == nullptr) {
                m_nosepieceConsumption = new QGraphicsTextItem(this);
                m_nosepieceConsumption->setPlainText("50");
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

/*
 * Draws a nosepiece and, when resizing, automatically adjusts the number of
 * steps and the distance between them.
 */
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

    if (m_nosepieceConsumption != nullptr) {
        qreal consumptionWidth{m_nosepieceConsumption->boundingRect().width()};
        qreal consumptionHeight{m_nosepieceConsumption->boundingRect().height()};
        m_nosepieceConsumption->setPos(m_nosepieceRect.center().x() - consumptionWidth
                                       , m_nosepieceRect.top() + m_nosepieceRect.height() / 6.0 + consumptionHeight);
    }
}

/*!
 * Reimplements: EquipmentShape::shapeType().
 * Required to determine the actual type of the object.
 *
 * \return Returns the type of equipment shape "Nosepiece".
 * \sa ShapeType.
 */
EquipmentShape::ShapeType NosepieceShape::shapeType() const
{
    return m_equipmentType;
}
