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

#include "abstractshape.h"
#include "sizegripitem.h"
#include "item_resizer.h"

#include <cmath>

#include <QGraphicsScene>
#include <QGraphicsSceneMouseEvent>
#include <QMenu>


AbstractShape::AbstractShape(QMenu *contextMenu, QGraphicsItem *parent)
    : QAbstractGraphicsShapeItem(parent)
    , m_contextMenu{contextMenu}
{

}

AbstractShape::~AbstractShape()
{

}

void AbstractShape::scaleShape(const QRectF &newRect)
{
    prepareGeometryChange();
    QRectF oldRect {boundingRect()};
    qreal oldSize = sqrt(oldRect.width() * oldRect.width() + oldRect.height() * oldRect.height());
    qreal newSize = sqrt(newRect.width() * newRect.width() + newRect.height() * newRect.height());
    qreal scaleFactor = newSize / oldSize;
    setTransform(QTransform::fromScale(scaleFactor, scaleFactor), true);
    update();
}

void AbstractShape::mouseDoubleClickEvent(QGraphicsSceneMouseEvent *mouseEvent)
{
    if (isSelected()) {
        m_sizeGripItem->setActionType((m_sizeGripItem->actionType()
                                       == SizeGripItem::Resize) ? SizeGripItem::Rotate
                                                                :SizeGripItem::Resize);
    } else {
        QGraphicsItem::mouseDoubleClickEvent(mouseEvent);
    }
}

void AbstractShape::mouseMoveEvent(QGraphicsSceneMouseEvent *mouseEvent)
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

void AbstractShape::mousePressEvent(QGraphicsSceneMouseEvent *mouseEvent)
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

void AbstractShape::wheelEvent(QGraphicsSceneWheelEvent *wheelEvent)
{
    if (isSelected()) {
        qreal s_xy {(wheelEvent->delta() > 0) ? 1.03 : 0.97};
        setTransform(QTransform::fromScale(s_xy, s_xy), true);
    } else {
        QGraphicsItem::wheelEvent(wheelEvent);
    }
}

QVariant AbstractShape::itemChange(GraphicsItemChange change, const QVariant &value)
{
    if (change == GraphicsItemChange::ItemSelectedChange && value == true) {
        m_sizeGripItem = new SizeGripItem(new ItemResizer, this);
    }
    if (change == GraphicsItemChange::ItemSelectedChange && value == false) {
        delete  m_sizeGripItem;
    }

    return QGraphicsItem::itemChange(change, value);
}
