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
#include <QSignalSpy>
#include <QMenu>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QGraphicsSceneMouseEvent>

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

//static void sendMouseRelease(QGraphicsScene *scene, const QPointF &point
//                             , Qt::MouseButton button = Qt::LeftButton)
//{
//    QGraphicsSceneMouseEvent event(QEvent::GraphicsSceneMouseRelease);
//    event.setScenePos(point);
//    event.setButton(button);
//    QApplication::sendEvent(scene, &event);
//}
//static void sendMouseClick(QGraphicsScene *scene, const QPointF &point
//                           , Qt::MouseButton button = Qt::LeftButton
//        , Qt::KeyboardModifier modifier = Qt::NoModifier)
//{
//    sendMousePress(scene, point, button, modifier);
//    sendMouseRelease(scene, point);
//}

static void sendMouseWheel(QGraphicsScene *scene, const QPointF &point, int delta)
{
    QGraphicsSceneWheelEvent wheelEvent(QEvent::GraphicsSceneWheel);
    wheelEvent.setScenePos(point);
    wheelEvent.setDelta(delta);
    QApplication::sendEvent(scene, &wheelEvent);
}

class tst_RectShape : public QObject
{
    Q_OBJECT

private slots:
    void constructor();
    void type();
    void boundingRect();
    void setRect_data();
    void setRect();
    void shape();
    void contains();
    void paint();
    void isObscuredBy();
    void opaqueArea();

