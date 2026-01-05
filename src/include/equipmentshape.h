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

/*!
 * \file
 *  \brief This header file contains declarations like classes used to draw fire
 *  equipment.
 *
 *  The equipmentshape.h is a header file that contains a declarations of the Nosepiece,
 *  Branching, Stair, Collector, HoseBridge, HoseReel, Hydroelevator, FoamMixer,
 *  FireColumn, SmokePump, Hose, FoamLift and LiftGPS classes.
 *  \copyright (C) 2022 by Viktor Ermolov <ermolovva@gmail.com>.
 *  You can redistribute it and/or modify it under the terms of the
 *  GNU General Public License as published by the Free Software Foundation,
 *  either version 3 of the License, or (at your option) any later version.
 *  \date October 18 2024
 *  \author Ermolov V.A.
 */

/*!
 * \defgroup EquipmentShapes Equipment shapes library
 * \brief This module is a fire equipment library of shapes for the RSiSed application.
 * \ingroup libshapes
 *
 *  This module includes elements designed to create fire fighting equipment (nosepieces,
 *  branches, stairs, hoses, etc.).
 */
///@{

#ifndef EQUIPMENTSHAPE_H
#define EQUIPMENTSHAPE_H

#include "abstractshape.h"

/*!
 * \brief The EquipmentShape class is an interface class for creating fire fighting
 *  equipment shapes.
 *
 *  The class has an available static factory function that returns a pointer
 *  to the base class, with which instances of the corresponding classes are
 *  created.
 *
 *  \sa Nosepiece, Branching, Stair, Collector, HoseBridge, HoseReel, Hydroelevator,
 *  FoamMixer, FireColumn, SmokePump, Hose, FoamLift and LiftGPS.
 */
class EquipmentShape : public AbstractShape
{
public:

    /*!
     * \brief Identifier for the equipment shape type.
     *
     *  Used to uniquely identify the shape type within the system.
     *  The value is set to `UserType + 300`.
     *  \sa EquipmentShape
     */
    enum {Type = UserType + 300};
/*    enum ShapeType { Barrel_0       //РС (nosepiece)
                     , Barrel_1     //РС 50
                     , Barrel_2     //РС 70
                     , Barrel_3     //Ствол ручной высокого давления
                     , Barrel_4     //СВП
                     , Barrel_5     //ГПС
                     , Barrel_6     //Ствол ручной с добавками
                     , Carriage_1   //Переносной лафетный ствол (fire monitor)
                     , Carriage_2   //Лафетный ствол стационарный с водяными насадками
                     , Carriage_3   //Лафетный ствол стационарный порошковый
                     , Carriage_4   //Лафетный ствол стационарный с пенными насадками
                     , Carriage_5   //Лафетный ствол возимый
                     , Branches_2   //РД
                     , Branches_3   //РТ
                     , Branches_4   //РЧ
                     , Ladder_1     //ЛП
                     , Ladder_2     //ЛШ
                     , Ladder_3     //ВПЛ
                     , Collector    //Водосборник
                     , Bridge       //Рукавный мостик
                     , Reel         //Рукавная катушка
                     , Reel_mobile  //Рукавная катушка возимая
                     , HydrElevator //Гидроэлеватор
                     , Foam_mix     //Пеносмеситель
                     , Column       //Колонка пожарная
                     , SmokePump_1  //Дымосос переносной
                     , SmokePump_2  //Дымосос прицепной
                     , Hose         //Рукав всасывающий
                     , FoamLift_1   //Подёмник-пенослив
                     , FoamLift_2 };//Подъёмник пенный с гребёнокой генераторов ГПС-600
*/
    /*!
     * \enum ShapeType
     * \brief Enumeration of possible shapes for fire fighting equipment.
     *
     *  This enumeration lists the different types of equipment used in fire fighting
     *  operations.
     */
    enum ShapeType { Nosepiece, /*!< Includes all types fire nosepieces */
                     Branch, /*!< Includes all types fire branches */
                     Ladder, /*!< Includes all types fire ladders */
                     Collector, /*!< Water collector */
                     HoseBridge, /*!< Fire hose bridge */
                     HoseReel, /*!< Includes all types of coils for fire hoses */
                     Hydroelevator, /*!< Injection fire pump for water intake (hydraulic elevator) */
                     FoamMixer, /*!< Foam mixer */
                     FireColumn, /*!< Fire pump for water intake from the hydrant */
                     SmokePump, /*!< Includes all types of smoke pumps */
                     Hose, /*!< Includes all types of fire hoses */
                     FoamLift, /*!< Fire foam lifter */
                     LiftGPS /*!< Fire foam lifter with multiple foam generators */
    };

    /*!
     * \brief The EquipmentShapeDeleter struct is a custom cleanup handler.
     *
     * EquipmentShapeDeleter is a custom deleter class needed when creating
     * client-side objects using smart pointers.
     *
     * \sa deleter(), cleanup().
     */
    struct EquipmentShapeDeleter
    {
        /*!
         * Constructs a EquipmentShapeDeleter.
         * Creation of the EquipmentShapeDeleter class is prohibited.
         */
        EquipmentShapeDeleter() = delete;

