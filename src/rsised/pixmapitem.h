#ifndef PIXMAPITEM_H
#define PIXMAPITEM_H

#include <QGraphicsPixmapItem>

class SizeGripItem;

QT_BEGIN_NAMESPACE
class QMenu;
QT_END_NAMESPACE

class PixmapItem : public QGraphicsPixmapItem
{
public:
    enum { Type = UserType + 6};

    explicit PixmapItem(QGraphicsItem *parent = nullptr);

    int type() const override {return Type;}
    void scalePixmap(const QRectF &newBoundingRect);

protected:
    void mouseDoubleClickEvent(QGraphicsSceneMouseEvent *mouseEvent) override;
    void mouseMoveEvent(QGraphicsSceneMouseEvent *mouseEvent) override;
    void wheelEvent(QGraphicsSceneWheelEvent *wheelEvent) override;

    QVariant itemChange(GraphicsItemChange change, const QVariant &value) override;

private:
    SizeGripItem *pixmapSizeGripItem;
};

#endif // PIXMAPITEM_H
