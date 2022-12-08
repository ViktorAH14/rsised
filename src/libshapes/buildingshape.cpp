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

#include "../include/buildingshape.h"

#include <QtMath>
#include <QPainter>
#include <QActionGroup>
#include <QGraphicsSceneEvent>
#include <QStyleOptionGraphicsItem>

BuildingShape::BuildingShape(QGraphicsItem *parent)
    : AbstractShape(parent)
{
}

BuildingShape::~BuildingShape() = default;

void BuildingShape::deleter()
{
    delete this;
}

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
    default:
        break;
    }
    return p_buildingShape;
}

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
        for (WallShape *p_wallShape : qAsConst(m_collidingWallSet)) {
            wallPath.addPolygon(mapFromItem(p_wallShape, p_wallShape->rect()));
        }
        painter->strokePath(wallPath.simplified(), pen());
    }

    if (option->state & QStyle::State_Selected) {
         highlightSelected(painter, option);
    }

}

QRectF WallShape::boundingRect() const
{
    QRectF boundingRect{m_wallRect};
    qreal halfpw{pen().style() == Qt::NoPen ? qreal(0.0) : pen().widthF() / 2};
    if (halfpw > 0.0)
        boundingRect.adjust(-halfpw, -halfpw, halfpw, halfpw);

    return boundingRect;
}

QPainterPath WallShape::shape() const
{
    QPainterPath path;
    path.addRect(rect());

    return shapeFromPath(path);
}

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

BuildingShape::ShapeType WallShape::shapeType() const
{
    return m_wallType;
}

void WallShape::setRect(const QRectF &rect)
{
    if (m_wallRect == rect)
        return;

    prepareGeometryChange();
    m_wallRect.setRect(rect.topLeft().x(), rect.topLeft().y(), rect.width(), rect.height());
    update();
}

QRectF WallShape::rect() const
{
    return m_wallRect;
}

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

qreal WallShape::height() const
{
    return m_wallRect.height();
}

QSet<WallShape *> WallShape::collidingWalls()
{
    return m_collidingWallSet;
}

bool WallShape::removeCollidingWall(WallShape *wallShape)
{
    return m_collidingWallSet.remove(wallShape);
}

void WallShape::mousePressEvent(QGraphicsSceneMouseEvent *mouseEvent)
{
    if (mouseEvent->buttons() == Qt::LeftButton) {
        m_leftButtonPressed = true;
    } else {
        AbstractShape::mousePressEvent(mouseEvent);
    }
}

void WallShape::mouseReleaseEvent(QGraphicsSceneMouseEvent *mouseEvent)
{
    if (m_leftButtonPressed && !collidingWallsIsEmpty()) {
        bindingWall();
        m_leftButtonPressed = false;
    }

    QGraphicsItem::mouseReleaseEvent(mouseEvent);
}

void WallShape::setCollidingWalls()
{
    m_collidingWallSet.clear();
    QList<QGraphicsItem *> collidingShapeList{collidingItems()};
    for (QGraphicsItem *p_shape : qAsConst(collidingShapeList)) {
        if (WallShape *p_wallShape = dynamic_cast<WallShape *>(p_shape)) {
            m_collidingWallSet.insert(p_wallShape);
            if (!p_wallShape->collidingWallsIsEmpty()) {
                m_collidingWallSet += p_wallShape->collidingWalls();
            }
        }
    }
    m_collidingWallSet.remove(this);
}

bool WallShape::collidingWallsIsEmpty()
{
    return m_collidingWallSet.isEmpty() ? true : false;
}

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
    createAction();
}

void DoorShape::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(widget);

    painter->setRenderHint(QPainter::Antialiasing);
    painter->setRenderHint(QPainter::SmoothPixmapTransform);

    painter->setPen(QPen(Qt::NoPen));
    painter->setBrush(brush());
    painter->drawRect(m_doorRect);

    drawDoor(painter);

    if (option->state & QStyle::State_Selected) {
         highlightSelected(painter, option);
    }
}

QRectF DoorShape::boundingRect() const
{
    QRectF boundingRect{m_leftFrame.left(), m_leftFrame.top() - qFabs(m_doorLeaf.dy())
                , m_doorRect.width(), m_doorRect.height() + qFabs(m_doorLeaf.dy())};
    qreal halfpw{pen().style() == Qt::NoPen ? qreal(0.0) : pen().widthF() / 2};
    if (halfpw > 0.0)
        boundingRect.adjust(-halfpw, -halfpw, halfpw, halfpw);

    return boundingRect;
}

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