        /*!
         * Static method remover.
         *
         * \param *equipmentShape[in] The pointer to the object to be deleted.
         * \sa deleter().
         */
        static inline void cleanup(EquipmentShape *equipmentShape) {equipmentShape->deleter();}
    };

    /*!
     * \brief Creates a new equipment shape of the specified type.
     *
     * This is a factory method that creates instances of equipment shapes
     * based on the provided ShapeType. The method returns a pointer to the
     * base EquipmentShape class, which can be cast to the specific shape type
     * as needed.
     *
     * \param shapeType[in] The type of equipment shape to create. Must be one
     *                      of the values from the ShapeType enumeration.
     * \param parent[in] Optional pointer to the parent QGraphicsItem. This is
     *                   used for Qt's memory management and scene hierarchy.
     *                   Defaults to nullptr if not specified.
     *
     * \return Returns a pointer to the newly created EquipmentShape object,
     *         or nullptr if the shapeType is not recognized or not yet
     *         implemented.
     *
     * \note The caller is responsible for managing the memory of the returned
     *       pointer. Consider using smart pointers with EquipmentShapeDeleter
     *       for automatic memory management.
     *
     * \note Currently only Nosepiece shape type is implemented. Other types
     *       will return nullptr.
     *
     * \example
     * \code
     * EquipmentShape *shape = EquipmentShape::createEquipmentShape(
     *     EquipmentShape::Nosepiece, parentItem);
     * if (shape) {
     *     scene->addItem(shape);
     * }
     * \endcode
     *
     * \sa ShapeType, EquipmentShapeDeleter, NosepieceShape
     */
    static EquipmentShape *createEquipmentShape(ShapeType shapeType, QGraphicsItem *parent = nullptr);

    /*!
     * This type information is used by qgraphicsitem_cast() to distinguish
     * between types.
     * All standard graphicsitem classes are associated with a unique value;
     * see QGraphicsItem::Type. The default implementation (in QGraphicsItem)
     * returns UserType. To enable use of qgraphicsitem_cast() with a custom
     * item, reimplement this function and declare a Type enum value equal to
     * your custom item's type. Custom items must return a value larger than
     * or equal to UserType (65536).
     *
     * \return Returns the type of an item as an int.
     */
    inline int type() const override {return Type;}

    /*!
     * A pure virtual method that needs to be overridden in a child class.
     * Required to create a shape icon in ShapeToolBox.
     * Used by the MainWindow::createEuipmentShapeCellWidget() method to
     * create a shape icon in the ShapeToolBox.
     *
     * \return Returns a QPixmap object containing the shape image.
     */
    virtual QPixmap image() = 0;

    /*!
     * A pure virtual method that needs to be overridden in a child class.
     * Required to determine the actual type of the object.
     *
     * \return Returns the ShapeType (Nosepiece or Branch etc.).
     * \sa ShapeType.
     */
    virtual ShapeType shapeType() const = 0;

    /*!
     * \brief A pure virtual method that needs to be overridden in a child class.
     *
     * This method is used to set the size and position of the shape using
     * a rectangle. The rectangle defines both the geometry and position of
     * the shape in local coordinates.
     *
     * \param rect[in] The rectangle that defines the shape's size and position.
     *                 The rectangle is specified in local coordinates of the
     *                 shape item.
     *
     * \note Implementations should call prepareGeometryChange() before
     *       modifying the shape's geometry to notify the scene about the
     *       impending change.
     *
     * \note The actual implementation may adjust the rectangle based on the
     *       shape's specific requirements (e.g., substance type for nosepiece).
     *
     * \sa rect(), prepareGeometryChange()
     */
    virtual void setRect(const QRectF &rect) = 0;

    /*!
     * \brief A pure virtual method that needs to be overridden in a child class.
     *
     * Returns the rectangle that defines the shape's size and position.
     * The rectangle is returned in local coordinates and represents the
     * base geometry of the shape without pen width adjustments.
     *
     * \return Returns the shape's rectangle in local coordinates. This is
     *         the rectangle that was set via setRect(), possibly adjusted
     *         for internal requirements.
     *
     * \note This rectangle does not include pen width. For the bounding
     *       rectangle including pen width, use boundingRect().
     *
     * \sa setRect(), boundingRect()
     */
    virtual QRectF rect() const = 0;

    /*!
     * \brief A pure virtual method that needs to be overridden in a child class.
     *
     * This method is used to set the height of the shape while maintaining
     * its width and center position. The shape will be resized vertically
     * around its center point.
     *
     * \param height[in] The new height for the shape in local coordinates.
     *                  Must be a positive value.
     *
     * \note Implementations should call prepareGeometryChange() before
     *       modifying the shape's geometry to notify the scene about the
     *       impending change.
     *
     * \note If the height is the same as the current height, the method
     *       should return early without triggering a geometry change.
     *
     * \sa height(), setRect()
     */
    virtual void setHeight(const qreal &height) = 0;

