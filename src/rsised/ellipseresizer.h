#ifndef ELLIPSERESIZER_H
#define ELLIPSERESIZER_H

#include "sizegripitem.h"


class EllipseResizer : public SizeGripItem::Resizer
{
public:
    void operator()(QGraphicsItem *item, const QVariant &rect) override;

};

#endif // ELLIPSERESIZER_H
