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

    //TankerShape, PumpHoseShape
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

    // PumpHoseShape
    TechnicsShape *p_pumpHoseShape = nullptr;
    p_pumpHoseShape = TechnicsShape::createTechnicsShape(TechnicsShape::PumpHose);
    QVERIFY2(p_pumpHoseShape, "pumpHoseShape is nullptr");
    QCOMPARE(int(p_pumpHoseShape->type()), int(QGraphicsItem::UserType + 203));
    TechnicsShape::TechnicsShapeDeleter::cleanup(p_pumpHoseShape);

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

    // PumpHoseShape
    TechnicsShape *p_pumpHoseShape = TechnicsShape::createTechnicsShape(TechnicsShape::PumpHose);
    QCOMPARE(p_pumpHoseShape->boundingRect(), QRectF(-15.5, -38.0, 31.0, 76.0));
    PumpHoseShape *p_pumpHose = dynamic_cast<PumpHoseShape *>(p_pumpHoseShape);
    p_pumpHose->setPipes(true);
    QCOMPARE(p_pumpHoseShape->boundingRect(), QRectF(-20.5, -38.0, 41.0, 76.0));
    p_pumpHose->setCollector(true);
    QCOMPARE(p_pumpHoseShape->boundingRect(), QRectF(-20.5, -38.0, 41.0, 86.0));
    p_pumpHose->setPipes(false);
    QCOMPARE(p_pumpHoseShape->boundingRect(), QRectF(-15.5, -38.0, 31.0, 86.0));
    p_pumpHose->setCollector(false);
    QCOMPARE(p_pumpHoseShape->boundingRect(), QRectF(-15.5, -38.0, 31.0, 76.0));
    TechnicsShape::TechnicsShapeDeleter::cleanup(p_pumpHoseShape);
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
    qreal sixthWidthTanker{tankerRect.width() / 6}; // 5.0
    qreal pipeYTanker{tankerRect.bottom() - sixthWidthTanker};
    QPointF rightPipeP1Tanker{tankerRect.right(), pipeYTanker};
    QPointF rightPipeP2Tanker{tankerRect.right() + sixthWidthTanker, pipeYTanker};
    // Right pipe
    tankerPath.moveTo(rightPipeP1Tanker);
    tankerPath.lineTo(rightPipeP2Tanker);
    QPointF rightConnectP1Tanker{rightPipeP2Tanker.x(), rightPipeP2Tanker.y()
                                                            + sixthWidthTanker / 2};
    QPointF rightConnectP2Tanker{rightPipeP2Tanker.x(), rightPipeP2Tanker.y()
                                                            - sixthWidthTanker / 2};
    // Right pipe connection
    tankerPath.moveTo(rightConnectP1Tanker);
    tankerPath.lineTo(rightConnectP2Tanker);
    QPointF leftPipeP1Tanker{tankerRect.left(), pipeYTanker};
    QPointF leftPipeP2Tanker{tankerRect.left() - sixthWidthTanker, pipeYTanker};
    // Left pipe
    tankerPath.moveTo(leftPipeP1Tanker);
    tankerPath.lineTo(leftPipeP2Tanker);
    QPointF leftConnectP1Tanker{leftPipeP2Tanker.x(), leftPipeP2Tanker.y()
                                                          + sixthWidthTanker / 2};
    QPointF leftConnectP2Tanker{leftPipeP2Tanker.x(), leftPipeP2Tanker.y()
                                                          - sixthWidthTanker / 2};
    // Right pipe connection
    tankerPath.moveTo(leftConnectP1Tanker);
    tankerPath.lineTo(leftConnectP2Tanker);
    strokeTankerPath = ps_tankerShape.createStroke(tankerPath);
    strokeTankerPath.addPath(tankerPath);
    QCOMPARE(p_tanker->shape(), strokeTankerPath);

    // TankerShape show collector
    tankerPath.clear();
    strokeTankerPath.clear();
    p_tanker->setPipes(false);
    p_tanker->setCollector(true);
    tankerPath.addPolygon(tankerPolygon);
    qreal collectorXTanker{tankerRect.center().x()};
    qreal collectorYTanker{tankerRect.bottom() + sixthWidthTanker * 2};
    qreal leftCollectorPipeXTanker{collectorXTanker - sixthWidthTanker};
    QPointF leftRightCollectorPipeP1Tanker{collectorXTanker, tankerRect.bottom()};
    QPointF leftCollectorPipe2Tanker{leftCollectorPipeXTanker, collectorYTanker};
    //Left collector pipe
    tankerPath.moveTo(leftRightCollectorPipeP1Tanker);
    tankerPath.lineTo(leftCollectorPipe2Tanker);
    qreal rightCollectorPipeXTanker{collectorXTanker + sixthWidthTanker};
    QPointF rightCollectorPipeP2Tanker{rightCollectorPipeXTanker, collectorYTanker};
    //Right collector pipe
    tankerPath.moveTo(leftRightCollectorPipeP1Tanker);
    tankerPath.lineTo(rightCollectorPipeP2Tanker);
    QPointF leftCollectorConnectP1Tanker{leftCollectorPipeXTanker - sixthWidthTanker / 2
                                         , collectorYTanker};
    QPointF leftCollectorConnectP2Tanker{leftCollectorPipeXTanker + sixthWidthTanker / 2
                                         , collectorYTanker};
    //Left connector
    tankerPath.moveTo(leftCollectorConnectP1Tanker);
    tankerPath.lineTo(leftCollectorConnectP2Tanker);
    QPointF rightCollectorConnectP1Tanker{rightCollectorPipeXTanker - sixthWidthTanker / 2
                                          , collectorYTanker};
    QPointF rightCollectorConnectP2Tanker{rightCollectorPipeXTanker + sixthWidthTanker / 2
                                          , collectorYTanker};
    //Right connector
    tankerPath.moveTo(rightCollectorConnectP1Tanker);
    tankerPath.lineTo(rightCollectorConnectP2Tanker);
    strokeTankerPath = ps_tankerShape.createStroke(tankerPath);
    strokeTankerPath.addPath(tankerPath);
    QCOMPARE(p_tanker->shape(), strokeTankerPath);

    p_tanker= nullptr;
    TechnicsShape::TechnicsShapeDeleter::cleanup(p_tankerShape);

    // PumpHoseShape
    TechnicsShape *p_pumpHoseShape = TechnicsShape::createTechnicsShape(TechnicsShape::PumpHose);
    QPainterPathStroker ps_pumpHoseShape;
    ps_pumpHoseShape.setWidth(p_pumpHoseShape->pen().widthF());
    QRectF pumpHoseRect{p_pumpHoseShape->rect()};
    qreal frontTabPumpHose{pumpHoseRect.height() / 3};
    QPointF frontCenterPumpHose{pumpHoseRect.center().x(), pumpHoseRect.top()}; // 0.0, -37.5
    QPointF frontRightPumpHose{pumpHoseRect.right(), pumpHoseRect.top() + frontTabPumpHose}; // 15.0, -12.5
    QPointF frontLeftPumpHose{pumpHoseRect.left(), pumpHoseRect.top() + frontTabPumpHose}; // -15.0, -12.5
    QPointF bottomRightPumpHose{pumpHoseRect.bottomRight()}; // 15.0, 37.5
    QPointF bottomLeftPumpHose{pumpHoseRect.bottomLeft()}; // -15.0, 37.5
    QPolygonF pumpHosePolygon;
    pumpHosePolygon << frontCenterPumpHose << frontRightPumpHose << bottomRightPumpHose
                  << bottomLeftPumpHose << frontLeftPumpHose << frontCenterPumpHose;
    QPainterPath pumpHosePath;
    pumpHosePath.addPolygon(pumpHosePolygon);
    QPainterPath strokePumpHosePath = ps_pumpHoseShape.createStroke(pumpHosePath);
    strokePumpHosePath.addPath(pumpHosePath);
    QCOMPARE(p_pumpHoseShape->shape(), strokePumpHosePath);

    // PumpHoseShape show pipes
    PumpHoseShape *p_pumpHose = dynamic_cast<PumpHoseShape *>(p_pumpHoseShape);
    pumpHosePath.clear();
    strokePumpHosePath.clear();
    p_pumpHose->setPipes(true);
    pumpHosePath.addPolygon(pumpHosePolygon);
    qreal sixtWidthPumpHose{pumpHoseRect.width() / 6}; // 5.0
    qreal pipeYPumpHose{pumpHoseRect.bottom() - sixtWidthPumpHose};
    QPointF rightPipeP1PumpHose{pumpHoseRect.right(), pipeYPumpHose};
    QPointF rightPipeP2PumpHose{pumpHoseRect.right() + sixtWidthPumpHose, pipeYPumpHose};
    // Right pipe
    pumpHosePath.moveTo(rightPipeP1PumpHose);
    pumpHosePath.lineTo(rightPipeP2PumpHose);
    QPointF rightConnectP1PumpHose{rightPipeP2PumpHose.x(), rightPipeP2PumpHose.y()
                                                                + sixtWidthPumpHose / 2};
    QPointF rightConnectP2PumpHose{rightPipeP2PumpHose.x(), rightPipeP2PumpHose.y()
                                                                - sixtWidthPumpHose / 2};
    // Right pipe connection
    pumpHosePath.moveTo(rightConnectP1PumpHose);
    pumpHosePath.lineTo(rightConnectP2PumpHose);
    QPointF leftPipeP1PumpHose{pumpHoseRect.left(), pipeYPumpHose};
    QPointF leftPipeP2PumpHose{pumpHoseRect.left() - sixtWidthPumpHose, pipeYPumpHose};
    // Left pipe
    pumpHosePath.moveTo(leftPipeP1PumpHose);
    pumpHosePath.lineTo(leftPipeP2PumpHose);
    QPointF leftConnectP1PumpHose{leftPipeP2PumpHose.x(), leftPipeP2PumpHose.y()
                                                              + sixtWidthPumpHose / 2};
    QPointF leftConnectP2PumpHose{leftPipeP2PumpHose.x(), leftPipeP2PumpHose.y()
                                                              - sixtWidthPumpHose / 2};
    // Right pipe connection
    pumpHosePath.moveTo(leftConnectP1PumpHose);
    pumpHosePath.lineTo(leftConnectP2PumpHose);
    strokePumpHosePath = ps_pumpHoseShape.createStroke(pumpHosePath);
    strokePumpHosePath.addPath(pumpHosePath);
    QCOMPARE(p_pumpHose->shape(), strokePumpHosePath);

    // PumpHoseShape show collector
    pumpHosePath.clear();
    strokePumpHosePath.clear();
    p_pumpHose->setPipes(false);
    p_pumpHose->setCollector(true);
    pumpHosePath.addPolygon(pumpHosePolygon);
    qreal collectorXPumpHose{pumpHoseRect.center().x()};
    qreal collectorYPumpHose{pumpHoseRect.bottom() + sixtWidthPumpHose * 2};
    qreal leftCollectorPipeXPumpHose{collectorXPumpHose - sixtWidthPumpHose};
    QPointF leftRightCollectorPipeP1PumpHose{collectorXPumpHose, pumpHoseRect.bottom()};
    QPointF leftCollectorPipeP2PumpHose{leftCollectorPipeXPumpHose, collectorYPumpHose};
    //Left collector pipe
    pumpHosePath.moveTo(leftRightCollectorPipeP1PumpHose);
    pumpHosePath.lineTo(leftCollectorPipeP2PumpHose);
    qreal rightCollectorPipeXPumpHose{collectorXPumpHose + sixtWidthPumpHose};
    QPointF rightCollectorPipeP2PumpHose{rightCollectorPipeXPumpHose, collectorYPumpHose};
    //Right collector pipe
    pumpHosePath.moveTo(leftRightCollectorPipeP1PumpHose);
    pumpHosePath.lineTo(rightCollectorPipeP2PumpHose);
    QPointF leftCollectorConnectP1PumpHose{leftCollectorPipeXPumpHose - sixtWidthPumpHose / 2
                                           , collectorYPumpHose};
    QPointF leftCollectorConnectP2PumpHose{leftCollectorPipeXPumpHose + sixtWidthPumpHose / 2
                                           , collectorYPumpHose};
    //Left connector
    pumpHosePath.moveTo(leftCollectorConnectP1PumpHose);
    pumpHosePath.lineTo(leftCollectorConnectP2PumpHose);
    QPointF rightCollectorConnectP1PumpHose{rightCollectorPipeXPumpHose - sixtWidthPumpHose / 2
                                            , collectorYPumpHose};
    QPointF rightCollectorConnectP2PumpHOse{rightCollectorPipeXPumpHose + sixtWidthPumpHose / 2
                                            , collectorYPumpHose};
    //Right connector
    pumpHosePath.moveTo(rightCollectorConnectP1PumpHose);
    pumpHosePath.lineTo(rightCollectorConnectP2PumpHOse);
    strokePumpHosePath = ps_pumpHoseShape.createStroke(pumpHosePath);
    strokePumpHosePath.addPath(pumpHosePath);
    QCOMPARE(p_pumpHose->shape(), strokePumpHosePath);

    p_pumpHose= nullptr;
    TechnicsShape::TechnicsShapeDeleter::cleanup(p_pumpHoseShape);
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

    // PumpHoseShape
    TechnicsShape *p_pumpHoseShape = TechnicsShape::createTechnicsShape(TechnicsShape::PumpHose);
    QPixmap pumpHoseImage{p_pumpHoseShape->image()};
    QVERIFY2(!pumpHoseImage.isNull(), "PumpHoseShape::image() returned a null pixmap");
    QCOMPARE(pumpHoseImage.width(), p_pumpHoseShape->boundingRect().width());
    QCOMPARE(pumpHoseImage.height(), p_pumpHoseShape->boundingRect().height());
    TechnicsShape::TechnicsShapeDeleter::cleanup(p_pumpHoseShape);
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

    // PumpHoseShape
    TechnicsShape *p_pumpHoseShape = TechnicsShape::createTechnicsShape(TechnicsShape::PumpHose);
    p_pumpHoseShape->setRect(rect);
    QCOMPARE(p_pumpHoseShape->rect(), rect);
    TechnicsShape::TechnicsShapeDeleter::cleanup(p_pumpHoseShape);
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

    // PumpHoseShape
    TechnicsShape *p_pumpHoseShape = TechnicsShape::createTechnicsShape(TechnicsShape::PumpHose);
    p_pumpHoseShape->setHeight(height);
    QCOMPARE(p_pumpHoseShape->height(), height);
    TechnicsShape::TechnicsShapeDeleter::cleanup(p_pumpHoseShape);
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
    QFETCH(QString, text);

    // BaseShape
    TechnicsShape *p_baseShape = TechnicsShape::createTechnicsShape(TechnicsShape::Base);
    p_baseShape->setText(text);
    QCOMPARE(p_baseShape->text(), text);
    TechnicsShape::TechnicsShapeDeleter::cleanup(p_baseShape);

    // TankerShape
    TechnicsShape *p_tankerShape = TechnicsShape::createTechnicsShape(TechnicsShape::Tanker);
    p_tankerShape->setText(text);
    QCOMPARE(p_tankerShape->text(), text);
    TechnicsShape::TechnicsShapeDeleter::cleanup(p_tankerShape);

    // PumpHoseShape
    TechnicsShape *p_pumpHoseShape = TechnicsShape::createTechnicsShape(TechnicsShape::PumpHose);
    p_pumpHoseShape->setText(text);
    QCOMPARE(p_pumpHoseShape->text(), text);
    TechnicsShape::TechnicsShapeDeleter::cleanup(p_pumpHoseShape);
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

    //PumpHoseShape
    TechnicsShape *p_pumpHoseShape = TechnicsShape::createTechnicsShape(TechnicsShape::PumpHose);
    PumpHoseShape *p_pumpHose = dynamic_cast<PumpHoseShape *>(p_pumpHoseShape);
    QCOMPARE(p_pumpHose->pipes(), false);
    p_pumpHose->setPipes(true);
    QCOMPARE(p_pumpHose->pipes(), true);
    p_pumpHose->setPipes(false);
    QCOMPARE(p_pumpHose->pipes(), false);
    p_pumpHose= nullptr;
    TechnicsShape::TechnicsShapeDeleter::cleanup(p_pumpHoseShape);
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

    //PumpHoseShape
    TechnicsShape *p_pumpHoseShape = TechnicsShape::createTechnicsShape(TechnicsShape::PumpHose);
    PumpHoseShape *p_pumpHose= dynamic_cast<PumpHoseShape *>(p_pumpHoseShape);
    QCOMPARE(p_pumpHose->collector(), false);
    p_pumpHose->setCollector(true);
    QCOMPARE(p_pumpHose->collector(), true);
    p_pumpHose->setCollector(false);
    QCOMPARE(p_pumpHose->collector(), false);
    p_pumpHose = nullptr;
    TechnicsShape::TechnicsShapeDeleter::cleanup(p_pumpHoseShape);
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
    QGraphicsScene scene;
    QGraphicsView view(&scene);
    view.show();
    view.fitInView(scene.sceneRect());
    QVERIFY(QTest::qWaitForWindowActive(&view));

    QGraphicsSceneMouseEvent mousePressEvent(QEvent::GraphicsSceneMouseMove);
    mousePressEvent.setButton(Qt::LeftButton);

    // BaseShape
    ContextMenuTester *p_baseContextMenu = new ContextMenuTester();

    TechnicsShape *p_baseShape = TechnicsShape::createTechnicsShape(TechnicsShape::Base);
    p_baseShape->setMenu(p_baseContextMenu);
    scene.addItem(p_baseShape);

    mousePressEvent.setScenePos(p_baseShape->pos());
    QApplication::sendEvent(&scene, &mousePressEvent);
    QVERIFY(mousePressEvent.isAccepted());

    p_baseShape->setSelected(true);
    QSignalSpy baseContextMenuSpy(p_baseShape->menu(), &QMenu::aboutToShow);
    QCOMPARE(baseContextMenuSpy.count(), 0);

    QList<QAction *> baseMenuActions{p_baseShape->menu()->actions()};
    QCOMPARE(baseMenuActions.size(), 1);
    baseMenuActions.clear();

    QTest::mouseClick(view.viewport(), Qt::RightButton, Qt::NoModifier
                      , view.mapFromScene(p_baseShape->boundingRect().center()));
    baseMenuActions = p_baseShape->menu()->actions();
    QCOMPARE(baseMenuActions.size(), 1);
    QCOMPARE(baseContextMenuSpy.count(), 1);

    scene.removeItem(p_baseShape);
    delete p_baseContextMenu;
    TechnicsShape::TechnicsShapeDeleter::cleanup(p_baseShape);

    // TankerShape
    ContextMenuTester *p_tankerContextMenu = new ContextMenuTester();

    TechnicsShape *p_tankerShape = TechnicsShape::createTechnicsShape(TechnicsShape::Tanker);
    p_tankerShape->setMenu(p_tankerContextMenu);
    scene.addItem(p_tankerShape);

    mousePressEvent.setScenePos(p_tankerShape->pos());
    QApplication::sendEvent(&scene, &mousePressEvent);
    QVERIFY(mousePressEvent.isAccepted());

    p_tankerShape->setSelected(true);
    QSignalSpy tankerContextMenuSpy(p_tankerShape->menu(), &QMenu::aboutToShow);
    QCOMPARE(tankerContextMenuSpy.count(), 0);

    QList<QAction *> tankerMenuActions{p_tankerShape->menu()->actions()};
    QCOMPARE(tankerMenuActions.size(), 1);
    tankerMenuActions.clear();

    QTest::mouseClick(view.viewport(), Qt::RightButton, Qt::NoModifier
                      , view.mapFromScene(p_tankerShape->boundingRect().center()));
    tankerMenuActions = p_tankerShape->menu()->actions();
    QCOMPARE(tankerMenuActions.size(), 1);
    QCOMPARE(tankerContextMenuSpy.count(), 1);

    scene.removeItem(p_tankerShape);
    delete p_tankerContextMenu;
    TechnicsShape::TechnicsShapeDeleter::cleanup(p_tankerShape);

    // PumpHoseShape
    ContextMenuTester *p_pumpHoseContextMenu = new ContextMenuTester();

    TechnicsShape *p_pumpHoseShape = TechnicsShape::createTechnicsShape(TechnicsShape::PumpHose);
    p_pumpHoseShape->setMenu(p_pumpHoseContextMenu);
    scene.addItem(p_pumpHoseShape);

    mousePressEvent.setScenePos(p_pumpHoseShape->pos());
    QApplication::sendEvent(&scene, &mousePressEvent);
    QVERIFY(mousePressEvent.isAccepted());

    p_pumpHoseShape->setSelected(true);
    QSignalSpy pumpHoseContextMenuSpy(p_pumpHoseShape->menu(), &QMenu::aboutToShow);
    QCOMPARE(pumpHoseContextMenuSpy.count(), 0);

    QList<QAction *> pumpHoseMenuActions{p_pumpHoseShape->menu()->actions()};
    QCOMPARE(pumpHoseMenuActions.size(), 1);
    pumpHoseMenuActions.clear();

    QTest::mouseClick(view.viewport(), Qt::RightButton, Qt::NoModifier
                      , view.mapFromScene(p_pumpHoseShape->boundingRect().center()));
    pumpHoseMenuActions = p_pumpHoseShape->menu()->actions();
    QCOMPARE(pumpHoseMenuActions.size(), 1);
    QCOMPARE(pumpHoseContextMenuSpy.count(), 1);

    scene.removeItem(p_pumpHoseShape);
    delete p_pumpHoseContextMenu;
    TechnicsShape::TechnicsShapeDeleter::cleanup(p_pumpHoseShape);
}

QTEST_MAIN(tst_TechnicShape)

#include "tst_technicsshape.moc"