    /*!
     * \brief A pure virtual method that needs to be overridden in a child class.
     *
     * Returns the current height of the shape in local coordinates.
     * The height is measured vertically along the shape's local y-axis.
     *
     * \return Returns the shape's height as a qreal value in local coordinates.
     *
     * \note This is typically the height of the base rectangle returned by rect().
     *
     * \sa setHeight(), rect()
     */
    virtual qreal height() const = 0;

protected:
    /*!
     * \brief Constructs an EquipmentShape object.
     *
     * The constructor is declared protected because EquipmentShape is an
     * abstract base class. It should only be called from derived class
     * constructors.
     *
     * \param parent[in] Optional pointer to the parent QGraphicsItem. This
     *                   is used for Qt's memory management and scene hierarchy.
     *                   Defaults to nullptr if not specified.
     *
     * \sa AbstractShape
     */
    explicit EquipmentShape(QGraphicsItem *parent = nullptr);

    /*!
     * \brief Destroys the EquipmentShape object.
     *
     * The destructor is declared protected and virtual to ensure proper
     * cleanup of derived classes. It is defined as default, meaning it
     * performs no special cleanup beyond what the base class provides.
     */
    virtual ~EquipmentShape() = 0;

    /*!
     * \brief Protected method for deleting the equipment shape.
     *
     * This method is declared protected to prevent direct deletion by clients.
     * It should be used in conjunction with EquipmentShapeDeleter when working
     * with smart pointers. This design pattern helps reduce errors associated
     * with manual memory management.
     *
     * \note Clients should use EquipmentShapeDeleter::cleanup() instead of
     *       calling this method directly.
     *
     * \sa EquipmentShapeDeleter::cleanup()
     */
    virtual void deleter();

private:
    /*
     * This class contains a private copy constructor and assignment
     * operator to disable copying (the compiler gives an error message).
     * This makros defined in the qlobal.h file
    */
    Q_DISABLE_COPY(EquipmentShape)
};

/*!
 * \brief The NosepieceShape class provides nosepice item.
 *
 * The nosepieceShape class is an image of a fire nosepiece. This allows you to change
 * the size, position, type of fire nosepiece and the type of extinguishing agent used.
 *
 * \sa Branchshape, LadderShape, CollectorShape, HoseBridgeshape, HoseReelShape,
 * HydroelevatorShape, FoamMixerShape, FireColumnShape, SmokePumpShape, Hoseshape,
 * FoamLiftShape, LiftGPSShape
 */
class NosepieceShape : public EquipmentShape
{
public:

    //! This type information is used by qgraphicsitem_cast to distinguish between types.
    enum { Type = UserType + 301 };

    //! Sets the type of extinguishing agent.
    enum SubstanceType { NoneSubstance        //!< The fire extinguishing substance is not indicated.
                         , CompactWater       //!< Compact stream of water.
                         , SprayedWater      //!< Sprayed water stream.
                         , ThinlySprayedWater //!< Thin-poured stream of water.
                         , LowFoam            //!< Low multiplicity foam.
                         , MiddleFoam         //!< Middle multiplicity foam.
                         , HighFoam           //!< Foam of high multiplicity.
                         , WaterFoam          //!< Aqueous solution of the foaming agent.
                         , WaterAdditives     //!< Water with additives.
                         , Powder             //!< Fire extinguishing powder.
                         , Powder_BC          //!< Powder designed to extinguish fires of BC classes.
                         , Powder_ABC         //!< Powder designed to extinguish fires of ABC classes.
                         , Chladon            //!< Refrigerants for extinguishing fires.
                         , CarbonDioxide      //!< Carbon dioxide for extinguishing fires.
                         , WaterVapor         //!< Water steam for extinguishing fires.
                         , Gas                //!< Gas for extinguishing fires.
                         , Count              //!< The number of elements in the SubstanceType enumeration
    };

    /*!
     * \enum TextItemType
     * \brief Enumeration for types of text items that can be displayed on a nosepiece shape.
     *
     * This enumeration is used to specify which type of text item should be set
     * when calling the setTextItem() method. Each type corresponds to a specific
     * QGraphicsTextItem member of the NosepieceShape class.
     *
     * \sa setTextItem(), nominalDiameter(), consumption()
     */
    enum TextItemType { NominalDiameter      //!< Nominal diameter (DN) - the diameter of the firefighting nozzle connection.
                       , Consumption         //!< Consumption - the flow rate of the firefighting substance.
    };

    /*!
    * \brief Constructs a NosepieceShape object.
    *
    * Initializes a new nosepiece shape with default values:
    * - Equipment type: Nosepiece
    * - Initial rectangle: QRectF(-6.0, -16.0, 12.0, 32.0)
    * - Nominal diameter and consumption text items: nullptr (not created yet)
    * - Visibility flags: both false (hidden)
    * - Substance type: NoneSubstance (no indicator)
    * - Flags: ItemSendsGeometryChanges and accept hover events enabled
    * - Pen: black with width 1
    *
    * The nosepiece shape represents a firefighting nozzle that can display
    * nominal diameter, consumption, and fire extinguishing substance type
    * indicators.
    *
    * \param parent[in] Optional pointer to the parent QGraphicsItem. This is
    *                   used for Qt's memory management and scene hierarchy.
    *                   Defaults to nullptr if not specified.
    *
    * \note Text items (nominal diameter and consumption) are created lazily
    *       when first set or shown via the context menu.
    *
    * \sa setTextItem(), setSubstanceType(), nominalDiameterShow(), consumptionShow()
    */
    explicit NosepieceShape(QGraphicsItem *parent = nullptr);

