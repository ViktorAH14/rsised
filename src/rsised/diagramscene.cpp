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

#include "diagramscene.h"
#include "../include/rectshape.h"
#include "../include/ellipseshape.h"
#include "../include/polylineshape.h"
#include "../include/curve.h"
#include "../include/textshape.h"
#include "../include/pixmapshape.h"

#include <math.h>

#include <QGraphicsSceneMouseEvent>
#include <QMenu>
#include <QGraphicsPixmapItem>
//#include <QScopedPointer>

DiagramScene::DiagramScene(QMenu *itemMenu, QObject *parent)
    : QGraphicsScene(parent)
    , m_technicsShapeType{TechnicsShape::Base}
    , m_technicsShape{nullptr}
    , m_deviceShapeType{DeviceShape::Barrel_0}
    , m_deviceShape{nullptr}
    , m_buildingShapeType{BuildingShape::Wall}
    , m_buildingShape{nullptr}
    , m_rectShape{nullptr}
    , m_polyline{nullptr}
    , m_ellipseShape{nullptr}
    , m_tempPath{nullptr}
    , m_curve{nullptr}
    , m_textItem{nullptr}
    , m_pixmapItem{nullptr}
    , m_shapeMenu{itemMenu}
    , m_sceneMode{SelectItem}
    , m_shapePen{Qt::black, 1}
    , m_shapeBrush{Qt::white}
    , m_wallHeight{10}
    , m_wallPen{Qt::black, 1}
    , m_wallBrush{Qt::lightGray}
    , leftButtonPressed{false}
    , sceneChanged(false)
{
}

void DiagramScene::setMode(SceneMode mode)
{
    m_sceneMode = mode;
}

void DiagramScene::setSelectableItems(bool selectable)
{
    QList<QGraphicsItem *> items = this->items();
    if (selectable) {
        for (QGraphicsItem *item : qAsConst(items)) {
            item->setFlag(QGraphicsItem::ItemIsSelectable, true);
        }
    } else {
        for (QGraphicsItem *item : qAsConst(items)){
            item->setFlag(QGraphicsItem::ItemIsSelectable, false);
        }
    }
}

void DiagramScene::setItemPen(const QColor &color, const qreal width, const Qt::PenStyle &penStyle)
{
    m_shapePen.setColor(color);
    m_shapePen.setWidth(width);
    m_shapePen.setStyle(penStyle);

    if (!selectedItems().isEmpty()){
        QList<QGraphicsItem *> selectedShapeList = selectedItems();
        for (QGraphicsItem *item : qAsConst(selectedShapeList)) {
            if (QGraphicsLineItem *lineItem = qgraphicsitem_cast<QGraphicsLineItem *>(item)) {
                lineItem->setPen(m_shapePen);
            }
            if (RectShape *rectshape = qgraphicsitem_cast<RectShape *>(item)) {
                rectshape->setPen(m_shapePen);
            }
            if (EllipseShape *ellipseShape = qgraphicsitem_cast<EllipseShape *>(item)) {
                ellipseShape->setPen(m_shapePen);
            }
            if (PolylineShape *polylineShape = qgraphicsitem_cast<PolylineShape *>(item)) {
                polylineShape->setPen(m_shapePen);
            }
            if (Curve *curveShape = qgraphicsitem_cast<Curve *>(item)) {
                curveShape->setPen(m_shapePen);
            }
        }
    }
}

void DiagramScene::setItemBrush(const QColor &color, const Qt::BrushStyle &brushStyle)
{
    m_shapeBrush.setColor(color);
    m_shapeBrush.setStyle(brushStyle);

    if (!selectedItems().isEmpty()) {
        QList<QGraphicsItem *> selectedItems = this->selectedItems();
        for (QGraphicsItem *item : qAsConst(selectedItems)) {
            if (RectShape *rectShape = qgraphicsitem_cast<RectShape *>(item)) {
                rectShape->setBrush(m_shapeBrush);
            }
            if (EllipseShape *ellipseShape = qgraphicsitem_cast<EllipseShape *>(item)) {
                ellipseShape->setBrush(m_shapeBrush);
            }
        }
    }
}

