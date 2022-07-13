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

#include <QPen>
#include <QPainter>

EllipseShape::EllipseShape(QGraphicsItem *parent)
    : AbstractShape(parent)
    , m_startAngle(0)
    , m_spanAngle(0)
{
    setFlag(ItemSendsGeometryChanges, true);
    setAcceptHoverEvents(true);
}

EllipseShape::EllipseShape(const QRectF &rect, QGraphicsItem *parent)
    : AbstractShape(parent)
    , m_ellipseRect(rect)
    , m_startAngle(0)
    , m_spanAngle(0)
{
    setAcceptHoverEvents(true);
    setFlag(ItemSendsGeometryChanges, true);
}

EllipseShape::EllipseShape(qreal x, qreal y, qreal w, qreal h, QGraphicsItem *parent)
    : AbstractShape(parent)
    , m_ellipseRect(QRectF(x, y, w, h))
    , m_startAngle(0)
    , m_spanAngle(0)
{
    setFlag(ItemSendsGeometryChanges, true);
    setAcceptHoverEvents(true);
}

EllipseShape::~EllipseShape()
{

}

QRectF EllipseShape::boundingRect() const
{
    qreal halfpw = pen().style() == Qt::NoPen ? qreal(0.0) : pen().widthF() / 2;
    QRectF  boundingRect = m_ellipseRect;
    if (halfpw > 0.0)
        boundingRect.adjust(-halfpw, -halfpw, halfpw, halfpw);
    return boundingRect;
}

void EllipseShape::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(option);
    Q_UNUSED(widget);

    painter->setRenderHint(QPainter::Antialiasing);
    painter->setPen(pen());
    painter->setBrush(brush());
    painter->drawEllipse(m_ellipseRect);
}

void EllipseShape::setRect(const QRectF &rect)
{
    if (m_ellipseRect == rect)
        return;
    prepareGeometryChange();
    m_ellipseRect = rect;
    update();
}

void EllipseShape::setRect(qreal x, qreal y, qreal w, qreal h)
{
    setRect(QRectF(x, y, w, h));
}

QRectF EllipseShape::rect() const
{
    return m_ellipseRect;
}
