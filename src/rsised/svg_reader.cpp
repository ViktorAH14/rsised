#include "svg_reader.h"
#include "rectangle.h"
#include "ellipse.h"
#include "polyline.h"

#include <QDomDocument>
#include <QFile>
#include <QPen>

SvgReader::SvgReader(QMenu *itemMenu) : itemMenu{itemMenu}
{
}

QRectF SvgReader::getSize(const QString &fileName)
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

// NOTE refactoring
// NOTE возможны конфликты между path и polyline
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
            Rectangle *rectangle = new Rectangle(itemMenu);
// Position and size
            rectangle->setRect(elementRect.attribute("x").toInt(),
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
                rectangle->setBrush(QBrush(fillColor, brushStyle));
            } else {
                QColor fillColor(gElement.attribute("fill", "#ffffff"));
                fillColor.setAlphaF(gElement.attribute("fill-opacity","0").toFloat());
                rectangle->setBrush(QBrush(fillColor, Qt::SolidPattern));
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
            rectangle->setPen(QPen(strokeColor, strokeWidth, penStyle));
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
            rectangle->setTransform(transformation);

            itemList.append(rectangle);
            continue;
        }

        QDomElement elementEllipse = gNode.firstChildElement("ellipse");
        if (!elementEllipse.isNull()) {
            Ellipse *ellipse = new Ellipse(itemMenu);
// Position and size
            qreal cx = elementEllipse.attribute("cx").toFloat();
            qreal cy = elementEllipse.attribute("cy").toFloat();
            qreal rx = elementEllipse.attribute("rx").toFloat();
            qreal ry = elementEllipse.attribute("ry").toFloat();
            qreal x = cx - rx;
            qreal y = cy - ry;
            qreal width = rx * 2;
            qreal height = ry * 2;
            ellipse->setRect(x, y, width, height);

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
                ellipse->setBrush(QBrush(fillColor, brushStyle));
            } else {
                QColor fillColor(gElement.attribute("fill", "#ffffff"));
                fillColor.setAlphaF(gElement.attribute("fill-opacity","0").toFloat());
                ellipse->setBrush(QBrush(fillColor, Qt::SolidPattern));
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
            ellipse->setPen(QPen(strokeColor, strokeWidth, penStyle));
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
            ellipse->setTransform(transformation);

            itemList.append(ellipse);
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

        QDomElement elementPolyline = gNode.firstChildElement("polyline");
        if (!elementPolyline.isNull()) {
            QGraphicsPathItem *polyline = new QGraphicsPathItem();
            polyline->setFlag(QGraphicsItem::ItemIsMovable, true);

            QStringList listDotes = elementPolyline.attribute("points").split(" ");
            listDotes.removeLast();
            QString firstDotes = listDotes.at(0);
            QStringList listFirstDotes = firstDotes.split(",");
            QPainterPath painterPath;
            painterPath.moveTo(listFirstDotes.at(0).toFloat(), listFirstDotes.at(1).toFloat());
            for (int i = 1; i < listDotes.length(); i++) {
                QString dotes = listDotes.at(i);
                QStringList nextDotes = dotes.split(",");
                painterPath.lineTo(nextDotes.at(0).toFloat(), nextDotes.at(1).toFloat());
            }
            polyline->setPath(painterPath);
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
            polyline->setPen(QPen(strokeColor, strokeWidth, penStyle));
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
            polyline->setTransform(transformation);

            itemList.append(polyline);
            continue;
        }

        QDomElement elementPath = gNode.firstChildElement("path");
        if (!elementPath.isNull()) {
            Polyline *polylineItem = new Polyline(itemMenu);
            QPainterPath path;
            QStringList listDotes = elementPath.attribute("d").split(" ");
            QString first = listDotes.at(0);
            QStringList firstElement = first.replace(QString("M"), QString("")).split(",");
            path.moveTo(firstElement.at(0).toInt(), firstElement.at(1).toInt());
            for (int i = 1; i < listDotes.length(); i++) {
                QString other = listDotes.at(i);
                QStringList dot = other.replace(QString("L"), QString("")).split(",");
                path.lineTo(dot.at(0).toInt(), dot.at(1).toInt());
            }
            polylineItem->setPath(path);
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
            polylineItem->setPen(QPen(strokeColor, strokeWidth, penStyle));
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
            polylineItem->setTransform(transformation);

            itemList.append(polylineItem);
            continue;
        }
    }

    file.close();
    return itemList;
}
