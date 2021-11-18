#include "sizegripitem.h"
#include "rectangle.h"
#include "ellipse.h"
#include "polyline.h"
#include "curve.h"
#include "pixmapitem.h"
#include "technics_shape.h"

#include <cmath>

#include <QBrush>
#include <QGraphicsSceneHoverEvent>
#include <QApplication>
#include <QCursor>

Q_DECLARE_METATYPE(QPainterPath)

static const double PI {3.14159265358979323846264338327950288419717};
static double TWO_PI {2.0 * PI};

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

SizeGripItem::HandleItem::HandleItem(int positionFlags, SizeGripItem *parent)
    : QGraphicsRectItem(-3, -3, 6, 6, parent)
    , handlePositionFlags {positionFlags}
    , parentItem {parent}
    , leftButtonPressed {false}
{
    setBrush(QBrush(Qt::lightGray));
    setFlag(ItemIsMovable, true);
    setFlag(ItemSendsGeometryChanges, true);
    setFlag(ItemIgnoresTransformations, true);
    setAcceptHoverEvents(true);
}

int SizeGripItem::HandleItem::positionFlags() const
{
    return handlePositionFlags;
}

void SizeGripItem::HandleItem::setPathElementNum(int num)
{
    pathElementNum = num;
}

void SizeGripItem::HandleItem::mousePressEvent(QGraphicsSceneMouseEvent *mouseEvent)
{
    leftButtonPressed = true;

    QGraphicsItem::mousePressEvent(mouseEvent);
}

void SizeGripItem::HandleItem::mouseMoveEvent(QGraphicsSceneMouseEvent *mouseEvent)
{
    if ((parentItem->actionType() == Rotate) && (leftButtonPressed)) {
        setFlag(ItemIgnoresTransformations, false);
        QPointF currentPos = mapToParent(mouseEvent->pos());
        parentItem->rotateParentItem(currentPos, positionFlags());
    } else {
        setFlag(ItemIgnoresTransformations, true);
        QGraphicsItem::mouseMoveEvent(mouseEvent);
    }
}

void SizeGripItem::HandleItem::mouseReleaseEvent(QGraphicsSceneMouseEvent *mouseEvent)
{
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
        case PathLine:
            QApplication::setOverrideCursor(Qt::SizeAllCursor);
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
    QVariant retVal {value};
    if (parentItem->actionType() == SizeGripItem::Resize) {
        if (change == ItemPositionChange)
        {
            retVal = restrictPosition(value.toPointF());
        }
        else if (change == ItemPositionHasChanged)
        {
            QPointF newPos {value.toPointF()};

            switch (handlePositionFlags)
            {
            case TopLeft:
                parentItem->setTopLeft(newPos);
                break;
            case Top:
                parentItem->setTop(newPos.y());
                break;
            case TopRight:
                parentItem->setTopRight(newPos);
                break;
            case Right:
                parentItem->setRight(newPos.x());
                break;
            case BottomRight:
                parentItem->setBottomRight(newPos);
                break;
            case Bottom:
                parentItem->setBottom(newPos.y());
                break;
            case BottomLeft:
                parentItem->setBottomLeft(newPos);
                break;
            case Left:
                parentItem->setLeft(newPos.x());
                break;
            case PathLine:
                QPainterPath oldPath {parentItem->parentItemPath()};
                QPainterPath newPath;
                if (parentItem->parentItem()->type() == Polyline::Type) {
                    for (int i = 0; i < oldPath.elementCount(); i++) {
                        if (i == 0) {
                            if (i == pathElementNum) {
                                newPath.moveTo(newPos);
                            } else {
                                newPath.moveTo(oldPath.elementAt(i));
                            }
                        } else {
                            if (i == pathElementNum) {
                                newPath.lineTo(newPos);
                            } else {
                                newPath.lineTo(oldPath.elementAt(i));
                            }
                        }
                    }
                }
                if (parentItem->parentItem()->type() == Curve::Type) {
                    for (int i = 0; i < oldPath.elementCount(); i++) {
                        int identPoint(i % 3); // control point or a path point
                        switch (identPoint) {
                        case 0:
                            if (i == 0) {
                                if (i == pathElementNum) {
                                    newPath.moveTo(newPos);
                                } else {
                                    newPath.moveTo(oldPath.elementAt(0));
                                }
                            } else {
                                if (i == pathElementNum) {
                                    newPath.cubicTo(oldPath.elementAt(i - 2), oldPath.elementAt(i - 1), newPos);
                                } else {
                                    newPath.cubicTo(oldPath.elementAt(i - 2), oldPath.elementAt(i - 1), oldPath.elementAt(i));
                                }
                            }
                            break;

                        case 1: // control point 1
                            if (i == pathElementNum) {
                                newPath.cubicTo(newPos, oldPath.elementAt(i + 1),oldPath.elementAt(i + 2));
                                i += 2; // moving to the next element of the path
                            }
                            break;
                        case 2: // control point 2
                            if (i == pathElementNum) {
                                newPath.cubicTo(oldPath.elementAt(i - 1), newPos, oldPath.elementAt(i + 1));
                                i++; // moving to the next element of the path
                            }
                            break;
                        }
                    }
                }
                parentItem->setParentItemPath(newPath);
                parentItem->doResize();
                break;
            }
        }
    }

    return retVal;
}

