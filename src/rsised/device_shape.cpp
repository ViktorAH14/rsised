#include "device_shape.h"
#include "sizegripitem.h"
#include "item_resizer.h"

#include <cmath>

#include <QGraphicsScene>
#include <QGraphicsSceneMouseEvent>
#include <QPainter>
#include <QMenu>

DeviceShape::DeviceShape(QMenu *contextMenu, ShapeType shapeType, QGraphicsItem *parent)
    : QAbstractGraphicsShapeItem(parent)
    , m_shapeType{shapeType}
    , m_contextMenu{contextMenu}
{
    setFlag(ItemSendsGeometryChanges, true);
    setAcceptHoverEvents(true);
}

void DeviceShape::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(option);
    Q_UNUSED(widget);

    drawShape(painter);
}

QRectF DeviceShape::boundingRect() const
{
    qreal penWidth {2.0};

    return QRectF(-28.0 - penWidth / 2.0, -16.0 - penWidth / 2.0
                  , 56.0 + penWidth, 32.0 + penWidth);
}

QPixmap DeviceShape::image()
{
    QPixmap pixmap(60, 40);
    pixmap.fill(Qt::transparent);
    QPainter *painter = new QPainter(&pixmap);
    painter->translate(30, 20);
    drawShape(painter);

    return pixmap;
}

void DeviceShape::scaleDeviceShape(const QRectF &newRect)
{
    prepareGeometryChange();
    QRectF oldRect {boundingRect()};
    qreal oldSize = sqrt(oldRect.width() * oldRect.width() + oldRect.height() * oldRect.height());
    qreal newSize = sqrt(newRect.width() * newRect.width() + newRect.height() * newRect.height());
    qreal scaleFactor = newSize / oldSize;
    setTransform(QTransform::fromScale(scaleFactor, scaleFactor), true);
    update();
}

DeviceShape::ShapeType DeviceShape::shapeType() const
{
    return m_shapeType;
}

void DeviceShape::mouseDoubleClickEvent(QGraphicsSceneMouseEvent *mouseEvent)
{
    if (isSelected()) {
        m_sizeGripItem->setActionType((m_sizeGripItem->actionType()
                                       == SizeGripItem::Resize) ? SizeGripItem::Rotate
                                                                :SizeGripItem::Resize);
    } else {
        QGraphicsItem::mouseDoubleClickEvent(mouseEvent);
    }
}

void DeviceShape::mouseMoveEvent(QGraphicsSceneMouseEvent *mouseEvent)
{
    if ((mouseEvent->buttons() == Qt::LeftButton) && isSelected()) {
        qreal dx = mouseEvent->scenePos().x() - mouseEvent->lastScenePos().x();
        qreal dy = mouseEvent->scenePos().y() - mouseEvent->lastScenePos().y();
        moveBy(dx, dy);
    } else {
        QGraphicsItem::mouseMoveEvent( mouseEvent );
    }
}

void DeviceShape::contextMenuEvent(QGraphicsSceneContextMenuEvent *event)
{
    scene()->clearSelection();
    setSelected(true);
    m_contextMenu->exec(event->screenPos());
}

void DeviceShape::wheelEvent(QGraphicsSceneWheelEvent *wheelEvent)
{
    if (isSelected()) {
        qreal s_xy {(wheelEvent->delta() > 0) ? 1.03 : 0.97};
        setTransform(QTransform::fromScale(s_xy, s_xy), true);
    } else {
        QGraphicsItem::wheelEvent(wheelEvent);
    }
}

QVariant DeviceShape::itemChange(GraphicsItemChange change, const QVariant &value)
{
    if (change == GraphicsItemChange::ItemSelectedChange && value == true) {
        m_sizeGripItem = new SizeGripItem(new ItemResizer, this);
    }
    if (change == GraphicsItemChange::ItemSelectedChange && value == false) {
        delete  m_sizeGripItem;
    }

    return QGraphicsItem::itemChange(change, value);
}

void DeviceShape::drawShape(QPainter *painter)
{
    painter->setRenderHint(QPainter::Antialiasing);
    painter->setRenderHint(QPainter::SmoothPixmapTransform);
    painter->setPen(QPen(Qt::black, 3));

    switch (m_shapeType) {
    case Barrel: {
        painter->drawLine(QLineF(-4.0, 16.0, 4.0, 16.0));
        painter->drawLine(QLineF(0.0, 14.0, 0.0, -14.0));
        painter->drawLine(QLineF(-6.0, -10.0, 0.0, -16.0));
        painter->drawLine(QLineF(0.0, -16.0, 6.0, -10.0));
        break;
    }
    case Branches_3: {
        painter->drawLine(QLineF(-4.0, 16.0, 4.0, 16.0));
        painter->drawLine(QLineF(0.0, 14.0, 0.0, -14.0));
        painter->drawLine(QLineF(-16.0, 4.0, 16.0, 4.0));
        painter->drawLine(QLineF(-16.0, 4.0, -16.0, -14.0));
        painter->drawLine(QLineF(-20.0, -16.0, -12.0, -16.0));
        painter->drawLine(QLineF(-4.0, -16.0, 4.0, -16.0));
        painter->drawLine(QLineF(16.0, 4.0, 16.0, -14.0));
        painter->drawLine(QLineF(12.0, -16.0, 20.0, -16.0));
        break;
    }
    case Branches_4: {
        painter->drawLine(QLineF(-4.0, 16.0, 4.0, 16.0));
        painter->drawLine(QLineF(0.0, 14.0, 0.0, 4.0));
        painter->drawLine(QLineF(-24.0, 4.0, 24.0, 4.0));
        painter->drawLine(QLineF(-24.0, 4.0, -24.0, -14.0));
        painter->drawLine(QLineF(-28.0, -16.0, -20.0, -16.0));
        painter->drawLine(QLineF(-8.0, 4.0, -8.0, -14.0));
        painter->drawLine(QLineF(-12.0, -16.0, -4.0, -16.0));
        painter->drawLine(QLineF(8.0, 4.0, 8.0, -14.0));
        painter->drawLine(QLineF(12.0, -16.0, 4.0, -16.0));
        painter->drawLine(QLineF(24.0, 4.0, 24.0, -14.0));
        painter->drawLine(QLineF(20.0, -16.0, 28.0, -16.0));
        break;
    }
    case Collector: {
        painter->drawLine(QLineF(-4.0, 16.0, 4.0, 16.0));
        painter->drawLine(QLineF(0.0, 14.0, 0.0, -2.0));
        painter->drawLine(QLineF(0.0, -2.0, -12.0, -14.0));
        painter->drawLine(QLineF(0.0, -2.0, 12.0, -14.0));
        painter->drawLine(QLineF(-17.0, -11.0, -8.0, -17.0));
        painter->drawLine(QLineF(17.0, -11.0, 8.0, -17.0));
        break;
    }
    default:
        break;
    }
}
