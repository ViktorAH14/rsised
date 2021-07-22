#ifndef RECTANGLE_H
#define RECTANGLE_H

#include <QObject>
#include <QGraphicsRectItem>

class Dotsignal;

QT_BEGIN_NAMESPACE
class QGraphicsSceneMouseEvent;
class QGraphicsSceneHoverEvent;
QT_END_NAMESPACE

class Rectangle : public QObject, public QGraphicsRectItem
{
    Q_OBJECT
    Q_PROPERTY(QPointF previousPosition READ previousPosition WRITE setPreviousPosition NOTIFY previousPosition)

    enum { Type = UserType + 1 };
    enum ActionType { Resize = 0x01, Rotation = 0x02 };
    enum CornerGrabbers { GrTop, GrBottom, GrLeft, GrRight,
                          GrTopLeft, GrTopRight, GrBottomLeft, GrBottomRight };
    enum CornerFlags
    {
        Move,
        Top,
        Bottom,
        Left,
        Right,
        TopLeft,
        TopRight,
        BottomLeft,
        BottomRight
    };

public:
    explicit Rectangle(QObject *parent = 0);
    ~Rectangle();

    QPointF previousPosition() const;
    void setPreviousPosition(const QPointF previousPosition);

    void setRect(qreal x, qreal y, qreal w, qreal h);
    void setRect(const QRectF rect);

signals:
    void rectChanged(Rectangle *rect);
    void previousPositionChanged();
    void clicked(Rectangle *rect);
    void signalMove(QGraphicsItem *item, qreal dx, qreal dy);



protected:
    void mouseDoubleClickEvent(QGraphicsSceneMouseEvent *mouseEvent) override;
    void mousePressEvent(QGraphicsSceneMouseEvent *mouseEvent) override;
    void mouseMoveEvent(QGraphicsSceneMouseEvent *mouseEvent) override;
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *mouseEvent) override;
    void hoverEnterEvent(QGraphicsSceneHoverEvent *hoverEvent) override;
    void hoverMoveEvent(QGraphicsSceneHoverEvent *hoverEvent) override;
    void hoverLeaveEvent(QGraphicsSceneHoverEvent *hoverEvent) override;

    QVariant itemChange(GraphicsItemChange change, const QVariant &value) override;

private:
    Dotsignal *cornerGrabber[8];
    QPointF m_previousPosition;
    bool m_leftMouseButtonPressed;
    unsigned int m_actionType;
    unsigned int m_cornerFlag;

    void resizeLeft(const QPointF &currentPoint);
    void resizeRight(const QPointF &currentPoint);
    void resizeBottom(const QPointF &currentPoint);
    void resizeTop(const QPointF &currentPoint);
    void rotateItem(const QPointF &currentPoint);

    void setPositionGrabbers();
    void setVisibilityGrabbers();
    void hideGrabbers();
};

#endif // RECTANGLE_H
