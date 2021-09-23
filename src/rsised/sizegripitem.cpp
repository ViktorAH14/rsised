#include "sizegripitem.h"

#include <cmath>

#include <QBrush>
#include <QGraphicsSceneHoverEvent>
#include <QApplication>
#include <QCursor>

static const double PI = 3.14159265358979323846264338327950288419717;
static double TWO_PI = 2.0 * PI;

static qreal normalizeAngle(qreal angle) {
    while (angle < 0) {
        angle += TWO_PI;
    }
    while (angle > TWO_PI) {
        angle -= TWO_PI;
    }
    return angle;
}

SizeGripItem::HandleItem::HandleItem(int positionFlags, SizeGripItem *parent)
    : QGraphicsRectItem(-4, -4, 8, 8, parent),
      handlePositionFlags(positionFlags),
      parentItem(parent)
{
    setBrush(QBrush(Qt::lightGray));
    setFlag(ItemIsMovable);
    setFlag(ItemSendsGeometryChanges);
    setAcceptHoverEvents(true);
}

int SizeGripItem::HandleItem::positionFlags() const
{
    return handlePositionFlags;
}

void SizeGripItem::HandleItem::mousePressEvent(QGraphicsSceneMouseEvent *mouseEvent) {
    leftButtonPressed = true;

    QGraphicsItem::mousePressEvent(mouseEvent);
}

void SizeGripItem::HandleItem::mouseMoveEvent(QGraphicsSceneMouseEvent *mouseEvent) {
    if ((parentItem->actionType() == Rotate) && (leftButtonPressed)) {
        QPointF currentPos = mapToParent(mouseEvent->pos());
        parentItem->rotateParentItem(currentPos, positionFlags());
    } else {
        QGraphicsItem::mouseMoveEvent(mouseEvent);
    }
}

void SizeGripItem::HandleItem::mouseReleaseEvent(QGraphicsSceneMouseEvent *mouseEvent) {
    leftButtonPressed = false;

    QGraphicsItem::mouseReleaseEvent(mouseEvent);
}

void SizeGripItem::HandleItem::hoverEnterEvent(QGraphicsSceneHoverEvent *hoverEvent)
{
    if (parentItem->actionType() == Resize) {
        switch (handlePositionFlags) {
        case Top:
            QApplication::setOverrideCursor(Qt::SizeVerCursor);
            break;
        case Bottom:
            QApplication::setOverrideCursor(Qt::SizeVerCursor);
            break;
        case Left:
            QApplication::setOverrideCursor(Qt::SizeHorCursor);
            break;
        case Right:
            QApplication::setOverrideCursor(Qt::SizeHorCursor);
            break;
        case TopLeft:
            QApplication::setOverrideCursor(Qt::SizeFDiagCursor);
            break;
        case BottomRight:
            QApplication::setOverrideCursor(Qt::SizeFDiagCursor);
            break;
        case TopRight:
            QApplication::setOverrideCursor(Qt::SizeBDiagCursor);
            break;
        case BottomLeft:
            QApplication::setOverrideCursor(Qt::SizeBDiagCursor);
            break;
        }
    } else if (parentItem->actionType() ==Rotate) {
        QCursor rotateCursor = QCursor(QPixmap(":images/icons/rotate.png").scaled(22, 22));
        switch (handlePositionFlags) {
        case TopLeft:
            QApplication::setOverrideCursor(rotateCursor);
            break;
        case TopRight:
            QApplication::setOverrideCursor(rotateCursor);
            break;
        case BottomLeft:
            QApplication::setOverrideCursor(rotateCursor);
            break;
        case BottomRight:
            QApplication::setOverrideCursor(rotateCursor);
            break;
        }
    }

    QGraphicsItem::hoverEnterEvent(hoverEvent);
}

void SizeGripItem::HandleItem::hoverLeaveEvent(QGraphicsSceneHoverEvent *hovereEvent)
{
    QApplication::restoreOverrideCursor();
    QGraphicsItem::hoverLeaveEvent(hovereEvent);
}

