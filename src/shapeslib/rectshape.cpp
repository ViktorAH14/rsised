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

#include "../include/rectshape.h"

#include <QPainter>

RectShape::RectShape(QMenu *contextMenu, QGraphicsItem *parent)
    : AbstractShape(contextMenu, parent), m_shapeRect(QRectF(0.0, 0.0, 0.0,0.0))
{
    setFlag(ItemSendsGeometryChanges, true);
    setAcceptHoverEvents(true);
}

RectShape::RectShape(const QRectF &rect, QMenu *contextMenu, QGraphicsItem *parent)
    : AbstractShape(contextMenu, parent)
{
    setRect(rect);
    setFlag(ItemSendsGeometryChanges, true);
    setAcceptHoverEvents(true);
}

RectShape::RectShape(qreal x, qreal y, qreal w, qreal h, QMenu *contextMenu,
                     QGraphicsItem *parent) : AbstractShape(contextMenu, parent)
{
    setRect(QRectF(x, y, w, h));
    setFlag(ItemSendsGeometryChanges, true);
    setAcceptHoverEvents(true);
}

RectShape::~RectShape()
{
}

QRectF RectShape::boundingRect() const
{
    qreal halfpw = pen().style() == Qt::NoPen ? qreal(0) : pen().widthF() / 2;
    QRectF  boundingRect = m_shapeRect;
    if (halfpw > 0.0)
        boundingRect.adjust(-halfpw, -halfpw, halfpw, halfpw);
    return boundingRect;
}

void RectShape::setRect(const QRectF &rect)
{
    if (m_shapeRect == rect)
        return;
    prepareGeometryChange();
    m_shapeRect.setRect(rect.topLeft().x(), rect.topLeft().y(), rect.width(), rect.height());
    update();
}

void RectShape::setRect(qreal x, qreal y, qreal w, qreal h)
{
    setRect(QRectF(x, y, w, h));
}

QRectF RectShape::rect()
{
    return m_shapeRect;
}

QPainterPath RectShape::shape() const
{
    QPainterPath path;
    path.addRect(m_shapeRect);
    return path;
}

bool RectShape::contains(const QPointF &point) const
{
    return QAbstractGraphicsShapeItem::contains(point);
}

void RectShape::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(option);
    Q_UNUSED(widget);

    painter->setRenderHint(QPainter::Antialiasing);
    painter->setPen(pen());
    painter->setBrush(brush());
    painter->drawRect(m_shapeRect);
}

bool RectShape::isObscuredBy(const QGraphicsItem *item) const
{
    return QAbstractGraphicsShapeItem::isObscuredBy(item);
}

QPainterPath RectShape::opaqueArea() const
{
    return QAbstractGraphicsShapeItem::opaqueArea();
}
