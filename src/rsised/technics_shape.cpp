#include "technics_shape.h"
#include "sizegripitem.h"
#include "rectangleresizer.h"

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
    QPolygonF polygon;
    polygon << QPointF(0.0, -37.5) << QPointF(15.0, -12.5) << QPointF(15.0, 37.5)
            << QPointF(-15.0, 37.5) << QPointF(-15.0, -12.5) << QPointF(0.0, -37.5);
    m_path.setFillRule(Qt::WindingFill);
    switch (m_shapeType) {
    case Base:
        m_path.addPolygon(polygon);
        break;
    case Tanker:
        m_path.addPolygon(polygon);
        m_path.addRoundedRect(-10.0, -12.0, 20.0, 45.0, 5.0, 5.0);
        break;
    default:
        break;
    }
    setFlag(ItemSendsGeometryChanges, true);
    setAcceptHoverEvents(true);
}

void TechnicsShape::paint(QPainter *painter, const QStyleOptionGraphicsItem *option
                          , QWidget *widget)
{
    Q_UNUSED(option);
    Q_UNUSED(widget);

    painter->setRenderHint(QPainter::Antialiasing);
    painter->setRenderHint(QPainter::SmoothPixmapTransform);
    painter->setPen(QPen(Qt::red, 1));
    painter->drawPath(m_path);
}

QRectF TechnicsShape::boundingRect() const
{
    qreal penWidth {1.0};
    return QRectF(-15.0 - penWidth / 2.0, -37.5 - penWidth / 2.0
                  , 30.0 + penWidth, 75.0 + penWidth);
}

QPainterPath TechnicsShape::shape() const
{
    return m_path;
}

QVariant TechnicsShape::itemChange(GraphicsItemChange change, const QVariant &value)
{
    if (change == GraphicsItemChange::ItemSelectedChange && value == true) {
        m_sizeGripItem = new SizeGripItem(new RectangleResizer, this);
    }
    if (change == GraphicsItemChange::ItemSelectedChange && value == false) {
        delete  m_sizeGripItem;
    }

    return QGraphicsItem::itemChange(change, value);
}

QPixmap TechnicsShape::image() const
{
    QPixmap pixmap(36, 76);
    pixmap.fill(Qt::transparent);
    QPainter painter(&pixmap);
    painter.setPen(QPen(Qt::red, 2));
    painter.translate(18, 38);
    painter.drawPath(m_path);

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
    m_sizeGripItem->setActionType((m_sizeGripItem->actionType()
                                          == SizeGripItem::Resize) ? SizeGripItem::Rotate
                                                                   :SizeGripItem::Resize);

    QGraphicsItem::mouseDoubleClickEvent(mouseEvent);
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
