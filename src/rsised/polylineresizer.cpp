#include "polylineresizer.h"
#include "polyline.h"

#include <QPainterPath>

Q_DECLARE_METATYPE(QPainterPath)

void PolylineResizer::operator()(QGraphicsItem *item, const QVariant &path)
{
    Polyline *polylineItem = dynamic_cast<Polyline *>(item);
    if (polylineItem) {
        QPainterPath itemPath = path.value<QPainterPath>();
//        polylineItem->path().clear();
        polylineItem->setPath(itemPath);
    }
}
