#ifndef RECTANGLERESIZER_H
#define RECTANGLERESIZER_H

#include "sizegripitem.h"

class RectangleResizer : public SizeGripItem::Resizer
{
public:
    void operator()(QGraphicsItem *item, const QVariant &rect) override;
};

#endif // RECTANGLERESIZER_H
