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

    //AbstractShape
    void setMenu();
    void mousePressEvent();
    void mouseMoveEvent();
    void mouseDoubleClickEvent();
    void wheelEvent();
    void itemChange();
};

void tst_EllipseShape::constructor()
{
    EllipseShape *ellipseShape = nullptr;

    ellipseShape = new EllipseShape;
    ellipseShape->setPen(QPen(Qt::black, 0));
    QVERIFY2(ellipseShape, "ellipseShape nullptr");
    QCOMPARE(ellipseShape->type(), int(QGraphicsItem::UserType + 2));
    QCOMPARE(ellipseShape->flags(), 0x800); //ItemSendsGeometryChanges true
    QVERIFY(ellipseShape->acceptHoverEvents());
    QCOMPARE(ellipseShape->rect(), QRectF());
    delete ellipseShape;

    QRectF rect(-5.0, -5.0, 5.0, 5.0);
    ellipseShape = new EllipseShape(rect);
    ellipseShape->setPen(QPen(Qt::black, 0));
    QVERIFY2(ellipseShape, "rectShape nullptr");
    QCOMPARE(ellipseShape->type(), int(QGraphicsItem::UserType + 2));
    QCOMPARE(ellipseShape->flags(), 0x800);
    QVERIFY(ellipseShape->acceptHoverEvents());
    QCOMPARE(ellipseShape->rect(), rect);
    delete ellipseShape;

    qreal x{rect.topLeft().x()};
    qreal y{rect.topLeft().y()};
    qreal w{rect.width()};
    qreal h{rect.height()};
    ellipseShape = new EllipseShape(x, y, w, h);
    ellipseShape->setPen(QPen(Qt::black, 0));
    QVERIFY2(ellipseShape, "rectShape nullptr");
    QCOMPARE(ellipseShape->type(), int(QGraphicsItem::UserType + 2));
    QCOMPARE(ellipseShape->flags(), 0x800);
    QVERIFY(ellipseShape->acceptHoverEvents());
    QCOMPARE(ellipseShape->rect(), rect);
    delete ellipseShape;
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
    PaintTester() : widget(NULL), painted(0)
    {
        setRect(10.0, 10.0, 20.0, 20.0);
    }

    void paint(QPainter *p, const QStyleOptionGraphicsItem *s, QWidget *w)
    {
        EllipseShape::paint(p, s, w);
        widget = w;
        painted++;
    }

    QWidget*  widget;
    int painted;
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
    QTRY_COMPARE(paintTester.widget, view.viewport());
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
    QCOMPARE(tester2.painted, 0);
    QTRY_VERIFY(tester2.painted > 0);
    int painted = tester2.painted;
    //nominal case, update call paint
    tester2.update();
    QTRY_COMPARE(tester2.painted, painted + 1);
    painted = tester2.painted;
    //we remove the item from the scene, number of updates is still the same
    tester2.update();
    scene2.removeItem(&tester2);
    QTRY_COMPARE(tester2.painted, painted);
    //We re-add the item, the number of paint should increase
    scene2.addItem(&tester2);
    tester2.update();
    QTRY_COMPARE(tester2.painted, painted + 1);
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
    EllipseShape *ellipseShape = new EllipseShape(-100.0, -100.0, 200.0, 200.0);
    ellipseShape->setZValue(-1.0);
    QPainterPath opaquePath;
    QCOMPARE(ellipseShape->opaqueArea(), opaquePath);

    ellipseShape->setBrush(QBrush(Qt::red));
    QCOMPARE(ellipseShape->opaqueArea(), ellipseShape->shape());

    EllipseShape *opaqueShape = new EllipseShape(-50.0, -50.0, 200.0, 200.0);
    opaqueShape->setBrush(QBrush(Qt::blue));
    ellipseShape->setFlag(QGraphicsItem::ItemClipsToShape, true);
    QCOMPARE(ellipseShape->opaqueArea(), ellipseShape->clipPath());

    EllipseShape *parentShape = new EllipseShape(-120.0, -120.0, 200.0, 200.0, ellipseShape);
    parentShape->setBrush(QBrush(Qt::black));
    QCOMPARE(ellipseShape->opaqueArea(), ellipseShape->clipPath());

    ellipseShape->setFlag(QGraphicsItem::ItemClipsChildrenToShape, true);
    QCOMPARE(parentShape->opaqueArea(), parentShape->clipPath());
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

//    QGraphicsScene scene;
//    QGraphicsView view(&scene);
//    view.show();
//    view.fitInView(scene.sceneRect());
//    QVERIFY(QTest::qWaitForWindowActive(&view));

    EllipseShape ellipseShape;
    ellipseShape.setRect(-30.0, -30.0, 60.0, 60.0);
    ellipseShape.setStartAngle(1440);
    ellipseShape.setSpanAngle(spanAngle);
//    scene.addItem(&ellipseShape);
    QCOMPARE(spanAngle, ellipseShape.spanAngle());
}

