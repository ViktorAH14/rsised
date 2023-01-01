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
#include <QGraphicsSceneMouseEvent>
#include <QGraphicsView>

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

        painter->setPen(pen());
        painter->setBrush(brush());
        painter->drawRect(m_shapeRect);

        if (option->state & QStyle::State_Selected) {
             highlightSelected(painter, option);
        }
    }
    QPainterPath shape() const override
    {
        QPainterPath path;
        path.addRect(m_shapeRect);

        return shapeFromPath(path);
    }
//    bool contains(const QPointF &point) const override;
//    bool isObscuredBy(const QGraphicsItem *item) const override;
//    QPainterPath opaqueArea() const override;
    void setRect(const QRectF &rect)
    {
        if (m_shapeRect == rect)
            return;
        prepareGeometryChange();
        m_shapeRect = rect;
        update();
    }

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
    void cleanup();
    void pen_setPen();
    void brush_setBrush();
    void isObscuredBy();
    void opaqueArea();
    void scaleShape();
    void menu_setMenu();
    void add_removeActions();
    void mouseDoubleClickEvent();
    void mouseMoveEvent();
    void mousePressEvent();
    void whellEvent();
    void itemChange();

private:
    AbstractShapeTester *p_abstractShapeTester;
};



void tst_AbstractShape::init()
{
    p_abstractShapeTester = new AbstractShapeTester();
}

void tst_AbstractShape::cleanup()
{
    delete p_abstractShapeTester;
}

void tst_AbstractShape::pen_setPen()
{
    p_abstractShapeTester->setPen(QPen(Qt::black));
    QCOMPARE(p_abstractShapeTester->pen(), QPen(Qt::black));
    p_abstractShapeTester->setPen(QPen(Qt::red));
    QCOMPARE( p_abstractShapeTester->pen(), QPen(Qt::red));
    p_abstractShapeTester->setPen(QPen(Qt::white));
    QCOMPARE(p_abstractShapeTester->pen(), QPen(Qt::white));
}

void tst_AbstractShape::brush_setBrush()
{
    p_abstractShapeTester->setBrush(QBrush(Qt::black));
    QCOMPARE(p_abstractShapeTester->brush(), QBrush(Qt::black));
    p_abstractShapeTester->setBrush(QBrush(Qt::red, Qt::CrossPattern));
    QCOMPARE(p_abstractShapeTester->brush(), QBrush(Qt::red, Qt::CrossPattern));
    p_abstractShapeTester->setBrush(QBrush(Qt::white, Qt::NoBrush));
    QCOMPARE(p_abstractShapeTester->brush(), QBrush(Qt::white, Qt::NoBrush));
}

void tst_AbstractShape::isObscuredBy()
{
    QGraphicsScene scene;

    AbstractShapeTester * p_abstractShapeTester2 = new AbstractShapeTester();
    p_abstractShapeTester->setRect(QRectF(50, 50, 40, 200));
    p_abstractShapeTester->setTransform(QTransform().rotate(67), true);
    p_abstractShapeTester->setBrush(Qt::blue);
    p_abstractShapeTester2->setRect(QRectF(25, 25, 20, 20));
    p_abstractShapeTester2->setZValue(-1.0);
    p_abstractShapeTester2->setBrush(Qt::red);
    scene.addItem(p_abstractShapeTester);
    scene.addItem(p_abstractShapeTester2);

    QVERIFY(!p_abstractShapeTester2->isObscuredBy(p_abstractShapeTester));
    QVERIFY(!p_abstractShapeTester->isObscuredBy(p_abstractShapeTester2));

    p_abstractShapeTester2->setRect(QRectF(-50, 85, 20, 20));
    QVERIFY(p_abstractShapeTester2->isObscuredBy(p_abstractShapeTester));
    QVERIFY(!p_abstractShapeTester->isObscuredBy(p_abstractShapeTester2));

    p_abstractShapeTester2->setRect(QRectF(-30, 70, 20, 20));
    QVERIFY(!p_abstractShapeTester2->isObscuredBy(p_abstractShapeTester));
    QVERIFY(!p_abstractShapeTester->isObscuredBy(p_abstractShapeTester2));

    scene.removeItem(p_abstractShapeTester);
    scene.removeItem(p_abstractShapeTester2);
    delete p_abstractShapeTester2;
}

