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

#ifndef SIZEGRIPSHAPE_H
#define SIZEGRIPSHAPE_H

#include <QGraphicsItem>

class EllipseShape;

class SizeGripShape : public QGraphicsItem
{
public:
public:
    enum ActionType { Resize, Rotate};
    class Resizer
    {
    public:
        virtual ~Resizer() = 0;
        virtual void operator()(QGraphicsItem *item, const QVariant &value) = 0;
    };

    explicit SizeGripShape(Resizer *resizer = nullptr, QGraphicsItem *parent = nullptr);
    virtual ~SizeGripShape();

    QRectF boundingRect() const override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option,QWidget *widget) override;

    void setTopLeft(const QPointF &pos);
    void setTop(qreal y);
    void setTopRight(const QPointF &pos);
    void setRight(qreal x);
    void setBottomRight(const QPointF &pos);
    void setBottom(qreal y);
    void setBottomLeft(const QPointF &pos);
    void setLeft(qreal x);
    void setCenter(const QPointF &pos);
    void setStartPoint(const QPointF &pos);
    void setSpanPoint(const QPointF &pos);

    void setActionType(ActionType actionType);
    ActionType actionType();
    QPainterPath parentItemPath();
    void setParentItemPath(QPainterPath newPath);

private:
    enum PositionFlags {
        PathLine    = 0x0,
        Top         = 0x1,
        Bottom      = 0x2,
        Left        = 0x4,
        TopLeft     = Top | Left,
        BottomLeft  = Bottom | Left,
        Right       = 0x8,
        TopRight    = Top | Right,
        BottomRight = Bottom | Right,
        Center      = 0xB,
        StartPoint  = 0xC,
        SpanPoint    = 0xD
    };

    enum ItemType { Rect, Pie, Path };

    class HandleItem : public QGraphicsRectItem
    {
    public:
        HandleItem(int positionFlags, SizeGripShape *parent);
        int positionFlags() const;
        void setPathElementNum(int num);

    protected:
        void mousePressEvent(QGraphicsSceneMouseEvent *mouseEvent) override;
        void mouseMoveEvent(QGraphicsSceneMouseEvent *mouseEvent) override;
        void mouseReleaseEvent(QGraphicsSceneMouseEvent *mouseEvent) override;
        void hoverEnterEvent(QGraphicsSceneHoverEvent *hoverEvent) override;
        void hoverLeaveEvent(QGraphicsSceneHoverEvent *hoverEvent) override;
        QVariant itemChange(GraphicsItemChange change, const QVariant &value) override;

    private:
        QPointF restrictPosition(const QPointF &newPos);

        int m_handlePositionFlags;
        SizeGripShape *m_parentItem;
        bool m_leftButtonPressed;
        int m_pathElementNum;
    };

    void doResize();
    void rotateParentItem(const QPointF &currentPos, int positionFlag);
    void setItemType(ItemType type);
    void updateHandleItemPositions();
    void setPieHandleItem();

    QList<HandleItem *> handleItemList;
    Resizer *m_itemResizer;
    QRectF m_parentItemRect;
    QPainterPath m_parentPath;
    ActionType m_actionType;
    ItemType m_itemType;
    EllipseShape *m_ellipseShape;
    QPointF m_centerPoint;
    QPointF m_startPoint;
    QPointF m_spanPoint;
};

#endif // SIZEGRIPSHAPE_H
