#include "rectangle.h"
#include "dotsignal.h"

#include <math.h>

#include <QGraphicsSceneMouseEvent>
#include <QCursor>
#include <QBrush>

static const double PI = 3.14159265358979323846264338327950288419717;
static double TWO_PI = 2.0 * PI;

static qreal normalizeAngle(qreal angle)
{
    while (angle < 0) {
        angle += TWO_PI;
    }
    while (angle > TWO_PI) {
        angle -= TWO_PI;
    }
    return angle;
}

Rectangle::Rectangle(QObject *parent) : QObject(parent), m_actionType(Resize), m_cornerFlag(Move)
{
    setAcceptHoverEvents(true);
    setFlags(ItemIsSelectable | ItemSendsGeometryChanges);

    for (int i = 0; i < 8; i++) {
        cornerGrabber[i] = new Dotsignal(this);
    }
    setPositionGrabbers();
}
Rectangle::~Rectangle()
{
    for (int i = 0; i <8; i++) {
        delete cornerGrabber[i];
    }
}

QPointF Rectangle::previousPosition() const
{
    return m_previousPosition;
}

void Rectangle::setPreviousPosition(const QPointF previousPosition)
{
    if (m_previousPosition == previousPosition) {
        return;
    }
    m_previousPosition = previousPosition;
    emit previousPositionChanged();
}

void Rectangle::setRect(qreal x, qreal y, qreal w, qreal h)
{
    setRect(QRectF(x, y, w, h));
    setPositionGrabbers();
}

void Rectangle::setRect(const QRectF rect)
{
    QGraphicsRectItem::setRect(rect);
    setPositionGrabbers();
}

void Rectangle::mouseDoubleClickEvent(QGraphicsSceneMouseEvent *mouseEvent)
{
    m_actionType = (m_actionType == Resize) ? Rotation : Resize;
    setVisibilityGrabbers();

    QGraphicsItem::mouseDoubleClickEvent(mouseEvent);
}

void Rectangle::mousePressEvent(QGraphicsSceneMouseEvent *mouseEvent)
{
    setFiltersChildEvents(true);
    if (mouseEvent->button() == Qt::LeftButton) {
        m_leftMouseButtonPressed =true;
        setPreviousPosition(mouseEvent->scenePos());
        emit clicked(this);
    }

     QGraphicsItem::mousePressEvent( mouseEvent );
}

void Rectangle::mouseMoveEvent(QGraphicsSceneMouseEvent *mouseEvent)
{
    QPointF currentPos = mouseEvent->pos();

    if (m_actionType == Resize) {
        switch (m_cornerFlag) {
        case Top:
            resizeTop(currentPos);
            break;
        case Bottom:
            resizeBottom(currentPos);
            break;
        case Left:
            resizeLeft(currentPos);
            break;
        case Right:
            resizeRight(currentPos);
            break;
        case TopLeft:
            resizeTop(currentPos);
            resizeLeft(currentPos);
            break;
        case TopRight:
            resizeTop(currentPos);
            resizeRight(currentPos);
            break;
        case BottomLeft:
            resizeBottom(currentPos);
            resizeLeft(currentPos);
            break;
        case BottomRight:
            resizeBottom(currentPos);
            resizeRight(currentPos);
            break;
        default:
            if (m_leftMouseButtonPressed) {
//                setCursor(Qt::ClosedHandCursor);
                qreal dx = mouseEvent->scenePos().x() - m_previousPosition.x();
                qreal dy = mouseEvent->scenePos().y() -m_previousPosition.y();
                moveBy(dx, dy);
                setPreviousPosition(mouseEvent->scenePos());
                emit signalMove(this, dx, dy);
            }
            break;

        }
    } else {
        switch (m_cornerFlag) {
        case TopLeft:
        case TopRight:
        case BottomLeft:
        case BottomRight:
        {
            rotateItem(currentPos);
            break;
        }
        default:
            if (m_leftMouseButtonPressed) {
//                setCursor(Qt::ClosedHandCursor);
                qreal dx = mouseEvent->scenePos().x() - m_previousPosition.x();
                qreal dy = mouseEvent->scenePos().y() -m_previousPosition.y();
                moveBy(dx, dy);
                setPreviousPosition(mouseEvent->scenePos());
                emit signalMove(this, dx, dy);
            }
            break;

        }
    }

    QGraphicsItem::mouseMoveEvent( mouseEvent );

}

void Rectangle::mouseReleaseEvent(QGraphicsSceneMouseEvent *mouseEvent)
{
    if (mouseEvent->button() == Qt::LeftButton) {
        m_leftMouseButtonPressed = false;
        unsetCursor();
    }
    setFiltersChildEvents(false);

    QGraphicsItem::mouseReleaseEvent(mouseEvent);
}

