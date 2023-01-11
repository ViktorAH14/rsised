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

#include "../../../../src/include/technicsshape.h"

#include <QtTest>

class tst_TechnicShape : public QObject
{
    Q_OBJECT

private slots:
    void constructor();
    void boundingRect();
    void shape();
    void image();
    void setRect_data();
    void setRect();
};



void tst_TechnicShape::constructor()
{
    // TankerShape
    TechnicsShape *p_tankerShape = nullptr;
    p_tankerShape = TechnicsShape::createTechnicsShape(TechnicsShape::Tanker);
    QVERIFY2(p_tankerShape, "tankerShape nullptr");
    QCOMPARE(int(p_tankerShape->type()), int(QGraphicsItem::UserType + 202));
    QCOMPARE(p_tankerShape->shapeType(), TechnicsShape::Tanker);
    TechnicsShape::TechnicsShapeDeleter::cleanup(p_tankerShape);
}

void tst_TechnicShape::boundingRect()
{
    // TankerShape
    TechnicsShape *p_tankerShape = TechnicsShape::createTechnicsShape(TechnicsShape::Tanker);
    QCOMPARE(p_tankerShape->boundingRect(), QRectF(-15.5, -38.0, 31.0, 76.0));
    TankerShape *p_tanker = dynamic_cast<TankerShape *>(p_tankerShape);
    p_tanker->setPipes(true);
    QCOMPARE(p_tankerShape->boundingRect(), QRectF(-20.5, -38.0, 41.0, 76.0));
    p_tanker->setCollector(true);
    QCOMPARE(p_tankerShape->boundingRect(), QRectF(-20.5, -38.0, 41.0, 86.0));
    p_tanker->setText("Text");
    QCOMPARE(p_tankerShape->boundingRect(), QRectF(-20.5, -38.0, 41.0, 86.0));
    p_tanker->setPipes(false);
    QCOMPARE(p_tankerShape->boundingRect(), QRectF(-15.5, -38.0, 31.0, 86.0));
    p_tanker->setCollector(false);
    QCOMPARE(p_tankerShape->boundingRect(), QRectF(-15.5, -38.0, 31.0, 76.0));
    TechnicsShape::TechnicsShapeDeleter::cleanup(p_tankerShape);
}

void tst_TechnicShape::shape()
{
    // TankerShape
    TechnicsShape *p_tankerShape = TechnicsShape::createTechnicsShape(TechnicsShape::Tanker);
    QPainterPathStroker ps_tankerShape;
    ps_tankerShape.setWidth(p_tankerShape->pen().widthF());
    QRectF tankerRect{p_tankerShape->rect()};
    qreal frontTab{tankerRect.height() / 3};
    QPointF frontCenter{tankerRect.center().x(), tankerRect.top()}; // 0.0, -37.5
    QPointF frontRight{tankerRect.right(), tankerRect.top() + frontTab}; // 15.0, -12.5
    QPointF frontLeft{tankerRect.left(), tankerRect.top() + frontTab}; // -15.0, -12.5
    QPointF bottomRight{tankerRect.bottomRight()}; // 15.0, 37.5
    QPointF bottomLeft{tankerRect.bottomLeft()}; // -15.0, 37.5
    QPolygonF basePolygon;
    basePolygon << frontCenter << frontRight << bottomRight << bottomLeft << frontLeft << frontCenter;
    QPainterPath tankerPath;
    tankerPath.addPolygon(basePolygon);
    QPainterPath strokeTankerPath = ps_tankerShape.createStroke(tankerPath);
    strokeTankerPath.addPath(tankerPath);
    QCOMPARE(p_tankerShape->shape(), strokeTankerPath);

    // TankerShape show pipes
    TankerShape *p_tanker = dynamic_cast<TankerShape *>(p_tankerShape);
    tankerPath.clear();
    strokeTankerPath.clear();
    p_tanker->setPipes(true);
    tankerPath.addPolygon(basePolygon);
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
    tankerPath.addPolygon(basePolygon);
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

    TechnicsShape::TechnicsShapeDeleter::cleanup(p_tankerShape);
}

void tst_TechnicShape::image()
{
    // TankerShape
    TechnicsShape *p_tankerShape = TechnicsShape::createTechnicsShape(TechnicsShape::Tanker);
    QPixmap tankerImage{p_tankerShape->image()};
    QVERIFY2(!tankerImage.isNull(), "TankerShape::image() returned a null pixmap");
    QCOMPARE(tankerImage.width(), p_tankerShape->boundingRect().width());
    QCOMPARE(tankerImage.height(), p_tankerShape->boundingRect().height());
    TechnicsShape::TechnicsShapeDeleter::cleanup(p_tankerShape);
}

void tst_TechnicShape::setRect_data()
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

void tst_TechnicShape::setRect()
{
    QFETCH(QRectF, rect);

    // TankerShape
    TechnicsShape *p_tankerShape = TechnicsShape::createTechnicsShape(TechnicsShape::Tanker);
    p_tankerShape->setRect(rect);
    QCOMPARE(p_tankerShape->rect(), rect);
    TechnicsShape::TechnicsShapeDeleter::cleanup(p_tankerShape);
}

QTEST_MAIN(tst_TechnicShape)

#include "tst_technicsshape.moc"
