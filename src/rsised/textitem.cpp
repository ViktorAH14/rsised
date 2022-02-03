#include "textitem.h"

#include <QGraphicsSceneMouseEvent>
#include <QGraphicsScene>
#include <QMenu>

TextItem::TextItem(QMenu *contextMenu, QGraphicsItem *parent)
    : QGraphicsTextItem(parent), m_contextMenu{contextMenu}
{
}

void TextItem::mouseDoubleClickEvent(QGraphicsSceneMouseEvent *mouseEvent)
{
    // NOTE переработать
    if (isSelected()) {
        if (textInteractionFlags() == Qt::NoTextInteraction)
            setTextInteractionFlags(Qt::TextEditorInteraction);
    } else {
        QGraphicsTextItem::mouseDoubleClickEvent(mouseEvent);
    }
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

bool TextItem::sceneEvent(QEvent *event)
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
       return QGraphicsTextItem::sceneEvent(event);
    }
}

void TextItem::contextMenuEvent(QGraphicsSceneContextMenuEvent *event)
{
    scene()->clearSelection();
    setSelected(true);
    m_contextMenu->exec(event->screenPos());
}

void TextItem::focusOutEvent(QFocusEvent *focusEvent)
{
    setTextInteractionFlags(Qt::NoTextInteraction);

    QGraphicsTextItem::focusOutEvent(focusEvent);
}
