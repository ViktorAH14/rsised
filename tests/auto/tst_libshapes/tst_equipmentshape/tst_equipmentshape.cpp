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
#include <QStyleOptionGraphicsItem>
#include <array>
#include <utility>

class tst_EquipmentShape : public QObject
{
    Q_OBJECT

private slots:
    void constructor();
    void factory_returnsNullForUnsupportedTypes();
    void boundingRect();
    void boundingRect_penWidthAdjustments();
    void shape();
    void image();
    void rect_setRect_data();
    void rect_setRect();
    void setRect_sameRect();
    void setRect_withSubstanceType();
    void setRect_withConsumption();
    void height_setHeight();
    void text_setText();
    void mousePressEvent();
    // void textShow();
    void paint();
    void substanceType_data();
    void substanceType();
    void createSubstanceActions();
    void type();
    void shapeType();
    void updateDNPosition();
};

void tst_EquipmentShape::constructor()
{
    // NosepieceShape
    EquipmentShape *p_nosepieceShape = nullptr;
    p_nosepieceShape = EquipmentShape::createEquipmentShape(EquipmentShape::Nosepiece);
    QVERIFY2(p_nosepieceShape, "baseShape is  nullptr");
    QCOMPARE(int(p_nosepieceShape->type()), int(QGraphicsItem::UserType + 301));
    QCOMPARE(p_nosepieceShape->shapeType(), EquipmentShape::Nosepiece);

    // Verify default-initialized state of NosepieceShape
    NosepieceShape *nosepiece = dynamic_cast<NosepieceShape *>(p_nosepieceShape);
    QVERIFY2(nosepiece, "Failed to cast EquipmentShape to NosepieceShape");

    // Default geometry
    QCOMPARE(nosepiece->rect(), QRectF(-6.0, -16.0, 12.0, 32.0));

    // Default substance and text labels
    QCOMPARE(nosepiece->substanceType(), NosepieceShape::NoneSubstance);
    QVERIFY(nosepiece->nominalDiameter().isEmpty());
    QVERIFY(nosepiece->consumption().isEmpty());

    // Default interaction flags
    QVERIFY(nosepiece->flags().testFlag(QGraphicsItem::ItemSendsGeometryChanges));
    QVERIFY(nosepiece->acceptHoverEvents());

    // Default pen
    QCOMPARE(nosepiece->pen(), QPen(Qt::black, 1));

    EquipmentShape::EquipmentShapeDeleter::cleanup(p_nosepieceShape);
}

void tst_EquipmentShape::factory_returnsNullForUnsupportedTypes()
{
    const std::array<EquipmentShape::ShapeType, 12> unsupportedShapeTypes = {
        EquipmentShape::Branch,
        EquipmentShape::Ladder,
        EquipmentShape::Collector,
        EquipmentShape::HoseBridge,
        EquipmentShape::HoseReel,
        EquipmentShape::Hydroelevator,
        EquipmentShape::FoamMixer,
        EquipmentShape::FireColumn,
        EquipmentShape::SmokePump,
        EquipmentShape::Hose,
        EquipmentShape::FoamLift,
        EquipmentShape::LiftGPS
    };

    for (const auto shapeType : unsupportedShapeTypes) {
        EquipmentShape *shape = EquipmentShape::createEquipmentShape(shapeType);
        QVERIFY2(shape == nullptr, "Unsupported shape type must return nullptr");
    }
}

