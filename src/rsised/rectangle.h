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
    Rectangle(QRectF rect, QMenu *contextMenu, QGraphicsItem *parent = nullptr);

    int type() const override { return Type;}

protected:
    void mouseDoubleClickEvent(QGraphicsSceneMouseEvent *mouseEvent) override;
    void mouseMoveEvent(QGraphicsSceneMouseEvent *mouseEvent) override;
    void contextMenuEvent(QGraphicsSceneContextMenuEvent *event) override;
    bool sceneEvent(QEvent *event) override;
    QVariant itemChange(GraphicsItemChange change, const QVariant &value) override;

private:
    SizeGripItem *m_sizeGripItem;
    QMenu *m_contextMenu;
};

#endif // RECTANGLE_H
