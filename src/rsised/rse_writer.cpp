#include "rse_writer.h"
#include "rectangle.h"
#include "ellipse.h"
#include "polyline.h"
#include "curve.h"

#include <QXmlStreamWriter>
#include <QGraphicsItem>
#include <QPen>

RseWriter::RseWriter()
{
}

void RseWriter::writeRse(QIODevice *file, const QList<QGraphicsItem *> items, QRectF sceneRect)
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
        if (item->type() == Rectangle::Type) {
            Rectangle *rectangle = qgraphicsitem_cast<Rectangle *>(item);
            QRectF rect(rectangle->rect());
            QTransform trans(rectangle->sceneTransform());
            QString transStr(QString::number(trans.m11()) + "," + QString::number(trans.m12())
                             + "," + QString::number(trans.m13()) + ","
                             + QString::number(trans.m21()) + "," + QString::number(trans.m22())
                             + "," + QString::number(trans.m23()) + ","
                             + QString::number(trans.m31()) + "," + QString::number(trans.m32())
                             + "," + QString::number(trans.m33()));
            rseWriter.writeStartElement("rect");
            rseWriter.writeAttribute("x", QString::number(rect.x()));
            rseWriter.writeAttribute("y", QString::number(rect.y()));
            rseWriter.writeAttribute("width", QString::number(rectangle->rect().width()));
            rseWriter.writeAttribute("height", QString::number(rectangle->rect().height()));
            rseWriter.writeAttribute("pen-color", rectangle->pen().color().name());
            rseWriter.writeAttribute("pen-width", QString::number(rectangle->pen().width()));
            rseWriter.writeAttribute("pen-style", QString::number(rectangle->pen().style()));
            rseWriter.writeAttribute("brush-color", rectangle->brush().color().name());
            rseWriter.writeAttribute("brush-style", QString::number(rectangle->brush().style()));
            rseWriter.writeAttribute("z", QString::number(rectangle->zValue()));
            rseWriter.writeAttribute("transform", transStr);
            rseWriter.writeEndElement(); // rect
        }
        if (item->type() == Ellipse::Type) {
            Ellipse *ellipse = qgraphicsitem_cast<Ellipse *>(item);
            QRectF rect = ellipse->rect();
            QTransform trans(ellipse->sceneTransform());
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
            rseWriter.writeAttribute("pen-color", ellipse->pen().color().name());
            rseWriter.writeAttribute("pen-width", QString::number(ellipse->pen().width()));
            rseWriter.writeAttribute("pen-style", QString::number(ellipse->pen().style()));
            rseWriter.writeAttribute("brush-color", ellipse->brush().color().name());
            rseWriter.writeAttribute("brush-style", QString::number(ellipse->brush().style()));
            rseWriter.writeAttribute("z", QString::number(ellipse->zValue()));
            rseWriter.writeAttribute("transform", transStr);
            rseWriter.writeEndElement(); // ellipse
        }
        if (item->type() == Polyline::Type) {
            Polyline *polyline = qgraphicsitem_cast<Polyline *>(item);
            QPainterPath linePath = polyline->path();
            QStringList dotList;
            for (int i = 0; i < linePath.elementCount(); i++) {
                dotList << QString::number(linePath.elementAt(i).x) + ","
                           + QString::number(linePath.elementAt(i).y);
            }
            rseWriter.writeStartElement("polyline");
            rseWriter.writeAttribute("m", dotList.at(0));
            QString dotLine;
            for (int i = 1; i < dotList.count(); i++) {
                dotLine += dotList.at(i) + " ";
            }
            dotLine.chop(1);
            QTransform trans(polyline->sceneTransform());
            QString transStr(QString::number(trans.m11()) + "," + QString::number(trans.m12())
                             + "," + QString::number(trans.m13()) + ","
                             + QString::number(trans.m21()) + "," + QString::number(trans.m22())
                             + "," + QString::number(trans.m23()) + ","
                             + QString::number(trans.m31()) + "," + QString::number(trans.m32())
                             + "," + QString::number(trans.m33()));
            rseWriter.writeAttribute("l", dotLine);
            rseWriter.writeAttribute("pen-color", polyline->pen().color().name());
            rseWriter.writeAttribute("pen-width", QString::number(polyline->pen().width()));
            rseWriter.writeAttribute("pen-style", QString::number(polyline->pen().style()));
            rseWriter.writeAttribute("z", QString::number(polyline->zValue()));
            rseWriter.writeAttribute("transform", transStr);
            rseWriter.writeEndElement(); // polyline
        }
        if (item->type() == Curve::Type) {
            Curve *curve = qgraphicsitem_cast<Curve *>(item);
            QPainterPath curvePath = curve->path();
            QStringList dotList;
            for (int i = 0; i < curvePath.elementCount(); i++) {
                dotList << QString::number(curvePath.elementAt(i).x) + ","
                           + QString::number(curvePath.elementAt(i).y);
            }
            rseWriter.writeStartElement("curve");
            rseWriter.writeAttribute("m", dotList.at(0));
            QString dotLine;
            for (int i = 1; i < dotList.count(); i ++) {
                dotLine += dotList.at(i) + " ";
            }
            dotLine.chop(1);
            QTransform trans(curve->sceneTransform());
            QString transStr(QString::number(trans.m11()) + "," + QString::number(trans.m12())
                             + "," + QString::number(trans.m13()) + ","
                             + QString::number(trans.m21()) + "," + QString::number(trans.m22())
                             + "," + QString::number(trans.m23()) + ","
                             + QString::number(trans.m31()) + "," + QString::number(trans.m32())
                             + "," + QString::number(trans.m33()));
            rseWriter.writeAttribute("c", dotLine);
            rseWriter.writeAttribute("pen-color", curve->pen().color().name());
            rseWriter.writeAttribute("pen-width", QString::number(curve->pen().width()));
            rseWriter.writeAttribute("pen-style", QString::number(curve->pen().style()));
            rseWriter.writeAttribute("z", QString::number(curve->zValue()));
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
    }
    rseWriter.writeEndElement(); // ItemList
    rseWriter.writeEndElement(); // Scene
    rseWriter.writeEndElement(); // RSiSedData
    rseWriter.writeEndDocument();
}