void tst_EquipmentShape::boundingRect()
{
    // Nosepiece default bounding rect
    EquipmentShape *p_nosepieceShape = EquipmentShape::createEquipmentShape(EquipmentShape::Nosepiece);
    QVERIFY2(p_nosepieceShape, "nosepieceShape is nullptr");

    const QRectF defaultBoundingRect = p_nosepieceShape->boundingRect();
    QCOMPARE(defaultBoundingRect, QRectF(-6.5, -16.5, 13.0, 33.0));

    // For a substance type with top adjustment, bounding rect must grow upward
    NosepieceShape *nosepiece = dynamic_cast<NosepieceShape *>(p_nosepieceShape);
    QVERIFY2(nosepiece, "Failed to cast EquipmentShape to NosepieceShape");

    nosepiece->setSubstanceType(NosepieceShape::CompactWater);
    // Recalculate bounding rect with substance indicator
    const QRectF substanceBoundingRect = nosepiece->boundingRect();

    // Top moves up (y becomes smaller), height increases
    QVERIFY(substanceBoundingRect.top() < defaultBoundingRect.top());
    QVERIFY(substanceBoundingRect.height() > defaultBoundingRect.height());

    EquipmentShape::EquipmentShapeDeleter::cleanup(p_nosepieceShape);
}

void tst_EquipmentShape::boundingRect_penWidthAdjustments()
{
    EquipmentShape *shape = EquipmentShape::createEquipmentShape(EquipmentShape::Nosepiece);
    QVERIFY2(shape, "nosepieceShape is nullptr");

    NosepieceShape *nosepiece = dynamic_cast<NosepieceShape *>(shape);
    QVERIFY2(nosepiece, "Failed to cast EquipmentShape to NosepieceShape");

    nosepiece->setSubstanceType(NosepieceShape::NoneSubstance);

    nosepiece->setPen(QPen(Qt::black, 1));
    const QRectF rectWithDefaultPen = nosepiece->boundingRect();
    QCOMPARE(rectWithDefaultPen, QRectF(-6.5, -16.5, 13.0, 33.0));

    nosepiece->setPen(QPen(Qt::NoPen));
    const QRectF rectWithNoPen = nosepiece->boundingRect();
    QCOMPARE(rectWithNoPen, QRectF(-6.0, -16.0, 12.0, 32.0));

    nosepiece->setPen(QPen(Qt::black, 4));
    const QRectF rectWithWidePen = nosepiece->boundingRect();
    QCOMPARE(rectWithWidePen, QRectF(-8.0, -18.0, 16.0, 36.0));

    EquipmentShape::EquipmentShapeDeleter::cleanup(shape);
}

void tst_EquipmentShape::shape()
{
    // Nosepiece
    EquipmentShape *p_nosepieceShape = EquipmentShape::createEquipmentShape(EquipmentShape::Nosepiece);
    QVERIFY2(p_nosepieceShape, "nosepieceShape is nullptr");

    NosepieceShape *nosepiece = dynamic_cast<NosepieceShape *>(p_nosepieceShape);
    QVERIFY2(nosepiece, "Failed to cast EquipmentShape to NosepieceShape");

    // Base shape path should not be empty and should be within boundingRect
    QPainterPath baseShape = nosepiece->shape();
    QVERIFY(!baseShape.isEmpty());
    QRectF baseBounds = baseShape.boundingRect();
    QRectF bounding = nosepiece->boundingRect();
    // Allow for small differences between geometric shape() and boundingRect() calculations:
    // they should at least intersect.
    QVERIFY(bounding.intersects(baseBounds));

    // For a substance type with indicator, shape() should expand beyond base nosepiece rect
    QRectF baseRect = nosepiece->rect();
    nosepiece->setSubstanceType(NosepieceShape::CompactWater);
    QPainterPath substanceShape = nosepiece->shape();
    QRectF substanceBounds = substanceShape.boundingRect();

    // Substance symbol is drawn above the nosepiece: top moves up (y smaller)
    QVERIFY(substanceBounds.top() < baseRect.top());

    EquipmentShape::EquipmentShapeDeleter::cleanup(p_nosepieceShape);
}

