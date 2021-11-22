#include "rectangle.h"
#include "sizegripitem.h"
#include "item_resizer.h"

#include <QGraphicsSceneMouseEvent>
#include <QMenu>
#include <QGraphicsScene>

Rectangle::Rectangle(QMenu *contextMenu, QGraphicsItem *parent)
    : QGraphicsRectItem(parent), m_contextMenu{contextMenu}
{
    setFlag(ItemSendsGeometryChanges, true);
    setAcceptHoverEvents(true);
}

Rectangle::Rectangle(QRectF rect, QMenu *contextMenu, QGraphicsItem *parent)
    : QGraphicsRectItem(parent), m_contextMenu{contextMenu}
{
    QGraphicsRectItem::setRect(rect);
    setFlag(ItemSendsGeometryChanges, true);
    setAcceptHoverEvents(true);
}

void Rectangle::mouseDoubleClickEvent(QGraphicsSceneMouseEvent *mouseEvent)
{
    if (isSelected()) {
        m_sizeGripItem->setActionType((m_sizeGripItem->actionType()
                                              == SizeGripItem::Resize) ? SizeGripItem::Rotate
                                                                       :SizeGripItem::Resize);
    } else {
        QGraphicsItem::mouseDoubleClickEvent(mouseEvent);
    }
}

void Rectangle::mouseMoveEvent(QGraphicsSceneMouseEvent *mouseEvent)
{
    if ((mouseEvent->buttons() == Qt::LeftButton) && isSelected()) {
        qreal dx = mouseEvent->scenePos().x() - mouseEvent->lastScenePos().x();
        qreal dy = mouseEvent->scenePos().y() - mouseEvent->lastScenePos().y();
        moveBy(dx, dy);
    } else {
        QGraphicsItem::mouseMoveEvent( mouseEvent );
    }
}

void Rectangle::contextMenuEvent(QGraphicsSceneContextMenuEvent *event)
{
    scene()->clearSelection();
    setSelected(true);
    m_contextMenu->exec(event->screenPos());
}

QVariant Rectangle::itemChange(GraphicsItemChange change, const QVariant &value)
{
    if (change == GraphicsItemChange::ItemSelectedChange && value == true) {
        m_sizeGripItem = new SizeGripItem(new ItemResizer, this);
    }
    if (change == GraphicsItemChange::ItemSelectedChange && value == false) {
        delete  m_sizeGripItem;
    }

    return QGraphicsItem::itemChange(change, value);
}