void tst_AbstractShape::opaqueArea()
{
    QGraphicsScene scene;

    p_abstractShapeTester->setRect(QRectF(-100.0, -100.0, 200.0, 200.0));
    p_abstractShapeTester->setZValue(-1.0);
    scene.addItem(p_abstractShapeTester);
    QPainterPath opaquePath;
    QCOMPARE(p_abstractShapeTester->opaqueArea(), opaquePath);

    p_abstractShapeTester->setBrush(QBrush(Qt::red));
    QCOMPARE(p_abstractShapeTester->opaqueArea(), p_abstractShapeTester->shape());

    AbstractShapeTester *p_opaqueShape = new AbstractShapeTester();
    p_opaqueShape->setRect(QRectF(-50.0, -50.0, 200.0, 200.0));
    p_opaqueShape->setBrush(QBrush(Qt::blue));
    p_abstractShapeTester->setFlag(QGraphicsItem::ItemClipsToShape, true);
    scene.addItem(p_opaqueShape);
    QCOMPARE(p_abstractShapeTester->opaqueArea(), p_abstractShapeTester->clipPath());

    AbstractShapeTester *p_parentShape = new AbstractShapeTester();
    p_parentShape->setRect(QRectF(-120.0, -120.0, 200.0, 200.0));
    p_parentShape->setParentItem(p_abstractShapeTester);
    p_parentShape->setBrush(QBrush(Qt::black));
    QCOMPARE(p_abstractShapeTester->opaqueArea(), p_abstractShapeTester->clipPath());

    p_abstractShapeTester->setFlag(QGraphicsItem::ItemClipsChildrenToShape, true);
    QCOMPARE(p_parentShape->opaqueArea(), p_parentShape->clipPath());

    scene.removeItem(p_parentShape);
    scene.removeItem(p_opaqueShape);
    scene.removeItem(p_abstractShapeTester);
    delete p_parentShape;
    delete p_opaqueShape;
}

void tst_AbstractShape::scaleShape()
{
    //TODO реализовать!
}

void tst_AbstractShape::menu_setMenu()
{
    QMenu *p_contextMenu = new QMenu();
    QAction *p_action1 = new QAction("Item 1");
    p_contextMenu->addAction(p_action1);
    QAction *p_action2 = new QAction("Item 2");
    p_contextMenu->addAction(p_action2);
    p_abstractShapeTester->setMenu(p_contextMenu);
    QCOMPARE(p_abstractShapeTester->menu()->actions().at(0), p_action1);
    QCOMPARE(p_abstractShapeTester->menu()->actions().at(1), p_action2);
    delete p_contextMenu;
    delete p_action1;
    delete p_action2;
}

void tst_AbstractShape::add_removeActions()
{
    QMenu contextMenu;
    p_abstractShapeTester->setMenu(&contextMenu);
    QCOMPARE(p_abstractShapeTester->menu()->actions().count(), 0);
    QAction *p_action1 = new QAction();
    QAction *p_action2 = new QAction();
    QAction *p_action3 = new QAction();
    QList<QAction *> actions;
    actions << p_action1 << p_action2 << p_action3;
    p_abstractShapeTester->addActions(actions);
    QCOMPARE(p_abstractShapeTester->menu()->actions().count(), 4);
    p_abstractShapeTester->removeActions(actions);
    QCOMPARE(p_abstractShapeTester->menu()->actions().count(), 0);
    p_abstractShapeTester->addActions(actions);
    QCOMPARE(p_abstractShapeTester->menu()->actions().count(), 4);
    p_abstractShapeTester->removeActions(actions);
    QCOMPARE(p_abstractShapeTester->menu()->actions().count(), 0);
}