void DiagramScene::setWallPen(const QColor &color, const int width)
{
    m_wallPen.setColor(color);
    m_wallPen.setWidth(width);
    if (!selectedItems().isEmpty()) {
        QList<QGraphicsItem *> selectedShapeList = selectedItems();
        for (QGraphicsItem *p_shape : qAsConst(selectedShapeList)) {
            if (WallShape *wallShape = qgraphicsitem_cast<WallShape *>(p_shape)) {
                wallShape->setPen(m_wallPen);
            }
        }
    }
}

void DiagramScene::setWallHatching(const QColor &color, const Qt::BrushStyle &brushStyle)
{
    m_wallBrush.setColor(color);
    m_wallBrush.setStyle(brushStyle);
    if (!selectedItems().isEmpty()) {
        QList<QGraphicsItem *> selectedShapeList = selectedItems();
        for (QGraphicsItem *p_shape : qAsConst(selectedShapeList)) {
            if (WallShape *wallShape = qgraphicsitem_cast<WallShape *>(p_shape)) {
                wallShape->setBrush(m_wallBrush);
            }
        }
    }
}

void DiagramScene::setWallHeight(const qreal &height)
{
    m_wallHeight = height;
    if (!selectedItems().isEmpty()) {
        QList<QGraphicsItem *> selectedShapeList = selectedItems();
        for (QGraphicsItem *p_shape : qAsConst(selectedShapeList)) {
            if (WallShape *wallShape = qgraphicsitem_cast<WallShape *>(p_shape)) {
                wallShape->setHeight(height);
            }
        }
    }
}

void DiagramScene::setItemFont(const QFont &font, const QColor &textColor)
{
    m_shapeFont = font;
    m_fontColor = textColor;

    if (!selectedItems().isEmpty()) {
        QList<QGraphicsItem *> selectedItems = this->selectedItems();
        for (QGraphicsItem *item : qAsConst(selectedItems)) {
            if (TextShape *textShape = qgraphicsitem_cast<TextShape *>(item)) {
                textShape->setFont(m_shapeFont);
                textShape->setDefaultTextColor(m_fontColor);
            }
        }
    }
}

bool DiagramScene::isChanged()
{
    return sceneChanged;
}

void DiagramScene::setSceneChanged(bool changed)
{
    if (changed) {
        sceneChanged = true;
        update();
    } else {
        sceneChanged = false;
    }
}

void DiagramScene::setTechnicsShapeType(TechnicsShape::ShapeType type)
{
    m_technicsShapeType = type;
}

void DiagramScene::setDeviceShapeType(DeviceShape::ShapeType type)
{
    m_deviceShapeType = type;
}

void DiagramScene::setBuildingShapeType(BuildingShape::ShapeType type)
{
    m_buildingShapeType = type;
}

void DiagramScene::clearPie()
{
    removeItem(m_tempPath);
    m_tempPath = nullptr;
    m_pathPointList.clear();
    m_ellipseShape = nullptr;
}

void DiagramScene::insertPixmap(const QString &imageFile)
{
    m_pixmapItem = new PixmapShape();
    QPixmap image(imageFile);
    m_pixmapItem->setPixmap(image);
    m_pixmapItem->setZValue(-1000.0);
    addItem(m_pixmapItem);
}

void DiagramScene::mouseDoubleClickEvent(QGraphicsSceneMouseEvent *mouseEvent)
{
    if (m_sceneMode == InsertPolyline) {
        m_polyline = nullptr;
        m_pathPointList.clear();
    }
    if (m_sceneMode == InsertCurve) {
        m_curve = nullptr;
        m_pathPointList.clear();
    }

    QGraphicsScene::mouseDoubleClickEvent(mouseEvent);
}

