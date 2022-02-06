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

#ifndef DEVICE_SHAPE_H
#define DEVICE_SHAPE_H

#include <QAbstractGraphicsShapeItem>

class SizeGripItem;

class DeviceShape : public QAbstractGraphicsShapeItem
{
public:
    enum {Type = UserType + 30};
    enum ShapeType { Barrel
                     , Branches_3
                     , Branches_4
                     , Collector };

    DeviceShape(QMenu *contextMenu, ShapeType shapeType, QGraphicsItem *parent = nullptr);

    QRectF boundingRect() const override;
    int type() const override {return Type;}

    QPixmap image();
    void scaleDeviceShape(const QRectF &newRect);
    ShapeType shapeType() const;

protected:
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;
    void mouseDoubleClickEvent(QGraphicsSceneMouseEvent *mouseEvent) override;
    void mouseMoveEvent(QGraphicsSceneMouseEvent *mouseEvent) override;
    bool sceneEvent(QEvent *event) override;
    void contextMenuEvent(QGraphicsSceneContextMenuEvent *event) override;
    void wheelEvent(QGraphicsSceneWheelEvent *wheelEvent) override;
    QVariant itemChange(GraphicsItemChange change, const QVariant &value) override;

private:
    void drawShape(QPainter *painter);

    ShapeType m_shapeType;
    SizeGripItem *m_sizeGripItem;
    QMenu *m_contextMenu;
};

#endif // DEVICE_SHAPE_H
