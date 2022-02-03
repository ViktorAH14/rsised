#include "ellipse.h"
#include "sizegripitem.h"
#include "item_resizer.h"

#include <QGraphicsSceneMouseEvent>
#include <QGraphicsScene>
#include <QMenu>

Ellipse::Ellipse(QMenu *contextMenu, QGraphicsItem *parent)
    : QGraphicsEllipseItem(parent), m_contextMenu{contextMenu}
{
    setAcceptHoverEvents(true);
    setFlag(ItemSendsGeometryChanges, true);
}

Ellipse::Ellipse(QRectF rect, QMenu *contextMenu, QGraphicsItem *parent)
    : QGraphicsEllipseItem(parent), m_contextMenu{contextMenu}
{
    QGraphicsEllipseItem::setRect(rect);
    setFlag(ItemSendsGeometryChanges, true);
    setAcceptHoverEvents(true);
}

void Ellipse::mouseMoveEvent(QGraphicsSceneMouseEvent *mouseEvent)
{
    if (mouseEvent->buttons() == Qt::LeftButton && isSelected()) {
        qreal dx = mouseEvent->scenePos().x() - mouseEvent->lastScenePos().x();
        qreal dy = mouseEvent->scenePos().y() - mouseEvent->lastScenePos().y();
        moveBy(dx, dy);
    } else {
        QGraphicsItem::mouseMoveEvent(mouseEvent);
    }
}

void Ellipse::mouseDoubleClickEvent(QGraphicsSceneMouseEvent *mouseEvent)
{
    if (isSelected()) {
        m_sizeGripItem->setActionType((m_sizeGripItem->actionType()
                                       == SizeGripItem::Resize) ? SizeGripItem::Rotate
                                                                :SizeGripItem::Resize);
    } else {
        QGraphicsItem::mouseDoubleClickEvent(mouseEvent);
    }
}

bool Ellipse::sceneEvent(QEvent *event)
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

void Ellipse::contextMenuEvent(QGraphicsSceneContextMenuEvent *event)
{
    scene()->clearSelection();
    setSelected(true);
    m_contextMenu->exec(event->screenPos());
}

QVariant Ellipse::itemChange(GraphicsItemChange change, const QVariant &value)
{
    if (change == GraphicsItemChange::ItemSelectedChange && value == true) {
        m_sizeGripItem = new SizeGripItem(new ItemResizer, this);
    }
    if (change == GraphicsItemChange::ItemSelectedChange && value == false) {
        delete m_sizeGripItem;
    }

    return QGraphicsItem::itemChange(change, value);
}
