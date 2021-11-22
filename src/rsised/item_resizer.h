#ifndef ITEM_RESIZER_H
#define ITEM_RESIZER_H

#include "sizegripitem.h"

class ItemResizer : public SizeGripItem::Resizer
{
public:
    void operator()(QGraphicsItem *item, const QVariant &value) override;
};

#endif // ITEM_RESIZER_H
