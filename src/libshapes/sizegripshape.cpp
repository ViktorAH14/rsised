/*
 * Copyright (c) 2022 by Viktor Ermolov <ermolovva@gmail.com>.
 *
 * This file is part of the RSiSed project, a editor of the alignment of forces
 * and means in extinguishing a fire. (RSiSed)
 *
 * RSiSed is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * RSiSed is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <https://www.gnu.org/licenses/>.
 */

#include "../include/sizegripshape.h"
#include "../include/rectshape.h"
#include "../include/ellipseshape.h"
#include "../include/polylineshape.h"
#include "../include/curve.h"
#include "../include/pixmapshape.h"
#include "../include/technicsshape.h"
#include "../include/deviceshape.h"
#include "../include/buildingshape.h"

#include <cmath>

#include <QBrush>
#include <QGraphicsSceneHoverEvent>
#include <QApplication>
#include <QCursor>

Q_DECLARE_METATYPE(QPainterPath)

static const double PI {3.14159265358979323846264338327950288419717}; //TODO put in a separate header (global.h)
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

SizeGripShape::HandleItem::HandleItem(int positionFlags, SizeGripShape *parent)
    : QGraphicsRectItem(-3, -3, 6, 6, parent)
    , m_handlePositionFlags {positionFlags}
    , m_parentItem {parent}
    , m_leftButtonPressed {false}
    , m_pathElementNum {0}
{
    setBrush(QBrush(Qt::lightGray));
    setFlag(ItemIsMovable, true);
    setFlag(ItemSendsGeometryChanges, true);
    setFlag(ItemIgnoresTransformations, true);
    setAcceptHoverEvents(true);
}

int SizeGripShape::HandleItem::positionFlags() const
{
    return m_handlePositionFlags;
}

void SizeGripShape::HandleItem::setPathElementNum(int num)
{
    m_pathElementNum = num;
}

void SizeGripShape::HandleItem::mousePressEvent(QGraphicsSceneMouseEvent *mouseEvent)
{
    if (mouseEvent->button() == Qt::LeftButton)
        m_leftButtonPressed = true;

    QGraphicsItem::mousePressEvent(mouseEvent);
}

void SizeGripShape::HandleItem::mouseMoveEvent(QGraphicsSceneMouseEvent *mouseEvent)
{
    if ((m_parentItem->actionType() == Rotate) && (m_leftButtonPressed)) {
        setFlag(ItemIgnoresTransformations, false);
        QPointF currentPos{mapToParent(mouseEvent->pos())};
        m_parentItem->rotateParentItem(currentPos, positionFlags());
    } else {
        setFlag(ItemIgnoresTransformations, true);
        QGraphicsItem::mouseMoveEvent(mouseEvent);
    }
}

void SizeGripShape::HandleItem::mouseReleaseEvent(QGraphicsSceneMouseEvent *mouseEvent)
{
    m_leftButtonPressed = false;

    QGraphicsItem::mouseReleaseEvent(mouseEvent);
}

void SizeGripShape::HandleItem::hoverEnterEvent(QGraphicsSceneHoverEvent *hoverEvent)
{
    if (m_parentItem->actionType() == Resize) {
        switch (m_handlePositionFlags) {
        case Top: case Bottom:
            QApplication::setOverrideCursor(Qt::SizeVerCursor);
            break;
        case Left: case Right:
            QApplication::setOverrideCursor(Qt::SizeHorCursor);
            break;
        case TopLeft: case BottomRight:
            QApplication::setOverrideCursor(Qt::SizeFDiagCursor);
            break;
        case TopRight: case BottomLeft:
            QApplication::setOverrideCursor(Qt::SizeBDiagCursor);
            break;
        case PathLine: case Center: case StartPoint: case SpanPoint:
            QApplication::setOverrideCursor(Qt::SizeAllCursor);
            break;
        }
    } else {
        QCursor rotateCursor{QCursor(QPixmap(":images/icons/rotate.png").scaled(22, 22))};
        QApplication::setOverrideCursor(rotateCursor);
    }

    QGraphicsItem::hoverEnterEvent(hoverEvent);
}

