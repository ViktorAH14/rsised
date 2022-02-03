#include "technics_shape.h"
#include "sizegripitem.h"
#include "item_resizer.h"

#include <cmath>

#include <QGraphicsScene>
#include <QGraphicsSceneMouseEvent>
#include <QPainter>
#include <QMenu>

TechnicsShape::TechnicsShape(QMenu *contextMenu, ShapeType shapeType, QGraphicsItem *parent)
    : QAbstractGraphicsShapeItem(parent)
    , m_shapeType{shapeType}
    , m_contextMenu{contextMenu}
{
    setFlag(ItemSendsGeometryChanges, true);
    setAcceptHoverEvents(true);
}

void TechnicsShape::paint(QPainter *painter, const QStyleOptionGraphicsItem *option
                          , QWidget *widget)
{
    Q_UNUSED(option);
    Q_UNUSED(widget);

    drawShape(painter);
}

QRectF TechnicsShape::boundingRect() const
{
    qreal penWidth {1.0};
    return QRectF(-15.0 - penWidth / 2.0, -37.5 - penWidth / 2.0
                  , 30.0 + penWidth, 75.0 + penWidth);
}

void TechnicsShape::drawShape(QPainter *painter)
{
    painter->setRenderHint(QPainter::Antialiasing);
    painter->setRenderHint(QPainter::SmoothPixmapTransform);
    QPolygonF autoBase;
    autoBase << QPointF(0.0, -37.5) << QPointF(15.0, -12.5) << QPointF(15.0, 37.5)
            << QPointF(-15.0, 37.5) << QPointF(-15.0, -12.5) << QPointF(0.0, -37.5);
    painter->setBrush(QBrush(Qt::white));
    switch (m_shapeType) {
    case Base: {
        painter->setPen(QPen(Qt::red, 1));
        painter->drawPolygon(autoBase);
        break;
    }
    case Tanker: {
        painter->setPen(QPen(Qt::red, 1));
        painter->drawPolygon(autoBase);
        painter->drawRoundedRect(-10.0, -12.0, 20.0, 45.0, 5.0, 5.0);
        break;
    }
    case AutoPump: {
        QPolygonF pump;
        pump << QPointF(-10.0, 37.5) << QPointF(-10.0, 25.0) << QPointF(10.0, 25.0)
             << QPointF(10.0, 37.5);
        painter->setPen(QPen(Qt::red, 1));
        painter->drawPolygon(autoBase);
        painter->drawPolygon(pump);
        break;
    }
    case AutoLadder: {
        painter->setPen(QPen(Qt::red, 1));
        painter->drawPolygon(autoBase);
        QVector<QLineF> ladder;
        ladder.append(QLineF(-10.0, 32.5, -10.0, -12.5));
        ladder.append(QLineF(10.0, 32.5, 10.0, -12.5));
        ladder.append(QLineF(-10.0, 25.0, 10.0, 25.0));
        ladder.append(QLineF(-10.0, 20.0, 10.0, 20.0));
        ladder.append(QLineF(-10.0, 15.0, 10.0, 15.0));
        ladder.append(QLineF(-10.0, 10.0, 10.0, 10.0));
        ladder.append(QLineF(-10.0, 5.0, 10.0, 5.0));
        ladder.append(QLineF(-10.0, 0.0, 10.0, 0.0));
        ladder.append(QLineF(-10.0, -5.0, 10.0, -5.0));
        painter->drawLines(ladder);
        break;
    }
    case CrankLift: {
        painter->setPen(QPen(Qt::red, 1));
        painter->drawPolygon(autoBase);
        QPolygonF crank;
        crank << QPointF(-10.0, -12.5) << QPointF(-10.0, 32.5) << QPointF(10.0, -12.5)
              <<QPointF(10.0, 32.5);
        painter->drawPolyline(crank);
        break;
    }
    case TelescopicLift: {
        painter->setPen(QPen(Qt::red, 1));
        painter->drawPolygon(autoBase);
        QVector<QLineF> telescopic;
        telescopic.append(QLineF(-10.0, 32.5, -10.0, -12.5));
        telescopic.append(QLineF(0.0, 20.0, 0.0, -25.0));
        telescopic.append(QLineF(10.0, 32.5, 10.0, -12.5));
        painter->drawLines(telescopic);
        break;
    }
    case Tracked: {
        painter->setPen(QPen(Qt::red, 1));
        painter->drawPolygon(autoBase);
        painter->drawLine(QLineF(-10.0, 37.5, -10.0, -20.5));
        painter->drawLine(QLineF(10.0, 37.5, 10.0, -20.5));
        break;
    }
    case Adapted: {
        painter->setPen(QPen(Qt::black, 1));
        painter->drawPolygon(autoBase);
        QPolygonF adaptedPolygon;
        adaptedPolygon << QPointF(-8.0, 36.5) << QPointF(-8.0, -22.5) << QPointF(0.0, -36.0)
                       << QPointF(8.0, -22.5) << QPointF(8.0, 36.5);
        painter->setPen(QPen(Qt::red, 1));
        painter->setBrush(QBrush(Qt::red));
        painter->drawPolygon(adaptedPolygon);
        break;
    }
    case Ambulance: {
        painter->setPen(QPen(Qt::black, 1));
        painter->drawPolygon(autoBase);
        QPolygonF ambulancePolygon;
        ambulancePolygon << QPointF(-3.0, 9.0) << QPointF(-3.0, 3.0) << QPointF(-9.0, 3.0)
                         << QPointF(-9.0, -3.0) << QPointF(-3.0, -3.0) << QPointF(-3.0, -9.0)
                         << QPointF(3.0, -9.0) << QPointF(3.0, -3.0) << QPointF(9.0, -3.0)
                         << QPointF(9.0, 3.0) << QPointF(3.0, 3.0) << QPointF(3.0, 9.0);
        painter->setPen(QPen(Qt::red, 1));
        painter->setBrush(QBrush(Qt::red));
        painter->drawPolygon(ambulancePolygon);
        break;
    }
    case Police: {
        painter->setPen(QPen(Qt::black, 1));
        painter->drawPolygon(autoBase);
        painter->rotate(-90);
        painter->drawText(boundingRect(), Qt::AlignCenter, "МВД");
        break;
    }
    case Train: {
        QPolygonF train;
        train << QPointF(-15.0, 25.0) << QPointF(-15.0, 10.0) << QPointF(-7.0, 10.0)
              << QPointF(-7.0, -25.0) << QPointF(7.0, -25.0) << QPointF(7.0, 10.0)
              << QPointF(15.0, 10.0) << QPointF(15.0, 25.0);
        painter->setPen(QPen(Qt::red, 1));
        painter->drawPolygon(train);
        break;
    }
    case OtherAdapted: {
        painter->setPen(QPen(Qt::black, 1));
        painter->drawRect(QRectF(-15.0, -10.0, 30.0, 41));
        painter->drawLine(QLineF(0.0, -10.0, 0.0, -30.0));
        painter->drawEllipse(QRectF(-4.0, -38.0, 8.0, 8.0));
        painter->setPen(QPen(Qt::red, 1));
        painter->setBrush(QBrush(Qt::red));
        painter->drawRect(QRectF(-8.0, -9.0, 16.0, 39.0));
        break;
    }
    default:
        break;
    }
}

