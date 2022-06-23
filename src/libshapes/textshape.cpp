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

#include "../include/textshape.h"

#include <QGraphicsSceneMouseEvent>
#include <QGraphicsScene>
#include <QMenu>

TextShape::TextShape(QMenu *contextMenu, QGraphicsItem *parent)
    : QGraphicsTextItem(parent), m_contextMenu{contextMenu}
{
}

void TextShape::mouseDoubleClickEvent(QGraphicsSceneMouseEvent *mouseEvent)
{
    // NOTE переработать
    if (isSelected()) {
        if (textInteractionFlags() == Qt::NoTextInteraction)
            setTextInteractionFlags(Qt::TextEditorInteraction);
    } else {
        QGraphicsTextItem::mouseDoubleClickEvent(mouseEvent);
    }
}

void TextShape::mouseMoveEvent(QGraphicsSceneMouseEvent *mouseEvent)
{
    if ((mouseEvent->buttons() == Qt::LeftButton) && isSelected()) {
        QList<QGraphicsItem *> selItems = scene()->selectedItems();
        for (QGraphicsItem *item : qAsConst(selItems)) {
            qreal dx = mouseEvent->scenePos().x() - mouseEvent->lastScenePos().x();
            qreal dy = mouseEvent->scenePos().y() - mouseEvent->lastScenePos().y();
            item->moveBy(dx, dy);
        }
    } else {
        QGraphicsTextItem::mouseMoveEvent( mouseEvent );
    }
}

void TextShape::mousePressEvent(QGraphicsSceneMouseEvent *mouseEvent)
{
    if ((mouseEvent->buttons() == Qt::RightButton) && isSelected()) {
        QList<QGraphicsItem *> selItems = scene()->selectedItems();
        for (QGraphicsItem *item : qAsConst(selItems))
            item->setSelected(true);
        m_contextMenu->exec(mouseEvent->screenPos());
    } else {
        QGraphicsTextItem::mousePressEvent( mouseEvent );
    }
}

void TextShape::focusOutEvent(QFocusEvent *focusEvent)
{
    setTextInteractionFlags(Qt::NoTextInteraction);

    QGraphicsTextItem::focusOutEvent(focusEvent);
}
