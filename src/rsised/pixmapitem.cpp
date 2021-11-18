#include "pixmapitem.h"
#include "sizegripitem.h"
#include "pixmapresizer.h"

#include <QGraphicsScene>
#include <QGraphicsSceneMouseEvent>
#include <QMenu>

PixmapItem::PixmapItem(QGraphicsItem *parent)
    : QGraphicsPixmapItem(parent)
{
    setFlag(ItemSendsGeometryChanges, true);
    setAcceptHoverEvents(true);
}

// TODO не совсем адекватное поведение при изменении размеров,
// вариант с масштабирование QPixmap даёт худшие результаты
void PixmapItem::scalePixmap(const QRectF &newBoundingRect)
{
    prepareGeometryChange();
    QRectF oldRect {boundingRect()};
    if (oldRect.topLeft() != newBoundingRect.topLeft()) {
        setOffset(newBoundingRect.topLeft());
    }
    qreal sx {newBoundingRect.width() / oldRect.width()};
    qreal sy {newBoundingRect.height() / oldRect.height()};
    if (sx > 1.0) {
        sx = 1.0015;
    } else if (sx < 1.0) {
        sx = 0.998502247;
    }
    if (sy > 1.0) {
        sy = 1.0015;
    } else if (sy < 1.0){
        sy = 0.998502247;
    }
    setTransform(QTransform::fromScale(sx, sy), true);
    update();
}

void PixmapItem::mouseDoubleClickEvent(QGraphicsSceneMouseEvent *mouseEvent)
{
    if (isSelected()) {
        pixmapSizeGripItem->setActionType((pixmapSizeGripItem->actionType()
                                           == SizeGripItem::Resize) ? SizeGripItem::Rotate
                                                                    :SizeGripItem::Resize);
    }

    QGraphicsItem::mouseDoubleClickEvent(mouseEvent);
}

void PixmapItem::mouseMoveEvent(QGraphicsSceneMouseEvent *mouseEvent)
{
    if ((mouseEvent->buttons() == Qt::LeftButton) && isSelected()) {
        qreal dx {mouseEvent->scenePos().x() - mouseEvent->lastScenePos().x()};
        qreal dy {mouseEvent->scenePos().y() - mouseEvent->lastScenePos().y()};
        moveBy(dx, dy);
    } else {
        QGraphicsItem::mouseMoveEvent(mouseEvent);
    }
}

void PixmapItem::wheelEvent(QGraphicsSceneWheelEvent *wheelEvent)
{
    if (isSelected()) {
        qreal s_xy {(wheelEvent->delta() > 0) ? 1.02 : 0.98};
        setTransform(QTransform::fromScale(s_xy, s_xy), true);
    } else {
        QGraphicsItem::wheelEvent(wheelEvent);
    }
}

QVariant PixmapItem::itemChange(GraphicsItemChange change, const QVariant &value)
{
    if (change == GraphicsItemChange::ItemSelectedChange && value == true) {
        pixmapSizeGripItem = new SizeGripItem(new PixmapResizer, this);
    }
    if (change == GraphicsItemChange::ItemSelectedChange && value == false) {
        delete  pixmapSizeGripItem;
    }

    return QGraphicsItem::itemChange(change, value);
}