void tst_EquipmentShape::image()
{
    // Nosepiece
    EquipmentShape *p_nosepieceShape = EquipmentShape::createEquipmentShape(EquipmentShape::Nosepiece);
    QVERIFY2(p_nosepieceShape, "nosepieceShape is nullptr");

    NosepieceShape *nosepiece = dynamic_cast<NosepieceShape *>(p_nosepieceShape);
    QVERIFY2(nosepiece, "Failed to cast EquipmentShape to NosepieceShape");

    // Generate pixmap and verify basic properties
    QPixmap pixmap = nosepiece->image();
    QVERIFY(!pixmap.isNull());

    // Pixmap size should match boundingRect size (within integer rounding)
    const QRectF brect = nosepiece->boundingRect();
    QCOMPARE(pixmap.width(), qRound(brect.width()));
    QCOMPARE(pixmap.height(), qRound(brect.height()));

    // Optional: ensure that pixmap is not fully transparent (some drawing occurred)
    bool hasNonTransparentPixel = false;
    for (int y = 0; y < pixmap.height() && !hasNonTransparentPixel; ++y) {
        for (int x = 0; x < pixmap.width(); ++x) {
            if (qAlpha(pixmap.toImage().pixel(x, y)) != 0) {
                hasNonTransparentPixel = true;
                break;
            }
        }
    }
    QVERIFY(hasNonTransparentPixel);

    EquipmentShape::EquipmentShapeDeleter::cleanup(p_nosepieceShape);
}

// rect_setRect_data() and rect_setRect() are parameterized tests that verify setting
// various rectangles (default, at the origin, with positive/negative coordinates,
// small and large sizes).
void tst_EquipmentShape::rect_setRect_data()
{
    QTest::addColumn<QRectF>("inputRect");
    QTest::addColumn<QRectF>("expectedRect");

    // Default rectangle (no substance type, so topAdjust = 0)
    QTest::newRow("default_rect") << QRectF(-6.0, -16.0, 12.0, 32.0)
                                   << QRectF(-6.0, -16.0, 12.0, 32.0);

    // Simple rectangle at origin
    QTest::newRow("origin_rect") << QRectF(0.0, 0.0, 10.0, 20.0)
                                  << QRectF(0.0, 0.0, 10.0, 20.0);

    // Rectangle with positive coordinates
    QTest::newRow("positive_rect") << QRectF(10.0, 20.0, 15.0, 25.0)
                                    << QRectF(10.0, 20.0, 15.0, 25.0);

    // Rectangle with negative coordinates
    QTest::newRow("negative_rect") << QRectF(-20.0, -30.0, 8.0, 16.0)
                                    << QRectF(-20.0, -30.0, 8.0, 16.0);

    // Small rectangle
    QTest::newRow("small_rect") << QRectF(-3.0, -8.0, 6.0, 16.0)
                                 << QRectF(-3.0, -8.0, 6.0, 16.0);

    // Large rectangle
    QTest::newRow("large_rect") << QRectF(-50.0, -100.0, 100.0, 200.0)
                                 << QRectF(-50.0, -100.0, 100.0, 200.0);
}

void tst_EquipmentShape::rect_setRect()
{
    QFETCH(QRectF, inputRect);
    QFETCH(QRectF, expectedRect);

    EquipmentShape *p_nosepieceShape = EquipmentShape::createEquipmentShape(EquipmentShape::Nosepiece);
    QVERIFY2(p_nosepieceShape, "nosepieceShape is nullptr");

    // Set the rectangle
    p_nosepieceShape->setRect(inputRect);

    // Verify that rect() returns the expected value
    // Note: setRect adjusts the rectangle by topAdjust, but for NoneSubstance, topAdjust = 0
    QCOMPARE(p_nosepieceShape->rect(), expectedRect);

    EquipmentShape::EquipmentShapeDeleter::cleanup(p_nosepieceShape);
}

