#ifndef CURVERESIZER_H
#define CURVERESIZER_H

#include "sizegripitem.h"


class CurveResizer : public SizeGripItem::Resizer
{
public:
    void operator()(QGraphicsItem *item, const QVariant &path) override;
};

#endif // CURVERESIZER_H
