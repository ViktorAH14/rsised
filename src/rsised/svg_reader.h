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

    QRectF getSize(const QString &fileName) const;
    QList<QGraphicsItem *> getElements(const QString &fileName);

private:
    enum class PathType{ Polyline, Curve };
    QMenu   *m_itemMenu;
    PathType currentPathType;
};

#endif // SVG_READER_H
