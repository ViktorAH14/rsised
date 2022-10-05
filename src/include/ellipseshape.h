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


#ifndef ELLIPSESHAPE_H
#define ELLIPSESHAPE_H

#include "abstractshape.h"

class EllipseShape : public AbstractShape
{
public:
    enum { Type = UserType + 2 };

    explicit EllipseShape(QGraphicsItem *parent = nullptr);
    explicit EllipseShape(const QRectF &rect, QGraphicsItem *parent = nullptr);
    explicit EllipseShape(qreal x, qreal y, qreal w, qreal h, QGraphicsItem *parent = nullptr);
    ~EllipseShape() = default;

    inline int type() const override { return Type;}
    QRectF boundingRect() const override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;
    QPainterPath shape() const override;
    bool contains(const QPointF &point) const override;
    bool isObscuredBy(const QGraphicsItem *item) const override;
    QPainterPath opaqueArea() const override;

    void setRect(const QRectF &rect);
    void setRect(qreal x, qreal y, qreal w, qreal h);
    QRectF rect() const;

    int startAngle() const;
    void setStartAngle(int angle);

    int spanAngle() const;
    void setSpanAngle(int spanAngle);

protected:
    void mouseDoubleClickEvent(QGraphicsSceneMouseEvent *mouseEvent) override;

private:
    Q_DISABLE_COPY(EllipseShape);

    QRectF m_ellipseRect;
    int m_startAngle;
    int m_spanAngle;
};

#endif // ELLIPSESHAPE_H
