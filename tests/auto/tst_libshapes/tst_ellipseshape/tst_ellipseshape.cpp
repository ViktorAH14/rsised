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

#include "../../../../src/include/ellipseshape.h"
#include "../../../../src/include/sizegripshape.h"

#include <QtTest>

#include <QGraphicsScene>
#include <QGraphicsView>
#include <QGraphicsSceneMouseEvent>
#include <QMenu>
#include <QSignalSpy>

static void sendMousePress(QGraphicsScene *scene, const QPointF &point
                           , Qt::MouseButton button = Qt::LeftButton
                            , Qt::KeyboardModifier modifier = Qt::NoModifier)
{
    QGraphicsSceneMouseEvent event(QEvent::GraphicsSceneMousePress);
    event.setScenePos(point);
    event.setButton(button);
    event.setButtons(button);
    event.setModifiers(modifier);
    QApplication::sendEvent(scene, &event);
}
static void sendMouseMove(QGraphicsScene *scene, const QPointF &point,
                          Qt::MouseButton button = Qt::NoButton)
{
    QGraphicsSceneMouseEvent event(QEvent::GraphicsSceneMouseMove);
    event.setScenePos(point);
    event.setButton(button);
    event.setButtons(button);
    QApplication::sendEvent(scene, &event);
}

static void sendMouseWheel(QGraphicsScene *scene, const QPointF &point, int delta)
{
    QGraphicsSceneWheelEvent wheelEvent(QEvent::GraphicsSceneWheel);
    wheelEvent.setScenePos(point);
    wheelEvent.setDelta(delta);
    QApplication::sendEvent(scene, &wheelEvent);
}

class tst_EllipseShape : public QObject
{
    Q_OBJECT

private slots:
    void constructor();
    void type();
    void boundingRect();
    void paint();
    void shape();
    void contains();
    void isObscuredBy();
    void setRect_data();
    void setRect();
    void opaqueArea();
    void setStartAngle_data();
    void setStartAngle();
    void setSpanAngle_data();
    void setSpanAngle();
    void pieMouseDoubleClickEvent();

    //AbstractShape
    void mouseMoveEvent();
    void mouseDoubleClickEvent();
    void wheelEvent();
    void itemChange();
};

void tst_EllipseShape::constructor()
{
    EllipseShape *p_ellipseShape = nullptr;

    p_ellipseShape = new EllipseShape;
    p_ellipseShape->setPen(QPen(Qt::black, 0));
    QVERIFY2(p_ellipseShape, "ellipseShape nullptr");
    QCOMPARE(p_ellipseShape->type(), int(QGraphicsItem::UserType + 2));
    QCOMPARE(p_ellipseShape->flags(), 0x800); //ItemSendsGeometryChanges true
    QVERIFY(p_ellipseShape->acceptHoverEvents());
    QCOMPARE(p_ellipseShape->rect(), QRectF());
    delete p_ellipseShape;

    QRectF rect(-5.0, -5.0, 5.0, 5.0);
    p_ellipseShape = new EllipseShape(rect);
    p_ellipseShape->setPen(QPen(Qt::black, 0));
    QVERIFY2(p_ellipseShape, "rectShape nullptr");
    QCOMPARE(p_ellipseShape->type(), int(QGraphicsItem::UserType + 2));
    QCOMPARE(p_ellipseShape->flags(), 0x800);
    QVERIFY(p_ellipseShape->acceptHoverEvents());
    QCOMPARE(p_ellipseShape->rect(), rect);
    delete p_ellipseShape;

    qreal x{rect.topLeft().x()};
    qreal y{rect.topLeft().y()};
    qreal w{rect.width()};
    qreal h{rect.height()};
    p_ellipseShape = new EllipseShape(x, y, w, h);
    p_ellipseShape->setPen(QPen(Qt::black, 0));
    QVERIFY2(p_ellipseShape, "rectShape nullptr");
    QCOMPARE(p_ellipseShape->type(), int(QGraphicsItem::UserType + 2));
    QCOMPARE(p_ellipseShape->flags(), 0x800);
    QVERIFY(p_ellipseShape->acceptHoverEvents());
    QCOMPARE(p_ellipseShape->rect(), rect);
    delete p_ellipseShape;
}

