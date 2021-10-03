#include "rse_writer.h"
#include "rectangle.h"
#include "ellipse.h"

#include <QXmlStreamWriter>
#include <QGraphicsItem>
#include <QPen>

RSEwriter::RSEwriter()
{
}

void RSEwriter::writeRSE(QIODevice *file, const QList<QGraphicsItem *> items)
{
    QXmlStreamWriter RSEwriter(file);
    RSEwriter.setAutoFormatting(true);
    RSEwriter.writeStartDocument();
    RSEwriter.writeStartElement("RSiSedData");
    RSEwriter.writeAttribute("version", "v0.1");
    RSEwriter.writeStartElement("ItemsList");
    for (QGraphicsItem *item : qAsConst(items)) {
        if (item->type() == Rectangle::Type) {
            Rectangle *rectangle = qgraphicsitem_cast<Rectangle *>(item);
            QRectF rect = rectangle->rect();
            RSEwriter.writeStartElement("rect");
            RSEwriter.writeAttribute("x", QString::number(rect.x()));
            RSEwriter.writeAttribute("y", QString::number(rect.y()));
            RSEwriter.writeAttribute("width", QString::number(rect.width()));
            RSEwriter.writeAttribute("height", QString::number(rect.height()));
            RSEwriter.writeAttribute("pen-color", rectangle->pen().color().name());
            RSEwriter.writeAttribute("pen-width", QString::number(rectangle->pen().width()));
            RSEwriter.writeAttribute("pen-style", QString::number(rectangle->pen().style()));
            RSEwriter.writeAttribute("brush-color", rectangle->brush().color().name());
            RSEwriter.writeAttribute("brush-style", QString::number(rectangle->brush().style()));
            RSEwriter.writeEndElement(); // rect
        }
        if (item->type() == Ellipse::Type) {
            Ellipse *ellipse = qgraphicsitem_cast<Ellipse *>(item);
            QRectF rect = ellipse->rect();
            RSEwriter.writeStartElement("ellipse");
            RSEwriter.writeAttribute("x", QString::number(rect.x()));
            RSEwriter.writeAttribute("y", QString::number(rect.y()));
            RSEwriter.writeAttribute("width", QString::number(rect.width()));
            RSEwriter.writeAttribute("height", QString::number(rect.height()));
            RSEwriter.writeAttribute("pen-color", ellipse->pen().color().name());
            RSEwriter.writeAttribute("pen-width", QString::number(ellipse->pen().width()));
            RSEwriter.writeAttribute("pen-style", QString::number(ellipse->pen().style()));
            RSEwriter.writeAttribute("brush-color", ellipse->brush().color().name());
            RSEwriter.writeAttribute("brush-style", QString::number(ellipse->brush().style()));
            RSEwriter.writeEndElement(); // ellipse
        }
        if (item->type() == QGraphicsLineItem::Type) {
            QGraphicsLineItem *lineItem = qgraphicsitem_cast<QGraphicsLineItem *>(item);
            RSEwriter.writeStartElement("line");
            RSEwriter.writeAttribute("x1", QString::number(lineItem->line().x1()));
            RSEwriter.writeAttribute("y1", QString::number(lineItem->line().y1()));
            RSEwriter.writeAttribute("x2", QString::number(lineItem->line().x2()));
            RSEwriter.writeAttribute("y2", QString::number(lineItem->line().y2()));
            RSEwriter.writeAttribute("pen-color", lineItem->pen().color().name());
            RSEwriter.writeAttribute("pen-width", QString::number(lineItem->pen().width()));
            RSEwriter.writeAttribute("pen-style", QString::number(lineItem->pen().style()));
            RSEwriter.writeEndElement(); // lineItem
        }
    }
    RSEwriter.writeEndElement(); // ItemList
    RSEwriter.writeEndElement(); // RSiSedData
    RSEwriter.writeEndDocument();
}