    /*!
     * All standard graphicsitem classes are associated with a unique value;
     * see QGraphicsItem::Type. This type information is used by
     * qgraphicsitem_cast() to distinguish between types. Custom items must
     * return a value larger than or equal to UserType (65536).
     *
     * \return Returns the type of an item as an int.
     */
    inline int type() const override {return Type;}

    /*!
     * \brief Reimplements QGraphicsItem::paint().
     *
     * This method is called by QGraphicsView to paint the nosepiece shape
     * in local coordinates. It draws the nosepiece body, any text items
     * (nominal diameter or consumption), and the substance type indicator
     * if set.
     *
     * If the item is selected, it also draws selection highlighting.
     *
     * \param painter[in] The painter to use for drawing. Must not be null.
     * \param option[in] Style options that provide information about how
     *                   the item should be drawn, including its state
     *                   (selected, hovered, etc.) and level-of-detail hints.
     * \param widget[in] Optional pointer to the widget being painted on.
     *                   This is typically nullptr for cached painting.
     *
     * \sa QGraphicsItem::paint(), drawNosepiece(), drawSubstance()
     */
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;

    /*!
     * \brief Reimplements QGraphicsItem::boundingRect().
     *
     * Returns the bounding rectangle of the nosepiece shape, including
     * any substance type indicators that extend above the base shape.
     * The bounding rect is used by QGraphicsView to determine whether
     * the item needs to be repainted and for collision detection.
     *
     * The bounding rectangle includes half the pen width on all sides
     * to ensure proper rendering of the shape's outline.
     *
     * \return Returns the bounding rectangle of the nosepiece shape in
     *         local coordinates, adjusted for pen width and substance
     *         type indicators.
     *
     * \note The bounding rect always includes the full area that might
     *       be painted, including the substance type symbols that extend
     *       above the nosepiece base.
     *
     * \sa shape(), rect(), calculateTopAdjust(), adjustForPenWidth()
     */
    QRectF boundingRect() const override;

    /*!
     * \brief Reimplements QGraphicsItem::shape().
     *
     * Returns the exact shape of the nosepiece as a QPainterPath, which
     * includes both the nosepiece body and any substance type indicators.
     * This shape is used for precise collision detection and hit testing.
     *
     * The shape path includes:
     * - The nosepiece body (base line, center line, and arrow)
     * - Substance type symbols (circles, squares, or triangles) if set
     *
     * \return Returns a QPainterPath representing the exact shape of the
     *         nosepiece in local coordinates.
     *
     * \sa boundingRect(), contains(), collidesWithPath()
     */
    QPainterPath shape() const override;

    /*!
     * \brief Reimplements EquipmentShape::image().
     *
     * Creates and returns a pixmap containing an icon representation of
     * the nosepiece shape. This is used to create shape icons in the
     * ShapeToolBox for user selection.
     *
     * The pixmap is created by painting the nosepiece shape onto a
     * transparent pixmap of the appropriate size, centered within the
     * pixmap.
     *
     * \return Returns a QPixmap containing the nosepiece shape icon,
     *         with transparent background.
     *
     * \note The pixmap size is determined by the current boundingRect()
     *       of the shape.
     *
     * \sa drawNosepiece(), boundingRect()
     */
    QPixmap image() override;

    /*!
     * \brief Reimplements EquipmentShape::shapeType().
     *
     * Returns the equipment shape type for this nosepiece. This method
     * is used to determine the actual type of equipment shape instance.
     *
     * \return Returns EquipmentShape::Nosepiece, indicating this is a
     *         nosepiece shape instance.
     *
     * \sa ShapeType, type()
     */
    ShapeType shapeType() const override;

    /*!
     * \brief Reimplements EquipmentShape::setRect().
     *
     * Sets the size and position of the nosepiece shape using a rectangle.
     * The rectangle is adjusted to account for any substance type indicators
     * that extend above the base shape. If the rectangle hasn't changed,
     * the method returns early without triggering a geometry update.
     *
     * After setting the rectangle, the consumption position is updated
     * if consumption is currently visible.
     *
     * \param rect[in] The rectangle defining the new size and position
     *                 of the nosepiece in local coordinates.
     *
     * \note This method calls prepareGeometryChange() before modifying
     *       the geometry and update() after to trigger a repaint.
     *
     * \note The actual nosepiece rectangle may differ from the input
     *       rectangle due to adjustments for substance type indicators.
     *
     * \sa rect(), calculateTopAdjust(), updateConsumptionPosition()
     */
    void setRect(const QRectF &rect) override;

