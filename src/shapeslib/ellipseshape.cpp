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

#include "../include/ellipseshape.h"
#include "../include/sizegripshape.h"
#include "../include/shaperesizer.h"

#include <QGraphicsSceneMouseEvent>
#include <QGraphicsScene>
#include <QMenu>

EllipseShape::EllipseShape(QMenu *contextMenu, QGraphicsItem *parent)
    : QGraphicsEllipseItem(parent), m_contextMenu{contextMenu}
{
    setAcceptHoverEvents(true);
    setFlag(ItemSendsGeometryChanges, true);
}

EllipseShape::EllipseShape(QRectF rect, QMenu *contextMenu, QGraphicsItem *parent)
    : QGraphicsEllipseItem(parent), m_contextMenu{contextMenu}
{
    QGraphicsEllipseItem::setRect(rect);
    setFlag(ItemSendsGeometryChanges, true);
    setAcceptHoverEvents(true);
}

void EllipseShape::mouseMoveEvent(QGraphicsSceneMouseEvent *mouseEvent)
{
    if ((mouseEvent->buttons() == Qt::LeftButton) && isSelected()) {
        QList<QGraphicsItem *> selItems = scene()->selectedItems();
        for (QGraphicsItem *item : qAsConst(selItems)) {
            qreal dx = mouseEvent->scenePos().x() - mouseEvent->lastScenePos().x();
            qreal dy = mouseEvent->scenePos().y() - mouseEvent->lastScenePos().y();
            item->moveBy(dx, dy);
        }
    } else {
        QGraphicsItem::mouseMoveEvent( mouseEvent );
    }
}

void EllipseShape::mouseDoubleClickEvent(QGraphicsSceneMouseEvent *mouseEvent)
{
    if (isSelected()) {
        m_sizeGripShape->setActionType((m_sizeGripShape->actionType()
                                       == SizeGripShape::Resize) ? SizeGripShape::Rotate
                                                                :SizeGripShape::Resize);
    } else {
        QGraphicsItem::mouseDoubleClickEvent(mouseEvent);
    }
}

void EllipseShape::mousePressEvent(QGraphicsSceneMouseEvent *mouseEvent)
{
    if ((mouseEvent->buttons() == Qt::RightButton) && isSelected()) {
        QList<QGraphicsItem *> selItems = scene()->selectedItems();
        for (QGraphicsItem *item : qAsConst(selItems))
            item->setSelected(true);
        m_contextMenu->exec(mouseEvent->screenPos());
    } else {
        QGraphicsItem::mousePressEvent(mouseEvent);
    }
}

QVariant EllipseShape::itemChange(GraphicsItemChange change, const QVariant &value)
{
    if (change == GraphicsItemChange::ItemSelectedChange && value == true) {
        m_sizeGripShape = new SizeGripShape(new ShapeResizer, this);
    }
    if (change == GraphicsItemChange::ItemSelectedChange && value == false) {
        delete m_sizeGripShape;
    }

    return QGraphicsItem::itemChange(change, value);
}
