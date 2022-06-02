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

#include "polyline.h"
#include "sizegripitem.h"
#include "item_resizer.h"

#include <QGraphicsSceneMouseEvent>
#include <QGraphicsScene>
#include <QMenu>

Polyline::Polyline(QMenu *contextMenu, QGraphicsItem *parent)
    : QGraphicsPathItem(parent), m_contextMenu{contextMenu}
{
    setFlag(ItemSendsGeometryChanges, true);
    setAcceptHoverEvents(true);
}

void Polyline::mouseDoubleClickEvent(QGraphicsSceneMouseEvent *mouseEvent)
{
    QPointF clickPos = mouseEvent->pos();
    setSelected(false);
    QLineF checkLineFirst(clickPos.x() - 5, clickPos.y() - 5, clickPos.x() + 5, clickPos.y() + 5);
    QLineF checkLineSecond(clickPos.x() + 5, clickPos.y() - 5, clickPos.x() - 5, clickPos.y() + 5);
    QPainterPath oldPath = path();
    QPainterPath newPath;
    for(int i = 0; i < oldPath.elementCount(); i++){
        QLineF checkableLine(oldPath.elementAt(i), oldPath.elementAt(i+1));
        if(checkableLine.intersects(checkLineFirst,0) == 1 || checkableLine.intersects(checkLineSecond,0) == 1){
            if(i == 0){
                newPath.moveTo(oldPath.elementAt(i));
                newPath.lineTo(clickPos);
            } else {
                newPath.lineTo(oldPath.elementAt(i));
                newPath.lineTo(clickPos);
            }
        } else {
            if(i == 0){
                newPath.moveTo(oldPath.elementAt(i));
            } else {
                newPath.lineTo(oldPath.elementAt(i));
            }
        }
        if(i == (oldPath.elementCount() - 2)) {
            newPath.lineTo(oldPath.elementAt(i + 1));
            i++;
        }
    }
    setPath(newPath);
    setSelected(true);

    QGraphicsItem::mouseDoubleClickEvent(mouseEvent);
}

void Polyline::mouseMoveEvent(QGraphicsSceneMouseEvent *mouseEvent)
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

void Polyline::mousePressEvent(QGraphicsSceneMouseEvent *mouseEvent)
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

QVariant Polyline::itemChange(GraphicsItemChange change, const QVariant &value)
{
    if (change == GraphicsItemChange::ItemSelectedChange && value == true) {
        m_sizeGripItem = new SizeGripItem(new ItemResizer, this);
    }
    if (change == GraphicsItemChange::ItemSelectedChange && value == false) {
        delete m_sizeGripItem;
    }
    return QGraphicsItem::itemChange(change, value);
}
