#include "diagramscene.h"
#include "rectangle.h"
#include "ellipse.h"

#include <QGraphicsSceneMouseEvent>
#include <QGraphicsLineItem>
#include <QMenu>

DiagramScene::DiagramScene(QMenu *editMenu, QObject *parent)
    : QGraphicsScene(parent),
      leftButtonPressed{false},
      currentMode{MoveItem},
      itemMenu{editMenu}
{
}

void DiagramScene::setMode(Mode mode)
{
    currentMode = mode;
}

void DiagramScene::setSelectableItems(bool selectable)
{
    QList<QGraphicsItem *> items = this->items();
    if (selectable) {
        for (QGraphicsItem *item : qAsConst(items)) {
            item->setFlag(QGraphicsItem::ItemIsSelectable, true);
        }
    } else {
        for (QGraphicsItem *item : qAsConst(items)){
            item->setFlag(QGraphicsItem::ItemIsSelectable, false);
        }
    }
}

void DiagramScene::setItemPen(const QColor &color, qreal width, Qt::PenStyle penStyle)
{
    itemPen.setColor(color);
    itemPen.setWidth(width);
    itemPen.setStyle(penStyle);

    if (!selectedItems().isEmpty()){
        QList<QGraphicsItem *> selectedItems = this->selectedItems();
        for (QGraphicsItem *item : qAsConst(selectedItems)) {
            if (QGraphicsLineItem *lineItem = qgraphicsitem_cast<QGraphicsLineItem *>(item)) {
                lineItem->setPen(itemPen);
            }
            if (Rectangle *rectItem = qgraphicsitem_cast<Rectangle *>(item)) {
                rectItem->setPen(itemPen);
            }
            if (Ellipse *ellipseItem = qgraphicsitem_cast<Ellipse *>(item)) {
                ellipseItem->setPen(itemPen);
            }
        }
    }
}

void DiagramScene::setItemBrush(const QColor &color, Qt::BrushStyle brushStyle)
{
    itemBrush.setColor(color);
    itemBrush.setStyle(brushStyle);

    if (!selectedItems().isEmpty()){
        QList<QGraphicsItem *> selectedItems = this->selectedItems();
        for (QGraphicsItem *item : qAsConst(selectedItems)) {
            if (Rectangle *rectItem = qgraphicsitem_cast<Rectangle *>(item)) {
                rectItem->setBrush(itemBrush);
            }
            if (Ellipse *ellipseItem = qgraphicsitem_cast<Ellipse *>(item)) {
                ellipseItem->setBrush(itemBrush);
            }
        }
    }
}

bool DiagramScene::isChanged()
{
    return sceneChanged;
}

void DiagramScene::setSceneChanged(bool changed)
{
    if (changed) {
        sceneChanged = true;
        update();
    } else {
        sceneChanged = false;
    }
}

void DiagramScene::mousePressEvent(QGraphicsSceneMouseEvent *mouseEvent)
{
    if (mouseEvent->button() != Qt::LeftButton) {
        return;
    }

    leftButtonPressed = true;

    switch (currentMode) {
    case InsertLine:
        line = new QGraphicsLineItem(QLineF(mouseEvent->scenePos(), mouseEvent->scenePos()));
        line->setPen(itemPen);
        addItem(line);
        break;
    case InsertRect:
        rect = new Rectangle(QRectF(mouseEvent->scenePos(), mouseEvent->scenePos()), itemMenu);
        addItem(rect);
        break;
    case InsertEllipse:
        ellipse = new Ellipse(QRectF(mouseEvent->scenePos(), mouseEvent->scenePos()), itemMenu);
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
    if (leftButtonPressed) {

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
            rect->setPen(itemPen);
            rect->setBrush(itemBrush);
        }

        if ((currentMode == InsertEllipse) && (ellipse != nullptr)) {
            qreal dx = mouseEvent->scenePos().x() - ellipse->rect().left();
            qreal dy = mouseEvent->scenePos().y() - ellipse->rect().top();
            ellipse->setRect( ( dx > 0 ) ? ellipse->rect().left() : mouseEvent->scenePos().x(),
                              ( dy > 0 ) ? ellipse->rect().top() : mouseEvent->scenePos().y(),
                              qAbs( dx ), qAbs( dy ) );
            ellipse->setPen(itemPen);
            ellipse->setBrush(itemBrush);
        }

        if (currentMode == InsertCurve) {
            curve = addLine(previousPoint.x(), previousPoint.y(),
                            mouseEvent->scenePos().x(), mouseEvent->scenePos().y());
            previousPoint = mouseEvent->scenePos();
            curve->setPen(itemPen);
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

    leftButtonPressed = false;
    setSceneChanged(true);

    QGraphicsScene::mouseReleaseEvent(mouseEvent);
}

bool DiagramScene::isItemChange(int type) const //NOTE удалить если не нужна?
{
    const QList<QGraphicsItem *> items;
    const auto cb = [type](const QGraphicsItem *item) {return item->type() == type;};
    return std::find_if(items.begin(), items.end(), cb) != items.end();
}
