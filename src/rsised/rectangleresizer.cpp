#include "rectangleresizer.h"
#include "rectangle.h"

void RectangleResizer::operator()(QGraphicsItem *item, const QVariant &rect)
{
    Rectangle *rectItem = dynamic_cast<Rectangle *>(item);
    if (rectItem) {
        QRectF itemRect = rect.toRectF();
        rectItem->setRect(itemRect);
    }
}
