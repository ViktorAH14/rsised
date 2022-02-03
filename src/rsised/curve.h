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
    void mouseMoveEvent(QGraphicsSceneMouseEvent *mouseEvent) override;
    void contextMenuEvent(QGraphicsSceneContextMenuEvent *event) override;
    bool sceneEvent(QEvent *event) override;
    QVariant itemChange(GraphicsItemChange change, const QVariant &value) override;

private:
    SizeGripItem *m_sizeGripItem;
    QMenu *m_contextMenu;
};

#endif // CURVE_H
