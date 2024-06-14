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

#include "../../../../src/include/rectshape.h"

#include <QtTest>
#include <QGraphicsScene>
#include <QGraphicsView>

class tst_RectShape : public QObject
{
    Q_OBJECT

private slots:
    void constructor();
    void type();
    void boundingRect();
    void rect_setRect_data();
    void rect_setRect();
    void shape();
    void contains();
    void paint();
    void isObscuredBy();
    void opaqueArea();
};

void tst_RectShape::constructor()
{
    RectShape *p_rectShape = nullptr;

    p_rectShape = new RectShape;
    p_rectShape->setPen(QPen(Qt::black, 0));
    QVERIFY2(p_rectShape, "rectShape nullptr");
    QCOMPARE(int(p_rectShape->type()), int(QGraphicsItem::UserType + 1));
    QCOMPARE(p_rectShape->flags(), 0x800); //ItemSendsGeometryChanges true
    QVERIFY(p_rectShape->acceptHoverEvents());
    QCOMPARE(p_rectShape->rect(), QRectF());
    delete p_rectShape;

    QRectF rect(-5.0, -5.0, 5.0, 5.0);
    p_rectShape = new RectShape(rect);
    p_rectShape->setPen(QPen(Qt::black, 0));
    QVERIFY2(p_rectShape, "rectShape nullptr");
    QCOMPARE(int(p_rectShape->type()), int(QGraphicsItem::UserType + 1));
    QCOMPARE(p_rectShape->flags(), 0x800);
    QVERIFY(p_rectShape->acceptHoverEvents());
    QCOMPARE(p_rectShape->rect(), rect);
    delete p_rectShape;

    qreal x{rect.topLeft().x()};
    qreal y{rect.topLeft().y()};
    qreal w{rect.width()};
    qreal h{rect.height()};
    p_rectShape = new RectShape(x, y, w, h);
    p_rectShape->setPen(QPen(Qt::black, 0));
    QVERIFY2(p_rectShape, "rectShape nullptr");
    QCOMPARE(int(p_rectShape->type()), int(QGraphicsItem::UserType + 1));
    QCOMPARE(p_rectShape->flags(), 0x800);
    QVERIFY(p_rectShape->acceptHoverEvents());
    QCOMPARE(p_rectShape->rect(), rect);
    delete p_rectShape;
}

void tst_RectShape::type()
{
    RectShape rectShape;
    QCOMPARE(rectShape.type(), QGraphicsItem::UserType + 1);
}

void tst_RectShape::boundingRect()
{
    QRectF rect(-40.1, -40.2, 40.3, 40.4);
    RectShape rectShape(rect);
    rectShape.setPen(QPen(Qt::NoPen));
    QCOMPARE(rectShape.boundingRect(), rect);
    rectShape.setPen(QPen(Qt::green, 0));
    QCOMPARE(rectShape.boundingRect(), rect);
    QPen shapePen(Qt::gray, 4);
    qreal halfpw = shapePen.widthF() / 2;
    rect.adjust(-halfpw, -halfpw, halfpw, halfpw);
    rectShape.setPen(shapePen);
    QCOMPARE(rectShape.boundingRect(), rect);
}

void tst_RectShape::rect_setRect_data()
{
    QTest::addColumn<QRectF>("rect");
    QTest::newRow("rect_0") << QRectF(0.0, 0.0, 0.0, 0.0);
    QTest::newRow("rect_1") << QRectF(0.1, 0.0, 0.0, 0.0);
    QTest::newRow("rect_2") << QRectF(0.1, 0.1, 0.0, 0.0);
    QTest::newRow("rect_3") << QRectF(0.1, 0.1, 0.1, 0.0);
    QTest::newRow("rect_4") << QRectF(0.1, 0.1, 0.1, 0.1);
    QTest::newRow("rect_5") << QRectF(-0.1, 0.0, 0.0, 0.0);
    QTest::newRow("rect_6") << QRectF(-0.1, -0.1, 0.0, 0.0);
    QTest::newRow("rect_7") << QRectF(-0.1, -0.1, -0.1, 0.0);
    QTest::newRow("rect_8") << QRectF(-0.1, -0.1, -0.1, -0.1);
    QTest::newRow("rect_9") << QRectF(-0.1, 0.1, -0.1, 0.1);
    QTest::newRow("rect_10") << QRectF(0.1, -0.1, 0.1, -0.1);
    QTest::newRow("rect_11") << QRectF(-20.0, -20.0, 40.0, 40.0);
    QTest::newRow("rect_12") << QRectF(-100.1, -100.2, 200.9, 200.9);
    QTest::newRow("rect_12") << QRectF(-999999999.9, -999999999.9, 999999999.9, 999999999.9);
    QTest::newRow("rect_13") << QRectF(999999999.9, 999999999.9, 999999999.9, 999999999.9);
}

