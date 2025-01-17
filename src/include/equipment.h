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

#ifndef DEVICESHAPE_H
#define DEVICESHAPE_H

#include "abstractshape.h"

class DeviceShape : public AbstractShape
{
public:
    enum {Type = UserType + 30};
    enum ShapeType { Barrel_0
                     , Barrel_1
                     , Barrel_2
                     , Barrel_3
                     , Barrel_4
                     , Barrel_5
                     , Barrel_6
                     , Carriage_1
                     , Carriage_2
                     , Carriage_3
                     , Carriage_4
                     , Carriage_5
                     , Branches_2
                     , Branches_3
                     , Branches_4
                     , Ladder_1
                     , Ladder_2
                     , Ladder_3
                     , Collector
                     , Bridge
                     , Reel
                     , Reel_mobile
                     , HydrElevator
                     , Foam_mix
                     , Column
                     , SmokePump_1
                     , SmokePump_2
                     , Hose
                     , FoamLift_1
                     , FoamLift_2 };

    explicit DeviceShape(ShapeType shapeType, QGraphicsItem *parent = nullptr);

    QRectF boundingRect() const override;
    int type() const override {return Type;}

    QPixmap image();
    ShapeType shapeType() const;

protected:
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;

private:
    void drawShape(QPainter *painter);

    ShapeType m_shapeType;
};

#endif // DEVICESHAPE_H
