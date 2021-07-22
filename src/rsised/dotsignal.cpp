#include "dotsignal.h"

#include <QBrush>
#include <QGraphicsSceneMouseEvent>

Dotsignal::Dotsignal(QGraphicsItem *parentItem, QObject *parent) : QObject(parent)
{
    setParentItem(parentItem);
    setAcceptHoverEvents(true);
    setFlag(ItemIsSelectable, true);
    setBrush(QBrush(Qt::black));
    setRect(-4, -4, 8, 8);
    setDotFlag(DotFlag::None);
    setVisible(false);
}

Dotsignal::Dotsignal(QPointF pos, QGraphicsItem *parentItem, QObject *parent) : QObject(parent)
{
    setParentItem(parentItem);
    setFlag(ItemIsSelectable, true);
    setAcceptHoverEvents(true);
    setBrush(QBrush(Qt::black));
    setRect(-4, -4, 8, 8);
    setPos(pos);
    setPreviousPosition(pos);
    setDotFlag(DotFlag::None);
    setVisible(false);
}

Dotsignal::~Dotsignal()
{

}

QPointF Dotsignal::previousPosition() const
{
    return m_previousPosition;
}

void Dotsignal::setPreviousPosition(const QPointF previousPosition)
{
    if (m_previousPosition == previousPosition) {
        return;
    }

    m_previousPosition = previousPosition;
    emit previousPositionChanged();
}

void Dotsignal::setDotFlag(DotFlag flag)
{
    m_flag = flag;
}

void Dotsignal::mousePressEvent(QGraphicsSceneMouseEvent *mouseEvent)
{
    if (m_flag == DotFlag::None) {
        setPreviousPosition(mouseEvent->scenePos());
    } else {
        QGraphicsItem::mousePressEvent(mouseEvent);
    }
}
void Dotsignal::mouseMoveEvent(QGraphicsSceneMouseEvent *mouseEvent)
{
    if (m_flag == DotFlag::Movable) {
        qreal dx = mouseEvent->scenePos().x() - m_previousPosition.x();
        qreal dy = mouseEvent->scenePos().y() - m_previousPosition.y();
        moveBy(dx, dy);
        setPreviousPosition(mouseEvent->scenePos());

        emit signalMove(this, dx, dy);
    } else {
        QGraphicsItem::mouseMoveEvent(mouseEvent);
    }
}

void Dotsignal::mouseReleaseEvent(QGraphicsSceneMouseEvent *mouseEvent)
{
    emit signalMouseRelease();
    QGraphicsItem::mouseReleaseEvent(mouseEvent);
}

void Dotsignal::hoverEnterEvent(QGraphicsSceneHoverEvent *hoverEvent)
{
    Q_UNUSED(hoverEvent)
    setBrush(QBrush(Qt::red));
}

void Dotsignal::hoverLeaveEvent(QGraphicsSceneHoverEvent *hoverEvent)
{
    Q_UNUSED(hoverEvent)
    setBrush(QBrush(Qt::black));
}