void SizeGripShape::HandleItem::hoverLeaveEvent(QGraphicsSceneHoverEvent *hoverEvent)
{
    QApplication::restoreOverrideCursor();
    QGraphicsItem::hoverLeaveEvent(hoverEvent);
}

QVariant SizeGripShape::HandleItem::itemChange(GraphicsItemChange change, const QVariant &value)
{
    QVariant retVal{value};
    ActionType currentActionType{m_parentItem->actionType()};
    if (currentActionType == SizeGripShape::Resize) {
        if (change == ItemPositionChange) {
            retVal = restrictPosition(value.toPointF());
        } else if (change == ItemPositionHasChanged) {
            QPointF newPos = value.toPointF();
            switch (m_handlePositionFlags) {
            case TopLeft:
                m_parentItem->setTopLeft(newPos);
                break;
            case Top:
                m_parentItem->setTop(newPos.y());
                break;
            case TopRight:
                m_parentItem->setTopRight(newPos);
                break;
            case Right:
                m_parentItem->setRight(newPos.x());
                break;
            case BottomRight:
                m_parentItem->setBottomRight(newPos);
                break;
            case Bottom:
                m_parentItem->setBottom(newPos.y());
                break;
            case BottomLeft:
                m_parentItem->setBottomLeft(newPos);
                break;
            case Left:
                m_parentItem->setLeft(newPos.x());
                break;
            case PathLine: {
                QPainterPath oldPath{m_parentItem->parentItemPath()};
                QPainterPath newPath;
                if (m_parentItem->parentItem()->type() == PolylineShape::Type) {
                    for (int i = 0; i < oldPath.elementCount(); i++) {
                        if (i == 0) {
                            if (i == m_pathElementNum) {
                                newPath.moveTo(newPos);
                            } else {
                                newPath.moveTo(oldPath.elementAt(i));
                            }
                        } else {
                            if (i == m_pathElementNum) {
                                newPath.lineTo(newPos);
                            } else {
                                newPath.lineTo(oldPath.elementAt(i));
                            }
                        }
                    }
                }
                if (m_parentItem->parentItem()->type() == Curve::Type) {
                    for (int i = 0; i < oldPath.elementCount(); i++) {
                        int identPoint{i % 3}; // control point or a path point
                        switch (identPoint) {
                        case 0:
                            if (i == 0) {
                                if (i == m_pathElementNum) {
                                    newPath.moveTo(newPos);
                                } else {
                                    newPath.moveTo(oldPath.elementAt(0));
                                }
                            } else {
                                if (i == m_pathElementNum) {
                                    newPath.cubicTo(oldPath.elementAt(i - 2)
                                                    , oldPath.elementAt(i - 1), newPos);
                                } else {
                                    newPath.cubicTo(oldPath.elementAt(i - 2)
                                                    , oldPath.elementAt(i - 1)
                                                    , oldPath.elementAt(i));
                                }
                            }
                            break;

                        case 1: // control point 1
                            if (i == m_pathElementNum) {
                                newPath.cubicTo(newPos, oldPath.elementAt(i + 1)
                                                ,oldPath.elementAt(i + 2));
                                i += 2; // moving to the next element of the path
                            }
                            break;
                        case 2: // control point 2
                            if (i == m_pathElementNum) {
                                newPath.cubicTo(oldPath.elementAt(i - 1), newPos
                                                , oldPath.elementAt(i + 1));
                                i++; // moving to the next element of the path
                            }
                            break;
                        }
                    }
                }
                m_parentItem->setParentItemPath(newPath);
                m_parentItem->doResize();
            }
                break;
            case Center:
                m_parentItem->setCenter(newPos);
                break;
            case StartPoint:
                m_parentItem->setStartPoint(newPos);
                break;
            case SpanPoint:
                m_parentItem->setSpanPoint(newPos);
                break;
            }
        }
    }

    return retVal;
}

