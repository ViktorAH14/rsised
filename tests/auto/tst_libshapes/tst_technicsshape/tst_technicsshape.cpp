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

    // TankerShape, PumpHoseShape, FirstAidShape, EmergencyShape, PumpStatShape, LafetTankerShape,
    // Aerodromeshape, FoamShape
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

    // TechServShape
    TechnicsShape *p_techServShape = nullptr;
    p_techServShape = TechnicsShape::createTechnicsShape(TechnicsShape::TechServ);
    QVERIFY2(p_techServShape, "techServShape is nullptr");
    QCOMPARE(int(p_techServShape->type()), int(QGraphicsItem::UserType + 211));
    TechnicsShape::TechnicsShapeDeleter::cleanup(p_techServShape);

    // SmokRemShape
    TechnicsShape *p_smokRemShape = nullptr;
    p_smokRemShape = TechnicsShape::createTechnicsShape(TechnicsShape::SmokRem);
    QVERIFY2(p_smokRemShape, "smokRemShape is nullptr");
    QCOMPARE(int(p_smokRemShape->type()), int(QGraphicsItem::UserType + 212));
    TechnicsShape::TechnicsShapeDeleter::cleanup(p_smokRemShape);

    // PumpStatShape
    TechnicsShape *p_pumpStatShape = nullptr;
    p_pumpStatShape = TechnicsShape::createTechnicsShape(TechnicsShape::PumpStat);
    QVERIFY2(p_pumpStatShape, "pumpStatShape is nullptr");
    QCOMPARE(int(p_pumpStatShape->type()), int(QGraphicsItem::UserType + 213));
    TechnicsShape::TechnicsShapeDeleter::cleanup(p_pumpStatShape);

    // LafetTankerShape
    TechnicsShape *p_lafetTankerShape = nullptr;
    p_lafetTankerShape = TechnicsShape::createTechnicsShape(TechnicsShape::LafetTanker);
    QVERIFY2(p_lafetTankerShape, "lafetTankerShape is nullptr");
    QCOMPARE(int(p_lafetTankerShape->type()), int(QGraphicsItem::UserType + 214));
    TechnicsShape::TechnicsShapeDeleter::cleanup(p_lafetTankerShape);

    // LafetCarShape
    TechnicsShape *p_lafetCarShape = nullptr;
    p_lafetCarShape = TechnicsShape::createTechnicsShape(TechnicsShape::LafetCar);
    QVERIFY2(p_lafetCarShape, "lafetCarShape is nullptr");
    QCOMPARE(int(p_lafetCarShape->type()), int(QGraphicsItem::UserType + 215));
    TechnicsShape::TechnicsShapeDeleter::cleanup(p_lafetCarShape);

    // AerodromeShape
    TechnicsShape *p_aerodromeShape = nullptr;
    p_aerodromeShape = TechnicsShape::createTechnicsShape(TechnicsShape::Aerodrome);
    QVERIFY2(p_aerodromeShape, "aerodromeShape is nullptr");
    QCOMPARE(int(p_aerodromeShape->type()), int(QGraphicsItem::UserType + 216));
    TechnicsShape::TechnicsShapeDeleter::cleanup(p_aerodromeShape);

    // FoamShape
    TechnicsShape *p_foamShape = nullptr;
    p_foamShape = TechnicsShape::createTechnicsShape(TechnicsShape::Foam);
    QVERIFY2(p_foamShape, "foamShape is nullptr");
    QCOMPARE(int(p_foamShape->type()), int(QGraphicsItem::UserType + 217));
    TechnicsShape::TechnicsShapeDeleter::cleanup(p_foamShape);

    // ComboShape
    TechnicsShape *p_comboShape = nullptr;
    p_comboShape = TechnicsShape::createTechnicsShape(TechnicsShape::Combo);
    QVERIFY2(p_comboShape, "comboShape is nullptr");
    QCOMPARE(int(p_comboShape->type()), int(QGraphicsItem::UserType + 218));
    TechnicsShape::TechnicsShapeDeleter::cleanup(p_comboShape);

    // AerosolShape
    TechnicsShape *p_aerosolShape = nullptr;
    p_aerosolShape = TechnicsShape::createTechnicsShape(TechnicsShape::Aerosol);
    QVERIFY2(p_aerosolShape, "aerosolShape is nullptr");
    QCOMPARE(int(p_aerosolShape->type()), int(QGraphicsItem::UserType + 219));
    TechnicsShape::TechnicsShapeDeleter::cleanup(p_aerosolShape);

    // PowderShape
    TechnicsShape *p_powderShape = nullptr;
    p_powderShape = TechnicsShape::createTechnicsShape(TechnicsShape::Powder);
    QVERIFY2(p_powderShape, "powderShape is nullptr");
    QCOMPARE(int(p_powderShape->type()), int(QGraphicsItem::UserType + 220));
    TechnicsShape::TechnicsShapeDeleter::cleanup(p_powderShape);

    // CarbonShape
    TechnicsShape *p_carbonShape = nullptr;
    p_carbonShape = TechnicsShape::createTechnicsShape(TechnicsShape::Carbon);
    QVERIFY2(p_carbonShape, "carbonShape is nullptr");
    QCOMPARE(int(p_carbonShape->type()), int(QGraphicsItem::UserType + 221));
    TechnicsShape::TechnicsShapeDeleter::cleanup(p_carbonShape);

    // GazWaterShape
    TechnicsShape *p_gazWaterShape = nullptr;
    p_gazWaterShape = TechnicsShape::createTechnicsShape(TechnicsShape::GazWater);
    QVERIFY2(p_gazWaterShape, "gazWaterShape is nullptr");
    QCOMPARE(int(p_gazWaterShape->type()), int(QGraphicsItem::UserType + 222));
    TechnicsShape::TechnicsShapeDeleter::cleanup(p_gazWaterShape);
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

    // TechServShape
    TechnicsShape *p_techServShape = TechnicsShape::createTechnicsShape(TechnicsShape::TechServ);
    QCOMPARE(p_techServShape->boundingRect(), QRectF(-15.5, -38.0, 31.0, 76.0));
    TechnicsShape::TechnicsShapeDeleter::cleanup(p_techServShape);

    // SmokRemShape
    TechnicsShape *p_smokRemShape = TechnicsShape::createTechnicsShape(TechnicsShape::SmokRem);
    QCOMPARE(p_smokRemShape->boundingRect(), QRectF(-15.5, -38.0, 31.0, 76.0));
    TechnicsShape::TechnicsShapeDeleter::cleanup(p_smokRemShape);

    // PumpStatShape
    TechnicsShape *p_pumpStatShape = TechnicsShape::createTechnicsShape(TechnicsShape::PumpStat);
    QCOMPARE(p_pumpStatShape->boundingRect(), QRectF(-15.5, -38.0, 31.0, 76.0));
    PumpStatShape *p_pumpStat = dynamic_cast<PumpStatShape *>(p_pumpStatShape);
    p_pumpStat->setPipes(true);
    QCOMPARE(p_pumpStatShape->boundingRect(), QRectF(-20.5, -38.0, 41.0, 76.0));
    p_pumpStat->setCollector(true);
    QCOMPARE(p_pumpStatShape->boundingRect(), QRectF(-20.5, -38.0, 41.0, 86.0));
    p_pumpStat->setPipes(false);
    QCOMPARE(p_pumpStatShape->boundingRect(), QRectF(-15.5, -38.0, 31.0, 86.0));
    p_pumpStat->setCollector(false);
    QCOMPARE(p_pumpStatShape->boundingRect(), QRectF(-15.5, -38.0, 31.0, 76.0));
    TechnicsShape::TechnicsShapeDeleter::cleanup(p_pumpStatShape);

    // LafetTankerShape
    TechnicsShape *p_lafetTankerShape = TechnicsShape::createTechnicsShape(TechnicsShape::LafetTanker);
    QCOMPARE(p_lafetTankerShape->boundingRect(), QRectF(-24.0, -38.0, 48.0, 76.0));
    LafetTankerShape *p_lafetTanker = dynamic_cast<LafetTankerShape *>(p_lafetTankerShape);
    p_lafetTanker->setPipes(true);
    QCOMPARE(p_lafetTankerShape->boundingRect(), QRectF(-24.0, -38.0, 53.0, 76.0));
    p_lafetTanker->setCollector(true);
    QCOMPARE(p_lafetTankerShape->boundingRect(), QRectF(-24.0, -38.0, 53.0, 86.0));
    p_lafetTanker->setPipes(false);
    QCOMPARE(p_lafetTankerShape->boundingRect(), QRectF(-24.0, -38.0, 48.0, 86.0));
    p_lafetTanker->setCollector(false);
    QCOMPARE(p_lafetTankerShape->boundingRect(), QRectF(-24.0, -38.0, 48.0, 76.0));
    TechnicsShape::TechnicsShapeDeleter::cleanup(p_lafetTankerShape);

    // LafetCarShape
    TechnicsShape *p_lafetCarShape = TechnicsShape::createTechnicsShape(TechnicsShape::LafetCar);
    QCOMPARE(p_lafetCarShape->boundingRect(), QRectF(-15.5, -38.0, 31.0, 76.0));
    TechnicsShape::TechnicsShapeDeleter::cleanup(p_lafetCarShape);

    // AerodromeShape
    TechnicsShape *p_aerodromeShape = TechnicsShape::createTechnicsShape(TechnicsShape::Aerodrome);
    QCOMPARE(p_aerodromeShape->boundingRect(), QRectF(-15.5, -38.0, 31.0, 76.0));
    AerodromeShape *p_aerodrome = dynamic_cast<AerodromeShape *>(p_aerodromeShape);
    p_aerodrome->setPipes(true);
    QCOMPARE(p_aerodromeShape->boundingRect(), QRectF(-20.5, -38.0, 41.0, 76.0));
    p_aerodrome->setCollector(true);
    QCOMPARE(p_aerodromeShape->boundingRect(), QRectF(-20.5, -38.0, 41.0, 86.0));
    p_aerodrome->setPipes(false);
    QCOMPARE(p_aerodromeShape->boundingRect(), QRectF(-15.5, -38.0, 31.0, 86.0));
    p_aerodrome->setCollector(false);
    QCOMPARE(p_aerodromeShape->boundingRect(), QRectF(-15.5, -38.0, 31.0, 76.0));
    TechnicsShape::TechnicsShapeDeleter::cleanup(p_aerodromeShape);

    // FoamShape
    TechnicsShape *p_foamShape = TechnicsShape::createTechnicsShape(TechnicsShape::Foam);
    QCOMPARE(p_foamShape->boundingRect(), QRectF(-15.5, -38.0, 31.0, 76.0));
    FoamShape *p_foam = dynamic_cast<FoamShape *>(p_foamShape);
    p_foam->setPipes(true);
    QCOMPARE(p_foamShape->boundingRect(), QRectF(-20.5, -38.0, 41.0, 76.0));
    p_foam->setCollector(true);
    QCOMPARE(p_foamShape->boundingRect(), QRectF(-20.5, -38.0, 41.0, 86.0));
    p_foam->setPipes(false);
    QCOMPARE(p_foamShape->boundingRect(), QRectF(-15.5, -38.0, 31.0, 86.0));
    p_foam->setCollector(false);
    QCOMPARE(p_foamShape->boundingRect(), QRectF(-15.5, -38.0, 31.0, 76.0));
    TechnicsShape::TechnicsShapeDeleter::cleanup(p_foamShape);

    // ComboShape
    TechnicsShape *p_comboShape = TechnicsShape::createTechnicsShape(TechnicsShape::Combo);
    QCOMPARE(p_comboShape->boundingRect(), QRectF(-15.5, -38.0, 31.0, 76.0));
    ComboShape *p_combo = dynamic_cast<ComboShape *>(p_comboShape);
    p_combo->setPipes(true);
    QCOMPARE(p_comboShape->boundingRect(), QRectF(-20.5, -38.0, 41.0, 76.0));
    p_combo->setCollector(true);
    QCOMPARE(p_comboShape->boundingRect(), QRectF(-20.5, -38.0, 41.0, 86.0));
    p_combo->setPipes(false);
    QCOMPARE(p_comboShape->boundingRect(), QRectF(-15.5, -38.0, 31.0, 86.0));
    p_combo->setCollector(false);
    QCOMPARE(p_comboShape->boundingRect(), QRectF(-15.5, -38.0, 31.0, 76.0));
    TechnicsShape::TechnicsShapeDeleter::cleanup(p_comboShape);

    // AerosolShape
    TechnicsShape *p_aerosolShape = TechnicsShape::createTechnicsShape(TechnicsShape::Aerosol);
    QCOMPARE(p_aerosolShape->boundingRect(), QRectF(-15.5, -38.0, 31.0, 76.0));
    TechnicsShape::TechnicsShapeDeleter::cleanup(p_aerosolShape);

    // PowderShape
    TechnicsShape *p_powderShape = TechnicsShape::createTechnicsShape(TechnicsShape::Powder);
    QCOMPARE(p_powderShape->boundingRect(), QRectF(-15.5, -38.0, 31.0, 76.0));
    TechnicsShape::TechnicsShapeDeleter::cleanup(p_powderShape);

    // CarbonShape
    TechnicsShape *p_carbonShape = TechnicsShape::createTechnicsShape(TechnicsShape::Carbon);
    QCOMPARE(p_carbonShape->boundingRect(), QRectF(-15.5, -38.0, 31.0, 76.0));
    TechnicsShape::TechnicsShapeDeleter::cleanup(p_carbonShape);

    // GazWaterShape
    TechnicsShape *p_gazWaterShape = TechnicsShape::createTechnicsShape(TechnicsShape::GazWater);
    QCOMPARE(p_gazWaterShape->boundingRect(), QRectF(-15.5, -38.0, 31.0, 76.0));
    TechnicsShape::TechnicsShapeDeleter::cleanup(p_gazWaterShape);
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

