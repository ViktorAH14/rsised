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

    //TankerShape, PumpHoseShape, FirstAidShape, EmergencyShape
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

    // FirstAidShape
    TechnicsShape *p_firstAidShape = nullptr;
    p_firstAidShape = TechnicsShape::createTechnicsShape(TechnicsShape::FirstAid);
    QVERIFY2(p_firstAidShape, "pumpHoseShape is nullptr");
    QCOMPARE(int(p_firstAidShape->type()), int(QGraphicsItem::UserType + 204));
    TechnicsShape::TechnicsShapeDeleter::cleanup(p_firstAidShape);

    // EmergencyShape
    TechnicsShape *p_emergencyShape = nullptr;
    p_emergencyShape = TechnicsShape::createTechnicsShape(TechnicsShape::Emergency);
    QVERIFY2(p_emergencyShape, "emergencyShape is nullptr");
    QCOMPARE(int(p_emergencyShape->type()), int(QGraphicsItem::UserType + 205));
    TechnicsShape::TechnicsShapeDeleter::cleanup(p_emergencyShape);

    // AutoLadderShape
    TechnicsShape *p_autoLadderShape = nullptr;
    p_autoLadderShape = TechnicsShape::createTechnicsShape(TechnicsShape::AutoLadder);
    QVERIFY2(p_autoLadderShape, "autoLadderShape is nullptr");
    QCOMPARE(int(p_autoLadderShape->type()), int(QGraphicsItem::UserType + 206));
    TechnicsShape::TechnicsShapeDeleter::cleanup(p_autoLadderShape);

    // CrancLiftShape
    TechnicsShape *p_crankLiftShape = nullptr;
    p_crankLiftShape = TechnicsShape::createTechnicsShape(TechnicsShape::CrankLift);
    QVERIFY2(p_crankLiftShape, "crankLiftShape is nullptr");
    QCOMPARE(int(p_crankLiftShape->type()), int(QGraphicsItem::UserType + 207));
    TechnicsShape::TechnicsShapeDeleter::cleanup(p_crankLiftShape);

    // TelescopicLiftShape
    TechnicsShape *p_telescopicLiftShape = nullptr;
    p_telescopicLiftShape = TechnicsShape::createTechnicsShape(TechnicsShape::TelescopicLift);
    QVERIFY2(p_telescopicLiftShape, "telescopicLiftShape is nullptr");
    QCOMPARE(int(p_telescopicLiftShape->type()), int(QGraphicsItem::UserType + 208));
    TechnicsShape::TechnicsShapeDeleter::cleanup(p_telescopicLiftShape);

    // HoseCarShape
    TechnicsShape *p_hoseCarShape = nullptr;
    p_hoseCarShape = TechnicsShape::createTechnicsShape(TechnicsShape::HoseCar);
    QVERIFY2(p_hoseCarShape, "hoseCarShape is nullptr");
    QCOMPARE(int(p_hoseCarShape->type()), int(QGraphicsItem::UserType + 209));
    TechnicsShape::TechnicsShapeDeleter::cleanup(p_hoseCarShape);

    // CommShape
    TechnicsShape *p_commShape = nullptr;
    p_commShape = TechnicsShape::createTechnicsShape(TechnicsShape::Comm);
    QVERIFY2(p_commShape, "commShape is nullptr");
    QCOMPARE(int(p_commShape->type()), int(QGraphicsItem::UserType + 210));
    TechnicsShape::TechnicsShapeDeleter::cleanup(p_commShape);
}

