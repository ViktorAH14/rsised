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

#include "../../../../src/include/abstractshape.h"

#include <QtTest>
#include <QPainter>
#include <QGraphicsScene>
#include <QStyleOptionGraphicsItem>

class AbstractShapeTester : public AbstractShape
{
public:
    enum { Type = UserType + 1}; //RectShape

    explicit AbstractShapeTester(QGraphicsItem *parent = nullptr)
        : AbstractShape(parent)
          , m_shapeRect{QRectF(-20.0, -20.0, 40.0, 40.0)}
    {
        setFlag(ItemSendsGeometryChanges);
        setFlag(QGraphicsItem::ItemIsSelectable);
        setAcceptHoverEvents(true);
    }
    ~AbstractShapeTester() = default;

    inline int type() const override { return Type;}
    QRectF boundingRect() const override
    {
        QRectF boundingRect{m_shapeRect};
        qreal halfpw{pen().style() == Qt::NoPen ? qreal(0.0) : pen().widthF() / 2};
        if (halfpw > 0.0)
            boundingRect.adjust(-halfpw, -halfpw, halfpw, halfpw);

        return boundingRect;
    }
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override
    {
        Q_UNUSED(widget);
//        Q_UNUSED(option);

        painter->setPen(pen());
        painter->setBrush(brush());
        painter->drawRect(m_shapeRect);

        if (option->state & QStyle::State_Selected) {
             highlightSelected(painter, option);
        }
    }
//    QPainterPath shape() const override;
//    bool contains(const QPointF &point) const override;
//    bool isObscuredBy(const QGraphicsItem *item) const override;
//    QPainterPath opaqueArea() const override;

    private:
    QRectF m_shapeRect;
};

class tst_AbstractShape : public QObject
{
    Q_OBJECT

public:
    explicit tst_AbstractShape() : p_abstractShapeTester{nullptr}
    {

    }
private slots:
    void init();
    void itemChange();
    void cleanup();

private:
    AbstractShapeTester *p_abstractShapeTester;
};



void tst_AbstractShape::init()
{
    p_abstractShapeTester = new AbstractShapeTester();
}

void tst_AbstractShape::itemChange()
{
    QGraphicsScene scene;
    scene.addItem(p_abstractShapeTester);
    QCOMPARE(p_abstractShapeTester->childItems().count(), 0);
    p_abstractShapeTester->setSelected(true);
    QGraphicsItem *sizegripItem = p_abstractShapeTester->childItems().constFirst();
    QCOMPARE(sizegripItem->childItems().count(), 8);
    p_abstractShapeTester->setSelected(false);
    QCOMPARE(p_abstractShapeTester->childItems().count(), 0);
    scene.removeItem(p_abstractShapeTester);
}

void tst_AbstractShape::cleanup()
{
    delete p_abstractShapeTester;
}

QTEST_MAIN(tst_AbstractShape)

#include "tst_abstractshape.moc"
