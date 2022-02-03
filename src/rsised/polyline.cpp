#include "polyline.h"
#include "sizegripitem.h"
#include "item_resizer.h"

#include <QGraphicsSceneMouseEvent>
#include <QGraphicsScene>
#include <QMenu>

Polyline::Polyline(QMenu *contextMenu, QGraphicsItem *parent)
    : QGraphicsPathItem(parent), m_contextMenu{contextMenu}
{
    setFlag(ItemSendsGeometryChanges, true);
    setAcceptHoverEvents(true);
}

void Polyline::mouseDoubleClickEvent(QGraphicsSceneMouseEvent *mouseEvent)
{
    QPointF clickPos = mouseEvent->pos();
    setSelected(false);
    QLineF checkLineFirst(clickPos.x() - 5, clickPos.y() - 5, clickPos.x() + 5, clickPos.y() + 5);
    QLineF checkLineSecond(clickPos.x() + 5, clickPos.y() - 5, clickPos.x() - 5, clickPos.y() + 5);
    QPainterPath oldPath = path();
    QPainterPath newPath;
    for(int i = 0; i < oldPath.elementCount(); i++){
        QLineF checkableLine(oldPath.elementAt(i), oldPath.elementAt(i+1));
        if(checkableLine.intersects(checkLineFirst,0) == 1 || checkableLine.intersects(checkLineSecond,0) == 1){
            if(i == 0){
                newPath.moveTo(oldPath.elementAt(i));
                newPath.lineTo(clickPos);
            } else {
                newPath.lineTo(oldPath.elementAt(i));
                newPath.lineTo(clickPos);
            }
        } else {
            if(i == 0){
                newPath.moveTo(oldPath.elementAt(i));
            } else {
                newPath.lineTo(oldPath.elementAt(i));
            }
        }
        if(i == (oldPath.elementCount() - 2)) {
            newPath.lineTo(oldPath.elementAt(i + 1));
            i++;
        }
    }
    setPath(newPath);
    setSelected(true);

    QGraphicsItem::mouseDoubleClickEvent(mouseEvent);
}

void Polyline::mouseMoveEvent(QGraphicsSceneMouseEvent *mouseEvent)
{
    if ((mouseEvent->buttons() == Qt::LeftButton) && (isSelected())) {
        qreal dx = mouseEvent->scenePos().x() - mouseEvent->lastScenePos().x();
        qreal dy = mouseEvent->scenePos().y() - mouseEvent->lastScenePos().y();
        moveBy(dx, dy);
    } else {
        QGraphicsItem::mouseMoveEvent(mouseEvent);
    }
}

bool Polyline::sceneEvent(QEvent *event)
{
    QList<QGraphicsItem *>selItems = scene()->selectedItems();
    if (selItems.count() > 1) {
        QGraphicsSceneMouseEvent *mouseEvent = static_cast<QGraphicsSceneMouseEvent *>(event);
        for (QGraphicsItem *item : qAsConst(selItems))
            item->setSelected(true);

        if ((event->type() == QEvent::GraphicsSceneMousePress)
                && (mouseEvent->buttons() == Qt::RightButton))
                m_contextMenu->exec(mouseEvent->screenPos());
        if ((event->type() == QEvent::GraphicsSceneMouseMove)
                && (mouseEvent->buttons() == Qt::LeftButton)) {
            for (QGraphicsItem *item : qAsConst(selItems)) {
                qreal dx = mouseEvent->scenePos().x() - mouseEvent->lastScenePos().x();
                qreal dy = mouseEvent->scenePos().y() - mouseEvent->lastScenePos().y();
                item->moveBy(dx, dy);
            }
        }
        return true;
    } else {
       return QGraphicsItem::sceneEvent(event);
    }
}

void Polyline::contextMenuEvent(QGraphicsSceneContextMenuEvent *event)
{
    scene()->clearSelection();
    setSelected(true);
    m_contextMenu->exec(event->screenPos());
}

QVariant Polyline::itemChange(GraphicsItemChange change, const QVariant &value)
{
    if (change == GraphicsItemChange::ItemSelectedChange && value == true) {
        m_sizeGripItem = new SizeGripItem(new ItemResizer, this);
    }
    if (change == GraphicsItemChange::ItemSelectedChange && value == false) {
        delete m_sizeGripItem;
    }
    return QGraphicsItem::itemChange(change, value);
}
