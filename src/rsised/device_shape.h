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
