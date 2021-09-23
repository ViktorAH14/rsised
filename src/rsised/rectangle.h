#ifndef RECTANGLE_H
#define RECTANGLE_H

#include <QGraphicsRectItem>

class SizeGripItem;

class Rectangle : public QGraphicsRectItem
{
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
    void hoverLeaveEvent(QGraphicsSceneHoverEvent *hoverEvent) override;

    QVariant itemChange(GraphicsItemChange change, const QVariant &value) override;

private:
    SizeGripItem *rectangleSizeGripItem;
};

#endif // RECTANGLE_H
