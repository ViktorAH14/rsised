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

/*!
 * \file
 * \brief This file contains a description of the class methods used by drawing
 * building structures.
 *
 * The buildingshape.h is a header file that contains a description of the
 * BuildingShape, WallShape, DoorShape, WindowShape, OpenShape, StairwellShape
 * and StairsShape classes.
 *
 * \copyright (C) 2022 by Viktor Ermolov <ermolovva@gmail.com>.
 * You can redistribute it and/or modify it under the terms of the
 * GNU General Public License as published by the Free Software Foundation,
 * either version 3 of the License, or (at your option) any later version.
 * \date May 25 2023
 * \author Ermolov V.A.
 */

/*!
 * \defgroup BuildingShapes Building shapes library
 * \brief This module is a building library of shapes for the RSiSed application.
 * \ingroup libshapes
 *
 * The module includes elements for creating building structures, walls,
 * windows, doors, openings, stairwells and stairs.
 */
///@{

#ifndef BUILDINGSHAPE_H
#define BUILDINGSHAPE_H

#include "abstractshape.h"

#include <QBrush>
#include <QPen>
#include <QSet>

QT_BEGIN_NAMESPACE
class QAction;
class QActionGroup;
QT_END_NAMESPACE

/*!
 * \brief The BuildingShape class is an interface class for creating building
 * shapes.
 *
 * The class has an available static factory function that returns a pointer
 * to the base class, with which instances of the corresponding classes are
 * created.
 *
 * \sa WallShape, DoorShape, WindowShape, OpenShape, StairwellShape
 * and StairsShape.
 */
class BuildingShape : public AbstractShape
{
public:
    //! This type information is used by qgraphicsitem_cast to distinguish between types.
    enum { Type = UserType + 400};

    //! Set of possible building shapes.
    enum ShapeType { Wall           //!< The wall shape.
                     , Door         //!< The door shape.
                     , Window       //!< The window shape.
                     , Open         //!< Shape of the opening.
                     , Stairwell    //!< The stairwell shape
                     , Stairs       //!< The stairs shape
    };

    /*!
     * \brief The BuildingShapeDeleter struct is a custom cleanup handler.
     *
     * BuildingShapeDeleter is a custom deleter class needed when creating
     * client-side objects using smart pointers.
     *
     * \sa deleter(), cleanup().
     */
    struct BuildingShapeDeleter
    {
        /*!
         * Constructs a BuildingShapeDeleter.
         * Creation of the BuildingShapeDeleter class is prohibited.
         */
        BuildingShapeDeleter() = delete;

        /*!
         * Static method remover.
         *
         * \param *buildingShape[in] The pointer to the object to be deleted.
         * \sa deleter().
         */
        static inline void cleanup(BuildingShape *buildingShape) {buildingShape->deleter();}
    };

    static BuildingShape *createBuildingShape(ShapeType shapeType, QGraphicsItem *parent = nullptr);

    /*!
     * This type information is used by qgraphicsitem_cast() to distinguish
     * between types.
     * All standard graphicsitem classes are associated with a unique value;
     * see QGraphicsItem::Type. The default implementation (in QGraphicsItem)
     * returns UserType. To enable use of qgraphicsitem_cast() with a custom
     * item, reimplement this function and declare a Type enum value equal to
     * your custom item's type. Custom items must return a value larger than
     * or equal to UserType (65536).
     *
     * \return Returns the type of an item as an int.
     */
    inline int type() const override {return Type;}

    /*!
     * A pure virtual method that needs to be overridden in a child class.
     * Required to create a shape icon in ShapeToolBox.
     * Used by the MainWindow::createBuildingShapeCellWidget() method to
     * create a shape icon in the ShapeToolBox.
     *
     * \return Returns a QPixmap object containing the shape image.
     */
    virtual QPixmap image() = 0;

    /*!
     * A pure virtual method that needs to be overridden in a child class.
     * Required to determine the actual type of the object.
     *
     * \return Returns the ShapeType (Wall or Door etc.).
     * \sa ShapeType.
     */
    virtual ShapeType shapeType() const = 0;

    /*!
     * A purel virtual method that needs to be overridden in a child class.
     * This method is used to set the size of the shape.
     *
     * \param rect[in] Sets the shape's size to be the given  rectangle.
     * \sa rect().
     */
    virtual void setRect(const QRectF &rect) = 0;