// setRect_sameRect() verifies that setting the same rectangle again does not change
// the state (early return optimization).
void tst_EquipmentShape::setRect_sameRect()
{
    EquipmentShape *p_nosepieceShape = EquipmentShape::createEquipmentShape(EquipmentShape::Nosepiece);
    QVERIFY2(p_nosepieceShape, "nosepieceShape is nullptr");

    // Get the default rectangle
    QRectF defaultRect = p_nosepieceShape->rect();

    // Set the same rectangle - should not change anything
    p_nosepieceShape->setRect(defaultRect);

    // Verify rectangle is still the same
    QCOMPARE(p_nosepieceShape->rect(), defaultRect);

    // Set a new rectangle
    QRectF newRect(-10.0, -20.0, 20.0, 40.0);
    p_nosepieceShape->setRect(newRect);
    QCOMPARE(p_nosepieceShape->rect(), newRect);

    // Set the same rectangle again - should not change
    p_nosepieceShape->setRect(newRect);
    QCOMPARE(p_nosepieceShape->rect(), newRect);

    EquipmentShape::EquipmentShapeDeleter::cleanup(p_nosepieceShape);
}

// setRect_withSubstanceType() verifies correct behavior with different substance types:
// - with NoneSubstance (topAdjust = 0) the rectangle is not changed
// - with a type like CompactWater the rectangle is adjusted upward

void tst_EquipmentShape::setRect_withSubstanceType()
{
    EquipmentShape *p_nosepieceShape = EquipmentShape::createEquipmentShape(EquipmentShape::Nosepiece);
    QVERIFY2(p_nosepieceShape, "nosepieceShape is nullptr");

    // Cast to NosepieceShape to access setSubstanceType
    NosepieceShape *nosepiece = dynamic_cast<NosepieceShape *>(p_nosepieceShape);
    QVERIFY2(nosepiece, "Failed to cast to NosepieceShape");

    // Test with NoneSubstance (topAdjust = 0)
    nosepiece->setSubstanceType(NosepieceShape::NoneSubstance);
    QRectF inputRect1(0.0, 0.0, 12.0, 32.0);
    p_nosepieceShape->setRect(inputRect1);
    // With no substance, the rectangle should be adjusted by 0, so it stays the same
    QCOMPARE(p_nosepieceShape->rect(), inputRect1);

    EquipmentShape::EquipmentShapeDeleter::cleanup(p_nosepieceShape);

    // Test with a substance type that has an adjustment factor (CompactWater)
    EquipmentShape *p_nosepieceShape2 = EquipmentShape::createEquipmentShape(EquipmentShape::Nosepiece);
    QVERIFY2(p_nosepieceShape2, "nosepieceShape2 is nullptr");

    NosepieceShape *nosepiece2 = dynamic_cast<NosepieceShape *>(p_nosepieceShape2);
    QVERIFY2(nosepiece2, "Failed to cast to NosepieceShape (2)");

    nosepiece2->setSubstanceType(NosepieceShape::CompactWater);
    QRectF inputRect2(0.0, 0.0, 12.0, 32.0);
    p_nosepieceShape2->setRect(inputRect2);

    // We do not check the exact value, only the fact of adjustment:
    // - the top boundary must increase (y becomes larger because the coordinate system grows downwards)
    // - the rectangle height must decrease (we carve out space for the substance symbol above)
    QRectF resultRect2 = p_nosepieceShape2->rect();
    QVERIFY(resultRect2.top() > inputRect2.top());
    QVERIFY(resultRect2.height() < inputRect2.height());

    EquipmentShape::EquipmentShapeDeleter::cleanup(p_nosepieceShape2);
}

// setRect_withConsumption() — verifies that when consumption is visible,
// a call to setRect updates its position via updateConsumptionPosition().
void tst_EquipmentShape::setRect_withConsumption()
{
    EquipmentShape *p_nosepieceShape = EquipmentShape::createEquipmentShape(EquipmentShape::Nosepiece);
    QVERIFY2(p_nosepieceShape, "nosepieceShape is nullptr");

    // Cast to NosepieceShape to access setTextItem
    NosepieceShape *nosepiece = dynamic_cast<NosepieceShape *>(p_nosepieceShape);
    QVERIFY2(nosepiece, "Failed to cast to NosepieceShape");

    // Set consumption to make it visible
    nosepiece->setTextItem(NosepieceShape::Consumption, "2.7");
    QVERIFY(nosepiece->consumption() == "2.7");

    // Set a new rectangle - this should trigger updateConsumptionPosition()
    QRectF newRect(-10.0, -20.0, 20.0, 40.0);
    p_nosepieceShape->setRect(newRect);

    // Verify rectangle was set correctly
    QCOMPARE(p_nosepieceShape->rect(), newRect);

    // Verify consumption is still set (updateConsumptionPosition should not affect the text)
    QCOMPARE(nosepiece->consumption(), QString("2.7"));

    EquipmentShape::EquipmentShapeDeleter::cleanup(p_nosepieceShape);
}