void tst_AbstractShape::mouseDoubleClickEvent()
{
    QGraphicsScene scene;
    p_abstractShapeTester->setRect(QRectF(-20.0, -20.0, 40.0, 40.0));
    scene.addItem(p_abstractShapeTester);
    QCOMPARE(p_abstractShapeTester->childItems().count(), 0);

    QGraphicsSceneMouseEvent mouseDClickEvent(QEvent::GraphicsSceneMouseDoubleClick);
    mouseDClickEvent.setScenePos(p_abstractShapeTester->pos());
    mouseDClickEvent.setButton(Qt::LeftButton);
    QApplication::sendEvent(&scene, &mouseDClickEvent);
    QVERIFY(mouseDClickEvent.isAccepted());

    QGraphicsItem *sizegripItem = p_abstractShapeTester->childItems().constFirst();
    int itemVisible{0};
    for (int i = 0; i < sizegripItem->childItems().count(); i++) {
        QGraphicsItem *item {sizegripItem->childItems().at(i)};
        if (item->isVisible())
            itemVisible++;
    }
    QCOMPARE(itemVisible, 8);

    QApplication::sendEvent(&scene, &mouseDClickEvent);
    sizegripItem = p_abstractShapeTester->childItems().constFirst();
    itemVisible = 0;
    for (int i = 0; i < sizegripItem->childItems().count(); i++) {
        QGraphicsItem *item {sizegripItem->childItems().at(i)};
        if (item->isVisible())
            itemVisible++;
    }
    QCOMPARE(itemVisible, 4);

    QApplication::sendEvent(&scene, &mouseDClickEvent);
    sizegripItem = p_abstractShapeTester->childItems().constFirst();
    itemVisible = 0;
    for (int i = 0; i < sizegripItem->childItems().count(); i++) {
        QGraphicsItem *item {sizegripItem->childItems().at(i)};
        if (item->isVisible())
            itemVisible++;
    }
    QCOMPARE(itemVisible, 8);

    scene.removeItem(p_abstractShapeTester);
}

void tst_AbstractShape::mouseMoveEvent()
{
    QGraphicsScene scene;
    p_abstractShapeTester->setRect(QRectF(-10.0, -10.0, 20.0, 20.0));
    scene.addItem(p_abstractShapeTester);

    sendMousePress(&scene, p_abstractShapeTester->pos());
    QGraphicsSceneMouseEvent mouseMoveEvent(QEvent::GraphicsSceneMouseMove);
    mouseMoveEvent.setScenePos(p_abstractShapeTester->pos());
    mouseMoveEvent.setButton(Qt::LeftButton);
    QApplication::sendEvent(&scene, &mouseMoveEvent);
    QVERIFY(mouseMoveEvent.isAccepted());

    sendMousePress(&scene, p_abstractShapeTester->pos());
    sendMouseMove(&scene, QPointF(50.0, -50.0), Qt::LeftButton);
    QCOMPARE(p_abstractShapeTester->pos(), QPointF(50.0, -50.0));

    AbstractShapeTester *p_abstractShapeTester2 = new AbstractShapeTester();
    p_abstractShapeTester2->setRect(QRectF(-50.0, -50.0, 30.0, 25.0));
    p_abstractShapeTester2->setFlag(QGraphicsItem::ItemIsSelectable, true);
    scene.addItem(p_abstractShapeTester2);
    p_abstractShapeTester2->setSelected(true);

    sendMousePress(&scene, p_abstractShapeTester2->pos());
    sendMouseMove(&scene, QPointF(20.0, 20.0), Qt::LeftButton);
    QCOMPARE(p_abstractShapeTester2->pos(), QPointF(20.0, 20.0));

    scene.removeItem(p_abstractShapeTester);
    scene.removeItem(p_abstractShapeTester2);
    delete p_abstractShapeTester2;
}

class ContextMenuTester : public QMenu
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