// TechServShape
    TechnicsShape *p_techServShape = TechnicsShape::createTechnicsShape(TechnicsShape::TechServ);
    QPainterPathStroker ps_techServShape;
    ps_techServShape.setWidth(p_techServShape->pen().widthF());
    QRectF techServRect{p_techServShape->rect()};
    qreal frontTabTechServ{techServRect.height() / 3};
    QPointF frontCenterTechServ{techServRect.center().x(), techServRect.top()}; // 0.0, -37.5
    QPointF frontRightTechServ{techServRect.right(), techServRect.top() + frontTabTechServ}; // 15.0, -12.5
    QPointF frontLeftTechServ{techServRect.left(), techServRect.top() + frontTabTechServ}; // -15.0, -12.5
    QPointF bottomRightTechServ{techServRect.bottomRight()}; // 15.0, 37.5
    QPointF bottomLeftTechServ{techServRect.bottomLeft()}; // -15.0, 37.5
    QPolygonF techServPolygon;
    techServPolygon << frontCenterTechServ << frontRightTechServ << bottomRightTechServ
                    << bottomLeftTechServ << frontLeftTechServ << frontCenterTechServ;
    QPainterPath techServPath;
    techServPath.addPolygon(techServPolygon);
    QPainterPath strokeTechServPath = ps_techServShape.createStroke(techServPath);
    strokeTechServPath.addPath(techServPath);
    QCOMPARE(p_techServShape->shape(), strokeTechServPath);
    TechnicsShape::TechnicsShapeDeleter::cleanup(p_techServShape);

// SmokRemShape
    TechnicsShape *p_smokRemShape = TechnicsShape::createTechnicsShape(TechnicsShape::SmokRem);
    QPainterPathStroker ps_smokRemShape;
    ps_smokRemShape.setWidth(p_smokRemShape->pen().widthF());
    QRectF smokRemRect{p_smokRemShape->rect()};
    qreal frontTabSmokRem{smokRemRect.height() / 3};
    QPointF frontCenterSmokRem{smokRemRect.center().x(), smokRemRect.top()}; // 0.0, -37.5
    QPointF frontRightSmokRem{smokRemRect.right(), smokRemRect.top() + frontTabSmokRem}; // 15.0, -12.5
    QPointF frontLeftSmokRem{smokRemRect.left(), smokRemRect.top() + frontTabSmokRem}; // -15.0, -12.5
    QPointF bottomRightSmokRem{smokRemRect.bottomRight()}; // 15.0, 37.5
    QPointF bottomLeftSmokRem{smokRemRect.bottomLeft()}; // -15.0, 37.5
    QPolygonF smokRemPolygon;
    smokRemPolygon << frontCenterSmokRem << frontRightSmokRem << bottomRightSmokRem
                    << bottomLeftSmokRem << frontLeftSmokRem << frontCenterSmokRem;
    QPainterPath smokRemPath;
    smokRemPath.addPolygon(smokRemPolygon);
    QPainterPath strokeSmokRemPath = ps_smokRemShape.createStroke(smokRemPath);
    strokeSmokRemPath.addPath(smokRemPath);
    QCOMPARE(p_smokRemShape->shape(), strokeSmokRemPath);
    TechnicsShape::TechnicsShapeDeleter::cleanup(p_smokRemShape);

// PumpStatShape
    TechnicsShape *p_pumpStatShape = TechnicsShape::createTechnicsShape(TechnicsShape::PumpStat);
    QPainterPathStroker ps_pumpStatShape;
    ps_pumpStatShape.setWidth(p_pumpStatShape->pen().widthF());
    QRectF pumpStatRect{p_pumpStatShape->rect()};
    qreal frontTabPumpStat{pumpStatRect.height() / 3};
    QPointF frontCenterPumpStat{pumpStatRect.center().x(), pumpStatRect.top()}; // 0.0, -37.5
    QPointF frontRightPumpStat{pumpStatRect.right(), pumpStatRect.top() + frontTabPumpStat}; // 15.0, -12.5
    QPointF frontLeftPumpStat{pumpStatRect.left(), pumpStatRect.top() + frontTabPumpStat}; // -15.0, -12.5
    QPointF bottomRightPumpStat{pumpStatRect.bottomRight()}; // 15.0, 37.5
    QPointF bottomLeftPumpStat{pumpStatRect.bottomLeft()}; // -15.0, 37.5
    QPolygonF pumpStatPolygon;
    pumpStatPolygon << frontCenterPumpStat << frontRightPumpStat << bottomRightPumpStat
                  << bottomLeftPumpStat << frontLeftPumpStat << frontCenterPumpStat;
    QPainterPath pumpStatPath;
    pumpStatPath.addPolygon(pumpStatPolygon);
    QPainterPath strokePumpStatPath = ps_pumpStatShape.createStroke(pumpStatPath);
    strokePumpStatPath.addPath(pumpStatPath);
    QCOMPARE(p_pumpStatShape->shape(), strokePumpStatPath);

    // PumpStatShape show pipes
    PumpStatShape *p_pumpStat = dynamic_cast<PumpStatShape *>(p_pumpStatShape);
    pumpStatPath.clear();
    strokePumpStatPath.clear();
    p_pumpStat->setPipes(true);
    pumpStatPath.addPolygon(pumpStatPolygon);
    qreal sixthWidthPumpStat{pumpStatRect.width() / 6}; // 5.0
    qreal pipeYPumpStat{pumpStatRect.bottom() - sixthWidthPumpStat};
    QPointF rightPipeP1PumpStat{pumpStatRect.right(), pipeYPumpStat};
    QPointF rightPipeP2PumpStat{pumpStatRect.right() + sixthWidthPumpStat, pipeYPumpStat};
    // Right pipe
    pumpStatPath.moveTo(rightPipeP1PumpStat);
    pumpStatPath.lineTo(rightPipeP2PumpStat);
    QPointF rightConnectP1PumpStat{rightPipeP2PumpStat.x(), rightPipeP2PumpStat.y()
                                                            + sixthWidthPumpStat / 2};
    QPointF rightConnectP2PumpStat{rightPipeP2PumpStat.x(), rightPipeP2PumpStat.y()
                                                            - sixthWidthPumpStat / 2};
    // Right pipe connection
    pumpStatPath.moveTo(rightConnectP1PumpStat);
    pumpStatPath.lineTo(rightConnectP2PumpStat);
    QPointF leftPipeP1PumpStat{pumpStatRect.left(), pipeYPumpStat};
    QPointF leftPipeP2PumpStat{pumpStatRect.left() - sixthWidthPumpStat, pipeYPumpStat};
    // Left pipe
    pumpStatPath.moveTo(leftPipeP1PumpStat);
    pumpStatPath.lineTo(leftPipeP2PumpStat);
    QPointF leftConnectP1PumpStat{leftPipeP2PumpStat.x(), leftPipeP2PumpStat.y()
                                                          + sixthWidthPumpStat / 2};
    QPointF leftConnectP2PumpStat{leftPipeP2PumpStat.x(), leftPipeP2PumpStat.y()
                                                          - sixthWidthPumpStat / 2};
    // Right pipe connection
    pumpStatPath.moveTo(leftConnectP1PumpStat);
    pumpStatPath.lineTo(leftConnectP2PumpStat);
    strokePumpStatPath = ps_pumpStatShape.createStroke(pumpStatPath);
    strokePumpStatPath.addPath(pumpStatPath);
    QCOMPARE(p_pumpStat->shape(), strokePumpStatPath);

    // PumpStatShape show collector
    pumpStatPath.clear();
    strokePumpStatPath.clear();
    p_pumpStat->setPipes(false);
    p_pumpStat->setCollector(true);
    pumpStatPath.addPolygon(pumpStatPolygon);
    qreal collectorXPumpStat{pumpStatRect.center().x()};
    qreal collectorYPumpStat{pumpStatRect.bottom() + sixthWidthPumpStat * 2};
    qreal leftCollectorPipeXPumpStat{collectorXPumpStat - sixthWidthPumpStat};
    QPointF leftRightCollectorPipeP1PumpStat{collectorXPumpStat, pumpStatRect.bottom()};
    QPointF leftCollectorPipe2PumpStat{leftCollectorPipeXPumpStat, collectorYPumpStat};
    //Left collector pipe
    pumpStatPath.moveTo(leftRightCollectorPipeP1PumpStat);
    pumpStatPath.lineTo(leftCollectorPipe2PumpStat);
    qreal rightCollectorPipeXPumpStat{collectorXPumpStat + sixthWidthPumpStat};
    QPointF rightCollectorPipeP2PumpStat{rightCollectorPipeXPumpStat, collectorYPumpStat};
    //Right collector pipe
    pumpStatPath.moveTo(leftRightCollectorPipeP1PumpStat);
    pumpStatPath.lineTo(rightCollectorPipeP2PumpStat);
    QPointF leftCollectorConnectP1PumpStat{leftCollectorPipeXPumpStat - sixthWidthPumpStat / 2
                                         , collectorYPumpStat};
    QPointF leftCollectorConnectP2PumpStat{leftCollectorPipeXPumpStat + sixthWidthPumpStat / 2
                                         , collectorYPumpStat};
    //Left connector
    pumpStatPath.moveTo(leftCollectorConnectP1PumpStat);
    pumpStatPath.lineTo(leftCollectorConnectP2PumpStat);
    QPointF rightCollectorConnectP1PumpStat{rightCollectorPipeXPumpStat - sixthWidthPumpStat / 2
                                          , collectorYPumpStat};
    QPointF rightCollectorConnectP2PumpStat{rightCollectorPipeXPumpStat + sixthWidthPumpStat / 2
                                          , collectorYPumpStat};
    //Right connector
    pumpStatPath.moveTo(rightCollectorConnectP1PumpStat);
    pumpStatPath.lineTo(rightCollectorConnectP2PumpStat);
    strokePumpStatPath = ps_pumpStatShape.createStroke(pumpStatPath);
    strokePumpStatPath.addPath(pumpStatPath);
    QCOMPARE(p_pumpStat->shape(), strokePumpStatPath);

    p_pumpStat= nullptr;
    TechnicsShape::TechnicsShapeDeleter::cleanup(p_pumpStatShape);

