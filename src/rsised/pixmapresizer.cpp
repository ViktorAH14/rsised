#include "pixmapresizer.h"
#include "pixmapitem.h"

void PixmapResizer::operator()(QGraphicsItem *item, const QVariant &rect)
{
    PixmapItem *pixmapItem = dynamic_cast<PixmapItem *>(item);
    if (pixmapItem) {
        pixmapItem->scalePixmap(rect.toRectF());
    }
}
