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
    void bindingWall();
    void setHeight_data();
    void setHeight();

    // WallShape
    void collidingWall();

    // DoorShape
    void doorState();
    void leafPosition();
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
    QVERIFY2(p_doorShape, "doorShape nullptr");
    QCOMPARE(int(p_doorShape->type()), int(QGraphicsItem::UserType + 402));
    QCOMPARE(p_doorShape->shapeType(), BuildingShape::Door);
    BuildingShape::BuildingShapeDeleter::cleanup(p_doorShape);

    // WindowShape
    BuildingShape *p_windowShape = nullptr;
    p_windowShape = BuildingShape::createBuildingShape(BuildingShape::Window);
    QVERIFY2(p_windowShape, "windowShape nullptr");
    QCOMPARE(int(p_windowShape->type()), int(QGraphicsItem::UserType + 403));
    QCOMPARE(p_windowShape->shapeType(), BuildingShape::Window);
    BuildingShape::BuildingShapeDeleter::cleanup(p_windowShape);

    // OpenShape
    BuildingShape *p_openShape = nullptr;
    p_openShape = BuildingShape::createBuildingShape(BuildingShape::Open);
    QVERIFY2(p_openShape, "OpenShape nullptr");
    QCOMPARE(int(p_openShape->type()), int(QGraphicsItem::UserType + 404));
    QCOMPARE(p_openShape->shapeType(), BuildingShape::Open);
    BuildingShape::BuildingShapeDeleter::cleanup(p_openShape);

    // StairwellShape
    BuildingShape *p_stairwellShape = nullptr;
    p_stairwellShape = BuildingShape::createBuildingShape(BuildingShape::Stairwell);
    QVERIFY2(p_stairwellShape, "StairwellShape nullptr");
    QCOMPARE(int(p_stairwellShape->type()), int(QGraphicsItem::UserType + 405));
    QCOMPARE(p_stairwellShape->shapeType(), BuildingShape::Stairwell);
    BuildingShape::BuildingShapeDeleter::cleanup(p_stairwellShape);

    // StairsShape
    BuildingShape *p_stairsShape = nullptr;
    p_stairsShape = BuildingShape::createBuildingShape(BuildingShape::Stairs);
    QVERIFY2(p_stairsShape, "StairsShape nullptr");
    QCOMPARE(int(p_stairsShape->type()), int(QGraphicsItem::UserType + 406));
    QCOMPARE(p_stairsShape->shapeType(), BuildingShape::Stairs);
    BuildingShape::BuildingShapeDeleter::cleanup(p_stairsShape);
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

    // WindowShape
    BuildingShape *p_windowShape = BuildingShape::createBuildingShape(BuildingShape::Window);
    QCOMPARE(p_windowShape->boundingRect(), QRectF(-30.5, -5.5, 61.0, 11.0));
    BuildingShape::BuildingShapeDeleter::cleanup(p_windowShape);

    // OpenShape
    BuildingShape *p_openShape = BuildingShape::createBuildingShape(BuildingShape::Open);
    QCOMPARE(p_openShape->boundingRect(), QRectF(-30.5, -5.5, 61.0, 11.0));
    BuildingShape::BuildingShapeDeleter::cleanup(p_openShape);

    // StairwellShape
    BuildingShape *p_stairwellShape = BuildingShape::createBuildingShape(BuildingShape::Stairwell);
    QCOMPARE(p_stairwellShape->boundingRect(), QRectF(-30.5, -40.5, 61.0, 81.0));
    BuildingShape::BuildingShapeDeleter::cleanup(p_stairwellShape);

    // StairsShape
    BuildingShape *p_stairsShape = BuildingShape::createBuildingShape(BuildingShape::Stairs);
    QCOMPARE(p_stairsShape->boundingRect(), QRectF(-30.5, -40.5, 61.0, 81.0));
    BuildingShape::BuildingShapeDeleter::cleanup(p_stairsShape);
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
    DoorShape::DoorState currentDoorState{p_doorShape->doorState()};
    switch (currentDoorState) {
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

    // WindowShape
    BuildingShape *p_windowShape = BuildingShape::createBuildingShape(BuildingShape::Window);
    QPainterPathStroker ps_windowShape;
    ps_windowShape.setWidth(p_windowShape->pen().widthF());
    QPainterPath windowPath;
    windowPath.addRect(p_windowShape->rect());
    QPainterPath strokeWindowPath = ps_windowShape.createStroke(windowPath);
    strokeWindowPath.addPath(windowPath);
    QCOMPARE(p_windowShape->shape(), strokeWindowPath);
    BuildingShape::BuildingShapeDeleter::cleanup(p_windowShape);

    // OpenShape
    BuildingShape *p_openShape = BuildingShape::createBuildingShape(BuildingShape::Open);
    QPainterPathStroker ps_openShape;
    ps_openShape.setWidth(p_openShape->pen().widthF());
    QPainterPath openPath;
    openPath.addRect(p_openShape->rect());
    QPainterPath strokeOpenPath = ps_openShape.createStroke(openPath);
    strokeOpenPath.addPath(openPath);
    QCOMPARE(p_openShape->shape(), strokeOpenPath);
    BuildingShape::BuildingShapeDeleter::cleanup(p_openShape);

    // StairwellShape
    BuildingShape *p_stairwellShape = BuildingShape::createBuildingShape(BuildingShape::Stairwell);
    QPainterPathStroker ps_stairwellShape;
    ps_stairwellShape.setWidth(p_stairwellShape->pen().widthF());
    QPainterPath stairwellPath;
    stairwellPath.moveTo(p_stairwellShape->rect().topLeft());
    stairwellPath.lineTo(p_stairwellShape->rect().topRight());
    stairwellPath.lineTo(p_stairwellShape->rect().bottomRight());
    qreal rightRailingX{p_stairwellShape->rect().center().x() + 2.0};
    QPointF rightRailingBottom{rightRailingX, p_stairwellShape->rect().bottom()};
    stairwellPath.lineTo(rightRailingBottom);
    qreal marchWidth{p_stairwellShape->rect().width() / 2.0 - 2.0};
    QPointF rightRailingTop{rightRailingX, p_stairwellShape->rect().top() + marchWidth};
    stairwellPath.lineTo(rightRailingTop);
    qreal leftRailingX{p_stairwellShape->rect().center().x() - 2.0};
    QPointF leftRailingTop{(leftRailingX), p_stairwellShape->rect().top() + marchWidth};
    stairwellPath.lineTo(leftRailingTop);
    QPointF leftRailingBottom{leftRailingX, p_stairwellShape->rect().bottom()};
    stairwellPath.lineTo(leftRailingBottom);
    stairwellPath.lineTo(p_stairwellShape->rect().bottomLeft());
    stairwellPath.lineTo(p_stairwellShape->rect().topLeft());
    QPainterPath strokeStairwellPath = ps_stairwellShape.createStroke(stairwellPath);
    strokeStairwellPath.addPath(stairwellPath);
    QCOMPARE(p_stairwellShape->shape(), strokeStairwellPath);
    BuildingShape::BuildingShapeDeleter::cleanup(p_stairwellShape);
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
    QVERIFY2(!doorImage.isNull(), "DoorShape::image() returned a null pixmap");
    QCOMPARE(doorImage.width(), p_doorShape->boundingRect().width());
    QCOMPARE(doorImage.height(), p_doorShape->boundingRect().width());
    BuildingShape::BuildingShapeDeleter::cleanup(p_doorShape);

    // WindowShape
    BuildingShape *p_windowShape = BuildingShape::createBuildingShape(BuildingShape::Window);
    QPixmap windowImage = p_windowShape->image();
    QVERIFY2(!windowImage.isNull(), "WindowShape::image() returned a null pixmap");
    QCOMPARE(windowImage.width(), p_windowShape->boundingRect().width());
    QCOMPARE(windowImage.height(), p_windowShape->boundingRect().height());
    BuildingShape::BuildingShapeDeleter::cleanup(p_windowShape);

    // OpenShape
    BuildingShape *p_openShape = BuildingShape::createBuildingShape(BuildingShape::Open);
    QPixmap openImage = p_openShape->image();
    QVERIFY2(!openImage.isNull(), "OpenShape::image() returned a null pixmap");
    QCOMPARE(openImage.width(), p_openShape->boundingRect().width());
    QCOMPARE(openImage.height(), p_openShape->boundingRect().height());
    BuildingShape::BuildingShapeDeleter::cleanup(p_openShape);

    // StairwellShape
    BuildingShape *p_stairwellShape = BuildingShape::createBuildingShape(BuildingShape::Stairwell);
    QPixmap stairwellImage = p_stairwellShape->image();
    QVERIFY2(!stairwellImage.isNull(), "StairwellShape::image() returned a null pixmap");
    QCOMPARE(stairwellImage.width(), p_stairwellShape->boundingRect().width());
    QCOMPARE(stairwellImage.height(), p_stairwellShape->boundingRect().height());
    BuildingShape::BuildingShapeDeleter::cleanup(p_stairwellShape);
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

    // WindowShape
    BuildingShape *p_windowShape = BuildingShape::createBuildingShape(BuildingShape::Window);
    p_windowShape->setRect(rect);
    QCOMPARE(p_windowShape->rect(), rect);
    BuildingShape::BuildingShapeDeleter::cleanup(p_windowShape);

    // OpenShape
    BuildingShape *p_openShape = BuildingShape::createBuildingShape(BuildingShape::Open);
    p_openShape->setRect(rect);
    QCOMPARE(p_openShape->rect(), rect);
    BuildingShape::BuildingShapeDeleter::cleanup(p_openShape);

    // StairwellShape
    BuildingShape *p_stairwellShape = BuildingShape::createBuildingShape(BuildingShape::Stairwell);
    p_stairwellShape->setRect(rect);
    QCOMPARE(p_stairwellShape->rect(), rect);
    BuildingShape::BuildingShapeDeleter::cleanup(p_stairwellShape);
}

