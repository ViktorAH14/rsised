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

#include "../../../../src/include/buildingshape.h"

#include <QtTest>
#include <QPen>
#include <QGraphicsScene>
#include <QGraphicsView>

class tst_BuildingShape : public QObject
{
    Q_OBJECT

private slots:
    void constructor();
    void boundingRect();
    void shape();
    void image();
    void setRect_data();
    void setRect();
    void contains();
    void collidingWall();
};



void tst_BuildingShape::constructor()
{
    // WallShape
    BuildingShape *p_wallShape = nullptr;
    p_wallShape = BuildingShape::createBuildingShape(BuildingShape::Wall);
    QVERIFY2(p_wallShape, "wallShape nullptr");
    QCOMPARE(int(p_wallShape->type()), int(QGraphicsItem::UserType + 401));
    QCOMPARE(p_wallShape->shapeType(), BuildingShape::Wall);
    BuildingShape::BuildingShapeDeleter::cleanup(p_wallShape);

    // DoorShape
    BuildingShape *p_doorShape = nullptr;
    p_doorShape = BuildingShape::createBuildingShape(BuildingShape::Door);
    QVERIFY2(p_doorShape, "wallShape nullptr");
    QCOMPARE(int(p_doorShape->type()), int(QGraphicsItem::UserType + 402));
    QCOMPARE(p_doorShape->shapeType(), BuildingShape::Door);
    BuildingShape::BuildingShapeDeleter::cleanup(p_doorShape);
}

void tst_BuildingShape::boundingRect()
{
    // WallShape
    BuildingShape *p_wallShape = BuildingShape::createBuildingShape(BuildingShape::Wall);
    QCOMPARE(p_wallShape->boundingRect(), QRectF(-30.5, -5.5, 61.0, 11.0));
    BuildingShape::BuildingShapeDeleter::cleanup(p_wallShape);

    // DoorShape
    BuildingShape *p_doorShape = BuildingShape::createBuildingShape(BuildingShape::Door);
    QCOMPARE(p_doorShape->boundingRect(), QRectF(-30.5, -30.5, 61.0, 61.0));
    BuildingShape::BuildingShapeDeleter::cleanup(p_doorShape);
}

void tst_BuildingShape::shape()
{
    // WallShape
    BuildingShape *p_wallShape = BuildingShape::createBuildingShape(BuildingShape::Wall);
    QPainterPathStroker ps_wallShape;
    ps_wallShape.setWidth(p_wallShape->pen().widthF());
    QPainterPath wallPath;
    wallPath.addRect(p_wallShape->rect());
    QPainterPath strokeWallPath = ps_wallShape.createStroke(wallPath);
    strokeWallPath.addPath(wallPath);
    QCOMPARE(p_wallShape->shape(), strokeWallPath);
    BuildingShape::BuildingShapeDeleter::cleanup(p_wallShape);

    // DoorShape
    BuildingShape *p_buildingShape = BuildingShape::createBuildingShape(BuildingShape::Door);
    DoorShape *p_doorShape = dynamic_cast<DoorShape *>(p_buildingShape);
    QPainterPathStroker ps_doorShape;
    ps_doorShape.setWidth(p_doorShape->pen().widthF());
    QPainterPath doorPath;

    QRectF doorRect(p_doorShape->rect());
    doorPath.addRect(doorRect);

    qreal frameWidth{doorRect.height() / 2};
    qreal frameHeight{doorRect.height()};
    QRectF leftFrame(doorRect.left(), doorRect.top(), frameWidth, frameHeight);
    doorPath.addRect(leftFrame);

    qreal rightFrame_left((doorRect.right() - doorRect.height() / 2));
    QRectF rightFrame(rightFrame_left, doorRect.top(), frameWidth, frameHeight);
    doorPath.addRect(rightFrame);

    QLineF doorLeaf(rightFrame.topLeft(), leftFrame.topRight());
    DoorShape::DoorState doorState{p_doorShape->doorState()};
    switch (doorState) {
    case DoorShape::Open:
        doorLeaf.setAngle(90);
        break;
    case DoorShape::Ajar:
        doorLeaf.setAngle(135);
        break;
    case DoorShape::Close:
        doorLeaf.setAngle(180);
        break;
    default:
        break;
    }
    doorPath.moveTo(doorLeaf.p1());
    doorPath.moveTo(doorLeaf.p2());
    QRectF arcRectangle(leftFrame.right(), leftFrame.top() - qFabs(doorLeaf.length())
                        , (doorLeaf.length() * 2), (doorLeaf.length() * 2));
    int startAngle = doorLeaf.angle() * 16;
    int spanAngle = (180 - doorLeaf.angle()) * 16;
    doorPath.arcTo(arcRectangle, startAngle, spanAngle);
    QPainterPath strokeDoorPath = ps_doorShape.createStroke(doorPath);
    strokeDoorPath.addPath(doorPath);
    QCOMPARE(p_doorShape->shape(), strokeDoorPath);
    BuildingShape::BuildingShapeDeleter::cleanup(p_doorShape);

}