void tst_EllipseShape::setMenu()
{
    EllipseShape ellipseShape;
    QCOMPARE(ellipseShape.menu(), nullptr);
    QMenu *contextMenu = new QMenu;
    ellipseShape.setMenu(contextMenu);
    QCOMPARE(ellipseShape.menu(), contextMenu);
}

class ContextMenuTester :public QMenu
{
    Q_OBJECT
public:
    ContextMenuTester() : QMenu("Menu-Title"), m_timerId(-1)
    {
        addAction("Item 1");
    }

protected:
    void showEvent(QShowEvent *shEvent) override
    {
        m_timerId = startTimer(50);
        QMenu::showEvent(shEvent);
    }
    void timerEvent(QTimerEvent *tEvent) override
    {
        if (tEvent->timerId() == m_timerId)
            close();
    }

private:
    int m_timerId;
};

void tst_EllipseShape::mousePressEvent()
{
    QGraphicsScene scene;
    QGraphicsView view(&scene);
    view.show();
    view.fitInView(scene.sceneRect());
    QVERIFY(QTest::qWaitForWindowActive(&view));
    ContextMenuTester *contextMenu = new ContextMenuTester;

    EllipseShape *ellipseShape = new EllipseShape(-20.0, -20.0, 40.0, 40.0);
    ellipseShape->setMenu(contextMenu);
    ellipseShape->setFlag(QGraphicsItem::ItemIsSelectable, true);
    scene.addItem(ellipseShape);

    QGraphicsSceneMouseEvent mousePressEvent(QEvent::GraphicsSceneMouseMove);
    mousePressEvent.setScenePos(ellipseShape->pos());
    mousePressEvent.setButton(Qt::LeftButton);
    QApplication::sendEvent(&scene, &mousePressEvent);
    QVERIFY(mousePressEvent.isAccepted());

    ellipseShape->setSelected(true);
    QSignalSpy contextMenuSpy(contextMenu, &QMenu::aboutToShow);
    QCOMPARE(contextMenuSpy.count(), 0);

    QTest::mouseClick(view.viewport(), Qt::RightButton, Qt::NoModifier
                      , view.mapFromScene(ellipseShape->boundingRect().center()));
    QCOMPARE(contextMenuSpy.count(), 1);

    EllipseShape *ellipseShape2 = new EllipseShape(-50.0, -50.0, 20.0, 20.0);
    ellipseShape2->setMenu(contextMenu);
    ellipseShape2->setFlag(QGraphicsItem::ItemIsSelectable, true);
    scene.addItem(ellipseShape2);
    ellipseShape2->setSelected(true);

    QTest::mouseClick(view.viewport(), Qt::RightButton, Qt::NoModifier
                      , view.mapFromScene(ellipseShape2->boundingRect().center()));
    QCOMPARE(contextMenuSpy.count(), 2);
}

void tst_EllipseShape::mouseMoveEvent()
{
    QGraphicsScene scene;
    EllipseShape *ellipseShape = new EllipseShape(-10.0, -10.0, 20.0, 20.0);
    ellipseShape->setFlag(QGraphicsItem::ItemIsSelectable, true);
    scene.addItem(ellipseShape);

    sendMousePress(&scene, ellipseShape->pos());
    QGraphicsSceneMouseEvent mouseMoveEvent(QEvent::GraphicsSceneMouseMove);
    mouseMoveEvent.setScenePos(ellipseShape->pos());
    mouseMoveEvent.setButton(Qt::LeftButton);
    QApplication::sendEvent(&scene, &mouseMoveEvent);
    QVERIFY(mouseMoveEvent.isAccepted());

    sendMousePress(&scene, ellipseShape->pos());
    sendMouseMove(&scene, QPointF(50.0, -50.0), Qt::LeftButton);
    QCOMPARE(ellipseShape->pos(), QPointF(50.0, -50.0));

    EllipseShape *ellipseShape2 = new EllipseShape(-50.0, -50.0, 30.0, 25.0);
    ellipseShape2->setFlag(QGraphicsItem::ItemIsSelectable, true);
    scene.addItem(ellipseShape2);
    ellipseShape2->setSelected(true);

    sendMousePress(&scene, ellipseShape2->pos());
    sendMouseMove(&scene, QPointF(20.0, 20.0), Qt::LeftButton);
    QCOMPARE(ellipseShape2->pos(), QPointF(20.0, 20.0));
}

