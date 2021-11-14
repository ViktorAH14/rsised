#ifndef PIXMAPRESIZER_H
#define PIXMAPRESIZER_H

#include "sizegripitem.h"

class PixmapResizer : public SizeGripItem::Resizer
{
public:
    void operator()(QGraphicsItem *item, const QVariant &rect) override;
};

#endif // PIXMAPRESIZER_H
