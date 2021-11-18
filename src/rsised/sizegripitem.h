#ifndef SIZEGRIPITEM_H
#define SIZEGRIPITEM_H

#include <QGraphicsRectItem>

class SizeGripItem : public QGraphicsItem
{
public:
    enum ActionType { Resize, Rotate};
    class Resizer
    {
    public:
        virtual ~Resizer() = 0;
        virtual void operator()(QGraphicsItem *item, const QVariant &value) = 0;
    };

    SizeGripItem(Resizer *resizer = nullptr, QGraphicsItem *parent = nullptr);
    virtual ~SizeGripItem();
    QRectF boundingRect() const override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option,
               QWidget *widget = 0) override;
    void setTopLeft(const QPointF &pos);
    void setTop(qreal y);
    void setTopRight(const QPointF &pos);
    void setRight(qreal x);
    void setBottomRight(const QPointF &pos);
    void setBottom(qreal y);
    void setBottomLeft(const QPointF &pos);
    void setLeft(qreal x);

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
        BottomRight = Bottom | Right
    };

    enum ItemType { Rectangle, Path };

    class HandleItem : public QGraphicsRectItem
    {
    public:
        HandleItem(int positionFlags, SizeGripItem *parent);
        int positionFlags() const;
        void setPathElementNum(int num);

    protected:
        void mousePressEvent(QGraphicsSceneMouseEvent *mouseEvent) override;
        void mouseMoveEvent(QGraphicsSceneMouseEvent *mouseEvent) override;
        void mouseReleaseEvent(QGraphicsSceneMouseEvent *mouseEvent) override;
        void hoverEnterEvent(QGraphicsSceneHoverEvent *hoverEvent) override;
        void hoverLeaveEvent(QGraphicsSceneHoverEvent *hoverevent) override;
        QVariant itemChange(GraphicsItemChange change, const QVariant &value) override;

    private:
        QPointF restrictPosition(const QPointF &newPos);

        int handlePositionFlags;
        SizeGripItem *parentItem;
        bool leftButtonPressed;
        int pathElementNum;
    };

    void doResize();
    void rotateParentItem(const QPointF &currentPos, int positionFlag);
    void setItemType(ItemType type);
    void updateHandleItemPositions();

    QList<HandleItem *> handleItemList;
    Resizer *itemResizer;
    QRectF m_parentItemRect;
    QPainterPath m_parentPath;
    ActionType m_actionType;
    ItemType m_itemType;
};

#endif // SIZEGRIPITEM_H
