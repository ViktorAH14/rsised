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

#include "../include/buildingstruct.h"

#include <QPainter>

BuildingStruct::BuildingStruct(QMenu *contextMenu, ShapeType shapeType, QGraphicsItem *parent)
    : AbstractShape(contextMenu, parent)
    , shapeRect{QRectF(-30.0, -5.0, 60.0, 10.0)}
    , wallBrush(Qt::lightGray)
    , frameWidth{8.0}
    , m_shapeType{shapeType}
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
        rect = QRectF((shapeRect.left() - penWidth / 2.0)
                      , (shapeRect.top() - shapeRect.width() - penWidth / 2.0)
                      , shapeRect.width() + penWidth
                      , shapeRect.height() + shapeRect.width() + penWidth);
    } else {
        rect = QRectF(shapeRect.left() - penWidth / 2.0, shapeRect.top() - penWidth / 2.0
                , shapeRect.width() + penWidth, shapeRect.height() + penWidth);
    }

    return rect;
}

QPainterPath BuildingStruct::shape() const
{
    QPainterPath path;
    path.moveTo(shapeRect.topLeft());
    if (m_shapeType == Door) {
        path.lineTo(shapeRect.left() + frameWidth, shapeRect.top());
        path.quadTo(shapeRect.left() + frameWidth
                    , shapeRect.top() - shapeRect.width() / 4.0
                    , shapeRect.right() - frameWidth - shapeRect.width() / 2.0
                    , shapeRect.top() - shapeRect.width() / 2.0);
        path.lineTo(shapeRect.right() - frameWidth, shapeRect.top());
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
    qreal pixmapWidth = boundingRect().width();
    qreal pixmapHeight = boundingRect().height();
    QPixmap pixmap(pixmapWidth, pixmapHeight);
    pixmap.fill(Qt::transparent);
    QPainter painter(&pixmap);
    painter.translate(pixmapWidth / 2.0, pixmapHeight / 2.0);
    drawShape(&painter);

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

bool BuildingStruct::collidingWallsIsEmpty()
{
    if (collidingWalls.isEmpty()) {
        return true;
    } else {
        return false;
    }
}

QSet<BuildingStruct *> BuildingStruct::getCollidingWalls()
{
    return collidingWalls;
}

void BuildingStruct::setCollidingWals()
{
    QList<QGraphicsItem *> collidingItem = collidingItems();
    BuildingStruct *wallItem;
    for (QGraphicsItem *item : qAsConst(collidingItem)) {
        if ((wallItem = dynamic_cast<BuildingStruct *>(item))
                && (wallItem->shapeType() == Wall) && (wallItem != this)) {
                collidingWalls.insert(wallItem);
                if (!wallItem->collidingWallsIsEmpty()) {
                    collidingWalls += wallItem->getCollidingWalls();
                }
        }
    }
}

void BuildingStruct::drawShape(QPainter *painter)
{
    painter->setRenderHint(QPainter::Antialiasing);
    painter->setRenderHint(QPainter::SmoothPixmapTransform);
    painter->setPen(QPen(Qt::black, 1 ));

    prepareGeometryChange();
    switch (m_shapeType) {
    case Wall: {
        QPainterPath wallPath;
        wallPath.setFillRule(Qt::WindingFill);
        wallPath.addRect(boundingRect());

        setCollidingWals();

        for (BuildingStruct *item : qAsConst(collidingWalls)) {
            wallPath.addPolygon(mapFromItem(item, item->boundingRect()));
        }

        QPainterPath fillPath = wallPath;
        painter->fillPath(fillPath, wallBrush);
        painter->strokePath(wallPath.simplified(), QPen(Qt::black, 1));

        break;
    }
    case Window: {
        painter->setBrush(QBrush(Qt::white));
        painter->drawRect(shapeRect);
        painter->drawLine(shapeRect.left(), 0.0, shapeRect.right(), 0.0);   //Center line
        break;
    }
    case Door: {
        painter->setBrush(QBrush(Qt::white));
        painter->setPen(QPen(Qt::white, 1));
        painter->drawRect(shapeRect);
        painter->setPen(QPen(Qt::black, 1));
        painter->drawRect(QRectF(shapeRect.topLeft(), QSizeF(frameWidth, shapeRect.height())));
        painter->drawRect(QRectF(shapeRect.right() - frameWidth
                                 , shapeRect.top(), frameWidth, shapeRect.height()));
        painter->drawLine(shapeRect.right() - frameWidth, shapeRect.top()
                          , shapeRect.right() - frameWidth - shapeRect.width() / 2.0
                          , shapeRect.top() - shapeRect.width() / 2.0);
        QPainterPath arcPath;
        arcPath.moveTo(shapeRect.left() + frameWidth, shapeRect.top());
        arcPath.quadTo(shapeRect.left() + frameWidth
                       , shapeRect.top() - shapeRect.width() / 4.0
                       , shapeRect.right() - frameWidth - shapeRect.width() / 2.0
                       , shapeRect.top() - shapeRect.width() / 2.0);
        painter->drawPath(arcPath);
        break;
    }
    case Open: {
        painter->setBrush(QBrush(Qt::white));
        painter->setPen(QPen(Qt::white, 1));
        painter->drawRect(shapeRect);
        painter->setPen(QPen(Qt::black, 1));
        painter->drawRect(QRectF(shapeRect.topLeft(), QSizeF(frameWidth, shapeRect.height())));
        painter->drawRect(QRectF(shapeRect.right() - frameWidth
                                 , shapeRect.top(), frameWidth, shapeRect.height()));
        break;
    }
    default:
        break;
    }
    update();
}
