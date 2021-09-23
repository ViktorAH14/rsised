#include "ellipseresizer.h"

void EllipseResizer::operator()(QGraphicsItem *item, const QRectF &rect)
            {
                QGraphicsEllipseItem* ellipseItem =
                    dynamic_cast<QGraphicsEllipseItem*>(item);

                if (ellipseItem)
                {
                    ellipseItem->setRect(rect);
                }
            }