QPointF SizeGripShape::HandleItem::restrictPosition(const QPointF &newPos)
{
    QPointF retVal{pos()};

    if (m_handlePositionFlags & Top || m_handlePositionFlags & Bottom)
        retVal.setY(newPos.y());

    if (m_handlePositionFlags & Left || m_handlePositionFlags & Right)
        retVal.setX(newPos.x());

    if (m_handlePositionFlags == PathLine) {
        retVal.setX(newPos.x());
        retVal.setY(newPos.y());
    }
    if ((m_handlePositionFlags == Center) || (m_handlePositionFlags == StartPoint)
            || (m_handlePositionFlags == SpanPoint)) {
        retVal.setX(newPos.x());
        retVal.setY(newPos.y());
    }
    if (m_handlePositionFlags & Top && retVal.y() > m_parentItem->m_parentItemRect.bottom()) {
        retVal.setY(m_parentItem->m_parentItemRect.bottom());
    } else if (m_handlePositionFlags & Bottom && retVal.y() < m_parentItem->m_parentItemRect.top()) {
        retVal.setY(m_parentItem->m_parentItemRect.top());
    }

    if (m_handlePositionFlags & Left && retVal.x() > m_parentItem->m_parentItemRect.right()) {
        retVal.setX(m_parentItem->m_parentItemRect.right());
    } else if (m_handlePositionFlags & Right && retVal.x() < m_parentItem->m_parentItemRect.left()) {
        retVal.setX(m_parentItem->m_parentItemRect.left());
    }

    return retVal;
}
SizeGripShape::SizeGripShape(Resizer *resizer, QGraphicsItem *parent)
    : QGraphicsItem(parent)
    , m_itemResizer{resizer}
    , m_parentItemRect{QRectF()}
    , m_parentPath{QPainterPath()}
    , m_actionType{Resize}
    , m_itemType{Rect}
    , m_ellipseShape{nullptr}
    , m_centerPoint{QPointF()}
    , m_startPoint{QPointF()}
    , m_spanPoint{QPointF()}
{
    QList<int> rectTypeList;
    rectTypeList << RectShape::Type << PixmapShape::Type << BaseShape::Type << TankerShape::Type
                 << PumpHoseShape::Type << FirstAidShape::Type << EmergencyShape::Type
                 << AutoLadderShape::Type << CrankLiftShape::Type << TelescopicLiftShape::Type
                 << HoseCarShape::Type << CommShape::Type << TechServShape::Type
                 << SmokRemShape::Type << PumpStatShape::Type << LafetTankerShape::Type
                 << LafetCarShape::Type << AerodromeShape::Type << FoamShape::Type
                 << ComboShape::Type << AerosolShape::Type << PowderShape::Type
                 << CarbonShape::Type << GazWaterShape::Type << TrackedShape::Type
                 << TankShape::Type << GdzsShape::Type << WaterproofShape::Type
                 << LaboratoryShape::Type << StaffCarShape::Type << TrailerShape::Type
                 << ShipShape::Type << BoatShape::Type << TrainShape::Type << PlaneShape::Type
                 << SeaplaneShape::Type << HelicopterShape::Type
                 << DeviceShape::Type << StairwellShape::Type << StairsShape::Type;
    bool rectType{false};
    for (const int itemType : rectTypeList) {
        if (parent->type() == itemType) {
                rectType = true;
        }
    }

    if (rectType) {
        m_parentItemRect = parentItem()->boundingRect();
        setItemType(Rect);
        int handleNum {-1};

        handleItemList.append(new HandleItem(TopLeft, this));
        handleItemList.append(new HandleItem(Top, this));
        handleItemList.append(new HandleItem(TopRight, this));
        handleItemList.append(new HandleItem(Right, this));
        handleItemList.append(new HandleItem(BottomRight, this));
        handleItemList.append(new HandleItem(Bottom, this));
        handleItemList.append(new HandleItem(BottomLeft, this));
        handleItemList.append(new HandleItem(Left, this));
        for (HandleItem *item : qAsConst(handleItemList)) {
            item->setPathElementNum(handleNum);
        }
    }
    if (parent->type() == EllipseShape::Type) {
        m_ellipseShape = dynamic_cast<EllipseShape *>(parent);
        int spanAngle{m_ellipseShape->spanAngle()};
        if ((spanAngle != 0) && (qAbs(spanAngle) % (360 * 16) == 0)) {
            m_parentItemRect = parentItem()->boundingRect();
            setItemType(Rect);
            int handleNum{-1};

            handleItemList.append(new HandleItem(TopLeft, this));
            handleItemList.append(new HandleItem(Top, this));
            handleItemList.append(new HandleItem(TopRight, this));
            handleItemList.append(new HandleItem(Right, this));
            handleItemList.append(new HandleItem(BottomRight, this));
            handleItemList.append(new HandleItem(Bottom, this));
            handleItemList.append(new HandleItem(BottomLeft, this));
            handleItemList.append(new HandleItem(Left, this));
            for (HandleItem *p_handleItem : qAsConst(handleItemList)) {
                p_handleItem->setPathElementNum(handleNum);
            }
        } else {
            setItemType(Pie);
            m_centerPoint = m_ellipseShape->rect().center();
            setPieHandleItem();

            handleItemList.append(new HandleItem(Center, this));
            handleItemList.append(new HandleItem(StartPoint, this));
            handleItemList.append(new HandleItem(SpanPoint, this));
            int handleNum{-1};
            for (HandleItem *p_handleItem : qAsConst(handleItemList)) {
                p_handleItem->setPathElementNum(handleNum);
            }
        }
    }
    if (PolylineShape *p_polylineShape = dynamic_cast<PolylineShape *>(parent)) {
        setItemType(Path);
        m_parentPath = p_polylineShape->path();
        for (int i = 0; i < m_parentPath.elementCount(); i++) {
            handleItemList.append(new HandleItem(PathLine, this));
            HandleItem *p_handleItem {handleItemList.at(i)};
            p_handleItem->setPathElementNum(i);
        }
    }
    if (Curve *p_curveShape = dynamic_cast<Curve *>(parent)) {
        setItemType(Path);
        m_parentPath = p_curveShape->path();
        for (int i = 0; i < m_parentPath.elementCount(); i++) {
            handleItemList.append(new HandleItem(PathLine, this));
            HandleItem *p_handleItem {handleItemList.at(i)};
            p_handleItem->setPathElementNum(i);
        }
    }

    if ((parent->type() == WallShape::Type) || (parent->type() == DoorShape::Type)
            || (parent->type() == WindowShape::Type)
            || (parent->type() == OpenShape::Type)) {
        BuildingShape *p_parentBuildingshape = dynamic_cast<BuildingShape *>(parentItem());
        m_parentItemRect = p_parentBuildingshape->rect();
        setItemType(Rect); // NOTE возможно изменить?
        int handleNum{-1};

        handleItemList.append(new HandleItem(Right, this));
        handleItemList.append(new HandleItem(Left, this));
        for (HandleItem *p_handleItem : qAsConst(handleItemList)) {
            p_handleItem->setPathElementNum(handleNum);
        }
    }

    updateHandleItemPositions();
}