// LafetTankerShape
    TechnicsShape *p_lafetTankerShape = TechnicsShape::createTechnicsShape(TechnicsShape::LafetTanker);
    QRectF lafetTankerRect{p_lafetTankerShape->rect()};
    qreal arrowWidth{lafetTankerRect.width() / 23.5}; // 2.0
    qreal baseWidth{(lafetTankerRect.width() - arrowWidth) / 3.0 * 2.0}; // 30.0
    qreal baseCenterX{lafetTankerRect.right() - baseWidth / 2.0}; // 8.5
    qreal baseLeft{lafetTankerRect.right() - baseWidth}; // -6.5
    qreal thirdHeight{lafetTankerRect.height() / 3.0}; // 25.0
    // LafetTanker base
    QPointF frontCenterLafetTanker{baseCenterX, lafetTankerRect.top()}; // 0.0, -37.5
    QPointF frontRightLafetTanker{lafetTankerRect.right(), lafetTankerRect.top() + thirdHeight}; // 15.0, -12.5
    QPointF frontLeftLafetTanker{baseLeft, lafetTankerRect.top() + thirdHeight}; // -15.0, -12.5
    QPointF bottomRightLafetTanker{lafetTankerRect.bottomRight()}; // 15.0, 37.5
    QPointF bottomLeftLafetTanker{baseLeft, lafetTankerRect.bottom()}; // -15.0, 37.5
    QPolygonF lafetTankerBasePolygon;
    lafetTankerBasePolygon << frontCenterLafetTanker << frontRightLafetTanker
                           << bottomRightLafetTanker << bottomLeftLafetTanker
                           << frontLeftLafetTanker<< frontCenterLafetTanker;
    // LafetTanker lafet
    // Barrel
    QPointF barrelP1{lafetTankerRect.left() + arrowWidth, lafetTankerRect.top() + thirdHeight};
    QPointF barrelP2{baseLeft, lafetTankerRect.bottom()};
    QLineF barrelLine{barrelP1, barrelP2};
    //Stand
    QPointF standP1{barrelLine.pointAt(0.5)};
    QPointF standP2{baseLeft, standP1.y()};
    //Left arrow
    QLineF leftArrow;
    leftArrow.setP1(barrelP1);
    QPointF leftArrowP2{lafetTankerRect.left(), barrelP1.y() + lafetTankerRect.height() / 10.0};
    leftArrow.setP2(leftArrowP2);
    //Right arrow
    QLineF rightArrow;
    rightArrow.setP1(barrelP1);
    rightArrow.setLength(leftArrow.length());
    rightArrow.setAngle(barrelLine.angle() + leftArrow.angleTo(barrelLine));

    QPainterPath lafetTankerPath;
    lafetTankerPath.addPolygon(lafetTankerBasePolygon);
    lafetTankerPath.moveTo(barrelLine.p1());
    lafetTankerPath.lineTo(barrelLine.p2());
    lafetTankerPath.moveTo(standP1);
    lafetTankerPath.lineTo(standP2);
    lafetTankerPath.moveTo(leftArrow.p1());
    lafetTankerPath.lineTo(leftArrow.p2());
    lafetTankerPath.moveTo(rightArrow.p1());
    lafetTankerPath.lineTo(rightArrow.p2());

    QPainterPathStroker ps_lafetTankerShape;
    ps_lafetTankerShape.setWidth(p_lafetTankerShape->pen().widthF());
    QPainterPath strokeLafetTankerPath = ps_lafetTankerShape.createStroke(lafetTankerPath);
    strokeLafetTankerPath.addPath(lafetTankerPath);
    QCOMPARE(p_lafetTankerShape->shape(), strokeLafetTankerPath);

    // LafetTankerShape show pipes
    LafetTankerShape *p_lafetTanker= dynamic_cast<LafetTankerShape *>(p_lafetTankerShape);
    lafetTankerPath.clear();
    strokeLafetTankerPath.clear();
    p_lafetTanker->setPipes(true);
    lafetTankerPath.addPolygon(lafetTankerBasePolygon);
    lafetTankerPath.moveTo(barrelLine.p1());
    lafetTankerPath.lineTo(barrelLine.p2());
    lafetTankerPath.moveTo(standP1);
    lafetTankerPath.lineTo(standP2);
    lafetTankerPath.moveTo(leftArrow.p1());
    lafetTankerPath.lineTo(leftArrow.p2());
    lafetTankerPath.moveTo(rightArrow.p1());
    lafetTankerPath.lineTo(rightArrow.p2());

    qreal sixthWidthLafetTanker{lafetTankerRect.width() / 6}; // 5.0
    qreal pipeY{lafetTankerRect.bottom() - sixthWidthLafetTanker};
    // Right pipe
    QPointF rightPipeP1LafetTanker{lafetTankerRect.right(), pipeY};
    QPointF rightPipeP2LafetTanker{lafetTankerRect.right() + sixthWidthLafetTanker, pipeY};
    lafetTankerPath.moveTo(rightPipeP1LafetTanker);
    lafetTankerPath.lineTo(rightPipeP2LafetTanker);
    // Right pipe connection
    QPointF rightConnectP1LafetTanker{rightPipeP2LafetTanker.x(), rightPipeP2LafetTanker.y()
                                                                    + sixthWidthLafetTanker / 2};
    QPointF rightConnectP2LafetTanker{rightPipeP2LafetTanker.x(), rightPipeP2LafetTanker.y()
                                                                    - sixthWidthLafetTanker / 2};
    lafetTankerPath.moveTo(rightConnectP1LafetTanker);
    lafetTankerPath.lineTo(rightConnectP2LafetTanker);
    // Left pipe
    QPointF leftPipeP1LafetTanker{baseLeft, pipeY};
    QPointF leftPipeP2LafetTanker{baseLeft - sixthWidthLafetTanker, pipeY};
    lafetTankerPath.moveTo(leftPipeP1LafetTanker);
    lafetTankerPath.lineTo(leftPipeP2LafetTanker);
    // Right pipe connection
    QPointF leftConnectP1LafetTanker{leftPipeP2LafetTanker.x(), leftPipeP2LafetTanker.y()
                                                                    + sixthWidthLafetTanker / 2};
    QPointF leftConnectP2LafetTanker{leftPipeP2LafetTanker.x(), leftPipeP2LafetTanker.y()
                                                                    - sixthWidthLafetTanker / 2};
    lafetTankerPath.moveTo(leftConnectP1LafetTanker);
    lafetTankerPath.lineTo(leftConnectP2LafetTanker);

    strokeLafetTankerPath = ps_lafetTankerShape.createStroke(lafetTankerPath);
    strokeLafetTankerPath.addPath(lafetTankerPath);
    QCOMPARE(p_lafetTanker->shape(), strokeLafetTankerPath);

    // LafetTankerShape show collector
    lafetTankerPath.clear();
    strokeLafetTankerPath.clear();
    p_lafetTanker->setPipes(false);
    p_lafetTanker->setCollector(true);
    lafetTankerPath.addPolygon(lafetTankerBasePolygon);
    lafetTankerPath.moveTo(barrelLine.p1());
    lafetTankerPath.lineTo(barrelLine.p2());
    lafetTankerPath.moveTo(standP1);
    lafetTankerPath.lineTo(standP2);
    lafetTankerPath.moveTo(leftArrow.p1());
    lafetTankerPath.lineTo(leftArrow.p2());
    lafetTankerPath.moveTo(rightArrow.p1());
    lafetTankerPath.lineTo(rightArrow.p2());

    qreal lafetTankerCollectorX{lafetTankerRect.right() - baseWidth / 2.0}; // 8.5
    qreal lafetTankerCollectorY{lafetTankerRect.bottom() + lafetTankerRect.height() / 7.5}; // 10.0
    //Left collector pipe
    qreal lafetTankerLeftPipeX{lafetTankerCollectorX - sixthWidthLafetTanker};
    QPointF lafetTankerLeftRightPipeP1{lafetTankerCollectorX, lafetTankerRect.bottom()};
    QPointF lafetTankerLeftPipeP2{lafetTankerLeftPipeX, lafetTankerCollectorY};
    lafetTankerPath.moveTo(lafetTankerLeftRightPipeP1);
    lafetTankerPath.lineTo(lafetTankerLeftPipeP2);
    //Right collector pipe
    qreal lafetTankerRightPipeX{lafetTankerCollectorX + sixthWidthLafetTanker};
    QPointF lafetTankerRightPipeP2{lafetTankerRightPipeX, lafetTankerCollectorY};
    lafetTankerPath.moveTo(lafetTankerLeftRightPipeP1);
    lafetTankerPath.lineTo(lafetTankerRightPipeP2);
    //Left connector
    QPointF lafetTankerLeftConnectP1{lafetTankerLeftPipeX - sixthWidthLafetTanker / 2
                                     , lafetTankerCollectorY};
    QPointF lafetTankerLeftConnectP2{lafetTankerLeftPipeX + sixthWidthLafetTanker / 2
                                     , lafetTankerCollectorY};
    lafetTankerPath.moveTo(lafetTankerLeftConnectP1);
    lafetTankerPath.lineTo(lafetTankerLeftConnectP2);
    //Right connector
    QPointF lafetTankerRightConnectP1{lafetTankerRightPipeX - sixthWidthLafetTanker / 2
                                      , lafetTankerCollectorY};
    QPointF lafetTankerRightConnectP2{lafetTankerRightPipeX + sixthWidthLafetTanker / 2
                                      , lafetTankerCollectorY};
    lafetTankerPath.moveTo(lafetTankerRightConnectP1);
    lafetTankerPath.lineTo(lafetTankerRightConnectP2);

    strokeLafetTankerPath = ps_lafetTankerShape.createStroke(lafetTankerPath);
    strokeLafetTankerPath.addPath(lafetTankerPath);
    QCOMPARE(p_lafetTanker->shape(), strokeLafetTankerPath);

    p_lafetTanker = nullptr;
    TechnicsShape::TechnicsShapeDeleter::cleanup(p_lafetTankerShape);

// LafetCarShape
    TechnicsShape *p_lafetCarShape = TechnicsShape::createTechnicsShape(TechnicsShape::LafetCar);
    QPainterPathStroker ps_lafetCarShape;
    ps_lafetCarShape.setWidth(p_lafetCarShape->pen().widthF());
    QRectF lafetCarRect{p_lafetCarShape->rect()};
    qreal frontTabLafetCar{lafetCarRect.height() / 3};
    QPointF frontCenterLafetCar{lafetCarRect.center().x(), lafetCarRect.top()}; // 0.0, -37.5
    QPointF frontRightLafetCar{lafetCarRect.right(), lafetCarRect.top() + frontTabLafetCar}; // 15.0, -12.5
    QPointF frontLeftLafetCar{lafetCarRect.left(), lafetCarRect.top() + frontTabLafetCar}; // -15.0, -12.5
    QPointF bottomRightLafetCar{lafetCarRect.bottomRight()}; // 15.0, 37.5
    QPointF bottomLeftLafetCar{lafetCarRect.bottomLeft()}; // -15.0, 37.5
    QPolygonF lafetCarPolygon;
    lafetCarPolygon << frontCenterLafetCar << frontRightLafetCar << bottomRightLafetCar
                   << bottomLeftLafetCar << frontLeftLafetCar << frontCenterLafetCar;
    QPainterPath lafetCarPath;
    lafetCarPath.addPolygon(lafetCarPolygon);
    QPainterPath strokeLafetCarPath = ps_lafetCarShape.createStroke(lafetCarPath);
    strokeLafetCarPath.addPath(lafetCarPath);
    QCOMPARE(p_lafetCarShape->shape(), strokeLafetCarPath);
    TechnicsShape::TechnicsShapeDeleter::cleanup(p_lafetCarShape);

