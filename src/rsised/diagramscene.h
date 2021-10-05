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
class QMenu;
QT_END_NAMESPACE

class DiagramScene : public QGraphicsScene
{
    Q_OBJECT

public:
    enum Mode {InsertLine, InsertRect, InsertEllipse, InsertCurve, MoveItem};

    explicit DiagramScene(QMenu *editMenu, QObject *parent = nullptr);

    void setItemPen(const QColor &color, qreal width, Qt::PenStyle penStyle);
    void setItemBrush(const QColor &color, Qt::BrushStyle brushStyle);
    bool isChanged();


public slots:
    void setMode(DiagramScene::Mode mode);
    void setSelectableItems(bool selectable);
    void setSceneChanged(bool changed);

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
    bool sceneChanged;
    QPointF previousPoint;
    QPen itemPen;
    QBrush itemBrush;
    Mode currentMode;
    QMenu *itemMenu;
};

#endif // DIAGRAMSCENE_H