SizeGripShape::~SizeGripShape()
{
    if (m_itemResizer)
        delete m_itemResizer;
}

QRectF SizeGripShape::boundingRect() const
{
    return m_parentItemRect;
}

void SizeGripShape::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(painter);
    Q_UNUSED(option);
    Q_UNUSED(widget);
}

#define IMPL_SET_FN(TYPE, POS)              \
    void SizeGripShape::set ## POS (TYPE v) \
    {                                       \
        m_parentItemRect.set ## POS (v);    \
        doResize();                         \
    }

IMPL_SET_FN(qreal, Top)
IMPL_SET_FN(qreal, Right)
IMPL_SET_FN(qreal, Bottom)
IMPL_SET_FN(qreal, Left)
IMPL_SET_FN(const QPointF&, TopLeft)
IMPL_SET_FN(const QPointF&, TopRight)
IMPL_SET_FN(const QPointF&, BottomRight)
IMPL_SET_FN(const QPointF&, BottomLeft)

void SizeGripShape::setCenter(const QPointF &pos) {
    m_centerPoint = pos;
    m_parentItemRect.moveCenter(pos);
    doResize();
    setPieHandleItem();
    updateHandleItemPositions();
}

void SizeGripShape::doResize()
{
    if (m_itemResizer)
    {
        if ((m_itemType == Rect) || (m_itemType == Pie)) {
            (*m_itemResizer)(parentItem(), m_parentItemRect);
            if (parentItem()->type() == PixmapShape::Type) { //TODO изменить, неадекватное масштабирование нижеперечисленных шейпов
                m_parentItemRect = parentItem()->boundingRect();
            }
//            updateHandleItemPositions();
        }
        if (m_itemType == Path) {
            (*m_itemResizer)(parentItem(), QVariant::fromValue(m_parentPath));
        }
        updateHandleItemPositions();
    }
}

