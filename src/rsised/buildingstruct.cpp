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

#include "buildingstruct.h"
#include "sizegripitem.h"
#include "item_resizer.h"

#include <cmath>

#include <QGraphicsScene>
#include <QGraphicsSceneMouseEvent>
#include <QPainter>
#include <QMenu>

BuildingStruct::BuildingStruct(QMenu *contextMenu, ShapeType shapeType, QGraphicsItem *parent)
    :QAbstractGraphicsShapeItem(parent)
    , shapeRect{QRectF(-30.0, -5.0, 60.0, 10.0)}
    , wallBrush(Qt::lightGray)
    , m_shapeType{shapeType}
    , m_contextMenu{contextMenu}
{
    setFlag(ItemSendsGeometryChanges, true);
    setAcceptHoverEvents(true);
}

void BuildingStruct::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(option);
    Q_UNUSED(widget);

    drawShape(painter);
}

QRectF BuildingStruct::boundingRect() const
{
    qreal penWidth = 1;
    QRectF rect;
    if (m_shapeType == Door) {
        rect = QRectF((shapeRect.left() - penWidth / 2)
                      , (shapeRect.top() - sqrt(shapeRect.width() * shapeRect.width()) / 2 - penWidth / 2)
                      , shapeRect.width() + penWidth
                      , shapeRect.height() + sqrt(shapeRect.width() * shapeRect.width()) / 2 + penWidth);
    } else {
        rect = QRectF(shapeRect.left() - penWidth / 2, shapeRect.top() - penWidth / 2
                , shapeRect.width() + penWidth, shapeRect.height() + penWidth);
    }

    return rect;
}

QPainterPath BuildingStruct::shape() const
{
    QPainterPath path;
    path.moveTo(shapeRect.topLeft());
    if (m_shapeType == Door) {
        path.lineTo(shapeRect.left() + 8.0, shapeRect.top());
        path.quadTo(shapeRect.left() + 8.0
                    , shapeRect.top() - sqrt(shapeRect.width() * shapeRect.width()) / 4
                    , shapeRect.right() -8.0 - sqrt(shapeRect.width() * shapeRect.width()) / 2
                    , shapeRect.top() - sqrt(shapeRect.width() * shapeRect.width()) / 2);
        path.lineTo(shapeRect.right() - 8.0, shapeRect.top());
        path.lineTo(shapeRect.topRight());
        path.lineTo(shapeRect.bottomRight());
        path.lineTo(shapeRect.bottomLeft());
        path.lineTo(shapeRect.topLeft());
    } else {
        path.lineTo(shapeRect.topRight());
        path.lineTo(shapeRect.bottomRight());
        path.lineTo(shapeRect.bottomLeft());
        path.lineTo(shapeRect.topLeft());
    }
    return path;
}

QPixmap BuildingStruct::image()
{
    QPixmap pixmap(66, 70);
    pixmap.fill(Qt::transparent);
    QPainter *painter = new QPainter(&pixmap);
    painter->translate(33, 35);
    drawShape(painter);

    return pixmap;
}

BuildingStruct::ShapeType BuildingStruct::shapeType() const
{
    return m_shapeType;
}

void BuildingStruct::setRect(QRectF rect)
{
    prepareGeometryChange();
    shapeRect.setRect(rect.topLeft().x(), rect.topLeft().y(), rect.width(), rect.height());
    update();
}

QRectF BuildingStruct::getRect()
{
    return shapeRect;
}

void BuildingStruct::mouseDoubleClickEvent(QGraphicsSceneMouseEvent *mouseEvent)
{
    if (isSelected()) {
        m_sizeGripItem->setActionType((m_sizeGripItem->actionType()
                                       == SizeGripItem::Resize) ? SizeGripItem::Rotate
                                                                :SizeGripItem::Resize);
    } else {
        QGraphicsItem::mouseDoubleClickEvent(mouseEvent);
    }
}

void BuildingStruct::mouseMoveEvent(QGraphicsSceneMouseEvent *mouseEvent)
{
    if ((mouseEvent->buttons() == Qt::LeftButton) && isSelected()) {
        qreal dx = mouseEvent->scenePos().x() - mouseEvent->lastScenePos().x();
        qreal dy = mouseEvent->scenePos().y() - mouseEvent->lastScenePos().y();
        moveBy(dx, dy);
    } else {
        QGraphicsItem::mouseMoveEvent( mouseEvent );
    }
}

