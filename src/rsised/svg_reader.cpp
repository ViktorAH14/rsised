#include "svg_reader.h"
#include "rectangle.h"
#include "ellipse.h"

#include <QDomDocument>
#include <QFile>
#include <QPen>

SvgReader::SvgReader()
{
}

QRectF SvgReader::getSize(const QString fileName)
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

QList<QGraphicsItem *> SvgReader::getElements(const QString fileName)
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
            Rectangle *rectangle = new Rectangle();
            rectangle->setFlag(QGraphicsItem::ItemSendsGeometryChanges, true);
            rectangle->setAcceptHoverEvents(true);
            rectangle->setRect(elementRect.attribute("x").toInt(),
                               elementRect.attribute("y").toInt(),
                               elementRect.attribute("width").toInt(),
                               elementRect.attribute("height").toInt());

            QDomElement gElement = gNode.toElement();
            QColor fillColor(gElement.attribute("fill", "#ffffff"));
            fillColor.setAlphaF(gElement.attribute("fill-opacity","0").toFloat());
            rectangle->setBrush(QBrush(fillColor));

            QColor strokeColor(gElement.attribute("stroke", "#000000"));
            strokeColor.setAlphaF(gElement.attribute("stroke-opacity").toFloat());
            rectangle->setPen(QPen(strokeColor,gElement.attribute("stroke-width", "0").toInt()));

            itemList.append(rectangle);
            continue;
        }

        QDomElement elementEllipse = gNode.firstChildElement("ellipse");
        if (!elementEllipse.isNull()) {
            Ellipse *ellipse = new Ellipse();
            ellipse->setFlag(QGraphicsItem::ItemSendsGeometryChanges, true);
            ellipse->setAcceptHoverEvents(true);

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
            QColor fillColor(gElement.attribute("fill", "ffffff"));
            ellipse->setBrush(QBrush(fillColor));
            QColor strokeColor(gElement.attribute("stroke", "000000"));
            ellipse->setPen(QPen(strokeColor, gElement.attribute("stroke-width", "0").toInt()));
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
            QColor strokeColor(gElement.attribute("stroke", "000000"));
            line->setPen(QPen(strokeColor, gElement.attribute("stroke-width", "0").toInt()));
            itemList.append(line);
            continue;
        }

        QDomElement elementPolyline = gNode.firstChildElement("polyline");
        if (!elementPolyline.isNull()) {
            QGraphicsPathItem *pathItem = new QGraphicsPathItem();
            pathItem->setFlag(QGraphicsItem::ItemIsMovable, true);

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
            pathItem->setPath(painterPath);
            QDomElement gElement = gNode.toElement();
            QColor strokeColor(gElement.attribute("stroke", "000000"));
            pathItem->setPen(QPen(strokeColor, gElement.attribute("stroke-width", "0").toInt()));
            itemList.append(pathItem);
            continue;
        }
    }

    file.close();
    return itemList;
}
