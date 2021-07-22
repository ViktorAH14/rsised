#ifndef DOTSIGNAL_H
#define DOTSIGNAL_H

#include <QObject>
#include <QGraphicsRectItem>

QT_BEGIN_NAMESPACE
class QGraphicsSceneMouseEvent;
class QGraphicsSceneHoverEvent;
QT_END_NAMESPACE

class Dotsignal : public QObject, public QGraphicsRectItem
{
    Q_OBJECT
    Q_PROPERTY(QPointF previousPosition READ previousPosition WRITE setPreviousPosition NOTIFY previousPositionChanged)


    enum class DotFlag{None, Movable};

public:
    explicit Dotsignal(QGraphicsItem *parentItem = nullptr, QObject *parent = nullptr);
    explicit Dotsignal(QPointF pos, QGraphicsItem *parentItem = nullptr, QObject *parent = nullptr);
    ~Dotsignal();

    QPointF previousPosition() const;
    void setPreviousPosition(const QPointF previousPosition);
    void setDotFlag(DotFlag flag);

signals:
    void previousPositionChanged();
    void signalMouseRelease();
    void signalMove(QGraphicsItem *signalOwner, qreal dx, qreal dy);

protected:
    void mousePressEvent(QGraphicsSceneMouseEvent *mouseEvent) override;
    void mouseMoveEvent(QGraphicsSceneMouseEvent *mouseEvent) override;
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *mouseEvent) override;
    void hoverEnterEvent(QGraphicsSceneHoverEvent *hoverEvent) override;
    void hoverLeaveEvent(QGraphicsSceneHoverEvent *hoverEvent) override;

private:
    DotFlag m_flag;
    QPointF m_previousPosition;

};

#endif // DOTSIGNAL_H
