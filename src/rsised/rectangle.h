#ifndef RECTANGLE_H
#define RECTANGLE_H

#include <QGraphicsRectItem>

class SizeGripItem;

QT_BEGIN_NAMESPACE
class QMenu;
QT_END_NAMESPACE

class Rectangle : public QGraphicsRectItem
{
public:
    enum { Type = UserType + 1 };

    explicit Rectangle(QMenu *contextMenu, QGraphicsItem *parent = nullptr);
    explicit Rectangle(QRectF rect, QMenu *contextMenu, QGraphicsItem *parent = nullptr);
    ~Rectangle();

    int type() const override { return Type;}

protected:
    void mouseDoubleClickEvent(QGraphicsSceneMouseEvent *mouseEvent) override;
    void mousePressEvent(QGraphicsSceneMouseEvent *mouseEvent) override;
    void mouseMoveEvent(QGraphicsSceneMouseEvent *mouseEvent) override;
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *mouseEvent) override;
    void hoverEnterEvent(QGraphicsSceneHoverEvent *hoverEvent) override;
    void hoverLeaveEvent(QGraphicsSceneHoverEvent *hoverEvent) override;
    void contextMenuEvent(QGraphicsSceneContextMenuEvent *event) override;    

    QVariant itemChange(GraphicsItemChange change, const QVariant &value) override;

private:
    SizeGripItem *rectangleSizeGripItem;
    QMenu *contextMenu;
};

#endif // RECTANGLE_H
