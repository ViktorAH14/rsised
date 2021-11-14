#ifndef POLYLINERESIZER_H
#define POLYLINERESIZER_H

#include "sizegripitem.h"

class PolylineResizer : public SizeGripItem::Resizer
{
public:
    void operator()(QGraphicsItem *item, const QVariant &path) override;
};


#endif // POLYLINERESIZER_H
