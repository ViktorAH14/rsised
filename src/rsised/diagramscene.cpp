#include "diagramscene.h"

#include <QGraphicsSceneEvent>
#include <QGraphicsLineItem>
#include <QGraphicsRectItem>
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
            rect = new QGraphicsRectItem(QRectF(mouseEvent->scenePos(), mouseEvent->scenePos()));
            rect->setPen(QPen(Qt::red));
            rect->setBrush(QBrush(Qt::blue));
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
        QRectF newRect(rect->rect().topLeft(), mouseEvent->scenePos());
        rect->setRect(newRect);
        rect->setFlag(QGraphicsItem::ItemIsSelectable, true);
        rect->setFlag(QGraphicsItem::ItemIsMovable, true);
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
