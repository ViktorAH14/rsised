#ifndef DIAGRAMSCENE_H
#define DIAGRAMSCENE_H

#include "technics_shape.h"
#include "device_shape.h"
#include "buildingstruct.h"

#include <QGraphicsScene>
#include <QObject>

class Rectangle;
class Ellipse;
class Polyline;
class Curve;
class TextItem;
class PixmapItem;

QT_BEGIN_NAMESPACE
class QMenu;
QT_END_NAMESPACE

class DiagramScene : public QGraphicsScene
{
    Q_OBJECT

public:
    enum SceneMode {InsertPolyline
                    , InsertRect
                    , InsertEllipse
                    , InsertCurve
                    , InserText
                    , InsertImage
                    , InsertTechnicsShape
                    , InsertDeviceShape
                    , InsertBuildingStruct
                    , SelectItem };

    explicit DiagramScene(QMenu *itemMenu, QObject *parent = nullptr);

    bool isChanged();
    void setItemPen(const QColor &color, const qreal width, const Qt::PenStyle &penStyle);
    void setItemBrush(const QColor &color, const Qt::BrushStyle &brushStyle);
    void setItemFont(const QFont &font , const QColor &textColor);
    void setSelectableItems(bool selectable);
    void setTechnicsShapeType(TechnicsShape::ShapeType type);
    void setDeviceShapeType(DeviceShape::ShapeType type);
    void setBuildingStructShapeType(BuildingStruct::ShapeType type);

public slots:
    void setMode(DiagramScene::SceneMode mode);
    void setSceneChanged(bool changed);
    void insertPixmap(const QString &imageFile);

protected:
    void mouseDoubleClickEvent(QGraphicsSceneMouseEvent *mouseEvent) override;
    void mousePressEvent(QGraphicsSceneMouseEvent *mouseEvent) override;
    void mouseMoveEvent(QGraphicsSceneMouseEvent *mouseEvent) override;
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *mouseEvent) override;

private:
    TechnicsShape::ShapeType m_technicsShapeType;
    TechnicsShape *technicsShape;
    DeviceShape::ShapeType m_deviceShapeType;
    DeviceShape *deviceShape;
    BuildingStruct::ShapeType m_buildingStructType;
    BuildingStruct *buildingStructItem;
    Rectangle   *rectangle;
    Polyline    *polyline;
    Ellipse     *ellipse;
    Curve       *curve;
    TextItem    *textItem;
    PixmapItem  *pixmapItem;
    QMenu       *m_itemMenu;
    SceneMode   m_sceneMode;
    QPen        itemPen;
    QBrush      itemBrush;
    QFont       itemFont;
    QColor      fontColor;
    QList<QPointF>  pathPoint;
    QPointF     startPoint; // NOTE Without this variable, a segmentation fault occurs???
    bool        leftButtonPressed;
    bool        sceneChanged;
};

#endif // DIAGRAMSCENE_H
