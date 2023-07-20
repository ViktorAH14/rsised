/*
 * Copyright (c) 2022 by Viktor Ermolov <ermolovva@gmail.com>.
 *
 * This file is part of the RSiSed project, an editor of the alignment of
 * forces and means in extinguishing a fire. (RSiSed)
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

/*!
 * Constructs a AbstractShape.
 * \param parent is passed to QGraphicsItem's constructor.
 */
AbstractShape::AbstractShape(QGraphicsItem *parent)
    : QGraphicsItem(parent)
    , m_sizeGripItem{nullptr}
    , m_contextMenu{nullptr}
{
}

/*!
 * Destroys a AbstractShape
 */
AbstractShape::~AbstractShape()
{
}

/*!
 * The shape's pen
 * \return Returns the shape's pen. If no pen has been set, this function
 * returns QPen(), a default black solid line pen with 1 width.
 */
QPen AbstractShape::pen() const
{
    return m_pen;
}

/*!
 * Sets the pen for this shape.
 * \param pen[in] the pen is used to draw the shape's outline.
 */
void AbstractShape::setPen(const QPen &pen)
{
    if (m_pen == pen)
        return;
    prepareGeometryChange();
    m_pen = pen;
    update();
}

/*!
 * The shape's brush
 * \return Returns the shape's brush, or an empty brush if no brush has been set.
 */
QBrush AbstractShape::brush() const
{
    return m_brush;
}

/*!
 * Sets the brush for this shape.
 * \param brush[in] the shape's brush is used to fill the shape.
 *
 * If you use a brush with a QGradient, the gradient is relative to the shape's
 * coordinate system.
 */
void AbstractShape::setBrush(const QBrush &brush)
{
    if (m_brush == brush)
        return;
    prepareGeometryChange();
    m_brush = brush;
    update();
}

/*!
 * Reimplements: QGraphicsItem::isObscuredBy(const QGraphicsItem *item) const.
 * \param item[in] pointer to matched item.
 * \return Returns true if this shape's bounding rect is completely obscured by
 * the opaque shape of item.
 *
 * The base implementation maps item's opaqueArea() to this shape's coordinate
 * system, and then checks if this shape's boundingRect() is fully contained
 * within the mapped shape.
 */
bool AbstractShape::isObscuredBy(const QGraphicsItem *item) const
{
    return QGraphicsItem::isObscuredBy(item);
}

/*!
 * Reimplements: QGraphicsItem::opaqueArea() const.
 * \return This virtual function returns a shape representing the area where
 *  this item is opaque. An area is opaque if it is filled using an opaque
 *  brush or color (i.e., not transparent).
 *
 *  This function is used by isObscuredBy(), which is called by underlying
 *  items to determine if they are obscured by this item. The default
 *  implementation returns an empty QPainterPath, indicating that this item is
 *  completely transparent and does not obscure any other items.
 */
QPainterPath AbstractShape::opaqueArea() const
{
    if (m_brush.isOpaque())
            return isClipped() ? clipPath() : shape();
        return QGraphicsItem::opaqueArea();
}

/*!
 * This method is used to resize some shape.
 * \param newRect[in] new shape size.
 * \bug Incorrect resizing.
 * \deprecated This method will be removed when the shapes that use it are
 *  refactored.
 */
void AbstractShape::scaleShape(const QRectF &newRect)
// FIXME wrong scalling
// NOTE limit resizing
{
    prepareGeometryChange();
    QSizeF size{boundingRect().size()};
    QSizeF newSize{newRect.size()};
    qreal s_xy{((newSize.height() > size.height()) ? 1.018 : 0.988)};
    setTransform(QTransform::fromScale(s_xy, s_xy), true);
    update();
}

/*!
 * Sets the shape's context menu.
 * \param contextMenu[in] context menu pointer.
 */
void AbstractShape::setMenu(QMenu *contextMenu)
{
    m_contextMenu = contextMenu;
}

/*!
 * Shape context menu
 * \return Return's a pointer to the shape's context menu.
 */
QMenu* AbstractShape::menu() const
{
    return m_contextMenu;
}

/*!
 * Adds new actions to the shape's context menu.
 * \param actions[in] list of pointers to add actions.
 *
 * New actions are inserted after the separator.
 */
void AbstractShape::addActions(const QList<QAction *> &actions)
{
    m_contextMenu->addSeparator();
    m_contextMenu->addActions(actions);
}

/*!
 * Removes actions from the shape's context menu.
 * \param actions[in] a list of pointers to the actions to be removed.
 *
 * The separator is also removed.
 */
void AbstractShape::removeActions(const QList<QAction *> &actions)
{
    for (int i = 0; i < actions.size(); i++)
        m_contextMenu->removeAction(actions.at(i));
    m_contextMenu->removeAction(m_contextMenu->actions().constLast()); //Remove Separator
}

/*!
 * Reimplements:
 * void QGraphicsItem::mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event).
 * \param mouseEvent[in] pointer to QGraphicsSceneMouseEvent.
 *
 * If a shape is selected, then double-clicking on it changes the resize mode
 * to the rotate mode, and vice versa. Otherwise, the event is passed to the
 * default implementation, i.e. to the
 * void QGraphicsItem::mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event).
 */
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

/*!
 * Reimplements:
 * void QGraphicsItem::mouseMoveEvent(QGraphicsSceneMouseEvent *event).
 * \param mouseEvent[in] pointer to QGraphicsSceneMouseEvent.
 *
 * If the shape is selected and the left mouse button is pressed, the shape
 * will move following the mouse pointer. Otherwise, the event is passed to
 * the default implementation, i.e. to the
 * void QGraphicsItem::mouseMoveEvent(QGraphicsSceneMouseEvent *event).
 */
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
        QGraphicsItem::mouseMoveEvent(mouseEvent);
    }
}

/*!
 * Reimplements:
 * void QGraphicsItem::mousePressEvent(QGraphicsSceneMouseEvent *event).
 * \param mouseEvent[in] pointer to QGraphicsSceneMouseEvent.
 *
 * If the shape is selected and the right mouse button is pressed, then the
 * context menu for all selected shapes is called. Otherwise, the event is
 * passed to the default implementation, i.e. to the
 * void QGraphicsItem::mousePressEvent(QGraphicsSceneMouseEvent *event).
 */
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

/*!
 * Reimplements: void QGraphicsItem::wheelEvent(QGraphicsSceneWheelEvent *event).
 * \param wheelEvent[in] pointer to QGraphicsSceneWheelEvent.
 *
 * If a shape is selected, then rotating the mouse wheel will cause it to scale.
 * Otherwise, the event is passed to the default implementation, i.e. to the
 * void QGraphicsItem::wheelEvent(QGraphicsSceneWheelEvent *event).
 */
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

/*!
 * Reimplements:
 * QVariant QGraphicsItem::itemChange(QGraphicsItem::GraphicsItemChange change,
 *  const QVariant &value)
 * \param change[in] is the parameter of the item that is changing.
 * \param value[in] is the new value; the type of the value depends on change.
 * \return Returns the passed value.
 *
 * If the item's selected state changes, for example, if it is now selected,
 * it will become unselected, and vice versa. A SizeGrippShape object is
 * created, which allows you to transformations the specified shape in a
 * variety of ways.
 */
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

/*!
 * Creates a contrasting border around the chosen shape.
 * \param painter[in,out] pointer to QPainter.
 * \param option[in]  is used to describe the parameters needed to draw a shape.
 */
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

/*!
 * Ignoring dash pattern.
 * \param path[in] original QPainterPath.
 * \return  Returns a QPainterPath of path when stroked with the pen.
 */
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
