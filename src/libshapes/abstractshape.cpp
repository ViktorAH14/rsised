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

#include "../include/abstractshape.h"
#include "../include/sizegripshape.h"
#include "../include/shaperesizer.h"

#include <QGraphicsScene>
#include <QGraphicsSceneMouseEvent>
#include <QPainter>
#include <QStyleOptionGraphicsItem>

AbstractShape::AbstractShape(QGraphicsItem *parent)
    : QGraphicsItem(parent)
    , m_sizeGripItem{nullptr}
    , m_contextMenu{new QMenu()}
{
}

AbstractShape::~AbstractShape()
{
    m_contextMenu->deleteLater();
}

QPen AbstractShape::pen() const
{
    return m_pen;
}

void AbstractShape::setPen(const QPen &pen)
{
    if (m_pen == pen)
        return;
    prepareGeometryChange();
    m_pen = pen;
    update();
}

QBrush AbstractShape::brush() const
{
    return m_brush;
}

void AbstractShape::setBrush(const QBrush &brush)
{
    if (m_brush == brush)
        return;
    prepareGeometryChange();
    m_brush = brush;
    update();
}

bool AbstractShape::isObscuredBy(const QGraphicsItem *item) const
{
    return QGraphicsItem::isObscuredBy(item);
}

QPainterPath AbstractShape::opaqueArea() const
{
    if (m_brush.isOpaque())
            return isClipped() ? clipPath() : shape();
        return QGraphicsItem::opaqueArea();
}

void AbstractShape::scaleShape(const QRectF &newRect)
// FIXME не совсем коректное масштабирование
// NOTE Ограничить изменение размера определённым значением
{
    prepareGeometryChange();
    QSizeF size{boundingRect().size()};
    QSizeF newSize{newRect.size()};
    qreal s_xy{((newSize.height() > size.height()) ? 1.018 : 0.988)};
    setTransform(QTransform::fromScale(s_xy, s_xy), true);
    update();
}

void AbstractShape::setMenu(QMenu *contextMenu) //TODO удалить после рефакторинга libshapes
{
    QList<QAction *> actionList{contextMenu->actions()};
    if (!m_contextMenu->isEmpty())
        m_contextMenu->addSeparator();
    for (int i = 0; i < actionList.size(); i++)
        m_contextMenu->addAction(actionList.at(i));
}

QMenu* AbstractShape::menu() const
{
    return m_contextMenu;
}

void AbstractShape::addActions(const QList<QAction *> &actions)
{
    for (int i = 0; i < actions.size(); i++)
        m_contextMenu->addAction(actions.at(i));
}

void AbstractShape::mouseDoubleClickEvent(QGraphicsSceneMouseEvent *mouseEvent)
{
    if (isSelected()) {
        m_sizeGripItem->setActionType((m_sizeGripItem->actionType()
                                       == SizeGripShape::Resize) ? SizeGripShape::Rotate
                                                                :SizeGripShape::Resize);
    } else {
        QGraphicsItem::mouseDoubleClickEvent(mouseEvent);
    }
}

void AbstractShape::mouseMoveEvent(QGraphicsSceneMouseEvent *mouseEvent)
{
    if ((mouseEvent->buttons() == Qt::LeftButton) && isSelected()) {
        QList<QGraphicsItem *> selectedShapeList = scene()->selectedItems();
        for (QGraphicsItem *p_shape : qAsConst(selectedShapeList)) {
            qreal dx{mouseEvent->scenePos().x() - mouseEvent->lastScenePos().x()};
            qreal dy{mouseEvent->scenePos().y() - mouseEvent->lastScenePos().y()};
            p_shape->moveBy(dx, dy);
        }
    } else {
        QGraphicsItem::mouseMoveEvent( mouseEvent );
    }
}

void AbstractShape::mousePressEvent(QGraphicsSceneMouseEvent *mouseEvent)
{
    if ((mouseEvent->buttons() == Qt::RightButton) && isSelected() && m_contextMenu != nullptr) {
        QList<QGraphicsItem *> selectedShapeList = scene()->selectedItems();
        for (QGraphicsItem *p_shape : qAsConst(selectedShapeList))
            p_shape->setSelected(true);
        m_contextMenu->exec(mouseEvent->screenPos());
    } else {
        QGraphicsItem::mousePressEvent(mouseEvent);
    }
}

void AbstractShape::wheelEvent(QGraphicsSceneWheelEvent *wheelEvent)
{
    if (isSelected()) {
        prepareGeometryChange();
        qreal s_xy{((wheelEvent->delta() > 0) ? 1.03 : 0.97)};
        QTransform shapeTransform = transform();
        shapeTransform.translate(boundingRect().center().x(), boundingRect().center().y());
        shapeTransform.scale(s_xy, s_xy);
        shapeTransform.translate(-boundingRect().center().x(), -boundingRect().center().y());
        setTransform(shapeTransform);
        update();
     } else {
        QGraphicsItem::wheelEvent(wheelEvent);
     }
}

QVariant AbstractShape::itemChange(GraphicsItemChange change, const QVariant &value)
{
    if (change == GraphicsItemChange::ItemSelectedChange && value == true) {
        m_sizeGripItem = new SizeGripShape(new ShapeResizer, this);
    }
    if (change == GraphicsItemChange::ItemSelectedChange && value == false) {
        delete  m_sizeGripItem;
    }

    return QGraphicsItem::itemChange(change, value);
}

void AbstractShape::highlightSelected(QPainter *painter, const QStyleOptionGraphicsItem *option)
{
    const QRectF murect{painter->transform().mapRect(QRectF(0, 0, 1, 1))};
    if (qFuzzyIsNull(qMax(murect.width(), murect.height())))
        return;
    const QRectF mbrect{painter->transform().mapRect(boundingRect())};
    if (qMin(mbrect.width(), mbrect.height()) < qreal(1.0))
        return;
    qreal shapePenWidth{pen().widthF()};
    const qreal pad{shapePenWidth / 2};
    const qreal penWidth{0};
    const QColor fgcolor{option->palette.windowText().color()};
    const QColor bgcolor{fgcolor.red()   > 127 ? 0 : 255,
                        fgcolor.green() > 127 ? 0 : 255,
                        fgcolor.blue()  > 127 ? 0 : 255};
    painter->setPen(QPen(bgcolor, penWidth, Qt::SolidLine));
    painter->setBrush(Qt::NoBrush);
    painter->drawRect(boundingRect().adjusted(pad, pad, -pad, -pad));
    painter->setPen(QPen(option->palette.windowText(), 0, Qt::DashLine));
    painter->setBrush(Qt::NoBrush);
    painter->drawRect(boundingRect().adjusted(pad, pad, -pad, -pad));
}

QPainterPath AbstractShape::shapeFromPath(const QPainterPath &path) const
{
        const qreal penWidthZero{qreal(0.00000001)};
        QPen shapePen{pen()};
        if (path == QPainterPath() || shapePen == Qt::NoPen)
            return path;
        QPainterPathStroker ps;
        ps.setCapStyle(shapePen.capStyle());
        if (shapePen.widthF() <= 0.0)
            ps.setWidth(penWidthZero);
        else
            ps.setWidth(shapePen.widthF());
        ps.setJoinStyle(shapePen.joinStyle());
        ps.setMiterLimit(shapePen.miterLimit());
        QPainterPath p{ps.createStroke(path)};
        p.addPath(path);
        return p;
}
