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

#include <stdlib.h>
#include "../include/buildingshape.h"

#include <QtMath>
#include <QPainter>
#include <QMenu>
#include <QActionGroup>
#include <QGraphicsSceneEvent>
#include <QStyleOptionGraphicsItem>

/*!
 * Constructs a BuildingShape. The constructor is declared protected because
 * creating an abstract class is prohibited.
 *
 * \param parent[in] A pointer to the parent object is passed to the AbtractShape
 * constructor. This is part of the memory management strategy used in
 * Qt-Framework.
 */
BuildingShape::BuildingShape(QGraphicsItem *parent)
    : AbstractShape(parent)
{
}

/*!
 * Destoys the BuildingShape. Protected purely virtual destructor.
 * Defined as default.
 */
BuildingShape::~BuildingShape() = default;

/*!
 * The remover method is declared protected. This prevents the client from
 * calling deleter() directly and thus reduces the likelihood of errors
 * associated with deleting an object. Deleting objects involves the use of
 * the BuildingShapeDeleter deleter class and is oriented towards the use of
 * smart pointers.
 *
 * \sa BuildingShapeDeleter::cleanup()
 */
void BuildingShape::deleter()
{
    delete this;
}

/*!
 * This method creates a new object of the specified type and returns a pointer
 * to it cast to the BuildingShape type.
 *
 * \param shapeType[in] The type of object being created.
 * \param parent[in] A pointer to the parent object is passed to the
 * AbtractShape constructor. This is part of the memory management strategy used
 * in Qt-Framework.
 * \return Returns a pointer to the created object cast to the BuildingShape
 *  type
 */
BuildingShape *BuildingShape::createBuildingShape(ShapeType shapeType, QGraphicsItem *parent)
{
    BuildingShape *p_buildingShape{nullptr};
    switch (shapeType) {
    case Wall:
        p_buildingShape = new WallShape(parent);
        break;
    case Door:
        p_buildingShape = new DoorShape(parent);
        break;
    case Window:
        p_buildingShape = new WindowShape(parent);
        break;
    case Open:
        p_buildingShape = new OpenShape(parent);
        break;
    case Stairwell:
        p_buildingShape = new StairwellShape(parent);
        break;
    case Stairs:
        p_buildingShape = new StairsShape(parent);
        break;
    default:
        break;
    }
    return p_buildingShape;
}

/*!
 * Constructs an WallShape class. The default wall dimensions are 60x10 pixels.
 * The outline is black, thickness 1 pixel. The fill is light gray. The
 * ItemSendsGeometryChanges and AcceptHoverEvents flags are set to true.
 *
 * \param parent[in] A pointer to the parent object is passed to the
 * QGraphicsItem constructor. This is part of the memory management strategy
 * used in Qt-Framework.
 */