QPointF SizeGripItem::HandleItem::restrictPosition(const QPointF &newPos)
{
    QPointF retVal {pos()};

    if (handlePositionFlags & Top || handlePositionFlags & Bottom)
        retVal.setY(newPos.y());

    if (handlePositionFlags & Left || handlePositionFlags & Right)
        retVal.setX(newPos.x());

    if (handlePositionFlags == PathLine) {
        retVal.setX(newPos.x());
        retVal.setY(newPos.y());
    }

    if (handlePositionFlags & Top && retVal.y() > parentItem->m_parentItemRect.bottom())
        retVal.setY(parentItem->m_parentItemRect.bottom());
    else if (handlePositionFlags & Bottom && retVal.y() < parentItem->m_parentItemRect.top())
        retVal.setY(parentItem->m_parentItemRect.top());

    if (handlePositionFlags & Left && retVal.x() > parentItem->m_parentItemRect.right())
        retVal.setX(parentItem->m_parentItemRect.right());
    else if (handlePositionFlags & Right && retVal.x() < parentItem->m_parentItemRect.left())
        retVal.setX(parentItem->m_parentItemRect.left());

    return retVal;
}

SizeGripItem::SizeGripItem(Resizer *resizer, QGraphicsItem *parent)
    : QGraphicsItem(parent)
    , itemResizer(resizer)
{
    if ((parent->type() == Rectangle::Type) || (parent->type() == Ellipse::Type)
            || (parent->type() == PixmapItem::Type) || (parent->type() == TechnicsShape::Type)) {
        m_parentItemRect = parentItem()->boundingRect();
        setItemType(Rectangle);
        int handleNum {-1};

        handleItemList.append(new HandleItem(TopLeft, this));
        handleItemList.append(new HandleItem(Top, this));
        handleItemList.append(new HandleItem(TopRight, this));
        handleItemList.append(new HandleItem(Right, this));
        handleItemList.append(new HandleItem(BottomRight, this));
        handleItemList.append(new HandleItem(Bottom, this));
        handleItemList.append(new HandleItem(BottomLeft, this));
        handleItemList.append(new HandleItem(Left, this));
        for (HandleItem *item :qAsConst(handleItemList)) {
            item->setPathElementNum(handleNum);
        }
    }
    if (Polyline *polylineItem = dynamic_cast<Polyline *>(parent)) {
        setItemType(Path);
        m_parentPath = polylineItem->path();
        for (int i = 0; i < m_parentPath.elementCount(); i++) {
            handleItemList.append(new HandleItem(PathLine, this));
            HandleItem *item {handleItemList.at(i)};
            item->setPathElementNum(i);
        }
    }
    if (Curve *curveItem = dynamic_cast<Curve *>(parent)) {
        setItemType(Path);
        m_parentPath = curveItem->path();
        for (int i = 0; i < m_parentPath.elementCount(); i++) {
            handleItemList.append(new HandleItem(PathLine, this));
            HandleItem *item {handleItemList.at(i)};
            item->setPathElementNum(i);
        }
    }

    setActionType(Resize);
    updateHandleItemPositions();
}

SizeGripItem::~SizeGripItem()
{
    if (itemResizer)
        delete itemResizer;
}