QVariant TechnicsShape::itemChange(GraphicsItemChange change, const QVariant &value)
{
    if (change == GraphicsItemChange::ItemSelectedChange && value == true) {
        m_sizeGripItem = new SizeGripItem(new ItemResizer, this);
    }
    if (change == GraphicsItemChange::ItemSelectedChange && value == false) {
        delete  m_sizeGripItem;
    }

    return QGraphicsItem::itemChange(change, value);
}

QPixmap TechnicsShape::image()
{
    QPixmap pixmap(36, 76);
    pixmap.fill(Qt::transparent);
    QPainter *painter = new QPainter(&pixmap);
    painter->translate(18, 38);
    drawShape(painter);

    return pixmap;
}

void TechnicsShape::scaleTechnicsShape(const QRectF &newRect)
{
    prepareGeometryChange();
    QRectF oldRect {boundingRect()};
    qreal oldSize = sqrt(oldRect.width() * oldRect.width() + oldRect.height() * oldRect.height());
    qreal newSize = sqrt(newRect.width() * newRect.width() + newRect.height() * newRect.height());
    qreal scaleFactor = newSize / oldSize;
    setTransform(QTransform::fromScale(scaleFactor, scaleFactor), true);
    update();
}

TechnicsShape::ShapeType TechnicsShape::shapeType() const
{
    return m_shapeType;
}

void TechnicsShape::mouseDoubleClickEvent(QGraphicsSceneMouseEvent *mouseEvent)
{
    if (isSelected()) {
        m_sizeGripItem->setActionType((m_sizeGripItem->actionType()
                                       == SizeGripItem::Resize) ? SizeGripItem::Rotate
                                                                :SizeGripItem::Resize);
    } else {
        QGraphicsItem::mouseDoubleClickEvent(mouseEvent);
    }
}

void TechnicsShape::mouseMoveEvent(QGraphicsSceneMouseEvent *mouseEvent)
{
    if ((mouseEvent->buttons() == Qt::LeftButton) && isSelected()) {
        qreal dx = mouseEvent->scenePos().x() - mouseEvent->lastScenePos().x();
        qreal dy = mouseEvent->scenePos().y() - mouseEvent->lastScenePos().y();
        moveBy(dx, dy);
    } else {
        QGraphicsItem::mouseMoveEvent( mouseEvent );
    }
}

bool TechnicsShape::sceneEvent(QEvent *event)
{
    QList<QGraphicsItem *>selItems = scene()->selectedItems();
    if (selItems.count() > 1) {
        QGraphicsSceneMouseEvent *mouseEvent = static_cast<QGraphicsSceneMouseEvent *>(event);
        for (QGraphicsItem *item : qAsConst(selItems))
            item->setSelected(true);

        if ((event->type() == QEvent::GraphicsSceneMousePress)
                && (mouseEvent->buttons() == Qt::RightButton))
                m_contextMenu->exec(mouseEvent->screenPos());
        if ((event->type() == QEvent::GraphicsSceneMouseMove)
                && (mouseEvent->buttons() == Qt::LeftButton)) {
            for (QGraphicsItem *item : qAsConst(selItems)) {
                qreal dx = mouseEvent->scenePos().x() - mouseEvent->lastScenePos().x();
                qreal dy = mouseEvent->scenePos().y() - mouseEvent->lastScenePos().y();
                item->moveBy(dx, dy);
            }
        }
        return true;
    } else {
       return QGraphicsItem::sceneEvent(event);
    }
}

void TechnicsShape::contextMenuEvent(QGraphicsSceneContextMenuEvent *event)
{
    scene()->clearSelection();
    setSelected(true);
    m_contextMenu->exec(event->screenPos());
}

void TechnicsShape::wheelEvent(QGraphicsSceneWheelEvent *wheelEvent)
{
    if (isSelected()) {
        qreal s_xy {(wheelEvent->delta() > 0) ? 1.03 : 0.97};
        setTransform(QTransform::fromScale(s_xy, s_xy), true);
    } else {
        QGraphicsItem::wheelEvent(wheelEvent);
    }
}