    /*!
     * A pure virtual method that needs to be overridden in a child class.
     *
     * \return Returns the shape`s rectangle.
     * \sa setRect()
     */
    virtual QRectF rect() const = 0;

    /*!
     * A pure virtual method that needs to be overriden in a child class.
     * This method is used to set the height of the shape.
     *
     * \param height[in] Sets the height of the shape to the given height.
     *
     * \sa height()
     */
    virtual void setHeight(const qreal &height) = 0;

    /*!
     * A pure virtual method that needs to be overriden in a child class.
     *
     * \return Returns the shape`s height.
     *
     * \sa setHeight()
     */
    virtual qreal height() const = 0;


protected:
    explicit BuildingShape(QGraphicsItem *parent = nullptr);
    virtual ~BuildingShape() = 0;
    virtual void deleter();

private:
    /*
     * This class contains a private copy constructor and assignment
     * operator to disable copying (the compiler gives an error message).
     * This makros defined in the qlobal.h file
    */
    Q_DISABLE_COPY(BuildingShape)
};

/*!
 * \brief The WallShape class provides an wall item.
 *
 * The WallShape class represents an image of a wall. It allows you to change
 * the size, position of the wall, the type and color of its fill. The overlap
 * of the walls with each other and their automatic connection are also
 * determined.
 *
 * \sa DoorShape, WindowShape, OpenShape, StairwellShape, StairsShape,
 * createBuildingShape().
 */
class WallShape : public BuildingShape
{
public:
    //! This type information is used by qgraphicsitem_cast to distinguish between types.
    enum { Type = UserType + 401};

    explicit WallShape(QGraphicsItem *parent = nullptr);

    /*!
     * All standard graphicsitem classes are associated with a unique value;
     * see QGraphicsItem::Type. This type information is used by
     * qgraphicsitem_cast() to distinguish between types. Custom items must
     * return a value larger than or equal to UserType (65536).
     *
     * \return Returns the type of an item as an int.
     */
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
    /*
     * This class contains a private copy constructor and assignment
     * operator to disable copying (the compiler gives an error message).
     * This makros defined in the qlobal.h file
    */
    Q_DISABLE_COPY(WallShape)

    void setCollidingWalls();
    bool collidingWallsIsEmpty();
    void bindingWall();

    QSet<WallShape *>  m_collidingWallSet;
    const ShapeType m_wallType;
    QRectF  m_wallRect;
    bool m_leftButtonPressed;
};

<<<<<<< HEAD
/*!
 * \brief The DoorShape class provides an door item.
 *
 * The DoorShape class represents an image of a door. Allows you to change the
 * size, position and degree of opening of the door. The doors are automatically
 * positioned and glued to the walls. Doors can open to the right or left.
 *
 * \sa WallShape, WindowShape, OpenShape, StairwellShape, StairsShape,
 * createBuildingShape().
 */
=======
>>>>>>> refs/remotes/origin/develop
class DoorShape :public BuildingShape
{
public:
    //! This type information is used by qgraphicsitem_cast to distinguish between types.
    enum { Type = UserType + 402 };
    //! Determines the degree of door opening.
    enum DoorState { Open       //!< The door is open.
                     , Ajar     //!< The door is ajar.
                     , Close    //!< The door is closed.
    };
    //! Determines the door opening direction (left or right).
    enum LeafPosition { Left    //! The door opens to the left.
                        , Right //! The door opens to the right.
    };

    explicit DoorShape(QGraphicsItem *parent = nullptr);

    /*!
     * All standard graphicsitem classes are associated with a unique value;
     * see QGraphicsItem::Type. This type information is used by
     * qgraphicsitem_cast() to distinguish between types. Custom items must
     * return a value larger than or equal to UserType (65536).
     *
     * \return Returns the type of an item as an int.
     */
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
    /*
     * This class contains a private copy constructor and assignment
     * operator to disable copying (the compiler gives an error message).
     * This makros defined in the qlobal.h file
    */
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
    QList<QAction *> m_doorActionList;
};

/*!
 * \brief The WindowShape class provides an window item.
 *
 * The WindowShape class represents an image of a window. Allows you to change
 * the size and position of the window. The window are automatically positioned
 * and glued to the walls.
 *
 * \sa WallShape, DoorShape, OpenShape, StairwellShape, StairsShape,
 * createBuildingShape().
 */
class WindowShape : public BuildingShape
{
public:
    //! This type information is used by qgraphicsitem_cast to distinguish between types.
    enum { Type = UserType + 403 };

