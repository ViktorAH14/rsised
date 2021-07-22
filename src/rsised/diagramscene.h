#ifndef DIAGRAMSCENE_H
#define DIAGRAMSCENE_H

#include <QGraphicsScene>

class Rectangle;

QT_BEGIN_NAMESPACE
class QGraphicsLineItem;
class QGraphicsEllipseItem;
class QGraphicsSceneMouseEvent;
QT_END_NAMESPACE

class DiagramScene : public QGraphicsScene
{
    Q_OBJECT

public:
    enum Mode{InsertLine, InsertRect, InsertEllipse, InsertCurve, MoveItem};

    explicit DiagramScene(QObject *parent = nullptr);

public slots:
    void setMode(Mode mode);

protected:
    void mousePressEvent(QGraphicsSceneMouseEvent *mouseEvent) override;
    void mouseMoveEvent(QGraphicsSceneMouseEvent *mouseEvent) override;
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *mouseEvent) override;

private:
    Rectangle *rect;

    QGraphicsLineItem *line;
    QGraphicsEllipseItem *ellipse;
    QPointF previousPoint;
//    QPointF endPoint;

    Mode m_mode;
};

#endif // DIAGRAMSCENE_H
