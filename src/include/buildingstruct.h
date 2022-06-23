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

#ifndef BUILDINGSTRUCT_H
#define BUILDINGSTRUCT_H

#include "../include/abstractshape.h"

#include <QBrush>
#include <QSet>

class BuildingStruct : public AbstractShape
{
public:
    enum { Type = UserType + 40 };
    enum ShapeType { Wall, Window, Door, Open };

    BuildingStruct(ShapeType shapeType, QGraphicsItem *parent = nullptr);

    QRectF boundingRect() const override;
    QPainterPath shape() const override;
    int type() const override {return Type;}

    QPixmap image();
    ShapeType shapeType() const;
    void setRect(QRectF rect);
    QRectF getRect();

    bool collidingWallsIsEmpty();
    QSet<BuildingStruct *> getCollidingWalls();

protected:
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;

private:
    void drawShape(QPainter *painter);
    void setCollidingWals();

    QSet<BuildingStruct *>  collidingWalls;
    QRectF  shapeRect;
    QBrush  wallBrush;
    qreal   frameWidth;
    ShapeType   m_shapeType;
};

#endif // BUILDINGSTRUCT_H
