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

#include <QGraphicsSceneMouseEvent>
#include <QMenu>
#include <QGraphicsPixmapItem>

DiagramScene::DiagramScene(QMenu *itemMenu, QObject *parent)
    : QGraphicsScene(parent)
    , m_rectShape{nullptr}
    , polyline{nullptr}
    , ellipse{nullptr}
    , curve{nullptr}
    , textItem{nullptr}
    , pixmapItem{nullptr}
    , m_itemMenu{itemMenu}
    , m_sceneMode{SelectItem}
    , leftButtonPressed{false}
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
    itemPen.setColor(color);
    itemPen.setWidth(width);
    itemPen.setStyle(penStyle);

    if (!selectedItems().isEmpty()){
        QList<QGraphicsItem *> selectedItems = this->selectedItems();
        for (QGraphicsItem *item : qAsConst(selectedItems)) {
            if (QGraphicsLineItem *lineItem = qgraphicsitem_cast<QGraphicsLineItem *>(item)) {
                lineItem->setPen(itemPen);
            }
            if (RectShape *rectshape = qgraphicsitem_cast<RectShape *>(item)) {
                rectshape->setPen(itemPen);
            }
            if (EllipseShape *ellipseShape = qgraphicsitem_cast<EllipseShape *>(item)) {
                ellipseShape->setPen(itemPen);
            }
            if (PolylineShape *polylineShape = qgraphicsitem_cast<PolylineShape *>(item)) {
                polylineShape->setPen(itemPen);
            }
            if (Curve *curveShape = qgraphicsitem_cast<Curve *>(item)) {
                curveShape->setPen(itemPen);
            }
        }
    }
}

void DiagramScene::setItemBrush(const QColor &color, const Qt::BrushStyle &brushStyle)
{
    itemBrush.setColor(color);
    itemBrush.setStyle(brushStyle);

    if (!selectedItems().isEmpty()) {
        QList<QGraphicsItem *> selectedItems = this->selectedItems();
        for (QGraphicsItem *item : qAsConst(selectedItems)) {
            if (RectShape *rectShape = qgraphicsitem_cast<RectShape *>(item)) {
                rectShape->setBrush(itemBrush);
            }
            if (EllipseShape *ellipseShape = qgraphicsitem_cast<EllipseShape *>(item)) {
                ellipseShape->setBrush(itemBrush);
            }
        }
    }
}

