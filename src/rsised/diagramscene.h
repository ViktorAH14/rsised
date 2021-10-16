#ifndef DIAGRAMSCENE_H
#define DIAGRAMSCENE_H

#include <QGraphicsScene>
#include <QObject>

class Rectangle;
class Ellipse;
class Polyline;

QT_BEGIN_NAMESPACE
class QMenu;
QT_END_NAMESPACE

class DiagramScene : public QGraphicsScene
{
    Q_OBJECT

public:
    enum Mode {InsertPolyline, InsertRect, InsertEllipse, InsertCurve, SelectItem};

    explicit DiagramScene(QMenu *editMenu, QObject *parent = nullptr);

    void setItemPen(const QColor &color, const qreal width, const Qt::PenStyle &penStyle);
    void setItemBrush(const QColor &color, const Qt::BrushStyle &brushStyle);
    bool isChanged();


public slots:
    void setMode(Mode mode);
    void setSelectableItems(bool selectable);
    void setSceneChanged(bool changed);

protected:
    void mouseDoubleClickEvent(QGraphicsSceneMouseEvent *mouseEvent) override;
    void mousePressEvent(QGraphicsSceneMouseEvent *mouseEvent) override;
    void mouseMoveEvent(QGraphicsSceneMouseEvent *mouseEvent) override;
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *mouseEvent) override;

private:
    Rectangle   *rectangle;
    Polyline    *polyline;
    Ellipse     *ellipse;
    QGraphicsLineItem *curve;
    QMenu       *itemMenu;
    Mode        currentMode; // Initialized in mainwindow.cpp
    QPointF     startPoint;
    QPen        itemPen; // Initialized in mainwindow.cpp
    QBrush      itemBrush; // Initialized in mainwindow.cpp
    QList<QPointF>  polylinePoint;
    bool        leftButtonPressed;
    bool        sceneChanged;
};

#endif // DIAGRAMSCENE_H
