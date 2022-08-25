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

#include <QPainter>
#include <QStyleOptionGraphicsItem>

EllipseShape::EllipseShape(QGraphicsItem *parent)
    : AbstractShape(parent)
    , m_ellipseRect(QRectF())
    , m_startAngle(0)
    , m_spanAngle(360 * 16)
{
    setFlag(ItemSendsGeometryChanges, true);
    setAcceptHoverEvents(true);
}

EllipseShape::EllipseShape(const QRectF &rect, QGraphicsItem *parent)
    : AbstractShape(parent)
    , m_ellipseRect(rect)
    , m_startAngle(0)
    , m_spanAngle(360 *16)
{
    setAcceptHoverEvents(true);
    setFlag(ItemSendsGeometryChanges, true);
}

EllipseShape::EllipseShape(qreal x, qreal y, qreal w, qreal h, QGraphicsItem *parent)
    : AbstractShape(parent)
    , m_ellipseRect(QRectF(x, y, w, h))
    , m_startAngle(0)
    , m_spanAngle(360*16)
{
    setFlag(ItemSendsGeometryChanges, true);
    setAcceptHoverEvents(true);
}

EllipseShape::~EllipseShape()
{

}

QRectF EllipseShape::boundingRect() const
{
    QRectF  boundingRect;
    qreal pw = pen().style() == Qt::NoPen ? qreal(0) : pen().widthF();
    if (pw == 0.0 && m_spanAngle == 360 * 16)
        boundingRect = m_ellipseRect;
    else
        boundingRect = shape().controlPointRect();
    return boundingRect;
}

void EllipseShape::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(widget);

    painter->setPen(pen());
    painter->setBrush(brush());

    if ((m_spanAngle != 0) && (qAbs(m_spanAngle) % (360 * 16) == 0))
        painter->drawEllipse(m_ellipseRect);
    else
        painter->drawPie(m_ellipseRect, m_startAngle, m_spanAngle);

    if (option->state & QStyle::State_Selected)
        highlightSelected(painter, option);

}

QPainterPath EllipseShape::shape() const
{
    QPainterPath path;

    if (m_ellipseRect.isNull())
        return path;
    if (m_spanAngle != 360 * 16) {
        path.moveTo(m_ellipseRect.center());
        path.arcTo(m_ellipseRect, m_startAngle / 16.0, m_spanAngle / 16.0);
    } else {
        path.addEllipse(m_ellipseRect);
    }

    return shapeFromPath(path);
}

bool EllipseShape::contains(const QPointF &point) const
{
    return QAbstractGraphicsShapeItem::contains(point);
}

bool EllipseShape::isObscuredBy(const QGraphicsItem *item) const
{
    return QAbstractGraphicsShapeItem::isObscuredBy(item);
}

QPainterPath EllipseShape::opaqueArea() const
{
    return QAbstractGraphicsShapeItem::opaqueArea();
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

int EllipseShape::startAngle() const
{
    return m_startAngle;
}

void EllipseShape::setStartAngle(int angle)
{
    if (angle != m_startAngle) {
            prepareGeometryChange();
            m_startAngle = angle;
            update();
    }
}

int EllipseShape::spanAngle() const
{
    return m_spanAngle;
}

void EllipseShape::setSpanAngle(int spanAngle)
{
    if (spanAngle != m_spanAngle) {
        prepareGeometryChange();
        m_spanAngle = spanAngle;
        update();
    }
}

void EllipseShape::mouseDoubleClickEvent(QGraphicsSceneMouseEvent *mouseEvent)
{
    if ((m_spanAngle != 0) && (qAbs(m_spanAngle) % (360 *16) != 0)) {
        return;
    } else {
        AbstractShape::mouseDoubleClickEvent(mouseEvent);
    }
}
