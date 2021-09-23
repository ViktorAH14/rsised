#include "rectangleresizer.h"
#include "rectangle.h"

void RectangleResizer::operator()(QGraphicsItem *item, const QRectF &rect)
{
    Rectangle *rectItem = dynamic_cast<Rectangle *>(item);
    if (rectItem) {
        rectItem->setRect(rect);
    }
}