void Rectangle::hoverEnterEvent(QGraphicsSceneHoverEvent *hoverEvent)
{
//    setFiltersChildEvents(true);
//    if (filtersChildEvents()) {
//        setBrush(QBrush(Qt::green));
//    }

        setPositionGrabbers();
        setVisibilityGrabbers();

    QGraphicsItem::hoverEnterEvent(hoverEvent);
}

void Rectangle::hoverMoveEvent(QGraphicsSceneHoverEvent *hoverEvent)
{
    QPointF currentPos = hoverEvent->pos();

    qreal drx = currentPos.x() - rect().right();
    qreal dlx = currentPos.x() - rect().left();
    qreal dty = currentPos.y() - rect().top();
    qreal dby = currentPos.y() - rect().bottom();

    if (dty < 7 && dty > -7) {
        m_cornerFlag = Top;
        setCursor(Qt::SizeVerCursor);
    } else if (dby < 7 && dby > -7) {
        m_cornerFlag = Bottom;
        setCursor(Qt::SizeVerCursor);
    } else if (drx < 7 && drx > -7) {
        m_cornerFlag = Right;
        setCursor(Qt::SizeHorCursor);
    } else if (dlx < 7 && dlx > -7) {
        m_cornerFlag = Left;
        setCursor(Qt::SizeHorCursor);
    }

//    if (cornerGrabber[GrTopLeft]->isUnderMouse()) {
//        setBrush(QBrush(Qt::blue));
//        m_cornerFlag = TopLeft;
//        setCursor(Qt::SizeFDiagCursor);
//    }

//    if (m_actionType == Resize) {
//        QPixmap cursor(":images/icons/cursor.png");
//        QPixmap resCursor;
//        QTransform trans = transform();
//        switch (m_cornerFlag) {
//        case Top:
//        case Bottom:
//            resCursor = cursor.transformed(trans);
//            setCursor(resCursor.scaled(24, 24, Qt::KeepAspectRatio));
//            break;
//        case Left:
//        case Right:
//            trans.rotate(90);
//            resCursor = cursor.transformed(trans);
//            setCursor(resCursor.scaled(24, 24, Qt::KeepAspectRatio));
//            break;
//        case TopRight:
//        case BottomLeft:
//            trans.rotate(45);
//            resCursor = cursor.transformed(trans);
//            setCursor(resCursor.scaled(24, 24, Qt::KeepAspectRatio));
//            break;
//        case TopLeft:
//        case BottomRight:
//            trans.rotate(135);
//            resCursor = cursor.transformed(trans);
//            setCursor(resCursor.scaled(24, 24, Qt::KeepAspectRatio));
//            break;
//        default:
//           setCursor(Qt::CrossCursor);
//            break;
//        }
//    } else {
//        switch (m_cornerFlag) {
//        case TopLeft:
//        case TopRight:
//        case BottomLeft:
//        case BottomRight:
//        {
//            QPixmap cursor(":images/icons/rotate.png");
//            setCursor(QCursor(cursor.scaled(40, 40, Qt::KeepAspectRatio)));
//            break;
//        }
//        default:
//            setCursor(Qt::CrossCursor);
//            break;
//        }
//    }

    QGraphicsItem::hoverMoveEvent(hoverEvent);
}

void Rectangle::hoverLeaveEvent(QGraphicsSceneHoverEvent *hoverEvent)
{
    m_cornerFlag = Move;
    hideGrabbers();
//    setFiltersChildEvents(false);
//    if (!filtersChildEvents()) {
//        setBrush(QBrush(Qt::yellow));
//    }
    unsetCursor();
    QGraphicsItem::hoverLeaveEvent(hoverEvent);
}

QVariant Rectangle::itemChange(GraphicsItemChange change, const QVariant &value)
{
    switch (change) {
    case QGraphicsItem::ItemSelectedChange:
        m_actionType = Resize;
        break;
    default:
        break;
    }

    return QGraphicsItem::itemChange(change, value);
}

void Rectangle::resizeLeft(const QPointF &currentPoint)
{
    QRectF newRect = rect();
    if (currentPoint.x() > newRect.right()) {
        return;
    }

    qreal widhtOffset = (currentPoint.x() - newRect.right());
    if (widhtOffset > -10) {
        return;
    }
    if (widhtOffset < 0) {
        newRect.setWidth(-widhtOffset);
    } else {
        newRect.setWidth(widhtOffset);
    }

    newRect.translate(rect().width() - newRect.width(), 0);
    prepareGeometryChange();
    setRect(newRect);
    update();
    setPositionGrabbers();
}

