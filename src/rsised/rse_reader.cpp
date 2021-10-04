#include "rse_reader.h"
#include "rectangle.h"
#include "ellipse.h"

#include <QXmlStreamReader>
#include <QPen>

RseReader::RseReader()
{
}

QRectF RseReader::getSceneRect(QIODevice *device)
{
    QRectF sceneRect;
    QXmlStreamReader rseSceneReader;
    rseSceneReader.setDevice(device);
    rseSceneReader.readNext();
    while (!rseSceneReader.atEnd()) {
        if (rseSceneReader.isStartElement()) {
            if (rseSceneReader.name() == "Scene") {
                qreal x{0.0};
                qreal y{0.0};
                qreal width{0.0};
                qreal height{0.0};
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

QList<QGraphicsItem *> RseReader::getElement(QIODevice *device)
{
    QList<QGraphicsItem *> itemList;
    QXmlStreamReader rseItemReader;
    rseItemReader.setDevice(device);
    rseItemReader.readNext();
    while (!rseItemReader.atEnd()) {
        if (rseItemReader.isStartElement()) {
            if (rseItemReader.name() == "rect") {
                Rectangle *rectangle = new Rectangle();
                rectangle->setFlag(QGraphicsItem::ItemSendsGeometryChanges, true);
                rectangle->setAcceptHoverEvents(true);
                qreal x{0.0};
                qreal y{0.0};
                qreal width{0.0};
                qreal height{0.0};
                qreal zValue{0.0};
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
                }
                rectangle->setRect(x, y, width, height);
                rectangle->setPen(itemPen);
                rectangle->setBrush(itemBrush);
                rectangle->setZValue(zValue);
                itemList.append(rectangle);
            }
            if (rseItemReader.name() == "ellipse") {
                Ellipse *ellipse = new Ellipse();
                ellipse->setFlag(QGraphicsItem::ItemSendsGeometryChanges, true);
                ellipse->setAcceptHoverEvents(true);
                qreal x{0.0};
                qreal y{0.0};
                qreal width{0.0};
                qreal height{0.0};
                qreal zValue{0.0};
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
                }
                ellipse->setRect(x, y, width, height);
                ellipse->setPen(itemPen);
                ellipse->setBrush(itemBrush);
                ellipse->setZValue(zValue);
                itemList.append(ellipse);
            }
            if (rseItemReader.name() == "line") {
                QGraphicsLineItem *line = new QGraphicsLineItem();
                line->setFlag(QGraphicsItem::ItemIsMovable, true);
                qreal x1{0.0};
                qreal y1{0.0};
                qreal x2{0.0};
                qreal y2{0.0};
                qreal zValue{0.0};
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
                }
                line->setLine(x1, y1, x2, y2);
                line->setPen(itemPen);
                line->setZValue(zValue);
                itemList.append(line);
            }
        }
        rseItemReader.readNext();
    }

    return itemList;
}
