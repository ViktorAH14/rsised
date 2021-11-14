#include "curve.h"
#include "sizegripitem.h"
#include "curveresizer.h"

#include <QGraphicsSceneMouseEvent>
#include <QApplication>
#include <QGraphicsScene>
#include <QMenu>

Curve::Curve(QMenu *contextMenu, QGraphicsItem *parent)
    : QGraphicsPathItem(parent), m_contextMenu{contextMenu}
{
    setFlag(ItemSendsGeometryChanges, true);
    setAcceptHoverEvents(true);
}

void Curve::mousePressEvent(QGraphicsSceneMouseEvent *mouseEvent)
{
    if (isSelected()) {
        QApplication ::setOverrideCursor(Qt::ClosedHandCursor);
    }

    QGraphicsItem::mousePressEvent(mouseEvent);
}

void Curve::mouseMoveEvent(QGraphicsSceneMouseEvent *mouseEvent)
{
    if ((mouseEvent->buttons() == Qt::LeftButton) && (isSelected())) {
        qreal dx = mouseEvent->scenePos().x() - mouseEvent->lastScenePos().x();
        qreal dy = mouseEvent->scenePos().y() - mouseEvent->lastScenePos().y();
        moveBy(dx, dy);
    } else {
        QGraphicsItem::mouseMoveEvent(mouseEvent);
    }
}

void Curve::mouseReleaseEvent(QGraphicsSceneMouseEvent *mouseEvent)
{
    if (isSelected()) {
        QApplication::restoreOverrideCursor();
    }

    QGraphicsItem::mouseReleaseEvent(mouseEvent);
}

void Curve::contextMenuEvent(QGraphicsSceneContextMenuEvent *event)
{
    scene()->clearSelection();
    setSelected(true);
    m_contextMenu->exec(event->screenPos());
}

QVariant Curve::itemChange(GraphicsItemChange change, const QVariant &value)
{
    if (change == GraphicsItemChange::ItemSelectedChange && value == true) {
        curveSizeGripItem = new SizeGripItem(new CurveResizer, this);
    }
    if (change == GraphicsItemChange::ItemSelectedChange && value == false) {
        delete curveSizeGripItem;
    }
    return QGraphicsItem::itemChange(change, value);
}