void BuildingStruct::contextMenuEvent(QGraphicsSceneContextMenuEvent *event)
{
    scene()->clearSelection();
    setSelected(true);
    m_contextMenu->exec(event->screenPos());
}

bool BuildingStruct::sceneEvent(QEvent *event)
{
    QList<QGraphicsItem *>selItems = scene()->selectedItems();
    if (selItems.count() > 1) {
        QGraphicsSceneMouseEvent *mouseEvent = static_cast<QGraphicsSceneMouseEvent *>(event);
        for (QGraphicsItem *item : qAsConst(selItems))
            item->setSelected(true);

        if ((event->type() == QEvent::GraphicsSceneMousePress)
                && (mouseEvent->buttons() == Qt::RightButton))
                m_contextMenu->exec(mouseEvent->screenPos());
        if ((event->type() == QEvent::GraphicsSceneMouseMove)
                && (mouseEvent->buttons() == Qt::LeftButton)) {
            for (QGraphicsItem *item : qAsConst(selItems)) {
                qreal dx = mouseEvent->scenePos().x() - mouseEvent->lastScenePos().x();
                qreal dy = mouseEvent->scenePos().y() - mouseEvent->lastScenePos().y();
                item->moveBy(dx, dy);
            }
        }
        return true;
    } else {
       return QGraphicsItem::sceneEvent(event);
    }
}

QVariant BuildingStruct::itemChange(GraphicsItemChange change, const QVariant &value)
{
    if (change == GraphicsItemChange::ItemSelectedChange && value == true)
        m_sizeGripItem = new SizeGripItem(new ItemResizer, this);
    if (change == GraphicsItemChange::ItemSelectedChange && value == false)
        delete  m_sizeGripItem;

    return QGraphicsItem::itemChange(change, value);
}

void BuildingStruct::drawShape(QPainter *painter)
{
    painter->setRenderHint(QPainter::Antialiasing);
    painter->setRenderHint(QPainter::SmoothPixmapTransform);
    painter->setPen(QPen(Qt::black, 1 ));

    prepareGeometryChange();
    switch (m_shapeType) {
    case Wall: {
        painter->setBrush(wallBrush);
        painter->drawRect(shapeRect);
        break;
    }
    case Window: {
        painter->setBrush(QBrush(Qt::white));
        painter->drawRect(shapeRect);
        painter->drawLine(shapeRect.left(), 0.0, shapeRect.right(), 0.0);
        break;
    }
    case Door: {
        painter->setBrush(QBrush(Qt::white));
        painter->setPen(QPen(Qt::white, 1));
        painter->drawRect(shapeRect);
        painter->setPen(QPen(Qt::black, 1));
        painter->drawRect(QRectF(shapeRect.topLeft(), QSizeF(8.0, shapeRect.height())));
        painter->drawRect(QRectF(shapeRect.right() - 8.0, shapeRect.top(), 8.0, shapeRect.height()));
        painter->drawLine(shapeRect.right() - 8.0, shapeRect.top()
                          , shapeRect.right() - 8.0 - sqrt(shapeRect.width() * shapeRect.width()) / 2
                          , shapeRect.top() - sqrt(shapeRect.width() * shapeRect.width()) / 2);
        QPainterPath arcPath;
        arcPath.moveTo(shapeRect.left() + 8.0, shapeRect.top());
        arcPath.quadTo(shapeRect.left() + 8.0
                       , shapeRect.top() - sqrt(shapeRect.width() * shapeRect.width()) / 4
                       , shapeRect.right() -8.0 - sqrt(shapeRect.width() * shapeRect.width()) / 2
                       , shapeRect.top() - sqrt(shapeRect.width() * shapeRect.width()) / 2);
        painter->drawPath(arcPath);
        break;
    }
    case Open: {
        painter->setBrush(QBrush(Qt::white));
        painter->setPen(QPen(Qt::white, 1));
        painter->drawRect(shapeRect);
        painter->setPen(QPen(Qt::black, 1));
        painter->drawRect(QRectF(shapeRect.topLeft(), QSizeF(8.0, shapeRect.height())));
        painter->drawRect(QRectF(shapeRect.right() - 8.0, shapeRect.top(), 8.0, shapeRect.height()));
        break;
    }
    default:
        break;
    }
    update();
}
