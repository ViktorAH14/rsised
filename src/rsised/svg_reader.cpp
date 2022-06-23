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

#include "svg_reader.h"
#include "../include/rectshape.h"
#include "../include/ellipseshape.h"
#include "../include/polylineshape.h"
#include "../include/curve.h"
#include "../include/textshape.h"
#include "../include/pixmapshape.h"

#include <QDomDocument>
#include <QFile>
#include <QPen>
#include <QFont>

SvgReader::SvgReader(QMenu *itemMenu) : m_itemMenu{itemMenu}, currentPathType{PathType::Polyline}
{
}

QRectF SvgReader::getSize(const QString &fileName) const
{
    QDomDocument doc;
    QFile file(fileName);
    if (!file.open(QIODevice::ReadOnly) || !doc.setContent(&file)) {
        return QRectF(0,0,1920,1080);
    }

    QDomNodeList list = doc.elementsByTagName("svg");
    if(list.length() > 0) {
        QDomElement svgElement = list.item(0).toElement();
        QStringList parameters = svgElement.attribute("viewBox").split(" ");
        file.close();
        return QRectF(parameters.at(0).toInt(),
                      parameters.at(1).toInt(),
                      parameters.at(2).toInt(),
                      parameters.at(3).toInt());
    }
    file.close();
    return QRectF(0,0,1920,1080);
}

