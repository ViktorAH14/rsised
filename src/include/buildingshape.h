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

QT_BEGIN_NAMESPACE
class QAction;
class QActionGroup;
QT_END_NAMESPACE

class BuildingShape : public AbstractShape
{
public:
    enum { Type = UserType + 400 };
    enum ShapeType { Wall, Door, Window, Open, Stairwell, Stairs };

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
    virtual void setHeight(const qreal &height) = 0;
    virtual qreal height() const = 0;


protected:
    explicit BuildingShape(QGraphicsItem *parent = nullptr);
    virtual ~BuildingShape() = 0;
    virtual void deleter();

private:
    Q_DISABLE_COPY(BuildingShape)
};

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
    void setHeight(const qreal &height) override;
    qreal height() const override;


    QSet<WallShape *> collidingWalls();
    bool removeCollidingWall(WallShape *wallShape);

protected:
    ~WallShape() = default;

    void mousePressEvent(QGraphicsSceneMouseEvent *mouseEvent) override;
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *mouseEvent) override;

private:
    Q_DISABLE_COPY(WallShape)

    void setCollidingWalls();
    bool collidingWallsIsEmpty();
    void bindingWall();

    QSet<WallShape *>  m_collidingWallSet;
    const ShapeType m_wallType;
    QRectF  m_wallRect;
    bool m_leftButtonPressed;
};


class DoorShape :public BuildingShape
{
public:
    enum { Type = UserType + 402 };
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
    void setHeight(const qreal &height) override;
    qreal height() const override;

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
    void createAction();

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

    QScopedPointer<QAction> m_doorLeafPosAction;
    QScopedPointer<QAction> m_doorOpenAction;
    QScopedPointer<QAction> m_doorAjarAction;
    QScopedPointer<QAction> m_doorCloseAction;
    QScopedPointer<QActionGroup> m_doorStateActionGroup;
    QList<QAction *> m_actionList;
};

class WindowShape : public BuildingShape
{
public:
    enum { Type = UserType + 403 };

    explicit WindowShape(QGraphicsItem *parent = nullptr);

    inline int type() const override {return Type;}
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;
    QRectF boundingRect() const override;
    QPainterPath shape() const override;

    QPixmap image() override;
    ShapeType shapeType() const override;
    void setRect(const QRectF &rect) override;
    QRectF rect() const override;
    void setHeight(const qreal &height) override;
    qreal height() const override;

protected:
    ~WindowShape() = default;

    void mousePressEvent(QGraphicsSceneMouseEvent *mouseEvent) override;
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *mouseEvent) override;

private:
    Q_DISABLE_COPY(WindowShape)

    void bindingWall();

    const ShapeType m_windowType;
    QRectF m_windowRect;
    bool m_leftButtonPressed;
};

class OpenShape : public BuildingShape
{
public:
    enum { Type = UserType + 404 };

    explicit OpenShape(QGraphicsItem *parent = nullptr);

    inline int type() const override {return Type;}
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;
    QRectF boundingRect() const override;
    QPainterPath shape() const override;

    QPixmap image() override;
    ShapeType shapeType() const override;
    void setRect(const QRectF &rect) override;
    QRectF rect() const override;
    void setHeight(const qreal &height) override;
    qreal height() const override;

protected:
    ~OpenShape() = default;

    void mousePressEvent(QGraphicsSceneMouseEvent *mouseEvent) override;
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *mouseEvent) override;

private:
    Q_DISABLE_COPY(OpenShape)

    void bindingWall();

    const ShapeType m_openType;
    QRectF m_openRect;
    bool m_leftButtonPressed;
};

class StairwellShape : public BuildingShape
{
public:
    enum { Type = UserType + 405 };

    explicit StairwellShape(QGraphicsItem *parent = nullptr);

    inline int type() const override {return Type;}
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;
    QRectF boundingRect() const override;
    QPainterPath shape() const override;

    QPixmap image() override;
    ShapeType shapeType() const override;
    void setRect(const QRectF &rect) override;
    QRectF rect() const override;
    void setHeight(const qreal &height) override;
    qreal height() const override;

protected:
    ~StairwellShape() = default;

private:
    Q_DISABLE_COPY(StairwellShape)

    void drawStairwell(QPainter *painter);

    const ShapeType m_stairwellType;
    QRectF m_stairwellRect;
};

class StairsShape :public BuildingShape
{
public:
    enum { Type = UserType + 406 };

    explicit StairsShape(QGraphicsItem *parent = nullptr);

    inline int type() const override {return Type;}
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;
    QRectF boundingRect() const override;
    QPainterPath shape() const override;

    QPixmap image() override;
    ShapeType shapeType() const override;
    void setRect(const QRectF &rect) override;
    QRectF rect() const override;
    void setHeight(const qreal &height) override;
    qreal height() const override;

protected:
    ~StairsShape() = default;

private:
    Q_DISABLE_COPY(StairsShape)

    void drawStairs(QPainter *painter);

    const ShapeType m_stairsType;
    QRectF m_stairsRect;
};

#endif // BUILDINGSHAPE_H