void tst_AbstractShape::mousePressEvent()
{
    QGraphicsScene scene;
    QGraphicsView view(&scene);
    view.show();
    view.fitInView(scene.sceneRect());
    QVERIFY(QTest::qWaitForWindowActive(&view));
    ContextMenuTester *p_contextMenu = new ContextMenuTester();

    p_abstractShapeTester->setRect(QRectF(-20.0, -20.0, 40.0, 40.0));
    p_abstractShapeTester->setMenu(p_contextMenu);
    scene.addItem(p_abstractShapeTester);

    QGraphicsSceneMouseEvent mousePressEvent(QEvent::GraphicsSceneMouseMove);
    mousePressEvent.setScenePos(p_abstractShapeTester->pos());
    mousePressEvent.setButton(Qt::LeftButton);
    QApplication::sendEvent(&scene, &mousePressEvent);
    QVERIFY(mousePressEvent.isAccepted());

    p_abstractShapeTester->setSelected(true);
    QSignalSpy contextMenuSpy(p_abstractShapeTester->menu(), &QMenu::aboutToShow);
    QCOMPARE(contextMenuSpy.count(), 0);

    QTest::mouseClick(view.viewport(), Qt::RightButton, Qt::NoModifier
                      , view.mapFromScene(p_abstractShapeTester->boundingRect().center()));
    QCOMPARE(contextMenuSpy.count(), 1);

    scene.removeItem(p_abstractShapeTester);

    delete p_contextMenu;
}

void tst_AbstractShape::whellEvent()
{
    QGraphicsScene scene;
    QGraphicsView view(&scene);
    view.show();
    view.fitInView(scene.sceneRect());
    QVERIFY(QTest::qWaitForWindowActive(&view));

    p_abstractShapeTester->setRect(QRectF(-20.0, -20.0, 40.0, 40.0));
    scene.addItem(p_abstractShapeTester);

    QGraphicsSceneWheelEvent wheelEvent(QEvent::GraphicsSceneWheel);
    wheelEvent.setScenePos(p_abstractShapeTester->scenePos());
    wheelEvent.setDelta(1);
    QApplication::sendEvent(&scene, &wheelEvent);
    QVERIFY(!wheelEvent.isAccepted());

    p_abstractShapeTester->setSelected(true);
    p_abstractShapeTester->resetTransform();

    qreal m11Actual = p_abstractShapeTester->transform().m11();
    qreal m11Expected = 1.0;
    bool m11Compare = qFuzzyCompare(m11Actual, m11Expected);
    QVERIFY(m11Compare);

    qreal m22Actual = p_abstractShapeTester->transform().m22();
    qreal m22Expected = 1.0;
    bool m22Compare = qFuzzyCompare(m22Actual, m22Expected);
    QVERIFY(m22Compare);

    QTest::mouseMove(view.viewport(), p_abstractShapeTester->scenePos().toPoint());

    for (int i = 0; i < 40; i++) {
        sendMouseWheel(&scene, p_abstractShapeTester->scenePos(), 1);

        m11Actual = p_abstractShapeTester->transform().m11();
        m11Expected *= 1.03;
        m11Compare = qFuzzyCompare(m11Actual, m11Expected);
        QVERIFY(m11Compare);

        m22Actual = p_abstractShapeTester->transform().m22();
        m22Expected *= 1.03;
        m22Compare = qFuzzyCompare(m22Actual, m22Expected);
        QVERIFY(m22Compare);
    }

    for (int i = 0; i < 40; i++) {
        sendMouseWheel(&scene, p_abstractShapeTester->scenePos(), -1);

        m11Actual = p_abstractShapeTester->transform().m11();
        m11Expected *= 0.97;
        m11Compare = qFuzzyCompare(m11Actual, m11Expected);
        QVERIFY(m11Compare);

        m22Actual = p_abstractShapeTester->transform().m22();
        m22Expected *= 0.97;
        m22Compare = qFuzzyCompare(m22Actual, m22Expected);
        QVERIFY(m22Compare);
    }

    scene.removeItem(p_abstractShapeTester);
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

QTEST_MAIN(tst_AbstractShape)

#include "tst_abstractshape.moc"
