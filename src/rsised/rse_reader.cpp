#include "rse_reader.h"
#include "rectangle.h"
#include "ellipse.h"
#include "polyline.h"

#include <QXmlStreamReader>
#include <QPen>

RseReader::RseReader(QMenu *itemMenu) : itemMenu{itemMenu}
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

//NOTE refactoring
QList<QGraphicsItem *> RseReader::getElement(QIODevice *device)
{
    QList<QGraphicsItem *> itemList;
    QXmlStreamReader rseItemReader;
    rseItemReader.setDevice(device);
    rseItemReader.readNext();
    while (!rseItemReader.atEnd()) {
        if (rseItemReader.isStartElement()) {
            if (rseItemReader.name() == "rect") {
                Rectangle *rectangle = new Rectangle(itemMenu);
                qreal x{0.0};
                qreal y{0.0};
                qreal width{0.0};
                qreal height{0.0};
                qreal zValue{0.0};
                qreal m11{0.0};
                qreal m12{0.0};
                qreal m13{0.0};
                qreal m21{0.0};
                qreal m22{0.0};
                qreal m23{0.0};
                qreal m31{0.0};
                qreal m32{0.0};
                qreal m33{0.0};
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
                Ellipse *ellipse = new Ellipse(itemMenu);
                qreal x{0.0};
                qreal y{0.0};
                qreal width{0.0};
                qreal height{0.0};
                qreal zValue{0.0};
                qreal m11{0.0};
                qreal m12{0.0};
                qreal m13{0.0};
                qreal m21{0.0};
                qreal m22{0.0};
                qreal m23{0.0};
                qreal m31{0.0};
                qreal m32{0.0};
                qreal m33{0.0};
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
                qreal x1{0.0};
                qreal y1{0.0};
                qreal x2{0.0};
                qreal y2{0.0};
                qreal zValue{0.0};
                qreal m11{0.0};
                qreal m12{0.0};
                qreal m13{0.0};
                qreal m21{0.0};
                qreal m22{0.0};
                qreal m23{0.0};
                qreal m31{0.0};
                qreal m32{0.0};
                qreal m33{0.0};
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
                Polyline *polyline = new Polyline(itemMenu);
                QPainterPath path;
                QPen itemPen;
                qreal zValue{0.0};
                qreal m11{0.0};
                qreal m12{0.0};
                qreal m13{0.0};
                qreal m21{0.0};
                qreal m22{0.0};
                qreal m23{0.0};
                qreal m31{0.0};
                qreal m32{0.0};
                qreal m33{0.0};
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
        }
        rseItemReader.readNext();
    }

    return itemList;
}
