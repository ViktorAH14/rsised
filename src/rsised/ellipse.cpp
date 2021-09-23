#include "ellipse.h"
#include "sizegripitem.h"
#include "ellipseresizer.h"

#include <QGraphicsSceneMouseEvent>
#include <QApplication>

Ellipse::Ellipse(QGraphicsItem *parent) : QGraphicsEllipseItem(parent)
{
    setAcceptHoverEvents(true);
    setFlag(ItemSendsGeometryChanges, true);
}

Ellipse::Ellipse(QRectF rect, QGraphicsItem *parent) : QGraphicsEllipseItem(parent)
{
    QGraphicsEllipseItem::setRect(rect);
    setFlag(ItemSendsGeometryChanges, true);
    setAcceptHoverEvents(true);
}

Ellipse::~Ellipse()
{
}

void Ellipse::hoverEnterEvent(QGraphicsSceneHoverEvent *hoverEvent)
{
    if (isSelected()) {
        QApplication::setOverrideCursor(Qt::OpenHandCursor);
    }

    QGraphicsItem::hoverEnterEvent(hoverEvent);
}

void Ellipse::hoverLeaveEvent(QGraphicsSceneHoverEvent *hoverEvent)
{
    QApplication::restoreOverrideCursor();
    QGraphicsItem::hoverLeaveEvent(hoverEvent);
}

void Ellipse::mousePressEvent(QGraphicsSceneMouseEvent *mouseEvent)
{
    if (isSelected()) {
        QApplication::setOverrideCursor(Qt::ClosedHandCursor);
    }
    QGraphicsItem::mousePressEvent(mouseEvent);
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

void Ellipse::mouseReleaseEvent(QGraphicsSceneMouseEvent *mouseEvent)
{
    if (isSelected()) {
        QApplication::restoreOverrideCursor();
    }

    QGraphicsItem::mouseReleaseEvent(mouseEvent);
}

void Ellipse::mouseDoubleClickEvent(QGraphicsSceneMouseEvent *mouseEvent)
{
    ellipseSizeGripItem->setActionType((ellipseSizeGripItem->actionType() == SizeGripItem::Resize)
                                       ? SizeGripItem::Rotate : SizeGripItem::Resize);

    QGraphicsItem::mouseDoubleClickEvent(mouseEvent);
}

QVariant Ellipse::itemChange(GraphicsItemChange change, const QVariant &value)
{
    if (change == GraphicsItemChange::ItemSelectedChange && value == true) {
        ellipseSizeGripItem = new SizeGripItem(new EllipseResizer, this);
    }
    if (change == GraphicsItemChange::ItemSelectedChange && value == false) {
        delete ellipseSizeGripItem;
    }

    return QGraphicsItem::itemChange(change, value);
}
