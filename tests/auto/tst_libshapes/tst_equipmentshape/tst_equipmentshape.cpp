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

#define EQUIPMENTSHAPE_TEST

#include "../../../../src/include/equipmentshape.h"

#include <QtTest>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QGraphicsSceneMouseEvent>

class tst_EquipmentShape : public QObject
{
    Q_OBJECT

private slots:
    void constructor();
    // void boundingRect();
    // void shape();
    // void image();
    // void rect_setRect_data();
    // void rect_setRect();
    // void height_setHeight_data();
    // void height_setHeight();
    // void text_setText_data();
    // void text_setText();
    // void mousePressEvent();
    // void textShow();
    // void paint();
};

void tst_EquipmentShape::constructor()
{
    // NosepieceShape
    EquipmentShape *p_nosepieceShape = nullptr;
    p_nosepieceShape = EquipmentShape::createEquipmentShape(EquipmentShape::Nosepiece);
    QVERIFY2(p_nosepieceShape, "baseShape is  nullptr");
    QCOMPARE(int(p_nosepieceShape->type()), int(QGraphicsItem::UserType + 301));
    QCOMPARE(p_nosepieceShape->shapeType(), EquipmentShape::Nosepiece);
    EquipmentShape::EquipmentShapeDeleter::cleanup(p_nosepieceShape);
}

QTEST_MAIN(tst_EquipmentShape)

#include "tst_equipmentshape.moc"

