#ifndef ELLIPSE_H
#define ELLIPSE_H

#include <QGraphicsEllipseItem>

class SizeGripItem;

class Ellipse : public QGraphicsEllipseItem
{
public:
    enum { Type = UserType + 2 };

    explicit Ellipse(QGraphicsItem *parent = nullptr);
    explicit Ellipse(QRectF rect, QGraphicsItem *parent = nullptr);
    ~Ellipse();

    int type() const override { return Type;}

protected:
    void hoverEnterEvent(QGraphicsSceneHoverEvent *hoverEvent) override;
    void hoverLeaveEvent(QGraphicsSceneHoverEvent *hoverEvent) override;
    void mousePressEvent(QGraphicsSceneMouseEvent *mouseEvent) override;
    void mouseMoveEvent(QGraphicsSceneMouseEvent *mouseEvent) override;
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *mouseEvent) override;
    void mouseDoubleClickEvent(QGraphicsSceneMouseEvent *mouseEvent) override;
    QVariant itemChange(GraphicsItemChange change, const QVariant &value) override;

private:
    SizeGripItem *ellipseSizeGripItem;
};

#endif // ELLIPSE_H
