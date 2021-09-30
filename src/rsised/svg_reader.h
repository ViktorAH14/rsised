#ifndef SVG_READER_H
#define SVG_READER_H

#include <QGraphicsItem>

class SVGreader
{
public:
    SVGreader();

    static QRectF getSize(const QString filePath);
    static QList<QGraphicsItem *> getElements(const QString filePath);
};

#endif // SVG_READER_H
