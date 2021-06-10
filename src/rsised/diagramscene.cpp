#include "diagramscene.h"

#include <QGraphicsSceneEvent>
#include <QGraphicsLineItem>

DiagramScene::DiagramScene(QObject *parent) : QGraphicsScene(parent)
{

}

void DiagramScene::mousePressEvent(QGraphicsSceneMouseEvent *mouseEvent)
{
    line = new QGraphicsLineItem(QLineF(mouseEvent->scenePos(), mouseEvent->scenePos()));
    line->setPen(QPen(Qt::black));
    addItem(line);
}

void DiagramScene::mouseMoveEvent(QGraphicsSceneMouseEvent *mouseEvent)
{
    if (line != nullptr) {
        QLineF newLine(line->line().p1(), mouseEvent->scenePos());
        line->setLine(newLine);
    }
}