QRectF SizeGripItem::boundingRect() const
{
    return m_parentItemRect;
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
        m_parentItemRect.set ## POS (v);                   \
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
        if (m_itemType == Rectangle) {
            (*itemResizer)(parentItem(), m_parentItemRect);
            if (parentItem()->type() == PixmapItem::Type ||
                    parentItem()->type() == TechnicsShape::Type) {
                m_parentItemRect = parentItem()->boundingRect();
            }
            updateHandleItemPositions();
        }
        if (m_itemType == Path) {
            (*itemResizer)(parentItem(), QVariant::fromValue(m_parentPath));
            updateHandleItemPositions();
        }
    }
}

//TODO сделать HandleItem независимыми от поворота фигуры
void SizeGripItem::updateHandleItemPositions()
{
    for (int i = 0; i < handleItemList.count(); i++) {
        HandleItem *item {handleItemList.at(i)};
        item->setFlag(ItemSendsGeometryChanges, false);

        switch (item->positionFlags())
        {
        case TopLeft:
            item->setPos(m_parentItemRect.topLeft());
            break;
        case Top:
            item->setPos(m_parentItemRect.left() + m_parentItemRect.width() / 2 - 1,
                         m_parentItemRect.top());
            break;
        case TopRight:
            item->setPos(m_parentItemRect.topRight());
            break;
        case Right:
            item->setPos(m_parentItemRect.right(),
                         m_parentItemRect.top() + m_parentItemRect.height() / 2 - 1);
            break;
        case BottomRight:
            item->setPos(m_parentItemRect.bottomRight());
            break;
        case Bottom:
            item->setPos(m_parentItemRect.left() + m_parentItemRect.width() / 2 - 1,
                         m_parentItemRect.bottom());
            break;
        case BottomLeft:
            item->setPos(m_parentItemRect.bottomLeft());
            break;
        case Left:
            item->setPos(m_parentItemRect.left(),
                         m_parentItemRect.top() + m_parentItemRect.height() / 2 - 1);
            break;
        case PathLine:
            item->setPos(m_parentPath.elementAt(i));
            break;
        }

        item->setFlag(ItemSendsGeometryChanges, true);
    }
}

SizeGripItem::Resizer::~Resizer()
{
}

void SizeGripItem::rotateParentItem(const QPointF &currentPos, int positionFlag)
{
    QPointF parentItemCenter {m_parentItemRect.center()};
    QPointF corner;

    switch (positionFlag) {
    case TopLeft:
        corner = m_parentItemRect.topLeft();
        break;
    case TopRight:
        corner = m_parentItemRect.topRight();
        break;
    case BottomLeft:
        corner = m_parentItemRect.bottomLeft();
        break;
    case BottomRight:
        corner = m_parentItemRect.bottomRight();
        break;
    }
    QLineF lineToTarget(parentItemCenter, corner);
    QLineF lineToCursor(parentItemCenter, currentPos);

    qreal angleToTarget {::acos(lineToTarget.dx() / lineToTarget.length())};
    qreal angleToCursor {::acos(lineToCursor.dx() / lineToCursor.length())};

    if (lineToTarget.dy() < 0) {
        angleToTarget = (TWO_PI - angleToTarget);
    }
    angleToTarget = normalizeAngle((PI - angleToTarget) + PI / 2);

    if (lineToCursor.dy() < 0) {
        angleToCursor = TWO_PI - angleToCursor;
    }
    angleToCursor = normalizeAngle((PI - angleToCursor) + PI / 2);

    qreal resultAngle {angleToTarget - angleToCursor};

    QTransform parentTransformation {parentItem()->transform()};
    parentTransformation.translate(parentItemCenter.x(), parentItemCenter.y());
    parentTransformation.rotateRadians(parentItem()->rotation() + resultAngle, Qt::ZAxis);
    parentTransformation.translate(-parentItemCenter.x(), -parentItemCenter.y());
    parentItem()->setTransform(parentTransformation);
    updateHandleItemPositions();
}

void SizeGripItem::setItemType(SizeGripItem::ItemType type)
{
    m_itemType = type;
}

QPainterPath SizeGripItem::parentItemPath()
{
    return m_parentPath;
}

void SizeGripItem::setParentItemPath(QPainterPath newPath)
{
    m_parentPath.swap(newPath);
}

void SizeGripItem::setActionType(SizeGripItem::ActionType actionType)
{
    m_actionType = actionType;
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

SizeGripItem::ActionType SizeGripItem::actionType()
{
    return m_actionType;
}
