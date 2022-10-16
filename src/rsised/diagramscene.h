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
#include "../include/buildingshape.h"

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
                    , InsertBuildingShape
                    , SelectItem };

    explicit DiagramScene(QMenu *itemMenu, QObject *parent = nullptr);

    bool isChanged();
    void setItemPen(const QColor &color, const qreal width, const Qt::PenStyle &penStyle);
    void setItemBrush(const QColor &color, const Qt::BrushStyle &brushStyle);
    void setWallPen(const QColor &color, const int width);
    void setWallHatching(const QColor &color, const Qt::BrushStyle &brushStyle);
    void setWallHeight(const qreal &height);
    void setItemFont(const QFont &font , const QColor &textColor);
    void setSelectableItems(bool selectable);
    void setTechnicsShapeType(TechnicsShape::ShapeType type);
    void setDeviceShapeType(DeviceShape::ShapeType type);
    void setBuildingShapeType(BuildingShape::ShapeType type);
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
    TechnicsShape *m_technicsShape;

    DeviceShape::ShapeType m_deviceShapeType;
    DeviceShape *m_deviceShape;

    BuildingShape::ShapeType m_buildingShapeType;
    BuildingShape *m_buildingShape;

    RectShape   *m_rectShape;
    PolylineShape    *m_polyline;
    EllipseShape     *m_ellipseShape;
    QGraphicsPathItem *m_tempPath;
    Curve       *m_curve;
    TextShape    *m_textItem;
    PixmapShape  *m_pixmapItem;
    QMenu       *m_shapeMenu;
    SceneMode   m_sceneMode;
    QPen        m_shapePen;
    QBrush      m_shapeBrush;
    qreal       m_wallHeight;
    QPen        m_wallPen;
    QBrush      m_wallBrush;
    QFont       m_shapeFont;
    QColor      m_fontColor;
    QList<QPointF>  m_pathPointList;
    bool        leftButtonPressed;
    bool        sceneChanged;
};

#endif // DIAGRAMSCENE_H
