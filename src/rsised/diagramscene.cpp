#include "diagramscene.h"
#include "rectangle.h"

#include <QGraphicsSceneMouseEvent>
#include <QGraphicsLineItem>
#include <QGraphicsEllipseItem>

DiagramScene::DiagramScene(QObject *parent)
    : QGraphicsScene(parent),
      leftButton {false},
      currentMode {MoveItem}
{
    itemPen = new QPen();
}

void DiagramScene::setMode(Mode mode)
{
    currentMode = mode;
}

void DiagramScene::setSelectableItems(bool selectable)
{
    if (selectable) {
        foreach (QGraphicsItem *item, items()) {
            item->setFlag(QGraphicsItem::ItemIsSelectable, true);
        }
    } else {
        foreach (QGraphicsItem *item, items()){
            item->setFlag(QGraphicsItem::ItemIsSelectable, false);
        }
    }
}

void DiagramScene::setItemPen(const QColor &color, qreal width, Qt::PenStyle penStyle)
{
    itemPen->setColor(color);
    itemPen->setWidth(width);
    itemPen->setStyle(penStyle);

    if (!selectedItems().isEmpty()){
        QList<QGraphicsItem *> selectedItems = this->selectedItems();
        for (QGraphicsItem *item : qAsConst(selectedItems)) {
            if (QGraphicsLineItem *lineItem = qgraphicsitem_cast<QGraphicsLineItem *>(item)) {
                lineItem->setPen(*itemPen);
            }
            if (Rectangle *rectItem = qgraphicsitem_cast<Rectangle *>(item)) {
                rectItem->setPen(*itemPen);
            }
            if (QGraphicsEllipseItem *ellipseItem = qgraphicsitem_cast<QGraphicsEllipseItem *>(item)) {
                ellipseItem->setPen(*itemPen);
            }
        }
    }
}

void DiagramScene::mousePressEvent(QGraphicsSceneMouseEvent *mouseEvent)
{
    if (mouseEvent->button() != Qt::LeftButton) {
        return;
    }

    leftButton = true;

    switch (currentMode) {
    case InsertLine:
        line = new QGraphicsLineItem(QLineF(mouseEvent->scenePos(), mouseEvent->scenePos()));
//        line->setPen(QPen(penColor, 1, penStyle));
        line->setPen(*itemPen);
        addItem(line);
        break;
    case InsertRect:
        rect = new Rectangle(QRectF(mouseEvent->scenePos(), mouseEvent->scenePos()));
        addItem(rect);
        break;
    case InsertEllipse:
        ellipse = new QGraphicsEllipseItem(QRectF(mouseEvent->scenePos(), mouseEvent->scenePos()));
//        ellipse->setPen(QPen(penColor, 1, penStyle));
        ellipse->setPen(*itemPen);
        ellipse->setBrush(QBrush(Qt::magenta));
        addItem(ellipse);
        break;
    case InsertCurve:
        previousPoint = mouseEvent->scenePos();
        break;
    default:
        break;
    }

    QGraphicsScene::mousePressEvent(mouseEvent);
}

void DiagramScene::mouseMoveEvent(QGraphicsSceneMouseEvent *mouseEvent)
{
    if (leftButton) {

        if ((currentMode == InsertLine) && (line != nullptr)) {
            QLineF newLine(line->line().p1(), mouseEvent->scenePos());
            line->setLine(newLine);
            line->setFlag(QGraphicsItem::ItemIsMovable, true);
        }

        if ((currentMode == InsertRect) && (rect != nullptr)) {
            qreal dx = mouseEvent->scenePos().x() - rect->rect().left();
            qreal dy = mouseEvent->scenePos().y() - rect->rect().top();
            rect->setRect( ( dx > 0 ) ? rect->rect().left() : mouseEvent->scenePos().x(),
                           ( dy > 0 ) ? rect->rect().top() : mouseEvent->scenePos().y(),
                           qAbs( dx ), qAbs( dy ) );
//            rect->setPen(QPen(penColor, 1, penStyle));
            rect->setPen(*itemPen);
        }

        if ((currentMode == InsertEllipse) && (ellipse != nullptr)) {
            qreal dx = mouseEvent->scenePos().x() - ellipse->rect().left();
            qreal dy = mouseEvent->scenePos().y() - ellipse->rect().top();
            ellipse->setRect( ( dx > 0 ) ? ellipse->rect().left() : mouseEvent->scenePos().x(),
                              ( dy > 0 ) ? ellipse->rect().top() : mouseEvent->scenePos().y(),
                              qAbs( dx ), qAbs( dy ) );
            ellipse->setFlag(QGraphicsItem::ItemIsMovable, true);
        }

        if (currentMode == InsertCurve) {
            curve = addLine(previousPoint.x(), previousPoint.y(),
                            mouseEvent->scenePos().x(), mouseEvent->scenePos().y());
            previousPoint = mouseEvent->scenePos();
//            curve->setPen(QPen(penColor, 1, penStyle));
            curve->setPen(*itemPen);
        }
    }

    QGraphicsScene::mouseMoveEvent(mouseEvent);
}

void DiagramScene::mouseReleaseEvent(QGraphicsSceneMouseEvent *mouseEvent)
{
    switch (currentMode) {
    case InsertLine:
        line = nullptr;
        break;
    case InsertRect:
        rect = nullptr;
        break;
    case InsertEllipse:
        ellipse = nullptr;
        break;
    case InsertCurve:
        break;
    default:
        break;
    }

    leftButton = false;

    QGraphicsScene::mouseReleaseEvent(mouseEvent);
}

bool DiagramScene::isItemChange(int type) const
{
    const QList<QGraphicsItem *> items;
    const auto cb = [type](const QGraphicsItem *item) {return item->type() == type;};
    return std::find_if(items.begin(), items.end(), cb) != items.end();
}
