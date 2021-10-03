#ifndef RSEWRITER_H
#define RSEWRITER_H

#include <QGraphicsItem>

class RSEwriter
{
public:
    RSEwriter();

    void writeRSE(QIODevice *file, const QList<QGraphicsItem *> items);
};

#endif // RSEWRITER_H