    explicit WindowShape(QGraphicsItem *parent = nullptr);

    /*!
     * All standard graphicsitem classes are associated with a unique value;
     * see QGraphicsItem::Type. This type information is used by
     * qgraphicsitem_cast() to distinguish between types. Custom items must
     * return a value larger than or equal to UserType (65536).
     *
     * \return Returns the type of an item as an int.
     */
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
    /*
     * This class contains a private copy constructor and assignment
     * operator to disable copying (the compiler gives an error message).
     * This makros defined in the qlobal.h file
    */
    Q_DISABLE_COPY(WindowShape)

    void bindingWall();

    const ShapeType m_windowType;
    QRectF m_windowRect;
    bool m_leftButtonPressed;
};

/*!
 * \brief The OpenShape class provides a wall opening item.
 *
 * The OpenShape class represents an image of an opening in a wall. Allows you
 * to change the size and position of the opening in the wall. The wall opening
 * is automatically positioned and stuck to the wall.
 *
 * \sa WallShape, DoorShape, WindowShape, StairwellShape, StairsShape,
 * createBuildingShape().
 */
class OpenShape : public BuildingShape
{
public:
    //! This type information is used by qgraphicsitem_cast to distinguish between types.
    enum { Type = UserType + 404 };

    explicit OpenShape(QGraphicsItem *parent = nullptr);

    /*!
     * All standard graphicsitem classes are associated with a unique value;
     * see QGraphicsItem::Type. This type information is used by
     * qgraphicsitem_cast() to distinguish between types. Custom items must
     * return a value larger than or equal to UserType (65536).
     *
     * \return Returns the type of an item as an int.
     */
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
    /*
     * This class contains a private copy constructor and assignment
     * operator to disable copying (the compiler gives an error message).
     * This makros defined in the qlobal.h file
    */
    Q_DISABLE_COPY(OpenShape)

    void bindingWall();

    const ShapeType m_openType;
    QRectF m_openRect;
    bool m_leftButtonPressed;
};

/*!
 * \brief The StairwellShape class provides a stairwell item.
 *
 * The SairwellShape class represents an image of a stairwell. Allows you to
 * change the size and position of the stairwell.
 *
 * \sa WallShape, DoorShape, WindowShape, OpenShape, StairsShape,
 * createBuildingShape().
 */
class StairwellShape : public BuildingShape
{
public:
    //! This type information is used by qgraphicsitem_cast to distinguish between types.
    enum { Type = UserType + 405 };

    explicit StairwellShape(QGraphicsItem *parent = nullptr);

    /*!
     * All standard graphicsitem classes are associated with a unique value;
     * see QGraphicsItem::Type. This type information is used by
     * qgraphicsitem_cast() to distinguish between types. Custom items must
     * return a value larger than or equal to UserType (65536).
     *
     * \return Returns the type of an item as an int.
     */
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
    /*
     * This class contains a private copy constructor and assignment
     * operator to disable copying (the compiler gives an error message).
     * This makros defined in the qlobal.h file
    */
    Q_DISABLE_COPY(StairwellShape)

    void drawStairwell(QPainter *painter);

    const ShapeType m_stairwellType;
    QRectF m_stairwellRect;
};

/*!
 * \brief The StairsShape class provides a stair item.
 *
 * The SairsShape class represents an image of a staircase. Allows you to change
 * the size and position of the stairs.
 *
 * \sa WallShape, DoorShape, WindowShape, OpenShape, StairwellShape,
 * createBuildingShape().
 */
class StairsShape :public BuildingShape
{
public:
    //! This type information is used by qgraphicsitem_cast to distinguish between types.
    enum { Type = UserType + 406 };

    explicit StairsShape(QGraphicsItem *parent = nullptr);

    /*!
     * All standard graphicsitem classes are associated with a unique value;
     * see QGraphicsItem::Type. This type information is used by
     * qgraphicsitem_cast() to distinguish between types. Custom items must
     * return a value larger than or equal to UserType (65536).
     *
     * \return Returns the type of an item as an int.
     */
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
    /*
     * This class contains a private copy constructor and assignment
     * operator to disable copying (the compiler gives an error message).
     * This makros defined in the qlobal.h file
    */
    Q_DISABLE_COPY(StairsShape)

    void drawStairs(QPainter *painter);

    const ShapeType m_stairsType;
    QRectF m_stairsRect;
};

#endif // BUILDINGSHAPE_H
///@}
