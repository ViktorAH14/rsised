#ifndef TECHNICS_SHAPE_H
#define TECHNICS_SHAPE_H

#include <QAbstractGraphicsShapeItem>

class SizeGripItem;

class TechnicsShape : public QAbstractGraphicsShapeItem
{
public:
    enum { Type = UserType + 20};
    enum ShapeType{ Base
                    , Tanker
                    , AutoPump
                    , AutoLadder
                    , CrankLift
                    , TelescopicLift
                    , Tracked
                    , Adapted
                    , Ambulance
                    , Police };

    TechnicsShape(QMenu *contextMenu, ShapeType shapeType, QGraphicsItem *parent = nullptr);

    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;
    QRectF boundingRect() const override;
    QPainterPath shape() const override;
    int type() const override { return Type;}

    QPixmap image() const;
    void scaleTechnicsShape(const QRectF &newRect);
    ShapeType shapeType() const;

protected:
    void mouseDoubleClickEvent(QGraphicsSceneMouseEvent *mouseEvent) override;
    void mouseMoveEvent(QGraphicsSceneMouseEvent *mouseEvent) override;
    void contextMenuEvent(QGraphicsSceneContextMenuEvent *event) override;
    void wheelEvent(QGraphicsSceneWheelEvent *wheelEvent) override;
    QVariant itemChange(GraphicsItemChange change, const QVariant &value) override;

private:
    QPainterPath m_path;
    ShapeType m_shapeType;
    SizeGripItem *m_sizeGripItem;
    QMenu *m_contextMenu;
    QPolygonF autoBase;
    QPolygonF adaptedPolygon;
    QPolygonF ambulancePolygon;
};

#endif // TECHNICS_SHAPE_H
