#include "ellipseresizer.h"
#include "ellipse.h"

void EllipseResizer::operator()(QGraphicsItem *item, const QVariant &rect)
{
    Ellipse *ellipseItem = dynamic_cast<Ellipse *>(item);
    if (ellipseItem) {
        QRectF itemRect = rect.toRectF();
        ellipseItem->setRect(itemRect);
    }
}
