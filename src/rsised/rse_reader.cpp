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

#include "rse_reader.h"
#include "rectangle.h"
#include "ellipse.h"
#include "polyline.h"
#include "curve.h"
#include "textitem.h"
#include "pixmapitem.h"
#include "technics_shape.h"
#include "device_shape.h"
#include "buildingstruct.h"

#include <QXmlStreamReader>
#include <QPen>
#include <QFont>

RseReader::RseReader(QMenu *itemMenu) : m_itemMenu{itemMenu}
{
}

QRectF RseReader::getSceneRect(QIODevice *device) const
{
    QRectF sceneRect;
    QXmlStreamReader rseSceneReader;
    rseSceneReader.setDevice(device);
    rseSceneReader.readNext();
    while (!rseSceneReader.atEnd()) {
        if (rseSceneReader.isStartElement()) {
            if (rseSceneReader.name() == "Scene") {
                qreal x {0.0};
                qreal y {0.0};
                qreal width {0.0};
                qreal height {0.0};
                QXmlStreamAttributes attributes = rseSceneReader.attributes();
                for (const QXmlStreamAttribute &attr : qAsConst(attributes)) {
                    if (attr.name() == "x") {
                        x = attr.value().toFloat();
                    }
                    if (attr.name() == "y") {
                        y = attr.value().toFloat();
                    }
                    if (attr.name() == "width") {
                        width = attr.value().toFloat();
                    }
                    if (attr.name() == "height") {
                        height = attr.value().toFloat();
                    }
                }
                sceneRect.setRect(x, y, width, height);
            }
        }
        rseSceneReader.readNext();
    }
    if (sceneRect.isNull()) {
        sceneRect.setRect(0.0, 0.0, 1920.0, 1080.0);
        return sceneRect;
    } else {
        return sceneRect;
    }
}