    /*!
     * \brief Reimplements EquipmentShape::rect().
     *
     * Returns the base rectangle of the nosepiece shape without pen width
     * adjustments. This rectangle represents the core geometry of the
     * nosepiece excluding any substance type indicators that extend above
     * the base.
     *
     * \return Returns the nosepiece rectangle in local coordinates,
     *         excluding pen width.
     *
     * \note This is the rectangle that was set via setRect(), possibly
     *       adjusted for substance type. For the full bounding rectangle
     *       including substance indicators and pen width, use boundingRect().
     *
     * \sa setRect(), boundingRect()
     */
    QRectF rect() const override;

    /*!
     * \brief Reimplements EquipmentShape::setHeight().
     *
     * Sets the height of the nosepiece shape while maintaining its width
     * and center position. The shape is resized vertically around its
     * center point. If the new height is the same as the current height,
     * the method returns early.
     *
     * \param height[in] The new height for the nosepiece in local
     *                  coordinates. Must be a positive value.
     *
     * \note This method calls prepareGeometryChange() before modifying
     *       the geometry and update() after to trigger a repaint.
     *
     * \note The shape's center position is maintained during height changes.
     *
     * \sa height(), setRect()
     */
    void setHeight(const qreal &height) override;

    /*!
     * \brief Reimplements EquipmentShape::height().
     *
     * Returns the current height of the nosepiece shape in local coordinates.
     *
     * \return Returns the height of the nosepiece rectangle as a qreal value.
     *
     * \sa setHeight(), rect()
     */
    qreal height() const override;

    /*!
     * \brief Sets the text item value (nominal diameter or consumption).
     *
     * This method is a unified interface for setting either the nominal diameter
     * or consumption text on a nosepiece shape. It replaces the previous separate
     * methods setNominalDiameter() and setConsumption() to reduce code duplication.
     *
     * The method performs the following actions:
     * - If the corresponding QGraphicsTextItem hasn't been created yet, it creates
     *   a new QGraphicsTextItem as a child of this nosepiece shape
     * - Configures the text item with text editing interaction flags and rotates
     *   it -90 degrees for vertical display
     * - Sets the plain text content to the provided value
     * - Sets the corresponding visibility flag to true, making the text item visible
     *
     * \param textItemType[in] The type of text item to be set. Must be either
     *                         NosepieceShape::NominalDiameter or
     *                         NosepieceShape::Consumption.
     * \param value[in] The text value to be displayed, provided as a QString.
     *                  For nominal diameter, this is typically a number like "50"
     *                  or "70". For consumption, this is typically a decimal number
     *                  like "2.7" or "3.5".
     *
     * \note The text item will be displayed rotated -90 degrees from the default
     *       orientation. The text is editable by default when the user interacts
     *       with it in the graphics scene.
     *
     * \note Calling this method automatically makes the text item visible. To hide
     *       it, use the context menu options "Hide DN" or "Hide consumption".
     *
     * \internal
     * The method uses a conditional statement to select the appropriate member
     * variable (m_nominalDiameter or m_nosepieceConsumption) and visibility flag
     * (m_showDN or m_showConsumption) based on the textItemType parameter.
     *
     * \example
     * \code
     * NosepieceShape *nosepiece = new NosepieceShape();
     * // Set nominal diameter
     * nosepiece->setTextItem(NosepieceShape::NominalDiameter, "50");
     * // Set consumption
     * nosepiece->setTextItem(NosepieceShape::Consumption, "2.7");
     * \endcode
     *
     * \sa TextItemType, nominalDiameter(), consumption(), setSubstanceType()
     */
    void setTextItem(TextItemType textItemType, const QString &value);

    /*!
     * \brief Returns the nominal diameter of the nosepiece shape.
     *
     * Returns the text content of the nominal diameter (DN) text item if it
     * has been set and is currently displayed. If the nominal diameter text
     * item has not been created or is not set, returns an empty string.
     *
     * \return Returns the nominal diameter as a QString, or an empty string
     *         if the nominal diameter text item is nullptr or not initialized.
     *
     * \note This method does not return the actual diameter value, but rather
     *       the text that is displayed in the graphics scene.
     *
     * \sa setTextItem(), consumption()
     */
    QString nominalDiameter() const;

    /*!
     * \brief Returns the consumption of the nosepiece shape.
     *
     * Returns the text content of the consumption text item if it has been
     * set and is currently displayed. If the consumption text item has not
     * been created or is not set, returns an empty string.
     *
     * \return Returns the consumption as a QString, or an empty string if
     *         the consumption text item is nullptr or not initialized.
     *
     * \note This method does not return the actual consumption value, but
     *       rather the text that is displayed in the graphics scene.
     *
     * \sa setTextItem(), nominalDiameter()
     */
    QString consumption() const;

