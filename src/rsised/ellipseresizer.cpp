#include "ellipseresizer.h"
#include "ellipse.h"

void EllipseResizer::operator()(QGraphicsItem *item, const QRectF &rect)
{
    Ellipse *ellipseItem = dynamic_cast<Ellipse *>(item);
    if (ellipseItem) {
        ellipseItem->setRect(rect);
    }
}
