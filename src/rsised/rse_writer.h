#ifndef RSEWRITER_H
#define RSEWRITER_H

#include <QGraphicsItem>

class RseWriter
{
public:
    RseWriter();

    void writeRse(QIODevice *file, const QList<QGraphicsItem *> items, QRectF sceneRect);
};

#endif // RSEWRITER_H
