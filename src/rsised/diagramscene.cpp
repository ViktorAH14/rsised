#include "diagramscene.h"
#include "rectangle.h"

#include <QGraphicsSceneMouseEvent>
#include <QGraphicsLineItem>
#include <QGraphicsEllipseItem>

DiagramScene::DiagramScene(QObject *parent)
    : QGraphicsScene(parent), leftButton {false}, m_mode {MoveItem}
{
}

void DiagramScene::setMode(Mode mode)
{
    m_mode = mode;
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

void DiagramScene::mousePressEvent(QGraphicsSceneMouseEvent *mouseEvent)
{
    if (mouseEvent->button() != Qt::LeftButton) {
        return;
    }

    leftButton = true;

    switch (m_mode) {
    case InsertLine:
        line = new QGraphicsLineItem(QLineF(mouseEvent->scenePos(), mouseEvent->scenePos()));
        line->setPen(QPen(Qt::green));
        addItem(line);
        break;
    case InsertRect:
        rect = new Rectangle(QRectF(mouseEvent->scenePos(), mouseEvent->scenePos()));
        addItem(rect);
        break;
    case InsertEllipse:
        ellipse = new QGraphicsEllipseItem(QRectF(mouseEvent->scenePos(), mouseEvent->scenePos()));
        ellipse->setPen(QPen(Qt::yellow));
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

        if ((m_mode == InsertLine) && (line != nullptr)) {
            QLineF newLine(line->line().p1(), mouseEvent->scenePos());
            line->setLine(newLine);
            line->setFlag(QGraphicsItem::ItemIsMovable, true);
        }

        if ((m_mode == InsertRect) && (rect != nullptr)) {
            qreal dx = mouseEvent->scenePos().x() - rect->rect().left();
            qreal dy = mouseEvent->scenePos().y() - rect->rect().top();
            rect->setRect( ( dx > 0 ) ? rect->rect().left() : mouseEvent->scenePos().x(),
                           ( dy > 0 ) ? rect->rect().top() : mouseEvent->scenePos().y(),
                           qAbs( dx ), qAbs( dy ) );
        }

        if ((m_mode == InsertEllipse) && (ellipse != nullptr)) {
            qreal dx = mouseEvent->scenePos().x() - ellipse->rect().left();
            qreal dy = mouseEvent->scenePos().y() - ellipse->rect().top();
            ellipse->setRect( ( dx > 0 ) ? ellipse->rect().left() : mouseEvent->scenePos().x(),
                              ( dy > 0 ) ? ellipse->rect().top() : mouseEvent->scenePos().y(),
                              qAbs( dx ), qAbs( dy ) );
            ellipse->setFlag(QGraphicsItem::ItemIsMovable, true);
        }

        if (m_mode == InsertCurve) {
            curve = addLine(previousPoint.x(), previousPoint.y(),
                            mouseEvent->scenePos().x(), mouseEvent->scenePos().y());
            previousPoint = mouseEvent->scenePos();
        }
    }

    QGraphicsScene::mouseMoveEvent(mouseEvent);
}

void DiagramScene::mouseReleaseEvent(QGraphicsSceneMouseEvent *mouseEvent)
{
    switch (m_mode) {
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