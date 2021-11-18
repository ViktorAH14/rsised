#include "rectangle.h"
#include "sizegripitem.h"
#include "rectangleresizer.h"

#include <QApplication>
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
    rectangleSizeGripItem->setActionType((rectangleSizeGripItem->actionType()
                                          == SizeGripItem::Resize) ? SizeGripItem::Rotate
                                                                   :SizeGripItem::Resize);

    QGraphicsItem::mouseDoubleClickEvent(mouseEvent);
}

//NOTE наверное лучше отключить эти функции
void Rectangle::mousePressEvent(QGraphicsSceneMouseEvent *mouseEvent)
{
    if (isSelected()){
        QApplication::setOverrideCursor(Qt::ClosedHandCursor);
    }

    QGraphicsItem::mousePressEvent( mouseEvent );
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

void Rectangle::mouseReleaseEvent(QGraphicsSceneMouseEvent *mouseEvent)
{
    if (isSelected()) {
    QApplication::restoreOverrideCursor();
    }

    QGraphicsItem::mouseReleaseEvent(mouseEvent);
}

void Rectangle::hoverEnterEvent(QGraphicsSceneHoverEvent *hoverEvent)
{
    if (isSelected()) {
        QApplication::setOverrideCursor(Qt::OpenHandCursor);
    }

    QGraphicsItem::hoverEnterEvent(hoverEvent);
}

void Rectangle::hoverLeaveEvent(QGraphicsSceneHoverEvent *hoverEvent)
{
    QApplication::restoreOverrideCursor();

    QGraphicsItem::hoverLeaveEvent(hoverEvent);
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
        rectangleSizeGripItem = new SizeGripItem(new RectangleResizer, this);
    }
    if (change == GraphicsItemChange::ItemSelectedChange && value == false) {
        delete  rectangleSizeGripItem;
    }

    return QGraphicsItem::itemChange(change, value);
}
