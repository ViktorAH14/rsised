#include "rectangle.h"

#include <math.h>

#include <QApplication>
#include <QGraphicsSceneMouseEvent>
#include <QGraphicsSceneHoverEvent>
#include <QCursor>

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

Rectangle::Rectangle(QGraphicsItem *parent)
    : QGraphicsRectItem(parent),
      m_actionType {ActionType::Resize},
      m_cornerFlag {CornerFlags::None}
{
    setFlag(ItemSendsGeometryChanges, true);
}

Rectangle::Rectangle(QRectF rect, QGraphicsItem *parent)
    : QGraphicsRectItem(parent),
      m_actionType {ActionType::Resize},
      m_cornerFlag {CornerFlags::None}
{
    QGraphicsRectItem::setRect(rect);
    setFlag(ItemSendsGeometryChanges, true);
}
Rectangle::~Rectangle()
{
}

void Rectangle::mouseDoubleClickEvent(QGraphicsSceneMouseEvent *mouseEvent)
{
    m_actionType = (m_actionType == ActionType::Resize) ? ActionType::Rotation : ActionType::Resize;

    QGraphicsItem::mouseDoubleClickEvent(mouseEvent);
}

void Rectangle::mousePressEvent(QGraphicsSceneMouseEvent *mouseEvent)
{
    if ((m_cornerFlag == CornerFlags::None) && isSelected()) {
        QApplication::setOverrideCursor(Qt::ClosedHandCursor);
    }

    QGraphicsItem::mousePressEvent( mouseEvent );
}

void Rectangle::mouseMoveEvent(QGraphicsSceneMouseEvent *mouseEvent)
{
    QPointF currentPos = mouseEvent->pos();

    if (m_actionType == ActionType::Resize) {
        switch (m_cornerFlag) {
        case CornerFlags::Top:
            resizeTop(currentPos);
            break;
        case CornerFlags::Bottom:
            resizeBottom(currentPos);
            break;
        case CornerFlags::Left:
            resizeLeft(currentPos);
            break;
        case CornerFlags::Right:
            resizeRight(currentPos);
            break;
        case CornerFlags::TopLeft:
            resizeTop(currentPos);
            resizeLeft(currentPos);
            break;
        case CornerFlags::TopRight:
            resizeTop(currentPos);
            resizeRight(currentPos);
            break;
        case CornerFlags::BottomLeft:
            resizeBottom(currentPos);
            resizeLeft(currentPos);
            break;
        case CornerFlags::BottomRight:
            resizeBottom(currentPos);
            resizeRight(currentPos);
            break;
        default:
            if (mouseEvent->buttons() == Qt::LeftButton) {
                qreal dx = mouseEvent->scenePos().x() - mouseEvent->lastScenePos().x();
                qreal dy = mouseEvent->scenePos().y() - mouseEvent->lastScenePos().y();
                moveBy(dx, dy);
            }
            break;

        }
    } else {
        switch (m_cornerFlag) {
        case CornerFlags::TopLeft:
        case CornerFlags::TopRight:
        case CornerFlags::BottomLeft:
        case CornerFlags::BottomRight:
        {
            rotateItem(currentPos);
            break;
        }
        default:
            if (mouseEvent->buttons() == Qt::LeftButton) {
                qreal dx = mouseEvent->scenePos().x() - mouseEvent->lastScenePos().x();
                qreal dy = mouseEvent->scenePos().y() - mouseEvent->lastScenePos().y();
                moveBy(dx, dy);
            }
            break;

        }
    }

    QGraphicsItem::mouseMoveEvent( mouseEvent );

}

void Rectangle::mouseReleaseEvent(QGraphicsSceneMouseEvent *mouseEvent)
{
    QApplication::restoreOverrideCursor();

    QGraphicsItem::mouseReleaseEvent(mouseEvent);
}

void Rectangle::hoverEnterEvent(QGraphicsSceneHoverEvent *hoverEvent)
{

    QGraphicsItem::hoverEnterEvent(hoverEvent);
}

