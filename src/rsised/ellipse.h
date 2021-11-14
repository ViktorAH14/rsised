#ifndef ELLIPSE_H
#define ELLIPSE_H

#include <QGraphicsEllipseItem>

class SizeGripItem;

QT_BEGIN_NAMESPACE
class QMenu;
QT_END_MOC_NAMESPACE

class Ellipse : public QGraphicsEllipseItem
{
public:
    enum { Type = UserType + 2 };

    explicit Ellipse(QMenu *contextMenu, QGraphicsItem *parent = nullptr);
    explicit Ellipse(QRectF rect, QMenu *contextMenu, QGraphicsItem *parent = nullptr);

    int type() const override { return Type;}

protected:
    void hoverEnterEvent(QGraphicsSceneHoverEvent *hoverEvent) override;
    void hoverLeaveEvent(QGraphicsSceneHoverEvent *hoverEvent) override;
    void mousePressEvent(QGraphicsSceneMouseEvent *mouseEvent) override;
    void mouseMoveEvent(QGraphicsSceneMouseEvent *mouseEvent) override;
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *mouseEvent) override;
    void mouseDoubleClickEvent(QGraphicsSceneMouseEvent *mouseEvent) override;
    void contextMenuEvent(QGraphicsSceneContextMenuEvent *event) override;

    QVariant itemChange(GraphicsItemChange change, const QVariant &value) override;

private:
    SizeGripItem *ellipseSizeGripItem;
    QMenu *m_contextMenu;
};

#endif // ELLIPSE_H
