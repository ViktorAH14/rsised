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

#include "../../../../src/include/ellipseshape.h"

#include <QtTest>

#include <QPen>

class tst_EllipseShape : public QObject
{
    Q_OBJECT

private slots:
    void constructor();
};



void tst_EllipseShape::constructor()
{
    EllipseShape *ellipseShape = nullptr;

    ellipseShape = new EllipseShape;
    ellipseShape->setPen(QPen(Qt::black, 0));
    QVERIFY2(ellipseShape, "ellipseShape nullptr");
    QCOMPARE(int(ellipseShape->type()), int(EllipseShape::Type));
    QCOMPARE(ellipseShape->flags(), 0x800); //ItemSendsGeometryChanges true
    QVERIFY(ellipseShape->acceptHoverEvents());
    QCOMPARE(ellipseShape->rect(), QRectF());
    delete ellipseShape;

    QRectF rect(-5.0, -5.0, 5.0, 5.0);
    ellipseShape = new EllipseShape(rect);
    ellipseShape->setPen(QPen(Qt::black, 0));
    QVERIFY2(ellipseShape, "rectShape nullptr");
    QCOMPARE(int(ellipseShape->type()), int(EllipseShape::Type));
    QCOMPARE(ellipseShape->flags(), 0x800);
    QVERIFY(ellipseShape->acceptHoverEvents());
    QCOMPARE(ellipseShape->rect(), rect);
    delete ellipseShape;

    qreal x{rect.topLeft().x()};
    qreal y{rect.topLeft().y()};
    qreal w{rect.width()};
    qreal h{rect.height()};
    ellipseShape = new EllipseShape(x, y, w, h);
    ellipseShape->setPen(QPen(Qt::black, 0));
    QVERIFY2(ellipseShape, "rectShape nullptr");
    QCOMPARE(int(ellipseShape->type()), int(EllipseShape::Type));
    QCOMPARE(ellipseShape->flags(), 0x800);
    QVERIFY(ellipseShape->acceptHoverEvents());
    QCOMPARE(ellipseShape->rect(), rect);
    delete ellipseShape;
}

QTEST_MAIN(tst_EllipseShape)

#include "tst_ellipseshape.moc"