void tst_EllipseShape::type()
{
    EllipseShape ellipseShape;
    QCOMPARE(ellipseShape.type(), QGraphicsItem::UserType + 2);
}

void tst_EllipseShape::boundingRect()
{
    QRectF rect(-30.4, -15.5, 40.6, 50.7);
    EllipseShape ellipseShape(rect);
    ellipseShape.setPen(QPen(Qt::NoPen));
    QCOMPARE(ellipseShape.boundingRect(), rect);
    ellipseShape.setPen(QPen(Qt::green, 0));
    QCOMPARE(ellipseShape.boundingRect(), rect);
    QPen shapePen(Qt::gray, 4);
    qreal halfpw = shapePen.widthF() / 2;
    rect.adjust(-halfpw, -halfpw, halfpw, halfpw);
    ellipseShape.setPen(shapePen);
    QCOMPARE(ellipseShape.boundingRect(), rect);
}

class PaintTester : public EllipseShape
{
public:
    PaintTester() : m_widget(NULL), m_painted(0)
    {
        setRect(10.0, 10.0, 20.0, 20.0);
    }

    void paint(QPainter *p, const QStyleOptionGraphicsItem *s, QWidget *w)
    {
        EllipseShape::paint(p, s, w);
        m_widget = w;
        m_painted++;
    }

    QWidget*  m_widget;
    int m_painted;
};

void tst_EllipseShape::paint()
{
    QGraphicsScene scene;
    PaintTester paintTester;
    scene.addItem(&paintTester);
    QGraphicsView view(&scene);
    view.show();
    QVERIFY(QTest::qWaitForWindowExposed(&view));
    QApplication::processEvents();
#ifdef Q_OS_WIN32
    //we try to switch the desktop: if it fails, we skip the test
    if (::SwitchDesktop( ::GetThreadDesktop( ::GetCurrentThreadId() ) ) == 0) {
        QSKIP("The Graphics View doesn't get the paint events");
    }
#endif
    QTRY_COMPARE(paintTester.m_widget, view.viewport());
    view.hide();

    QGraphicsScene scene2;
    QGraphicsView view2(&scene2);
    view2.show();
    QVERIFY(QTest::qWaitForWindowExposed(&view2));
    QCoreApplication::processEvents(); // Process all queued paint events
    PaintTester tester2;
    tester2.setSpanAngle(1440);
    scene2.addItem(&tester2);
    //First show at least one paint
    QCOMPARE(tester2.m_painted, 0);
    QTRY_VERIFY(tester2.m_painted > 0);
    int painted = tester2.m_painted;
    //nominal case, update call paint
    tester2.update();
    QTRY_COMPARE(tester2.m_painted, painted + 1);
    painted = tester2.m_painted;
    //we remove the item from the scene, number of updates is still the same
    tester2.update();
    scene2.removeItem(&tester2);
    QTRY_COMPARE(tester2.m_painted, painted);
    //We re-add the item, the number of paint should increase
    scene2.addItem(&tester2);
    tester2.update();
    QTRY_COMPARE(tester2.m_painted, painted + 1);
}

void tst_EllipseShape::shape()
{
    const qreal penWidthZero = qreal(0.00000001);
    QPainterPathStroker ps;
    ps.setWidth(penWidthZero);

    EllipseShape ellipseShape(-10.0, -10.0, 20.0, 20.0);
    ellipseShape.setPen(QPen(Qt::black, 0));

    QPainterPath path;
    path.addEllipse(ellipseShape.rect());
    QPainterPath p = ps.createStroke(path);
    p.addPath(path);
    QCOMPARE(ellipseShape.shape(), p);

    path.clear();
    p.clear();
    ellipseShape.setSpanAngle(1440);
    path.moveTo(ellipseShape.rect().center());
    path.arcTo(ellipseShape.rect(), ellipseShape.startAngle() / 16.0
               , ellipseShape.spanAngle() / 16.0);
    p = ps.createStroke(path);
    p.addPath(path);
    QCOMPARE(ellipseShape.shape(), p);

    path.clear();
    p.clear();
    ellipseShape.setRect(QRectF());
    path.addEllipse(ellipseShape.rect());
    p = ps.createStroke(path);
    p.addPath(path);
    QCOMPARE(ellipseShape.shape(), p);
}

