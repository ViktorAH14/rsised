#include "rse_writer.h"
#include "rectangle.h"
#include "ellipse.h"
#include "polyline.h"
#include "curve.h"
#include "textitem.h"
#include "pixmapitem.h"
#include "technics_shape.h"
#include "device_shape.h"

#include <QXmlStreamWriter>
#include <QGraphicsItem>
#include <QPen>
#include <QTextDocument>
#include <QPixmap>
#include <QBuffer>

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
        if (item->type() == TextItem::Type) {
            TextItem *textItem = qgraphicsitem_cast<TextItem *>(item);
            rseWriter.writeStartElement("text");
            rseWriter.writeAttribute("x", QString::number(textItem->x()));
            rseWriter.writeAttribute("y", QString::number(textItem->y()));
            rseWriter.writeAttribute("font", textItem->font().family());
            rseWriter.writeAttribute("font-size", QString::number(textItem->font().pointSize()));
            rseWriter.writeAttribute("bold", QString::number(textItem->font().bold()));
            rseWriter.writeAttribute("italic", QString::number(textItem->font().italic()));
            rseWriter.writeAttribute("underline", QString::number(textItem->font().underline()));
            rseWriter.writeAttribute("color", textItem->defaultTextColor().name());
            rseWriter.writeAttribute("z", QString::number(textItem->zValue()));
            rseWriter.writeCharacters(textItem->document()->toPlainText());
            rseWriter.writeEndElement(); // textItem
        }
        if (item->type() == PixmapItem::Type) {
            PixmapItem *pixmapItem = qgraphicsitem_cast<PixmapItem *> (item);
            rseWriter.writeStartElement("pixmap");
            rseWriter.writeAttribute("x", QString::number(pixmapItem->scenePos().x()));
            rseWriter.writeAttribute("y", QString::number(pixmapItem->scenePos().y()));
            rseWriter.writeAttribute("width", QString::number(pixmapItem->pixmap().width()));
            rseWriter.writeAttribute("height", QString::number(pixmapItem->pixmap().height()));
            rseWriter.writeAttribute("z", QString::number(pixmapItem->zValue()));
            QTransform trans(pixmapItem->transform());
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
            pixmapItem->pixmap().save(&buffer, "png");
            const QString &strPixmap(pixmapArray.toBase64());
            rseWriter.writeCharacters(strPixmap);
            rseWriter.writeEndElement(); // pixmapitems
        }
        if (item->type() == TechnicsShape::Type) {
            TechnicsShape *technicsShapeItem = qgraphicsitem_cast<TechnicsShape *>(item);
            rseWriter.writeStartElement("technics_shape");
            rseWriter.writeAttribute("x", QString::number(technicsShapeItem->scenePos().x()));
            rseWriter.writeAttribute("y", QString::number(technicsShapeItem->scenePos().y()));
            TechnicsShape::ShapeType shapeType = technicsShapeItem->shapeType();
            rseWriter.writeAttribute("shape_type", QString::number(shapeType));
            rseWriter.writeAttribute("z", QString::number(technicsShapeItem->zValue()));
            QTransform transform(technicsShapeItem->transform());
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
            rseWriter.writeEndElement(); // technicsShapeItem
        }
        if (item->type() == DeviceShape::Type) {
            DeviceShape *deviceShapeItem = qgraphicsitem_cast<DeviceShape *>(item);
            rseWriter.writeStartElement("device_shape");
            rseWriter.writeAttribute("x", QString::number(deviceShapeItem->scenePos().x()));
            rseWriter.writeAttribute("y", QString::number(deviceShapeItem->scenePos().y()));
            DeviceShape::ShapeType shapeType = deviceShapeItem->shapeType();
            rseWriter.writeAttribute("shape_type", QString::number(shapeType));
            rseWriter.writeAttribute("z", QString::number(deviceShapeItem->zValue()));
            QTransform transform(deviceShapeItem->transform());
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
            rseWriter.writeEndElement(); // deviceShapeItem
        }
    }
    rseWriter.writeEndElement(); // ItemList
    rseWriter.writeEndElement(); // Scene
    rseWriter.writeEndElement(); // RSiSedData
    rseWriter.writeEndDocument();
}