QVariant SizeGripItem::HandleItem::itemChange(GraphicsItemChange change,
                                              const QVariant &value)
{
    QVariant retVal = value;
    if (parentItem->actionType() == SizeGripItem::Resize) {
        if (change == ItemPositionChange)
        {
            retVal = restrictPosition(value.toPointF());
        }
        else if (change == ItemPositionHasChanged)
        {
            QPointF pos = value.toPointF();

            switch (handlePositionFlags)
            {
            case TopLeft:
                parentItem->setTopLeft(pos);
                break;
            case Top:
                parentItem->setTop(pos.y());
                break;
            case TopRight:
                parentItem->setTopRight(pos);
                break;
            case Right:
                parentItem->setRight(pos.x());
                break;
            case BottomRight:
                parentItem->setBottomRight(pos);
                break;
            case Bottom:
                parentItem->setBottom(pos.y());
                break;
            case BottomLeft:
                parentItem->setBottomLeft(pos);
                break;
            case Left:
                parentItem->setLeft(pos.x());
                break;
            }
        }
    }

    return retVal;
}

QPointF SizeGripItem::HandleItem::restrictPosition(const QPointF &newPos)
{
    QPointF retVal = pos();

    if (handlePositionFlags & Top || handlePositionFlags & Bottom)
        retVal.setY(newPos.y());

    if (handlePositionFlags & Left || handlePositionFlags & Right)
        retVal.setX(newPos.x());

    if (handlePositionFlags & Top && retVal.y() > parentItem->parentItemRect.bottom())
        retVal.setY(parentItem->parentItemRect.bottom());
    else if (handlePositionFlags & Bottom && retVal.y() < parentItem->parentItemRect.top())
        retVal.setY(parentItem->parentItemRect.top());

    if (handlePositionFlags & Left && retVal.x() > parentItem->parentItemRect.right())
        retVal.setX(parentItem->parentItemRect.right());
    else if (handlePositionFlags & Right && retVal.x() < parentItem->parentItemRect.left())
        retVal.setX(parentItem->parentItemRect.left());

    return retVal;
}

SizeGripItem::SizeGripItem(Resizer *resizer, QGraphicsItem *parent)
    : QGraphicsItem(parent),
      itemResizer(resizer)
{
    if (parentItem()) {
        parentItemRect = parentItem()->boundingRect();
    }

    setActionType(Resize);

    handleItemList.append(new HandleItem(TopLeft, this));
    handleItemList.append(new HandleItem(Top, this));
    handleItemList.append(new HandleItem(TopRight, this));
    handleItemList.append(new HandleItem(Right, this));
    handleItemList.append(new HandleItem(BottomRight, this));
    handleItemList.append(new HandleItem(Bottom, this));
    handleItemList.append(new HandleItem(BottomLeft, this));
    handleItemList.append(new HandleItem(Left, this));
    updateHandleItemPositions();
}

SizeGripItem::~SizeGripItem()
{
    if (itemResizer)
        delete itemResizer;
}

QRectF SizeGripItem::boundingRect() const
{
    return parentItemRect;
}

void SizeGripItem::paint(QPainter *painter,
                         const QStyleOptionGraphicsItem *option,
                         QWidget *widget)
{
    Q_UNUSED(painter);
    Q_UNUSED(option);
    Q_UNUSED(widget);
}

#define IMPL_SET_FN(TYPE, POS)                  \
    void SizeGripItem::set ## POS (TYPE v)      \
    {                                           \
        parentItemRect.set ## POS (v);                   \
        doResize();                             \
    }

IMPL_SET_FN(qreal, Top)
IMPL_SET_FN(qreal, Right)
IMPL_SET_FN(qreal, Bottom)
IMPL_SET_FN(qreal, Left)
IMPL_SET_FN(const QPointF&, TopLeft)
IMPL_SET_FN(const QPointF&, TopRight)
IMPL_SET_FN(const QPointF&, BottomRight)
IMPL_SET_FN(const QPointF&, BottomLeft)