void tst_EllipseShape::contains()
{
    if (sizeof(qreal) != sizeof(double))
        QSKIP("Skipped due to rounding errors");

    EllipseShape ellipseShape(QRectF(-10, -10, 20, 20));
    QVERIFY(!ellipseShape.contains(QPointF(-11, 0)));
    QVERIFY(ellipseShape.contains(QPointF(-10, 0)));
    QVERIFY(!ellipseShape.contains(QPointF(0, -11)));
    QVERIFY(ellipseShape.contains(QPointF(0, -10)));
    QVERIFY(!ellipseShape.contains(QPointF(11, 0)));
    QVERIFY(ellipseShape.contains(QPointF(10, 0)));
    QVERIFY(!ellipseShape.contains(QPointF(11, 0)));
    QVERIFY(ellipseShape.contains(QPointF(10, 0)));
    QVERIFY(ellipseShape.contains(QPointF(0, 0)));
}

void tst_EllipseShape::isObscuredBy()
{
    EllipseShape ellipseShape1;
    ellipseShape1.setRect(-50.0, -50.0, 50.0, 50.0);
    ellipseShape1.setBrush(QBrush(Qt::red));

    EllipseShape ellipseShape2;
    ellipseShape2.setRect(-30.0, -30.0, 20.0, 20.0);
    ellipseShape2.setBrush(QBrush(Qt::blue));
    ellipseShape2.setZValue(-1.0);

    QVERIFY(!ellipseShape1.isObscuredBy(&ellipseShape2));
    QVERIFY(ellipseShape2.isObscuredBy(&ellipseShape1));

    ellipseShape2.setPos(-30.0, -30.0);
    QVERIFY(!ellipseShape1.isObscuredBy(&ellipseShape2));
    QVERIFY(!ellipseShape2.isObscuredBy(&ellipseShape1));

    ellipseShape2.setPos(-100.0, -100.0);
    QVERIFY(!ellipseShape1.isObscuredBy(&ellipseShape2));
    QVERIFY(!ellipseShape2.isObscuredBy(&ellipseShape1));
}

void tst_EllipseShape::setRect_data()
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
    QTest::newRow("rect_14") << QRectF();
}

void tst_EllipseShape::setRect()
{
    QFETCH(QRectF, rect);

    EllipseShape ellipseShape;
    ellipseShape.setRect(rect);
    QCOMPARE(ellipseShape.rect(), rect);

    qreal x{rect.topLeft().x()};
    qreal y{rect.topLeft().y()};
    qreal w{rect.width()};
    qreal h{rect.height()};
    EllipseShape ellipseShape2;
    ellipseShape2.setRect(x, y, w, h);
    QCOMPARE(ellipseShape2.rect(), rect);
}

void tst_EllipseShape::opaqueArea()
{
    EllipseShape *p_ellipseShape = new EllipseShape(-100.0, -100.0, 200.0, 200.0);
    p_ellipseShape->setZValue(-1.0);
    QPainterPath opaquePath;
    QCOMPARE(p_ellipseShape->opaqueArea(), opaquePath);

    p_ellipseShape->setBrush(QBrush(Qt::red));
    QCOMPARE(p_ellipseShape->opaqueArea(), p_ellipseShape->shape());

    EllipseShape *p_opaqueShape = new EllipseShape(-50.0, -50.0, 200.0, 200.0);
    p_opaqueShape->setBrush(QBrush(Qt::blue));
    p_ellipseShape->setFlag(QGraphicsItem::ItemClipsToShape, true);
    QCOMPARE(p_ellipseShape->opaqueArea(), p_ellipseShape->clipPath());

    EllipseShape *p_parentShape = new EllipseShape(-120.0, -120.0, 200.0, 200.0, p_ellipseShape);
    p_parentShape->setBrush(QBrush(Qt::black));
    QCOMPARE(p_ellipseShape->opaqueArea(), p_ellipseShape->clipPath());

    p_ellipseShape->setFlag(QGraphicsItem::ItemClipsChildrenToShape, true);
    QCOMPARE(p_parentShape->opaqueArea(), p_parentShape->clipPath());

    delete p_parentShape;
    delete p_opaqueShape;
    delete p_ellipseShape;
}

