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

#include "rse_writer.h"
#include "../include/rectshape.h"
#include "../include/ellipseshape.h"
#include "../include/polylineshape.h"
#include "../include/curve.h"
#include "../include/textshape.h"
#include "../include/pixmapshape.h"
#include "../include/technicsshape.h"
#include "../include/deviceshape.h"
#include "../include/buildingshape.h"

#include <QXmlStreamWriter>
#include <QGraphicsItem>
#include <QPen>
#include <QTextDocument>
#include <QPixmap>
#include <QBuffer>

RseWriter::RseWriter()
{
}

void RseWriter::writeRse(QIODevice *file, const QList<QGraphicsItem *> &items, QRectF sceneRect)
{
    QXmlStreamWriter rseWriter(file);
    rseWriter.setAutoFormatting(true);
    rseWriter.writeStartDocument();
    rseWriter.writeStartElement("RSiSedData");
    rseWriter.writeAttribute("version", "v0.1");
    rseWriter.writeStartElement("Scene");
    if (sceneRect.isNull()) {
        rseWriter.writeAttribute("x", QString::number(0));
        rseWriter.writeAttribute("y", QString::number(0));
        rseWriter.writeAttribute("width", QString::number(1920));
        rseWriter.writeAttribute("height", QString::number(1080));
    } else {
        rseWriter.writeAttribute("x", QString::number(sceneRect.x()));
        rseWriter.writeAttribute("y", QString::number(sceneRect.y()));
        rseWriter.writeAttribute("width", QString::number(sceneRect.width()));
        rseWriter.writeAttribute("height", QString::number(sceneRect.height()));
    }
    rseWriter.writeStartElement("ItemsList");
    for (QGraphicsItem *item : qAsConst(items)) {
        if (item->type() == RectShape::Type) {
            RectShape *rectShape = qgraphicsitem_cast<RectShape *>(item);
            QRectF rect(rectShape->rect());
            QTransform trans(rectShape->sceneTransform());
            QString transStr(QString::number(trans.m11()) + "," + QString::number(trans.m12())
                             + "," + QString::number(trans.m13()) + ","
                             + QString::number(trans.m21()) + "," + QString::number(trans.m22())
                             + "," + QString::number(trans.m23()) + ","
                             + QString::number(trans.m31()) + "," + QString::number(trans.m32())
                             + "," + QString::number(trans.m33()));
            rseWriter.writeStartElement("rect");
            rseWriter.writeAttribute("x", QString::number(rect.x()));
            rseWriter.writeAttribute("y", QString::number(rect.y()));
            rseWriter.writeAttribute("width", QString::number(rectShape->rect().width()));
            rseWriter.writeAttribute("height", QString::number(rectShape->rect().height()));
            rseWriter.writeAttribute("pen-color", rectShape->pen().color().name());
            rseWriter.writeAttribute("pen-width", QString::number(rectShape->pen().width()));
            rseWriter.writeAttribute("pen-style", QString::number(rectShape->pen().style()));
            rseWriter.writeAttribute("brush-color", rectShape->brush().color().name());
            rseWriter.writeAttribute("brush-style", QString::number(rectShape->brush().style()));
            rseWriter.writeAttribute("z", QString::number(rectShape->zValue()));
            rseWriter.writeAttribute("transform", transStr);
            rseWriter.writeEndElement(); // rect
        }
        if (item->type() == EllipseShape::Type) {
            EllipseShape *ellipseShape = qgraphicsitem_cast<EllipseShape *>(item);
            QRectF rect = ellipseShape->rect();
            QTransform trans(ellipseShape->sceneTransform());
            QString transStr(QString::number(trans.m11()) + "," + QString::number(trans.m12())
                             + "," + QString::number(trans.m13()) + ","
                             + QString::number(trans.m21()) + "," + QString::number(trans.m22())
                             + "," + QString::number(trans.m23()) + ","
                             + QString::number(trans.m31()) + "," + QString::number(trans.m32())
                             + "," + QString::number(trans.m33()));
            rseWriter.writeStartElement("ellipse");
            rseWriter.writeAttribute("x", QString::number(rect.x()));
            rseWriter.writeAttribute("y", QString::number(rect.y()));
            rseWriter.writeAttribute("width", QString::number(rect.width()));
            rseWriter.writeAttribute("height", QString::number(rect.height()));
            rseWriter.writeAttribute("start-angle", QString::number(ellipseShape->startAngle()));
            rseWriter.writeAttribute("span-angle", QString::number(ellipseShape->spanAngle()));
            rseWriter.writeAttribute("pen-color", ellipseShape->pen().color().name());
            rseWriter.writeAttribute("pen-width", QString::number(ellipseShape->pen().width()));
            rseWriter.writeAttribute("pen-style", QString::number(ellipseShape->pen().style()));
            rseWriter.writeAttribute("brush-color", ellipseShape->brush().color().name());
            rseWriter.writeAttribute("brush-style", QString::number(ellipseShape->brush().style()));
            rseWriter.writeAttribute("z", QString::number(ellipseShape->zValue()));
            rseWriter.writeAttribute("transform", transStr);
            rseWriter.writeEndElement(); // ellipse
        }
        if (item->type() == PolylineShape::Type) {
            PolylineShape *polylineShape = qgraphicsitem_cast<PolylineShape *>(item);
            QPainterPath linePath = polylineShape->path();
            QStringList dotList;
            for (int i = 0; i < linePath.elementCount(); i++) {
                dotList << QString::number(linePath.elementAt(i).x) + ","
                           + QString::number(linePath.elementAt(i).y);
            }
            rseWriter.writeStartElement("polyline");
            rseWriter.writeAttribute("m", dotList.constFirst());
            QString dotLine;
            for (int i = 1; i < dotList.count(); i++) {
                dotLine += dotList.at(i) + " ";
            }
            dotLine.chop(1);
            QTransform trans(polylineShape->sceneTransform());
            QString transStr(QString::number(trans.m11()) + "," + QString::number(trans.m12())
                             + "," + QString::number(trans.m13()) + ","
                             + QString::number(trans.m21()) + "," + QString::number(trans.m22())
                             + "," + QString::number(trans.m23()) + ","
                             + QString::number(trans.m31()) + "," + QString::number(trans.m32())
                             + "," + QString::number(trans.m33()));
            rseWriter.writeAttribute("l", dotLine);
            rseWriter.writeAttribute("pen-color", polylineShape->pen().color().name());
            rseWriter.writeAttribute("pen-width", QString::number(polylineShape->pen().width()));
            rseWriter.writeAttribute("pen-style", QString::number(polylineShape->pen().style()));
            rseWriter.writeAttribute("z", QString::number(polylineShape->zValue()));
            rseWriter.writeAttribute("transform", transStr);
            rseWriter.writeEndElement(); // polyline
        }
        if (item->type() == Curve::Type) {
            Curve *curveShape = qgraphicsitem_cast<Curve *>(item);
            QPainterPath curvePath = curveShape->path();
            QStringList dotList;
            for (int i = 0; i < curvePath.elementCount(); i++) {
                dotList << QString::number(curvePath.elementAt(i).x) + ","
                           + QString::number(curvePath.elementAt(i).y);
            }
            rseWriter.writeStartElement("curve");
            rseWriter.writeAttribute("m", dotList.constFirst());
            QString dotLine;
            for (int i = 1; i < dotList.count(); i ++) {
                dotLine += dotList.at(i) + " ";
            }
            dotLine.chop(1);
            QTransform trans(curveShape->sceneTransform());
            QString transStr(QString::number(trans.m11()) + "," + QString::number(trans.m12())
                             + "," + QString::number(trans.m13()) + ","
                             + QString::number(trans.m21()) + "," + QString::number(trans.m22())
                             + "," + QString::number(trans.m23()) + ","
                             + QString::number(trans.m31()) + "," + QString::number(trans.m32())
                             + "," + QString::number(trans.m33()));
            rseWriter.writeAttribute("c", dotLine);
            rseWriter.writeAttribute("pen-color", curveShape->pen().color().name());
            rseWriter.writeAttribute("pen-width", QString::number(curveShape->pen().width()));
            rseWriter.writeAttribute("pen-style", QString::number(curveShape->pen().style()));
            rseWriter.writeAttribute("z", QString::number(curveShape->zValue()));
            rseWriter.writeAttribute("transform", transStr);
            rseWriter.writeEndElement(); // curve
        }
        if (item->type() == QGraphicsLineItem::Type) {
            QGraphicsLineItem *lineItem = qgraphicsitem_cast<QGraphicsLineItem *>(item);
            QTransform trans(lineItem->sceneTransform());
            QString transStr(QString::number(trans.m11()) + "," + QString::number(trans.m12())
                             + "," + QString::number(trans.m13()) + ","
                             + QString::number(trans.m21()) + "," + QString::number(trans.m22())
                             + "," + QString::number(trans.m23()) + ","
                             + QString::number(trans.m31()) + "," + QString::number(trans.m32())
                             + "," + QString::number(trans.m33()));
            rseWriter.writeStartElement("line");
            rseWriter.writeAttribute("x1", QString::number(lineItem->line().x1()));
            rseWriter.writeAttribute("y1", QString::number(lineItem->line().y1()));
            rseWriter.writeAttribute("x2", QString::number(lineItem->line().x2()));
            rseWriter.writeAttribute("y2", QString::number(lineItem->line().y2()));
            rseWriter.writeAttribute("pen-color", lineItem->pen().color().name());
            rseWriter.writeAttribute("pen-width", QString::number(lineItem->pen().width()));
            rseWriter.writeAttribute("pen-style", QString::number(lineItem->pen().style()));
            rseWriter.writeAttribute("z", QString::number(lineItem->zValue()));
            rseWriter.writeAttribute("transform", transStr);
            rseWriter.writeEndElement(); // lineItem
        }
        if (item->type() == TextShape::Type) {
            TextShape *textShape = qgraphicsitem_cast<TextShape *>(item);
            rseWriter.writeStartElement("text");
            rseWriter.writeAttribute("x", QString::number(textShape->x()));
            rseWriter.writeAttribute("y", QString::number(textShape->y()));
            rseWriter.writeAttribute("font", textShape->font().family());
            rseWriter.writeAttribute("font-size", QString::number(textShape->font().pointSize()));
            rseWriter.writeAttribute("bold", QString::number(textShape->font().bold()));
            rseWriter.writeAttribute("italic", QString::number(textShape->font().italic()));
            rseWriter.writeAttribute("underline", QString::number(textShape->font().underline()));
            rseWriter.writeAttribute("color", textShape->defaultTextColor().name());
            rseWriter.writeAttribute("z", QString::number(textShape->zValue()));
            rseWriter.writeCharacters(textShape->document()->toPlainText());
            rseWriter.writeEndElement(); // textItem
        }
        if (item->type() == PixmapShape::Type) {
            PixmapShape *pixmapShape = qgraphicsitem_cast<PixmapShape *> (item);
            rseWriter.writeStartElement("pixmap");
            rseWriter.writeAttribute("x", QString::number(pixmapShape->scenePos().x()));
            rseWriter.writeAttribute("y", QString::number(pixmapShape->scenePos().y()));
            rseWriter.writeAttribute("width", QString::number(pixmapShape->pixmap().width()));
            rseWriter.writeAttribute("height", QString::number(pixmapShape->pixmap().height()));
            rseWriter.writeAttribute("z", QString::number(pixmapShape->zValue()));
            QTransform trans(pixmapShape->transform());
            QString transPixmap(QString::number(trans.m11()) + "," + QString::number(trans.m12())
                                + "," + QString::number(trans.m13()) + ","
                                + QString::number(trans.m21()) + "," + QString::number(trans.m22())
                                + "," + QString::number(trans.m23()) + ","
                                + QString::number(trans.m31()) + "," + QString::number(trans.m32())
                                + "," + QString::number(trans.m33()));
            rseWriter.writeAttribute("transform", transPixmap);
            QByteArray pixmapArray;
            QBuffer buffer(&pixmapArray);
            buffer.open(QIODevice::WriteOnly);
            pixmapShape->pixmap().save(&buffer, "png");
            const QString &strPixmap(pixmapArray.toBase64());
            rseWriter.writeCharacters(strPixmap);
            rseWriter.writeEndElement(); // pixmapitems
        }
        if (TechnicsShape *p_technicsShape = dynamic_cast<TechnicsShape *>(item)) {
            rseWriter.writeStartElement("technics_shape");
            rseWriter.writeAttribute("x", QString::number(p_technicsShape->scenePos().x()));
            rseWriter.writeAttribute("y", QString::number(p_technicsShape->scenePos().y()));
            rseWriter.writeAttribute("item_left", QString::number(p_technicsShape->rect().left()));
            rseWriter.writeAttribute("item_top", QString::number(p_technicsShape->rect().top()));
            rseWriter.writeAttribute("width", QString::number(p_technicsShape->rect().width()));
            rseWriter.writeAttribute("height", QString::number(p_technicsShape->rect().height()));
            TechnicsShape::ShapeType shapeType = p_technicsShape->shapeType();
            rseWriter.writeAttribute("shape_type", QString::number(shapeType));
            rseWriter.writeAttribute("z", QString::number(p_technicsShape->zValue()));
            QTransform transform(p_technicsShape->transform());
            QString transfomTechnicsShape(QString::number(transform.m11()) + ","
                                          + QString::number(transform.m12()) + ","
                                          + QString::number(transform.m13()) + ","
                                          + QString::number(transform.m21()) + ","
                                          + QString::number(transform.m22()) + ","
                                          + QString::number(transform.m23()) + ","
                                          + QString::number(transform.m31()) + ","
                                          + QString::number(transform.m32()) + ","
                                          + QString::number(transform.m33()));
            rseWriter.writeAttribute("transform", transfomTechnicsShape);
            rseWriter.writeAttribute("text", p_technicsShape->text());
            if (TankerShape *p_tankerShape = dynamic_cast<TankerShape *>(p_technicsShape)) {
                rseWriter.writeAttribute("pipes", QString::number(p_tankerShape->pipes()));
                rseWriter.writeAttribute("collector", QString::number(p_tankerShape->collector()));
            }
            rseWriter.writeEndElement(); // technicsShapeItem
        }
        if (item->type() == DeviceShape::Type) {
            DeviceShape *deviceShape = qgraphicsitem_cast<DeviceShape *>(item);
            rseWriter.writeStartElement("device_shape");
            rseWriter.writeAttribute("x", QString::number(deviceShape->scenePos().x()));
            rseWriter.writeAttribute("y", QString::number(deviceShape->scenePos().y()));
            DeviceShape::ShapeType shapeType = deviceShape->shapeType();
            rseWriter.writeAttribute("shape_type", QString::number(shapeType));
            rseWriter.writeAttribute("z", QString::number(deviceShape->zValue()));
            QTransform transform(deviceShape->transform());
            QString transfomDeviceShape(QString::number(transform.m11()) + ","
                                          + QString::number(transform.m12()) + ","
                                          + QString::number(transform.m13()) + ","
                                          + QString::number(transform.m21()) + ","
                                          + QString::number(transform.m22()) + ","
                                          + QString::number(transform.m23()) + ","
                                          + QString::number(transform.m31()) + ","
                                          + QString::number(transform.m32()) + ","
                                          + QString::number(transform.m33()));
            rseWriter.writeAttribute("transform", transfomDeviceShape);
            rseWriter.writeEndElement(); // deviceShapeItem
        }
        if (BuildingShape *buildingShape = dynamic_cast<BuildingShape *>(item)) {
            rseWriter.writeStartElement("building_shape");
            rseWriter.writeAttribute("x", QString::number(buildingShape->scenePos().x()));
            rseWriter.writeAttribute("y", QString::number(buildingShape->scenePos().y()));
            rseWriter.writeAttribute("item_left", QString::number(buildingShape->rect().left()));
            rseWriter.writeAttribute("item_top", QString::number(buildingShape->rect().top()));
            rseWriter.writeAttribute("width", QString::number(buildingShape->rect().width()));
            rseWriter.writeAttribute("height", QString::number(buildingShape->rect().height()));
            rseWriter.writeAttribute("pen-color", buildingShape->pen().color().name());
            rseWriter.writeAttribute("pen-width", QString::number(buildingShape->pen().width()));
            rseWriter.writeAttribute("brush-color", buildingShape->brush().color().name());
            rseWriter.writeAttribute("brush-style", QString::number(buildingShape->brush().style()));
            BuildingShape::ShapeType shapeType{buildingShape->shapeType()};
            rseWriter.writeAttribute("shape_type", QString::number(shapeType));
            rseWriter.writeAttribute("z", QString::number(buildingShape->zValue()));
            QTransform transform(buildingShape->transform());
            QString transBuildingItem(QString::number(transform.m11()) + ","
                                          + QString::number(transform.m12()) + ","
                                          + QString::number(transform.m13()) + ","
                                          + QString::number(transform.m21()) + ","
                                          + QString::number(transform.m22()) + ","
                                          + QString::number(transform.m23()) + ","
                                          + QString::number(transform.m33()));
            rseWriter.writeAttribute("transform", transBuildingItem);
            if (DoorShape *p_doorShape = dynamic_cast<DoorShape *>(buildingShape)) {
                DoorShape::DoorState doorState{p_doorShape->doorState()};
                rseWriter.writeAttribute("door-state", QString::number(doorState));
                DoorShape::LeafPosition leafPosition{p_doorShape->leafPosition()};
                rseWriter.writeAttribute("leaf-position", QString::number(leafPosition));
            }
            rseWriter.writeEndElement(); // buildingItem
        }
    }
    rseWriter.writeEndElement(); // ItemList
    rseWriter.writeEndElement(); // Scene
    rseWriter.writeEndElement(); // RSiSedData
    rseWriter.writeEndDocument();
}
