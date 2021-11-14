#ifndef RSEREADER_H
#define RSEREADER_H

#include <QGraphicsItem>

QT_BEGIN_NAMESPACE
class QMenu;
QT_END_MOC_NAMESPACE


class RseReader
{
public:
    RseReader(QMenu *itemMenu);

    QRectF getSceneRect(QIODevice *device) const;
    QList<QGraphicsItem *> getElement(QIODevice *device) const;

private:
    QMenu *m_itemMenu;
};

#endif // RSEREADER_H