    /*!
     * \brief Sets the type of fire extinguishing substance used by the nosepiece.
     *
     * This method sets the substance type, which determines what visual
     * indicator (symbol) is drawn above the nosepiece to represent the type
     * of extinguishing agent being used (water, foam, powder, gas, etc.).
     *
     * Different substance types result in different visual representations:
     * - Water types: circles (1-3 depending on spray type)
     * - Foam types: circles with crosses (1-3 depending on multiplicity)
     * - Powder types: squares (with or without cross/fill)
     * - Gas types: triangles (with various fill patterns)
     *
     * Setting a substance type automatically updates the shape's bounding
     * rectangle to include space for the substance indicator symbol.
     *
     * \param newSubstanceType[in] The type of fire extinguishing substance
     *                            to be set. Must be one of the values from
     *                            the SubstanceType enumeration.
     *
     * \note Setting a substance type may change the bounding rectangle and
     *       require a repaint of the shape.
     *
     * \note To remove the substance indicator, set the substance type to
     *       SubstanceType::NoneSubstance.
     *
     * \sa SubstanceType, substanceType(), drawSubstance(), calculateTopAdjust()
     */
    void setSubstanceType(SubstanceType newSubstanceType);

    /*!
     * \brief Returns the current type of fire extinguishing substance.
     *
     * Returns the substance type that was previously set for this nosepiece.
     * This determines what visual indicator is drawn above the nosepiece.
     *
     * \return Returns the current SubstanceType value. If no substance type
     *         has been explicitly set, returns SubstanceType::NoneSubstance
     *         by default.
     *
     * \sa SubstanceType, setSubstanceType()
     */
    SubstanceType substanceType();

protected:

    /*!
     * \brief Destroys the NosepieceShape object.
     *
     * The destructor is declared protected and defined as default. All
     * cleanup is handled automatically by Qt's parent-child memory
     * management system, as QGraphicsTextItem children are deleted
     * automatically when the parent is destroyed.
     */
    ~NosepieceShape() = default;

    /*!
     * \brief Reimplements AbstractShape::mousePressEvent().
     *
     * Handles mouse press events on the nosepiece shape. If the right mouse
     * button is pressed, this method creates and displays a context menu
     * with options for:
     * - Showing/hiding nominal diameter (DN)
     * - Showing/hiding consumption
     * - Setting the substance type (via a submenu)
     * - Standard shape operations (delete, cut, etc.)
     *
     * If the left mouse button or other buttons are pressed, the event
     * is forwarded to the base class implementation.
     *
     * \param mouseEvent[in] Pointer to the QGraphicsSceneMouseEvent that
     *                      contains information about the mouse press event,
     *                      including button, position, and modifiers.
     *
     * \note The context menu is created dynamically on each right-click.
     *       Actions are removed after menu execution (except for delete and
     *       cut actions which may trigger object deletion).
     *
     * \sa createActions(), createSubstanceActions(), addSubstanceMenu()
     */
    void mousePressEvent(QGraphicsSceneMouseEvent *mouseEvent) override;

private:

    /*
     * This class contains a private copy constructor and assignment
     * operator to disable copying (the compiler gives an error message).
     * This makros defined in the qlobal.h file
    */
    Q_DISABLE_COPY(NosepieceShape)

    // Shape

    /*!
    * \brief Returns a static hash map containing adjustment factors for different substance types.
    *
    * This method returns a reference to a static hash map that maps each
    * SubstanceType to a multiplier factor. These factors are used to calculate
    * how much additional vertical space (top adjustment) is needed in the
    * bounding rectangle to accommodate the substance type indicator symbol.
    *
    * The adjustment factors represent how many times the nosepiece width should
    * be added to the top of the bounding rectangle:
    * - Water types: 0.75 to 2.25 (depending on spray type)
    * - Foam types: 1.0 to 3.0 (depending on multiplicity)
    * - Other types: typically 1.0
    *
    * \return Returns a const reference to a static QHash mapping SubstanceType
    *         to qreal adjustment factors.
    *
    * \note The hash map is created once and reused for all instances, making
    *       this an efficient operation.
    *
    * \sa calculateTopAdjust(), SubstanceType
    */
    const QHash<SubstanceType, qreal>& adjustFactors() const;

    /*!
    * \brief Updates the display position of the nominal diameter (DN) text item.
    *
    * This method recalculates and updates the position of the nominal diameter
    * text item based on the current position and dimensions of the nosepiece
    * rectangle. The text item is positioned to the left of the nosepiece center,
    * accounting for the text item's rotated bounding rectangle.
    *
    * The position is calculated to center the text item vertically relative to
    * the nosepiece center, and to position it horizontally at a fixed offset
    * from the nosepiece center point.
    *
    * \note This method only updates the position if m_showDN is true (the
    *       nominal diameter is currently visible).
    *
    * \note The calculation accounts for the fact that the text item is rotated
    *       -90 degrees, so its width and height are swapped relative to its
    *       bounding rectangle.
    *
    * \sa updateConsumptionPosition(), nominalDiameterShow()
    */
    void updateDNPosition();

