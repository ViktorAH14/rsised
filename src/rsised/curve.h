#ifndef CURVE_H
#define CURVE_H

#include <QGraphicsPathItem>

class SizeGripItem;

class Curve : public QGraphicsPathItem
{
public:
    enum {Type = UserType + 4};

    explicit Curve(QMenu *contextMenu, QGraphicsItem *parent = nullptr);

    int type() const override {return Type;}

protected:
    void mousePressEvent(QGraphicsSceneMouseEvent *mouseEvent) override;
    void mouseMoveEvent(QGraphicsSceneMouseEvent *mouseEvent) override;
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *mouseEvent) override;

    void contextMenuEvent(QGraphicsSceneContextMenuEvent *event) override;
    QVariant itemChange(GraphicsItemChange change, const QVariant &value) override;

private:
    SizeGripItem *curveSizeGripItem;
    QMenu *m_contextMenu;
};

#endif // CURVE_H