void DiagramScene::mousePressEvent(QGraphicsSceneMouseEvent *mouseEvent)
{
    if (mouseEvent->button() == Qt::LeftButton) {
        leftButtonPressed = true;
        switch (m_sceneMode) {
        case InsertPolyline:
            m_pathPointList.append(mouseEvent->scenePos());
            if (m_polyline == nullptr) {
                m_polyline = new PolylineShape(m_shapeMenu);
                addItem(m_polyline);
            }
            break;
        case InsertRectShape:
            m_rectShape = new RectShape(QRectF(mouseEvent->scenePos(), mouseEvent->scenePos()));
            m_rectShape->setMenu(m_shapeMenu);
            addItem(m_rectShape);
            break;
        case InsertEllipse:
            m_ellipseShape = new EllipseShape(QRectF(mouseEvent->scenePos()
                                                     , mouseEvent->scenePos()));
            m_ellipseShape->setMenu(m_shapeMenu);
            addItem(m_ellipseShape);
            break;
        case InsertPie:
            if (m_ellipseShape == nullptr) {
                m_ellipseShape = new EllipseShape(QRectF(mouseEvent->scenePos()
                                                         , mouseEvent->scenePos()));
                m_ellipseShape->setMenu(m_shapeMenu);
                m_ellipseShape->setPen(QPen(Qt::black, 0, Qt::DashLine));
                addItem(m_ellipseShape);
                m_tempPath = new QGraphicsPathItem();
                addItem(m_tempPath);
            }
            break;
        case InsertCurve:
            m_pathPointList.append(mouseEvent->scenePos());
            if (m_curve == nullptr) {
                m_curve = new Curve(m_shapeMenu);
                addItem(m_curve);
            }
            break;
        case InserText: // TODO добавить editorLostFocus(TextItem *textItem); утечка памяти???
            m_textItem = new TextShape(m_shapeMenu);
            m_textItem->setTextInteractionFlags(Qt::TextEditorInteraction);
            m_textItem->setPos(mouseEvent->scenePos());
            m_textItem->setFont(m_shapeFont);
            m_textItem->setDefaultTextColor(m_fontColor);
            m_textItem->setZValue(1000.0);
            addItem(m_textItem);
            break;
        case InsertTechnicsShape:
            m_technicsShape = new TechnicsShape(m_technicsShapeType);
            m_technicsShape->setMenu(m_shapeMenu);
            m_technicsShape->setPos(mouseEvent->scenePos());
            addItem(m_technicsShape);
            break;
        case InsertDeviceShape:
            m_deviceShape = new DeviceShape(m_deviceShapeType);
            m_deviceShape->setMenu(m_shapeMenu);
            m_deviceShape->setPos(mouseEvent->scenePos());
            addItem(m_deviceShape);
            break;
        case InsertBuildingShape:
            m_buildingShape = BuildingShape::createBuildingShape(m_buildingShapeType);

            m_buildingShape->setMenu(m_shapeMenu);
            m_buildingShape->setPos(mouseEvent->scenePos());
            if (m_buildingShapeType == BuildingShape::Wall) {
                m_buildingShape->setPen(m_wallPen);
                m_buildingShape->setBrush(m_wallBrush);
                m_buildingShape->setHeight(m_wallHeight);
                m_buildingShape->setZValue(900.0);
            } else {
                m_buildingShape->setZValue(950.0);
            }
            addItem(m_buildingShape);
            break;
        default:
            break;
        }
    }

        QGraphicsScene::mousePressEvent(mouseEvent);
}

