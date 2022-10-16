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

#include <QPainter>
#include <QStyleOptionGraphicsItem>
#include <QtMath>
#include <QGraphicsSceneEvent>

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
    case Window:
        break;
    case Door:
        p_buildingShape = new DoorShape(parent);
        break;
    case Open:
        break;
    default:
        break;
    }
    return p_buildingShape;
}

//void BuildingShape::drawShape(QPainter *painter)
//{
//    painter->setRenderHint(QPainter::Antialiasing);
//    painter->setRenderHint(QPainter::SmoothPixmapTransform);
//    painter->setPen(QPen(Qt::black, 1 ));

//    prepareGeometryChange();
//    switch (m_shapeType) {
//    case Wall: {
//        QPainterPath wallPath;
//        wallPath.setFillRule(Qt::WindingFill);
//        wallPath.addRect(boundingRect());

//        setCollidingWals();

//        for (BuildingShape *item : qAsConst(collidingWalls)) {
//            wallPath.addPolygon(mapFromItem(item, item->boundingRect()));
//        }

//        QPainterPath fillPath = wallPath;
//        painter->fillPath(fillPath, wallBrush);
//        painter->strokePath(wallPath.simplified(), QPen(Qt::black, 1));

//        break;
//    }
//    case Window: {
//        painter->setBrush(QBrush(Qt::white));
//        painter->drawRect(shapeRect);
//        painter->drawLine(shapeRect.left(), 0.0, shapeRect.right(), 0.0);   //Center line
//        break;
//    }
//    case Door: {
//        painter->setBrush(QBrush(Qt::white));
//        painter->setPen(QPen(Qt::white, 1));
//        painter->drawRect(shapeRect);
//        painter->setPen(QPen(Qt::black, 1));
//        painter->drawRect(QRectF(shapeRect.topLeft(), QSizeF(frameWidth, shapeRect.height())));
//        painter->drawRect(QRectF(shapeRect.right() - frameWidth
//                                 , shapeRect.top(), frameWidth, shapeRect.height()));
//        painter->drawLine(shapeRect.right() - frameWidth, shapeRect.top()
//                          , shapeRect.right() - frameWidth - shapeRect.width() / 2.0
//                          , shapeRect.top() - shapeRect.width() / 2.0);
//        QPainterPath arcPath;
//        arcPath.moveTo(shapeRect.left() + frameWidth, shapeRect.top());
//        arcPath.quadTo(shapeRect.left() + frameWidth
//                       , shapeRect.top() - shapeRect.width() / 4.0
//                       , shapeRect.right() - frameWidth - shapeRect.width() / 2.0
//                       , shapeRect.top() - shapeRect.width() / 2.0);
//        painter->drawPath(arcPath);
//        break;
//    }
//    case Open: {
//        painter->setBrush(QBrush(Qt::white));
//        painter->setPen(QPen(Qt::white, 1));
//        painter->drawRect(shapeRect);
//        painter->setPen(QPen(Qt::black, 1));
//        painter->drawRect(QRectF(shapeRect.topLeft(), QSizeF(frameWidth, shapeRect.height())));
//        painter->drawRect(QRectF(shapeRect.right() - frameWidth
//                                 , shapeRect.top(), frameWidth, shapeRect.height()));
//        break;
//    }
//    default:
//        break;
//    }
//    update();
//}

WallShape::WallShape(QGraphicsItem *parent)
    : BuildingShape(parent)
    , m_wallType{Wall}
    , m_wallHeight{10}
    , m_wallRect{QRectF(-30.0, -5.0, 60.0, m_wallHeight)}
    , m_leftButtonPressed{false}
    , m_bindingOffset{m_wallHeight - 2.0}
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

    setCollidingWalls();
    if (m_collidingWallSet.isEmpty()) {
        painter->drawPath(shape());
    } else {
        QPainterPath wallPath;
        wallPath.setFillRule(Qt::WindingFill);
        wallPath.addRect(rect());
        for (WallShape *p_wallShape : qAsConst(m_collidingWallSet)) {
            wallPath.addPolygon(mapFromItem(p_wallShape, p_wallShape->boundingRect()));
        }
        QPainterPath fillPath{wallPath};
        painter->fillPath(fillPath, brush());
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

bool WallShape::contains(const QPointF &point) const
{
    return AbstractShape::contains(point);
}

QPixmap WallShape::image()
{
    qreal pixmapWidth{boundingRect().width()};
    qreal pixmapHeight{boundingRect().height()};
    QPixmap pixmap(pixmapWidth, pixmapHeight);
    pixmap.fill(Qt::transparent);

    QPainter painter(&pixmap);
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
    m_wallHeight = height;
}

qreal WallShape::height() const
{
    return m_wallHeight;
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
    if (m_leftButtonPressed) {
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
}

bool WallShape::collidingWallsIsEmpty()
{
    return m_collidingWallSet.isEmpty() ? true : false;
}

void WallShape::bindingWall()
{
    prepareGeometryChange();
    QList<QGraphicsItem *> collidingShapeList{collidingItems()};
    for (QGraphicsItem *p_shape : qAsConst(collidingShapeList)) {
        if (WallShape *p_collidingWall = dynamic_cast<WallShape *>(p_shape)) {
            QRectF collidingRect{mapRectFromItem(p_collidingWall, p_collidingWall->rect())};
            QList<QPointF> collidingCornerList{collidingRect.topLeft(), collidingRect.topRight()
                        , collidingRect.bottomLeft(), collidingRect.bottomRight()};
            QList<QPointF> cornerList{m_wallRect.topLeft(), m_wallRect.bottomRight()};
            for (int i = 0; i < cornerList.size(); i++) {
                for (int j = 0; j < collidingCornerList.size(); j++) {
                    QLineF distLine(cornerList.at(i), collidingCornerList.at(j));
                    if (distLine.length() < m_bindingOffset) {
                        cornerList[i] = collidingCornerList.at(j);
                        break;
                    }
                }
            }
            setRect(QRectF(cornerList.at(0), cornerList.at(1)));
        }
    }
    m_wallRect.setHeight(m_wallHeight);
    setSelected(false);
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