void tst_BuildingShape::bindingWall()
{
    QGraphicsScene scene;
    QGraphicsView view(&scene);
    view.show();

    // WallShape
    BuildingShape *p_testWall = BuildingShape::createBuildingShape(BuildingShape::Wall);
    scene.addItem(p_testWall);

    BuildingShape *p_leftWall = BuildingShape::createBuildingShape(BuildingShape::Wall);
    scene.addItem(p_leftWall);
    p_leftWall->setRotation(90);
    p_leftWall->moveBy(-29, 0);
    QTest::mouseClick(view.viewport(), Qt::LeftButton, Qt::NoModifier
                      , view.mapFromScene(p_testWall->boundingRect().center()), 50);
    qreal leftLWall{p_leftWall->mapRectToItem(p_testWall, p_leftWall->rect()).left()};
    QCOMPARE(leftLWall, p_testWall->rect().left());

    BuildingShape *p_rightWall = BuildingShape::createBuildingShape(BuildingShape::Wall);
    scene.addItem(p_rightWall);
    p_rightWall->setRotation(90);
    p_rightWall->moveBy(29, 0);
    QTest::mouseClick(view.viewport(), Qt::LeftButton, Qt::NoModifier
                      , view.mapFromScene(p_testWall->boundingRect().center()), 50);
    qreal rightRWall{p_rightWall->mapRectToItem(p_testWall, p_rightWall->rect()).right()};
    QCOMPARE(rightRWall, p_testWall->rect().right());

    leftLWall = p_leftWall->mapRectToItem(p_testWall, p_leftWall->rect()).left();
    QCOMPARE(leftLWall, p_testWall->rect().left());

    BuildingShape::BuildingShapeDeleter::cleanup(p_testWall);
    BuildingShape::BuildingShapeDeleter::cleanup(p_leftWall);
    BuildingShape::BuildingShapeDeleter::cleanup(p_rightWall);

    // DoorShape
    BuildingShape *p_wallShape = BuildingShape::createBuildingShape(BuildingShape::Wall);
    scene.addItem(p_wallShape);
    p_wallShape->setHeight(18);

    BuildingShape *p_doorShape = BuildingShape::createBuildingShape(BuildingShape::Door);
    scene.addItem(p_doorShape);
    QCOMPARE(p_doorShape->height(), 10);
    QTest::mouseClick(view.viewport(), Qt::LeftButton, Qt::NoModifier
                      , view.mapFromScene(p_doorShape->boundingRect().center()), 50);
    QCOMPARE(p_doorShape->height(), 19); //wallShape.height() + penWidth

    BuildingShape::BuildingShapeDeleter::cleanup(p_doorShape);
    BuildingShape::BuildingShapeDeleter::cleanup(p_wallShape);

    // WindowShape
    BuildingShape *p_wallShape2 = BuildingShape::createBuildingShape(BuildingShape::Wall);
    scene.addItem(p_wallShape2);
    p_wallShape2->setHeight(20);

    BuildingShape *p_windowShape = BuildingShape::createBuildingShape(BuildingShape::Window);
    scene.addItem(p_windowShape);
    QCOMPARE(p_windowShape->height(), 10);
    QTest::mouseClick(view.viewport(), Qt::LeftButton, Qt::NoModifier
                      , view.mapFromScene(p_windowShape->boundingRect().center()), 50);
    QCOMPARE(p_windowShape->height(), 21); //wallShape.height() + penWidth

    BuildingShape::BuildingShapeDeleter::cleanup(p_windowShape);
    BuildingShape::BuildingShapeDeleter::cleanup(p_wallShape2);

    // OpenShape
    BuildingShape *p_wallShape3 = BuildingShape::createBuildingShape(BuildingShape::Wall);
    scene.addItem(p_wallShape3);
    p_wallShape3->setHeight(8);

    BuildingShape *p_openShape = BuildingShape::createBuildingShape(BuildingShape::Open);
    scene.addItem(p_openShape);
    QCOMPARE(p_openShape->height(), 10);
    QTest::mouseClick(view.viewport(), Qt::LeftButton, Qt::NoModifier
                      , view.mapFromScene(p_openShape->boundingRect().center()), 50);
    QCOMPARE(p_openShape->height(), 9); //wallShape.height() + penWidth

    BuildingShape::BuildingShapeDeleter::cleanup(p_openShape);
    BuildingShape::BuildingShapeDeleter::cleanup(p_wallShape3);
}

