#ifndef DIAGRAMSCENE_H
#define DIAGRAMSCENE_H

#include <QGraphicsScene>
#include <QObject>

class Rectangle;
class Ellipse;

QT_BEGIN_NAMESPACE
class QGraphicsLineItem;
class QGraphicsEllipseItem;
class QGraphicsSceneMouseEvent;
QT_END_NAMESPACE

class DiagramScene : public QGraphicsScene
{
    Q_OBJECT

public:
    enum Mode {InsertLine, InsertRect, InsertEllipse, InsertCurve, MoveItem};

    explicit DiagramScene(QObject *parent = nullptr);

    void setItemPen(const QColor &color, qreal width, Qt::PenStyle penStyle);
    void setItemBrush(const QColor &color, Qt::BrushStyle brushStyle);

public slots:
    void setMode(Mode mode);
    void setSelectableItems(bool selectable);

protected:
    void mousePressEvent(QGraphicsSceneMouseEvent *mouseEvent) override;
    void mouseMoveEvent(QGraphicsSceneMouseEvent *mouseEvent) override;
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *mouseEvent) override;

private:
    bool isItemChange(int type) const;

    Rectangle *rect;
    QGraphicsLineItem *line;
    Ellipse *ellipse;
    QGraphicsLineItem *curve;

    bool leftButtonPressed;
    QPointF previousPoint;
    QPen *itemPen;
    QBrush *itemBrush;
    Mode currentMode;
};

#endif // DIAGRAMSCENE_H