void tst_EllipseShape::setStartAngle_data()
{
    QTest::addColumn<int>("startAngle");
    QTest::newRow("angle 0") << 0;
    QTest::newRow("angle -1") << -1;
    QTest::newRow("angle 1") << 1;
    QTest::newRow("angle -90") << -1440;
    QTest::newRow("angle 90") << 1440;
    QTest::newRow("angle -180") << -2880;
    QTest::newRow("angle 180") << 2880;
    QTest::newRow("angle -270") << -4320;
    QTest::newRow("angle 270") << 4320;
    QTest::newRow("angle -359") << -5744;
    QTest::newRow("angle 359") << 5744;
    QTest::newRow("angle -360") << -5760;
    QTest::newRow("angle 360") << 5760;
    QTest::newRow("angle -361") << -5776;
    QTest::newRow("angle 361") << 5776;
    QTest::newRow("angle -999") << -9999;
    QTest::newRow("angle 999") << 9999;
}

void tst_EllipseShape::setStartAngle()
{
    QFETCH(int, startAngle);

    EllipseShape ellipseShape;
    ellipseShape.setRect(-30.0, -30.0, 60.0, 60.0);
    ellipseShape.setStartAngle(startAngle);
    ellipseShape.setSpanAngle(3840);
    QCOMPARE(startAngle, ellipseShape.startAngle());
}

void tst_EllipseShape::setSpanAngle_data()
{
    QTest::addColumn<int>("spanAngle");
    QTest::newRow("angle 0") << 0;
    QTest::newRow("angle -1") << -1;
    QTest::newRow("angle 1") << 1;
    QTest::newRow("angle -90") << -1440;
    QTest::newRow("angle 90") << 1440;
    QTest::newRow("angle -180") << -2880;
    QTest::newRow("angle 180") << 2880;
    QTest::newRow("angle -270") << -4320;
    QTest::newRow("angle 270") << 4320;
    QTest::newRow("angle -359") << -5744;
    QTest::newRow("angle 359") << 5744;
    QTest::newRow("angle -360") << -5760;
    QTest::newRow("angle 360") << 5760;
    QTest::newRow("angle -361") << -5776;
    QTest::newRow("angle 361") << 5776;
    QTest::newRow("angle -999") << -9999;
    QTest::newRow("angle 999") << 9999;
}

void tst_EllipseShape::setSpanAngle()
{
    QFETCH(int, spanAngle);
    EllipseShape ellipseShape;
    ellipseShape.setRect(-30.0, -30.0, 60.0, 60.0);
    ellipseShape.setStartAngle(1440);
    ellipseShape.setSpanAngle(spanAngle);
    QCOMPARE(spanAngle, ellipseShape.spanAngle());
}

void tst_EllipseShape::pieMouseDoubleClickEvent()
{
    QGraphicsScene scene;
    EllipseShape *p_pieShape = new EllipseShape(-20.0, -20.0, 40.0, 40.0);
    p_pieShape->setSpanAngle(120 * 16);
    p_pieShape->setFlag(QGraphicsItem::ItemIsSelectable, true);
    scene.addItem(p_pieShape);
    QCOMPARE(p_pieShape->childItems().count(), 0);
    p_pieShape->setSelected(true);

    QGraphicsSceneMouseEvent mouseDClickEvent(QEvent::GraphicsSceneMouseDoubleClick);
    mouseDClickEvent.setScenePos(p_pieShape->pos());
    mouseDClickEvent.setButton(Qt::LeftButton);
    QApplication::sendEvent(&scene, &mouseDClickEvent);
    QVERIFY(mouseDClickEvent.isAccepted());

    SizeGripShape *sizegripItem
            = qgraphicsitem_cast<SizeGripShape *>(p_pieShape->childItems().constFirst());
    int itemVisible = 0;
    for (int i = 0; i < sizegripItem->childItems().count(); i++) {
        QGraphicsItem *item {sizegripItem->childItems().at(i)};
        if (item->isVisible())
            itemVisible++;
    }
    QCOMPARE(itemVisible, 3);
    QCOMPARE(sizegripItem->actionType(), SizeGripShape::Resize);

    QApplication::sendEvent(&scene, &mouseDClickEvent);
    sizegripItem->childItems().constFirst();
    itemVisible = 0;
    for (int i = 0; i < sizegripItem->childItems().count(); i++) {
        QGraphicsItem *item {sizegripItem->childItems().at(i)};
        if (item->isVisible())
            itemVisible++;
    }
    QCOMPARE(itemVisible, 3);
    QCOMPARE(sizegripItem->actionType(), SizeGripShape::Resize);

    delete p_pieShape;
}