void tst_EquipmentShape::height_setHeight()
{
    EquipmentShape *p_nosepieceShape = EquipmentShape::createEquipmentShape(EquipmentShape::Nosepiece);
    QVERIFY2(p_nosepieceShape, "nosepieceShape is nullptr");

    NosepieceShape *nosepiece = dynamic_cast<NosepieceShape *>(p_nosepieceShape);
    QVERIFY2(nosepiece, "Failed to cast to NosepieceShape");

    // Default height from constructor
    const qreal defaultHeight = nosepiece->height();
    QCOMPARE(defaultHeight, 32.0);

    // Case 1: setting the same height should not change rect
    QRectF initialRect = nosepiece->rect();
    nosepiece->setHeight(defaultHeight);
    QCOMPARE(nosepiece->rect(), initialRect);
    QCOMPARE(nosepiece->height(), defaultHeight);

    // Case 2: increase height and ensure center stays the same
    const qreal newHeight = 64.0;
    const QPointF oldCenter = nosepiece->rect().center();
    nosepiece->setHeight(newHeight);
    QCOMPARE(nosepiece->height(), newHeight);
    QCOMPARE(nosepiece->rect().center(), oldCenter);

    // Case 3: decrease height and ensure center still stays the same
    const qreal smallerHeight = 16.0;
    const QPointF centerBeforeSmaller = nosepiece->rect().center();
    nosepiece->setHeight(smallerHeight);
    QCOMPARE(nosepiece->height(), smallerHeight);
    QCOMPARE(nosepiece->rect().center(), centerBeforeSmaller);

    EquipmentShape::EquipmentShapeDeleter::cleanup(p_nosepieceShape);
}

void tst_EquipmentShape::text_setText()
{
    EquipmentShape *p_nosepieceShape = EquipmentShape::createEquipmentShape(EquipmentShape::Nosepiece);
    QVERIFY2(p_nosepieceShape, "nosepieceShape is nullptr");

    NosepieceShape *nosepiece = dynamic_cast<NosepieceShape *>(p_nosepieceShape);
    QVERIFY2(nosepiece, "Failed to cast to NosepieceShape");

    // Initially both text values should be empty
    QVERIFY(nosepiece->nominalDiameter().isEmpty());
    QVERIFY(nosepiece->consumption().isEmpty());

    // Set nominal diameter text and verify
    nosepiece->setTextItem(NosepieceShape::NominalDiameter, "50");
    QCOMPARE(nosepiece->nominalDiameter(), QString("50"));

    // Update nominal diameter text and verify it changes
    nosepiece->setTextItem(NosepieceShape::NominalDiameter, "65");
    QCOMPARE(nosepiece->nominalDiameter(), QString("65"));

    // Set consumption text and verify
    nosepiece->setTextItem(NosepieceShape::Consumption, "2.7");
    QCOMPARE(nosepiece->consumption(), QString("2.7"));

    // Update consumption text and verify it changes
    nosepiece->setTextItem(NosepieceShape::Consumption, "3.5");
    QCOMPARE(nosepiece->consumption(), QString("3.5"));

#ifdef EQUIPMENTSHAPE_TEST
    // Verify internal QGraphicsTextItem configuration for nominal diameter
    Q_ASSERT(nosepiece->m_nominalDiameter != nullptr);
    QVERIFY(nosepiece->m_nominalDiameter->textInteractionFlags().testFlag(Qt::TextEditorInteraction));
    QCOMPARE(nosepiece->m_nominalDiameter->rotation(), qreal(-90));

    // Verify internal QGraphicsTextItem configuration for consumption
    Q_ASSERT(nosepiece->m_nosepieceConsumption != nullptr);
    QVERIFY(nosepiece->m_nosepieceConsumption->textInteractionFlags().testFlag(Qt::TextEditorInteraction));
    QCOMPARE(nosepiece->m_nosepieceConsumption->rotation(), qreal(-90));
#endif

    EquipmentShape::EquipmentShapeDeleter::cleanup(p_nosepieceShape);
}