// AerodromeShape
    TechnicsShape *p_aerodromeShape = TechnicsShape::createTechnicsShape(TechnicsShape::Aerodrome);
    QPainterPathStroker ps_aerodromeShape;
    ps_aerodromeShape.setWidth(p_aerodromeShape->pen().widthF());
    QRectF aerodromeRect{p_aerodromeShape->rect()};
    qreal frontTabAerodrome{aerodromeRect.height() / 3};
    QPointF frontCenterAerodrome{aerodromeRect.center().x(), aerodromeRect.top()}; // 0.0, -37.5
    QPointF frontRightAerodrome{aerodromeRect.right(), aerodromeRect.top() + frontTabAerodrome}; // 15.0, -12.5
    QPointF frontLeftAerodrome{aerodromeRect.left(), aerodromeRect.top() + frontTabAerodrome}; // -15.0, -12.5
    QPointF bottomRightAerodrome{aerodromeRect.bottomRight()}; // 15.0, 37.5
    QPointF bottomLeftAerodrome{aerodromeRect.bottomLeft()}; // -15.0, 37.5
    QPolygonF aerodromePolygon;
    aerodromePolygon << frontCenterAerodrome << frontRightAerodrome << bottomRightAerodrome
                    << bottomLeftAerodrome << frontLeftAerodrome << frontCenterAerodrome;
    QPainterPath aerodromePath;
    aerodromePath.addPolygon(aerodromePolygon);
    QPainterPath strokeAerodromePath = ps_aerodromeShape.createStroke(aerodromePath);
    strokeAerodromePath.addPath(aerodromePath);
    QCOMPARE(p_aerodromeShape->shape(), strokeAerodromePath);

    // AerodromeShape show pipes
    AerodromeShape *p_aerodrome = dynamic_cast<AerodromeShape *>(p_aerodromeShape);
    aerodromePath.clear();
    strokeAerodromePath.clear();
    p_aerodrome->setPipes(true);
    aerodromePath.addPolygon(aerodromePolygon);
    qreal sixtWidthAerodrome{aerodromeRect.width() / 6}; // 5.0
    qreal pipeYAerodrome{aerodromeRect.bottom() - sixtWidthAerodrome};
    QPointF rightPipeP1Aerodrome{aerodromeRect.right(), pipeYAerodrome};
    QPointF rightPipeP2Aerodrome{aerodromeRect.right() + sixtWidthAerodrome, pipeYAerodrome};
    // Right pipe
    aerodromePath.moveTo(rightPipeP1Aerodrome);
    aerodromePath.lineTo(rightPipeP2Aerodrome);
    QPointF rightConnectP1Aerodrome{rightPipeP2Aerodrome.x(), rightPipeP2Aerodrome.y()
                                                                + sixtWidthAerodrome / 2};
    QPointF rightConnectP2Aerodrome{rightPipeP2Aerodrome.x(), rightPipeP2Aerodrome.y()
                                                                - sixtWidthAerodrome / 2};
    // Right pipe connection
    aerodromePath.moveTo(rightConnectP1Aerodrome);
    aerodromePath.lineTo(rightConnectP2Aerodrome);
    QPointF leftPipeP1Aerodrome{aerodromeRect.left(), pipeYAerodrome};
    QPointF leftPipeP2Aerodrome{aerodromeRect.left() - sixtWidthAerodrome, pipeYAerodrome};
    // Left pipe
    aerodromePath.moveTo(leftPipeP1Aerodrome);
    aerodromePath.lineTo(leftPipeP2Aerodrome);
    QPointF leftConnectP1Aerodrome{leftPipeP2Aerodrome.x(), leftPipeP2Aerodrome.y()
                                                              + sixtWidthAerodrome / 2};
    QPointF leftConnectP2Aerodrome{leftPipeP2Aerodrome.x(), leftPipeP2Aerodrome.y()
                                                              - sixtWidthAerodrome / 2};
    // Right pipe connection
    aerodromePath.moveTo(leftConnectP1Aerodrome);
    aerodromePath.lineTo(leftConnectP2Aerodrome);
    strokeAerodromePath = ps_aerodromeShape.createStroke(aerodromePath);
    strokeAerodromePath.addPath(aerodromePath);
    QCOMPARE(p_aerodrome->shape(), strokeAerodromePath);

    // AerodromeShape show collector
    aerodromePath.clear();
    strokeAerodromePath.clear();
    p_aerodrome->setPipes(false);
    p_aerodrome->setCollector(true);
    aerodromePath.addPolygon(aerodromePolygon);
    qreal collectorXAerodrome{aerodromeRect.center().x()};
    qreal collectorYAerodrome{aerodromeRect.bottom() + sixtWidthAerodrome * 2};
    qreal leftCollectorPipeXAerodrome{collectorXAerodrome - sixtWidthAerodrome};
    QPointF leftRightCollectorPipeP1Aerodrome{collectorXAerodrome, aerodromeRect.bottom()};
    QPointF leftCollectorPipeP2Aerodrome{leftCollectorPipeXAerodrome, collectorYAerodrome};
    //Left collector pipe
    aerodromePath.moveTo(leftRightCollectorPipeP1Aerodrome);
    aerodromePath.lineTo(leftCollectorPipeP2Aerodrome);
    qreal rightCollectorPipeXAerodrome{collectorXAerodrome + sixtWidthAerodrome};
    QPointF rightCollectorPipeP2Aerodrome{rightCollectorPipeXAerodrome, collectorYAerodrome};
    //Right collector pipe
    aerodromePath.moveTo(leftRightCollectorPipeP1Aerodrome);
    aerodromePath.lineTo(rightCollectorPipeP2Aerodrome);
    QPointF leftCollectorConnectP1Aerodrome{leftCollectorPipeXAerodrome - sixtWidthAerodrome / 2
                                           , collectorYAerodrome};
    QPointF leftCollectorConnectP2Aerodrome{leftCollectorPipeXAerodrome + sixtWidthAerodrome / 2
                                           , collectorYAerodrome};
    //Left connector
    aerodromePath.moveTo(leftCollectorConnectP1Aerodrome);
    aerodromePath.lineTo(leftCollectorConnectP2Aerodrome);
    QPointF rightCollectorConnectP1Aerodrome{rightCollectorPipeXAerodrome - sixtWidthAerodrome / 2
                                            , collectorYAerodrome};
    QPointF rightCollectorConnectP2Aerodrome{rightCollectorPipeXAerodrome + sixtWidthAerodrome / 2
                                            , collectorYAerodrome};
    //Right connector
    aerodromePath.moveTo(rightCollectorConnectP1Aerodrome);
    aerodromePath.lineTo(rightCollectorConnectP2Aerodrome);
    strokeAerodromePath = ps_aerodromeShape.createStroke(aerodromePath);
    strokeAerodromePath.addPath(aerodromePath);
    QCOMPARE(p_aerodrome->shape(), strokeAerodromePath);

    p_aerodrome = nullptr;
    TechnicsShape::TechnicsShapeDeleter::cleanup(p_aerodromeShape);

// FoamShape
    TechnicsShape *p_foamShape = TechnicsShape::createTechnicsShape(TechnicsShape::Aerodrome);
    QPainterPathStroker ps_foamShape;
    ps_foamShape.setWidth(p_foamShape->pen().widthF());
    QRectF foamRect{p_foamShape->rect()};
    qreal frontTabFoam{foamRect.height() / 3};
    QPointF frontCenterFoam{foamRect.center().x(), foamRect.top()}; // 0.0, -37.5
    QPointF frontRightFoam{foamRect.right(), foamRect.top() + frontTabFoam}; // 15.0, -12.5
    QPointF frontLeftFoam{foamRect.left(), foamRect.top() + frontTabFoam}; // -15.0, -12.5
    QPointF bottomRightFoam{foamRect.bottomRight()}; // 15.0, 37.5
    QPointF bottomLeftFoam{foamRect.bottomLeft()}; // -15.0, 37.5
    QPolygonF foamPolygon;
    foamPolygon << frontCenterFoam << frontRightFoam << bottomRightFoam
                     << bottomLeftFoam << frontLeftFoam << frontCenterFoam;
    QPainterPath foamPath;
    foamPath.addPolygon(foamPolygon);
    QPainterPath strokeFoamPath = ps_foamShape.createStroke(foamPath);
    strokeFoamPath.addPath(foamPath);
    QCOMPARE(p_foamShape->shape(), strokeFoamPath);

    // FoamShape show pipes
    AerodromeShape *p_foam = dynamic_cast<AerodromeShape *>(p_foamShape);
    foamPath.clear();
    strokeFoamPath.clear();
    p_foam->setPipes(true);
    foamPath.addPolygon(foamPolygon);
    qreal sixtWidthFoam{foamRect.width() / 6}; // 5.0
    qreal pipeYFoam{foamRect.bottom() - sixtWidthFoam};
    QPointF rightPipeP1Foam{foamRect.right(), pipeYFoam};
    QPointF rightPipeP2Foam{foamRect.right() + sixtWidthFoam, pipeYFoam};
    // Right pipe
    foamPath.moveTo(rightPipeP1Foam);
    foamPath.lineTo(rightPipeP2Foam);
    QPointF rightConnectP1Foam{rightPipeP2Foam.x(), rightPipeP2Foam.y()
                                                                  + sixtWidthFoam / 2};
    QPointF rightConnectP2Foam{rightPipeP2Foam.x(), rightPipeP2Foam.y()
                                                                  - sixtWidthFoam / 2};
    // Right pipe connection
    foamPath.moveTo(rightConnectP1Foam);
    foamPath.lineTo(rightConnectP2Foam);
    QPointF leftPipeP1Foam{foamRect.left(), pipeYFoam};
    QPointF leftPipeP2Foam{foamRect.left() - sixtWidthFoam, pipeYFoam};
    // Left pipe
    foamPath.moveTo(leftPipeP1Foam);
    foamPath.lineTo(leftPipeP2Foam);
    QPointF leftConnectP1Foam{leftPipeP2Foam.x(), leftPipeP2Foam.y()
                                                                + sixtWidthFoam / 2};
    QPointF leftConnectP2Foam{leftPipeP2Foam.x(), leftPipeP2Foam.y()
                                                                - sixtWidthFoam / 2};
    // Right pipe connection
    foamPath.moveTo(leftConnectP1Foam);
    foamPath.lineTo(leftConnectP2Foam);
    strokeFoamPath = ps_foamShape.createStroke(foamPath);
    strokeFoamPath.addPath(foamPath);
    QCOMPARE(p_foam->shape(), strokeFoamPath);

    // FoamShape show collector
    foamPath.clear();
    strokeFoamPath.clear();
    p_foam->setPipes(false);
    p_foam->setCollector(true);
    foamPath.addPolygon(foamPolygon);
    qreal collectorXFoam{foamRect.center().x()};
    qreal collectorYFoam{foamRect.bottom() + sixtWidthFoam * 2};
    qreal leftCollectorPipeXFoam{collectorXFoam - sixtWidthFoam};
    QPointF leftRightCollectorPipeP1Foam{collectorXFoam, foamRect.bottom()};
    QPointF leftCollectorPipeP2Foam{leftCollectorPipeXFoam, collectorYFoam};
    //Left collector pipe
    foamPath.moveTo(leftRightCollectorPipeP1Foam);
    foamPath.lineTo(leftCollectorPipeP2Foam);
    qreal rightCollectorPipeXFoam{collectorXFoam + sixtWidthFoam};
    QPointF rightCollectorPipeP2Foam{rightCollectorPipeXFoam, collectorYFoam};
    //Right collector pipe
    foamPath.moveTo(leftRightCollectorPipeP1Foam);
    foamPath.lineTo(rightCollectorPipeP2Foam);
    QPointF leftCollectorConnectP1Foam{leftCollectorPipeXFoam - sixtWidthFoam / 2
                                            , collectorYFoam};
    QPointF leftCollectorConnectP2Foam{leftCollectorPipeXFoam + sixtWidthFoam / 2
                                            , collectorYFoam};
    //Left connector
    foamPath.moveTo(leftCollectorConnectP1Foam);
    foamPath.lineTo(leftCollectorConnectP2Foam);
    QPointF rightCollectorConnectP1Foam{rightCollectorPipeXFoam - sixtWidthFoam / 2
                                             , collectorYFoam};
    QPointF rightCollectorConnectP2Foam{rightCollectorPipeXFoam + sixtWidthFoam / 2
                                             , collectorYFoam};
    //Right connector
    foamPath.moveTo(rightCollectorConnectP1Foam);
    foamPath.lineTo(rightCollectorConnectP2Foam);
    strokeFoamPath = ps_foamShape.createStroke(foamPath);
    strokeFoamPath.addPath(foamPath);
    QCOMPARE(p_foam->shape(), strokeFoamPath);

    p_foam = nullptr;
    TechnicsShape::TechnicsShapeDeleter::cleanup(p_foamShape);

// ComboShape
    TechnicsShape *p_comboShape = TechnicsShape::createTechnicsShape(TechnicsShape::Aerodrome);
    QPainterPathStroker ps_comboShape;
    ps_comboShape.setWidth(p_comboShape->pen().widthF());
    QRectF comboRect{p_comboShape->rect()};
    qreal frontTabCombo{comboRect.height() / 3};
    QPointF frontCenterCombo{comboRect.center().x(), comboRect.top()}; // 0.0, -37.5
    QPointF frontRightCombo{comboRect.right(), comboRect.top() + frontTabCombo}; // 15.0, -12.5
    QPointF frontLeftCombo{comboRect.left(), comboRect.top() + frontTabCombo}; // -15.0, -12.5
    QPointF bottomRightCombo{comboRect.bottomRight()}; // 15.0, 37.5
    QPointF bottomLeftCombo{comboRect.bottomLeft()}; // -15.0, 37.5
    QPolygonF comboPolygon;
    comboPolygon << frontCenterCombo << frontRightCombo << bottomRightCombo
                << bottomLeftCombo << frontLeftCombo << frontCenterCombo;
    QPainterPath comboPath;
    comboPath.addPolygon(comboPolygon);
    QPainterPath strokeComboPath = ps_comboShape.createStroke(comboPath);
    strokeComboPath.addPath(comboPath);
    QCOMPARE(p_comboShape->shape(), strokeComboPath);

    // ComboShape show pipes
    AerodromeShape *p_combo = dynamic_cast<AerodromeShape *>(p_comboShape);
    comboPath.clear();
    strokeComboPath.clear();
    p_combo->setPipes(true);
    comboPath.addPolygon(comboPolygon);
    qreal sixtWidthCombo{comboRect.width() / 6}; // 5.0
    qreal pipeYCombo{comboRect.bottom() - sixtWidthCombo};
    QPointF rightPipeP1Combo{comboRect.right(), pipeYCombo};
    QPointF rightPipeP2Combo{comboRect.right() + sixtWidthCombo, pipeYCombo};
    // Right pipe
    comboPath.moveTo(rightPipeP1Combo);
    comboPath.lineTo(rightPipeP2Combo);
    QPointF rightConnectP1Combo{rightPipeP2Combo.x(), rightPipeP2Combo.y()
                                                        + sixtWidthCombo / 2};
    QPointF rightConnectP2Combo{rightPipeP2Combo.x(), rightPipeP2Combo.y()
                                                        - sixtWidthCombo / 2};
    // Right pipe connection
    comboPath.moveTo(rightConnectP1Combo);
    comboPath.lineTo(rightConnectP2Combo);
    QPointF leftPipeP1Combo{comboRect.left(), pipeYCombo};
    QPointF leftPipeP2Combo{comboRect.left() - sixtWidthCombo, pipeYCombo};
    // Left pipe
    comboPath.moveTo(leftPipeP1Combo);
    comboPath.lineTo(leftPipeP2Combo);
    QPointF leftConnectP1Combo{leftPipeP2Combo.x(), leftPipeP2Combo.y()
                                                      + sixtWidthCombo / 2};
    QPointF leftConnectP2Combo{leftPipeP2Combo.x(), leftPipeP2Combo.y()
                                                      - sixtWidthCombo / 2};
    // Right pipe connection
    comboPath.moveTo(leftConnectP1Combo);
    comboPath.lineTo(leftConnectP2Combo);
    strokeComboPath = ps_comboShape.createStroke(comboPath);
    strokeComboPath.addPath(comboPath);
    QCOMPARE(p_combo->shape(), strokeComboPath);

    // ComboShape show collector
    comboPath.clear();
    strokeComboPath.clear();
    p_combo->setPipes(false);
    p_combo->setCollector(true);
    comboPath.addPolygon(comboPolygon);
    qreal collectorXCombo{comboRect.center().x()};
    qreal collectorYCombo{comboRect.bottom() + sixtWidthCombo * 2};
    qreal leftCollectorPipeXCombo{collectorXCombo - sixtWidthCombo};
    QPointF leftRightCollectorPipeP1Combo{collectorXCombo, comboRect.bottom()};
    QPointF leftCollectorPipeP2Combo{leftCollectorPipeXCombo, collectorYCombo};
    //Left collector pipe
    comboPath.moveTo(leftRightCollectorPipeP1Combo);
    comboPath.lineTo(leftCollectorPipeP2Combo);
    qreal rightCollectorPipeXCombo{collectorXCombo + sixtWidthCombo};
    QPointF rightCollectorPipeP2Combo{rightCollectorPipeXCombo, collectorYCombo};
    //Right collector pipe
    comboPath.moveTo(leftRightCollectorPipeP1Combo);
    comboPath.lineTo(rightCollectorPipeP2Combo);
    QPointF leftCollectorConnectP1Combo{leftCollectorPipeXCombo - sixtWidthCombo / 2
                                       , collectorYCombo};
    QPointF leftCollectorConnectP2Combo{leftCollectorPipeXCombo + sixtWidthCombo / 2
                                       , collectorYCombo};
    //Left connector
    comboPath.moveTo(leftCollectorConnectP1Combo);
    comboPath.lineTo(leftCollectorConnectP2Combo);
    QPointF rightCollectorConnectP1Combo{rightCollectorPipeXCombo - sixtWidthCombo / 2
                                        , collectorYCombo};
    QPointF rightCollectorConnectP2Combo{rightCollectorPipeXCombo + sixtWidthCombo / 2
                                        , collectorYCombo};
    //Right connector
    comboPath.moveTo(rightCollectorConnectP1Combo);
    comboPath.lineTo(rightCollectorConnectP2Combo);
    strokeComboPath = ps_comboShape.createStroke(comboPath);
    strokeComboPath.addPath(comboPath);
    QCOMPARE(p_combo->shape(), strokeComboPath);

    p_combo = nullptr;
    TechnicsShape::TechnicsShapeDeleter::cleanup(p_comboShape);