void SizeGripShape::updateHandleItemPositions()
{
    for (int i = 0; i < handleItemList.count(); i++) {
        HandleItem *p_handleItem {handleItemList.at(i)};
        p_handleItem->setFlag(ItemSendsGeometryChanges, false);

        switch (p_handleItem->positionFlags())
        {
        case TopLeft:
            p_handleItem->setPos(m_parentItemRect.topLeft());
            break;
        case Top:
            p_handleItem->setPos(m_parentItemRect.left() + m_parentItemRect.width() / 2 - 1,
                         m_parentItemRect.top());
            break;
        case TopRight:
            p_handleItem->setPos(m_parentItemRect.topRight());
            break;
        case Right:
            p_handleItem->setPos(m_parentItemRect.right(),
                         m_parentItemRect.top() + m_parentItemRect.height() / 2 - 1);
            break;
        case BottomRight:
            p_handleItem->setPos(m_parentItemRect.bottomRight());
            break;
        case Bottom:
            p_handleItem->setPos(m_parentItemRect.left() + m_parentItemRect.width() / 2 - 1,
                         m_parentItemRect.bottom());
            break;
        case BottomLeft:
            p_handleItem->setPos(m_parentItemRect.bottomLeft());
            break;
        case Left:
            p_handleItem->setPos(m_parentItemRect.left(),
                         m_parentItemRect.top() + m_parentItemRect.height() / 2 - 1);
            break;
        case PathLine:
            p_handleItem->setPos(m_parentPath.elementAt(i));
            break;
        case Center:
            p_handleItem->setPos(m_centerPoint);
            break;
        case StartPoint:
            p_handleItem->setPos(m_startPoint);
            break;
        case SpanPoint:
            p_handleItem->setPos(m_spanPoint);
            break;
        }

        p_handleItem->setFlag(ItemSendsGeometryChanges, true);
    }
}

SizeGripShape::Resizer::~Resizer()
{
}

void SizeGripShape::rotateParentItem(const QPointF &currentPos, int positionFlag)
{
    QPointF parentItemCenter{m_parentItemRect.center()};
    QPointF corner;

    if ((parentItem()->type() ==  WallShape::Type) || (parentItem()->type() == DoorShape::Type)
            || (parentItem()->type() == WindowShape::Type)
            || (parentItem()->type() == OpenShape::Type)) {
        switch (positionFlag) {
        case Left:
            corner = m_parentItemRect.topLeft();
            break;
        case Right:
            corner = m_parentItemRect.topRight();
            break;
        }
    } else {
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
    }
    QLineF lineToTarget(parentItemCenter, corner);
    QLineF lineToCursor(parentItemCenter, currentPos);

    qreal angleToTarget{::acos(lineToTarget.dx() / lineToTarget.length())};
    qreal angleToCursor{::acos(lineToCursor.dx() / lineToCursor.length())};

    if (lineToTarget.dy() < 0) {
        angleToTarget = (TWO_PI - angleToTarget);
    }
    angleToTarget = normalizeAngle((PI - angleToTarget) + PI / 2);

    if (lineToCursor.dy() < 0) {
        angleToCursor = TWO_PI - angleToCursor;
    }
    angleToCursor = normalizeAngle((PI - angleToCursor) + PI / 2);

    qreal resultAngle{angleToTarget - angleToCursor};

    QTransform parentTransformation{parentItem()->transform()};
    parentTransformation.translate(parentItemCenter.x(), parentItemCenter.y());
    parentTransformation.rotateRadians(parentItem()->rotation() + resultAngle, Qt::ZAxis);
    parentTransformation.translate(-parentItemCenter.x(), -parentItemCenter.y());
    parentItem()->setTransform(parentTransformation);
    updateHandleItemPositions();
}

