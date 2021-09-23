#ifndef RECTANGLE_H
#define RECTANGLE_H

#include <QGraphicsRectItem>

QT_BEGIN_NAMESPACE
//class QGraphicsSceneMouseEvent;
class QGraphicsSceneHoverEvent;
QT_END_NAMESPACE

class Rectangle : public QGraphicsRectItem
{
    enum class ActionType { Resize, Rotation };
    enum class CornerFlags
    {
        None,
        Top,
        Bottom,
        Left,
        Right,
        TopLeft,
        TopRight,
        BottomLeft,
        BottomRight
    };

public:
    enum { Type = UserType + 1 };

    explicit Rectangle(QGraphicsItem *parent = nullptr);
    explicit Rectangle(QRectF rect, QGraphicsItem *parent = nullptr);
    ~Rectangle();

    int type() const override { return Type;}

protected:
    void mouseDoubleClickEvent(QGraphicsSceneMouseEvent *mouseEvent) override;
    void mousePressEvent(QGraphicsSceneMouseEvent *mouseEvent) override;
    void mouseMoveEvent(QGraphicsSceneMouseEvent *mouseEvent) override;
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *mouseEvent) override;
    void hoverEnterEvent(QGraphicsSceneHoverEvent *hoverEvent) override;
    void hoverMoveEvent(QGraphicsSceneHoverEvent *hoverEvent) override;
    void hoverLeaveEvent(QGraphicsSceneHoverEvent *hoverEvent) override;

    QVariant itemChange(GraphicsItemChange change, const QVariant &value) override;

private:
    ActionType m_actionType;
    CornerFlags m_cornerFlag;

    void resizeLeft(const QPointF &currentPoint);
    void resizeRight(const QPointF &currentPoint);
    void resizeBottom(const QPointF &currentPoint);
    void resizeTop(const QPointF &currentPoint);
    void rotateItem(const QPointF &currentPoint);
};

#endif // RECTANGLE_H