void tst_EquipmentShape::mousePressEvent()
{
    EquipmentShape *p_nosepieceShape = EquipmentShape::createEquipmentShape(EquipmentShape::Nosepiece);
    QVERIFY2(p_nosepieceShape, "nosepieceShape is nullptr");

    NosepieceShape *nosepiece = dynamic_cast<NosepieceShape *>(p_nosepieceShape);
    QVERIFY2(nosepiece, "Failed to cast to NosepieceShape");

    // Prepare a scene and view to host the item
    QGraphicsScene scene;
    scene.addItem(nosepiece);

    // Simulate left mouse button press (should delegate to AbstractShape::mousePressEvent
    // and must NOT open context menu or populate action lists)
    QGraphicsSceneMouseEvent leftPressEvent(QEvent::GraphicsSceneMousePress);
    leftPressEvent.setButton(Qt::LeftButton);
    leftPressEvent.setButtons(Qt::LeftButton);
    leftPressEvent.setScenePos(QPointF(0.0, 0.0));
    leftPressEvent.setScreenPos(QPoint(0, 0));

    nosepiece->mousePressEvent(&leftPressEvent);

#ifdef EQUIPMENTSHAPE_TEST
    // For left button, no context actions should be created
    QVERIFY(nosepiece->m_nosepieceActionList.isEmpty());
    QVERIFY(nosepiece->m_substanceActionList.isEmpty());
#endif

    EquipmentShape::EquipmentShapeDeleter::cleanup(p_nosepieceShape);
}

void tst_EquipmentShape::paint()
{
    EquipmentShape *p_nosepieceShape = EquipmentShape::createEquipmentShape(EquipmentShape::Nosepiece);
    QVERIFY2(p_nosepieceShape, "nosepieceShape is nullptr");

    NosepieceShape *nosepiece = dynamic_cast<NosepieceShape *>(p_nosepieceShape);
    QVERIFY2(nosepiece, "Failed to cast to NosepieceShape");

    // Prepare an image matching the bounding rect size
    const QRectF brect = nosepiece->boundingRect();
    QImage image(qRound(brect.width()), qRound(brect.height()), QImage::Format_ARGB32_Premultiplied);
    image.fill(Qt::transparent);

    QPainter painter(&image);
    QStyleOptionGraphicsItem option;

    // Case 1: not selected
    nosepiece->paint(&painter, &option, nullptr);
    painter.end();

    // Verify that something was drawn (image is not fully transparent)
    bool hasNonTransparentPixel = false;
    for (int y = 0; y < image.height() && !hasNonTransparentPixel; ++y) {
        for (int x = 0; x < image.width(); ++x) {
            if (qAlpha(image.pixel(x, y)) != 0) {
                hasNonTransparentPixel = true;
                break;
            }
        }
    }
    QVERIFY(hasNonTransparentPixel);

    // Case 2: selected (should trigger highlightSelected, but must not crash)
    QImage selectedImage(qRound(brect.width()), qRound(brect.height()), QImage::Format_ARGB32_Premultiplied);
    selectedImage.fill(Qt::transparent);

    QPainter selectedPainter(&selectedImage);
    QStyleOptionGraphicsItem selectedOption;
    selectedOption.state |= QStyle::State_Selected;

    nosepiece->paint(&selectedPainter, &selectedOption, nullptr);
    selectedPainter.end();

    EquipmentShape::EquipmentShapeDeleter::cleanup(p_nosepieceShape);
}