void DiagramScene::mouseMoveEvent(QGraphicsSceneMouseEvent *mouseEvent)
{
    if (leftButtonPressed) {
        if ((m_sceneMode == InsertRectShape) && (m_rectShape != nullptr)) {
            qreal dx = mouseEvent->scenePos().x() - m_rectShape->rect().left();
            qreal dy = mouseEvent->scenePos().y() - m_rectShape->rect().top();
            m_rectShape->setRect(( dx > 0 ) ? m_rectShape->rect().left() : mouseEvent->scenePos().x(),
                           ( dy > 0 ) ? m_rectShape->rect().top() : mouseEvent->scenePos().y(),
                           qAbs( dx ), qAbs( dy ));
            m_rectShape->setPen(m_shapePen);
            m_rectShape->setBrush(m_shapeBrush);
        }
        if ((m_sceneMode == InsertEllipse) && (m_ellipseShape != nullptr)) {
            qreal dx = mouseEvent->scenePos().x() - m_ellipseShape->rect().x();
            qreal dy = mouseEvent->scenePos().y() - m_ellipseShape->rect().y();
            m_ellipseShape->setRect((dx > 0) ? m_ellipseShape->rect().x() : mouseEvent->scenePos().x(),
                              (dy > 0) ? m_ellipseShape->rect().y() : mouseEvent->scenePos().y(),
                              qAbs( dx ), qAbs( dy ) );

            m_ellipseShape->setPen(m_shapePen);
            m_ellipseShape->setBrush(m_shapeBrush);
        }
        if ((m_sceneMode == InsertPie) && (m_ellipseShape != nullptr)) {
                QPointF center = m_ellipseShape->rect().center();
                QLineF radiusLine(center, mouseEvent->scenePos());
                qreal radius = radiusLine.length();
                qreal centerX = center.x();
                qreal centerY = center.y();
                qreal x = centerX - radius;
                qreal y = centerY - radius;
                m_ellipseShape->setRect(x, y, radius * 2, radius * 2);

                QPainterPath tempPiePath;
                tempPiePath.moveTo(center);
                tempPiePath.lineTo(mouseEvent->scenePos());
                m_tempPath->setPath(tempPiePath);
        }
    } else {
        if ((m_sceneMode == InsertPie) && (m_ellipseShape != nullptr)) {
            QPainterPath tempPiePath;
            QPointF center = m_ellipseShape->rect().center();
            tempPiePath.moveTo(center);
            tempPiePath.lineTo(m_pathPointList.constFirst());
            QLineF startRadius(center, m_pathPointList.constFirst());
            QLineF spanRadius(center, mouseEvent->scenePos());
            qreal startAngle = startRadius.angle();
            qreal spanAngle = startRadius.angleTo(spanRadius);
            tempPiePath.arcTo(m_ellipseShape->rect(), startAngle, spanAngle);
            tempPiePath.lineTo(center);
            m_tempPath->setPath(tempPiePath);
            m_tempPath->setPen(QPen(Qt::black, 1));
            m_tempPath->setBrush(QBrush(Qt::lightGray));
        }
        if (m_sceneMode == InsertCurve && (m_curve != nullptr)) {
            QPainterPath newPath;
            newPath.moveTo(m_pathPointList.at(0));
            for (int i = 2; i < m_pathPointList.count(); i += 2) {
                newPath.quadTo(m_pathPointList.at(i - 1), m_pathPointList.at(i));
            }
            newPath.quadTo(m_pathPointList.back(), mouseEvent->scenePos());
            m_curve->setPath(newPath);
            m_curve->setPen(m_shapePen);
        }
        if ((m_sceneMode == InsertPolyline) && (m_polyline != nullptr)) {
            QPainterPath newPath;
            newPath.moveTo(m_pathPointList.at(0));
            for (int i = 1; i < m_pathPointList.count(); i++) {
                newPath.lineTo(m_pathPointList.at(i));
            }
            newPath.lineTo(mouseEvent->scenePos());
            m_polyline->setPath(newPath);
            m_polyline->setPen(m_shapePen);
        }
    }

    QGraphicsScene::mouseMoveEvent(mouseEvent);
}

void DiagramScene::mouseReleaseEvent(QGraphicsSceneMouseEvent *mouseEvent)
{
    switch (m_sceneMode) {
    case InsertPolyline:
        break;
    case InsertRectShape:
        m_rectShape = nullptr;
        break;
    case InsertEllipse:
        m_ellipseShape = nullptr;
        break;
    case InsertPie:
        if (m_ellipseShape != nullptr) {
            QPointF center = m_ellipseShape->rect().center();
            if (m_pathPointList.isEmpty()) {
                m_pathPointList.append(mouseEvent->scenePos());
                QLineF ellipseStartRadius(center, m_pathPointList.constFirst());
                qreal startAngle = ellipseStartRadius.angle();
                m_ellipseShape->setStartAngle(startAngle * 16);
            } else {
                m_pathPointList.append(mouseEvent->scenePos());
                QLineF ellipseStartRadius(center, m_pathPointList.constFirst());
                QLineF ellipseSpanRadius(center, m_pathPointList.constLast());
                qreal spanAngle = ellipseStartRadius.angleTo(ellipseSpanRadius);
                m_ellipseShape->setSpanAngle(spanAngle * 16);
                m_ellipseShape->setPen(m_shapePen);
                m_ellipseShape->setBrush(m_shapeBrush);
                clearPie();
            }
        }
        break;
    case InsertCurve:
        break;
    case InsertTechnicsShape:
        m_technicsShape = nullptr;
        break;
    case InsertDeviceShape:
        m_deviceShape = nullptr;
        break;
    case InsertBuildingShape:
        m_buildingShape = nullptr;
        break;
    default:
        break;
    }

    leftButtonPressed = false;
    setSceneChanged(true);

    QGraphicsScene::mouseReleaseEvent(mouseEvent);
}
