#include "curveresizer.h"
#include "curve.h"

#include <QPainterPath>

Q_DECLARE_METATYPE(QPainterPath)

void CurveResizer::operator()(QGraphicsItem *item, const QVariant &path)
{
    Curve *curveItem = dynamic_cast<Curve *>(item);
    if (curveItem) {
        QPainterPath itemPath = path.value<QPainterPath>();
        curveItem->setPath(itemPath);
    }
}
