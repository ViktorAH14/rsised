#include "textitem.h"

#include <QGraphicsSceneMouseEvent>
#include <QGraphicsScene>
#include <QMenu>

TextItem::TextItem(QMenu *contextMenu, QGraphicsItem *parent)
    : QGraphicsTextItem(parent), contextMenu{contextMenu}
{
}

void TextItem::mouseDoubleClickEvent(QGraphicsSceneMouseEvent *mouseEvent)
{
    if (textInteractionFlags() == Qt::NoTextInteraction)
        setTextInteractionFlags(Qt::TextEditorInteraction);

    QGraphicsTextItem::mouseDoubleClickEvent(mouseEvent);
}

void TextItem::mouseMoveEvent(QGraphicsSceneMouseEvent *mouseEvent)
{
    if ((mouseEvent->buttons() == Qt::LeftButton) && isSelected()) {
        qreal dx = mouseEvent->scenePos().x() - mouseEvent->lastScenePos().x();
        qreal dy = mouseEvent->scenePos().y() - mouseEvent->lastScenePos().y();
        moveBy(dx, dy);
    } else {
    }
    QGraphicsTextItem::mouseMoveEvent( mouseEvent );
}

void TextItem::contextMenuEvent(QGraphicsSceneContextMenuEvent *event)
{
    scene()->clearSelection();
    setSelected(true);
    contextMenu->exec(event->screenPos());
}

void TextItem::focusOutEvent(QFocusEvent *focusEvent)
{
    setTextInteractionFlags(Qt::NoTextInteraction);

    QGraphicsTextItem::focusOutEvent(focusEvent);
}
