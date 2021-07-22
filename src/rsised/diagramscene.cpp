#include "diagramscene.h"
#include "rectangle.h"

#include <QGraphicsSceneEvent>
#include <QGraphicsLineItem>
#include <QGraphicsEllipseItem>

DiagramScene::DiagramScene(QObject *parent) : QGraphicsScene(parent)
{

}

void DiagramScene::setMode(Mode mode)
{
    m_mode = mode;
}

void DiagramScene::mousePressEvent(QGraphicsSceneMouseEvent *mouseEvent)
{
    if (mouseEvent->button() == Qt::LeftButton) {
        switch (m_mode) {
        case InsertLine:
            line = new QGraphicsLineItem(QLineF(mouseEvent->scenePos(), mouseEvent->scenePos()));
            line->setPen(QPen(Qt::green));
            addItem(line);
            break;
        case InsertRect:
            previousPoint = mouseEvent->scenePos();
            rect = new Rectangle();
            addItem(rect);
//            rect->setPos(previousPoint);
            break;
        case InsertEllipse:
            ellipse = new QGraphicsEllipseItem(QRectF(mouseEvent->scenePos(), mouseEvent->scenePos()));
            ellipse->setPen(QPen(Qt::yellow));
            ellipse->setBrush(QBrush(Qt::magenta));
            addItem(ellipse);
            break;
        case InsertCurve:
            previousPoint = mouseEvent->scenePos();
        default:
            ;
        }
    }
    QGraphicsScene::mousePressEvent(mouseEvent);
}

void DiagramScene::mouseMoveEvent(QGraphicsSceneMouseEvent *mouseEvent)
{

    if (m_mode == InsertLine && line != nullptr) {
        QLineF newLine(line->line().p1(), mouseEvent->scenePos());
        line->setLine(newLine);
        line->setFlag(QGraphicsItem::ItemIsSelectable, true);
        line->setFlag(QGraphicsItem::ItemIsMovable, true);
    }

    if (m_mode == InsertRect && rect != nullptr) {
        qreal dx = mouseEvent->scenePos().x() - previousPoint.x();
        qreal dy = mouseEvent->scenePos().y() - previousPoint.y();
        rect->setRect( ( dx > 0 ) ? previousPoint.x() : mouseEvent->scenePos().x(),
                            ( dy > 0 ) ? previousPoint.y() : mouseEvent->scenePos().y(),
                            qAbs( dx ), qAbs( dy ) );

//        rect->setFlag(QGraphicsItem::ItemIsSelectable, true);
//        rect->setFlag(QGraphicsItem::ItemIsMovable, true);
    }

    if (m_mode == InsertEllipse && ellipse != nullptr) {
        QRectF newRect(ellipse->rect().topLeft(), mouseEvent->scenePos());
        ellipse->setRect(newRect);
        ellipse->setFlag(QGraphicsItem::ItemIsSelectable, true);
        ellipse->setFlag(QGraphicsItem::ItemIsMovable, true);
    }

    if (m_mode == InsertCurve) {
        line = addLine(previousPoint.x(), previousPoint.y(), mouseEvent->scenePos().x(), mouseEvent->scenePos().y());
        previousPoint = mouseEvent->scenePos();
        line->setFlag(QGraphicsItem::ItemIsSelectable, true);
        line->setFlag(QGraphicsItem::ItemIsMovable, true);
    }
    update();

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
    default:
        ;
    }

    QGraphicsScene::mouseReleaseEvent(mouseEvent);
}