void tst_EllipseShape::mouseDoubleClickEvent()
{
    QGraphicsScene scene;
    EllipseShape *ellipseShape = new EllipseShape(-20.0, -20.0, 40.0, 40.0);
    ellipseShape->setFlag(QGraphicsItem::ItemIsSelectable, true);
    scene.addItem(ellipseShape);
    QCOMPARE(ellipseShape->childItems().count(), 0);

    QGraphicsSceneMouseEvent mouseDClickEvent(QEvent::GraphicsSceneMouseDoubleClick);
    mouseDClickEvent.setScenePos(ellipseShape->pos());
    mouseDClickEvent.setButton(Qt::LeftButton);
    QApplication::sendEvent(&scene, &mouseDClickEvent);
    QVERIFY(mouseDClickEvent.isAccepted());

    QGraphicsItem *sizegripItem = ellipseShape->childItems().constFirst();
    int itemVisible = 0;
    for (int i = 0; i < sizegripItem->childItems().count(); i++) {
        QGraphicsItem *item {sizegripItem->childItems().at(i)};
        if (item->isVisible())
            itemVisible++;
    }
    QCOMPARE(itemVisible, 8);

    QApplication::sendEvent(&scene, &mouseDClickEvent);
    sizegripItem = ellipseShape->childItems().constFirst();
    itemVisible = 0;
    for (int i = 0; i < sizegripItem->childItems().count(); i++) {
        QGraphicsItem *item {sizegripItem->childItems().at(i)};
        if (item->isVisible())
            itemVisible++;
    }
    QCOMPARE(itemVisible, 4);

    QApplication::sendEvent(&scene, &mouseDClickEvent);
    sizegripItem = ellipseShape->childItems().constFirst();
    itemVisible = 0;
    for (int i = 0; i < sizegripItem->childItems().count(); i++) {
        QGraphicsItem *item {sizegripItem->childItems().at(i)};
        if (item->isVisible())
            itemVisible++;
    }
    QCOMPARE(itemVisible, 8);
}

void tst_EllipseShape::wheelEvent()
{
    QGraphicsScene scene;
    QGraphicsView view(&scene);
    view.show();
    view.fitInView(scene.sceneRect());
    QVERIFY(QTest::qWaitForWindowActive(&view));

    EllipseShape *ellipseShape = new EllipseShape(-20.0, -20.0, 40.0, 40.0);
    ellipseShape->setFlag(QGraphicsItem::ItemIsSelectable, true);
    scene.addItem(ellipseShape);

    QGraphicsSceneWheelEvent wheelEvent(QEvent::GraphicsSceneWheel);
    wheelEvent.setScenePos(ellipseShape->scenePos());
    wheelEvent.setDelta(1);
    QApplication::sendEvent(&scene, &wheelEvent);
    QVERIFY(!wheelEvent.isAccepted());

    ellipseShape->setSelected(true);
    ellipseShape->resetTransform();

    qreal m11Actual = ellipseShape->transform().m11();
    qreal m11Expected = 1.0;
    bool m11Compare = qFuzzyCompare(m11Actual, m11Expected);
    QVERIFY(m11Compare);

    qreal m22Actual = ellipseShape->transform().m22();
    qreal m22Expected = 1.0;
    bool m22Compare = qFuzzyCompare(m22Actual, m22Expected);
    QVERIFY(m22Compare);

    QTest::mouseMove(view.viewport(), ellipseShape->scenePos().toPoint());

    for (int i = 0; i < 40; i++) {
        sendMouseWheel(&scene, ellipseShape->scenePos(), 1);

        m11Actual = ellipseShape->transform().m11();
        m11Expected *= 1.03;
        m11Compare = qFuzzyCompare(m11Actual, m11Expected);
        QVERIFY(m11Compare);

        m22Actual = ellipseShape->transform().m22();
        m22Expected *= 1.03;
        m22Compare = qFuzzyCompare(m22Actual, m22Expected);
        QVERIFY(m22Compare);
    }

    for (int i = 0; i < 40; i++) {
        sendMouseWheel(&scene, ellipseShape->scenePos(), -1);

        m11Actual = ellipseShape->transform().m11();
        m11Expected *= 0.97;
        m11Compare = qFuzzyCompare(m11Actual, m11Expected);
        QVERIFY(m11Compare);

        m22Actual = ellipseShape->transform().m22();
        m22Expected *= 0.97;
        m22Compare = qFuzzyCompare(m22Actual, m22Expected);
        QVERIFY(m22Compare);
    }
}

void tst_EllipseShape::itemChange()
{
    QGraphicsScene scene;
    EllipseShape *ellipseShape = new EllipseShape(-20.0, -20.0, 40.0, 40.0);
    ellipseShape->setFlag(QGraphicsItem::ItemIsSelectable, true);
    scene.addItem(ellipseShape);
    QCOMPARE(ellipseShape->childItems().count(), 0);
    ellipseShape->setSelected(true);
    QGraphicsItem *sizegripItem = ellipseShape->childItems().constFirst();
    QCOMPARE(sizegripItem->childItems().count(), 8);
    ellipseShape->setSelected(false);
    QCOMPARE(ellipseShape->childItems().count(), 0);
}

QTEST_MAIN(tst_EllipseShape)

#include "tst_ellipseshape.moc"
