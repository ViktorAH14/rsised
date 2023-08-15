/*
 * Copyright (c) 2022 by Viktor Ermolov <ermolovva@gmail.com>.
 *
 * This file is part of the RSiSed project, an editor of the alignment of forces
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

#include "../../../../src/include/technicsshape.h"

#include <QtTest>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QGraphicsSceneMouseEvent>

class tst_TechnicShape : public QObject
{
    Q_OBJECT

private slots:
    void constructor();
    void boundingRect();
    void shape();
    void image();
    void rect_setRect_data();
    void rect_setRect();
    void height_setHeight_data();
    void height_setHeight();
    void text_setText_data();
    void text_setText();

    //TankerShape
    void pipes_setPipes();
    void collector_setCollector();
    void mousePressEvent();
};



void tst_TechnicShape::constructor()
{
    // BaseShape
    TechnicsShape *p_baseShape = nullptr;
    p_baseShape = TechnicsShape::createTechnicsShape(TechnicsShape::Base);
    QVERIFY2(p_baseShape, "baseShape is  nullptr");
    QCOMPARE(int(p_baseShape->type()), int(QGraphicsItem::UserType + 201));
    QCOMPARE(p_baseShape->shapeType(), TechnicsShape::Base);
    TechnicsShape::TechnicsShapeDeleter::cleanup(p_baseShape);

    // TankerShape
    TechnicsShape *p_tankerShape = nullptr;
    p_tankerShape = TechnicsShape::createTechnicsShape(TechnicsShape::Tanker);
    QVERIFY2(p_tankerShape, "tankerShape is nullptr");
    QCOMPARE(int(p_tankerShape->type()), int(QGraphicsItem::UserType + 202));
    TechnicsShape::TechnicsShapeDeleter::cleanup(p_tankerShape);

}

void tst_TechnicShape::boundingRect()
{
    // BaseShape
    TechnicsShape *p_baseShape = TechnicsShape::createTechnicsShape(TechnicsShape::Base);
    QCOMPARE(p_baseShape->boundingRect(), QRectF(-15.5, -38.2, 31.0, 76.0));
    TechnicsShape::TechnicsShapeDeleter::cleanup(p_baseShape);

    // TankerShape
    TechnicsShape *p_tankerShape = TechnicsShape::createTechnicsShape(TechnicsShape::Tanker);
    QCOMPARE(p_tankerShape->boundingRect(), QRectF(-15.5, -38.0, 31.0, 76.0));
    TankerShape *p_tanker = dynamic_cast<TankerShape *>(p_tankerShape);
    p_tanker->setPipes(true);
    QCOMPARE(p_tankerShape->boundingRect(), QRectF(-20.5, -38.0, 41.0, 76.0));
    p_tanker->setCollector(true);
    QCOMPARE(p_tankerShape->boundingRect(), QRectF(-20.5, -38.0, 41.0, 86.0));
    p_tanker->setPipes(false);
    QCOMPARE(p_tankerShape->boundingRect(), QRectF(-15.5, -38.0, 31.0, 86.0));
    p_tanker->setCollector(false);
    QCOMPARE(p_tankerShape->boundingRect(), QRectF(-15.5, -38.0, 31.0, 76.0));
    TechnicsShape::TechnicsShapeDeleter::cleanup(p_tankerShape);
}

void tst_TechnicShape::shape()
{
    // BaseShape
    TechnicsShape *p_baseShape = TechnicsShape::createTechnicsShape(TechnicsShape::Base);
    QPainterPathStroker ps_baseShape;
    ps_baseShape.setWidth(p_baseShape->pen().widthF());
    QRectF baseRect{p_baseShape->rect()};
    qreal frontTabBase{baseRect.height() / 3};
    QPointF frontCenterBase{baseRect.center().x(), baseRect.top()}; // 0.0, -37.5
    QPointF frontRightBase{baseRect.right(), baseRect.top() + frontTabBase}; // 15.0, -12.5
    QPointF frontLeftBase{baseRect.left(), baseRect.top() + frontTabBase}; // -15.0, -12.5
    QPointF bottomRightBase{baseRect.bottomRight()}; // 15.0, 37.5
    QPointF bottomLeftBase{baseRect.bottomLeft()}; // -15.0, 37.5
    QPolygonF basePolygon;
    basePolygon << frontCenterBase << frontRightBase << bottomRightBase << bottomLeftBase
                << frontLeftBase << frontCenterBase;
    QPainterPath basePath;
    basePath.addPolygon(basePolygon);
    QPainterPath strokeBasePath = ps_baseShape.createStroke(basePath);
    strokeBasePath.addPath(basePath);
    QCOMPARE(p_baseShape->shape(), strokeBasePath);
    TechnicsShape::TechnicsShapeDeleter::cleanup(p_baseShape);

    // TankerShape
    TechnicsShape *p_tankerShape = TechnicsShape::createTechnicsShape(TechnicsShape::Tanker);
    QPainterPathStroker ps_tankerShape;
    ps_tankerShape.setWidth(p_tankerShape->pen().widthF());
    QRectF tankerRect{p_tankerShape->rect()};
    qreal frontTabTanker{tankerRect.height() / 3};
    QPointF frontCenterTanker{tankerRect.center().x(), tankerRect.top()}; // 0.0, -37.5
    QPointF frontRightTanker{tankerRect.right(), tankerRect.top() + frontTabTanker}; // 15.0, -12.5
    QPointF frontLeftTanker{tankerRect.left(), tankerRect.top() + frontTabTanker}; // -15.0, -12.5
    QPointF bottomRightTanker{tankerRect.bottomRight()}; // 15.0, 37.5
    QPointF bottomLeftTanker{tankerRect.bottomLeft()}; // -15.0, 37.5
    QPolygonF tankerPolygon;
    tankerPolygon << frontCenterTanker << frontRightTanker << bottomRightTanker
                << bottomLeftTanker << frontLeftTanker << frontCenterTanker;
    QPainterPath tankerPath;
    tankerPath.addPolygon(tankerPolygon);
    QPainterPath strokeTankerPath = ps_tankerShape.createStroke(tankerPath);
    strokeTankerPath.addPath(tankerPath);
    QCOMPARE(p_tankerShape->shape(), strokeTankerPath);

    // TankerShape show pipes
    TankerShape *p_tanker = dynamic_cast<TankerShape *>(p_tankerShape);
    tankerPath.clear();
    strokeTankerPath.clear();
    p_tanker->setPipes(true);
    tankerPath.addPolygon(tankerPolygon);
    qreal roundRadius{tankerRect.width() / 6}; // 5.0
    qreal pipeY{tankerRect.bottom() - roundRadius};
    QPointF rightPipeP1{tankerRect.right(), pipeY};
    QPointF rightPipeP2{tankerRect.right() + roundRadius, pipeY};
    // Right pipe
    tankerPath.moveTo(rightPipeP1);
    tankerPath.lineTo(rightPipeP2);
    QPointF rightConnectP1{rightPipeP2.x(), rightPipeP2.y() + roundRadius / 2};
    QPointF rightConnectP2{rightPipeP2.x(), rightPipeP2.y() - roundRadius / 2};
    // Right pipe connection
    tankerPath.moveTo(rightConnectP1);
    tankerPath.lineTo(rightConnectP2);
    QPointF leftPipeP1{tankerRect.left(), pipeY};
    QPointF leftPipeP2{tankerRect.left() - roundRadius, pipeY};
    // Left pipe
    tankerPath.moveTo(leftPipeP1);
    tankerPath.lineTo(leftPipeP2);
    QPointF leftConnectP1{leftPipeP2.x(), leftPipeP2.y() + roundRadius / 2};
    QPointF leftConnectP2{leftPipeP2.x(), leftPipeP2.y() - roundRadius / 2};
    // Right pipe connection
    tankerPath.moveTo(leftConnectP1);
    tankerPath.lineTo(leftConnectP2);
    strokeTankerPath = ps_tankerShape.createStroke(tankerPath);
    strokeTankerPath.addPath(tankerPath);
    QCOMPARE(p_tanker->shape(), strokeTankerPath);

    // TankerShape show collector
    tankerPath.clear();
    strokeTankerPath.clear();
    p_tanker->setPipes(false);
    p_tanker->setCollector(true);
    tankerPath.addPolygon(tankerPolygon);
    qreal collectorX{tankerRect.center().x()};
    qreal collectorY{tankerRect.bottom() + roundRadius * 2};
    qreal leftCollectorPipeX{collectorX - roundRadius};
    QPointF leftRightCollectorPipeP1{collectorX, tankerRect.bottom()};
    QPointF leftCollectorPipeP2{leftCollectorPipeX, collectorY};
    //Left collector pipe
    tankerPath.moveTo(leftRightCollectorPipeP1);
    tankerPath.lineTo(leftCollectorPipeP2);
    qreal rightCollectorPipeX{collectorX + roundRadius};
    QPointF rightCollectorPipeP2{rightCollectorPipeX, collectorY};
    //Right collector pipe
    tankerPath.moveTo(leftRightCollectorPipeP1);
    tankerPath.lineTo(rightCollectorPipeP2);
    QPointF leftCollectorConnectP1{leftCollectorPipeX - roundRadius / 2, collectorY};
    QPointF leftCollectorConnectP2{leftCollectorPipeX + roundRadius / 2, collectorY};
    //Left connector
    tankerPath.moveTo(leftCollectorConnectP1);
    tankerPath.lineTo(leftCollectorConnectP2);
    QPointF rightCollectorConnectP1{rightCollectorPipeX - roundRadius / 2, collectorY};
    QPointF rightCollectorConnectP2{rightCollectorPipeX + roundRadius / 2, collectorY};
    //Right connector
    tankerPath.moveTo(rightCollectorConnectP1);
    tankerPath.lineTo(rightCollectorConnectP2);
    strokeTankerPath = ps_tankerShape.createStroke(tankerPath);
    strokeTankerPath.addPath(tankerPath);
    QCOMPARE(p_tanker->shape(), strokeTankerPath);

    p_tanker= nullptr;
    TechnicsShape::TechnicsShapeDeleter::cleanup(p_tankerShape);
}

void tst_TechnicShape::image()
{
    // BaseShape
    TechnicsShape *p_baseShape = TechnicsShape::createTechnicsShape(TechnicsShape::Base);
    QPixmap baseImage{p_baseShape->image()};
    QVERIFY2(!baseImage.isNull(), "BaseShape::image() returned a null pixmap");
    QCOMPARE(baseImage.width(), p_baseShape->boundingRect().width());
    QCOMPARE(baseImage.height(), p_baseShape->boundingRect().height());
    TechnicsShape::TechnicsShapeDeleter::cleanup(p_baseShape);

    // TankerShape
    TechnicsShape *p_tankerShape = TechnicsShape::createTechnicsShape(TechnicsShape::Tanker);
    QPixmap tankerImage{p_tankerShape->image()};
    QVERIFY2(!tankerImage.isNull(), "TankerShape::image() returned a null pixmap");
    QCOMPARE(tankerImage.width(), p_tankerShape->boundingRect().width());
    QCOMPARE(tankerImage.height(), p_tankerShape->boundingRect().height());
    TechnicsShape::TechnicsShapeDeleter::cleanup(p_tankerShape);
}

void tst_TechnicShape::rect_setRect_data()
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

void tst_TechnicShape::rect_setRect()
{
    QFETCH(QRectF, rect);

    // BaseShape
    TechnicsShape *p_baseShape = TechnicsShape::createTechnicsShape(TechnicsShape::Base);
    p_baseShape->setRect(rect);
    QCOMPARE(p_baseShape->rect(), rect);
    TechnicsShape::TechnicsShapeDeleter::cleanup(p_baseShape);

    // TankerShape
    TechnicsShape *p_tankerShape = TechnicsShape::createTechnicsShape(TechnicsShape::Tanker);
    p_tankerShape->setRect(rect);
    QCOMPARE(p_tankerShape->rect(), rect);
    TechnicsShape::TechnicsShapeDeleter::cleanup(p_tankerShape);
}

void tst_TechnicShape::height_setHeight_data()
{
    QTest::addColumn<qreal>("height");
    QTest::newRow("height_0") << 0.0;
    QTest::newRow("height_01") << 0.1;
    QTest::newRow("height_-01") << -0.1;
    QTest::newRow("height_-6") << -6.0;
    QTest::newRow("height_6") << 6.0;
    QTest::newRow("height_30") << 30.0;
    QTest::newRow("height_50") << 50.0;
    QTest::newRow("height_9999") << 9999.0;
}

void tst_TechnicShape::height_setHeight()
{
    QFETCH(qreal, height);

    // BaseShape
    TechnicsShape *p_baseShape = TechnicsShape::createTechnicsShape(TechnicsShape::Base);
    p_baseShape->setHeight(height);
    QCOMPARE(p_baseShape->height(), height);
    TechnicsShape::TechnicsShapeDeleter::cleanup(p_baseShape);

    // TankerShape
    TechnicsShape *p_tankerShape = TechnicsShape::createTechnicsShape(TechnicsShape::Tanker);
    p_tankerShape->setHeight(height);
    QCOMPARE(p_tankerShape->height(), height);
    TechnicsShape::TechnicsShapeDeleter::cleanup(p_tankerShape);
}

void tst_TechnicShape::text_setText_data()
{
    QTest::addColumn<QString>("text");
    QTest::newRow("null") << QString();
    QTest::newRow("empty") << QString("");
    QTest::newRow("special") << QString("/~`!@#$%^&*()_+|;:'<,>.?{[}]");
    QTest::newRow("number") << QString("13027");
    QTest::newRow("appercase") << QString("TANKER");
    QTest::newRow("lowercase") << QString("tanker");
    QTest::newRow("appercase_lowercase") << QString("TaNkEr tAnKeR");
    QTest::newRow("long_string") << QString("`1234456678900-=fqwuieop ruiewopyopr[]eu dufgoiuzxc"
                                            "wyreutiwofjhvgmc;mln;g lsdfkuhjeoi ncvmsfguwygpdg");
    QTest::newRow("long_string_ru") << QString("ФАукпарш амфгшнек ывалдоварФАКУКаыпомщ магврВРПР"
                                               "врагфшы вапшгГЕГНШОР РШГЕГП 164732834 сырогэдфё");
}

void tst_TechnicShape::text_setText()
{
    // TankerShape
    QFETCH(QString, text);
    TechnicsShape *p_tankerShape = TechnicsShape::createTechnicsShape(TechnicsShape::Tanker);
    p_tankerShape->setText(text);
    QCOMPARE(p_tankerShape->text(), text);
    TechnicsShape::TechnicsShapeDeleter::cleanup(p_tankerShape);
}

void tst_TechnicShape::pipes_setPipes()
{
    //TankerShape
    TechnicsShape *p_tankerShape = TechnicsShape::createTechnicsShape(TechnicsShape::Tanker);
    TankerShape *p_tanker = dynamic_cast<TankerShape *>(p_tankerShape);
    QCOMPARE(p_tanker->pipes(), false);
    p_tanker->setPipes(true);
    QCOMPARE(p_tanker->pipes(), true);
    p_tanker->setPipes(false);
    QCOMPARE(p_tanker->pipes(), false);
    p_tanker = nullptr;
    TechnicsShape::TechnicsShapeDeleter::cleanup(p_tankerShape);
}

void tst_TechnicShape::collector_setCollector()
{
    //TankerShape
    TechnicsShape *p_tankerShape = TechnicsShape::createTechnicsShape(TechnicsShape::Tanker);
    TankerShape *p_tanker = dynamic_cast<TankerShape *>(p_tankerShape);
    QCOMPARE(p_tanker->collector(), false);
    p_tanker->setCollector(true);
    QCOMPARE(p_tanker->collector(), true);
    p_tanker->setCollector(false);
    QCOMPARE(p_tanker->collector(), false);
    p_tanker = nullptr;
    TechnicsShape::TechnicsShapeDeleter::cleanup(p_tankerShape);
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

void tst_TechnicShape::mousePressEvent()
{
    // Tankershape
    QGraphicsScene scene;
    QGraphicsView view(&scene);
    view.show();
    view.fitInView(scene.sceneRect());
    QVERIFY(QTest::qWaitForWindowActive(&view));
    ContextMenuTester *p_contextMenu = new ContextMenuTester();

    TechnicsShape *p_tankerShape = TechnicsShape::createTechnicsShape(TechnicsShape::Tanker);
    p_tankerShape->setMenu(p_contextMenu);
    scene.addItem(p_tankerShape);

    QGraphicsSceneMouseEvent mousePressEvent(QEvent::GraphicsSceneMouseMove);
    mousePressEvent.setScenePos(p_tankerShape->pos());
    mousePressEvent.setButton(Qt::LeftButton);
    QApplication::sendEvent(&scene, &mousePressEvent);
    QVERIFY(mousePressEvent.isAccepted());

    p_tankerShape->setSelected(true);
    QSignalSpy contextMenuSpy(p_tankerShape->menu(), &QMenu::aboutToShow);
    QCOMPARE(contextMenuSpy.count(), 0);

    QList<QAction *> menuActions{p_tankerShape->menu()->actions()};
    QCOMPARE(menuActions.size(), 1);
    menuActions.clear();

    QTest::mouseClick(view.viewport(), Qt::RightButton, Qt::NoModifier
                      , view.mapFromScene(p_tankerShape->boundingRect().center()));
    menuActions = p_tankerShape->menu()->actions();
    QCOMPARE(menuActions.size(), 1);
    QCOMPARE(contextMenuSpy.count(), 1);

    scene.removeItem(p_tankerShape);

    delete p_contextMenu;
    TechnicsShape::TechnicsShapeDeleter::cleanup(p_tankerShape);
}

QTEST_MAIN(tst_TechnicShape)

#include "tst_technicsshape.moc"