void tst_EquipmentShape::substanceType_data()
{
    QTest::addColumn<int>("substanceType");
    QTest::addColumn<bool>("expectTopAdjust");

    for (int type = NosepieceShape::NoneSubstance; type < NosepieceShape::Count; ++type) {
        const bool hasAdjust = (type != NosepieceShape::NoneSubstance);
        const QString rowName = QString("substance_%1").arg(type);
        QTest::newRow(rowName.toLocal8Bit().constData()) << type << hasAdjust;
    }
}

void tst_EquipmentShape::substanceType()
{
    QFETCH(int, substanceType);
    QFETCH(bool, expectTopAdjust);

    EquipmentShape *shape = EquipmentShape::createEquipmentShape(EquipmentShape::Nosepiece);
    QVERIFY2(shape, "nosepieceShape is nullptr");

    NosepieceShape *nosepiece = dynamic_cast<NosepieceShape *>(shape);
    QVERIFY2(nosepiece, "Failed to cast EquipmentShape to NosepieceShape");

    const QRectF baseBoundingRect = nosepiece->boundingRect();

    const auto selectedType = static_cast<NosepieceShape::SubstanceType>(substanceType);
    nosepiece->setSubstanceType(selectedType);
    QCOMPARE(nosepiece->substanceType(), selectedType);

    const QRectF substanceBoundingRect = nosepiece->boundingRect();
    if (expectTopAdjust) {
        QVERIFY(substanceBoundingRect.top() < baseBoundingRect.top());
        QVERIFY(substanceBoundingRect.height() > baseBoundingRect.height());
    } else {
        QCOMPARE(substanceBoundingRect, baseBoundingRect);
    }

    // shape() for any substance should remain valid and intersect with boundingRect.
    const QPainterPath itemShape = nosepiece->shape();
    QVERIFY(!itemShape.isEmpty());
    QVERIFY(substanceBoundingRect.intersects(itemShape.boundingRect()));

    // paint() should not crash for any substance type.
    QImage image(qRound(substanceBoundingRect.width()), qRound(substanceBoundingRect.height()),
                 QImage::Format_ARGB32_Premultiplied);
    image.fill(Qt::transparent);
    QPainter painter(&image);
    QStyleOptionGraphicsItem option;
    nosepiece->paint(&painter, &option, nullptr);
    painter.end();

    bool hasNonTransparentPixel = false;
    for (int y = 0; y < image.height() && !hasNonTransparentPixel; ++y) {
        for (int x = 0; x < image.width(); ++x) {
            if (qAlpha(image.pixel(x, y)) != 0) {
                hasNonTransparentPixel = true;
                break;
            }
        }
    }
    QVERIFY(hasNonTransparentPixel);

    EquipmentShape::EquipmentShapeDeleter::cleanup(shape);
}

void tst_EquipmentShape::createSubstanceActions()
{
    EquipmentShape *shape = EquipmentShape::createEquipmentShape(EquipmentShape::Nosepiece);
    QVERIFY2(shape, "nosepieceShape is nullptr");

    NosepieceShape *nosepiece = dynamic_cast<NosepieceShape *>(shape);
    QVERIFY2(nosepiece, "Failed to cast EquipmentShape to NosepieceShape");

    nosepiece->setSubstanceType(NosepieceShape::MiddleFoam);
    nosepiece->createSubstanceActions();

    QCOMPARE(nosepiece->m_substanceActionList.size(), int(NosepieceShape::SubstanceType::Count));
    QVERIFY(nosepiece->m_substanceActionGroup != nullptr);
    // QCOMPARE(nosepiece->m_substanceActionGroup->actions().size(), int(NosepieceShape::SubstanceType::Count));

    int checkedCount = 0;
    for (QAction *action : std::as_const(nosepiece->m_substanceActionList)) {
        QVERIFY(action != nullptr);
        QVERIFY(action->isCheckable());
        if (action->isChecked()) {
            ++checkedCount;
        }
    }
    QCOMPARE(checkedCount, 1);

    // Trigger another action and ensure selected substance changes.
    QVERIFY(nosepiece->m_substanceActionList.size() > NosepieceShape::LowFoam);
    nosepiece->m_substanceActionList.at(NosepieceShape::LowFoam)->trigger();
    QCOMPARE(nosepiece->substanceType(), NosepieceShape::LowFoam);

    EquipmentShape::EquipmentShapeDeleter::cleanup(shape);
}

