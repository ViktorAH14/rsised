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

#ifndef BUILDINGSTRUCT_H
#define BUILDINGSTRUCT_H

#include <QAbstractGraphicsShapeItem>
#include <QBrush>

class SizeGripItem;

class BuildingStruct : public QAbstractGraphicsShapeItem
{
public:
    enum { Type = UserType + 40 };
    enum ShapeType { Wall, Window, Door, Open };

    BuildingStruct(QMenu *contextMenu, ShapeType shapeType, QGraphicsItem *parent = nullptr);

    QRectF boundingRect() const override;
    QPainterPath shape() const override;
    int type() const override {return Type;}

    QPixmap image();
    ShapeType shapeType() const;
    void setRect(QRectF rect);
    QRectF getRect();

protected:
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;
    void mouseDoubleClickEvent(QGraphicsSceneMouseEvent *mouseEvent) override;
    void mouseMoveEvent(QGraphicsSceneMouseEvent *mouseEvent) override;
    void contextMenuEvent(QGraphicsSceneContextMenuEvent *event) override;
    bool sceneEvent(QEvent *event) override;
    QVariant itemChange(GraphicsItemChange change, const QVariant &value) override;

private:
    void drawShape(QPainter *painter);

    QRectF shapeRect;
    QBrush wallBrush;

    ShapeType m_shapeType;
    QMenu *m_contextMenu;
    SizeGripItem *m_sizeGripItem;
};

#endif // BUILDINGSTRUCT_H