BuildingShape::ShapeType DoorShape::shapeType() const
{
    return m_doorType;
}

void DoorShape::setRect(const QRectF &rect)
{
    prepareGeometryChange();
    m_doorRect.setRect(rect.topLeft().x(), rect.topLeft().y(), rect.width(), rect.height());
    update();
}

QRectF DoorShape::rect() const
{
    return m_doorRect;
}

void DoorShape::setHeight(const qreal &height)
{
    m_doorRect.setHeight(height);
}

qreal DoorShape::height() const
{
    return m_doorRect.height();
}

DoorShape::DoorState DoorShape::doorState() const
{
    return m_doorState;
}

void DoorShape::setDoorState(DoorState doorState)
{
    prepareGeometryChange();
    m_doorState = doorState;
    update();
}

DoorShape::LeafPosition DoorShape::leafPosition() const
{
    return m_leafPosition;
}

void DoorShape::setLeafPosition(LeafPosition leafPosition)
{
    prepareGeometryChange();
    m_leafPosition = leafPosition;
    update();
}

void DoorShape::mousePressEvent(QGraphicsSceneMouseEvent *mouseEvent)
{
    if (mouseEvent->buttons() == Qt::LeftButton) {
        m_leftButtonPressed = true;
    } else {
        AbstractShape::mousePressEvent(mouseEvent);
    }
}

void DoorShape::mouseReleaseEvent(QGraphicsSceneMouseEvent *mouseEvent)
{
    if (m_leftButtonPressed) {
        bindingWall();
        m_leftButtonPressed = false;
    }

    QGraphicsItem::mouseReleaseEvent(mouseEvent);
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

void DoorShape::createAction()
{
    m_doorLeafPosAction.reset(new QAction(QObject::tr("Leaf change")));
    m_doorLeafPosAction->setToolTip(QObject::tr("Changing the position of the door leaf"));
    QObject::connect(m_doorLeafPosAction.get(), &QAction::triggered
                     , [this](){m_leafPosition == Left ? setLeafPosition(Right)
                                                       : setLeafPosition(Left);});
    m_actionList.append(m_doorLeafPosAction.get());

    m_doorOpenAction.reset(new QAction(QObject::tr("Open door")));
    m_doorOpenAction->setToolTip(QObject::tr("Change the state of the door"));
    m_doorOpenAction->setCheckable(true);
    QObject::connect(m_doorOpenAction.get(), &QAction::triggered, [this](){setDoorState(Open);});
    m_actionList.append(m_doorOpenAction.get());

    m_doorAjarAction.reset(new QAction(QObject::tr("Ajar door")));
    m_doorAjarAction->setToolTip(QObject::tr("Change the state of the door"));
    m_doorAjarAction->setCheckable(true);
    QObject::connect(m_doorAjarAction.get(), &QAction::triggered, [this](){setDoorState(Ajar);});
    m_actionList.append(m_doorAjarAction.get());

    m_doorCloseAction.reset(new QAction(QObject::tr("Close door")));
    m_doorCloseAction->setToolTip(QObject::tr("Change the state of the door"));
    m_doorCloseAction->setCheckable(true);
    QObject::connect(m_doorCloseAction.get(), &QAction::triggered, [this](){setDoorState(Close);});
    m_actionList.append(m_doorCloseAction.get());

    m_doorStateActionGroup.reset(new QActionGroup(nullptr));
    m_doorStateActionGroup->addAction(m_doorOpenAction.get());
    m_doorStateActionGroup->addAction(m_doorAjarAction.get());
    m_doorStateActionGroup->addAction(m_doorCloseAction.get());
    m_doorOpenAction->setChecked(true);

    addActions(m_actionList);
}


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

    if (option->state & QStyle::State_Selected) {
         highlightSelected(painter, option);
    }
}

QRectF WindowShape::boundingRect() const
{
    QRectF boundingRect{m_windowRect};
    qreal halfpw{pen().style() == Qt::NoPen ? qreal(0.0) : pen().widthF() / 2};
    if (halfpw > 0.0)
        boundingRect.adjust(-halfpw, -halfpw, halfpw, halfpw);

    return boundingRect;
}

QPainterPath WindowShape::shape() const
{
    QPainterPath path;
    path.addRect(rect());

    return shapeFromPath(path);
}

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