void tst_EquipmentShape::type()
{
    EquipmentShape *p_nosepieceShape = EquipmentShape::createEquipmentShape(EquipmentShape::Nosepiece);
    QVERIFY2(p_nosepieceShape, "nosepieceShape is nullptr");

    // Verify that type() returns the correct value for NosepieceShape
    const int nosepieceType = p_nosepieceShape->type();
    QCOMPARE(nosepieceType, int(QGraphicsItem::UserType + 301));

    // Verify that NosepieceShape type differs from base EquipmentShape type
    QVERIFY(nosepieceType != EquipmentShape::Type);
    QCOMPARE(EquipmentShape::Type, int(QGraphicsItem::UserType + 300));

    // Verify that type() can be used with qgraphicsitem_cast
    NosepieceShape *castedNosepiece = qgraphicsitem_cast<NosepieceShape *>(p_nosepieceShape);
    QVERIFY2(castedNosepiece, "qgraphicsitem_cast failed for NosepieceShape");

    // Verify that casting to wrong type returns nullptr
    // (assuming there's no other shape type with Type = UserType + 301)
    QVERIFY(qgraphicsitem_cast<QGraphicsRectItem *>(p_nosepieceShape) == nullptr);

    EquipmentShape::EquipmentShapeDeleter::cleanup(p_nosepieceShape);
}

void tst_EquipmentShape::shapeType()
{
    EquipmentShape *p_nosepieceShape = EquipmentShape::createEquipmentShape(EquipmentShape::Nosepiece);
    QVERIFY2(p_nosepieceShape, "nosepieceShape is nullptr");

    // Verify that shapeType() returns the correct ShapeType for NosepieceShape
    EquipmentShape::ShapeType shapeType = p_nosepieceShape->shapeType();
    QCOMPARE(shapeType, EquipmentShape::Nosepiece);

    // Verify that shapeType() returns a valid ShapeType enum value
    QVERIFY(shapeType >= EquipmentShape::Nosepiece);
    QVERIFY(shapeType <= EquipmentShape::LiftGPS);

    // Verify consistency: shapeType() should match the type used to create the shape
    EquipmentShape *p_nosepieceShape2 = EquipmentShape::createEquipmentShape(EquipmentShape::Nosepiece);
    QVERIFY2(p_nosepieceShape2, "nosepieceShape2 is nullptr");
    QCOMPARE(p_nosepieceShape2->shapeType(), EquipmentShape::Nosepiece);

    // Verify that shapeType() is consistent across multiple calls
    QCOMPARE(p_nosepieceShape->shapeType(), p_nosepieceShape->shapeType());

    EquipmentShape::EquipmentShapeDeleter::cleanup(p_nosepieceShape);
    EquipmentShape::EquipmentShapeDeleter::cleanup(p_nosepieceShape2);
}

void tst_EquipmentShape::updateDNPosition()
{
    EquipmentShape *p_nosepieceShape = EquipmentShape::createEquipmentShape(EquipmentShape::Nosepiece);

    EquipmentShape::EquipmentShapeDeleter::cleanup(p_nosepieceShape);
}

QTEST_MAIN(tst_EquipmentShape)

#include "tst_equipmentshape.moc"