WallShape::WallShape(QGraphicsItem *parent)
    : BuildingShape(parent)
    , m_wallType{Wall}
    , m_wallRect{QRectF(-30.0, -5.0, 60.0, 10)}
    , m_leftButtonPressed{false}
{
    setFlag(ItemSendsGeometryChanges, true);
    setAcceptHoverEvents(true);
    setPen(QPen(Qt::black, 1));
    setBrush(Qt::lightGray);
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
void WallShape::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(widget);

    painter->setRenderHint(QPainter::Antialiasing);
    painter->setRenderHint(QPainter::SmoothPixmapTransform);
    painter->setPen(pen());
    painter->setBrush(brush());
    painter->setBackgroundMode(Qt::OpaqueMode);

    setCollidingWalls();
    if (m_collidingWallSet.isEmpty()) {
        painter->drawRect(rect());
    } else {
        QPainterPath fillPath;
        fillPath.addRect(rect());
        painter->fillPath(fillPath, brush());
        QPainterPath wallPath;
        wallPath.setFillRule(Qt::WindingFill);
        wallPath.addRect(rect());
        for (WallShape *p_wallShape : qAsConst(m_collidingWallSet))
            wallPath.addPolygon(mapFromItem(p_wallShape, p_wallShape->rect()));

        painter->strokePath(wallPath.simplified(), pen());
    }

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
 * \return Returns the outer bounds of the wall as a rectangle.
 *
 * \sa shape(), contains().
 */
QRectF WallShape::boundingRect() const
{
    QRectF boundingRect{m_wallRect};
    qreal halfpw{pen().style() == Qt::NoPen ? qreal(0.0) : pen().widthF() / 2};
    if (halfpw > 0.0)
        boundingRect.adjust(-halfpw, -halfpw, halfpw, halfpw);

    return boundingRect;
}


/*!
 * Reimplements: QGraphicsItem::shape().
 * The shape is used for many things, including collision detection, hit tests,
 * and for the QGraphicsScene::items() functions. This function is called by
 * the default implementations of contains() and collidesWithPath(). The wall
 * outline is included in the element shape.
 *
 * \return Returns the shape of this item as a QPainterPath in local coordinates.
 *
 * \sa boundingRect(), contains().
 */
QPainterPath WallShape::shape() const
{
    QPainterPath path;
    path.addRect(rect());

    return shapeFromPath(path);
}

/*!
 * Reimplements: BuildingShape::image().
 * Required to create a shape icon in ShapeToolBox. Used by the
 * MainWindow::createBuildingShapeCellWidget() method to create an wall icon
 * in the ShapeToolBox.
 *
 * \return Returns a QPixmap object containing the shape image.
 */
QPixmap WallShape::image()
{
    qreal pixmapWidth{boundingRect().width()};
    qreal pixmapHeight{boundingRect().height()};
    QPixmap pixmap(pixmapWidth, pixmapHeight);
    pixmap.fill(Qt::transparent);

    QPainter painter(&pixmap);
    painter.setPen(pen());
    painter.setBrush(brush());
    painter.translate(pixmapWidth / 2.0, pixmapHeight / 2.0);
    painter.drawRect(rect());

    return pixmap;
}

/*!
 * Reimplements: BuildingShape::shapeType().
 * Required to determine the actual type of the object.
 *
 * \return Returns the type of building shape "Wall".
 * \sa ShapeType.
 */
BuildingShape::ShapeType WallShape::shapeType() const
{
    return m_wallType;
}

/*!
 * Reimplements: BuildingShape::setRect().
 * This method is used to set the size of the shape.
 *
 * \param rect[in] Sets the shape's size to be the given  rectangle.
 * \sa rect().
 */
void WallShape::setRect(const QRectF &rect)
{
    if (m_wallRect == rect)
        return;

    prepareGeometryChange();
    m_wallRect.setRect(rect.topLeft().x(), rect.topLeft().y(), rect.width(), rect.height());
    update();
}

/*!
 * Reimplements: BuildingShape::rect().
 * This is the outer bounds shape whitout pen width.
 *
 * \return Returns the shape's rectangle.
 * \sa setRect().
 */
QRectF WallShape::rect() const
{
    return m_wallRect;
}

/*!
 * Reimplements: BuildingShape::setHeight().
 * Sets the height of the shape.
 *
 * \param height[in] Sets the height of the shape to the given height.
 * \sa height().
 */
void WallShape::setHeight(const qreal &height)
{
    if (m_wallRect.height() == height)
        return;

    qreal oldHeight{m_wallRect.height()};
    prepareGeometryChange();
    m_wallRect.setHeight(height);
    qreal dy{(m_wallRect.height() - oldHeight) / 2};
    m_wallRect.moveTo(QPointF(m_wallRect.x(), m_wallRect.y() - dy));
    update();
}

/*!
 * Reimplements: BuildingShape::height().
 *
 * \return Returns the shape's height.
 * \sa setHeight().
 */
qreal WallShape::height() const
{
    return m_wallRect.height();
}

/*!
 * The method is necessary to determine the walls intersecting with a given wall.
 *
 * \return Returns a set of pointers to walls intersecting with a given wall.
 * \sa removeCollidingWall().
 */
QSet<WallShape *> WallShape::collidingWalls()
{
    return m_collidingWallSet;
}

/*!
 * Removes a wall from the set that intersects the given wall.
 *
 * \param wallShape[in] Pointer to the wall that needs to be removed from the
 * set.
 * \return In case of successful deletion, returns true and vice versa.
 * \sa collidingWalls().
 */
bool WallShape::removeCollidingWall(WallShape *wallShape)
{
    return m_collidingWallSet.remove(wallShape);
}

/*!
 * Reimplements: AbstractShape::mousePressEvent().
 * This method sets the left mouse button click flag to true. Used to tie walls
 * to each other.
 *
 * \param mouseEvent[in] Pointer to the QGraphicsSceneMouseEvent class.
 * \sa mouseReleaseEvent().
 */
void WallShape::mousePressEvent(QGraphicsSceneMouseEvent *mouseEvent)
{
    if (mouseEvent->buttons() == Qt::LeftButton) {
        m_leftButtonPressed = true;
    } else {
        AbstractShape::mousePressEvent(mouseEvent);
    }
}

/*!
 * Reimplements: AbstractShape::mouseReleaseEvent().
 * This method is used to tie closely spaced walls to each other.
 *
 * \param mouseEvent[in] Pointer to the QGraphicsSceneMouseEvent class.
 * \sa mousePressEvent().
 */
void WallShape::mouseReleaseEvent(QGraphicsSceneMouseEvent *mouseEvent)
{
    if (m_leftButtonPressed && !collidingWallsIsEmpty()) {
        bindingWall();
        m_leftButtonPressed = false;
    }

    QGraphicsItem::mouseReleaseEvent(mouseEvent);
}

/*
 * Creates a set of intersecting walls. Necessary to create a common boundary of
 *intersecting walls.
 */
void WallShape::setCollidingWalls()
{
    m_collidingWallSet.clear();
    QList<QGraphicsItem *> collidingShapeList{collidingItems()};
    for (QGraphicsItem *p_shape : qAsConst(collidingShapeList)) {
        if (WallShape *p_wallShape = dynamic_cast<WallShape *>(p_shape)) {
            m_collidingWallSet.insert(p_wallShape);
            if (!p_wallShape->collidingWallsIsEmpty())
                m_collidingWallSet += p_wallShape->collidingWalls();
        }
    }
    m_collidingWallSet.remove(this);
}

bool WallShape::collidingWallsIsEmpty()
{
    return m_collidingWallSet.isEmpty() ? true : false;
}

/*
 *Ties nearby walls to each other.
 */
void WallShape::bindingWall()
{
    qreal bindingOffset{m_wallRect.height() < 10 ? m_wallRect.height() - 1 : m_wallRect.height() / 2};
    prepareGeometryChange();
    for (WallShape *p_collidingWall : qAsConst(m_collidingWallSet)) {
        QRectF collidingRect{mapRectFromItem(p_collidingWall, p_collidingWall->rect())};
        if ((qAbs(m_wallRect.left() - collidingRect.left())) < bindingOffset) {
            qreal left{collidingRect.left()};
            m_wallRect.setLeft(left);
        }
        if ((qAbs(m_wallRect.right() - collidingRect.right())) < bindingOffset) {
            qreal right{collidingRect.right()};
            m_wallRect.setRight(right);
        }
    }
    update();
}

/*!
 * Constructs a DoorShape class.
 *
 * \param parent[in] A pointer to the parent object is passed to the
 * QGraphicsItem constructor. This is part of the memory management strategy
 * used in Qt-Framework.
 */
DoorShape::DoorShape(QGraphicsItem *parent)
    : BuildingShape(parent)
    , m_doorType{Door}
    , m_doorState{Open}
    , m_leafPosition{Right}
    , m_doorRect{QRectF()}
    , m_leftFrame{QRectF()}
    , m_rightFrame{QRectF()}
    , m_arcRectangle{QRectF()}
    , m_startAngle{INIT_ANGLE}
    , m_spanAngle{INIT_ANGLE}
    , m_leftButtonPressed{false}
{
    switch (m_doorState) {
    case Open:
        m_doorRect.setRect(-30.0, 20.0, 60.0, 10.0);
        break;
    case Ajar:
        m_doorRect.setRect(-30.0, 12, 60.0, 10.0);
        break;
    case Close:
        m_doorRect.setRect(-30.0, -5.0, 60.0, 10.0);
    default:
        break;
    }

    setFlag(ItemSendsGeometryChanges, true);
    setFlag(ItemSendsScenePositionChanges, true);
    setAcceptHoverEvents(true);
    setDoor();
    setPen(QPen(Qt::black, 1));
    setBrush(QBrush(Qt::white));
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
void DoorShape::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(widget);

    painter->setRenderHint(QPainter::Antialiasing);
    painter->setRenderHint(QPainter::SmoothPixmapTransform);

    painter->setPen(QPen(Qt::NoPen));
    painter->setBrush(brush());
    painter->drawRect(m_doorRect);

    drawDoor(painter);

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
 * \return Returns the outer bounds of the door as a rectangle.
 *
 * \sa shape(), contains().
 */
QRectF DoorShape::boundingRect() const
{
    QRectF boundingRect{m_leftFrame.left(), m_leftFrame.top() - qFabs(m_doorLeaf.dy())
                , m_doorRect.width(), m_doorRect.height() + qFabs(m_doorLeaf.dy())};
    qreal halfpw{pen().style() == Qt::NoPen ? qreal(0.0) : pen().widthF() / 2};
    if (halfpw > 0.0)
        boundingRect.adjust(-halfpw, -halfpw, halfpw, halfpw);

    return boundingRect;
}

/*!
 * Reimplements: QGraphicsItem::shape().
 * The shape is used for many things, including collision detection, hit tests,
 * and for the QGraphicsScene::items() functions. This function is called by
 * the default implementations of contains() and collidesWithPath(). The door
 * outline is included in the element shape.
 *
 * \return Returns the shape of this item as a QPainterPath in local coordinates.
 *
 *  \sa boundingRect(), contains().
 */
QPainterPath DoorShape::shape() const
{
    QPainterPath doorPath;
    doorPath.addRect(m_doorRect);
    doorPath.addRect(m_leftFrame);
    doorPath.addRect(m_rightFrame);
    doorPath.moveTo(m_doorLeaf.p1());
    doorPath.moveTo(m_doorLeaf.p2());
    doorPath.arcTo(m_arcRectangle, m_startAngle, m_spanAngle);

    return shapeFromPath(doorPath);
}

/*!
 * Reimplements: BuildingShape::image().
 * Required to create a shape icon in ShapeToolBox. Used by the
 * MainWindow::createBuildingShapeCellWidget() method to create a door
 * icon in the ShapeToolBox.
 *
 * \return Returns a QPixmap object containing the shape image.
 */
QPixmap DoorShape::image()
{
    qreal pixmapWidth{boundingRect().width()};
    qreal pixmapHeight{boundingRect().height()};
    QPixmap pixmap(pixmapWidth, pixmapHeight);
    pixmap.fill(Qt::transparent);

    QPainter painter(&pixmap);
    painter.translate(pixmapWidth / 2.0, pixmapHeight / 2.0);
    drawDoor(&painter);

    return pixmap;
}

/*!
 * Reimplements: BuildingShape::shapeType().
 * Required to determine the actual type of the object.
 *
 * \return Returns the type of building shape "Door".
 * \sa ShapeType.
 */
BuildingShape::ShapeType DoorShape::shapeType() const
{
    return m_doorType;
}

/*!
 * Reimplements: BuildingShape::setRect().
 * This method is used to set the size of the shape.
 *
 * \param rect[in] Sets the shape's size to be the given  rectangle.
 * \sa rect().
 */
void DoorShape::setRect(const QRectF &rect)
{
    prepareGeometryChange();
    m_doorRect.setRect(rect.topLeft().x(), rect.topLeft().y(), rect.width(), rect.height());
    update();
}

/*!
 * Reimplements: BuildingShape::rect().
 * This is the outer bounds shape whitout pen width.
 *
 * \return Returns the shape's rectangle.
 * \sa setRect().
 */
QRectF DoorShape::rect() const
{
    return m_doorRect;
}

/*!
 * Reimplements: BuildingShape::setHeight().
 * Sets the height of the shape.
 *
 * \param height[in] Sets the height of the shape to the given height.
 * \sa height().
 */
void DoorShape::setHeight(const qreal &height)
{
    m_doorRect.setHeight(height);
}

/*!
 * Reimplements: BuildingShape::height().
 *
 * \return Returns the shape's height.
 * \sa setHeight().
 */
qreal DoorShape::height() const
{
    return m_doorRect.height();
}

/*!
 * Returns the current state of the door.
 *
 * \return Returns current door state (open or ajar or close).
 * \sa setDoorState(), DoorShape::DoorState.
 */
DoorShape::DoorState DoorShape::doorState() const
{
    return m_doorState;
}

/*!
 * Sets state of the door.
 *
 * \param doorState[in] Sets the current door state according to the doorState.
 * \sa doorState(), DoorShape::DoorState.
 */
void DoorShape::setDoorState(DoorState doorState)
{
    prepareGeometryChange();
    m_doorState = doorState;
    update();
}

/*!
 * Returns the current position of the door leaf.
 *
 * \return Returns the current position of the door leaf (Left or Right).
 * \sa setLeafPosition(), DoorShape::LeafPosition.
 */
DoorShape::LeafPosition DoorShape::leafPosition() const
{
    return m_leafPosition;
}

/*!
 * Sets the current position of the door leaf (left or right).
 *
 * \param leafPosition[in] The current position of the door leaf is set in
 * accordance with the parameter.
 * \sa leafPosition(), DoorShape::LeafPosition.
 */
void DoorShape::setLeafPosition(LeafPosition leafPosition)
{
    prepareGeometryChange();
    m_leafPosition = leafPosition;
    update();
}

/*!
 * Reimplements: AbstractShape::mousePressEvent().
 * If the left mouse button is pressed, this method is used to snap the door to
 * the wall it intersects. The right mouse button pressed is used to create a
 * door context menu.
 *
 * \param mouseEvent[in] Pointer to the QGraphicsSceneMouseEvent class.
 * \sa mouseReleaseEvent().
 */
void DoorShape::mousePressEvent(QGraphicsSceneMouseEvent *mouseEvent)
{
    switch (mouseEvent->buttons()) {
    case Qt::LeftButton:
        m_leftButtonPressed = true;
        break;
    case Qt::RightButton: {
        createAction();
        addActions(m_doorActionList);
        QAction menuAction{menu()->exec(mouseEvent->screenPos())};
        QString menuActionText;
        if (menuAction.parent()) {
            menuActionText = menuAction.parent()->objectName();
        }
        if ((menuActionText != "actionDeleteItem") && (menuActionText != "actionCut")) {
            removeActions(m_doorActionList);
            m_doorActionList.clear();
        }
    }
        break;
    default:
        AbstractShape::mousePressEvent(mouseEvent);
        break;
    }
}

/*!
 * Reimplements: AbstractShape::mouseReleaseEvent().
 * The method is used to position and link a door to an intersecting wall.
 *
 * \param mouseEvent[in] Pointer to the QGraphicsSceneMouseEvent class.
 * \sa mousePressEvent().
 */
void DoorShape::mouseReleaseEvent(QGraphicsSceneMouseEvent *mouseEvent)
{
    if (m_leftButtonPressed) {
        bindingWall();
        m_leftButtonPressed = false;
    }

    AbstractShape::mouseReleaseEvent(mouseEvent);
}

void DoorShape::drawDoor(QPainter *painter)
{
    setDoor();
    painter->setPen(pen());
    painter->drawRect(m_leftFrame);
    painter->drawRect(m_rightFrame);
    painter->drawLine(m_doorLeaf);
    painter->drawArc(m_arcRectangle, m_startAngle, m_spanAngle);
}

/*
 * Sets door parameters such as the degree of opening (open, ajar or closed) and
 * the location of the door leaf (left or right).
 */
void DoorShape::setDoor()
{
    qreal frameWidth{m_doorRect.height() / 2};
    qreal frameHeight{m_doorRect.height()};
    m_leftFrame.setRect(m_doorRect.left(), m_doorRect.top(), frameWidth, frameHeight);
    qreal rightFrame_left((m_doorRect.right() - m_doorRect.height() / 2));
    m_rightFrame.setRect(rightFrame_left, m_doorRect.top(), frameWidth, frameHeight);

    if (m_leafPosition == Right) {
        m_doorLeaf.setPoints(m_rightFrame.topLeft(), m_leftFrame.topRight());
        switch (m_doorState) {
        case Open:
            m_doorLeaf.setAngle(90);
            break;
        case Ajar:
                m_doorLeaf.setAngle(135);
            break;
        case Close:
                m_doorLeaf.setAngle(180);
            break;
        default:
            break;
        }
        m_arcRectangle.setRect(m_leftFrame.right(), m_leftFrame.top() - qFabs(m_doorLeaf.length())
                            , (m_doorLeaf.length() * 2), (m_doorLeaf.length() * 2));
        m_startAngle = m_doorLeaf.angle() * 16;
        m_spanAngle = (180 - m_doorLeaf.angle()) * 16;
    } else {
        m_doorLeaf.setPoints(m_leftFrame.topRight(), m_rightFrame.topLeft());
        switch (m_doorState) {
        case Open:
            m_doorLeaf.setAngle(90);
            break;
        case Ajar:
                m_doorLeaf.setAngle(45);
            break;
        case Close:
                m_doorLeaf.setAngle(0);
            break;
        default:
            break;
        }
        m_arcRectangle.setRect(m_leftFrame.right() - m_doorLeaf.length()
                               , m_leftFrame.top() - m_doorLeaf.length()
                            , (m_doorLeaf.length() * 2), (m_doorLeaf.length() * 2));
        QLineF frameLine(m_doorRect.topLeft(), m_doorRect.topRight());
        m_startAngle = frameLine.angle() * 16;
        m_spanAngle = m_doorLeaf.angle() * 16;
    }
}

/*
 * Binds the door to the wall with which it intersects, and sets the width of
 * the door according to the width of the wall.
 */
void DoorShape::bindingWall()
{
    QList<QGraphicsItem *> collidingShapeList{collidingItems()};
    for (QGraphicsItem *p_shape : qAsConst(collidingShapeList)) {
        if (WallShape *p_collidingWall = dynamic_cast<WallShape *>(p_shape)) {
            prepareGeometryChange();
            setTransform(p_collidingWall->transform());
            QRectF wallRect{mapRectFromItem(p_collidingWall, p_collidingWall->boundingRect())};
            setRect(QRectF(m_doorRect.x(), wallRect.y(), m_doorRect.width(), wallRect.height()));
            setSelected(false);
            update();
            break;
        }
    }
}

/*
 * Creates the actions “Open the door”, “Ajar the door”, “Close the door” and
 * “Change the position of the door leaf”.
 */
void DoorShape::createAction()
{
    m_doorLeafPosAction.reset(new QAction(QObject::tr("Leaf change")));
    m_doorLeafPosAction->setToolTip(QObject::tr("Changing the position of the door leaf"));
    //Allows you to use QObject::connect without inheriting a class from QObject.
    auto doorLeaf{[&](){m_leafPosition == Left ? setLeafPosition(Right)
                                                 : setLeafPosition(Left);}};
    QObject::connect(m_doorLeafPosAction.get(), &QAction::triggered, doorLeaf);
    m_doorActionList.append(m_doorLeafPosAction.get());

    m_doorOpenAction.reset(new QAction(QObject::tr("Open door")));
    m_doorOpenAction->setToolTip(QObject::tr("Change the state of the door"));
    m_doorOpenAction->setCheckable(true);
    //Allows you to use QObject::connect without inheriting a class from QObject.
    auto setOpenState{[&](){setDoorState(Open);}};
    QObject::connect(m_doorOpenAction.get(), &QAction::triggered, setOpenState);
    m_doorActionList.append(m_doorOpenAction.get());

    m_doorAjarAction.reset(new QAction(QObject::tr("Ajar door")));
    m_doorAjarAction->setToolTip(QObject::tr("Change the state of the door"));
    m_doorAjarAction->setCheckable(true);
    //Allows you to use QObject::connect without inheriting a class from QObject.
    auto setAjarState{[&](){setDoorState(Ajar);}};
    QObject::connect(m_doorAjarAction.get(), &QAction::triggered, setAjarState);
    m_doorActionList.append(m_doorAjarAction.get());

    m_doorCloseAction.reset(new QAction(QObject::tr("Close door")));
    m_doorCloseAction->setToolTip(QObject::tr("Change the state of the door"));
    m_doorCloseAction->setCheckable(true);
    //Allows you to use QObject::connect without inheriting a class from QObject.
    auto setCloseState{[&](){setDoorState(Close);}};
    QObject::connect(m_doorCloseAction.get(), &QAction::triggered, setCloseState);
    m_doorActionList.append(m_doorCloseAction.get());

    m_doorStateActionGroup.reset(new QActionGroup(nullptr));
    m_doorStateActionGroup->addAction(m_doorOpenAction.get());
    m_doorStateActionGroup->addAction(m_doorAjarAction.get());
    m_doorStateActionGroup->addAction(m_doorCloseAction.get());
    switch (m_doorState) {
    case Open:
        m_doorOpenAction->setChecked(true);
        break;
    case Ajar:
        m_doorAjarAction->setChecked(true);
        break;
    case Close:
        m_doorCloseAction->setChecked(true);
    default:
        break;
    }
}

/*!
 * Constructs a WindowShape class.
 *
 * \param parent[in] A pointer to the parent object is passed to the
 * QGraphicsItem constructor. This is part of the memory management strategy
 * used in Qt-Framework.
 */
WindowShape::WindowShape(QGraphicsItem *parent)
    : BuildingShape(parent)
    , m_windowType{Window}
    , m_windowRect{QRectF(-30.0, -5.0, 60.0, 10.0)}
    , m_leftButtonPressed{false}
{
    setFlag(ItemSendsGeometryChanges, true);
    setAcceptHoverEvents(true);
    setPen(QPen(Qt::black, 1));
    setBrush(Qt::white);
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
void WindowShape::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(widget);

    painter->setRenderHint(QPainter::Antialiasing);
    painter->setRenderHint(QPainter::SmoothPixmapTransform);
    painter->setPen(pen());
    painter->setBrush(brush());

    painter->drawRect(rect());
    qreal centerY{rect().center().y()};
    QPointF leftCenter{rect().left(), centerY};
    QPointF rightCenter{rect().right(), centerY};
    painter->drawLine(leftCenter, rightCenter);

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
 * \return Returns the outer bounds of the window as a rectangle.
 *
 * \sa shape(), contains().
 */
QRectF WindowShape::boundingRect() const
{
    QRectF boundingRect{m_windowRect};
    qreal halfpw{pen().style() == Qt::NoPen ? qreal(0.0) : pen().widthF() / 2};
    if (halfpw > 0.0)
        boundingRect.adjust(-halfpw, -halfpw, halfpw, halfpw);

    return boundingRect;
}

/*!
 * Reimplements: QGraphicsItem::shape().
 * The shape is used for many things, including collision detection, hit tests,
 * and for the QGraphicsScene::items() functions. This function is called by
 * the default implementations of contains() and collidesWithPath(). The window
 * outline is included in the element shape.
 *
 * \return Returns the shape of this item as a QPainterPath in local coordinates.
 *
 *  \sa boundingRect(), contains().
 */
QPainterPath WindowShape::shape() const
{
    QPainterPath path;
    path.addRect(rect());

    return shapeFromPath(path);
}

/*!
 * Reimplements: BuildingShape::image().
 * Required to create a shape icon in ShapeToolBox. Used by the
 * MainWindow::createBuildingShapeCellWidget() method to create an window
 * icon in the ShapeToolBox.
 *
 * \return Returns a QPixmap object containing the shape image.
 */
QPixmap WindowShape::image()
{
    qreal pixmapWidth{boundingRect().width()};
    qreal pixmapHeight{boundingRect().height()};
    QPixmap pixmap(pixmapWidth, pixmapHeight);
    pixmap.fill(Qt::transparent);

    QPainter painter(&pixmap);
    painter.setPen(pen());
    painter.setBrush(brush());
    painter.translate(pixmapWidth / 2.0, pixmapHeight / 2.0);
    painter.drawRect(rect());
    qreal centerY{rect().center().y()};
    QPointF leftCenter{rect().left(), centerY};
    QPointF rightCenter{rect().right(), centerY};
    painter.drawLine(leftCenter, rightCenter);

    return pixmap;
}

/*!
 * Reimplements: BuildingShape::shapeType().
 * Required to determine the actual type of the object.
 *
 * \return Returns the type of building shape "Window".
 * \sa ShapeType.
 */
BuildingShape::ShapeType WindowShape::shapeType() const
{
    return m_windowType;
}

/*!
 * Reimplements: BuildingShape::setRect().
 * This method is used to set the size of the shape.
 *
 * \param rect[in] Sets the shape's size to be the given  rectangle.
 * \sa rect().
 */
void WindowShape::setRect(const QRectF &rect)
{
    if (m_windowRect == rect)
        return;

    prepareGeometryChange();
    m_windowRect.setRect(rect.topLeft().x(), rect.topLeft().y(), rect.width(), rect.height());
    update();
}

/*!
 * Reimplements: BuildingShape::rect().
 * This is the outer bounds shape whitout pen width.
 *
 * \return Returns the shape's rectangle.
 * \sa setRect().
 */
QRectF WindowShape::rect() const
{
    return m_windowRect;
}

/*!
 * Reimplements: BuildingShape::setHeight().
 * Sets the height of the shape.
 *
 * \param height[in] Sets the height of the shape to the given height.
 * \sa height().
 */
void WindowShape::setHeight(const qreal &height)
{
    if (m_windowRect.height() == height)
        return;

    qreal oldHeight{m_windowRect.height()};
    prepareGeometryChange();
    m_windowRect.setHeight(height);
    qreal dy{(m_windowRect.height() - oldHeight) / 2};
    m_windowRect.moveTo(QPointF(m_windowRect.x(), m_windowRect.y() - dy));
    update();
}

/*!
 * Reimplements: BuildingShape::height().
 *
 * \return Returns the shape's height.
 * \sa setHeight().
 */
qreal WindowShape::height() const
{
    return m_windowRect.height();
}

/*!
 * Reimplements: AbstractShape::mousePressEvent().
 * If the left mouse button is pressed, this method is used to snap the window to
 * the wall it intersects.
 *
 * \param mouseEvent[in] Pointer to the QGraphicsSceneMouseEvent class.
 * \sa mouseReleaseEvent().
 */
void WindowShape::mousePressEvent(QGraphicsSceneMouseEvent *mouseEvent)
{
    if (mouseEvent->buttons() == Qt::LeftButton) {
        m_leftButtonPressed = true;
    } else {
        AbstractShape::mousePressEvent(mouseEvent);
    }
}

/*!
 * Reimplements: AbstractShape::mouseReleaseEvent().
 * The method is used to position and link a window to an intersecting wall.
 *
 * \param mouseEvent[in] Pointer to the QGraphicsSceneMouseEvent class.
 * \sa mousePressEvent().
 */
void WindowShape::mouseReleaseEvent(QGraphicsSceneMouseEvent *mouseEvent)
{
    if (m_leftButtonPressed) {
        bindingWall();
        m_leftButtonPressed = false;
    }

    QGraphicsItem::mouseReleaseEvent(mouseEvent);
}

/*
 * Binds the window to the wall with which it intersects, and sets the width of
 * the window according to the width of the wall.
 */
void WindowShape::bindingWall()
{
    QList<QGraphicsItem *> collidingShapeList{collidingItems()};
    for (QGraphicsItem *p_shape : qAsConst(collidingShapeList)) {
        if (WallShape *p_collidingWall = dynamic_cast<WallShape *>(p_shape)) {
            prepareGeometryChange();
            setTransform(p_collidingWall->transform());
            QRectF wallRect{mapRectFromItem(p_collidingWall, p_collidingWall->boundingRect())};
            setRect(QRectF(m_windowRect.x(), wallRect.y(), m_windowRect.width(), wallRect.height()));
            setSelected(false);
            update();
            break;
        }
    }
}

/*!
 * Constructs an OpenShape class.
 *
 * \param parent[in] A pointer to the parent object is passed to the
 * QGraphicsItem constructor. This is part of the memory management strategy
 * used in Qt-Framework.
 */
OpenShape::OpenShape(QGraphicsItem *parent)
    : BuildingShape(parent)
    , m_openType{Open}
    , m_openRect{QRectF(-30.0, -5.0, 60.0, 10.0)}
    , m_leftButtonPressed{false}
{
    setFlag(ItemSendsGeometryChanges, true);
    setAcceptHoverEvents(true);
    setPen(QPen(Qt::black, 1));
    setBrush(Qt::white);
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
void OpenShape::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(widget);

    painter->setRenderHint(QPainter::Antialiasing);
    painter->setRenderHint(QPainter::SmoothPixmapTransform);
    painter->setPen(pen());
    painter->setBrush(brush());

    painter->drawRect(rect());

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
 * \return Returns the outer bounds of the wall opening as a rectangle.
 *
 * \sa shape(), contains().
 */
QRectF OpenShape::boundingRect() const
{
    QRectF boundingRect{m_openRect};
    qreal halfpw{pen().style() == Qt::NoPen ? qreal(0.0) : pen().widthF() / 2};
    if (halfpw > 0.0)
        boundingRect.adjust(-halfpw, -halfpw, halfpw, halfpw);

    return boundingRect;
}

/*!
 * Reimplements: QGraphicsItem::shape().
 * The shape is used for many things, including collision detection, hit tests,
 * and for the QGraphicsScene::items() functions. This function is called by
 * the default implementations of contains() and collidesWithPath(). The wall
 * opening outline is included in the element shape.
 *
 * \return Returns the shape of this item as a QPainterPath in local coordinates.
 *
 *  \sa boundingRect(), contains().
 */
QPainterPath OpenShape::shape() const
{
    QPainterPath path;
    path.addRect(rect());

    return shapeFromPath(path);
}

/*!
 * Reimplements: BuildingShape::image().
 * Required to create a shape icon in ShapeToolBox. Used by the
 * MainWindow::createBuildingShapeCellWidget() method to create an wall opening
 * icon in the ShapeToolBox.
 *
 * \return Returns a QPixmap object containing the shape image.
 */
QPixmap OpenShape::image()
{
    qreal pixmapWidth{boundingRect().width()};
    qreal pixmapHeight{boundingRect().height()};
    QPixmap pixmap(pixmapWidth, pixmapHeight);
    pixmap.fill(Qt::transparent);

    QPainter painter(&pixmap);
    painter.setPen(pen());
    painter.setBrush(brush());
    painter.translate(pixmapWidth / 2.0, pixmapHeight / 2.0);
    painter.drawRect(rect());

    return pixmap;
}

/*!
 * Reimplements: BuildingShape::shapeType().
 * Required to determine the actual type of the object.
 *
 * \return Returns the type of building shape "Open".
 * \sa ShapeType.
 */
BuildingShape::ShapeType OpenShape::shapeType() const
{
    return m_openType;
}

/*!
 * Reimplements: BuildingShape::setRect().
 * This method is used to set the size of the shape.
 *
 * \param rect[in] Sets the shape's size to be the given  rectangle.
 * \sa rect().
 */
void OpenShape::setRect(const QRectF &rect)
{
    if (m_openRect == rect)
        return;

    prepareGeometryChange();
    m_openRect.setRect(rect.topLeft().x(), rect.topLeft().y(), rect.width(), rect.height());
    update();
}

/*!
 * Reimplements: BuildingShape::rect().
 * This is the outer bounds shape whitout pen width.
 *
 * \return Returns the shape's rectangle.
 * \sa setRect().
 */
QRectF OpenShape::rect() const
{
    return m_openRect;
}

/*!
 * Reimplements: BuildingShape::setHeight().
 * Sets the height of the shape.
 *
 * \param height[in] Sets the height of the shape to the given height.
 * \sa height().
 */
void OpenShape::setHeight(const qreal &height)
{
    if (m_openRect.height() == height)
        return;

    qreal oldHeight{m_openRect.height()};
    prepareGeometryChange();
    m_openRect.setHeight(height);
    qreal dy{(m_openRect.height() - oldHeight) / 2};
    m_openRect.moveTo(QPointF(m_openRect.x(), m_openRect.y() - dy));
    update();
}

/*!
 * Reimplements: BuildingShape::height().
 *
 * \return Returns the shape's height.
 * \sa setHeight().
 */
qreal OpenShape::height() const
{
    return m_openRect.height();
}

/*!
 * Reimplements: AbstractShape::mousePressEvent().
 * If the left mouse button is pressed, this method is used to snap the wall
 * opening to the wall it intersects.
 *
 * \param mouseEvent[in] Pointer to the QGraphicsSceneMouseEvent class.
 * \sa mouseReleaseEvent().
 */
void OpenShape::mousePressEvent(QGraphicsSceneMouseEvent *mouseEvent)
{
    if (mouseEvent->buttons() == Qt::LeftButton) {
        m_leftButtonPressed = true;
    } else {
        AbstractShape::mousePressEvent(mouseEvent);
    }
}

/*!
 * Reimplements: AbstractShape::mouseReleaseEvent().
 * The method is used to position and link a wall opening to an intersecting
 * wall.
 *
 * \param mouseEvent[in] Pointer to the QGraphicsSceneMouseEvent class.
 * \sa mousePressEvent().
 */
void OpenShape::mouseReleaseEvent(QGraphicsSceneMouseEvent *mouseEvent)
{
    if (m_leftButtonPressed) {
        bindingWall();
        m_leftButtonPressed = false;
    }

    QGraphicsItem::mouseReleaseEvent(mouseEvent);
}

/*
 * Binds the wall opening to the wall with which it intersects, and sets the
 * width of the wall opening according to the width of the wall.
 */
void OpenShape::bindingWall()
{
    QList<QGraphicsItem *> collidingShapeList{collidingItems()};
    for (QGraphicsItem *p_shape : qAsConst(collidingShapeList)) {
        if (WallShape *p_collidingWall = dynamic_cast<WallShape *>(p_shape)) {
            prepareGeometryChange();
            setTransform(p_collidingWall->transform());
            QRectF wallRect{mapRectFromItem(p_collidingWall, p_collidingWall->boundingRect())};
            setRect(QRectF(m_openRect.x(), wallRect.y(), m_openRect.width(), wallRect.height()));
            setSelected(false);
            update();
            break;
        }
    }
}

/*!
 * Constructs a StairwellShape class.
 *
 * \param parent[in] A pointer to the parent object is passed to the
 * QGraphicsItem constructor. This is part of the memory management strategy
 * used in Qt-Framework.
 */
StairwellShape::StairwellShape(QGraphicsItem *parent)
    : BuildingShape(parent)
    , m_stairwellType{Stairwell}
    , m_stairwellRect{QRectF(-30.0, -40.0, 60.0, 80.0)}
{
    setFlag(ItemSendsGeometryChanges, true);
    setAcceptHoverEvents(true);
    setPen(QPen(Qt::black, 1));
    setBrush(Qt::white);
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
void StairwellShape::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(widget);

    painter->setRenderHint(QPainter::Antialiasing);
    painter->setRenderHint(QPainter::SmoothPixmapTransform);
    painter->setPen(pen());
    painter->setBrush(brush());

    drawStairwell(painter);

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
 * \return Returns the outer bounds of the stairwell as a rectangle.
 *
 * \sa shape(), contains().
 */
QRectF StairwellShape::boundingRect() const
{
    QRectF boundingRect{m_stairwellRect};
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
QPainterPath StairwellShape::shape() const
{
    QPainterPath path;
    path.moveTo(m_stairwellRect.topLeft());
    path.lineTo(m_stairwellRect.topRight());
    path.lineTo(m_stairwellRect.bottomRight());
    qreal rightRailingX{m_stairwellRect.center().x() + 2.0};
    QPointF rightRailingBottom{rightRailingX, m_stairwellRect.bottom()};
    path.lineTo(rightRailingBottom);
    qreal marchWidth{m_stairwellRect.width() / 2.0 - 2.0};
    QPointF rightRailingTop{rightRailingX, m_stairwellRect.top() + marchWidth};
    path.lineTo(rightRailingTop);
    qreal leftRailingX{m_stairwellRect.center().x() - 2.0};
    QPointF leftRailingTop{(leftRailingX), m_stairwellRect.top() + marchWidth};
    path.lineTo(leftRailingTop);
    QPointF leftRailingBottom{leftRailingX, m_stairwellRect.bottom()};
    path.lineTo(leftRailingBottom);
    path.lineTo(m_stairwellRect.bottomLeft());
    path.lineTo(m_stairwellRect.topLeft());

    return shapeFromPath(path);
}

/*!
 * Reimplements: BuildingShape::image().
 * Required to create a shape icon in ShapeToolBox. Used by the
 * MainWindow::createBuildingShapeCellWidget() method to create a stairwell
 * icon in the ShapeToolBox.
 *
 * \return Returns a QPixmap object containing the shape image.
 */
QPixmap StairwellShape::image()
{
    qreal pixmapWidth{boundingRect().width()};
    qreal pixmapHeight{boundingRect().height()};
    QPixmap pixmap(pixmapWidth, pixmapHeight);
    pixmap.fill(Qt::transparent);

    QPainter painter(&pixmap);
    painter.setPen(pen());
    painter.setBrush(brush());
    painter.translate(pixmapWidth / 2.0, pixmapHeight / 2.0);
    drawStairwell(&painter);

    return pixmap;
}

/*!
 * Reimplements: BuildingShape::shapeType().
 * Required to determine the actual type of the object.
 *
 * \return Returns the type of building shape "Stairwell".
 * \sa ShapeType.
 */
BuildingShape::ShapeType StairwellShape::shapeType() const
{
    return m_stairwellType;
}

/*!
 * Reimplements: BuildingShape::setRect().
 * This method is used to set the size of the shape.
 *
 * \param rect[in] Sets the shape's size to be the given  rectangle.
 * \sa rect().
 */
void StairwellShape::setRect(const QRectF &rect)
{
    if (m_stairwellRect == rect)
        return;

    prepareGeometryChange();
    m_stairwellRect.setRect(rect.topLeft().x(), rect.topLeft().y(), rect.width(), rect.height());
    update();
}

/*!
 * Reimplements: BuildingShape::rect().
 * This is the outer bounds shape whitout pen width.
 *
 * \return Returns the shape's rectangle.
 * \sa setRect().
 */
QRectF StairwellShape::rect() const
{
    return m_stairwellRect;
}

/*!
 * Reimplements: BuildingShape::setHeight().
 * Sets the height of the shape.
 *
 * \param height[in] Sets the height of the shape to the given height.
 * \sa height().
 */
void StairwellShape::setHeight(const qreal &height)
{
    if (m_stairwellRect.height() == height)
        return;

    qreal oldHeight{m_stairwellRect.height()};
    prepareGeometryChange();
    m_stairwellRect.setHeight(height);
    qreal dy{(m_stairwellRect.height() - oldHeight) / 2};
    m_stairwellRect.moveTo(QPointF(m_stairwellRect.x(), m_stairwellRect.y() - dy));
    update();
}

/*!
 * Reimplements: BuildingShape::height().
 *
 * \return Returns the shape's height.
 * \sa setHeight().
 */
qreal StairwellShape::height() const
{
    return m_stairwellRect.height();
}

/*
 * Draws a stairwell and, when resizing, automatically adjusts the number of
 * steps and the distance between them.
 */
void StairwellShape::drawStairwell(QPainter *painter)
{
    QPointF stBottomLeft{m_stairwellRect.bottomLeft()};
    QPointF stTopLeft{m_stairwellRect.topLeft()};
    QLineF leftSide{stBottomLeft, stTopLeft};
    painter->drawLine(leftSide);

    QPointF stBotttomRight{m_stairwellRect.bottomRight()};
    QPointF stTopRight{m_stairwellRect.topRight()};
    QLineF rightSide{stBotttomRight, stTopRight};
    painter->drawLine(rightSide);

    QLineF topSide{stTopLeft, stTopRight};
    painter->drawLine(topSide);

    qreal marchWidth{m_stairwellRect.width() / 2.0 - 2.0};
    qreal leftRailingX{m_stairwellRect.center().x() - 2.0};
    QPointF leftRailingBottom{leftRailingX, m_stairwellRect.bottom()};
    QPointF leftRailingTop{(leftRailingX), m_stairwellRect.top() + marchWidth};
    QLineF leftRailing{leftRailingBottom, leftRailingTop};
    painter->drawLine(leftRailing);

    qreal rightRailingX{m_stairwellRect.center().x() + 2.0};
    QPointF rightRailingBottom{rightRailingX, m_stairwellRect.bottom()};
    QPointF rightRailingTop{rightRailingX, m_stairwellRect.top() + marchWidth};
    QLineF rightRailing{rightRailingBottom, rightRailingTop};
    painter->drawLine(rightRailing);

    qreal railingLength{m_stairwellRect.height() - marchWidth};
    int stepHeight{8};
    div_t divResalt{div(railingLength, stepHeight)};
    int stepNum{divResalt.quot};
    int stepCorrection{divResalt.rem};
    qreal stepPosY{m_stairwellRect.bottom()};
    qreal stLeft{m_stairwellRect.left()};
    qreal stRight{m_stairwellRect.right()};

    // Draw steps
    for (int i = 0; i < stepNum; i++) {
        QLineF leftStep{stLeft, stepPosY, (stLeft + marchWidth), stepPosY};
        painter->drawLine(leftStep);
        QLineF rightStep{stRight, stepPosY, (stRight - marchWidth), stepPosY};
        painter->drawLine(rightStep);
        stepPosY -= stepHeight;
        if (stepCorrection > 0) {
            stepPosY -= 1;
            stepCorrection -= 1;
        }
    }
    QLineF topStep{stLeft, stepPosY, stRight, stepPosY};
    painter->drawLine(topStep);
}

/*!
 * Constructs a StairsShape class.
 *
 * \param parent[in] A pointer to the parent object is passed to the
 * QGraphicsItem constructor. This is part of the memory management strategy
 * used in Qt-Framework.
 */
StairsShape::StairsShape(QGraphicsItem *parent)
    : BuildingShape(parent)
    , m_stairsType{Stairs}
    , m_stairsRect{QRectF(-30.0, -40.0, 60.0, 80.0)}
{
    setFlag(ItemSendsGeometryChanges, true);
    setAcceptHoverEvents(true);
    setPen(QPen(Qt::black, 1));
    setBrush(Qt::white);
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
void StairsShape::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(widget);

    painter->setRenderHint(QPainter::Antialiasing);
    painter->setRenderHint(QPainter::SmoothPixmapTransform);
    painter->setPen(pen());
    painter->setBrush(brush());

    drawStairs(painter);

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
 * \return Returns the outer bounds of the stair as a rectangle.
 *
 * \sa shape(), contains().
 */
QRectF StairsShape::boundingRect() const
{
    QRectF boundingRect{m_stairsRect};
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
 * stair outline is included in the element shape.
 *
 * \return Returns the shape of this item as a QPainterPath in local coordinates.
 *
 *  \sa boundingRect(), contains().
 */
QPainterPath StairsShape::shape() const
{
    QPainterPath path;
    path.addRect(rect());

    return shapeFromPath(path);
}

/*!
 * Reimplements: BuildingShape::image().
 * Required to create a shape icon in ShapeToolBox. Used by the
 * MainWindow::createBuildingShapeCellWidget() method to create a stair icon in
 * the ShapeToolBox.
 *
 * \return Returns a QPixmap object containing the shape image.
 */
QPixmap StairsShape::image()
{
    qreal pixmapWidth{boundingRect().width()};
    qreal pixmapHeight{boundingRect().height()};
    QPixmap pixmap(pixmapWidth, pixmapHeight);
    pixmap.fill(Qt::transparent);

    QPainter painter(&pixmap);
    painter.setPen(pen());
    painter.setBrush(brush());
    painter.translate(pixmapWidth / 2.0, pixmapHeight / 2.0);
    drawStairs(&painter);

    return pixmap;
}

/*!
 * Reimplements: BuildingShape::shapeType().
 * Required to determine the actual type of the object.
 *
 * \return Returns the type of building shape "Stairs".
 * \sa ShapeType.
 */
BuildingShape::ShapeType StairsShape::shapeType() const
{
    return m_stairsType;
}

/*!
 * Reimplements: BuildingShape::setRect().
 * This method is used to set the size of the shape.
 *
 * \param rect[in] Sets the shape's size to be the given  rectangle.
 * \sa rect().
 */
void StairsShape::setRect(const QRectF &rect)
{
    if (m_stairsRect == rect)
        return;

    prepareGeometryChange();
    m_stairsRect.setRect(rect.topLeft().x(), rect.topLeft().y(), rect.width(), rect.height());
    update();
}

/*!
 * Reimplements: BuildingShape::rect().
 * This is the outer bounds shape whitout pen width.
 *
 * \return Returns the shape's rectangle.
 * \sa setRect().
 */
QRectF StairsShape::rect() const
{
    return m_stairsRect;
}

/*!
 * Reimplements: BuildingShape::setHeight().
 * Sets the height of the shape.
 *
 * \param height[in] Sets the height of the shape to the given height.
 * \sa height().
 */
void StairsShape::setHeight(const qreal &height)
{
    if (m_stairsRect.height() == height)
        return;

    qreal oldHeight{m_stairsRect.height()};
    prepareGeometryChange();
    m_stairsRect.setHeight(height);
    qreal dy{(m_stairsRect.height() - oldHeight) / 2};
    m_stairsRect.moveTo(QPointF(m_stairsRect.x(), m_stairsRect.y() - dy));
    update();
}

/*!
 * Reimplements: BuildingShape::height().
 *
 * \return Returns the shape's height.
 * \sa setHeight().
 */
qreal StairsShape::height() const
{
    return m_stairsRect.height();
}

/*
 * Draws a staircase and, when resizing, automatically adjusts the number of
 * steps and the distance between them.
 */
void StairsShape::drawStairs(QPainter *painter)
{
    QPointF stBottomLeft{m_stairsRect.bottomLeft()};
    QPointF stTopLeft{m_stairsRect.topLeft()};
    QLineF leftSide{stBottomLeft, stTopLeft};
    painter->drawLine(leftSide);

    QPointF stBotttomRight{m_stairsRect.bottomRight()};
    QPointF stTopRight{m_stairsRect.topRight()};
    QLineF rightSide{stBotttomRight, stTopRight};
    painter->drawLine(rightSide);

    qreal stairsLength{m_stairsRect.height()};
    int stepHeight{8};
    div_t divResalt{div(stairsLength, stepHeight)};
    int stepNum{divResalt.quot};
    int stepCorrection{divResalt.rem};
    qreal stepPosY{m_stairsRect.bottom()};
    qreal stLeft{m_stairsRect.left()};
    qreal stRight{m_stairsRect.right()};

    // Draw steps
    for (int i = 0; i <= stepNum; i++) {
        QLineF step{stLeft, stepPosY, stRight, stepPosY};
        painter->drawLine(step);
        stepPosY -= stepHeight;
        if (stepCorrection > 0) {
            stepPosY -= 1;
            stepCorrection -= 1;
        }
    }
}
