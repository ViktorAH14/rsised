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