void tst_BuildingShape::setHeight_data()
{
    QTest::addColumn<qreal>("height");
    QTest::newRow("height_0") << 0.0;
    QTest::newRow("height_01") << 0.1;
    QTest::newRow("height_-01") << -0.1;
    QTest::newRow("height_-6") << -6.0;
    QTest::newRow("height_6") << 6.0;
    QTest::newRow("height_8") << 8.0;
    QTest::newRow("height_10") << 10.0;
    QTest::newRow("height_12") << 12.0;
    QTest::newRow("height_14") << 14.0;
    QTest::newRow("height_16") << 16.0;
    QTest::newRow("height_18") << 18.0;
    QTest::newRow("height_20") << 20.0;
    QTest::newRow("height_22") << 22.0;
    QTest::newRow("height_24") << 24.0;
    QTest::newRow("height_26") << 26.0;
}

void tst_BuildingShape::setHeight()
{
    QFETCH(qreal, height);

    // WallShape
    BuildingShape *p_wallShape = BuildingShape::createBuildingShape(BuildingShape::Wall);
    p_wallShape->setHeight(height);
    QCOMPARE(p_wallShape->height(), height);
    BuildingShape::BuildingShapeDeleter::cleanup(p_wallShape);

    // DoorShape
    BuildingShape *p_doorShape = BuildingShape::createBuildingShape(BuildingShape::Door);
    p_doorShape->setHeight(height);
    QCOMPARE(p_doorShape->height(), height);
    BuildingShape::BuildingShapeDeleter::cleanup(p_doorShape);

    // WindowShape
    BuildingShape *p_windowShape = BuildingShape::createBuildingShape(BuildingShape::Window);
    p_windowShape->setHeight(height);
    QCOMPARE(p_windowShape->height(), height);
    BuildingShape::BuildingShapeDeleter::cleanup(p_windowShape);

    // OpenShape
    BuildingShape *p_openShape = BuildingShape::createBuildingShape(BuildingShape::Open);
    p_openShape->setHeight(height);
    QCOMPARE(p_openShape->height(), height);
    BuildingShape::BuildingShapeDeleter::cleanup(p_openShape);

    // StairwellShape
    BuildingShape *p_stairwellShape = BuildingShape::createBuildingShape(BuildingShape::Stairwell);
    p_stairwellShape->setHeight(height);
    QCOMPARE(p_stairwellShape->height(), height);
    BuildingShape::BuildingShapeDeleter::cleanup(p_stairwellShape);
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
    QCOMPARE(p_wallShape->collidingWalls().size(), 1);

    BuildingShape *p_buildingShape3 = BuildingShape::createBuildingShape(BuildingShape::Wall);
    WallShape *p_wallShape3 = dynamic_cast<WallShape *>(p_buildingShape3);
    scene.addItem(p_wallShape3);
    QTest::qWait(50);
    p_wallShape3->setPos(p_wallShape2->x() + 10, p_wallShape2->y() + 10);
    QCOMPARE(p_wallShape->collidingWalls().size(), 2);

    scene.removeItem(p_wallShape3);
    p_wallShape->removeCollidingWall(p_wallShape3);
    QCOMPARE(p_wallShape->collidingWalls().size(), 1);
    BuildingShape::BuildingShapeDeleter::cleanup(p_wallShape3);

    scene.removeItem(p_wallShape2);
    p_wallShape->removeCollidingWall(p_wallShape2);
    QCOMPARE(p_wallShape->collidingWalls().size(), 0);
    BuildingShape::BuildingShapeDeleter::cleanup(p_wallShape2);

    scene.removeItem(p_wallShape);
    BuildingShape::BuildingShapeDeleter::cleanup(p_wallShape);
}

