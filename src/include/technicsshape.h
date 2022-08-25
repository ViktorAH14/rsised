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

#ifndef TECHNICSSHAPE_H
#define TECHNICSSHAPE_H

#include "abstractshape.h"

class TechnicsShape : public AbstractShape
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

    explicit TechnicsShape(ShapeType shapeType, QGraphicsItem *parent = nullptr);

    QRectF boundingRect() const override;
    int type() const override { return Type;}

    QPixmap image();
    ShapeType shapeType() const;

protected:
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;

private:
    void drawShape(QPainter *painter);

    ShapeType m_shapeType;
};

#endif // TECHNICSSHAPE_H
