#include "diagramscene.h"
#include "rectangle.h"
#include "ellipse.h"
#include "polyline.h"

#include <QGraphicsSceneMouseEvent>
#include <QMenu>

DiagramScene::DiagramScene(QMenu *editMenu, QObject *parent)
    : QGraphicsScene(parent),
      rectangle{nullptr},
      polyline{nullptr},
      ellipse{nullptr},
      curve{nullptr},
      itemMenu{editMenu},
      currentMode{SelectItem},
      leftButtonPressed{false},
      sceneChanged{false}
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

void DiagramScene::setItemPen(const QColor &color, const qreal width, const Qt::PenStyle &penStyle)
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
            if (Polyline *polylineItem = qgraphicsitem_cast<Polyline *>(item)) {
                polylineItem->setPen(itemPen);
            }
        }
    }
}

void DiagramScene::setItemBrush(const QColor &color, const Qt::BrushStyle &brushStyle)
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

void DiagramScene::mouseDoubleClickEvent(QGraphicsSceneMouseEvent *mouseEvent)
{
    if (currentMode == InsertPolyline) {
        polyline = nullptr;
        polylinePoint.clear();
    }

    QGraphicsScene::mouseDoubleClickEvent(mouseEvent);
}

void DiagramScene::mousePressEvent(QGraphicsSceneMouseEvent *mouseEvent)
{
    if (mouseEvent->button() == Qt::LeftButton) {
        leftButtonPressed = true;

        switch (currentMode) {
        case InsertPolyline:
            polylinePoint.append(mouseEvent->scenePos());
            if (polyline == nullptr) {
                polyline = new Polyline(itemMenu);
                addItem(polyline);
            }
            break;
        case InsertRect:
            rectangle = new Rectangle(QRectF(mouseEvent->scenePos(), mouseEvent->scenePos()), itemMenu);
            addItem(rectangle);
            break;
        case InsertEllipse:
            ellipse = new Ellipse(QRectF(mouseEvent->scenePos(), mouseEvent->scenePos()), itemMenu);
            addItem(ellipse);
            break;
        case InsertCurve:
            startPoint = mouseEvent->scenePos();
            break;
        default:
            break;
        }
    }

    QGraphicsScene::mousePressEvent(mouseEvent);
}

void DiagramScene::mouseMoveEvent(QGraphicsSceneMouseEvent *mouseEvent)
{
    if (leftButtonPressed) {
        if ((currentMode == InsertRect) && (rectangle != nullptr)) {
            qreal dx = mouseEvent->scenePos().x() - rectangle->rect().left();
            qreal dy = mouseEvent->scenePos().y() - rectangle->rect().top();
            rectangle->setRect( ( dx > 0 ) ? rectangle->rect().left() : mouseEvent->scenePos().x(),
                           ( dy > 0 ) ? rectangle->rect().top() : mouseEvent->scenePos().y(),
                           qAbs( dx ), qAbs( dy ) );
            rectangle->setPen(itemPen);
            rectangle->setBrush(itemBrush);
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
            curve = addLine(startPoint.x(), startPoint.y(),
                            mouseEvent->scenePos().x(), mouseEvent->scenePos().y());
            startPoint = mouseEvent->scenePos();
            curve->setPen(itemPen);
        }
    }
    if ((currentMode == InsertPolyline) && (polyline != nullptr)) {
        QPainterPath newPath;
        newPath.moveTo(polylinePoint.at(0));
        for (int i = 1; i < polylinePoint.count(); i++) {
            newPath.lineTo(polylinePoint.at(i));
        }
        newPath.lineTo(mouseEvent->scenePos());
        polyline->setPath(newPath);
        polyline->setPen(itemPen);
//        addItem(polyline);
    }

    QGraphicsScene::mouseMoveEvent(mouseEvent);
}

void DiagramScene::mouseReleaseEvent(QGraphicsSceneMouseEvent *mouseEvent)
{
    switch (currentMode) {
    case InsertPolyline:
        break;
    case InsertRect:
        rectangle = nullptr;
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
