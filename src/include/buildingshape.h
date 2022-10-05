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

#ifndef BUILDINGSHAPE_H
#define BUILDINGSHAPE_H

#include "../include/abstractshape.h"

#include <QBrush>
#include <QPen>
#include <QSet>
#include <QSharedPointer>


class BuildingShape : public AbstractShape
{
public:
    enum { Type = UserType + 400 };
    enum ShapeType { Wall, Window, Door, Open };

    struct BuildingShapeDeleter
    {
        BuildingShapeDeleter() = delete;
        static inline void cleanup(BuildingShape *buildingShape) {buildingShape->deleter();}
    };


    static BuildingShape *createBuildingShape(ShapeType shapeType, QGraphicsItem *parent = nullptr);

    inline int type() const override {return Type;}

    virtual QPixmap image() = 0;
    virtual ShapeType shapeType() const = 0;
    virtual void setRect(const QRectF &rect) = 0;
    virtual QRectF rect() const = 0;


protected:
    explicit BuildingShape(QGraphicsItem *parent = nullptr);
    virtual ~BuildingShape() = 0;
    virtual void deleter();

private:
    Q_DISABLE_COPY(BuildingShape)
//    friend struct BuildingShapeDeleter;
//    void drawShape(QPainter *painter);
//    qreal   frameWidth;
};

// TODO сделать привязку стен друг к другу
// TODO сделать настройку толщины стены из основного и контектстного меню
class WallShape : public BuildingShape
{
public:
    enum { Type = UserType + 401};

    explicit WallShape(QGraphicsItem *parent = nullptr);

    inline int type() const override {return Type;}
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;
    QRectF boundingRect() const override;
    QPainterPath shape() const override;

    QPixmap image() override;
    ShapeType shapeType() const override;
    void setRect(const QRectF &rect) override;
    QRectF rect() const override;

    QSet<WallShape *> collidingWalls();
    bool removeCollidingWall(WallShape *wallShape);

protected:
    ~WallShape() = default;

private:
    Q_DISABLE_COPY(WallShape)

    void setCollidingWalls();
    bool collidingWallsIsEmpty();

    QSet<WallShape *>  m_collidingWallSet;
    const ShapeType m_wallType;
    QRectF  m_wallRect;
};

// TODO сделать привязку деверей к стенам
class DoorShape :public BuildingShape
{
public:
    enum { Type = UserType + 402};
    enum DoorState { Open, Ajar, Close };
    enum LeafPosition { Left, Right };

    explicit DoorShape(QGraphicsItem *parent = nullptr);

    inline int type() const override {return Type;}
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;
    QRectF boundingRect() const override;
    QPainterPath shape() const override;

    QPixmap image() override;
    ShapeType shapeType() const override;
    void setRect(const QRectF &rect) override;
    QRectF rect() const override;

    DoorState doorState() const;
    void setDoorState(DoorState doorState);

    LeafPosition leafPosition() const;
    void setLeafPosition(LeafPosition leafPosition);

protected:
    ~DoorShape() = default;

    void mousePressEvent(QGraphicsSceneMouseEvent *mouseEvent) override;
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *mouseEvent) override;

private:
    Q_DISABLE_COPY(DoorShape)

    void drawDoor(QPainter *painter);
    void setDoor();
    void bindingWall();

    const int INIT_ANGLE = 1440; // 90 degrees

    const ShapeType m_doorType;
    DoorState   m_doorState;
    LeafPosition    m_leafPosition;
    QRectF  m_doorRect;
    QRectF  m_leftFrame;
    QRectF  m_rightFrame;
    QRectF  m_arcRectangle;
    QLineF  m_doorLeaf;
    int m_startAngle;
    int m_spanAngle;
    bool m_leftButtonPressed;
};
#endif // BUILDINGSHAPE_H
