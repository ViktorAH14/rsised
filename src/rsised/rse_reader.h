#ifndef RSEREADER_H
#define RSEREADER_H

#include <QGraphicsItem>


class RseReader
{
public:
    RseReader();

    QRectF getSceneRect(QIODevice *device);
    QList<QGraphicsItem *> getElement(QIODevice *device);
};

#endif // RSEREADER_H