void tst_BuildingShape::image()
{
    // WallShape
    BuildingShape *p_wallShape = BuildingShape::createBuildingShape(BuildingShape::Wall);
    QPixmap wallImage = p_wallShape->image();
    QVERIFY2(!wallImage.isNull(), "WallShape::image() returned a null pixmap");
    QCOMPARE(wallImage.width(), p_wallShape->boundingRect().width());
    QCOMPARE(wallImage.height(), p_wallShape->boundingRect().height());
    BuildingShape::BuildingShapeDeleter::cleanup(p_wallShape);

    // DoorShape
    BuildingShape *p_doorShape = BuildingShape::createBuildingShape(BuildingShape::Door);
    QPixmap doorImage = p_doorShape->image();
    QVERIFY2(!doorImage.isNull(), "WallShape::image() returned a null pixmap");
    QCOMPARE(doorImage.width(), p_doorShape->boundingRect().width());
    QCOMPARE(doorImage.height(), p_doorShape->boundingRect().width());
    BuildingShape::BuildingShapeDeleter::cleanup(p_doorShape);
}

void tst_BuildingShape::setRect_data()
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

void tst_BuildingShape::setRect()
{
    QFETCH(QRectF, rect);

    // WallShape
    BuildingShape *p_wallShape = BuildingShape::createBuildingShape(BuildingShape::Wall);
    p_wallShape->setRect(rect);
    QCOMPARE(p_wallShape->rect(), rect);
    BuildingShape::BuildingShapeDeleter::cleanup(p_wallShape);

    // DoorShape
    BuildingShape *p_doorShape = BuildingShape::createBuildingShape(BuildingShape::Door);
    p_doorShape->setRect(rect);
    QCOMPARE(p_doorShape->rect(), rect);
    BuildingShape::BuildingShapeDeleter::cleanup(p_doorShape);
}

void tst_BuildingShape::contains()
{
    if (sizeof(qreal) != sizeof(double))
        QSKIP("Skipped due to rounding errors");

    BuildingShape *p_wallShape = BuildingShape::createBuildingShape(BuildingShape::Wall);
    QVERIFY(!p_wallShape->contains(QPointF(-31, -6)));
    QVERIFY(p_wallShape->contains(QPointF(-30, -5)));
    QVERIFY(!p_wallShape->contains(QPointF(-31, 0)));
    QVERIFY(p_wallShape->contains(QPointF(-30, 0)));
    QVERIFY(p_wallShape->contains(QPointF(0, -5)));
    QVERIFY(p_wallShape->contains(QPointF(0, 0)));
    QVERIFY(p_wallShape->contains(QPointF(30, 5)));
}

void tst_BuildingShape::collidingWall()
{
    QGraphicsScene scene;
    QGraphicsView view(&scene);
    view.show();

    BuildingShape *p_buildingShape = BuildingShape::createBuildingShape(BuildingShape::Wall);
    WallShape *p_wallShape = dynamic_cast<WallShape *>(p_buildingShape);
    scene.addItem(p_wallShape);
    QVERIFY(p_wallShape->collidingWalls().isEmpty());

    BuildingShape *p_buildingShape2 = BuildingShape::createBuildingShape(BuildingShape::Wall);
    WallShape *p_wallShape2 = dynamic_cast<WallShape *>(p_buildingShape2);
    scene.addItem(p_wallShape2);
    p_wallShape2->setPos(p_wallShape->x() + 10, p_wallShape->y() + 10);
    QTest::qWait(50);
    QCOMPARE(p_wallShape->collidingWalls().size(), 2);

    BuildingShape *p_buildingShape3 = BuildingShape::createBuildingShape(BuildingShape::Wall);
    WallShape *p_wallShape3 = dynamic_cast<WallShape *>(p_buildingShape3);
    scene.addItem(p_wallShape3);
    QTest::qWait(50);
    p_wallShape3->setPos(p_wallShape2->x() + 10, p_wallShape2->y() + 10);
    QCOMPARE(p_wallShape->collidingWalls().size(), 3);

    scene.removeItem(p_wallShape3);
    p_wallShape->removeCollidingWall(p_wallShape3);
    QCOMPARE(p_wallShape->collidingWalls().size(), 2);
    BuildingShape::BuildingShapeDeleter::cleanup(p_wallShape3);

    scene.removeItem(p_wallShape2);
    p_wallShape->removeCollidingWall(p_wallShape2);
    QCOMPARE(p_wallShape->collidingWalls().size(), 1);
    BuildingShape::BuildingShapeDeleter::cleanup(p_wallShape2);

    scene.removeItem(p_wallShape);
    p_wallShape->removeCollidingWall(p_wallShape);
    QCOMPARE(p_wallShape->collidingWalls().size(), 0);
    BuildingShape::BuildingShapeDeleter::cleanup(p_wallShape);
}

QTEST_MAIN(tst_BuildingShape)

#include "tst_buildingshape.moc"
