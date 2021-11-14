#include "diagramscene.h"
#include "rectangle.h"
#include "ellipse.h"
#include "polyline.h"
#include "curve.h"
#include "textitem.h"
#include "pixmapitem.h"

#include <QGraphicsSceneMouseEvent>
#include <QMenu>
#include <QGraphicsPixmapItem>

DiagramScene::DiagramScene(QMenu *itemMenu, QObject *parent)
    : QGraphicsScene(parent)
    , rectangle{nullptr}
    , polyline{nullptr}
    , ellipse{nullptr}
    , curve{nullptr}
    , textItem{nullptr}
    , pixmapItem{nullptr}
    , m_itemMenu{itemMenu}
    , currentMode{SelectItem}
    , leftButtonPressed{false}
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
            if (Curve *curveItem = qgraphicsitem_cast<Curve *>(item)) {
                curveItem->setPen(itemPen);
            }
        }
    }
}

void DiagramScene::setItemBrush(const QColor &color, const Qt::BrushStyle &brushStyle)
{
    itemBrush.setColor(color);
    itemBrush.setStyle(brushStyle);

    if (!selectedItems().isEmpty()) {
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

void DiagramScene::setItemFont(const QFont &font, const QColor &textColor)
{
    itemFont = font;
    fontColor = textColor;

    if (!selectedItems().isEmpty()) {
        QList<QGraphicsItem *> selectedItems = this->selectedItems();
        for (QGraphicsItem *item : qAsConst(selectedItems)) {
            if (TextItem *textItem = qgraphicsitem_cast<TextItem *>(item)) {
                textItem->setFont(itemFont);
                textItem->setDefaultTextColor(fontColor);
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

void DiagramScene::insertPixmap(const QString &imageFile)
{
    pixmapItem = new PixmapItem();
    QPixmap image(imageFile);
    pixmapItem->setPixmap(image);
    addItem(pixmapItem);
}

void DiagramScene::mouseDoubleClickEvent(QGraphicsSceneMouseEvent *mouseEvent)
{
    if (currentMode == InsertPolyline) {
        polyline = nullptr;
        pathPoint.clear();
    }
    if (currentMode == InsertCurve) {
        curve = nullptr;
        pathPoint.clear();
    }

    QGraphicsScene::mouseDoubleClickEvent(mouseEvent);
}

void DiagramScene::mousePressEvent(QGraphicsSceneMouseEvent *mouseEvent)
{
    if (mouseEvent->button() == Qt::LeftButton) {
        leftButtonPressed = true;

        switch (currentMode) {
        case InsertPolyline:
            pathPoint.append(mouseEvent->scenePos());
            if (polyline == nullptr) {
                polyline = new Polyline(m_itemMenu);
                addItem(polyline);
            }
            break;
        case InsertRect:
            rectangle = new Rectangle(QRectF(mouseEvent->scenePos(), mouseEvent->scenePos())
                                      , m_itemMenu);
            addItem(rectangle);
            break;
        case InsertEllipse:
            ellipse = new Ellipse(QRectF(mouseEvent->scenePos(), mouseEvent->scenePos())
                                  , m_itemMenu);
            addItem(ellipse);
            break;
        case InsertCurve:
            pathPoint.append(mouseEvent->scenePos());
            if (curve == nullptr) {
                curve = new Curve(m_itemMenu);
                addItem(curve);
            }
            break;
        case InserText:
            textItem = new TextItem(m_itemMenu);
            textItem->setTextInteractionFlags(Qt::TextEditorInteraction);
            textItem->setPos(mouseEvent->scenePos());
            textItem->setFont(itemFont);
            textItem->setDefaultTextColor(fontColor);
            textItem->setZValue(1000.0);
            addItem(textItem);
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

    }
    if (currentMode == InsertCurve && (curve != nullptr)) {
        QPainterPath newPath;
        newPath.moveTo(pathPoint.at(0));
        for (int i = 2; i < pathPoint.count(); i += 2) {
            newPath.quadTo(pathPoint.at(i - 1), pathPoint.at(i));
        }
        newPath.quadTo(pathPoint.back(), mouseEvent->scenePos());
        curve->setPath(newPath);
        curve->setPen(itemPen);
    }
    if ((currentMode == InsertPolyline) && (polyline != nullptr)) {
        QPainterPath newPath;
        newPath.moveTo(pathPoint.at(0));
        for (int i = 1; i < pathPoint.count(); i++) {
            newPath.lineTo(pathPoint.at(i));
        }
        newPath.lineTo(mouseEvent->scenePos());
        polyline->setPath(newPath);
        polyline->setPen(itemPen);
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