//NOTE refactoring
QList<QGraphicsItem *> RseReader::getElement(QIODevice *device) const
{
    QList<QGraphicsItem *> itemList;
    QXmlStreamReader rseItemReader;
    rseItemReader.setDevice(device);
    rseItemReader.readNext();
    while (!rseItemReader.atEnd()) {
        if (rseItemReader.isStartElement()) {
            if (rseItemReader.name() == "rect") {
                Rectangle *rectangle = new Rectangle(m_itemMenu);
                qreal x {0.0};
                qreal y {0.0};
                qreal width {0.0};
                qreal height {0.0};
                qreal zValue {0.0};
                qreal m11 {0.0};
                qreal m12 {0.0};
                qreal m13 {0.0};
                qreal m21 {0.0};
                qreal m22 {0.0};
                qreal m23 {0.0};
                qreal m31 {0.0};
                qreal m32 {0.0};
                qreal m33 {0.0};
                QPen itemPen;
                QBrush itemBrush;
                QXmlStreamAttributes attributes = rseItemReader.attributes();
                for (const QXmlStreamAttribute &attr : qAsConst(attributes)) {
                    if (attr.name() == "x") {
                        x = attr.value().toFloat();
                    }
                    if (attr.name() == "y") {
                        y = attr.value().toFloat();
                    }
                    if (attr.name() == "width") {
                        width = attr.value().toFloat();
                    }
                    if (attr.name() == "height") {
                        height = attr.value().toFloat();
                    }
                    if (attr.name() == "pen-color") {
                        itemPen.setColor(attr.value().toString());
                    }
                    if (attr.name() == "pen-width") {
                        itemPen.setWidth(attr.value().toInt());
                    }
                    if (attr.name() == "pen-style") {
                        itemPen.setStyle(Qt::PenStyle(attr.value().toInt()));
                    }
                    if (attr.name() == "brush-color") {
                        itemBrush.setColor(attr.value().toString());
                    }
                    if (attr.name() == "brush-style") {
                        itemBrush.setStyle(Qt::BrushStyle(attr.value().toInt()));
                    }
                    if (attr.name() == "z") {
                        zValue = attr.value().toFloat();
                    }
                    if (attr.name() == "transform") {
                        QList<QStringRef> transList(attr.value().split(",").toList());
                        m11 = transList.at(0).toFloat();
                        m12 = transList.at(1).toFloat();
                        m13 = transList.at(2).toFloat();
                        m21 = transList.at(3).toFloat();
                        m22 = transList.at(4).toFloat();
                        m23 = transList.at(5).toFloat();
                        m31 = transList.at(6).toFloat();
                        m32 = transList.at(7).toFloat();
                        m33 = transList.at(8).toFloat();
                    }
                }
                rectangle->setRect(x, y, width, height);
                rectangle->setPen(itemPen);
                rectangle->setBrush(itemBrush);
                rectangle->setZValue(zValue);
                QTransform trans(m11, m12, m13, m21, m22, m23, m31, m32, m33);
                rectangle->setTransform(trans);

                itemList.append(rectangle);
            }
            if (rseItemReader.name() == "ellipse") {
                Ellipse *ellipse = new Ellipse(m_itemMenu);
                qreal x {0.0};
                qreal y {0.0};
                qreal width {0.0};
                qreal height {0.0};
                qreal zValue {0.0};
                qreal m11 {0.0};
                qreal m12 {0.0};
                qreal m13 {0.0};
                qreal m21 {0.0};
                qreal m22 {0.0};
                qreal m23 {0.0};
                qreal m31 {0.0};
                qreal m32 {0.0};
                qreal m33 {0.0};
                QPen itemPen;
                QBrush itemBrush;
                QXmlStreamAttributes attributes = rseItemReader.attributes();
                for (const QXmlStreamAttribute &attr : qAsConst(attributes)) {
                    if (attr.name() == "x") {
                        x = attr.value().toFloat();
                    }
                    if (attr.name() == "y") {
                        y = attr.value().toFloat();
                    }
                    if (attr.name() == "width") {
                        width = attr.value().toFloat();
                    }
                    if (attr.name() == "height") {
                        height = attr.value().toFloat();
                    }
                    if (attr.name() == "pen-color") {
                        itemPen.setColor(attr.value().toString());
                    }
                    if (attr.name() == "pen-width") {
                        itemPen.setWidth(attr.value().toInt());
                    }
                    if (attr.name() == "pen-style") {
                        itemPen.setStyle(Qt::PenStyle(attr.value().toInt()));
                    }
                    if (attr.name() == "brush-color") {
                        itemBrush.setColor(attr.value().toString());
                    }
                    if (attr.name() == "brush-style") {
                        itemBrush.setStyle(Qt::BrushStyle(attr.value().toInt()));
                    }
                    if (attr.name() == "z") {
                        zValue = attr.value().toFloat();
                    }
                    if (attr.name() == "transform") {
                        QList<QStringRef> transList(attr.value().split(",").toList());
                        m11 = transList.at(0).toFloat();
                        m12 = transList.at(1).toFloat();
                        m13 = transList.at(2).toFloat();
                        m21 = transList.at(3).toFloat();
                        m22 = transList.at(4).toFloat();
                        m23 = transList.at(5).toFloat();
                        m31 = transList.at(6).toFloat();
                        m32 = transList.at(7).toFloat();
                        m33 = transList.at(8).toFloat();
                    }
                }
                ellipse->setRect(x, y, width, height);
                ellipse->setPen(itemPen);
                ellipse->setBrush(itemBrush);
                ellipse->setZValue(zValue);
                QTransform trans(m11, m12, m13, m21, m22, m23, m31, m32, m33);
                ellipse->setTransform(trans);

                itemList.append(ellipse);
            }
            if (rseItemReader.name() == "line") {
                QGraphicsLineItem *line = new QGraphicsLineItem();
                line->setFlag(QGraphicsItem::ItemIsMovable, true);
                qreal x1 {0.0};
                qreal y1 {0.0};
                qreal x2 {0.0};
                qreal y2 {0.0};
                qreal zValue {0.0};
                qreal m11 {0.0};
                qreal m12 {0.0};
                qreal m13 {0.0};
                qreal m21 {0.0};
                qreal m22 {0.0};
                qreal m23 {0.0};
                qreal m31 {0.0};
                qreal m32 {0.0};
                qreal m33 {0.0};
                QPen itemPen;
                QXmlStreamAttributes attributes = rseItemReader.attributes();
                for (const QXmlStreamAttribute &attr : qAsConst(attributes)) {
                    if (attr.name() == "x1") {
                        x1 = attr.value().toFloat();
                    }
                    if (attr.name() == "y1") {
                        y1 = attr.value().toFloat();
                    }
                    if (attr.name() == "x2") {
                        x2 = attr.value().toFloat();
                    }
                    if (attr.name() == "y2") {
                        y2 = attr.value().toFloat();
                    }
                    if (attr.name() == "pen-color") {
                        itemPen.setColor(attr.value().toString());
                    }
                    if (attr.name() == "pen-width") {
                        itemPen.setWidth(attr.value().toInt());
                    }
                    if (attr.name() == "pen-style") {
                        itemPen.setStyle(Qt::PenStyle(attr.value().toInt()));
                    }
                    if (attr.name() == "z") {
                        zValue = attr.value().toFloat();
                    }
                    if (attr.name() == "transform") {
                        QList<QStringRef> transList(attr.value().split(",").toList());
                        m11 = transList.at(0).toFloat();
                        m12 = transList.at(1).toFloat();
                        m13 = transList.at(2).toFloat();
                        m21 = transList.at(3).toFloat();
                        m22 = transList.at(4).toFloat();
                        m23 = transList.at(5).toFloat();
                        m31 = transList.at(6).toFloat();
                        m32 = transList.at(7).toFloat();
                        m33 = transList.at(8).toFloat();
                    }
                }
                line->setLine(x1, y1, x2, y2);
                line->setPen(itemPen);
                line->setZValue(zValue);
                QTransform trans(m11, m12, m13, m21, m22, m23, m31, m32, m33);
                line->setTransform(trans);

                itemList.append(line);
            }
            if (rseItemReader.name() == "polyline") {
                Polyline *polyline = new Polyline(m_itemMenu);
                QPainterPath path;
                QPen itemPen;
                qreal zValue {0.0};
                qreal m11 {0.0};
                qreal m12 {0.0};
                qreal m13 {0.0};
                qreal m21 {0.0};
                qreal m22 {0.0};
                qreal m23 {0.0};
                qreal m31 {0.0};
                qreal m32 {0.0};
                qreal m33 {0.0};
                QXmlStreamAttributes attributes = rseItemReader.attributes();
                for (const QXmlStreamAttribute &attr : qAsConst(attributes)) {
                    if (attr.name() == "m") {
                        QList<QStringRef > point(attr.value().split(",").toList());
                        QPointF startPoint(point.at(0).toFloat(), point.at(1).toFloat());
                        path.moveTo(startPoint);
                    }
                    if (attr.name() == "l") {
                        QList<QStringRef> linePoints(attr.value().split(" ").toList());
                        for (int i = 0; i < linePoints.count(); i++) {
                            QList<QStringRef> point(linePoints.at(i).split(",").toList());
                            QPointF pathPoint(point.at(0).toFloat(), point.at(1).toFloat());
                            path.lineTo(pathPoint);
                        }
                    }
                    if (attr.name() == "pen-color") {
                        itemPen.setColor(attr.value().toString());
                    }
                    if (attr.name() == "pen-width") {
                        itemPen.setWidth(attr.value().toInt());
                    }
                    if (attr.name() == "pen-style") {
                        itemPen.setStyle(Qt::PenStyle(attr.value().toInt()));
                    }
                    if (attr.name() == "z") {
                        zValue = attr.value().toFloat();
                    }
                    if (attr.name() == "transform") {
                        QList<QStringRef> transList(attr.value().split(",").toList());
                        m11 = transList.at(0).toFloat();
                        m12 = transList.at(1).toFloat();
                        m13 = transList.at(2).toFloat();
                        m21 = transList.at(3).toFloat();
                        m22 = transList.at(4).toFloat();
                        m23 = transList.at(5).toFloat();
                        m31 = transList.at(6).toFloat();
                        m32 = transList.at(7).toFloat();
                        m33 = transList.at(8).toFloat();
                    }
                }
                polyline->setPath(path);
                polyline->setPen(itemPen);
                polyline->setZValue(zValue);
                QTransform trans(m11, m12, m13, m21, m22, m23, m31, m32, m33);
                polyline->setTransform(trans);
                itemList.append(polyline);
            }
            if (rseItemReader.name() == "curve") {
                Curve *curve = new Curve(m_itemMenu);
                QPainterPath path;
                QPen itemPen;
                qreal zValue {0.0};
                qreal m11 {0.0};
                qreal m12 {0.0};
                qreal m13 {0.0};
                qreal m21 {0.0};
                qreal m22 {0.0};
                qreal m23 {0.0};
                qreal m31 {0.0};
                qreal m32 {0.0};
                qreal m33 {0.0};
                QXmlStreamAttributes attributes = rseItemReader.attributes();
                for (const QXmlStreamAttribute &attr : qAsConst(attributes)) {
                    if (attr.name() == "m") {
                        QList<QStringRef > point(attr.value().split(",").toList());
                        QPointF startPoint(point.at(0).toFloat(), point.at(1).toFloat());
                        path.moveTo(startPoint);
                    }
                    if (attr.name() == "c") {
                        QList<QStringRef> curvePoints(attr.value().split(" ").toList());
                        for (int i = 0; i < curvePoints.count(); i += 3) {
                            QList<QStringRef> ctr_1_List(curvePoints.at(i).split(",").toList());
                            QPointF ctr_1_Point(ctr_1_List.at(0).toFloat(), ctr_1_List.at(1).toFloat());
                            QList<QStringRef> ctr_2_List(curvePoints.at(i + 1).split(",").toList());
                            QPointF ctr_2_Point(ctr_2_List.at(0).toFloat(), ctr_2_List.at(1).toFloat());
                            QList<QStringRef> curveList(curvePoints.at(i + 2).split(",").toList());
                            QPointF curvePoint(curveList.at(0).toFloat(), curveList.at(1).toFloat());
                            path.cubicTo(ctr_1_Point, ctr_2_Point, curvePoint);
                        }
                    }
                    if (attr.name() == "pen-color") {
                        itemPen.setColor(attr.value().toString());
                    }
                    if (attr.name() == "pen-width") {
                        itemPen.setWidth(attr.value().toInt());
                    }
                    if (attr.name() == "pen-style") {
                        itemPen.setStyle(Qt::PenStyle(attr.value().toInt()));
                    }
                    if (attr.name() == "z") {
                        zValue = attr.value().toFloat();
                    }
                    if (attr.name() == "transform") {
                        QList<QStringRef> transList(attr.value().split(",").toList());
                        m11 = transList.at(0).toFloat();
                        m12 = transList.at(1).toFloat();
                        m13 = transList.at(2).toFloat();
                        m21 = transList.at(3).toFloat();
                        m22 = transList.at(4).toFloat();
                        m23 = transList.at(5).toFloat();
                        m31 = transList.at(6).toFloat();
                        m32 = transList.at(7).toFloat();
                        m33 = transList.at(8).toFloat();
                    }
                }
                curve->setPath(path);
                curve->setPen(itemPen);
                curve->setZValue(zValue);
                QTransform trans(m11, m12, m13, m21, m22, m23, m31, m32, m33);
                curve->setTransform(trans);
                itemList.append(curve);
            }
            if (rseItemReader.name() == "text") {
                qreal x {0.0};
                qreal y {0.0};
                qreal zValue {0.0};
                int fontSize {0};
                bool bold {false};
                bool italic {false};
                bool underline {false};
                QFont font;
                QColor colorText;
                QXmlStreamAttributes attributes = rseItemReader.attributes();
                for (const QXmlStreamAttribute &attr : qAsConst(attributes)) {
                    if (attr.name() == "x") {
                        x = attr.value().toFloat();
                    }
                    if (attr.name() == "y") {
                        y = attr.value().toFloat();
                    }
                    if (attr.name() == "font") {
                        font = attr.value().toString();
                    }
                    if (attr.name() == "font-size") {
                        fontSize = attr.value().toInt();
                    }
                    if (attr.name() == "bold") {
                        bold = attr.value().toInt();
                    }
                    if (attr.name() == "italic") {
                        italic = attr.value().toInt();
                    }
                    if (attr.name() == "underline") {
                        underline = attr.value().toInt();
                    }
                    if (attr.name() == "color") {
                        colorText = attr.value().toString();
                    }
                    if (attr.name() == "z") {
                        zValue = attr.value().toFloat();
                    }
                }
                QString text(rseItemReader.readElementText());
                TextItem *textItem = new TextItem(m_itemMenu);
                textItem->setPlainText(text);
                textItem->setPos(x, y);
                font.setPointSize(fontSize);
                if (bold) {
                    font.setBold(true);
                }
                if (italic) {
                    font.setItalic(true);
                }
                if (underline) {
                    font.setUnderline(true);
                }
                textItem->setFont(font);
                textItem->setDefaultTextColor(colorText);
                textItem->setZValue(zValue);
                itemList.append(textItem);
            }
            if (rseItemReader.name() == "pixmap") {
                qreal x {0.0};
                qreal y {0.0};
                qreal width {0.0};
                qreal height {0.0};
                qreal zValue {0.0};
                qreal m11 {0.0};
                qreal m12 {0.0};
                qreal m13 {0.0};
                qreal m21 {0.0};
                qreal m22 {0.0};
                qreal m23 {0.0};
                qreal m31 {0.0};
                qreal m32 {0.0};
                qreal m33 {0.0};
                QXmlStreamAttributes attributes = rseItemReader.attributes();
                for (const QXmlStreamAttribute &attr : qAsConst(attributes)) {
                    if (attr.name() == "x") {
                        x = attr.value().toFloat();
                    }
                    if (attr.name() == "y") {
                        y = attr.value().toFloat();
                    }
                    if (attr.name() == "width") {
                        width = attr.value().toFloat();
                    }
                    if (attr.name() == "height") {
                        height = attr.value().toFloat();
                    }
                    if (attr.name() == "z") {
                        zValue = attr.value().toFloat();
                    }
                    if (attr.name() == "transform") {
                        QList<QStringRef> transList(attr.value().split(",").toList());
                        m11 = transList.at(0).toFloat();
                        m12 = transList.at(1).toFloat();
                        m13 = transList.at(2).toFloat();
                        m21 = transList.at(3).toFloat();
                        m22 = transList.at(4).toFloat();
                        m23 = transList.at(5).toFloat();
                        m31 = transList.at(6).toFloat();
                        m32 = transList.at(7).toFloat();
                        m33 = transList.at(8).toFloat();
                    }
                }
                const QString base64Pixmap(rseItemReader.readElementText());
                const QByteArray &pixmapArray = QByteArray::fromBase64(base64Pixmap.toLatin1());
                QPixmap pixmap(width, height);
                pixmap.loadFromData(pixmapArray);
                PixmapItem *pixmapItem = new PixmapItem();
                pixmapItem->setPixmap(pixmap);
                pixmapItem->setPos(QPointF(x, y));
                pixmapItem->setZValue(zValue);
                QTransform trans(m11, m12, m13, m21, m22, m23, m31, m32, m33);
                pixmapItem->setTransform(trans);

                itemList.append(pixmapItem);
            }
            if (rseItemReader.name() == "technics_shape") {
                qreal x {0.0};
                qreal y {0.0};
                TechnicsShape::ShapeType shapeType = TechnicsShape::Base;
                qreal zValue {0.0};
                qreal m11 {0.0};
                qreal m12 {0.0};
                qreal m13 {0.0};
                qreal m21 {0.0};
                qreal m22 {0.0};
                qreal m23 {0.0};
                qreal m31 {0.0};
                qreal m32 {0.0};
                qreal m33 {0.0};
                QXmlStreamAttributes attributes = rseItemReader.attributes();
                for (const QXmlStreamAttribute &attr : qAsConst(attributes)) {
                    if (attr.name() == "x") {
                        x = attr.value().toFloat();
                    }
                    if (attr.name() == "y") {
                        y = attr.value().toFloat();
                    }
                    if (attr.name() == "shape_type") {
                        shapeType = TechnicsShape::ShapeType(attr.value().toInt());
                    }
                    if (attr.name() == "z") {
                        zValue = attr.value().toFloat();
                    }
                    if (attr.name() == "transform") {
                        QList<QStringRef> transList(attr.value().split(",").toList());
                        m11 = transList.at(0).toFloat();
                        m12 = transList.at(1).toFloat();
                        m13 = transList.at(2).toFloat();
                        m21 = transList.at(3).toFloat();
                        m22 = transList.at(4).toFloat();
                        m23 = transList.at(5).toFloat();
                        m31 = transList.at(6).toFloat();
                        m32 = transList.at(7).toFloat();
                        m33 = transList.at(8).toFloat();
                    }
                }

                TechnicsShape *technicsShapeItem = new TechnicsShape(m_itemMenu, shapeType);
                technicsShapeItem->setPos(QPointF(x, y));
                technicsShapeItem->setZValue(zValue);
                QTransform trans(m11, m12, m13, m21, m22, m23, m31, m32, m33);
                technicsShapeItem->setTransform(trans);

                itemList.append(technicsShapeItem);
            }
            if (rseItemReader.name() == "device_shape") {
                qreal x {0.0};
                qreal y {0.0};
                DeviceShape::ShapeType shapeType = DeviceShape::Barrel;
                qreal zValue{0.0};
                qreal m11 {0.0};
                qreal m12 {0.0};
                qreal m13 {0.0};
                qreal m21 {0.0};
                qreal m22 {0.0};
                qreal m23 {0.0};
                qreal m31 {0.0};
                qreal m32 {0.0};
                qreal m33 {0.0};
                QXmlStreamAttributes attributes = rseItemReader.attributes();
                for (const QXmlStreamAttribute &attr : qAsConst(attributes)) {
                    if (attr.name() == "x") {
                        x = attr.value().toFloat();
                    }
                    if (attr.name() == "y") {
                        y = attr.value().toFloat();
                    }
                    if (attr.name() == "shape_type") {
                        shapeType = DeviceShape::ShapeType(attr.value().toInt());
                    }
                    if (attr.name() == "z") {
                        zValue = attr.value().toFloat();
                    }
                    if (attr.name() == "transform") {
                        QList<QStringRef> transList(attr.value().split(",").toList());
                        m11 = transList.at(0).toFloat();
                        m12 = transList.at(1).toFloat();
                        m13 = transList.at(2).toFloat();
                        m21 = transList.at(3).toFloat();
                        m22 = transList.at(4).toFloat();
                        m23 = transList.at(5).toFloat();
                        m31 = transList.at(6).toFloat();
                        m32 = transList.at(7).toFloat();
                        m33 = transList.at(8).toFloat();
                    }
                }

                DeviceShape *deviceShapeItem = new DeviceShape(m_itemMenu, shapeType);
                deviceShapeItem->setPos(QPointF(x, y));
                deviceShapeItem->setZValue(zValue);
                QTransform trans(m11, m12, m13, m21, m22, m23, m31, m32, m33);
                deviceShapeItem->setTransform(trans);

                itemList.append(deviceShapeItem);
            }
            if (rseItemReader.name() == "building_item") {
                qreal x {0.0};
                qreal y {0.0};
                qreal itemLeft {0.0};
                qreal itemTop {0.0};
                qreal width {0.0};
                qreal height {0.0};
                BuildingStruct::ShapeType shapeType = BuildingStruct::Wall;
                qreal zValue {0.0};
                qreal m11 {0.0};
                qreal m12 {0.0};
                qreal m13 {0.0};
                qreal m21 {0.0};
                qreal m22 {0.0};
                qreal m23 {0.0};
                qreal m31 {0.0};
                qreal m32 {0.0};
                qreal m33 {0.0};
                QXmlStreamAttributes attributes = rseItemReader.attributes();
                for (const QXmlStreamAttribute &attr : qAsConst(attributes)) {
                    if (attr.name() == "x") {
                        x = attr.value().toFloat();
                    }
                    if (attr.name() == "y") {
                        y = attr.value().toFloat();
                    }
                    if (attr.name() == "item_left") {
                        itemLeft = attr.value().toFloat();
                    }
                    if (attr.name() == "item_top") {
                        itemTop = attr.value().toFloat();
                    }
                    if (attr.name() == "width") {
                        width = attr.value().toFloat();
                    }
                    if (attr.name() == "height") {
                        height = attr.value().toFloat();
                    }
                    if (attr.name() == "shape_type") {
                        shapeType = BuildingStruct::ShapeType(attr.value().toInt());
                    }
                    if (attr.name() == "z") {
                        zValue = attr.value().toFloat();
                    }
                    if (attr.name() == "transform") {
                        QList<QStringRef> transList(attr.value().split(",").toList());
                        m11 = transList.at(0).toFloat();
                        m12 = transList.at(1).toFloat();
                        m13 = transList.at(2).toFloat();
                        m21 = transList.at(3).toFloat();
                        m22 = transList.at(4).toFloat();
                        m23 = transList.at(5).toFloat();
//                        m31 = transList.at(6).toFloat(); происходит смещение относительно начального положения
//                        m32 = transList.at(7).toFloat();
                        m33 = transList.at(8).toFloat();
                    }
                }

                BuildingStruct *deviceShapeItem = new BuildingStruct(m_itemMenu, shapeType);
                deviceShapeItem->setPos(QPointF(x, y));
                deviceShapeItem->setRect(QRectF(itemLeft, itemTop, width, height));
                deviceShapeItem->setZValue(zValue);
                QTransform trans(m11, m12, m13, m21, m22, m23, m31, m32, m33);
                deviceShapeItem->setTransform(trans);

                itemList.append(deviceShapeItem);
            }
        }
        rseItemReader.readNext();
    }

    return itemList;
}
