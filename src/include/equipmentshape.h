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
 * \brief This header file contains declarations like classes used to draw fire
 * equipment.
 *
 * The equipmentshape.h is a header file that contains a declarations of the Nosepiece,
 * Branching, Stair, Collector, HoseBridge, HoseReel, Hydroelevator, FoamMixer,
 * FireColumn, SmokePump, Hose, FoamLift and LiftGPS classes.
 *
 *
 * \copyright (C) 2022 by Viktor Ermolov <ermolovva@gmail.com>.
 * You can redistribute it and/or modify it under the terms of the
 * GNU General Public License as published by the Free Software Foundation,
 * either version 3 of the License, or (at your option) any later version.
 * \date October 18 2024
 * \author Ermolov V.A.
 */

/*!
 * \defgroup EquipmentShapes Equipment shapes library
 * \brief This module is a fire equipment library of shapes for the RSiSed application.
 * \ingroup libshapes
 *
 * This module includes elements designed to create fire fighting equipment (nosepieces,
 * branches, stairs, hoses, etc.).
 */
///@{

#ifndef EQUIPMENTSHAPE_H
#define EQUIPMENTSHAPE_H

#include "abstractshape.h"

/*!
 * \brief The EquipmentShape class is an interface class for creating fire fighting
 *  equipment shapes.
 *
 * The class has an available static factory function that returns a pointer
 * to the base class, with which instances of the corresponding classes are
 * created.
 *
 * \sa Nosepiece, Branching, Stair, Collector, HoseBridge, HoseReel, Hydroelevator,
 * FoamMixer, FireColumn, SmokePump, Hose, FoamLift and LiftGPS.
 */
//TODO Create an interface class
class EquipmentShape : public AbstractShape
{
public:
    //! This type information is used by qgraphicsitem_cast to distinguish between types.
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
    //! Set of possible shapes for fire fighting equipment.
    enum ShapeType { Nosepiece      //!< This type includes all types of firefighting nozzles.
                     , Branch       //!< This type includes all types of fire branches.
                     , Ladder       //!< This type includes all types of fire escape ladders.
                     , Collector    //!< This is a fire collector.
                     , HoseBridge   //!< This is a bridge for a fire hose.
                     , HoseReel     //!< This type includes all types of fire hose reels.
                     , Hydroelevator    //!< This is an inkjet fire pump for water intake.
                     , FoamMixer    //!< This is a foam mixer.
                     , FireColumn   //!< This is a fire hydrant column.
                     , SmokePump    //!< This type includes all types of fire smoke pumps.
                     , Hose         //!< This type includes all types of fire hoses.
                     , FoamLift     //!< This lift is foam.
                     , LiftGPS      //!< This is a lift with several foam generators.
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
        // static inline void cleanup(EquipmentShape *equipmentShape) {equipmentShape->deleter();}
    };

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
     * A purel virtual method that needs to be overridden in a child class.
     * This method is used to set the size of the shape.
     *
     * \param rect[in] Sets the shape's size to be the given  rectangle.
     * \sa rect().
     */
    virtual void setRect(const QRectF &rect) = 0;

    /*!
     * A pure virtual method that needs to be overridden in a child class.
     *
     * \return Returns the shape`s rectangle.
     * \sa setRect()
     */
    virtual QRectF rect() const = 0;

    /*!
     * A pure virtual method that needs to be overridden in a child class.
     * This method is used to set the height of the shape.
     *
     * \param height[in] Sets the height of the shape to the given height.
     *
     * \sa height()
     */
    virtual void setHeight(const qreal &height) = 0;

    /*!
     * A pure virtual method that needs to be overridden in a child class.
     *
     * \return Returns the shape`s height.
     *
     * \sa setHeight()
     */
    virtual qreal height() const = 0;

protected:
    // void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;

private:
    // void drawShape(QPainter *painter);

    // ShapeType m_shapeType;
};

//TODO Create a concrete classes
#endif // EQUIPMENTSHAPE_H
///@}