void tst_RectShape::rect_setRect()
{
    QFETCH(QRectF, rect);

    RectShape rectShape;
    rectShape.setRect(rect);
    QCOMPARE(rectShape.rect(), rect);

    qreal x{rect.topLeft().x()};
    qreal y{rect.topLeft().y()};
    qreal w{rect.width()};
    qreal h{rect.height()};
    RectShape rectShape2;
    rectShape2.setRect(x, y, w, h);
    QCOMPARE(rectShape2.rect(), rect);
}

void tst_RectShape::shape()
{
    const qreal penWidthZero = qreal(0.00000001);
    QPainterPathStroker ps;
    ps.setWidth(penWidthZero);
    RectShape rect(-10.0, -10.0, 20.0, 20.0);
    rect.setPen(QPen(Qt::black, 0));
    QPainterPath path;
    path.addRect(rect.rect());
    QPainterPath p = ps.createStroke(path);
    p.addPath(path);
    QCOMPARE(rect.shape(), p);

    path.clear();
    p.clear();
    rect.setRect(QRectF());
    path.addRect(rect.rect());
    p = ps.createStroke(path);
    p.addPath(path);
    QCOMPARE(rect.shape(), p);
}

void tst_RectShape::contains()
{
    if (sizeof(qreal) != sizeof(double))
        QSKIP("Skipped due to rounding errors");

    RectShape rectShape(QRectF(-10, -10, 20, 20));
    QVERIFY(!rectShape.contains(QPointF(-11, -10)));
    QVERIFY(rectShape.contains(QPointF(-10, -10)));
    QVERIFY(!rectShape.contains(QPointF(-11, 0)));
    QVERIFY(rectShape.contains(QPointF(-10, 0)));
    QVERIFY(rectShape.contains(QPointF(0, -10)));
    QVERIFY(rectShape.contains(QPointF(0, 0)));
    QVERIFY(rectShape.contains(QPointF(9, 9)));
}

class PaintTester : public RectShape
{
public:
    PaintTester() : m_widget(NULL), m_painted(0)
    {
        setFlag(QGraphicsItem::ItemIsSelectable, true);
        setRect(10.0, 10.0, 20.0, 20.0);
    }

    void paint(QPainter *p, const QStyleOptionGraphicsItem *s, QWidget *w)
    {
        RectShape::paint(p, s, w);
        m_widget = w;
        m_painted++;
    }

    QWidget*  m_widget;
    int m_painted;
};

void tst_RectShape::paint()
{
    QGraphicsScene scene;
    PaintTester paintTester;
    scene.addItem(&paintTester);
    QGraphicsView view(&scene);
    view.show();
    QCOMPARE(paintTester.m_painted, 0);
    paintTester.setSelected(true);
    QVERIFY(QTest::qWaitForWindowExposed(&view));
    QApplication::processEvents();
    QTRY_VERIFY(paintTester.m_painted > 0);
    QTRY_COMPARE(paintTester.m_widget, view.viewport());
}

void tst_RectShape::isObscuredBy()
{
    RectShape rect1;
    rect1.setRect(-50.0, -50.0, 50.0, 50.0);
    rect1.setBrush(QBrush(Qt::red));

    RectShape rect2;
    rect2.setRect(-30.0, -30.0, 20.0, 20.0);
    rect2.setBrush(QBrush(Qt::blue));
    rect2.setZValue(-1.0);

    QVERIFY(!rect1.isObscuredBy(&rect2));
    QVERIFY(rect2.isObscuredBy(&rect1));

    rect2.setPos(-30.0, -30.0);
    QVERIFY(!rect1.isObscuredBy(&rect2));
    QVERIFY(!rect2.isObscuredBy(&rect1));

    rect2.setPos(-100.0, -100.0);
    QVERIFY(!rect1.isObscuredBy(&rect2));
    QVERIFY(!rect2.isObscuredBy(&rect1));
}

void tst_RectShape::opaqueArea()
{
    RectShape *p_rectShape = new RectShape(-100.0, -100.0, 200.0, 200.0);
    p_rectShape->setZValue(-1.0);
    QPainterPath opaquePath;
    QCOMPARE(p_rectShape->opaqueArea(), opaquePath);

    p_rectShape->setBrush(QBrush(Qt::red));
    QCOMPARE(p_rectShape->opaqueArea(), p_rectShape->shape());

    RectShape *p_opaqueShape = new RectShape(-50.0, -50.0, 200.0, 200.0);
    p_opaqueShape->setBrush(QBrush(Qt::blue));
    p_rectShape->setFlag(QGraphicsItem::ItemClipsToShape, true);
    QCOMPARE(p_rectShape->opaqueArea(), p_rectShape->clipPath());

    RectShape *p_parentShape = new RectShape(-120.0, -120.0, 200.0, 200.0, p_rectShape);
    p_parentShape->setBrush(QBrush(Qt::black));
    QCOMPARE(p_rectShape->opaqueArea(), p_rectShape->clipPath());

    p_rectShape->setFlag(QGraphicsItem::ItemClipsChildrenToShape, true);
    QCOMPARE(p_parentShape->opaqueArea(), p_parentShape->clipPath());

    delete p_parentShape;
    delete p_opaqueShape;
    delete p_rectShape;
}

QTEST_MAIN(tst_RectShape)

#include "tst_rectshape.moc"