void tst_TechnicShape::boundingRect()
{
    // BaseShape
    TechnicsShape *p_baseShape = TechnicsShape::createTechnicsShape(TechnicsShape::Base);
    QCOMPARE(p_baseShape->boundingRect(), QRectF(-15.5, -38.0, 31.0, 76.0));
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

    // FirstAidShape
    TechnicsShape *p_firsAidShape = TechnicsShape::createTechnicsShape(TechnicsShape::FirstAid);
    QCOMPARE(p_firsAidShape->boundingRect(), QRectF(-15.5, -38.0, 31.0, 76.0));
    FirstAidShape *p_firstAid = dynamic_cast<FirstAidShape *>(p_firsAidShape);
    p_firstAid->setPipes(true);
    QCOMPARE(p_firsAidShape->boundingRect(), QRectF(-20.5, -38.0, 41.0, 76.0));
    p_firstAid->setCollector(true);
    QCOMPARE(p_firsAidShape->boundingRect(), QRectF(-20.5, -38.0, 41.0, 86.0));
    p_firstAid->setPipes(false);
    QCOMPARE(p_firsAidShape->boundingRect(), QRectF(-15.5, -38.0, 31.0, 86.0));
    p_firstAid->setCollector(false);
    QCOMPARE(p_firsAidShape->boundingRect(), QRectF(-15.5, -38.0, 31.0, 76.0));
    TechnicsShape::TechnicsShapeDeleter::cleanup(p_firsAidShape);

    // EmergencyShape
    TechnicsShape *p_emergencyShape = TechnicsShape::createTechnicsShape(TechnicsShape::Emergency);
    QCOMPARE(p_emergencyShape->boundingRect(), QRectF(-15.5, -38.0, 31.0, 76.0));
    EmergencyShape *p_emergency = dynamic_cast<EmergencyShape *>(p_emergencyShape);
    p_emergency->setPipes(true);
    QCOMPARE(p_emergencyShape->boundingRect(), QRectF(-20.5, -38.0, 41.0, 76.0));
    p_emergency->setCollector(true);
    QCOMPARE(p_emergencyShape->boundingRect(), QRectF(-20.5, -38.0, 41.0, 86.0));
    p_emergency->setPipes(false);
    QCOMPARE(p_emergencyShape->boundingRect(), QRectF(-15.5, -38.0, 31.0, 86.0));
    p_emergency->setCollector(false);
    QCOMPARE(p_emergencyShape->boundingRect(), QRectF(-15.5, -38.0, 31.0, 76.0));
    TechnicsShape::TechnicsShapeDeleter::cleanup(p_emergencyShape);

    // AutoLadderShape
    TechnicsShape *p_autoLadderShape = TechnicsShape::createTechnicsShape(TechnicsShape::AutoLadder);
    QCOMPARE(p_autoLadderShape->boundingRect(), QRectF(-15.5, -38.0, 31.0, 76.0));
    TechnicsShape::TechnicsShapeDeleter::cleanup(p_autoLadderShape);

    // CrankLiftShape
    TechnicsShape *p_crankLiftShape = TechnicsShape::createTechnicsShape(TechnicsShape::CrankLift);
    QCOMPARE(p_crankLiftShape->boundingRect(), QRectF(-15.5, -38.0, 31.0, 76.0));
    TechnicsShape::TechnicsShapeDeleter::cleanup(p_crankLiftShape);

    // TelescopicLiftShape
    TechnicsShape *p_telescopicLiftShape = TechnicsShape::createTechnicsShape(TechnicsShape::TelescopicLift);
    QCOMPARE(p_telescopicLiftShape->boundingRect(), QRectF(-15.5, -38.0, 31.0, 76.0));
    TechnicsShape::TechnicsShapeDeleter::cleanup(p_telescopicLiftShape);

    // HoseCarShape
    TechnicsShape *p_hoseCarShape = TechnicsShape::createTechnicsShape(TechnicsShape::HoseCar);
    QCOMPARE(p_hoseCarShape->boundingRect(), QRectF(-15.5, -38.0, 31.0, 76.0));
    TechnicsShape::TechnicsShapeDeleter::cleanup(p_hoseCarShape);

    // CommShape
    TechnicsShape *p_commShape = TechnicsShape::createTechnicsShape(TechnicsShape::Comm);
    QCOMPARE(p_commShape->boundingRect(), QRectF(-15.5, -38.0, 31.0, 76.0));
    TechnicsShape::TechnicsShapeDeleter::cleanup(p_commShape);
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

    // FirstAidShape
    TechnicsShape *p_firstAidShape = TechnicsShape::createTechnicsShape(TechnicsShape::FirstAid);
    QPainterPathStroker ps_firstAidShape;
    ps_firstAidShape.setWidth(p_firstAidShape->pen().widthF());
    QRectF firstAidRect{p_firstAidShape->rect()};
    qreal frontTabFirstAid{firstAidRect.height() / 3};
    QPointF frontCenterFirstAid{firstAidRect.center().x(), firstAidRect.top()}; // 0.0, -37.5
    QPointF frontRightFirstAid{firstAidRect.right(), firstAidRect.top() + frontTabFirstAid}; // 15.0, -12.5
    QPointF frontLeftFirstAid{firstAidRect.left(), firstAidRect.top() + frontTabFirstAid}; // -15.0, -12.5
    QPointF bottomRightFirstAid{firstAidRect.bottomRight()}; // 15.0, 37.5
    QPointF bottomLeftFirstAid{firstAidRect.bottomLeft()}; // -15.0, 37.5
    QPolygonF firstAidPolygon;
    firstAidPolygon << frontCenterFirstAid << frontRightFirstAid << bottomRightFirstAid
                    << bottomLeftFirstAid << frontLeftFirstAid << frontCenterFirstAid;
    QPainterPath firstAidPath;
    firstAidPath.addPolygon(firstAidPolygon);
    QPainterPath strokeFirstAidPath = ps_firstAidShape.createStroke(firstAidPath);
    strokeFirstAidPath.addPath(firstAidPath);
    QCOMPARE(p_firstAidShape->shape(), strokeFirstAidPath);

    // FirstAidShape show pipes
    FirstAidShape *p_firstAid = dynamic_cast<FirstAidShape *>(p_firstAidShape);
    firstAidPath.clear();
    strokeFirstAidPath.clear();
    p_firstAid->setPipes(true);
    firstAidPath.addPolygon(firstAidPolygon);
    qreal sixtWidthFirstAid{firstAidRect.width() / 6}; // 5.0
    qreal pipeYFirstAid{firstAidRect.bottom() - sixtWidthFirstAid};
    QPointF rightPipeP1FirstAid{firstAidRect.right(), pipeYFirstAid};
    QPointF rightPipeP2FirstAid{firstAidRect.right() + sixtWidthFirstAid, pipeYFirstAid};
    // Right pipe
    firstAidPath.moveTo(rightPipeP1FirstAid);
    firstAidPath.lineTo(rightPipeP2FirstAid);
    QPointF rightConnectP1FirstAid{rightPipeP2FirstAid.x(), rightPipeP2FirstAid.y()
                                                                + sixtWidthFirstAid / 2};
    QPointF rightConnectP2FirstAid{rightPipeP2FirstAid.x(), rightPipeP2FirstAid.y()
                                                                - sixtWidthFirstAid / 2};
    // Right pipe connection
    firstAidPath.moveTo(rightConnectP1FirstAid);
    firstAidPath.lineTo(rightConnectP2FirstAid);
    QPointF leftPipeP1FirstAid{firstAidRect.left(), pipeYFirstAid};
    QPointF leftPipeP2FirstAid{firstAidRect.left() - sixtWidthFirstAid, pipeYFirstAid};
    // Left pipe
    firstAidPath.moveTo(leftPipeP1FirstAid);
    firstAidPath.lineTo(leftPipeP2FirstAid);
    QPointF leftConnectP1FirstAid{leftPipeP2FirstAid.x(), leftPipeP2FirstAid.y()
                                                              + sixtWidthFirstAid / 2};
    QPointF leftConnectP2FirstAid{leftPipeP2FirstAid.x(), leftPipeP2FirstAid.y()
                                                              - sixtWidthFirstAid / 2};
    // Right pipe connection
    firstAidPath.moveTo(leftConnectP1FirstAid);
    firstAidPath.lineTo(leftConnectP2FirstAid);
    strokeFirstAidPath = ps_firstAidShape.createStroke(firstAidPath);
    strokeFirstAidPath.addPath(firstAidPath);
    QCOMPARE(p_firstAid->shape(), strokeFirstAidPath);

    // FirstAidShape show collector
    firstAidPath.clear();
    strokeFirstAidPath.clear();
    p_firstAid->setPipes(false);
    p_firstAid->setCollector(true);
    firstAidPath.addPolygon(firstAidPolygon);
    qreal collectorXFirstAid{firstAidRect.center().x()};
    qreal collectorYFirstAid{firstAidRect.bottom() + sixtWidthFirstAid * 2};
    qreal leftCollectorPipeXFirstAid{collectorXFirstAid - sixtWidthFirstAid};
    QPointF leftRightCollectorPipeP1FirstAid{collectorXFirstAid, firstAidRect.bottom()};
    QPointF leftCollectorPipeP2FirstAid{leftCollectorPipeXFirstAid, collectorYFirstAid};
    //Left collector pipe
    firstAidPath.moveTo(leftRightCollectorPipeP1FirstAid);
    firstAidPath.lineTo(leftCollectorPipeP2FirstAid);
    qreal rightCollectorPipeXFirstAid{collectorXFirstAid + sixtWidthFirstAid};
    QPointF rightCollectorPipeP2FirstAid{rightCollectorPipeXFirstAid, collectorYFirstAid};
    //Right collector pipe
    firstAidPath.moveTo(leftRightCollectorPipeP1FirstAid);
    firstAidPath.lineTo(rightCollectorPipeP2FirstAid);
    QPointF leftCollectorConnectP1FirstAid{leftCollectorPipeXFirstAid - sixtWidthFirstAid / 2
                                           , collectorYFirstAid};
    QPointF leftCollectorConnectP2FirstAid{leftCollectorPipeXFirstAid + sixtWidthFirstAid / 2
                                           , collectorYFirstAid};
    //Left connector
    firstAidPath.moveTo(leftCollectorConnectP1FirstAid);
    firstAidPath.lineTo(leftCollectorConnectP2FirstAid);
    QPointF rightCollectorConnectP1FirstAid{rightCollectorPipeXFirstAid - sixtWidthFirstAid / 2
                                            , collectorYFirstAid};
    QPointF rightCollectorConnectP2FirstAid{rightCollectorPipeXFirstAid + sixtWidthFirstAid / 2
                                            , collectorYFirstAid};
    //Right connector
    firstAidPath.moveTo(rightCollectorConnectP1FirstAid);
    firstAidPath.lineTo(rightCollectorConnectP2FirstAid);
    strokeFirstAidPath = ps_firstAidShape.createStroke(firstAidPath);
    strokeFirstAidPath.addPath(firstAidPath);
    QCOMPARE(p_firstAid->shape(), strokeFirstAidPath);

    p_firstAid = nullptr;
    TechnicsShape::TechnicsShapeDeleter::cleanup(p_firstAidShape);

    // EmergencyShape
    TechnicsShape *p_emergencyShape = TechnicsShape::createTechnicsShape(TechnicsShape::Emergency);
    QPainterPathStroker ps_emergencyShape;
    ps_emergencyShape.setWidth(p_emergencyShape->pen().widthF());
    QRectF emergencyRect{p_emergencyShape->rect()};
    qreal frontTabEmergency{emergencyRect.height() / 3};
    QPointF frontCenterEmergency{emergencyRect.center().x(), emergencyRect.top()}; // 0.0, -37.5
    QPointF frontRightEmergency{emergencyRect.right(), emergencyRect.top() + frontTabEmergency}; // 15.0, -12.5
    QPointF frontLeftEmergency{emergencyRect.left(), emergencyRect.top() + frontTabEmergency}; // -15.0, -12.5
    QPointF bottomRightEmergency{emergencyRect.bottomRight()}; // 15.0, 37.5
    QPointF bottomLeftEmergency{emergencyRect.bottomLeft()}; // -15.0, 37.5
    QPolygonF emergencyPolygon;
    emergencyPolygon << frontCenterEmergency << frontRightEmergency << bottomRightEmergency
                    << bottomLeftEmergency << frontLeftEmergency << frontCenterEmergency;
    QPainterPath emergencyPath;
    emergencyPath.addPolygon(emergencyPolygon);
    QPainterPath strokeEmergencyPath = ps_emergencyShape.createStroke(emergencyPath);
    strokeEmergencyPath.addPath(emergencyPath);
    QCOMPARE(p_emergencyShape->shape(), strokeEmergencyPath);

    // EmergencyShape show pipes
    EmergencyShape *p_emergency = dynamic_cast<EmergencyShape *>(p_emergencyShape);
    emergencyPath.clear();
    strokeEmergencyPath.clear();
    p_emergency->setPipes(true);
    emergencyPath.addPolygon(emergencyPolygon);
    qreal sixtWidthEmergency{emergencyRect.width() / 6}; // 5.0
    qreal pipeYEmergency{emergencyRect.bottom() - sixtWidthEmergency};
    QPointF rightPipeP1Emergency{emergencyRect.right(), pipeYEmergency};
    QPointF rightPipeP2Emergency{emergencyRect.right() + sixtWidthEmergency, pipeYEmergency};
    // Right pipe
    emergencyPath.moveTo(rightPipeP1Emergency);
    emergencyPath.lineTo(rightPipeP2Emergency);
    QPointF rightConnectP1Emergency{rightPipeP2Emergency.x(), rightPipeP2Emergency.y()
                                                                + sixtWidthEmergency / 2};
    QPointF rightConnectP2Emergency{rightPipeP2Emergency.x(), rightPipeP2Emergency.y()
                                                                - sixtWidthEmergency / 2};
    // Right pipe connection
    emergencyPath.moveTo(rightConnectP1Emergency);
    emergencyPath.lineTo(rightConnectP2Emergency);
    QPointF leftPipeP1Emergency{emergencyRect.left(), pipeYEmergency};
    QPointF leftPipeP2Emergency{emergencyRect.left() - sixtWidthEmergency, pipeYEmergency};
    // Left pipe
    emergencyPath.moveTo(leftPipeP1Emergency);
    emergencyPath.lineTo(leftPipeP2Emergency);
    QPointF leftConnectP1Emergency{leftPipeP2Emergency.x(), leftPipeP2Emergency.y()
                                                              + sixtWidthEmergency / 2};
    QPointF leftConnectP2emergency{leftPipeP2Emergency.x(), leftPipeP2Emergency.y()
                                                              - sixtWidthEmergency / 2};
    // Right pipe connection
    emergencyPath.moveTo(leftConnectP1Emergency);
    emergencyPath.lineTo(leftConnectP2emergency);
    strokeEmergencyPath = ps_emergencyShape.createStroke(emergencyPath);
    strokeEmergencyPath.addPath(emergencyPath);
    QCOMPARE(p_emergency->shape(), strokeEmergencyPath);

    // EmergencyShape show collector
    emergencyPath.clear();
    strokeEmergencyPath.clear();
    p_emergency->setPipes(false);
    p_emergency->setCollector(true);
    emergencyPath.addPolygon(emergencyPolygon);
    qreal collectorXEmergency{emergencyRect.center().x()};
    qreal collectorYEmergency{emergencyRect.bottom() + sixtWidthEmergency * 2};
    qreal leftCollectorPipeXEmergency{collectorXEmergency - sixtWidthEmergency};
    QPointF leftRightCollectorPipeP1Emergency{collectorXEmergency, emergencyRect.bottom()};
    QPointF leftCollectorPipeP2Emergency{leftCollectorPipeXEmergency, collectorYEmergency};
    //Left collector pipe
    emergencyPath.moveTo(leftRightCollectorPipeP1Emergency);
    emergencyPath.lineTo(leftCollectorPipeP2Emergency);
    qreal rightCollectorPipeXEmergency{collectorXEmergency + sixtWidthEmergency};
    QPointF rightCollectorPipeP2Emergency{rightCollectorPipeXEmergency, collectorYEmergency};
    //Right collector pipe
    emergencyPath.moveTo(leftRightCollectorPipeP1Emergency);
    emergencyPath.lineTo(rightCollectorPipeP2Emergency);
    QPointF leftCollectorConnectP1Emergency{leftCollectorPipeXEmergency - sixtWidthEmergency / 2
                                           , collectorYEmergency};
    QPointF leftCollectorConnectP2Emergency{leftCollectorPipeXEmergency + sixtWidthEmergency / 2
                                           , collectorYEmergency};
    //Left connector
    emergencyPath.moveTo(leftCollectorConnectP1Emergency);
    emergencyPath.lineTo(leftCollectorConnectP2Emergency);
    QPointF rightCollectorConnectP1Emergency{rightCollectorPipeXEmergency - sixtWidthEmergency / 2
                                            , collectorYEmergency};
    QPointF rightCollectorConnectP2Emergency{rightCollectorPipeXEmergency + sixtWidthEmergency / 2
                                            , collectorYEmergency};
    //Right connector
    emergencyPath.moveTo(rightCollectorConnectP1Emergency);
    emergencyPath.lineTo(rightCollectorConnectP2Emergency);
    strokeEmergencyPath = ps_emergencyShape.createStroke(emergencyPath);
    strokeEmergencyPath.addPath(emergencyPath);
    QCOMPARE(p_emergency->shape(), strokeEmergencyPath);

    p_emergency = nullptr;
    TechnicsShape::TechnicsShapeDeleter::cleanup(p_emergencyShape);

    // AutoLadderShape
    TechnicsShape *p_autoLadderShape = TechnicsShape::createTechnicsShape(TechnicsShape::AutoLadder);
    QPainterPathStroker ps_autoLadderShape;
    ps_autoLadderShape.setWidth(p_autoLadderShape->pen().widthF());
    QRectF autoLadderRect{p_autoLadderShape->rect()};
    qreal frontTabAutoLadder{autoLadderRect.height() / 3};
    QPointF frontCenterAutoLadder{autoLadderRect.center().x(), autoLadderRect.top()}; // 0.0, -37.5
    QPointF frontRightAutoLadder{autoLadderRect.right(), autoLadderRect.top() + frontTabAutoLadder}; // 15.0, -12.5
    QPointF frontLeftAutoLadder{autoLadderRect.left(), autoLadderRect.top() + frontTabAutoLadder}; // -15.0, -12.5
    QPointF bottomRightAutoLadder{autoLadderRect.bottomRight()}; // 15.0, 37.5
    QPointF bottomLeftAutoLadder{autoLadderRect.bottomLeft()}; // -15.0, 37.5
    QPolygonF autoLadderPolygon;
    autoLadderPolygon << frontCenterAutoLadder << frontRightAutoLadder << bottomRightAutoLadder
                      << bottomLeftAutoLadder << frontLeftAutoLadder << frontCenterAutoLadder;
    QPainterPath autoLadderPath;
    autoLadderPath.addPolygon(autoLadderPolygon);
    QPainterPath strokeAutoLadderPath = ps_autoLadderShape.createStroke(autoLadderPath);
    strokeAutoLadderPath.addPath(autoLadderPath);
    QCOMPARE(p_autoLadderShape->shape(), strokeAutoLadderPath);
    TechnicsShape::TechnicsShapeDeleter::cleanup(p_autoLadderShape);

    // CrankLiftShape
    TechnicsShape *p_crankLiftShape = TechnicsShape::createTechnicsShape(TechnicsShape::CrankLift);
    QPainterPathStroker ps_crankLiftShape;
    ps_crankLiftShape.setWidth(p_crankLiftShape->pen().widthF());
    QRectF crankLiftRect{p_crankLiftShape->rect()};
    qreal frontTabCrankLift{crankLiftRect.height() / 3};
    QPointF frontCenterCrankLift{crankLiftRect.center().x(), crankLiftRect.top()}; // 0.0, -37.5
    QPointF frontRightCrankLift{crankLiftRect.right(), crankLiftRect.top() + frontTabCrankLift}; // 15.0, -12.5
    QPointF frontLeftCrankLift{crankLiftRect.left(), crankLiftRect.top() + frontTabCrankLift}; // -15.0, -12.5
    QPointF bottomRightCrankLift{crankLiftRect.bottomRight()}; // 15.0, 37.5
    QPointF bottomLeftCrankLift{crankLiftRect.bottomLeft()}; // -15.0, 37.5
    QPolygonF crankLiftPolygon;
    crankLiftPolygon << frontCenterCrankLift << frontRightCrankLift << bottomRightCrankLift
                      << bottomLeftCrankLift << frontLeftCrankLift << frontCenterCrankLift;
    QPainterPath crankLiftPath;
    crankLiftPath.addPolygon(crankLiftPolygon);
    QPainterPath strokeCrankLiftPath = ps_crankLiftShape.createStroke(crankLiftPath);
    strokeCrankLiftPath.addPath(crankLiftPath);
    QCOMPARE(p_crankLiftShape->shape(), strokeCrankLiftPath);
    TechnicsShape::TechnicsShapeDeleter::cleanup(p_crankLiftShape);

    // TelescopicLiftShape
    TechnicsShape *p_telescopicLiftShape = TechnicsShape::createTechnicsShape(TechnicsShape::TelescopicLift);
    QPainterPathStroker ps_telescopicLiftShape;
    ps_telescopicLiftShape.setWidth(p_telescopicLiftShape->pen().widthF());
    QRectF telescopicLiftRect{p_telescopicLiftShape->rect()};
    qreal frontTabTelescopicLift{telescopicLiftRect.height() / 3};
    QPointF frontCenterTelescopicLift{telescopicLiftRect.center().x(), telescopicLiftRect.top()}; // 0.0, -37.5
    QPointF frontRightTelescopicLift{telescopicLiftRect.right(), telescopicLiftRect.top()
                                                                     + frontTabTelescopicLift}; // 15.0, -12.5
    QPointF frontLeftTelescopicLift{telescopicLiftRect.left(), telescopicLiftRect.top()
                                                                   + frontTabTelescopicLift}; // -15.0, -12.5
    QPointF bottomRightTelescopicLift{telescopicLiftRect.bottomRight()}; // 15.0, 37.5
    QPointF bottomLeftTelescopicLift{telescopicLiftRect.bottomLeft()}; // -15.0, 37.5
    QPolygonF telescopicLiftPolygon;
    telescopicLiftPolygon << frontCenterTelescopicLift << frontRightTelescopicLift
                          << bottomRightTelescopicLift << bottomLeftTelescopicLift
                          << frontLeftTelescopicLift << frontCenterTelescopicLift;
    QPainterPath telescopicLiftPath;
    telescopicLiftPath.addPolygon(telescopicLiftPolygon);
    QPainterPath strokeTelescopicLiftPath = ps_telescopicLiftShape.createStroke(telescopicLiftPath);
    strokeTelescopicLiftPath.addPath(telescopicLiftPath);
    QCOMPARE(p_telescopicLiftShape->shape(), strokeTelescopicLiftPath);
    TechnicsShape::TechnicsShapeDeleter::cleanup(p_telescopicLiftShape);

    // HoseCarShape
    TechnicsShape *p_hoseCarShape = TechnicsShape::createTechnicsShape(TechnicsShape::HoseCar);
    QPainterPathStroker ps_hoseCarShape;
    ps_hoseCarShape.setWidth(p_hoseCarShape->pen().widthF());
    QRectF hoseCarRect{p_hoseCarShape->rect()};
    qreal frontTabHoseCar{hoseCarRect.height() / 3};
    QPointF frontCenterHoseCar{hoseCarRect.center().x(), hoseCarRect.top()}; // 0.0, -37.5
    QPointF frontRightHoseCar{hoseCarRect.right(), hoseCarRect.top() + frontTabHoseCar}; // 15.0, -12.5
    QPointF frontLeftHoseCar{hoseCarRect.left(), hoseCarRect.top() + frontTabHoseCar}; // -15.0, -12.5
    QPointF bottomRightHoseCar{hoseCarRect.bottomRight()}; // 15.0, 37.5
    QPointF bottomLeftHoseCar{hoseCarRect.bottomLeft()}; // -15.0, 37.5
    QPolygonF hoseCarPolygon;
    hoseCarPolygon << frontCenterHoseCar << frontRightHoseCar << bottomRightHoseCar
                   << bottomLeftHoseCar << frontLeftHoseCar << frontCenterHoseCar;
    QPainterPath hoseCarPath;
    hoseCarPath.addPolygon(hoseCarPolygon);
    QPainterPath strokeHoseCarPath = ps_hoseCarShape.createStroke(hoseCarPath);
    strokeHoseCarPath.addPath(hoseCarPath);
    QCOMPARE(p_hoseCarShape->shape(), strokeHoseCarPath);
    TechnicsShape::TechnicsShapeDeleter::cleanup(p_hoseCarShape);

    // CommShape
    TechnicsShape *p_commShape = TechnicsShape::createTechnicsShape(TechnicsShape::Comm);
    QPainterPathStroker ps_commShape;
    ps_commShape.setWidth(p_commShape->pen().widthF());
    QRectF commRect{p_commShape->rect()};
    qreal frontTabComm{commRect.height() / 3};
    QPointF frontCenterComm{commRect.center().x(), commRect.top()}; // 0.0, -37.5
    QPointF frontRightComm{commRect.right(), commRect.top() + frontTabComm}; // 15.0, -12.5
    QPointF frontLeftComm{commRect.left(), commRect.top() + frontTabComm}; // -15.0, -12.5
    QPointF bottomRightComm{commRect.bottomRight()}; // 15.0, 37.5
    QPointF bottomLeftComm{commRect.bottomLeft()}; // -15.0, 37.5
    QPolygonF commPolygon;
    commPolygon << frontCenterComm << frontRightComm << bottomRightComm << bottomLeftComm
                << frontLeftComm << frontCenterComm;
    QPainterPath commPath;
    commPath.addPolygon(commPolygon);
    QPainterPath strokeCommPath = ps_commShape.createStroke(commPath);
    strokeCommPath.addPath(commPath);
    QCOMPARE(p_commShape->shape(), strokeCommPath);
    TechnicsShape::TechnicsShapeDeleter::cleanup(p_commShape);
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

    // FirstAidShape
    TechnicsShape *p_firstAidShape = TechnicsShape::createTechnicsShape(TechnicsShape::FirstAid);
    QPixmap firstAidImage{p_firstAidShape->image()};
    QVERIFY2(!firstAidImage.isNull(), "FirstAidShape::image() returned a null pixmap");
    QCOMPARE(firstAidImage.width(), p_firstAidShape->boundingRect().width());
    QCOMPARE(firstAidImage.height(), p_firstAidShape->boundingRect().height());
    TechnicsShape::TechnicsShapeDeleter::cleanup(p_firstAidShape);

    // EmergencyShape
    TechnicsShape *p_emergencyShape = TechnicsShape::createTechnicsShape(TechnicsShape::Emergency);
    QPixmap emergencyImage{p_emergencyShape->image()};
    QVERIFY2(!emergencyImage.isNull(), "emergencyShape::image() returned a null pixmap");
    QCOMPARE(emergencyImage.width(), p_emergencyShape->boundingRect().width());
    QCOMPARE(emergencyImage.height(), p_emergencyShape->boundingRect().height());
    TechnicsShape::TechnicsShapeDeleter::cleanup(p_emergencyShape);

    // AutoLadderShape
    TechnicsShape *p_autoLadderShape = TechnicsShape::createTechnicsShape(TechnicsShape::AutoLadder);
    QPixmap autoLadderImage{p_autoLadderShape->image()};
    QVERIFY2(!autoLadderImage.isNull(), "autoLadderShape::image() returned a null pixmap");
    QCOMPARE(autoLadderImage.width(), p_autoLadderShape->boundingRect().width());
    QCOMPARE(autoLadderImage.height(), p_autoLadderShape->boundingRect().height());
    TechnicsShape::TechnicsShapeDeleter::cleanup(p_autoLadderShape);

    // CrankLiftShape
    TechnicsShape *p_crankLiftShape = TechnicsShape::createTechnicsShape(TechnicsShape::CrankLift);
    QPixmap crankLiftImage{p_crankLiftShape->image()};
    QVERIFY2(!crankLiftImage.isNull(), "crankLiftShape::image() returned a null pixmap");
    QCOMPARE(crankLiftImage.width(), p_crankLiftShape->boundingRect().width());
    QCOMPARE(crankLiftImage.height(), p_crankLiftShape->boundingRect().height());
    TechnicsShape::TechnicsShapeDeleter::cleanup(p_crankLiftShape);

    // TelescopicLiftShape
    TechnicsShape *p_telescopicLiftShape = TechnicsShape::createTechnicsShape(TechnicsShape::TelescopicLift);
    QPixmap telescopicLiftImage{p_telescopicLiftShape->image()};
    QVERIFY2(!telescopicLiftImage.isNull(), "telescopicLiftShape::image() returned a null pixmap");
    QCOMPARE(telescopicLiftImage.width(), p_telescopicLiftShape->boundingRect().width());
    QCOMPARE(telescopicLiftImage.height(), p_telescopicLiftShape->boundingRect().height());
    TechnicsShape::TechnicsShapeDeleter::cleanup(p_telescopicLiftShape);

    // HoseCarShape
    TechnicsShape *p_hoseCarShape = TechnicsShape::createTechnicsShape(TechnicsShape::HoseCar);
    QPixmap hoseCarImage{p_hoseCarShape->image()};
    QVERIFY2(!hoseCarImage.isNull(), "hoseCarShape::image() returned a null pixmap");
    QCOMPARE(hoseCarImage.width(), p_hoseCarShape->boundingRect().width());
    QCOMPARE(hoseCarImage.height(), p_hoseCarShape->boundingRect().height());
    TechnicsShape::TechnicsShapeDeleter::cleanup(p_hoseCarShape);

    // CommShape
    TechnicsShape *p_commShape = TechnicsShape::createTechnicsShape(TechnicsShape::Comm);
    QPixmap commImage{p_commShape->image()};
    QVERIFY2(!commImage.isNull(), "commShape::image() returned a null pixmap");
    QCOMPARE(commImage.width(), p_commShape->boundingRect().width());
    QCOMPARE(commImage.height(), p_commShape->boundingRect().height());
    TechnicsShape::TechnicsShapeDeleter::cleanup(p_commShape);
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

    // FirstAidShape
    TechnicsShape *p_firstAidShape = TechnicsShape::createTechnicsShape(TechnicsShape::FirstAid);
    p_firstAidShape->setRect(rect);
    QCOMPARE(p_firstAidShape->rect(), rect);
    TechnicsShape::TechnicsShapeDeleter::cleanup(p_firstAidShape);

    // EmergencyShape
    TechnicsShape *p_emergencyShape = TechnicsShape::createTechnicsShape(TechnicsShape::Emergency);
    p_emergencyShape->setRect(rect);
    QCOMPARE(p_emergencyShape->rect(), rect);
    TechnicsShape::TechnicsShapeDeleter::cleanup(p_emergencyShape);

    // AutoLadderShape
    TechnicsShape *p_autoLadderShape = TechnicsShape::createTechnicsShape(TechnicsShape::AutoLadder);
    p_autoLadderShape->setRect(rect);
    QCOMPARE(p_autoLadderShape->rect(), rect);
    TechnicsShape::TechnicsShapeDeleter::cleanup(p_autoLadderShape);

    // CrankLIftShape
    TechnicsShape *p_crankLiftShape = TechnicsShape::createTechnicsShape(TechnicsShape::CrankLift);
    p_crankLiftShape->setRect(rect);
    QCOMPARE(p_crankLiftShape->rect(), rect);
    TechnicsShape::TechnicsShapeDeleter::cleanup(p_crankLiftShape);

    // TelescopicLIftShape
    TechnicsShape *p_telescopicLiftShape = TechnicsShape::createTechnicsShape(TechnicsShape::TelescopicLift);
    p_telescopicLiftShape->setRect(rect);
    QCOMPARE(p_telescopicLiftShape->rect(), rect);
    TechnicsShape::TechnicsShapeDeleter::cleanup(p_telescopicLiftShape);

    // HoseCarShape
    TechnicsShape *p_hoseCarShape = TechnicsShape::createTechnicsShape(TechnicsShape::HoseCar);
    p_hoseCarShape->setRect(rect);
    QCOMPARE(p_hoseCarShape->rect(), rect);
    TechnicsShape::TechnicsShapeDeleter::cleanup(p_hoseCarShape);

    // CommShape
    TechnicsShape *p_commShape = TechnicsShape::createTechnicsShape(TechnicsShape::Comm);
    p_commShape->setRect(rect);
    QCOMPARE(p_commShape->rect(), rect);
    TechnicsShape::TechnicsShapeDeleter::cleanup(p_commShape);
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

    // FirstAidShape
    TechnicsShape *p_firstAidShape = TechnicsShape::createTechnicsShape(TechnicsShape::FirstAid);
    p_firstAidShape->setHeight(height);
    QCOMPARE(p_firstAidShape->height(), height);
    TechnicsShape::TechnicsShapeDeleter::cleanup(p_firstAidShape);

    // EmergencyShape
    TechnicsShape *p_emergencyShape = TechnicsShape::createTechnicsShape(TechnicsShape::Emergency);
    p_emergencyShape->setHeight(height);
    QCOMPARE(p_emergencyShape->height(), height);
    TechnicsShape::TechnicsShapeDeleter::cleanup(p_emergencyShape);

    // AutoLadderShape
    TechnicsShape *p_autoLadderShape = TechnicsShape::createTechnicsShape(TechnicsShape::AutoLadder);
    p_autoLadderShape->setHeight(height);
    QCOMPARE(p_autoLadderShape->height(), height);
    TechnicsShape::TechnicsShapeDeleter::cleanup(p_autoLadderShape);

    // CrankLiftShape
    TechnicsShape *p_crankLiftShape = TechnicsShape::createTechnicsShape(TechnicsShape::CrankLift);
    p_crankLiftShape->setHeight(height);
    QCOMPARE(p_crankLiftShape->height(), height);
    TechnicsShape::TechnicsShapeDeleter::cleanup(p_crankLiftShape);

    // TelescopicLiftShape
    TechnicsShape *p_telescopicLiftShape = TechnicsShape::createTechnicsShape(TechnicsShape::TelescopicLift);
    p_telescopicLiftShape->setHeight(height);
    QCOMPARE(p_telescopicLiftShape->height(), height);
    TechnicsShape::TechnicsShapeDeleter::cleanup(p_telescopicLiftShape);

    // HoseCarShape
    TechnicsShape *p_hoseCarShape = TechnicsShape::createTechnicsShape(TechnicsShape::HoseCar);
    p_hoseCarShape->setHeight(height);
    QCOMPARE(p_hoseCarShape->height(), height);
    TechnicsShape::TechnicsShapeDeleter::cleanup(p_hoseCarShape);

    // CommShape
    TechnicsShape *p_commShape = TechnicsShape::createTechnicsShape(TechnicsShape::Comm);
    p_commShape->setHeight(height);
    QCOMPARE(p_commShape->height(), height);
    TechnicsShape::TechnicsShapeDeleter::cleanup(p_commShape);
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

    // FirstAidShape
    TechnicsShape *p_firstAidShape = TechnicsShape::createTechnicsShape(TechnicsShape::FirstAid);
    p_firstAidShape->setText(text);
    QCOMPARE(p_firstAidShape->text(), text);
    TechnicsShape::TechnicsShapeDeleter::cleanup(p_firstAidShape);

    // EmergencyShape
    TechnicsShape *p_emergencyShape = TechnicsShape::createTechnicsShape(TechnicsShape::Emergency);
    p_emergencyShape->setText(text);
    QCOMPARE(p_emergencyShape->text(), text);
    TechnicsShape::TechnicsShapeDeleter::cleanup(p_emergencyShape);

    // AutoLadderShape
    TechnicsShape *p_autoLadderShape = TechnicsShape::createTechnicsShape(TechnicsShape::AutoLadder);
    p_autoLadderShape->setText(text);
    QCOMPARE(p_autoLadderShape->text(), text);
    TechnicsShape::TechnicsShapeDeleter::cleanup(p_autoLadderShape);

    // CrankLIftShape
    TechnicsShape *p_crankLIftShape = TechnicsShape::createTechnicsShape(TechnicsShape::CrankLift);
    p_crankLIftShape->setText(text);
    QCOMPARE(p_crankLIftShape->text(), text);
    TechnicsShape::TechnicsShapeDeleter::cleanup(p_crankLIftShape);

    // TelescopicLIftShape
    TechnicsShape *p_telescopicLiftShape = TechnicsShape::createTechnicsShape(TechnicsShape::TelescopicLift);
    p_telescopicLiftShape->setText(text);
    QCOMPARE(p_telescopicLiftShape->text(), text);
    TechnicsShape::TechnicsShapeDeleter::cleanup(p_telescopicLiftShape);

    // HoseCarShape
    TechnicsShape *p_hoseCarShape = TechnicsShape::createTechnicsShape(TechnicsShape::HoseCar);
    p_hoseCarShape->setText(text);
    QCOMPARE(p_hoseCarShape->text(), text);
    TechnicsShape::TechnicsShapeDeleter::cleanup(p_hoseCarShape);

    // CommShape
    TechnicsShape *p_commShape = TechnicsShape::createTechnicsShape(TechnicsShape::Comm);
    p_commShape->setText(text);
    QCOMPARE(p_commShape->text(), text);
    TechnicsShape::TechnicsShapeDeleter::cleanup(p_commShape);
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
    p_pumpHose = nullptr;
    TechnicsShape::TechnicsShapeDeleter::cleanup(p_pumpHoseShape);

    //FirstAidShape
    TechnicsShape *p_firstAidShape = TechnicsShape::createTechnicsShape(TechnicsShape::FirstAid);
    FirstAidShape *p_firstAid = dynamic_cast<FirstAidShape *>(p_firstAidShape);
    QCOMPARE(p_firstAid->pipes(), false);
    p_firstAid->setPipes(true);
    QCOMPARE(p_firstAid->pipes(), true);
    p_firstAid->setPipes(false);
    QCOMPARE(p_firstAid->pipes(), false);
    p_firstAid = nullptr;
    TechnicsShape::TechnicsShapeDeleter::cleanup(p_firstAidShape);

    //EmergencyShape
    TechnicsShape *p_emergencyShape = TechnicsShape::createTechnicsShape(TechnicsShape::Emergency);
    EmergencyShape *p_emergency = dynamic_cast<EmergencyShape *>(p_emergencyShape);
    QCOMPARE(p_emergency->pipes(), false);
    p_emergency->setPipes(true);
    QCOMPARE(p_emergency->pipes(), true);
    p_emergency->setPipes(false);
    QCOMPARE(p_emergency->pipes(), false);
    p_emergency = nullptr;
    TechnicsShape::TechnicsShapeDeleter::cleanup(p_emergencyShape);
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
    PumpHoseShape *p_pumpHose = dynamic_cast<PumpHoseShape *>(p_pumpHoseShape);
    QCOMPARE(p_pumpHose->collector(), false);
    p_pumpHose->setCollector(true);
    QCOMPARE(p_pumpHose->collector(), true);
    p_pumpHose->setCollector(false);
    QCOMPARE(p_pumpHose->collector(), false);
    p_pumpHose = nullptr;
    TechnicsShape::TechnicsShapeDeleter::cleanup(p_pumpHoseShape);

    //FirstAidShape
    TechnicsShape *p_firstAidShape = TechnicsShape::createTechnicsShape(TechnicsShape::FirstAid);
    FirstAidShape *p_firstAid = dynamic_cast<FirstAidShape *>(p_firstAidShape);
    QCOMPARE(p_firstAid->collector(), false);
    p_firstAid->setCollector(true);
    QCOMPARE(p_firstAid->collector(), true);
    p_firstAid->setCollector(false);
    QCOMPARE(p_firstAid->collector(), false);
    p_firstAid = nullptr;
    TechnicsShape::TechnicsShapeDeleter::cleanup(p_firstAidShape);

    //EmergencyShape
    TechnicsShape *p_emergencyShape = TechnicsShape::createTechnicsShape(TechnicsShape::Emergency);
    EmergencyShape *p_emergency = dynamic_cast<EmergencyShape *>(p_emergencyShape);
    QCOMPARE(p_emergency->collector(), false);
    p_emergency->setCollector(true);
    QCOMPARE(p_emergency->collector(), true);
    p_emergency->setCollector(false);
    QCOMPARE(p_emergency->collector(), false);
    p_emergency = nullptr;
    TechnicsShape::TechnicsShapeDeleter::cleanup(p_emergencyShape);
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

    // FirstAidShape
    ContextMenuTester *p_firstAidContextMenu = new ContextMenuTester();

    TechnicsShape *p_firstAidShape = TechnicsShape::createTechnicsShape(TechnicsShape::FirstAid);
    p_firstAidShape->setMenu(p_firstAidContextMenu);
    scene.addItem(p_firstAidShape);

    mousePressEvent.setScenePos(p_firstAidShape->pos());
    QApplication::sendEvent(&scene, &mousePressEvent);
    QVERIFY(mousePressEvent.isAccepted());

    p_firstAidShape->setSelected(true);
    QSignalSpy firstAidContextMenuSpy(p_firstAidShape->menu(), &QMenu::aboutToShow);
    QCOMPARE(firstAidContextMenuSpy.count(), 0);

    QList<QAction *> firstAidMenuActions{p_firstAidShape->menu()->actions()};
    QCOMPARE(firstAidMenuActions.size(), 1);
    firstAidMenuActions.clear();

    QTest::mouseClick(view.viewport(), Qt::RightButton, Qt::NoModifier
                      , view.mapFromScene(p_firstAidShape->boundingRect().center()));
    firstAidMenuActions = p_firstAidShape->menu()->actions();
    QCOMPARE(firstAidMenuActions.size(), 1);
    QCOMPARE(firstAidContextMenuSpy.count(), 1);

    scene.removeItem(p_firstAidShape);
    delete p_firstAidContextMenu;
    TechnicsShape::TechnicsShapeDeleter::cleanup(p_firstAidShape);

    // EmergencyShape
    ContextMenuTester *p_emergencyContextMenu = new ContextMenuTester();

    TechnicsShape *p_emergencyShape = TechnicsShape::createTechnicsShape(TechnicsShape::Emergency);
    p_emergencyShape->setMenu(p_emergencyContextMenu);
    scene.addItem(p_emergencyShape);

    mousePressEvent.setScenePos(p_emergencyShape->pos());
    QApplication::sendEvent(&scene, &mousePressEvent);
    QVERIFY(mousePressEvent.isAccepted());

    p_emergencyShape->setSelected(true);
    QSignalSpy emergencyContextMenuSpy(p_emergencyShape->menu(), &QMenu::aboutToShow);
    QCOMPARE(emergencyContextMenuSpy.count(), 0);

    QList<QAction *> emergencyMenuActions{p_emergencyShape->menu()->actions()};
    QCOMPARE(emergencyMenuActions.size(), 1);
    emergencyMenuActions.clear();

    QTest::mouseClick(view.viewport(), Qt::RightButton, Qt::NoModifier
                      , view.mapFromScene(p_emergencyShape->boundingRect().center()));
    emergencyMenuActions = p_emergencyShape->menu()->actions();
    QCOMPARE(emergencyMenuActions.size(), 1);
    QCOMPARE(emergencyContextMenuSpy.count(), 1);

    scene.removeItem(p_emergencyShape);
    delete p_emergencyContextMenu;
    TechnicsShape::TechnicsShapeDeleter::cleanup(p_emergencyShape);

    // AutoLadderShape
    ContextMenuTester *p_autoLadderContextMenu = new ContextMenuTester();

    TechnicsShape *p_autoLadderShape = TechnicsShape::createTechnicsShape(TechnicsShape::AutoLadder);
    p_autoLadderShape->setMenu(p_autoLadderContextMenu);
    scene.addItem(p_autoLadderShape);

    mousePressEvent.setScenePos(p_autoLadderShape->pos());
    QApplication::sendEvent(&scene, &mousePressEvent);
    QVERIFY(mousePressEvent.isAccepted());

    p_autoLadderShape->setSelected(true);
    QSignalSpy autoLadderContextMenuSpy(p_autoLadderShape->menu(), &QMenu::aboutToShow);
    QCOMPARE(autoLadderContextMenuSpy.count(), 0);

    QList<QAction *> autoLadderMenuActions{p_autoLadderShape->menu()->actions()};
    QCOMPARE(autoLadderMenuActions.size(), 1);
    autoLadderMenuActions.clear();

    QTest::mouseClick(view.viewport(), Qt::RightButton, Qt::NoModifier
                      , view.mapFromScene(p_autoLadderShape->boundingRect().center()));
    autoLadderMenuActions = p_autoLadderShape->menu()->actions();
    QCOMPARE(autoLadderMenuActions.size(), 1);
    QCOMPARE(autoLadderContextMenuSpy.count(), 1);

    scene.removeItem(p_autoLadderShape);
    delete p_autoLadderContextMenu;
    TechnicsShape::TechnicsShapeDeleter::cleanup(p_autoLadderShape);

    // CrankLiftShape
    ContextMenuTester *p_crankLiftContextMenu = new ContextMenuTester();

    TechnicsShape *p_crankLiftShape = TechnicsShape::createTechnicsShape(TechnicsShape::CrankLift);
    p_crankLiftShape->setMenu(p_crankLiftContextMenu);
    scene.addItem(p_crankLiftShape);

    mousePressEvent.setScenePos(p_crankLiftShape->pos());
    QApplication::sendEvent(&scene, &mousePressEvent);
    QVERIFY(mousePressEvent.isAccepted());

    p_crankLiftShape->setSelected(true);
    QSignalSpy crankLiftContextMenuSpy(p_crankLiftShape->menu(), &QMenu::aboutToShow);
    QCOMPARE(crankLiftContextMenuSpy.count(), 0);

    QList<QAction *> crankLiftMenuActions{p_crankLiftShape->menu()->actions()};
    QCOMPARE(crankLiftMenuActions.size(), 1);
    crankLiftMenuActions.clear();

    QTest::mouseClick(view.viewport(), Qt::RightButton, Qt::NoModifier
                      , view.mapFromScene(p_crankLiftShape->boundingRect().center()));
    crankLiftMenuActions = p_crankLiftShape->menu()->actions();
    QCOMPARE(crankLiftMenuActions.size(), 1);
    QCOMPARE(crankLiftContextMenuSpy.count(), 1);

    scene.removeItem(p_crankLiftShape);
    delete p_crankLiftContextMenu;
    TechnicsShape::TechnicsShapeDeleter::cleanup(p_crankLiftShape);

    // TelescopicLiftShape
    ContextMenuTester *p_telescopicLiftContextMenu = new ContextMenuTester();

    TechnicsShape *p_telescopicLiftShape = TechnicsShape::createTechnicsShape(TechnicsShape::TelescopicLift);
    p_telescopicLiftShape->setMenu(p_telescopicLiftContextMenu);
    scene.addItem(p_telescopicLiftShape);

    mousePressEvent.setScenePos(p_telescopicLiftShape->pos());
    QApplication::sendEvent(&scene, &mousePressEvent);
    QVERIFY(mousePressEvent.isAccepted());

    p_telescopicLiftShape->setSelected(true);
    QSignalSpy telescopicLiftContextMenuSpy(p_telescopicLiftShape->menu(), &QMenu::aboutToShow);
    QCOMPARE(telescopicLiftContextMenuSpy.count(), 0);

    QList<QAction *> telescopicLiftMenuActions{p_telescopicLiftShape->menu()->actions()};
    QCOMPARE(telescopicLiftMenuActions.size(), 1);
    telescopicLiftMenuActions.clear();

    QTest::mouseClick(view.viewport(), Qt::RightButton, Qt::NoModifier
                      , view.mapFromScene(p_telescopicLiftShape->boundingRect().center()));
    telescopicLiftMenuActions = p_telescopicLiftShape->menu()->actions();
    QCOMPARE(telescopicLiftMenuActions.size(), 1);
    QCOMPARE(telescopicLiftContextMenuSpy.count(), 1);

    scene.removeItem(p_telescopicLiftShape);
    delete p_telescopicLiftContextMenu;
    TechnicsShape::TechnicsShapeDeleter::cleanup(p_telescopicLiftShape);

    // HoseCarShape
    ContextMenuTester *p_hoseCarContextMenu = new ContextMenuTester();

    TechnicsShape *p_hoseCarShape = TechnicsShape::createTechnicsShape(TechnicsShape::HoseCar);
    p_hoseCarShape->setMenu(p_hoseCarContextMenu);
    scene.addItem(p_hoseCarShape);

    mousePressEvent.setScenePos(p_hoseCarShape->pos());
    QApplication::sendEvent(&scene, &mousePressEvent);
    QVERIFY(mousePressEvent.isAccepted());

    p_hoseCarShape->setSelected(true);
    QSignalSpy hoseCarContextMenuSpy(p_hoseCarShape->menu(), &QMenu::aboutToShow);
    QCOMPARE(hoseCarContextMenuSpy.count(), 0);

    QList<QAction *> hoseCarMenuActions{p_hoseCarShape->menu()->actions()};
    QCOMPARE(hoseCarMenuActions.size(), 1);
    hoseCarMenuActions.clear();

    QTest::mouseClick(view.viewport(), Qt::RightButton, Qt::NoModifier
                      , view.mapFromScene(p_hoseCarShape->boundingRect().center()));
    hoseCarMenuActions = p_hoseCarShape->menu()->actions();
    QCOMPARE(hoseCarMenuActions.size(), 1);
    QCOMPARE(hoseCarContextMenuSpy.count(), 1);

    scene.removeItem(p_hoseCarShape);
    delete p_hoseCarContextMenu;
    TechnicsShape::TechnicsShapeDeleter::cleanup(p_hoseCarShape);

    // CommShape
    ContextMenuTester *p_commContextMenu = new ContextMenuTester();

    TechnicsShape *p_commShape = TechnicsShape::createTechnicsShape(TechnicsShape::Comm);
    p_commShape->setMenu(p_commContextMenu);
    scene.addItem(p_commShape);

    mousePressEvent.setScenePos(p_commShape->pos());
    QApplication::sendEvent(&scene, &mousePressEvent);
    QVERIFY(mousePressEvent.isAccepted());

    p_commShape->setSelected(true);
    QSignalSpy commContextMenuSpy(p_commShape->menu(), &QMenu::aboutToShow);
    QCOMPARE(commContextMenuSpy.count(), 0);

    QList<QAction *> commMenuActions{p_commShape->menu()->actions()};
    QCOMPARE(commMenuActions.size(), 1);
    commMenuActions.clear();

    QTest::mouseClick(view.viewport(), Qt::RightButton, Qt::NoModifier
                      , view.mapFromScene(p_commShape->boundingRect().center()));
    commMenuActions = p_commShape->menu()->actions();
    QCOMPARE(commMenuActions.size(), 1);
    QCOMPARE(commContextMenuSpy.count(), 1);

    scene.removeItem(p_commShape);
    delete p_commContextMenu;
    TechnicsShape::TechnicsShapeDeleter::cleanup(p_commShape);
}

QTEST_MAIN(tst_TechnicShape)

#include "tst_technicsshape.moc"
