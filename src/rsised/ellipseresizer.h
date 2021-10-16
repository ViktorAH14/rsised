#ifndef ELLIPSERESIZER_H
#define ELLIPSERESIZER_H

#include "sizegripitem.h"


class EllipseResizer : public SizeGripItem::Resizer
{
public:
    virtual void operator()(QGraphicsItem *item, const QVariant &rect);

};

#endif // ELLIPSERESIZER_H
