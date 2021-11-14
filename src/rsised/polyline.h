#ifndef POLYLINE_H
#define POLYLINE_H

#include <QGraphicsPathItem>

class SizeGripItem;

class Polyline : public QGraphicsPathItem
{
public:
    enum {Type = UserType + 3};

    explicit Polyline(QMenu *contextMenu, QGraphicsItem *parent = nullptr);

    int type() const override { return Type;}

protected:
    void mouseDoubleClickEvent(QGraphicsSceneMouseEvent *mouseEvent) override;
    void mousePressEvent(QGraphicsSceneMouseEvent *mouseEvent) override;
    void mouseMoveEvent(QGraphicsSceneMouseEvent *mouseEvent) override;
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *mouseEvent) override;
    void contextMenuEvent(QGraphicsSceneContextMenuEvent *event) override;

    QVariant itemChange(GraphicsItemChange change, const QVariant &value) override;

private:
    SizeGripItem *polylineSizeGripItem;
    QMenu *m_contextMenu;
};

#endif // POLYLINE_H
