#include "rectangleresizer.h"
#include "rectangle.h"
#include "technics_shape.h"

void RectangleResizer::operator()(QGraphicsItem *item, const QVariant &rect)
{
    switch (item->type()) {
    case Rectangle::Type: {
        Rectangle *rectItem = dynamic_cast<Rectangle *>(item);
        if (rectItem) {
            QRectF itemRect = rect.toRectF();
            rectItem->setRect(itemRect);
        }
        break;
    }
    case TechnicsShape::Type: {
        TechnicsShape *technicsShape = dynamic_cast<TechnicsShape *>(item);
        if (technicsShape) {
            technicsShape->scaleTechnicsShape(rect.toRectF());
        }
        break;
    }
    default:
        break;
    }
}
