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

#include <QGraphicsEllipseItem>

class SizeGripShape;

class EllipseShape : public QGraphicsEllipseItem
{
public:
    enum { Type = UserType + 2 };

    explicit EllipseShape(QMenu *contextMenu, QGraphicsItem *parent = nullptr);
    explicit EllipseShape(QRectF rect, QMenu *contextMenu, QGraphicsItem *parent = nullptr);

    int type() const override { return Type;}

protected:
    void mouseMoveEvent(QGraphicsSceneMouseEvent *mouseEvent) override;
    void mouseDoubleClickEvent(QGraphicsSceneMouseEvent *mouseEvent) override;
    void mousePressEvent(QGraphicsSceneMouseEvent *mouseEvent) override;
    QVariant itemChange(GraphicsItemChange change, const QVariant &value) override;

private:
    SizeGripShape *m_sizeGripShape;
    QMenu *m_contextMenu;
};

#endif // ELLIPSESHAPE_H