    //AbstractShape
    void setMenu();
    void mousePressEvent();
    void mouseMoveEvent();
    void mouseDoubleClickEvent();
    void wheelEvent();
    void itemChange();
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

void tst_RectShape::setRect_data()
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

void tst_RectShape::setRect()
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
        setRect(10.0, 10.0, 20.0, 20.0);
    }

    void paint(QPainter *, const QStyleOptionGraphicsItem *, QWidget *w)
    {
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

void tst_RectShape::setMenu()
{
    RectShape rectShape;
    QMenu *p_contextMenu = new QMenu();
    QAction *p_action = new QAction();
    p_contextMenu->addAction(p_action);
    rectShape.setMenu(p_contextMenu);
    QCOMPARE(rectShape.menu()->actions().at(0), p_action);
    delete p_contextMenu;
    delete p_action;
}

// TODO переделать тест mousePressEvent
//class ContextMenuTester :public QMenu
//{
//    Q_OBJECT
//public:
//    ContextMenuTester() : QMenu("Menu-Title")//, m_timerId(-1)
//    {
//        addAction("Item 1");
//    }

//protected:
//    void showEvent(QShowEvent *shEvent) override
//    {
//        m_timerId = startTimer(50);
//        QMenu::showEvent(shEvent);
//    }
//    void timerEvent(QTimerEvent *tEvent) override
//    {
//        if (tEvent->timerId() == m_timerId)
//            close();
//    }

//private:
//    int m_timerId;
//};

void tst_RectShape::mousePressEvent()
{
    QGraphicsScene scene;
    QGraphicsView view(&scene);
    view.show();
    view.fitInView(scene.sceneRect());
    QVERIFY(QTest::qWaitForWindowActive(&view));
//    ContextMenuTester *p_contextMenu = new ContextMenuTester;

    QMenu contextMenu;
    contextMenu.addAction("Item_1");

    RectShape *p_rectShape = new RectShape(-20.0, -20.0, 40.0, 40.0);
    p_rectShape->setMenu(&contextMenu);
    p_rectShape->setFlag(QGraphicsItem::ItemIsSelectable, true);
    scene.addItem(p_rectShape);

//    QGraphicsSceneMouseEvent mousePressEvent(QEvent::GraphicsSceneMouseMove);
//    mousePressEvent.setScenePos(p_rectShape->pos());
//    mousePressEvent.setButton(Qt::LeftButton);
//    QApplication::sendEvent(&scene, &mousePressEvent);
//    QVERIFY(mousePressEvent.isAccepted());

    p_rectShape->setSelected(true);
    QSignalSpy contextMenuSpy(p_rectShape->menu(), &QMenu::aboutToShow);
    QCOMPARE(contextMenuSpy.count(), 0);

//    QTest::mouseClick(view.viewport(), Qt::RightButton, Qt::NoModifier
//                      , view.mapFromScene(p_rectShape->boundingRect().center()));
//    QCOMPARE(contextMenuSpy.count(), 1);

//    delete p_contextMenu;
    delete p_rectShape;
}

void tst_RectShape::mouseMoveEvent()
{
    QGraphicsScene scene;
    RectShape *p_rectShape = new RectShape(-10.0, -10.0, 20.0, 20.0);
    p_rectShape->setFlag(QGraphicsItem::ItemIsSelectable, true);
    scene.addItem(p_rectShape);

    sendMousePress(&scene, p_rectShape->pos());
    QGraphicsSceneMouseEvent mouseMoveEvent(QEvent::GraphicsSceneMouseMove);
    mouseMoveEvent.setScenePos(p_rectShape->pos());
    mouseMoveEvent.setButton(Qt::LeftButton);
    QApplication::sendEvent(&scene, &mouseMoveEvent);
    QVERIFY(mouseMoveEvent.isAccepted());

    sendMousePress(&scene, p_rectShape->pos());
    sendMouseMove(&scene, QPointF(50.0, -50.0), Qt::LeftButton);
    QCOMPARE(p_rectShape->pos(), QPointF(50.0, -50.0));

    RectShape *p_rectShape2 = new RectShape(-50.0, -50.0, 30.0, 25.0);
    p_rectShape2->setFlag(QGraphicsItem::ItemIsSelectable, true);
    scene.addItem(p_rectShape2);
    p_rectShape2->setSelected(true);

    sendMousePress(&scene, p_rectShape2->pos());
    sendMouseMove(&scene, QPointF(20.0, 20.0), Qt::LeftButton);
    QCOMPARE(p_rectShape2->pos(), QPointF(20.0, 20.0));

    delete p_rectShape2;
    delete p_rectShape;
}

void tst_RectShape::mouseDoubleClickEvent()
{
    QGraphicsScene scene;
    RectShape *p_rectShape = new RectShape(-20.0, -20.0, 40.0, 40.0);
    p_rectShape->setFlag(QGraphicsItem::ItemIsSelectable, true);
    scene.addItem(p_rectShape);
    QCOMPARE(p_rectShape->childItems().count(), 0);

    QGraphicsSceneMouseEvent mouseDClickEvent(QEvent::GraphicsSceneMouseDoubleClick);
    mouseDClickEvent.setScenePos(p_rectShape->pos());
    mouseDClickEvent.setButton(Qt::LeftButton);
    QApplication::sendEvent(&scene, &mouseDClickEvent);
    QVERIFY(mouseDClickEvent.isAccepted());

    QGraphicsItem *sizegripItem = p_rectShape->childItems().constFirst();
    int itemVisible = 0;
    for (int i = 0; i < sizegripItem->childItems().count(); i++) {
        QGraphicsItem *item {sizegripItem->childItems().at(i)};
        if (item->isVisible())
            itemVisible++;
    }
    QCOMPARE(itemVisible, 8);

    QApplication::sendEvent(&scene, &mouseDClickEvent);
    sizegripItem = p_rectShape->childItems().constFirst();
    itemVisible = 0;
    for (int i = 0; i < sizegripItem->childItems().count(); i++) {
        QGraphicsItem *item {sizegripItem->childItems().at(i)};
        if (item->isVisible())
            itemVisible++;
    }
    QCOMPARE(itemVisible, 4);

    QApplication::sendEvent(&scene, &mouseDClickEvent);
    sizegripItem = p_rectShape->childItems().constFirst();
    itemVisible = 0;
    for (int i = 0; i < sizegripItem->childItems().count(); i++) {
        QGraphicsItem *item {sizegripItem->childItems().at(i)};
        if (item->isVisible())
            itemVisible++;
    }
    QCOMPARE(itemVisible, 8);

    delete p_rectShape;
}

void tst_RectShape::wheelEvent()
{
    QGraphicsScene scene;
    QGraphicsView view(&scene);
    view.show();
    view.fitInView(scene.sceneRect());
    QVERIFY(QTest::qWaitForWindowActive(&view));

    RectShape *p_rectShape = new RectShape(-20.0, -20.0, 40.0, 40.0);
    p_rectShape->setFlag(QGraphicsItem::ItemIsSelectable, true);
    scene.addItem(p_rectShape);

    QGraphicsSceneWheelEvent wheelEvent(QEvent::GraphicsSceneWheel);
    wheelEvent.setScenePos(p_rectShape->scenePos());
    wheelEvent.setDelta(1);
    QApplication::sendEvent(&scene, &wheelEvent);
    QVERIFY(!wheelEvent.isAccepted());

    p_rectShape->setSelected(true);
    p_rectShape->resetTransform();

    qreal m11Actual = p_rectShape->transform().m11();
    qreal m11Expected = 1.0;
    bool m11Compare = qFuzzyCompare(m11Actual, m11Expected);
    QVERIFY(m11Compare);

    qreal m22Actual = p_rectShape->transform().m22();
    qreal m22Expected = 1.0;
    bool m22Compare = qFuzzyCompare(m22Actual, m22Expected);
    QVERIFY(m22Compare);

    QTest::mouseMove(view.viewport(), p_rectShape->scenePos().toPoint());

    for (int i = 0; i < 40; i++) {
        sendMouseWheel(&scene, p_rectShape->scenePos(), 1);

        m11Actual = p_rectShape->transform().m11();
        m11Expected *= 1.03;
        m11Compare = qFuzzyCompare(m11Actual, m11Expected);
        QVERIFY(m11Compare);

        m22Actual = p_rectShape->transform().m22();
        m22Expected *= 1.03;
        m22Compare = qFuzzyCompare(m22Actual, m22Expected);
        QVERIFY(m22Compare);
    }

    for (int i = 0; i < 40; i++) {
        sendMouseWheel(&scene, p_rectShape->scenePos(), -1);

        m11Actual = p_rectShape->transform().m11();
        m11Expected *= 0.97;
        m11Compare = qFuzzyCompare(m11Actual, m11Expected);
        QVERIFY(m11Compare);

        m22Actual = p_rectShape->transform().m22();
        m22Expected *= 0.97;
        m22Compare = qFuzzyCompare(m22Actual, m22Expected);
        QVERIFY(m22Compare);
    }

    delete p_rectShape;
}

void tst_RectShape::itemChange()
{
    QGraphicsScene scene;
    RectShape *p_rectShape = new RectShape(-20.0, -20.0, 40.0, 40.0);
    p_rectShape->setFlag(QGraphicsItem::ItemIsSelectable, true);
    scene.addItem(p_rectShape);
    QCOMPARE(p_rectShape->childItems().count(), 0);
    p_rectShape->setSelected(true);
    QGraphicsItem *sizegripItem = p_rectShape->childItems().constFirst();
    QCOMPARE(sizegripItem->childItems().count(), 8);
    p_rectShape->setSelected(false);
    QCOMPARE(p_rectShape->childItems().count(), 0);

    delete p_rectShape;
}

QTEST_MAIN(tst_RectShape)

#include "tst_rectshape.moc"
