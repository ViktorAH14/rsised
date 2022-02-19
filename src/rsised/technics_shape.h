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

#ifndef TECHNICS_SHAPE_H
#define TECHNICS_SHAPE_H

#include <QAbstractGraphicsShapeItem>

class SizeGripItem;

class TechnicsShape : public QAbstractGraphicsShapeItem
{
public:
    enum { Type = UserType + 20 };
    enum ShapeType { Base
                     , Tanker
                     , AutoPump
                     , FirstAid
                     , Emergency
                     , AutoLadder
                     , CrankLift
                     , TelescopicLift
                     , Hose
                     , Comm
                     , Tech_serv
                     , Smok_rem
                     , AutoPumpS
                     , CarriageCar_1
                     , CarriageCar_2
                     , Aerodrome
                     , Foam
                     , Combo
                     , Aerosol
                     , Powder
                     , Carbon
                     , GazWater
                     , Tracked
                     , Tank
                     , GDZS
                     , Waterproof
                     , Laboratory
                     , StaffCar
                     , Trailer
                     , Vessel
                     , Boat
                     , Train
                     , Plane
                     , Seaplane
                     , Helicopter
                     , MotoPump_1
                     , MotoPump_2
                     , TrailerPowder
                     , Adapted
                     , OtherAdapted
                     , Ambulance
                     , Police };

    TechnicsShape(QMenu *contextMenu, ShapeType shapeType, QGraphicsItem *parent = nullptr);

    QRectF boundingRect() const override; //TODO проверить реализацию для прочей техники
    int type() const override { return Type;}

    QPixmap image();
    void scaleTechnicsShape(const QRectF &newRect);
    ShapeType shapeType() const;

protected:
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;
    void mouseDoubleClickEvent(QGraphicsSceneMouseEvent *mouseEvent) override;
    void mouseMoveEvent(QGraphicsSceneMouseEvent *mouseEvent) override;
    bool sceneEvent(QEvent *event) override;
    void contextMenuEvent(QGraphicsSceneContextMenuEvent *event) override;
    void wheelEvent(QGraphicsSceneWheelEvent *wheelEvent) override;
    QVariant itemChange(GraphicsItemChange change, const QVariant &value) override;

private:
    void drawShape(QPainter *painter);
    ShapeType m_shapeType;
    SizeGripItem *m_sizeGripItem;
    QMenu *m_contextMenu;
};

#endif // TECHNICS_SHAPE_H