void Rectangle::hoverMoveEvent(QGraphicsSceneHoverEvent *hoverEvent)
{
    QPointF currentPos = hoverEvent->pos();

    qreal drx = currentPos.x() - rect().right();
    qreal dlx = currentPos.x() - rect().left();
    qreal dty = currentPos.y() - rect().top();
    qreal dby = currentPos.y() - rect().bottom();
    switch (m_actionType) {
    case ActionType::Resize:
        if (dty < 5 && dty > 1) {
            m_cornerFlag = CornerFlags::Top;
            QApplication::setOverrideCursor(Qt::SizeVerCursor);
        } else if (dby < -1 && dby > -5) {
            m_cornerFlag = CornerFlags::Bottom;
            QApplication::setOverrideCursor(Qt::SizeVerCursor);
        } else if (drx < -1 && drx > -5) {
            m_cornerFlag = CornerFlags::Right;
            QApplication::setOverrideCursor(Qt::SizeHorCursor);
        } else if (dlx < 5 && dlx > 1) {
            m_cornerFlag = CornerFlags::Left;
            QApplication::setOverrideCursor(Qt::SizeHorCursor);
        } else if ((dty < 9 && dty > -1) && (dlx < 9 && dlx > -1)) {
            m_cornerFlag = CornerFlags::TopLeft;
            QApplication::setOverrideCursor(Qt::SizeFDiagCursor);
        } else if ((dty < 15 && dty > 1) && (drx < -1 && drx > -15)) {
            m_cornerFlag = CornerFlags::TopRight;
            QApplication::setOverrideCursor(Qt::SizeBDiagCursor);
        } else if ((dby < -1 && dby > -15) && (dlx < 15 && dlx > 1)) {
            m_cornerFlag = CornerFlags::BottomLeft;
            QApplication::setOverrideCursor(Qt::SizeBDiagCursor);
        } else if ((dby < -1 && dby > -15) && (drx < -1 && drx > -15)) {
            m_cornerFlag = CornerFlags::BottomRight;
            QApplication::setOverrideCursor(Qt::SizeFDiagCursor);
        } else {
            m_cornerFlag = CornerFlags::None;
            QApplication::restoreOverrideCursor();
        }
        break;
    case ActionType::Rotation: {
         QCursor rotationCursor = QCursor(QPixmap(":/images/icons/rotate.png").scaled(24, 24));
        if ((dty < 15 && dty > 1) && (dlx < 15 && dlx > 1)) {
            m_cornerFlag = CornerFlags::TopLeft;
            QApplication::setOverrideCursor(rotationCursor);
        } else if ((dty < 15 && dty > 1) && (drx < -1 && drx > -15)) {
            m_cornerFlag = CornerFlags::TopRight;
            QApplication::setOverrideCursor(rotationCursor);
        } else if ((dby < -1 && dby > -15) && (dlx < 15 && dlx > 1)) {
            m_cornerFlag = CornerFlags::BottomLeft;
            QApplication::setOverrideCursor(rotationCursor);
        } else if ((dby < -1 && dby > -15) && (drx < -1 && drx > -15)) {
            m_cornerFlag = CornerFlags::BottomRight;
            QApplication::setOverrideCursor(rotationCursor);
        } else {
            m_cornerFlag = CornerFlags::None;
            QApplication::restoreOverrideCursor();
        }
        break;
    }
    default:
        break;
    }

    QGraphicsItem::hoverMoveEvent(hoverEvent);
}

void Rectangle::hoverLeaveEvent(QGraphicsSceneHoverEvent *hoverEvent)
{
    QApplication::restoreOverrideCursor();

    QGraphicsItem::hoverLeaveEvent(hoverEvent);
}

QVariant Rectangle::itemChange(GraphicsItemChange change, const QVariant &value)
{
    if (change == GraphicsItemChange::ItemSelectedChange) {
       isSelected() ? setAcceptHoverEvents(false) : setAcceptHoverEvents(true);
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
}

void Rectangle::rotateItem(const QPointF &currentPoint)
{
    QRectF newRect = rect();
    QPointF center = boundingRect().center();
    QPointF corner;

    switch (m_cornerFlag) {
    case CornerFlags::TopLeft:
        corner = newRect.topLeft();
        break;
    case CornerFlags::TopRight:
        corner = newRect.topRight();
        break;
    case CornerFlags::BottomLeft:
        corner = newRect.bottomLeft();
        break;
    case CornerFlags::BottomRight:
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
    prepareGeometryChange();
    setTransform(trans);
}