void SizeGripItem::doResize()
{
    if (itemResizer)
    {
        (*itemResizer)(parentItem(), parentItemRect);
        updateHandleItemPositions();
    }
}

void SizeGripItem::updateHandleItemPositions()
{
    foreach (HandleItem *item, handleItemList)
    {
        item->setFlag(ItemSendsGeometryChanges, false);

        switch (item->positionFlags())
        {
            case TopLeft:
                item->setPos(parentItemRect.topLeft());
                break;
            case Top:
                item->setPos(parentItemRect.left() + parentItemRect.width() / 2 - 1,
                             parentItemRect.top());
                break;
            case TopRight:
                item->setPos(parentItemRect.topRight());
                break;
            case Right:
                item->setPos(parentItemRect.right(),
                             parentItemRect.top() + parentItemRect.height() / 2 - 1);
                break;
            case BottomRight:
                item->setPos(parentItemRect.bottomRight());
                break;
            case Bottom:
                item->setPos(parentItemRect.left() + parentItemRect.width() / 2 - 1,
                             parentItemRect.bottom());
                break;
            case BottomLeft:
                item->setPos(parentItemRect.bottomLeft());
                break;
            case Left:
                item->setPos(parentItemRect.left(),
                             parentItemRect.top() + parentItemRect.height() / 2 - 1);
                break;
        }

        item->setFlag(ItemSendsGeometryChanges, true);
    }
}

SizeGripItem::Resizer::~Resizer()
{
}
void SizeGripItem::rotateParentItem(const QPointF &currentPos, int positionFlag) {
    QPointF parentItemCenter = parentItemRect.center();
    QPointF corner;

    switch (positionFlag) {
    case TopLeft:
        corner = parentItemRect.topLeft();
        break;
    case TopRight:
        corner = parentItemRect.topRight();
        break;
    case BottomLeft:
        corner = parentItemRect.bottomLeft();
        break;
    case BottomRight:
        corner = parentItemRect.bottomRight();
        break;
    }
    QLineF lineToTarget(parentItemCenter, corner);
    QLineF lineToCursor(parentItemCenter, currentPos);

    qreal angleToTarget = ::acos(lineToTarget.dx() / lineToTarget.length());
    qreal angleToCursor = ::acos(lineToCursor.dx() / lineToCursor.length());

    if (lineToTarget.dy() < 0) {
        angleToTarget = (TWO_PI - angleToTarget);
    }
    angleToTarget = normalizeAngle((PI - angleToTarget) + PI / 2);

    if (lineToCursor.dy() < 0) {
        angleToCursor = TWO_PI - angleToCursor;
    }
    angleToCursor = normalizeAngle((PI - angleToCursor) + PI / 2);

    qreal resultAngle = angleToTarget - angleToCursor;

    QTransform parentTransformation = parentItem()->transform();
    parentTransformation.translate(parentItemCenter.x(), parentItemCenter.y());
    parentTransformation.rotateRadians(parentItem()->rotation() + resultAngle, Qt::ZAxis);
    parentTransformation.translate(-parentItemCenter.x(), -parentItemCenter.y());
    parentItem()->setTransform(parentTransformation);
    updateHandleItemPositions();
}

void SizeGripItem::setActionType(int actionType) {
    currentActionType = actionType;
    if (actionType == Rotate) {
        for (HandleItem *item : qAsConst(handleItemList)) {
            if ((item->positionFlags() == Top) || (item->positionFlags() == Bottom)
                    || (item->positionFlags() == Left) || (item->positionFlags() == Right)) {
                item->hide();
            }
        }
    } else {
        for (HandleItem *item : qAsConst(handleItemList)) {
            item->show();
        }
    }
}

int SizeGripItem::actionType() {
    return currentActionType;
}