void tst_EllipseShape::mouseMoveEvent()
{
    QGraphicsScene scene;
    EllipseShape *p_ellipseShape = new EllipseShape(-10.0, -10.0, 20.0, 20.0);
    p_ellipseShape->setFlag(QGraphicsItem::ItemIsSelectable, true);
    scene.addItem(p_ellipseShape);

    sendMousePress(&scene, p_ellipseShape->pos());
    QGraphicsSceneMouseEvent mouseMoveEvent(QEvent::GraphicsSceneMouseMove);
    mouseMoveEvent.setScenePos(p_ellipseShape->pos());
    mouseMoveEvent.setButton(Qt::LeftButton);
    QApplication::sendEvent(&scene, &mouseMoveEvent);
    QVERIFY(mouseMoveEvent.isAccepted());

    sendMousePress(&scene, p_ellipseShape->pos());
    sendMouseMove(&scene, QPointF(50.0, -50.0), Qt::LeftButton);
    QCOMPARE(p_ellipseShape->pos(), QPointF(50.0, -50.0));

    EllipseShape *p_ellipseShape2 = new EllipseShape(-50.0, -50.0, 30.0, 25.0);
    p_ellipseShape2->setFlag(QGraphicsItem::ItemIsSelectable, true);
    scene.addItem(p_ellipseShape2);
    p_ellipseShape2->setSelected(true);

    sendMousePress(&scene, p_ellipseShape2->pos());
    sendMouseMove(&scene, QPointF(20.0, 20.0), Qt::LeftButton);
    QCOMPARE(p_ellipseShape2->pos(), QPointF(20.0, 20.0));

    delete p_ellipseShape2;
    delete p_ellipseShape;
}

void tst_EllipseShape::mouseDoubleClickEvent()
{
    QGraphicsScene scene;
    EllipseShape *p_ellipseShape = new EllipseShape(-20.0, -20.0, 40.0, 40.0);
    p_ellipseShape->setFlag(QGraphicsItem::ItemIsSelectable, true);
    scene.addItem(p_ellipseShape);
    QCOMPARE(p_ellipseShape->childItems().count(), 0);

    QGraphicsSceneMouseEvent mouseDClickEvent(QEvent::GraphicsSceneMouseDoubleClick);
    mouseDClickEvent.setScenePos(p_ellipseShape->pos());
    mouseDClickEvent.setButton(Qt::LeftButton);
    QApplication::sendEvent(&scene, &mouseDClickEvent);
    QVERIFY(mouseDClickEvent.isAccepted());

    SizeGripShape *sizegripItem
            = qgraphicsitem_cast<SizeGripShape *>(p_ellipseShape->childItems().constFirst());
    int itemVisible = 0;
    for (int i = 0; i < sizegripItem->childItems().count(); i++) {
        QGraphicsItem *item {sizegripItem->childItems().at(i)};
        if (item->isVisible())
            itemVisible++;
    }
    QCOMPARE(itemVisible, 8);
    QCOMPARE(sizegripItem->actionType(), SizeGripShape::Resize);

    QApplication::sendEvent(&scene, &mouseDClickEvent);
    sizegripItem->childItems().constFirst();
    itemVisible = 0;
    for (int i = 0; i < sizegripItem->childItems().count(); i++) {
        QGraphicsItem *item {sizegripItem->childItems().at(i)};
        if (item->isVisible())
            itemVisible++;
    }
    QCOMPARE(itemVisible, 4);
    QCOMPARE(sizegripItem->actionType(), SizeGripShape::Rotate);

    QApplication::sendEvent(&scene, &mouseDClickEvent);
    sizegripItem->childItems().constFirst();
    itemVisible = 0;
    for (int i = 0; i < sizegripItem->childItems().count(); i++) {
        QGraphicsItem *item {sizegripItem->childItems().at(i)};
        if (item->isVisible())
            itemVisible++;
    }
    QCOMPARE(itemVisible, 8);
    QCOMPARE(sizegripItem->actionType(), SizeGripShape::Resize);

    delete p_ellipseShape;
}