void SizeGripShape::setItemType(SizeGripShape::ItemType type) // TODO проверить необходимость
{
    m_itemType = type;
}

QPainterPath SizeGripShape::parentItemPath()
{
    return m_parentPath;
}

void SizeGripShape::setParentItemPath(QPainterPath newPath)
{
    m_parentPath.swap(newPath);
}

void SizeGripShape::setActionType(SizeGripShape::ActionType actionType)
{
    m_actionType = actionType;
    if (actionType != Rotate) {
        for (HandleItem *p_handleItem : qAsConst(handleItemList)) {
            p_handleItem->show();
        }
        return;
    }

    if ((parentItem()->type() == WallShape::Type) || (parentItem()->type() == DoorShape::Type)
            || (parentItem()->type() == WindowShape::Type)
            || (parentItem()->type() == OpenShape::Type)) {
        for (HandleItem *p_handleItem : qAsConst(handleItemList)) {
            p_handleItem->show();
        }
    } else {
        for (HandleItem *p_handleItem : qAsConst(handleItemList)) {
            if ((p_handleItem->positionFlags() == Top)
                    || (p_handleItem->positionFlags() == Bottom)
                    || (p_handleItem->positionFlags() == Left)
                    || (p_handleItem->positionFlags() == Right)) {
                p_handleItem->hide();
            }
        }
    }
}

SizeGripShape::ActionType SizeGripShape::actionType()
{
    return m_actionType;
}

void SizeGripShape::setPieHandleItem() {
    m_parentItemRect = m_ellipseShape->rect();
    QPointF linePt2{QPointF(m_parentItemRect.right(), m_centerPoint.y())};
    QLineF angleLine{m_centerPoint, linePt2};
    angleLine.setAngle(m_ellipseShape->startAngle() / 16);
    m_startPoint = angleLine.p2();
    angleLine.setAngle((m_ellipseShape->spanAngle() / 16) + (m_ellipseShape->startAngle() / 16));
    m_spanPoint = angleLine.p2();
}

void SizeGripShape::setStartPoint(const QPointF &pos) {
    m_startPoint = pos;
    QLineF startLine{m_centerPoint, m_startPoint};
    qreal startAngle{startLine.angle()};
    qreal radius{startLine.length()};
    qreal centerX{m_centerPoint.x()};
    qreal centerY{m_centerPoint.y()};
    qreal x{centerX - radius};
    qreal y{centerY - radius};
    m_ellipseShape->setStartAngle(startAngle * 16);
    m_ellipseShape->setRect(x, y, radius * 2, radius * 2); //NOTE возможно изменить (doResize())
    setPieHandleItem();
    updateHandleItemPositions();
}

void SizeGripShape::setSpanPoint(const QPointF &pos) {
    m_spanPoint = pos;
    QLineF startLine{m_centerPoint, m_startPoint};
    QLineF spanLine{m_centerPoint, m_spanPoint};
    qreal spanAngle{startLine.angleTo(spanLine)};
    qreal radius{spanLine.length()};
    qreal centerX{m_centerPoint.x()};
    qreal centerY{m_centerPoint.y()};
    qreal x{centerX - radius};
    qreal y{centerY - radius};
    m_ellipseShape->setSpanAngle(spanAngle * 16);
    m_ellipseShape->setRect(x, y, radius * 2, radius * 2);
    setPieHandleItem();
    updateHandleItemPositions();
}