BuildingShape::ShapeType WindowShape::shapeType() const
{
    return m_windowType;
}

void WindowShape::setRect(const QRectF &rect)
{
    if (m_windowRect == rect)
        return;

    prepareGeometryChange();
    m_windowRect.setRect(rect.topLeft().x(), rect.topLeft().y(), rect.width(), rect.height());
    update();
}

QRectF WindowShape::rect() const
{
    return m_windowRect;
}

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

qreal WindowShape::height() const
{
    return m_windowRect.height();
}

void WindowShape::mousePressEvent(QGraphicsSceneMouseEvent *mouseEvent)
{
    if (mouseEvent->buttons() == Qt::LeftButton) {
        m_leftButtonPressed = true;
    } else {
        AbstractShape::mousePressEvent(mouseEvent);
    }
}

void WindowShape::mouseReleaseEvent(QGraphicsSceneMouseEvent *mouseEvent)
{
    if (m_leftButtonPressed) {
        bindingWall();
        m_leftButtonPressed = false;
    }

    QGraphicsItem::mouseReleaseEvent(mouseEvent);
}

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

void OpenShape::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(widget);

    painter->setRenderHint(QPainter::Antialiasing);
    painter->setRenderHint(QPainter::SmoothPixmapTransform);
    painter->setPen(pen());
    painter->setBrush(brush());

    painter->drawRect(rect());

    if (option->state & QStyle::State_Selected) {
         highlightSelected(painter, option);
    }
}

QRectF OpenShape::boundingRect() const
{
    QRectF boundingRect{m_openRect};
    qreal halfpw{pen().style() == Qt::NoPen ? qreal(0.0) : pen().widthF() / 2};
    if (halfpw > 0.0)
        boundingRect.adjust(-halfpw, -halfpw, halfpw, halfpw);

    return boundingRect;
}

QPainterPath OpenShape::shape() const
{
    QPainterPath path;
    path.addRect(rect());

    return shapeFromPath(path);
}

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

BuildingShape::ShapeType OpenShape::shapeType() const
{
    return m_openType;
}

void OpenShape::setRect(const QRectF &rect)
{
    if (m_openRect == rect)
        return;

    prepareGeometryChange();
    m_openRect.setRect(rect.topLeft().x(), rect.topLeft().y(), rect.width(), rect.height());
    update();
}

QRectF OpenShape::rect() const
{
    return m_openRect;
}

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

qreal OpenShape::height() const
{
    return m_openRect.height();
}

void OpenShape::mousePressEvent(QGraphicsSceneMouseEvent *mouseEvent)
{
    if (mouseEvent->buttons() == Qt::LeftButton) {
        m_leftButtonPressed = true;
    } else {
        AbstractShape::mousePressEvent(mouseEvent);
    }
}

void OpenShape::mouseReleaseEvent(QGraphicsSceneMouseEvent *mouseEvent)
{
    if (m_leftButtonPressed) {
        bindingWall();
        m_leftButtonPressed = false;
    }

    QGraphicsItem::mouseReleaseEvent(mouseEvent);
}

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

StairwellShape::StairwellShape(QGraphicsItem *parent)
    : BuildingShape(parent)
    , m_stairwellType{Stairwell}
    , m_stairwellRect{QRectF(-30.0, -30.0, 60.0, 60.0)}
{
    setFlag(ItemSendsGeometryChanges, true);
    setAcceptHoverEvents(true);
    setPen(QPen(Qt::black, 1));
    setBrush(Qt::white);
}

void StairwellShape::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(widget);

    painter->setRenderHint(QPainter::Antialiasing);
    painter->setRenderHint(QPainter::SmoothPixmapTransform);
    painter->setPen(pen());
    painter->setBrush(brush());

    painter->drawRect(rect()); // FIXME предварительная реализация

    if (option->state & QStyle::State_Selected) {
         highlightSelected(painter, option);
    }
}

QRectF StairwellShape::boundingRect() const
{
    QRectF boundingRect{m_stairwellRect};
    qreal halfpw{pen().style() == Qt::NoPen ? qreal(0.0) : pen().widthF() / 2};
    if (halfpw > 0.0)
        boundingRect.adjust(-halfpw, -halfpw, halfpw, halfpw);

    return boundingRect;
}

QPainterPath StairwellShape::shape() const
{
    QPainterPath path;
    path.addRect(rect()); // FIXME предварительная реализация

    return shapeFromPath(path);
}