void Rectangle::resizeRight(const QPointF &currentPoint)
{
    QRectF newRect = rect();
    if (currentPoint.x() < newRect.left()) {
        return;
    }

    qreal widhtOffset = (currentPoint.x() - newRect.left());
    if (widhtOffset < 10) {
        return;
    }
    if (widhtOffset > 0) {
        newRect.setWidth(widhtOffset);
    } else {
        newRect.setWidth(-widhtOffset);
    }

    prepareGeometryChange();
    setRect(newRect);
    update();
    setPositionGrabbers();
}

void Rectangle::resizeBottom(const QPointF &currentPoint)
{
    QRectF newRect = rect();
    if (currentPoint.y() < newRect.top()) {
        return;
    }

    qreal heightOffset = (currentPoint.y() - newRect.top());
    if (heightOffset < 10) {
        return;
    }
    if (heightOffset > 0) {
        newRect.setHeight(heightOffset);
    } else {
        newRect.setHeight(-heightOffset);
    }

    prepareGeometryChange();
    setRect(newRect);
    update();
    setPositionGrabbers();
}

void Rectangle::resizeTop(const QPointF &currentPoint)
{
    QRectF newRect = rect();
    if (currentPoint.y() > newRect.bottom()) {
        return;
    }

    qreal heightOffset = (currentPoint.y() - newRect.bottom());
    if (heightOffset > -10) {
        return;
    }
    if (heightOffset < 0) {
        newRect.setHeight(-heightOffset);
    } else {
        newRect.setHeight(heightOffset);
    }

    newRect.translate(0, rect().height() - newRect.height());
    prepareGeometryChange();
    setRect(newRect);
    update();
    setPositionGrabbers();
}

void Rectangle::rotateItem(const QPointF &currentPoint)
{
    QRectF newRect = rect();
    QPointF center = boundingRect().center();
    QPointF corner;

    switch (m_cornerFlag) {
    case TopLeft:
        corner = newRect.topLeft();
        break;
    case TopRight:
        corner = newRect.topRight();
        break;
    case BottomLeft:
        corner = newRect.bottomLeft();
        break;
    case BottomRight:
        corner = newRect.bottomRight();
        break;
    default:
        break;
    }

    QLineF lineToTarget(center, corner);
    QLineF lineToCursor(center, currentPoint);

    qreal angleToTarget = ::acos(lineToTarget.dx() / lineToTarget.length());
    qreal angleToCursor = ::acos(lineToCursor.dx() / lineToCursor.length());

    if (lineToTarget.dy() < 0) {
        angleToTarget = TWO_PI - angleToTarget;
    }
    angleToTarget = normalizeAngle((PI - angleToTarget) + PI / 2);

    if (lineToCursor.dy() < 0) {
        angleToCursor = TWO_PI - angleToCursor;
    }
    angleToCursor = normalizeAngle((PI - angleToCursor) + PI / 2);

    qreal resultAngle = angleToTarget - angleToCursor;

    QTransform trans = transform();
    trans.translate(center.x(), center.y());
    trans.rotateRadians(rotation() + resultAngle, Qt::ZAxis);
    trans.translate(-center.x(), -center.y());
    setTransform(trans);
}



void Rectangle::setPositionGrabbers()
{
    cornerGrabber[GrTop]->setPos(rect().left() + rect().width()/2, rect().top());
    cornerGrabber[GrBottom]->setPos(rect().left() + rect().width()/2, rect().bottom());
    cornerGrabber[GrLeft]->setPos(rect().left(), rect().top() + rect().height()/2);
    cornerGrabber[GrRight]->setPos(rect().right(), rect().top() + rect().height()/2);
    cornerGrabber[GrTopLeft]->setPos(rect().left(), rect().top());
    cornerGrabber[GrTopRight]->setPos(rect().right(), rect().top());
    cornerGrabber[GrBottomLeft]->setPos(rect().left(), rect().bottom());
    cornerGrabber[GrBottomRight]->setPos(rect().right(), rect().bottom());
}

void Rectangle::setVisibilityGrabbers()
{    
    cornerGrabber[GrTopLeft]->setVisible(true);
    cornerGrabber[GrTopRight]->setVisible(true);
    cornerGrabber[GrBottomLeft]->setVisible(true);
    cornerGrabber[GrBottomRight]->setVisible(true);
    if (m_actionType == Resize) {
        cornerGrabber[GrTop]->setVisible(true);
        cornerGrabber[GrBottom]->setVisible(true);
        cornerGrabber[GrLeft]->setVisible(true);
        cornerGrabber[GrRight]->setVisible(true);
    }
}

void Rectangle::hideGrabbers()
{
    for (int i = 0; i < 8; i++) {
        cornerGrabber[i]->setVisible(false);
    }
}
