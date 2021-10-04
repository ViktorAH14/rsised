#ifndef SVG_READER_H
#define SVG_READER_H

#include <QGraphicsItem>

class SvgReader
{
public:
    SvgReader();

    QRectF getSize(const QString fileName);
    QList<QGraphicsItem *> getElements(const QString fileName);
};

#endif // SVG_READER_H
