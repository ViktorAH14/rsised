#ifndef CURVERESIZER_H
#define CURVERESIZER_H

#include "sizegripitem.h"


class CurveResizer : public SizeGripItem::Resizer
{
public:
    virtual void operator()(QGraphicsItem *item, const QVariant &path);
};

#endif // CURVERESIZER_H