void tst_BuildingShape::doorState()
{
    BuildingShape *p_buildingShape = BuildingShape::createBuildingShape(BuildingShape::Door);
    DoorShape *p_doorShape = dynamic_cast<DoorShape *>(p_buildingShape);
    QCOMPARE(p_doorShape->doorState(), DoorShape::Open);
    p_doorShape->setDoorState(DoorShape::Ajar);
    QCOMPARE(p_doorShape->doorState(), DoorShape::Ajar);
    p_doorShape->setDoorState(DoorShape::Close);
    QCOMPARE(p_doorShape->doorState(), DoorShape::Close);
    p_doorShape->setDoorState(DoorShape::Open);
    QCOMPARE(p_doorShape->doorState(), DoorShape::Open);
    BuildingShape::BuildingShapeDeleter::cleanup(p_buildingShape);
}

void tst_BuildingShape::leafPosition()
{
    BuildingShape *p_buildingShape = BuildingShape::createBuildingShape(BuildingShape::Door);
    DoorShape *p_doorShape = dynamic_cast<DoorShape *>(p_buildingShape);
    QCOMPARE(p_doorShape->leafPosition(), DoorShape::Right);
    p_doorShape->setLeafPosition(DoorShape::Left);
    QCOMPARE(p_doorShape->leafPosition(), DoorShape::Left);
    p_doorShape->setLeafPosition(DoorShape::Right);
    QCOMPARE(p_doorShape->leafPosition(), DoorShape::Right);
    BuildingShape::BuildingShapeDeleter::cleanup(p_buildingShape);
}

QTEST_MAIN(tst_BuildingShape)

#include "tst_buildingshape.moc"
