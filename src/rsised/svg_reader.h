#ifndef SVG_READER_H
#define SVG_READER_H

#include <QGraphicsItem>

QT_BEGIN_MOC_NAMESPACE
class QMenu;
QT_END_NAMESPACE

class SvgReader
{
public:
    SvgReader(QMenu *itemMenu);

    QRectF getSize(const QString &fileName);
    QList<QGraphicsItem *> getElements(const QString &fileName);

private:
    QMenu   *itemMenu;
};

#endif // SVG_READER_H
