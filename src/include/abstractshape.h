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

#ifndef ABSTRACTSHAPE_H
#define ABSTRACTSHAPE_H

#include <QGraphicsItem>
#include <QMenu>
#include <QPen>

class SizeGripShape;

class AbstractShape : public QGraphicsItem
{
public:
    QPen pen() const;
    void setPen(const QPen &pen);
    QBrush brush() const;
    void setBrush(const QBrush &brush);
    bool isObscuredBy(const QGraphicsItem *item) const override;
    QPainterPath opaqueArea() const override;

    void scaleShape(const QRectF &newRect);
    void setMenu(QMenu *contextMenu);
    QMenu* menu() const;
    void addActions(const QList<QAction *> &actions);

protected:
    explicit AbstractShape(QGraphicsItem *parent = nullptr);
    virtual ~AbstractShape();

    void mouseDoubleClickEvent(QGraphicsSceneMouseEvent *mouseEvent) override;
    void mouseMoveEvent(QGraphicsSceneMouseEvent *mouseEvent) override;
    void mousePressEvent(QGraphicsSceneMouseEvent *mouseEvent) override;
    void wheelEvent(QGraphicsSceneWheelEvent *wheelEvent) override;
    QVariant itemChange(GraphicsItemChange change, const QVariant &value) override;

    void highlightSelected(QPainter *painter, const QStyleOptionGraphicsItem *option);
    QPainterPath shapeFromPath(const QPainterPath &path) const;

private:
    Q_DISABLE_COPY(AbstractShape)

    SizeGripShape   *m_sizeGripItem;
    QMenu   *m_contextMenu;
    QBrush  m_brush;
    QPen    m_pen;
};

#endif // ABSTRACTSHAPE_H
