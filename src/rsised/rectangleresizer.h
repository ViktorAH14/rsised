#ifndef RECTANGLERESIZER_H
#define RECTANGLERESIZER_H

#include "sizegripitem.h"

class RectangleResizer : public SizeGripItem::Resizer
{
public:
    virtual void operator()(QGraphicsItem *item, const QRectF &rect);
};

#endif // RECTANGLERESIZER_H