    /*!
    * \brief Updates the display position of the consumption text item.
    *
    * This method recalculates and updates the position of the consumption
    * text item based on the current position and dimensions of the nosepiece
    * rectangle. The text item is positioned at the center of the nosepiece,
    * accounting for the text item's rotated bounding rectangle.
    *
    * The position is calculated to center the text item both horizontally and
    * vertically relative to the nosepiece center point.
    *
    * \note This method only updates the position if m_showConsumption is true
    *       (the consumption is currently visible).
    *
    * \note The calculation accounts for the fact that the text item is rotated
    *       -90 degrees, so its width and height are swapped relative to its
    *       bounding rectangle.
    *
    * \sa updateDNPosition(), consumptionShow()
    */
    void updateConsumptionPosition();

    /*!
    * \brief Draws the fire nosepiece shape.
    *
    * This method draws the main body of the nosepiece shape, which consists of:
    * - A horizontal base line at the bottom
    * - A vertical center line from bottom to top
    * - An arrow pointing upward (formed by two diagonal lines meeting at the top)
    *
    * After drawing the basic shape, the method:
    * - Updates and draws the nominal diameter text item if it's visible
    * - Updates and draws the consumption text item if it's visible
    * - Draws the substance type indicator if a substance type is set
    *
    * \param painter[in] The painter to use for drawing. Must not be null.
    *                   The painter should already be configured with the
    *                   appropriate pen and brush.
    *
    * \note The nosepiece is drawn using the shape's pen() and brush()
    *       properties, which should be set before calling this method.
    *
    * \note The method uses a pen width of 2 for the main nosepiece lines.
    *
    * \sa drawSubstance(), updateDNPosition(), updateConsumptionPosition(),
    *     paint()
    */
    void drawNosepiece(QPainter *painter);

    /*!
    * \brief Draws the fire extinguishing substance indicator symbol.
    *
    * This method draws a visual indicator above the nosepiece to represent
    * the type of fire extinguishing substance being used. Different substance
    * types are represented by different symbols:
    *
    * - Water types (CompactWater, SprayedWater, ThinlySprayedWater):
    *   Filled circles, 1-3 depending on spray type
    *
    * - Foam types (LowFoam, MiddleFoam, HighFoam, WaterFoam):
    *   Circles with crosses, 1-3 depending on multiplicity
    *
    * - Powder types (Powder, Powder_BC, Powder_ABC):
    *   Squares with various fill patterns and optional crosses
    *
    * - Gas types (Chladon, CarbonDioxide, WaterVapor, Gas):
    *   Triangles with various fill patterns and optional center lines
    *
    * The symbols are positioned above the nosepiece, with spacing determined
    * by the adjustment factors from adjustFactors().
    *
    * \param painter[in] The painter to use for drawing. Must not be null.
    *                   The painter should already be configured with the
    *                   appropriate pen and brush.
    *
    * \note This method should only be called if a substance type other than
    *       NoneSubstance is set.
    *
    * \note The symbols are drawn using predefined patterns and positions
    *       based on the nosepiece rectangle dimensions.
    *
    * \sa SubstanceType, setSubstanceType(), drawNosepiece(), adjustFactors()
    */
    void drawSubstance(QPainter *painter);

    /*!
    * \brief Calculates the top adjustment value for the nosepiece shape based on substance type.
    *
    * This method retrieves the adjustment factor corresponding to the current
    * substance type from adjustFactors() and multiplies it by the nosepiece
    * width to calculate how much additional vertical space is needed above
    * the nosepiece base to accommodate the substance type indicator symbol.
    *
    * The adjustment is used to:
    * - Extend the bounding rectangle upward to include substance symbols
    * - Adjust the nosepiece rectangle when setting new dimensions
    *
    * \return Returns the top adjustment as a qreal value in local coordinates.
    *         If the substance type is not found in the adjustment factors map
    *         or is NoneSubstance, returns 0.0.
    *
    * \note The adjustment is calculated as: nosepieceWidth * adjustmentFactor
    *
    * \sa adjustFactors(), boundingRect(), setRect()
    */
    qreal calculateTopAdjust() const;

    /*!
    * \brief Adjusts a rectangle to account for the pen width when drawing.
    *
    * This method calculates half of the pen width and adjusts the rectangle
    * by expanding it outward on all sides by this amount. This ensures that
    * the full width of the pen stroke is included in the bounding rectangle,
    * preventing clipping of the shape's outline.
    *
    * The adjustment is done using QRectF::adjust(), which expands the rectangle
    * symmetrically. If the pen style is Qt::NoPen, no adjustment is made.
    *
    * \param rect[in,out] The rectangle to adjust. The rectangle is modified
    *                    in-place by expanding it by half the pen width on all
    *                    sides.
    *
    * \note If the pen style is Qt::NoPen or the pen width is 0, the rectangle
    *       is not modified.
    *
    * \note This method is typically called on bounding rectangles to ensure
    *       proper rendering bounds.
    *
    * \sa boundingRect(), pen()
    */
    void adjustForPenWidth(QRectF& rect) const;

    // Action