// AerosolShape
    TechnicsShape *p_aerosolShape = TechnicsShape::createTechnicsShape(TechnicsShape::Aerosol);
    QPainterPathStroker ps_aerosolShape;
    ps_aerosolShape.setWidth(p_aerosolShape->pen().widthF());
    QRectF aerosolRect{p_aerosolShape->rect()};
    qreal frontTabAerosol{aerosolRect.height() / 3};
    QPointF frontCenterAerosol{aerosolRect.center().x(), aerosolRect.top()}; // 0.0, -37.5
    QPointF frontRightAerosol{aerosolRect.right(), aerosolRect.top() + frontTabAerosol}; // 15.0, -12.5
    QPointF frontLeftAerosol{aerosolRect.left(), aerosolRect.top() + frontTabAerosol}; // -15.0, -12.5
    QPointF bottomRightAerosol{aerosolRect.bottomRight()}; // 15.0, 37.5
    QPointF bottomLeftAerosol{aerosolRect.bottomLeft()}; // -15.0, 37.5
    QPolygonF aerosolPolygon;
    aerosolPolygon << frontCenterAerosol << frontRightAerosol << bottomRightAerosol
                    << bottomLeftAerosol << frontLeftAerosol << frontCenterAerosol;
    QPainterPath aerosolPath;
    aerosolPath.addPolygon(aerosolPolygon);
    QPainterPath strokeAerosolPath = ps_aerosolShape.createStroke(aerosolPath);
    strokeAerosolPath.addPath(aerosolPath);
    QCOMPARE(p_aerosolShape->shape(), strokeAerosolPath);
    TechnicsShape::TechnicsShapeDeleter::cleanup(p_aerosolShape);

// PowderShape
    TechnicsShape *p_powderShape = TechnicsShape::createTechnicsShape(TechnicsShape::Powder);
    QPainterPathStroker ps_powderShape;
    ps_powderShape.setWidth(p_powderShape->pen().widthF());
    QRectF powderRect{p_powderShape->rect()};
    qreal frontTabPowder{powderRect.height() / 3};
    QPointF frontCenterPowder{powderRect.center().x(), powderRect.top()}; // 0.0, -37.5
    QPointF frontRightPowder{powderRect.right(), powderRect.top() + frontTabPowder}; // 15.0, -12.5
    QPointF frontLeftPowder{powderRect.left(), powderRect.top() + frontTabPowder}; // -15.0, -12.5
    QPointF bottomRightPowder{powderRect.bottomRight()}; // 15.0, 37.5
    QPointF bottomLeftPowder{powderRect.bottomLeft()}; // -15.0, 37.5
    QPolygonF powderPolygon;
    powderPolygon << frontCenterPowder << frontRightPowder << bottomRightPowder
                   << bottomLeftPowder << frontLeftPowder << frontCenterPowder;
    QPainterPath powderPath;
    powderPath.addPolygon(powderPolygon);
    QPainterPath strokePowderPath = ps_powderShape.createStroke(powderPath);
    strokePowderPath.addPath(powderPath);
    QCOMPARE(p_powderShape->shape(), strokePowderPath);
    TechnicsShape::TechnicsShapeDeleter::cleanup(p_powderShape);

// CarbonShape
    TechnicsShape *p_carbonShape = TechnicsShape::createTechnicsShape(TechnicsShape::Carbon);
    QPainterPathStroker ps_carbonShape;
    ps_carbonShape.setWidth(p_carbonShape->pen().widthF());
    QRectF carbonRect{p_carbonShape->rect()};
    qreal frontTabCarbon{carbonRect.height() / 3};
    QPointF frontCenterCarbon{carbonRect.center().x(), carbonRect.top()}; // 0.0, -37.5
    QPointF frontRightCarbon{carbonRect.right(), carbonRect.top() + frontTabCarbon}; // 15.0, -12.5
    QPointF frontLeftCarbon{carbonRect.left(), carbonRect.top() + frontTabCarbon}; // -15.0, -12.5
    QPointF bottomRightCarbon{carbonRect.bottomRight()}; // 15.0, 37.5
    QPointF bottomLeftCarbon{carbonRect.bottomLeft()}; // -15.0, 37.5
    QPolygonF carbonPolygon;
    carbonPolygon << frontCenterCarbon << frontRightCarbon << bottomRightCarbon
                  << bottomLeftCarbon << frontLeftCarbon << frontCenterCarbon;
    QPainterPath carbonPath;
    carbonPath.addPolygon(carbonPolygon);
    QPainterPath strokeCarbonPath = ps_carbonShape.createStroke(carbonPath);
    strokeCarbonPath.addPath(carbonPath);
    QCOMPARE(p_carbonShape->shape(), strokeCarbonPath);
    TechnicsShape::TechnicsShapeDeleter::cleanup(p_carbonShape);