void DiagramScene::setItemFont(const QFont &font, const QColor &textColor)
{
    itemFont = font;
    fontColor = textColor;

    if (!selectedItems().isEmpty()) {
        QList<QGraphicsItem *> selectedItems = this->selectedItems();
        for (QGraphicsItem *item : qAsConst(selectedItems)) {
            if (TextShape *textShape = qgraphicsitem_cast<TextShape *>(item)) {
                textShape->setFont(itemFont);
                textShape->setDefaultTextColor(fontColor);
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

void DiagramScene::setBuildingStructShapeType(BuildingStruct::ShapeType type)
{
    m_buildingStructType = type;
}

void DiagramScene::insertPixmap(const QString &imageFile)
{
    pixmapItem = new PixmapShape();
    QPixmap image(imageFile);
    pixmapItem->setPixmap(image);
    pixmapItem->setZValue(-1000.0);
    addItem(pixmapItem);
}

void DiagramScene::mouseDoubleClickEvent(QGraphicsSceneMouseEvent *mouseEvent)
{
    if (m_sceneMode == InsertPolyline) {
        polyline = nullptr;
        pathPoint.clear();
    }
    if (m_sceneMode == InsertCurve) {
        curve = nullptr;
        pathPoint.clear();
    }

    QGraphicsScene::mouseDoubleClickEvent(mouseEvent);
}

void DiagramScene::mousePressEvent(QGraphicsSceneMouseEvent *mouseEvent)
{
    if (mouseEvent->button() == Qt::LeftButton) {
        leftButtonPressed = true;

        switch (m_sceneMode) {
        case InsertPolyline:
            pathPoint.append(mouseEvent->scenePos());
            if (polyline == nullptr) {
                polyline = new PolylineShape(m_itemMenu);
                addItem(polyline);
            }
            break;
        case InsertRectShape:
            m_rectShape = new RectShape(QRectF(mouseEvent->scenePos(), mouseEvent->scenePos()));
            m_rectShape->setMenu(m_itemMenu);
            addItem(m_rectShape);
            break;
        case InsertEllipse:
            ellipse = new EllipseShape(QRectF(mouseEvent->scenePos(), mouseEvent->scenePos())
                                  , m_itemMenu);
            addItem(ellipse);
            break;
        case InsertCurve:
            pathPoint.append(mouseEvent->scenePos());
            if (curve == nullptr) {
                curve = new Curve(m_itemMenu);
                addItem(curve);
            }
            break;
        case InserText: // TODO добавить editorLostFocus(TextItem *textItem); утечка памяти???
            textItem = new TextShape(m_itemMenu);
            textItem->setTextInteractionFlags(Qt::TextEditorInteraction);
            textItem->setPos(mouseEvent->scenePos());
            textItem->setFont(itemFont);
            textItem->setDefaultTextColor(fontColor);
            textItem->setZValue(1000.0);
            addItem(textItem);
            break;
        case InsertTechnicsShape:
            technicsShape = new TechnicsShape(m_technicsShapeType);
            technicsShape->setMenu(m_itemMenu);
            technicsShape->setPos(mouseEvent->scenePos());
            addItem(technicsShape);
            break;
        case InsertDeviceShape:
            deviceShape = new DeviceShape(m_deviceShapeType);
            deviceShape->setMenu(m_itemMenu);
            deviceShape->setPos(mouseEvent->scenePos());
            addItem(deviceShape);
            break;
        case InsertBuildingStruct:
            buildingStructItem = new BuildingStruct(m_buildingStructType);
            buildingStructItem->setMenu(m_itemMenu);
            buildingStructItem->setPos(mouseEvent->scenePos());
            if (m_buildingStructType == BuildingStruct::Wall) {
                buildingStructItem->setZValue(900.0);
            } else {
                buildingStructItem->setZValue(950.0);
            }
            addItem(buildingStructItem);
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
            m_rectShape->setPen(itemPen);
            m_rectShape->setBrush(itemBrush);
        }
        if ((m_sceneMode == InsertEllipse) && (ellipse != nullptr)) {
            qreal dx = mouseEvent->scenePos().x() - ellipse->rect().left();
            qreal dy = mouseEvent->scenePos().y() - ellipse->rect().top();
            ellipse->setRect( ( dx > 0 ) ? ellipse->rect().left() : mouseEvent->scenePos().x(),
                              ( dy > 0 ) ? ellipse->rect().top() : mouseEvent->scenePos().y(),
                              qAbs( dx ), qAbs( dy ) );
            ellipse->setPen(itemPen);
            ellipse->setBrush(itemBrush);
        }

    }
    if (m_sceneMode == InsertCurve && (curve != nullptr)) {
        QPainterPath newPath;
        newPath.moveTo(pathPoint.at(0));
        for (int i = 2; i < pathPoint.count(); i += 2) {
            newPath.quadTo(pathPoint.at(i - 1), pathPoint.at(i));
        }
        newPath.quadTo(pathPoint.back(), mouseEvent->scenePos());
        curve->setPath(newPath);
        curve->setPen(itemPen);
    }
    if ((m_sceneMode == InsertPolyline) && (polyline != nullptr)) {
        QPainterPath newPath;
        newPath.moveTo(pathPoint.at(0));
        for (int i = 1; i < pathPoint.count(); i++) {
            newPath.lineTo(pathPoint.at(i));
        }
        newPath.lineTo(mouseEvent->scenePos());
        polyline->setPath(newPath);
        polyline->setPen(itemPen);
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
        ellipse = nullptr;
        break;
    case InsertCurve:
        break;
    case InsertTechnicsShape:
        technicsShape = nullptr;
        break;
    case InsertDeviceShape:
        deviceShape = nullptr;
        break;
    case InsertBuildingStruct:
        buildingStructItem = nullptr;
        break;
    default:
        break;
    }

    leftButtonPressed = false;
    setSceneChanged(true);

    QGraphicsScene::mouseReleaseEvent(mouseEvent);
}