    /*!
    * \brief Creates context menu actions for nosepiece-specific operations.
    *
    * This method creates QAction objects for the nosepiece context menu:
    * - "Show DN" / "Hide DN": Toggles visibility of the nominal diameter label
    * - "Show consumption" / "Hide consumption": Toggles visibility of the
    *   consumption label
    * - A separator action
    *
    * Each action is:
    * - Created with localized text that reflects the current state
    * - Given a tooltip explaining its purpose
    * - Connected to the appropriate handler function (nominalDiameterShow()
    *   or consumptionShow())
    * - Added to m_nosepieceActionList for later management
    *
    * The action text changes based on the current visibility state (e.g.,
    * "Show DN" if hidden, "Hide DN" if visible).
    *
    * \note This method should be called before displaying the context menu.
    *
    * \note The actions are created using smart pointers (QScopedPointer) to
    *       ensure proper memory management.
    *
    * \sa createSubstanceActions(), nominalDiameterShow(), consumptionShow()
    */
    void createActions();

    /*!
    * \brief Adds a substance menu to the context menu.
    *
    * This method takes a pointer to a QMenu object (the substance submenu)
    * and adds it to the main context menu. The substance menu contains actions
    * for selecting different types of fire extinguishing substances.
    *
    * \param contextSubMenu[in] Pointer to the substance submenu to be added
    *                          to the main context menu. Must not be null.
    *
    * \note The context submenu is owned by the caller and should be deleted
    *       appropriately after use.
    *
    * \sa createSubstanceActions(), createActions(), mousePressEvent()
    */
    void addSubstanceMenu(QMenu *contextSubMenu);

    /*!
    * \brief Creates actions for selecting different substance types.
    *
    * This method sets up a QActionGroup for exclusive selection of substance
    * types, creates QAction objects for each substance type in the
    * SubstanceType enumeration, and connects them to the setSubstanceType()
    * method.
    *
    * Each action:
    * - Has a localized display name
    * - Is checkable (for radio-button style selection)
    * - Has a tooltip explaining its purpose
    * - Is added to an action group to ensure only one substance type can be
    *   selected at a time
    * - Is automatically checked if it matches the current substance type
    *
    * The actions are stored in m_substanceActionList for later removal from
    * the context menu.
    *
    * \note This method should be called before displaying the context menu.
    *
    * \note The actions are created with localized names using QObject::tr().
    *
    * \sa SubstanceType, setSubstanceType(), createActions(), addSubstanceMenu()
    */
    void createSubstanceActions();

    /*!
    * \brief Shows or hides the nominal diameter (DN) label on the nosepiece shape.
    *
    * This method controls the visibility of the nominal diameter text item.
    * If showDN is true, the text item is created (if it doesn't exist), shown,
    * and initialized with a default value of "50". If showDN is false, the
    * text item is hidden.
    *
    * When showing the label, if the QGraphicsTextItem hasn't been created yet,
    * it is created and configured with:
    * - Text editor interaction flags (allowing in-place editing)
    * - -90 degree rotation (for vertical display)
    * - Default text "50"
    *
    * \param showDN[in] If true, shows the nominal diameter label. If false,
    *                  hides it.
    *
    * \note The visibility state is stored in m_showDN member variable.
    *
    * \note This method is typically called from context menu actions or
    *       during initialization.
    *
    * \sa consumptionShow(), setTextItem(), updateDNPosition()
    */
    void nominalDiameterShow(bool showDN);

    /*!
    * \brief Shows or hides the consumption label on the nosepiece shape.
    *
    * This method controls the visibility of the consumption text item.
    * If showConsumption is true, the text item is created (if it doesn't
    * exist), shown, and initialized with a default value of "2,7". If
    * showConsumption is false, the text item is hidden.
    *
    * When showing the label, if the QGraphicsTextItem hasn't been created yet,
    * it is created and configured with:
    * - Text editor interaction flags (allowing in-place editing)
    * - -90 degree rotation (for vertical display)
    * - Default text "2,7" (using comma as decimal separator)
    *
    * \param showConsumption[in] If true, shows the consumption label. If false,
    *                           hides it.
    *
    * \note The visibility state is stored in m_showConsumption member variable.
    *
    * \note This method is typically called from context menu actions or
    *       during initialization.
    *
    * \sa nominalDiameterShow(), setTextItem(), updateConsumptionPosition()
    */
    void consumptionShow(bool showConsumption);

    const ShapeType m_equipmentType;
    QRectF m_nosepieceRect;
    QGraphicsTextItem *m_nominalDiameter;
    QGraphicsTextItem *m_nosepieceConsumption;
    bool m_showDN;
    bool m_showConsumption;
    SubstanceType m_substanceType;

    QScopedPointer<QActionGroup> m_substanceActionGroup;
    QScopedPointer<QAction> m_separatorAction;
    QScopedPointer<QAction> m_addDNAction;
    QScopedPointer<QAction> m_addConsumptionAction;

    QList<QAction *> m_nosepieceActionList;
    QList<QAction *> m_substanceActionList;
};

//TODO Create a concrete classes
#endif // EQUIPMENTSHAPE_H
///@}
