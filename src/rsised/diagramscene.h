/*
 * Copyright (c) 2022 by Viktor Ermolov <ermolovva@gmail.com>.
 *
 * This file is part of the RSiSed project, a editor of the alignment of forces
 * and means in extinguishing a fire. (RSiSed)
 *
 * RSiSed is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * RSiSed is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <https://www.gnu.org/licenses/>.
 */

#ifndef DIAGRAMSCENE_H
#define DIAGRAMSCENE_H

#include "../include/technicsshape.h"
#include "../include/deviceshape.h"
#include "../include/buildingstruct.h"

#include <QGraphicsScene>
#include <QObject>

class RectShape;
class EllipseShape;
class PolylineShape;
class Curve;
class TextShape;
class PixmapShape;

QT_BEGIN_NAMESPACE
class QMenu;
QT_END_NAMESPACE

class DiagramScene : public QGraphicsScene
{
    Q_OBJECT

public:
    enum SceneMode {InsertPolyline
                    , InsertRectShape
                    , InsertEllipse
                    , InsertPie
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
    void clearPie();

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
    RectShape   *m_rectShape;
    PolylineShape    *polyline;
    EllipseShape     *m_ellipseShape;
    QGraphicsPathItem *tempPath;
    Curve       *curve;
    TextShape    *textItem;
    PixmapShape  *pixmapItem;
    QMenu       *m_itemMenu;
    SceneMode   m_sceneMode;
    QPen        itemPen;
    QBrush      itemBrush;
    QFont       itemFont;
    QColor      fontColor;
    QList<QPointF>  pathPoint;
//    QPointF     startPoint; // NOTE Without this variable, a segmentation fault occurs???
    bool        leftButtonPressed;
    bool        sceneChanged;
};

#endif // DIAGRAMSCENE_H
