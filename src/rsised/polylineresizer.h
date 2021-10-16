#ifndef POLYLINERESIZER_H
#define POLYLINERESIZER_H

#include "sizegripitem.h"

class PolylineResizer : public SizeGripItem::Resizer
{
public:
    virtual void operator()(QGraphicsItem *item, const QVariant &path);
};


#endif // POLYLINERESIZER_H