QList<QGraphicsItem *> SvgReader::getElements(const QString &fileName)
{
    QList<QGraphicsItem *> itemList;
    QDomDocument doc;
    QFile file(fileName);
    if (!file.open(QIODevice::ReadOnly) || !doc.setContent(&file)) {
        return itemList;
    }

    QDomNodeList gList = doc.elementsByTagName("g");
    for (int i = 0; i < gList.size(); i++) {
        QDomNode gNode = gList.item(i);

        QDomElement elementRect = gNode.firstChildElement("rect");
        if (!elementRect.isNull()){
            RectShape *rectShape = new RectShape();
            rectShape->setMenu(m_itemMenu);
// Position and size
            rectShape->setRect(elementRect.attribute("x").toInt(),
                               elementRect.attribute("y").toInt(),
                               elementRect.attribute("width").toInt(),
                               elementRect.attribute("height").toInt());

            QDomElement gElement = gNode.toElement();
// Brush
            QStringList urlList(gElement.attribute("fill").split("(#"));
            if ((QString::compare(urlList.at(0), "url")) == 0) {
                QStringList patternList(urlList.at(1).split("_"));
                QString color(patternList.at(1));
                color.chop(1);
                QColor fillColor("#" + color);
                Qt::BrushStyle brushStyle(Qt::SolidPattern);
                if (QString::compare(patternList.at(0), "fillpattern2") == 0) {
                    brushStyle = Qt::Dense1Pattern;
                }
                if (QString::compare(patternList.at(0), "fillpattern3") == 0) {
                    brushStyle = Qt::Dense2Pattern;
                }
                if (QString::compare(patternList.at(0), "fillpattern4") == 0) {
                    brushStyle = Qt::Dense3Pattern;
                }
                if (QString::compare(patternList.at(0), "fillpattern5") == 0) {
                    brushStyle = Qt::Dense4Pattern;
                }
                if (QString::compare(patternList.at(0), "fillpattern6") == 0) {
                    brushStyle = Qt::Dense5Pattern;
                }
                if (QString::compare(patternList.at(0), "fillpattern7") == 0) {
                    brushStyle = Qt::Dense6Pattern;
                }
                if (QString::compare(patternList.at(0), "fillpattern8") == 0) {
                    brushStyle = Qt::Dense7Pattern;
                }
                if (QString::compare(patternList.at(0), "fillpattern9") == 0) {
                    brushStyle = Qt::HorPattern;
                }
                if (QString::compare(patternList.at(0), "fillpattern10") == 0) {
                    brushStyle = Qt::VerPattern;
                }
                if (QString::compare(patternList.at(0), "fillpattern11") == 0) {
                    brushStyle = Qt::CrossPattern;
                }
                if (QString::compare(patternList.at(0), "fillpattern12") == 0) {
                    brushStyle = Qt::BDiagPattern;
                }
                if (QString::compare(patternList.at(0), "fillpattern13") == 0) {
                    brushStyle = Qt::FDiagPattern;
                }
                if (QString::compare(patternList.at(0), "fillpattern14") == 0) {
                    brushStyle = Qt::DiagCrossPattern;
                }
                rectShape->setBrush(QBrush(fillColor, brushStyle));
            } else {
                QColor fillColor(gElement.attribute("fill", "#ffffff"));
                fillColor.setAlphaF(gElement.attribute("fill-opacity","0").toFloat());
                rectShape->setBrush(QBrush(fillColor, Qt::SolidPattern));
            }
// Pen
            QColor strokeColor(gElement.attribute("stroke", "#000000"));
            strokeColor.setAlphaF(gElement.attribute("stroke-opacity").toFloat());
            qreal strokeWidth(gElement.attribute("stroke-width", "0").toInt());
            QStringList strokeDasharray(gElement.attribute("stroke-dasharray").split(","));
            Qt::PenStyle penStyle(Qt::SolidLine);
            switch (strokeDasharray.count()) {
            case 2:
                if ((strokeDasharray.at(0).toInt()) <= (strokeDasharray.at(1).toInt())) {
                    penStyle = Qt::DotLine;
                } else {
                    penStyle = Qt::DashLine;
                }
                break;
            case 4:
                penStyle = Qt::DashDotLine;
                break;
            case 6:
                penStyle = Qt::DashDotDotLine;
                break;
            default:
                break;
            }
            rectShape->setPen(QPen(strokeColor, strokeWidth, penStyle));
// Tronsfomation
            QString transStr = gElement.attribute("transform");
            transStr.replace(QString("matrix("), QString(""));
            transStr.replace(QString(")"), QString(""));
            QStringList transList(transStr.split(","));
            qreal m11{transList.at(0).toFloat()};   // Horizontal scaling
            qreal m12{transList.at(1).toFloat()};   // Vertical shearing
            qreal m21{transList.at(2).toFloat()};   // Horizontal shearing
            qreal m22{transList.at(3).toFloat()};   // Vertical scaling
            qreal m31{transList.at(4).toFloat()};   // Horizontal position (dx)
            qreal m32{transList.at(5).toFloat()};   // Vertical position (dy)
            QTransform transformation(m11, m12, m21, m22, m31, m32);
            rectShape->setTransform(transformation);

            itemList.append(rectShape);
            continue;
        }

        QDomElement elementEllipse = gNode.firstChildElement("ellipse");
        if (!elementEllipse.isNull()) {
            EllipseShape *ellipseShape = new EllipseShape(m_itemMenu);
// Position and size
            qreal cx = elementEllipse.attribute("cx").toFloat();
            qreal cy = elementEllipse.attribute("cy").toFloat();
            qreal rx = elementEllipse.attribute("rx").toFloat();
            qreal ry = elementEllipse.attribute("ry").toFloat();
            qreal x = cx - rx;
            qreal y = cy - ry;
            qreal width = rx * 2;
            qreal height = ry * 2;
            ellipseShape->setRect(x, y, width, height);

            QDomElement gElement = gNode.toElement();
// Brush
            QStringList urlList(gElement.attribute("fill").split("(#"));
            if ((QString::compare(urlList.at(0), "url")) == 0) {
                QStringList patternList(urlList.at(1).split("_"));
                QString color(patternList.at(1));
                color.chop(1);
                QColor fillColor("#" + color);
                Qt::BrushStyle brushStyle(Qt::SolidPattern);
                if (QString::compare(patternList.at(0), "fillpattern2") == 0) {
                    brushStyle = Qt::Dense1Pattern;
                }
                if (QString::compare(patternList.at(0), "fillpattern3") == 0) {
                    brushStyle = Qt::Dense2Pattern;
                }
                if (QString::compare(patternList.at(0), "fillpattern4") == 0) {
                    brushStyle = Qt::Dense3Pattern;
                }
                if (QString::compare(patternList.at(0), "fillpattern5") == 0) {
                    brushStyle = Qt::Dense4Pattern;
                }
                if (QString::compare(patternList.at(0), "fillpattern6") == 0) {
                    brushStyle = Qt::Dense5Pattern;
                }
                if (QString::compare(patternList.at(0), "fillpattern7") == 0) {
                    brushStyle = Qt::Dense6Pattern;
                }
                if (QString::compare(patternList.at(0), "fillpattern8") == 0) {
                    brushStyle = Qt::Dense7Pattern;
                }
                if (QString::compare(patternList.at(0), "fillpattern9") == 0) {
                    brushStyle = Qt::HorPattern;
                }
                if (QString::compare(patternList.at(0), "fillpattern10") == 0) {
                    brushStyle = Qt::VerPattern;
                }
                if (QString::compare(patternList.at(0), "fillpattern11") == 0) {
                    brushStyle = Qt::CrossPattern;
                }
                if (QString::compare(patternList.at(0), "fillpattern12") == 0) {
                    brushStyle = Qt::BDiagPattern;
                }
                if (QString::compare(patternList.at(0), "fillpattern13") == 0) {
                    brushStyle = Qt::FDiagPattern;
                }
                if (QString::compare(patternList.at(0), "fillpattern14") == 0) {
                    brushStyle = Qt::DiagCrossPattern;
                }
                ellipseShape->setBrush(QBrush(fillColor, brushStyle));
            } else {
                QColor fillColor(gElement.attribute("fill", "#ffffff"));
                fillColor.setAlphaF(gElement.attribute("fill-opacity","0").toFloat());
                ellipseShape->setBrush(QBrush(fillColor, Qt::SolidPattern));
            }
// Pen
            QColor strokeColor(gElement.attribute("stroke", "#000000"));
            strokeColor.setAlphaF(gElement.attribute("stroke-opacity").toFloat());
            qreal strokeWidth(gElement.attribute("stroke-width", "0").toInt());
            QStringList strokeDasharray(gElement.attribute("stroke-dasharray").split(","));
            Qt::PenStyle penStyle(Qt::SolidLine);
            switch (strokeDasharray.count()) {
            case 2:
                if ((strokeDasharray.at(0).toInt()) <= (strokeDasharray.at(1).toInt())) {
                    penStyle = Qt::DotLine;
                } else {
                    penStyle = Qt::DashLine;
                }
                break;
            case 4:
                penStyle = Qt::DashDotLine;
                break;
            case 6:
                penStyle = Qt::DashDotDotLine;
                break;
            default:
                break;
            }
            ellipseShape->setPen(QPen(strokeColor, strokeWidth, penStyle));
// Tronsfomation
            QString transStr = gElement.attribute("transform");
            transStr.replace(QString("matrix("), QString(""));
            transStr.replace(QString(")"), QString(""));
            QStringList transList(transStr.split(","));
            qreal m11{transList.at(0).toFloat()};   // Horizontal scaling
            qreal m12{transList.at(1).toFloat()};   // Vertical shearing
            qreal m21{transList.at(2).toFloat()};   // Horizontal shearing
            qreal m22{transList.at(3).toFloat()};   // Vertical scaling
            qreal m31{transList.at(4).toFloat()};   // Horizontal position (dx)
            qreal m32{transList.at(5).toFloat()};   // Vertical position (dy)
            QTransform transformation(m11, m12, m21, m22, m31, m32);
            ellipseShape->setTransform(transformation);

            itemList.append(ellipseShape);
            continue;
        }

        QDomElement elementLine = gNode.firstChildElement("line");
        if (!elementLine.isNull()) {
            QGraphicsLineItem *line = new QGraphicsLineItem();
            line->setFlag(QGraphicsItem::ItemIsMovable, true);

            line->setLine(elementLine.attribute("x1").toInt(),
                          elementLine.attribute("y1").toInt(),
                          elementLine.attribute("x2").toInt(),
                          elementLine.attribute("y2").toInt());
            QDomElement gElement = gNode.toElement();
// Pen
            QColor strokeColor(gElement.attribute("stroke", "#000000"));
            strokeColor.setAlphaF(gElement.attribute("stroke-opacity").toFloat());
            qreal strokeWidth(gElement.attribute("stroke-width", "0").toInt());
            QStringList strokeDasharray(gElement.attribute("stroke-dasharray").split(","));
            Qt::PenStyle penStyle(Qt::SolidLine);
            switch (strokeDasharray.count()) {
            case 2:
                if ((strokeDasharray.at(0).toInt()) <= (strokeDasharray.at(1).toInt())) {
                    penStyle = Qt::DotLine;
                } else {
                    penStyle = Qt::DashLine;
                }
                break;
            case 4:
                penStyle = Qt::DashDotLine;
                break;
            case 6:
                penStyle = Qt::DashDotDotLine;
                break;
            default:
                break;
            }
            line->setPen(QPen(strokeColor, strokeWidth, penStyle));
// Tronsfomation
            QString transStr = gElement.attribute("transform");
            transStr.replace(QString("matrix("), QString(""));
            transStr.replace(QString(")"), QString(""));
            QStringList transList(transStr.split(","));
            qreal m11{transList.at(0).toFloat()};   // Horizontal scaling
            qreal m12{transList.at(1).toFloat()};   // Vertical shearing
            qreal m21{transList.at(2).toFloat()};   // Horizontal shearing
            qreal m22{transList.at(3).toFloat()};   // Vertical scaling
            qreal m31{transList.at(4).toFloat()};   // Horizontal position (dx)
            qreal m32{transList.at(5).toFloat()};   // Vertical position (dy)
            QTransform transformation(m11, m12, m21, m22, m31, m32);
            line->setTransform(transformation);

            itemList.append(line);
            continue;
        }

        QDomElement elementPath = gNode.firstChildElement("path");
        if (!elementPath.isNull()) {
            QPainterPath path;
            QStringList pointsList = elementPath.attribute("d").split(" ");
            if (pointsList.back() == "") {
                pointsList.removeLast();
            }
            QString firstPoint = pointsList.at(0);
            QStringList firstPointList = firstPoint.replace(QString("M"), QString("")).split(",");
            path.moveTo(firstPointList.at(0).toFloat(), firstPointList.at(1).toFloat());
            for (int i = 1; i < pointsList.size(); i++) {
                QString pathPoints = pointsList.at(i);
                if (pathPoints.at(0) == 'L') {
                    currentPathType = PathType::Polyline;
                    QStringList pointList = pathPoints.replace(QString("L"), QString("")).split(",");
                    path.lineTo(pointList.at(0).toFloat(), pointList.at(1).toFloat());
                }
                if (pathPoints.at(0) == 'C') {
                    currentPathType = PathType::Curve;
                    QStringList c1PointList = pathPoints.replace(QString("C"), QString("")).split(" ");
                    QStringList c1(c1PointList.at(0).split(","));
                    QPointF ctr_1_Point(c1.at(0).toFloat(), c1.at(1).toFloat());
                    i++;
                    QStringList c2(pointsList.at(i).split(","));
                    QPointF ctr_2_Point(c2.at(0).toFloat(), c2.at(1).toFloat());
                    i++;
                    QStringList cur(pointsList.at(i).split(","));
                    QPointF curvePoint(cur.at(0).toFloat(), cur.at(1).toFloat());
                    path.cubicTo(ctr_1_Point, ctr_2_Point, curvePoint);
                }
            }
            QDomElement gElement = gNode.toElement();
// Pen
            QColor strokeColor(gElement.attribute("stroke", "#000000"));
            strokeColor.setAlphaF(gElement.attribute("stroke-opacity").toFloat());
            qreal strokeWidth(gElement.attribute("stroke-width", "0").toInt());
            QStringList strokeDasharray(gElement.attribute("stroke-dasharray").split(","));
            Qt::PenStyle penStyle(Qt::SolidLine);
            switch (strokeDasharray.count()) {
            case 2:
                if ((strokeDasharray.at(0).toInt()) <= (strokeDasharray.at(1).toInt())) {
                    penStyle = Qt::DotLine;
                } else {
                    penStyle = Qt::DashLine;
                }
                break;
            case 4:
                penStyle = Qt::DashDotLine;
                break;
            case 6:
                penStyle = Qt::DashDotDotLine;
                break;
            default:
                break;
            }
// Tronsfomation
            QString transStr = gElement.attribute("transform");
            transStr.replace(QString("matrix("), QString(""));
            transStr.replace(QString(")"), QString(""));
            QStringList transList(transStr.split(","));
            qreal m11{transList.at(0).toFloat()};   // Horizontal scaling
            qreal m12{transList.at(1).toFloat()};   // Vertical shearing
            qreal m21{transList.at(2).toFloat()};   // Horizontal shearing
            qreal m22{transList.at(3).toFloat()};   // Vertical scaling
            qreal m31{transList.at(4).toFloat()};   // Horizontal position (dx)
            qreal m32{transList.at(5).toFloat()};   // Vertical position (dy)
            QTransform transformation(m11, m12, m21, m22, m31, m32);

            if (currentPathType == PathType::Polyline) {
                PolylineShape *polylineShape = new PolylineShape(m_itemMenu);
                polylineShape->setPath(path);
                polylineShape->setPen(QPen(strokeColor, strokeWidth, penStyle));
                polylineShape->setTransform(transformation);
                itemList.append(polylineShape);
            }
            if (currentPathType == PathType::Curve) {
                Curve *curveShape = new Curve(m_itemMenu);
                curveShape->setPath(path);
                curveShape->setPen(QPen(strokeColor, strokeWidth, penStyle));
                curveShape->setTransform(transformation);
                itemList.append(curveShape);
            }
            continue;
        }
        QDomElement elementText = gNode.firstChildElement("text");
        if (!elementText.isNull()) {
            TextShape *textShape = new TextShape(m_itemMenu);
            QString text = elementText.text();
            textShape->setPlainText(text);
            qreal x = elementText.attribute("x").toFloat();
            qreal y = elementText.attribute("y").toFloat();
            textShape->setPos(x, y);
            QFont textFont(elementText.attribute("font-family"));
            int fontSize{elementText.attribute("font-size").toInt()};
            textFont.setPointSize(fontSize);
            int fontWeight{elementText.attribute("font-weight").toInt()};
            textFont.setWeight(fontWeight < 700 ? QFont::Normal : QFont::Bold);
            bool italic{false};
            if (elementText.attribute("font-style") == "italic") {
                italic = true;
            }
            textFont.setItalic(italic);
            //  The underlining of the text is not saved, so there is no definition of it.
            textShape->setFont(textFont);
            QColor textColor(elementText.attribute("fill"));
            textShape->setDefaultTextColor(textColor);
            QDomElement gElement = gNode.toElement();
// Tronsfomation
            QString transStr = gElement.attribute("transform");
            transStr.replace(QString("matrix("), QString(""));
            transStr.replace(QString(")"), QString(""));
            QStringList transList(transStr.split(","));
            qreal m11{transList.at(0).toFloat()};   // Horizontal scaling
            qreal m12{transList.at(1).toFloat()};   // Vertical shearing
            qreal m21{transList.at(2).toFloat()};   // Horizontal shearing
            qreal m22{transList.at(3).toFloat()};   // Vertical scaling
            qreal m31{transList.at(4).toFloat()};   // Horizontal position (dx)
            qreal m32{transList.at(5).toFloat()};   // Vertical position (dy)
            QTransform transformation(m11, m12, m21, m22, m31, m32);
            textShape->setTransform(transformation);

            itemList.append(textShape);
            continue;
        }
        QDomElement elementImage = gNode.firstChildElement("image");
        if (!elementImage.isNull()) {
            PixmapShape *pixmapShape = new PixmapShape();

            qreal x = elementImage.attribute("x").toFloat();
            qreal y = elementImage.attribute("y").toFloat();
            pixmapShape->setPos(x, y);

            qreal width = elementImage.attribute("width").toFloat();
            qreal height = elementImage.attribute("height").toFloat();
            QPixmap pixmap(width, height);
            QString imageData = elementImage.attribute("xlink:href");
            imageData.replace(QString("data:image/png;base64,"), QString(""));
            const QByteArray &pixmapArray = QByteArray::fromBase64(imageData.toLatin1());
            pixmap.loadFromData(pixmapArray);
            pixmapShape->setPixmap(pixmap);

            QDomElement gElement = gNode.toElement();
// Tronsfomation
            QString transStr = gElement.attribute("transform");
            transStr.replace(QString("matrix("), QString(""));
            transStr.replace(QString(")"), QString(""));
            QStringList transList(transStr.split(","));
            qreal m11{transList.at(0).toFloat()};   // Horizontal scaling
            qreal m12{transList.at(1).toFloat()};   // Vertical shearing
            qreal m21{transList.at(2).toFloat()};   // Horizontal shearing
            qreal m22{transList.at(3).toFloat()};   // Vertical scaling
            qreal m31{transList.at(4).toFloat()};   // Horizontal position (dx)
            qreal m32{transList.at(5).toFloat()};   // Vertical position (dy)
            QTransform transformation(m11, m12, m21, m22, m31, m32);
            pixmapShape->setTransform(transformation);

            itemList.append(pixmapShape);
            continue;
        }
    }

    file.close();
    return itemList;
}