void tst_EllipseShape::wheelEvent()
{
    QGraphicsScene scene;
    QGraphicsView view(&scene);
    view.show();
    view.fitInView(scene.sceneRect());
    QVERIFY(QTest::qWaitForWindowActive(&view));

    EllipseShape *p_ellipseShape = new EllipseShape(-20.0, -20.0, 40.0, 40.0);
    p_ellipseShape->setFlag(QGraphicsItem::ItemIsSelectable, true);
    scene.addItem(p_ellipseShape);

    QGraphicsSceneWheelEvent wheelEvent(QEvent::GraphicsSceneWheel);
    wheelEvent.setScenePos(p_ellipseShape->scenePos());
    wheelEvent.setDelta(1);
    QApplication::sendEvent(&scene, &wheelEvent);
    QVERIFY(!wheelEvent.isAccepted());

    p_ellipseShape->setSelected(true);
    p_ellipseShape->resetTransform();

    qreal m11Actual = p_ellipseShape->transform().m11();
    qreal m11Expected = 1.0;
    bool m11Compare = qFuzzyCompare(m11Actual, m11Expected);
    QVERIFY(m11Compare);

    qreal m22Actual = p_ellipseShape->transform().m22();
    qreal m22Expected = 1.0;
    bool m22Compare = qFuzzyCompare(m22Actual, m22Expected);
    QVERIFY(m22Compare);

    QTest::mouseMove(view.viewport(), p_ellipseShape->scenePos().toPoint());

    for (int i = 0; i < 40; i++) {
        sendMouseWheel(&scene, p_ellipseShape->scenePos(), 1);

        m11Actual = p_ellipseShape->transform().m11();
        m11Expected *= 1.03;
        m11Compare = qFuzzyCompare(m11Actual, m11Expected);
        QVERIFY(m11Compare);

        m22Actual = p_ellipseShape->transform().m22();
        m22Expected *= 1.03;
        m22Compare = qFuzzyCompare(m22Actual, m22Expected);
        QVERIFY(m22Compare);
    }

    for (int i = 0; i < 40; i++) {
        sendMouseWheel(&scene, p_ellipseShape->scenePos(), -1);

        m11Actual = p_ellipseShape->transform().m11();
        m11Expected *= 0.97;
        m11Compare = qFuzzyCompare(m11Actual, m11Expected);
        QVERIFY(m11Compare);

        m22Actual = p_ellipseShape->transform().m22();
        m22Expected *= 0.97;
        m22Compare = qFuzzyCompare(m22Actual, m22Expected);
        QVERIFY(m22Compare);
    }

    delete p_ellipseShape;
}

void tst_EllipseShape::itemChange()
{
    QGraphicsScene scene;
    EllipseShape *p_ellipseShape = new EllipseShape(-20.0, -20.0, 40.0, 40.0);
    p_ellipseShape->setFlag(QGraphicsItem::ItemIsSelectable, true);
    scene.addItem(p_ellipseShape);
    QCOMPARE(p_ellipseShape->childItems().count(), 0);
    p_ellipseShape->setSelected(true);
    QGraphicsItem *sizegripItem = p_ellipseShape->childItems().constFirst();
    QCOMPARE(sizegripItem->childItems().count(), 8);
    p_ellipseShape->setSelected(false);
    QCOMPARE(p_ellipseShape->childItems().count(), 0);
}

QTEST_MAIN(tst_EllipseShape)

#include "tst_ellipseshape.moc"