// GazWaterShape
    TechnicsShape *p_gazWaterShape = TechnicsShape::createTechnicsShape(TechnicsShape::GazWater);
    QPainterPathStroker ps_gazWaterShape;
    ps_gazWaterShape.setWidth(p_gazWaterShape->pen().widthF());
    QRectF gazWaterRect{p_gazWaterShape->rect()};
    qreal frontTabGazWater{gazWaterRect.height() / 3};
    QPointF frontCenterGazWater{gazWaterRect.center().x(), gazWaterRect.top()}; // 0.0, -37.5
    QPointF frontRightGazWater{gazWaterRect.right(), gazWaterRect.top() + frontTabGazWater}; // 15.0, -12.5
    QPointF frontLeftGazWater{gazWaterRect.left(), gazWaterRect.top() + frontTabGazWater}; // -15.0, -12.5
    QPointF bottomRightGazWater{gazWaterRect.bottomRight()}; // 15.0, 37.5
    QPointF bottomLeftGazWater{gazWaterRect.bottomLeft()}; // -15.0, 37.5
    QPolygonF gazWaterPolygon;
    gazWaterPolygon << frontCenterGazWater << frontRightGazWater << bottomRightGazWater
                  << bottomLeftGazWater << frontLeftGazWater << frontCenterGazWater;
    QPainterPath gazWaterPath;
    gazWaterPath.addPolygon(gazWaterPolygon);
    QPainterPath strokeGazWaterPath = ps_gazWaterShape.createStroke(gazWaterPath);
    strokeGazWaterPath.addPath(gazWaterPath);
    QCOMPARE(p_gazWaterShape->shape(), strokeGazWaterPath);
    TechnicsShape::TechnicsShapeDeleter::cleanup(p_gazWaterShape);
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

    // TechServShape
    TechnicsShape *p_techServShape = TechnicsShape::createTechnicsShape(TechnicsShape::TechServ);
    QPixmap techServImage{p_techServShape->image()};
    QVERIFY2(!techServImage.isNull(), "techServShape::image() returned a null pixmap");
    QCOMPARE(techServImage.width(), p_techServShape->boundingRect().width());
    QCOMPARE(techServImage.height(), p_techServShape->boundingRect().height());
    TechnicsShape::TechnicsShapeDeleter::cleanup(p_techServShape);

    // SmokRemShape
    TechnicsShape *p_smokRemShape = TechnicsShape::createTechnicsShape(TechnicsShape::SmokRem);
    QPixmap smokRemImage{p_smokRemShape->image()};
    QVERIFY2(!smokRemImage.isNull(), "smokRemShape::image() returned a null pixmap");
    QCOMPARE(smokRemImage.width(), p_smokRemShape->boundingRect().width());
    QCOMPARE(smokRemImage.height(), p_smokRemShape->boundingRect().height());
    TechnicsShape::TechnicsShapeDeleter::cleanup(p_smokRemShape);

    // PumpStatShape
    TechnicsShape *p_pumpStatShape = TechnicsShape::createTechnicsShape(TechnicsShape::PumpStat);
    QPixmap pumpStatImage{p_pumpStatShape->image()};
    QVERIFY2(!pumpStatImage.isNull(), "pumpStatShape::image() returned a null pixmap");
    QCOMPARE(pumpStatImage.width(), p_pumpStatShape->boundingRect().width());
    QCOMPARE(pumpStatImage.height(), p_pumpStatShape->boundingRect().height());
    TechnicsShape::TechnicsShapeDeleter::cleanup(p_pumpStatShape);

    // LafetTankerShape
    TechnicsShape *p_lafetTankerShape = TechnicsShape::createTechnicsShape(TechnicsShape::LafetTanker);
    QPixmap lafetTankerImage{p_lafetTankerShape->image()};
    QVERIFY2(!lafetTankerImage.isNull(), "lafetTankerShape::image() returned a null pixmap");
    QCOMPARE(lafetTankerImage.width(), p_lafetTankerShape->boundingRect().width());
    QCOMPARE(lafetTankerImage.height(), p_lafetTankerShape->boundingRect().height());
    TechnicsShape::TechnicsShapeDeleter::cleanup(p_lafetTankerShape);

    // LafetCarShape
    TechnicsShape *p_lafetCarShape = TechnicsShape::createTechnicsShape(TechnicsShape::LafetCar);
    QPixmap lafetCarImage{p_lafetCarShape->image()};
    QVERIFY2(!lafetCarImage.isNull(), "lafetCarShape::image() returned a null pixmap");
    QCOMPARE(lafetCarImage.width(), p_lafetCarShape->boundingRect().width());
    QCOMPARE(lafetCarImage.height(), p_lafetCarShape->boundingRect().height());
    TechnicsShape::TechnicsShapeDeleter::cleanup(p_lafetCarShape);

    // AerodromeShape
    TechnicsShape *p_aerodromeShape = TechnicsShape::createTechnicsShape(TechnicsShape::Aerodrome);
    QPixmap aerodromeImage{p_aerodromeShape->image()};
    QVERIFY2(!aerodromeImage.isNull(), "aerodromeShape::image() returned a null pixmap");
    QCOMPARE(aerodromeImage.width(), p_aerodromeShape->boundingRect().width());
    QCOMPARE(aerodromeImage.height(), p_aerodromeShape->boundingRect().height());
    TechnicsShape::TechnicsShapeDeleter::cleanup(p_aerodromeShape);

    // FoamShape
    TechnicsShape *p_foamShape = TechnicsShape::createTechnicsShape(TechnicsShape::Foam);
    QPixmap foamImage{p_foamShape->image()};
    QVERIFY2(!foamImage.isNull(), "foamShape::image() returned a null pixmap");
    QCOMPARE(foamImage.width(), p_foamShape->boundingRect().width());
    QCOMPARE(foamImage.height(), p_foamShape->boundingRect().height());
    TechnicsShape::TechnicsShapeDeleter::cleanup(p_foamShape);

    // ComboShape
    TechnicsShape *p_comboShape = TechnicsShape::createTechnicsShape(TechnicsShape::Combo);
    QPixmap comboImage{p_comboShape->image()};
    QVERIFY2(!comboImage.isNull(), "comboShape::image() returned a null pixmap");
    QCOMPARE(comboImage.width(), p_comboShape->boundingRect().width());
    QCOMPARE(comboImage.height(), p_comboShape->boundingRect().height());
    TechnicsShape::TechnicsShapeDeleter::cleanup(p_comboShape);

    // AerosolShape
    TechnicsShape *p_aerosolShape = TechnicsShape::createTechnicsShape(TechnicsShape::Aerosol);
    QPixmap aerosolImage{p_aerosolShape->image()};
    QVERIFY2(!aerosolImage.isNull(), "aerosolShape::image() returned a null pixmap");
    QCOMPARE(aerosolImage.width(), p_aerosolShape->boundingRect().width());
    QCOMPARE(aerosolImage.height(), p_aerosolShape->boundingRect().height());
    TechnicsShape::TechnicsShapeDeleter::cleanup(p_aerosolShape);

    // PowderShape
    TechnicsShape *p_powderShape = TechnicsShape::createTechnicsShape(TechnicsShape::Powder);
    QPixmap powderImage{p_powderShape->image()};
    QVERIFY2(!powderImage.isNull(), "powderShape::image() returned a null pixmap");
    QCOMPARE(powderImage.width(), p_powderShape->boundingRect().width());
    QCOMPARE(powderImage.height(), p_powderShape->boundingRect().height());
    TechnicsShape::TechnicsShapeDeleter::cleanup(p_powderShape);

    // CarbonShape
    TechnicsShape *p_carbonShape = TechnicsShape::createTechnicsShape(TechnicsShape::Carbon);
    QPixmap carbonImage{p_carbonShape->image()};
    QVERIFY2(!carbonImage.isNull(), "carbonShape::image() returned a null pixmap");
    QCOMPARE(carbonImage.width(), p_carbonShape->boundingRect().width());
    QCOMPARE(carbonImage.height(), p_carbonShape->boundingRect().height());
    TechnicsShape::TechnicsShapeDeleter::cleanup(p_carbonShape);

    // GazWaterShape
    TechnicsShape *p_gazWaterShape = TechnicsShape::createTechnicsShape(TechnicsShape::GazWater);
    QPixmap gazWaterImage{p_gazWaterShape->image()};
    QVERIFY2(!gazWaterImage.isNull(), "gazWaterShape::image() returned a null pixmap");
    QCOMPARE(gazWaterImage.width(), p_gazWaterShape->boundingRect().width());
    QCOMPARE(gazWaterImage.height(), p_gazWaterShape->boundingRect().height());
    TechnicsShape::TechnicsShapeDeleter::cleanup(p_gazWaterShape);
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

    // TechServShape
    TechnicsShape *p_techServShape = TechnicsShape::createTechnicsShape(TechnicsShape::TechServ);
    p_techServShape->setRect(rect);
    QCOMPARE(p_techServShape->rect(), rect);
    TechnicsShape::TechnicsShapeDeleter::cleanup(p_techServShape);

    // SmokRemShape
    TechnicsShape *p_smokRemShape = TechnicsShape::createTechnicsShape(TechnicsShape::SmokRem);
    p_smokRemShape->setRect(rect);
    QCOMPARE(p_smokRemShape->rect(), rect);
    TechnicsShape::TechnicsShapeDeleter::cleanup(p_smokRemShape);

    // PumpStatShape
    TechnicsShape *p_pumpStatShape = TechnicsShape::createTechnicsShape(TechnicsShape::PumpStat);
    p_pumpStatShape->setRect(rect);
    QCOMPARE(p_pumpStatShape->rect(), rect);
    TechnicsShape::TechnicsShapeDeleter::cleanup(p_pumpStatShape);

    // LafetTankerShape
    TechnicsShape *p_lafetTankerShape = TechnicsShape::createTechnicsShape(TechnicsShape::LafetTanker);
    p_lafetTankerShape->setRect(rect);
    QCOMPARE(p_lafetTankerShape->rect(), rect);
    TechnicsShape::TechnicsShapeDeleter::cleanup(p_lafetTankerShape);

    // LafetCarShape
    TechnicsShape *p_lafetCarShape = TechnicsShape::createTechnicsShape(TechnicsShape::LafetCar);
    p_lafetCarShape->setRect(rect);
    QCOMPARE(p_lafetCarShape->rect(), rect);
    TechnicsShape::TechnicsShapeDeleter::cleanup(p_lafetCarShape);

    // AerodromeShape
    TechnicsShape *p_aerodromeShape = TechnicsShape::createTechnicsShape(TechnicsShape::Aerodrome);
    p_aerodromeShape->setRect(rect);
    QCOMPARE(p_aerodromeShape->rect(), rect);
    TechnicsShape::TechnicsShapeDeleter::cleanup(p_aerodromeShape);

    // FoamShape
    TechnicsShape *p_foamShape = TechnicsShape::createTechnicsShape(TechnicsShape::Foam);
    p_foamShape->setRect(rect);
    QCOMPARE(p_foamShape->rect(), rect);
    TechnicsShape::TechnicsShapeDeleter::cleanup(p_foamShape);

    // ComboShape
    TechnicsShape *p_comboShape = TechnicsShape::createTechnicsShape(TechnicsShape::Combo);
    p_comboShape->setRect(rect);
    QCOMPARE(p_comboShape->rect(), rect);
    TechnicsShape::TechnicsShapeDeleter::cleanup(p_comboShape);

    // AerosolShape
    TechnicsShape *p_aerosolShape = TechnicsShape::createTechnicsShape(TechnicsShape::Aerosol);
    p_aerosolShape->setRect(rect);
    QCOMPARE(p_aerosolShape->rect(), rect);
    TechnicsShape::TechnicsShapeDeleter::cleanup(p_aerosolShape);

    // PowderShape
    TechnicsShape *p_powderShape = TechnicsShape::createTechnicsShape(TechnicsShape::Powder);
    p_powderShape->setRect(rect);
    QCOMPARE(p_powderShape->rect(), rect);
    TechnicsShape::TechnicsShapeDeleter::cleanup(p_powderShape);

    // GazWaterShape
    TechnicsShape *p_gazWaterShape = TechnicsShape::createTechnicsShape(TechnicsShape::GazWater);
    p_gazWaterShape->setRect(rect);
    QCOMPARE(p_gazWaterShape->rect(), rect);
    TechnicsShape::TechnicsShapeDeleter::cleanup(p_gazWaterShape);
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

    // SmokRemShape
    TechnicsShape *p_smokRemShape = TechnicsShape::createTechnicsShape(TechnicsShape::SmokRem);
    p_smokRemShape->setHeight(height);
    QCOMPARE(p_smokRemShape->height(), height);
    TechnicsShape::TechnicsShapeDeleter::cleanup(p_smokRemShape);

    // PumpStatShape
    TechnicsShape *p_pumpStatShape = TechnicsShape::createTechnicsShape(TechnicsShape::PumpStat);
    p_pumpStatShape->setHeight(height);
    QCOMPARE(p_pumpStatShape->height(), height);
    TechnicsShape::TechnicsShapeDeleter::cleanup(p_pumpStatShape);

    // LafetTankerShape
    TechnicsShape *p_lafetTankerShape = TechnicsShape::createTechnicsShape(TechnicsShape::LafetTanker);
    p_lafetTankerShape->setHeight(height);
    QCOMPARE(p_lafetTankerShape->height(), height);
    TechnicsShape::TechnicsShapeDeleter::cleanup(p_lafetTankerShape);

    // LafetCarShape
    TechnicsShape *p_lafetCarShape = TechnicsShape::createTechnicsShape(TechnicsShape::LafetCar);
    p_lafetCarShape->setHeight(height);
    QCOMPARE(p_lafetCarShape->height(), height);
    TechnicsShape::TechnicsShapeDeleter::cleanup(p_lafetCarShape);

    // AerodromeShape
    TechnicsShape *p_aerodromeShape = TechnicsShape::createTechnicsShape(TechnicsShape::Aerodrome);
    p_aerodromeShape->setHeight(height);
    QCOMPARE(p_aerodromeShape->height(), height);
    TechnicsShape::TechnicsShapeDeleter::cleanup(p_aerodromeShape);

    // FoamShape
    TechnicsShape *p_foamShape = TechnicsShape::createTechnicsShape(TechnicsShape::Foam);
    p_foamShape->setHeight(height);
    QCOMPARE(p_foamShape->height(), height);
    TechnicsShape::TechnicsShapeDeleter::cleanup(p_foamShape);

    // ComboShape
    TechnicsShape *p_comboShape = TechnicsShape::createTechnicsShape(TechnicsShape::Combo);
    p_comboShape->setHeight(height);
    QCOMPARE(p_comboShape->height(), height);
    TechnicsShape::TechnicsShapeDeleter::cleanup(p_comboShape);

    // AerosolShape
    TechnicsShape *p_aerosolShape = TechnicsShape::createTechnicsShape(TechnicsShape::Aerosol);
    p_aerosolShape->setHeight(height);
    QCOMPARE(p_aerosolShape->height(), height);
    TechnicsShape::TechnicsShapeDeleter::cleanup(p_aerosolShape);

    // PowderShape
    TechnicsShape *p_powderShape = TechnicsShape::createTechnicsShape(TechnicsShape::Powder);
    p_powderShape->setHeight(height);
    QCOMPARE(p_powderShape->height(), height);
    TechnicsShape::TechnicsShapeDeleter::cleanup(p_powderShape);

    // CarbonShape
    TechnicsShape *p_carbonShape = TechnicsShape::createTechnicsShape(TechnicsShape::Carbon);
    p_carbonShape->setHeight(height);
    QCOMPARE(p_carbonShape->height(), height);
    TechnicsShape::TechnicsShapeDeleter::cleanup(p_carbonShape);

    // GazWaterShape
    TechnicsShape *p_gazWaterShape = TechnicsShape::createTechnicsShape(TechnicsShape::GazWater);
    p_gazWaterShape->setHeight(height);
    QCOMPARE(p_gazWaterShape->height(), height);
    TechnicsShape::TechnicsShapeDeleter::cleanup(p_gazWaterShape);
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

    // TechServShape
    TechnicsShape *p_techServShape = TechnicsShape::createTechnicsShape(TechnicsShape::TechServ);
    p_techServShape->setText(text);
    QCOMPARE(p_techServShape->text(), text);
    TechnicsShape::TechnicsShapeDeleter::cleanup(p_techServShape);

    // SmokRemShape
    TechnicsShape *p_smokRemShape = TechnicsShape::createTechnicsShape(TechnicsShape::SmokRem);
    p_smokRemShape->setText(text);
    QCOMPARE(p_smokRemShape->text(), text);
    TechnicsShape::TechnicsShapeDeleter::cleanup(p_smokRemShape);

    // PumpStatShape
    TechnicsShape *p_pumpStatShape = TechnicsShape::createTechnicsShape(TechnicsShape::PumpStat);
    p_pumpStatShape->setText(text);
    QCOMPARE(p_pumpStatShape->text(), text);
    TechnicsShape::TechnicsShapeDeleter::cleanup(p_pumpStatShape);

    // LafetTankerShape
    TechnicsShape *p_lafetTankerShape = TechnicsShape::createTechnicsShape(TechnicsShape::LafetTanker);
    p_lafetTankerShape->setText(text);
    QCOMPARE(p_lafetTankerShape->text(), text);
    TechnicsShape::TechnicsShapeDeleter::cleanup(p_lafetTankerShape);

    // LafetCarShape
    TechnicsShape *p_lafetCarShape = TechnicsShape::createTechnicsShape(TechnicsShape::LafetCar);
    p_lafetCarShape->setText(text);
    QCOMPARE(p_lafetCarShape->text(), text);
    TechnicsShape::TechnicsShapeDeleter::cleanup(p_lafetCarShape);

    // AerodromeShape
    TechnicsShape *p_aerodromeShape = TechnicsShape::createTechnicsShape(TechnicsShape::Aerodrome);
    p_aerodromeShape->setText(text);
    QCOMPARE(p_aerodromeShape->text(), text);
    TechnicsShape::TechnicsShapeDeleter::cleanup(p_aerodromeShape);

    // FoamShape
    TechnicsShape *p_foamShape = TechnicsShape::createTechnicsShape(TechnicsShape::Foam);
    p_foamShape->setText(text);
    QCOMPARE(p_foamShape->text(), text);
    TechnicsShape::TechnicsShapeDeleter::cleanup(p_foamShape);

    // ComboShape
    TechnicsShape *p_comboShape = TechnicsShape::createTechnicsShape(TechnicsShape::Combo);
    p_comboShape->setText(text);
    QCOMPARE(p_comboShape->text(), text);
    TechnicsShape::TechnicsShapeDeleter::cleanup(p_comboShape);

    // AerosolShape
    TechnicsShape *p_aerosolShape = TechnicsShape::createTechnicsShape(TechnicsShape::Aerosol);
    p_aerosolShape->setText(text);
    QCOMPARE(p_aerosolShape->text(), text);
    TechnicsShape::TechnicsShapeDeleter::cleanup(p_aerosolShape);

    // PowderShape
    TechnicsShape *p_powderShape = TechnicsShape::createTechnicsShape(TechnicsShape::Powder);
    p_powderShape->setText(text);
    QCOMPARE(p_powderShape->text(), text);
    TechnicsShape::TechnicsShapeDeleter::cleanup(p_powderShape);

    // CarbonShape
    TechnicsShape *p_carbonShape = TechnicsShape::createTechnicsShape(TechnicsShape::Carbon);
    p_carbonShape->setText(text);
    QCOMPARE(p_carbonShape->text(), text);
    TechnicsShape::TechnicsShapeDeleter::cleanup(p_carbonShape);

    // GazWaterShape
    TechnicsShape *p_gazWaterShape = TechnicsShape::createTechnicsShape(TechnicsShape::GazWater);
    p_gazWaterShape->setText(text);
    QCOMPARE(p_gazWaterShape->text(), text);
    TechnicsShape::TechnicsShapeDeleter::cleanup(p_gazWaterShape);
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

    //PumpStatShape
    TechnicsShape *p_pumpStatShape = TechnicsShape::createTechnicsShape(TechnicsShape::PumpStat);
    PumpStatShape *p_pumpStat = dynamic_cast<PumpStatShape *>(p_pumpStatShape);
    QCOMPARE(p_pumpStat->pipes(), false);
    p_pumpStat->setPipes(true);
    QCOMPARE(p_pumpStat->pipes(), true);
    p_pumpStat->setPipes(false);
    QCOMPARE(p_pumpStat->pipes(), false);
    p_pumpStat = nullptr;
    TechnicsShape::TechnicsShapeDeleter::cleanup(p_pumpStatShape);

    //LafetTankerShape
    TechnicsShape *p_lafetTankerShape = TechnicsShape::createTechnicsShape(TechnicsShape::LafetTanker);
    LafetTankerShape *p_lafetTanker = dynamic_cast<LafetTankerShape *>(p_lafetTankerShape);
    QCOMPARE(p_lafetTanker->pipes(), false);
    p_lafetTanker->setPipes(true);
    QCOMPARE(p_lafetTanker->pipes(), true);
    p_lafetTanker->setPipes(false);
    QCOMPARE(p_lafetTanker->pipes(), false);
    p_lafetTanker = nullptr;
    TechnicsShape::TechnicsShapeDeleter::cleanup(p_lafetTankerShape);

    //AerodromeShape
    TechnicsShape *p_aerodromeShape = TechnicsShape::createTechnicsShape(TechnicsShape::Aerodrome);
    AerodromeShape *p_aerodrome = dynamic_cast<AerodromeShape *>(p_aerodromeShape);
    QCOMPARE(p_aerodrome->pipes(), false);
    p_aerodrome->setPipes(true);
    QCOMPARE(p_aerodrome->pipes(), true);
    p_aerodrome->setPipes(false);
    QCOMPARE(p_aerodrome->pipes(), false);
    p_aerodrome = nullptr;
    TechnicsShape::TechnicsShapeDeleter::cleanup(p_aerodromeShape);

    //FoamShape
    TechnicsShape *p_foamShape = TechnicsShape::createTechnicsShape(TechnicsShape::Foam);
    FoamShape *p_foam = dynamic_cast<FoamShape *>(p_foamShape);
    QCOMPARE(p_foam->pipes(), false);
    p_foam->setPipes(true);
    QCOMPARE(p_foam->pipes(), true);
    p_foam->setPipes(false);
    QCOMPARE(p_foam->pipes(), false);
    p_foam = nullptr;
    TechnicsShape::TechnicsShapeDeleter::cleanup(p_foamShape);

    //ComboShape
    TechnicsShape *p_comboShape = TechnicsShape::createTechnicsShape(TechnicsShape::Combo);
    ComboShape *p_combo = dynamic_cast<ComboShape *>(p_comboShape);
    QCOMPARE(p_combo->pipes(), false);
    p_combo->setPipes(true);
    QCOMPARE(p_combo->pipes(), true);
    p_combo->setPipes(false);
    QCOMPARE(p_combo->pipes(), false);
    p_combo = nullptr;
    TechnicsShape::TechnicsShapeDeleter::cleanup(p_comboShape);
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

    //PumpStatShape
    TechnicsShape *p_pumpStatShape = TechnicsShape::createTechnicsShape(TechnicsShape::PumpStat);
    PumpStatShape *p_pumpStat = dynamic_cast<PumpStatShape *>(p_pumpStatShape);
    QCOMPARE(p_pumpStat->collector(), false);
    p_pumpStat->setCollector(true);
    QCOMPARE(p_pumpStat->collector(), true);
    p_pumpStat->setCollector(false);
    QCOMPARE(p_pumpStat->collector(), false);
    p_pumpStat = nullptr;
    TechnicsShape::TechnicsShapeDeleter::cleanup(p_pumpStatShape);

    //LafetTankerShape
    TechnicsShape *p_lafetTankerShape = TechnicsShape::createTechnicsShape(TechnicsShape::LafetTanker);
    LafetTankerShape *p_lafetTanker = dynamic_cast<LafetTankerShape *>(p_lafetTankerShape);
    QCOMPARE(p_lafetTanker->collector(), false);
    p_lafetTanker->setCollector(true);
    QCOMPARE(p_lafetTanker->collector(), true);
    p_lafetTanker->setCollector(false);
    QCOMPARE(p_lafetTanker->collector(), false);
    p_lafetTanker = nullptr;
    TechnicsShape::TechnicsShapeDeleter::cleanup(p_lafetTankerShape);

    //AerodromeShape
    TechnicsShape *p_aerodromeShape = TechnicsShape::createTechnicsShape(TechnicsShape::Aerodrome);
    AerodromeShape *p_aerodrome = dynamic_cast<AerodromeShape *>(p_aerodromeShape);
    QCOMPARE(p_aerodrome->collector(), false);
    p_aerodrome->setCollector(true);
    QCOMPARE(p_aerodrome->collector(), true);
    p_aerodrome->setCollector(false);
    QCOMPARE(p_aerodrome->collector(), false);
    p_aerodrome = nullptr;
    TechnicsShape::TechnicsShapeDeleter::cleanup(p_aerodromeShape);

    //FoamShape
    TechnicsShape *p_foamShape = TechnicsShape::createTechnicsShape(TechnicsShape::Foam);
    FoamShape *p_foam = dynamic_cast<FoamShape *>(p_foamShape);
    QCOMPARE(p_foam->collector(), false);
    p_foam->setCollector(true);
    QCOMPARE(p_foam->collector(), true);
    p_foam->setCollector(false);
    QCOMPARE(p_foam->collector(), false);
    p_foam = nullptr;
    TechnicsShape::TechnicsShapeDeleter::cleanup(p_foamShape);

    //ComboShape
    TechnicsShape *p_comboShape = TechnicsShape::createTechnicsShape(TechnicsShape::Combo);
    ComboShape *p_combo = dynamic_cast<ComboShape *>(p_comboShape);
    QCOMPARE(p_combo->collector(), false);
    p_combo->setCollector(true);
    QCOMPARE(p_combo->collector(), true);
    p_combo->setCollector(false);
    QCOMPARE(p_combo->collector(), false);
    p_combo = nullptr;
    TechnicsShape::TechnicsShapeDeleter::cleanup(p_comboShape);
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

    // TechServShape
    ContextMenuTester *p_techServContextMenu = new ContextMenuTester();

    TechnicsShape *p_techServShape = TechnicsShape::createTechnicsShape(TechnicsShape::TechServ);
    p_techServShape->setMenu(p_techServContextMenu);
    scene.addItem(p_techServShape);

    mousePressEvent.setScenePos(p_techServShape->pos());
    QApplication::sendEvent(&scene, &mousePressEvent);
    QVERIFY(mousePressEvent.isAccepted());

    p_techServShape->setSelected(true);
    QSignalSpy techServContextMenuSpy(p_techServShape->menu(), &QMenu::aboutToShow);
    QCOMPARE(techServContextMenuSpy.count(), 0);

    QList<QAction *> techServMenuActions{p_techServShape->menu()->actions()};
    QCOMPARE(techServMenuActions.size(), 1);
    techServMenuActions.clear();

    QTest::mouseClick(view.viewport(), Qt::RightButton, Qt::NoModifier
                      , view.mapFromScene(p_techServShape->boundingRect().center()));
    techServMenuActions = p_techServShape->menu()->actions();
    QCOMPARE(techServMenuActions.size(), 1);
    QCOMPARE(techServContextMenuSpy.count(), 1);

    scene.removeItem(p_techServShape);
    delete p_techServContextMenu;
    TechnicsShape::TechnicsShapeDeleter::cleanup(p_techServShape);

    // SmokRemShape
    ContextMenuTester *p_smokRemContextMenu = new ContextMenuTester();

    TechnicsShape *p_smokRemShape = TechnicsShape::createTechnicsShape(TechnicsShape::SmokRem);
    p_smokRemShape->setMenu(p_smokRemContextMenu);
    scene.addItem(p_smokRemShape);

    mousePressEvent.setScenePos(p_smokRemShape->pos());
    QApplication::sendEvent(&scene, &mousePressEvent);
    QVERIFY(mousePressEvent.isAccepted());

    p_smokRemShape->setSelected(true);
    QSignalSpy smokRemContextMenuSpy(p_smokRemShape->menu(), &QMenu::aboutToShow);
    QCOMPARE(smokRemContextMenuSpy.count(), 0);

    QList<QAction *> smokRemMenuActions{p_smokRemShape->menu()->actions()};
    QCOMPARE(smokRemMenuActions.size(), 1);
    smokRemMenuActions.clear();

    QTest::mouseClick(view.viewport(), Qt::RightButton, Qt::NoModifier
                      , view.mapFromScene(p_smokRemShape->boundingRect().center()));
    smokRemMenuActions = p_smokRemShape->menu()->actions();
    QCOMPARE(smokRemMenuActions.size(), 1);
    QCOMPARE(smokRemContextMenuSpy.count(), 1);

    scene.removeItem(p_smokRemShape);
    delete p_smokRemContextMenu;
    TechnicsShape::TechnicsShapeDeleter::cleanup(p_smokRemShape);

    // PumpStatShape
    ContextMenuTester *p_pumpstatContextMenu = new ContextMenuTester();

    TechnicsShape *p_pumpStatShape = TechnicsShape::createTechnicsShape(TechnicsShape::PumpStat);
    p_pumpStatShape->setMenu(p_pumpstatContextMenu);
    scene.addItem(p_pumpStatShape);

    mousePressEvent.setScenePos(p_pumpStatShape->pos());
    QApplication::sendEvent(&scene, &mousePressEvent);
    QVERIFY(mousePressEvent.isAccepted());

    p_pumpStatShape->setSelected(true);
    QSignalSpy pumpStatContextMenuSpy(p_pumpStatShape->menu(), &QMenu::aboutToShow);
    QCOMPARE(pumpStatContextMenuSpy.count(), 0);

    QList<QAction *> pumpStatMenuActions{p_pumpStatShape->menu()->actions()};
    QCOMPARE(pumpStatMenuActions.size(), 1);
    pumpStatMenuActions.clear();

    QTest::mouseClick(view.viewport(), Qt::RightButton, Qt::NoModifier
                      , view.mapFromScene(p_pumpStatShape->boundingRect().center()));
    pumpStatMenuActions = p_pumpStatShape->menu()->actions();
    QCOMPARE(pumpStatMenuActions.size(), 1);
    QCOMPARE(pumpStatContextMenuSpy.count(), 1);

    scene.removeItem(p_pumpStatShape);
    delete p_pumpstatContextMenu;
    TechnicsShape::TechnicsShapeDeleter::cleanup(p_pumpStatShape);

    // LafetTankerShape
    ContextMenuTester *p_lafetTankerContextMenu = new ContextMenuTester();

    TechnicsShape *p_lafetTankerShape = TechnicsShape::createTechnicsShape(TechnicsShape::LafetTanker);
    p_lafetTankerShape->setMenu(p_lafetTankerContextMenu);
    scene.addItem(p_lafetTankerShape);

    mousePressEvent.setScenePos(p_lafetTankerShape->pos());
    QApplication::sendEvent(&scene, &mousePressEvent);
    QVERIFY(mousePressEvent.isAccepted());

    p_lafetTankerShape->setSelected(true);
    QSignalSpy lafetTankerContextMenuSpy(p_lafetTankerShape->menu(), &QMenu::aboutToShow);
    QCOMPARE(lafetTankerContextMenuSpy.count(), 0);

    QList<QAction *> lafetTankerMenuActions{p_lafetTankerShape->menu()->actions()};
    QCOMPARE(lafetTankerMenuActions.size(), 1);
    lafetTankerMenuActions.clear();

    QTest::mouseClick(view.viewport(), Qt::RightButton, Qt::NoModifier
                      , view.mapFromScene(p_lafetTankerShape->boundingRect().center()));
    lafetTankerMenuActions = p_lafetTankerShape->menu()->actions();
    QCOMPARE(lafetTankerMenuActions.size(), 1);
    QCOMPARE(lafetTankerContextMenuSpy.count(), 1);

    scene.removeItem(p_lafetTankerShape);
    delete p_lafetTankerContextMenu;
    TechnicsShape::TechnicsShapeDeleter::cleanup(p_lafetTankerShape);

    // LafetCarShape
    ContextMenuTester *p_lafetCarContextMenu = new ContextMenuTester();

    TechnicsShape *p_lafetCarShape = TechnicsShape::createTechnicsShape(TechnicsShape::LafetCar);
    p_lafetCarShape->setMenu(p_lafetCarContextMenu);
    scene.addItem(p_lafetCarShape);

    mousePressEvent.setScenePos(p_lafetCarShape->pos());
    QApplication::sendEvent(&scene, &mousePressEvent);
    QVERIFY(mousePressEvent.isAccepted());

    p_lafetCarShape->setSelected(true);
    QSignalSpy lafetCarContextMenuSpy(p_lafetCarShape->menu(), &QMenu::aboutToShow);
    QCOMPARE(lafetCarContextMenuSpy.count(), 0);

    QList<QAction *> lafetCarMenuActions{p_lafetCarShape->menu()->actions()};
    QCOMPARE(lafetCarMenuActions.size(), 1);
    lafetCarMenuActions.clear();

    QTest::mouseClick(view.viewport(), Qt::RightButton, Qt::NoModifier
                      , view.mapFromScene(p_lafetCarShape->boundingRect().center()));
    lafetCarMenuActions = p_lafetCarShape->menu()->actions();
    QCOMPARE(lafetCarMenuActions.size(), 1);
    QCOMPARE(lafetCarContextMenuSpy.count(), 1);

    scene.removeItem(p_lafetCarShape);
    delete p_lafetCarContextMenu;
    TechnicsShape::TechnicsShapeDeleter::cleanup(p_lafetCarShape);

    // AerodromeShape
    ContextMenuTester *p_aerodromeContextMenu = new ContextMenuTester();

    TechnicsShape *p_aerodromeShape = TechnicsShape::createTechnicsShape(TechnicsShape::Aerodrome);
    p_aerodromeShape->setMenu(p_aerodromeContextMenu);
    scene.addItem(p_aerodromeShape);

    mousePressEvent.setScenePos(p_aerodromeShape->pos());
    QApplication::sendEvent(&scene, &mousePressEvent);
    QVERIFY(mousePressEvent.isAccepted());

    p_aerodromeShape->setSelected(true);
    QSignalSpy aerodromeContextMenuSpy(p_aerodromeShape->menu(), &QMenu::aboutToShow);
    QCOMPARE(aerodromeContextMenuSpy.count(), 0);

    QList<QAction *> aerodromeMenuActions{p_aerodromeShape->menu()->actions()};
    QCOMPARE(aerodromeMenuActions.size(), 1);
    aerodromeMenuActions.clear();

    QTest::mouseClick(view.viewport(), Qt::RightButton, Qt::NoModifier
                      , view.mapFromScene(p_aerodromeShape->boundingRect().center()));
    aerodromeMenuActions = p_aerodromeShape->menu()->actions();
    QCOMPARE(aerodromeMenuActions.size(), 1);
    QCOMPARE(aerodromeContextMenuSpy.count(), 1);

    scene.removeItem(p_aerodromeShape);
    delete p_aerodromeContextMenu;
    TechnicsShape::TechnicsShapeDeleter::cleanup(p_aerodromeShape);

    // FoamShape
    ContextMenuTester *p_foamContextMenu = new ContextMenuTester();

    TechnicsShape *p_foamShape = TechnicsShape::createTechnicsShape(TechnicsShape::Foam);
    p_foamShape->setMenu(p_foamContextMenu);
    scene.addItem(p_foamShape);

    mousePressEvent.setScenePos(p_foamShape->pos());
    QApplication::sendEvent(&scene, &mousePressEvent);
    QVERIFY(mousePressEvent.isAccepted());

    p_foamShape->setSelected(true);
    QSignalSpy foamContextMenuSpy(p_foamShape->menu(), &QMenu::aboutToShow);
    QCOMPARE(foamContextMenuSpy.count(), 0);

    QList<QAction *> foamMenuActions{p_foamShape->menu()->actions()};
    QCOMPARE(foamMenuActions.size(), 1);
    foamMenuActions.clear();

    QTest::mouseClick(view.viewport(), Qt::RightButton, Qt::NoModifier
                      , view.mapFromScene(p_foamShape->boundingRect().center()));
    foamMenuActions = p_foamShape->menu()->actions();
    QCOMPARE(foamMenuActions.size(), 1);
    QCOMPARE(foamContextMenuSpy.count(), 1);

    scene.removeItem(p_foamShape);
    delete p_foamContextMenu;
    TechnicsShape::TechnicsShapeDeleter::cleanup(p_foamShape);

    // ComboShape
    ContextMenuTester *p_comboContextMenu = new ContextMenuTester();

    TechnicsShape *p_comboShape = TechnicsShape::createTechnicsShape(TechnicsShape::Combo);
    p_comboShape->setMenu(p_comboContextMenu);
    scene.addItem(p_comboShape);

    mousePressEvent.setScenePos(p_comboShape->pos());
    QApplication::sendEvent(&scene, &mousePressEvent);
    QVERIFY(mousePressEvent.isAccepted());

    p_comboShape->setSelected(true);
    QSignalSpy comboContextMenuSpy(p_comboShape->menu(), &QMenu::aboutToShow);
    QCOMPARE(comboContextMenuSpy.count(), 0);

    QList<QAction *> comboMenuActions{p_comboShape->menu()->actions()};
    QCOMPARE(comboMenuActions.size(), 1);
    comboMenuActions.clear();

    QTest::mouseClick(view.viewport(), Qt::RightButton, Qt::NoModifier
                      , view.mapFromScene(p_comboShape->boundingRect().center()));
    comboMenuActions = p_comboShape->menu()->actions();
    QCOMPARE(comboMenuActions.size(), 1);
    QCOMPARE(comboContextMenuSpy.count(), 1);

    scene.removeItem(p_comboShape);
    delete p_comboContextMenu;
    TechnicsShape::TechnicsShapeDeleter::cleanup(p_comboShape);

    // AerosolShape
    ContextMenuTester *p_aerosolContextMenu = new ContextMenuTester();

    TechnicsShape *p_aerosolShape = TechnicsShape::createTechnicsShape(TechnicsShape::Aerosol);
    p_aerosolShape->setMenu(p_aerosolContextMenu);
    scene.addItem(p_aerosolShape);

    mousePressEvent.setScenePos(p_aerosolShape->pos());
    QApplication::sendEvent(&scene, &mousePressEvent);
    QVERIFY(mousePressEvent.isAccepted());

    p_aerosolShape->setSelected(true);
    QSignalSpy aerosolContextMenuSpy(p_aerosolShape->menu(), &QMenu::aboutToShow);
    QCOMPARE(aerosolContextMenuSpy.count(), 0);

    QList<QAction *> aerosolMenuActions{p_aerosolShape->menu()->actions()};
    QCOMPARE(aerosolMenuActions.size(), 1);
    aerosolMenuActions.clear();

    QTest::mouseClick(view.viewport(), Qt::RightButton, Qt::NoModifier
                      , view.mapFromScene(p_aerosolShape->boundingRect().center()));
    aerosolMenuActions = p_aerosolShape->menu()->actions();
    QCOMPARE(aerosolMenuActions.size(), 1);
    QCOMPARE(aerosolContextMenuSpy.count(), 1);

    scene.removeItem(p_aerosolShape);
    delete p_aerosolContextMenu;
    TechnicsShape::TechnicsShapeDeleter::cleanup(p_aerosolShape);

    // PowderShape
    ContextMenuTester *p_powderContextMenu = new ContextMenuTester();

    TechnicsShape *p_powderShape = TechnicsShape::createTechnicsShape(TechnicsShape::Powder);
    p_powderShape->setMenu(p_powderContextMenu);
    scene.addItem(p_powderShape);

    mousePressEvent.setScenePos(p_powderShape->pos());
    QApplication::sendEvent(&scene, &mousePressEvent);
    QVERIFY(mousePressEvent.isAccepted());

    p_powderShape->setSelected(true);
    QSignalSpy powderContextMenuSpy(p_powderShape->menu(), &QMenu::aboutToShow);
    QCOMPARE(powderContextMenuSpy.count(), 0);

    QList<QAction *> powderMenuActions{p_powderShape->menu()->actions()};
    QCOMPARE(powderMenuActions.size(), 1);
    powderMenuActions.clear();

    QTest::mouseClick(view.viewport(), Qt::RightButton, Qt::NoModifier
                      , view.mapFromScene(p_powderShape->boundingRect().center()));
    powderMenuActions = p_powderShape->menu()->actions();
    QCOMPARE(powderMenuActions.size(), 1);
    QCOMPARE(powderContextMenuSpy.count(), 1);

    scene.removeItem(p_powderShape);
    delete p_powderContextMenu;
    TechnicsShape::TechnicsShapeDeleter::cleanup(p_powderShape);

    // CarbonShape
    ContextMenuTester *p_carbonContextMenu = new ContextMenuTester();

    TechnicsShape *p_carbonShape = TechnicsShape::createTechnicsShape(TechnicsShape::Carbon);
    p_carbonShape->setMenu(p_carbonContextMenu);
    scene.addItem(p_carbonShape);

    mousePressEvent.setScenePos(p_carbonShape->pos());
    QApplication::sendEvent(&scene, &mousePressEvent);
    QVERIFY(mousePressEvent.isAccepted());

    p_carbonShape->setSelected(true);
    QSignalSpy carbonContextMenuSpy(p_carbonShape->menu(), &QMenu::aboutToShow);
    QCOMPARE(carbonContextMenuSpy.count(), 0);

    QList<QAction *> carbonMenuActions{p_carbonShape->menu()->actions()};
    QCOMPARE(carbonMenuActions.size(), 1);
    carbonMenuActions.clear();

    QTest::mouseClick(view.viewport(), Qt::RightButton, Qt::NoModifier
                      , view.mapFromScene(p_carbonShape->boundingRect().center()));
    carbonMenuActions = p_carbonShape->menu()->actions();
    QCOMPARE(carbonMenuActions.size(), 1);
    QCOMPARE(carbonContextMenuSpy.count(), 1);

    scene.removeItem(p_carbonShape);
    delete p_carbonContextMenu;
    TechnicsShape::TechnicsShapeDeleter::cleanup(p_carbonShape);

    // GazWaterShape
    ContextMenuTester *p_gazWaterContextMenu = new ContextMenuTester();

    TechnicsShape *p_gazWaterShape = TechnicsShape::createTechnicsShape(TechnicsShape::GazWater);
    p_gazWaterShape->setMenu(p_gazWaterContextMenu);
    scene.addItem(p_gazWaterShape);

    mousePressEvent.setScenePos(p_gazWaterShape->pos());
    QApplication::sendEvent(&scene, &mousePressEvent);
    QVERIFY(mousePressEvent.isAccepted());

    p_gazWaterShape->setSelected(true);
    QSignalSpy gazWaterContextMenuSpy(p_gazWaterShape->menu(), &QMenu::aboutToShow);
    QCOMPARE(gazWaterContextMenuSpy.count(), 0);

    QList<QAction *> gazWaterMenuActions{p_gazWaterShape->menu()->actions()};
    QCOMPARE(gazWaterMenuActions.size(), 1);
    gazWaterMenuActions.clear();

    QTest::mouseClick(view.viewport(), Qt::RightButton, Qt::NoModifier
                      , view.mapFromScene(p_gazWaterShape->boundingRect().center()));
    gazWaterMenuActions = p_gazWaterShape->menu()->actions();
    QCOMPARE(gazWaterMenuActions.size(), 1);
    QCOMPARE(gazWaterContextMenuSpy.count(), 1);

    scene.removeItem(p_gazWaterShape);
    delete p_gazWaterContextMenu;
    TechnicsShape::TechnicsShapeDeleter::cleanup(p_gazWaterShape);
}

QTEST_MAIN(tst_TechnicShape)

#include "tst_technicsshape.moc"
