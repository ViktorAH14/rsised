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

#ifndef CURVE_H
#define CURVE_H

#include <QGraphicsPathItem>

class SizeGripShape;

class Curve : public QGraphicsPathItem
{
public:
    enum {Type = UserType + 4};

    explicit Curve(QMenu *contextMenu, QGraphicsItem *parent = nullptr);

    int type() const override {return Type;}

protected:
    void mouseMoveEvent(QGraphicsSceneMouseEvent *mouseEvent) override;
    void mousePressEvent(QGraphicsSceneMouseEvent *mouseEvent) override;
    QVariant itemChange(GraphicsItemChange change, const QVariant &value) override;

private:
    SizeGripShape *m_sizeGripItem;
    QMenu *m_contextMenu;
};

#endif // CURVE_H
