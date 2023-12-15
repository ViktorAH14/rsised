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

#ifndef TECHNICSSHAPE_H
#define TECHNICSSHAPE_H

#include "abstractshape.h"

QT_BEGIN_NAMESPACE
class QAction;
QT_END_NAMESPACE

class TechnicsShape : public AbstractShape
{
public:
    enum { Type = UserType + 200 };
    enum ShapeType { Base               //Автомобиль пожарный общее обозначение
                     , Tanker           //АЦ автоцистерна
                     , PumpHose         //АНР автомобиль насосно-рукавный
                     , FirstAid         //АПП автомобиль первой помощи
                     , Emergency        //АСА пожарный аварийно-спасательный автомобиль
                     , AutoLadder       //АЛ автолестница пожарная
                     , CrankLift        //АПК автоподъёмник коленчатый
                     , TelescopicLift   //ТПЛ автоподъёмник телескопический
                     , HoseCar          //АР автомобиль рукавный
                     , Comm             //АСО автомобиль связи и освещения
                     , TechServ         //АТ автомобиль технической службы
                     , SmokRem          //АД автомобиль дымоудаления
                     , PumpStat         //ПНС пожарная автонасосная станция
                     , LafetTanker      //АЛСС автомобиль пожарный со стационарным лафетным стволом
                     , LafetCar         //АЛСП автомобиль передвижной лафетный ствол
                     , Aerodrome        //АА автомобиль пожарный аэродромный
                     , Foam             //АПТ автомобиль пожарный пенного тушения
                     , Combo            //АКТ автомобиль пожарный комбинированного тушения
                     , Aerosol          //ABT автомобиль водоаэрозольного тушения
                     , Powder           //АП автомобиль порошкового тушения
                     , Carbon           //АГТ автомобиль углекислотного тушения
                     , GazWater         //АГВТ автомобиль газоводяного тушения
                     , Tracked          //ГПМ машина на гусеничном ходу
                     , Tank             //Танк пожарный
                     , GDZS             //АГ автомобиль газодымозащитной службы
                     , Waterproof       //АВЗ автомобиль водозащитный
                     , Laboratory       //АЛП автолаборатория пожарная
                     , StaffCar         //АШ автомобиль штабной
                     , Trailer          //Прицеп пожарный
                     , Vessel
                     , Boat
                     , Train
                     , Plane
                     , Seaplane
                     , Helicopter
                     , MotoPump_1
                     , MotoPump_2
                     , TrailerPowder
                     , Adapted
                     , OtherAdapted
                     , Ambulance
                     , Police };

    struct TechnicsShapeDeleter
    {
        TechnicsShapeDeleter() = delete;
        static inline void cleanup(TechnicsShape *technicsShape) {technicsShape->deleter();}
    };

    static TechnicsShape *createTechnicsShape(ShapeType shapeType, QGraphicsItem *parent = nullptr);

    inline int type() const override { return Type;}
    virtual QPixmap image() = 0;
    virtual ShapeType shapeType() const = 0;
    virtual void setRect(const QRectF &rect) = 0;
    virtual QRectF rect() const = 0;
    virtual void setHeight(const qreal &height) = 0;
    virtual qreal height() const = 0;
    virtual void setText(const QString &text) = 0;
    virtual QString text() const = 0;

protected:
    explicit TechnicsShape(QGraphicsItem *parent = nullptr);
    virtual ~TechnicsShape() = 0;
    virtual void deleter();

    QPolygonF basePolygon(const QRectF &rect) const;

private:
    Q_DISABLE_COPY(TechnicsShape)

};

class BaseShape : public TechnicsShape
{
public:
    enum {Type = UserType + 201};

    explicit BaseShape(QGraphicsItem *parent = nullptr);

    inline int type() const override {return Type;}
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;
    QRectF boundingRect() const override;
    QPainterPath shape() const override;

    QPixmap image() override;
    ShapeType shapeType() const override;
    void setRect(const QRectF &rect) override;
    QRectF rect() const override;
    void setHeight(const qreal &height) override;
    qreal height() const override;
    void setText(const QString &text) override;
    QString text() const override;

protected:
    ~BaseShape() = default;

    void mousePressEvent(QGraphicsSceneMouseEvent *mouseEvent) override;

private:
    Q_DISABLE_COPY(BaseShape)

    void createAction();
    void textShow(bool showText);

    const ShapeType m_baseType;
    QRectF m_baseRect;
    QGraphicsTextItem *m_baseText;
    bool m_showText;

    QScopedPointer<QAction> m_addTextAction;
    QList<QAction *> m_baseActionList;
};

class TankerShape : public TechnicsShape
{
public:
    enum {Type = UserType + 202};

    explicit TankerShape(QGraphicsItem *parent = nullptr);

    inline int type() const override {return Type;}
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;
    QRectF boundingRect() const override;
    QPainterPath shape() const override;

    QPixmap image() override;
    ShapeType shapeType() const override;
    void setRect(const QRectF &rect) override;
    QRectF rect() const override;
    void setHeight(const qreal &height) override;
    qreal height() const override;
    void setText(const QString &text) override;
    QString text() const override;

    void setPipes(bool showPipes);
    bool pipes() const;
    void setCollector(bool showCollector);
    bool collector();

protected:
    ~TankerShape() = default;

    void mousePressEvent(QGraphicsSceneMouseEvent *mouseEvent) override;

private:
    Q_DISABLE_COPY(TankerShape)

    void createAction();
    void textShow(bool showText);
    void drawTankerShape(QPainter *painter);
    void drawPipes(QPainter *painter, qreal sixtWidth);
    void drawCollector(QPainter *painter, qreal sixtWidth);

    const ShapeType m_tankerType;
    QGraphicsTextItem *m_tankerText;
    QRectF m_tankerRect;
    bool m_showPipes;
    bool m_showCollector;
    bool m_showText;

    QScopedPointer<QAction> m_showPipeAction;
    QScopedPointer<QAction> m_showCollectorAction;
    QScopedPointer<QAction> m_addTextAction;
    QList<QAction *> m_tankerActionList;
};

class PumpHoseShape : public TechnicsShape
{
public:
    enum {Type = UserType + 203};

    explicit PumpHoseShape(QGraphicsItem *parent = nullptr);

    inline int type() const override {return Type;}
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;
    QRectF boundingRect() const override;
    QPainterPath shape() const override;

    QPixmap image() override;
    ShapeType shapeType() const override;
    void setRect(const QRectF &rect) override;
    QRectF rect() const override;
    void setHeight(const qreal &height) override;
    qreal height() const override;
    void setText(const QString &text) override;
    QString text() const override;

    void setPipes(bool showPipes);
    bool pipes() const;
    void setCollector(bool showCollector);
    bool collector();

protected:
    ~PumpHoseShape() = default;

    void mousePressEvent(QGraphicsSceneMouseEvent *mouseEvent) override;

private:
    Q_DISABLE_COPY(PumpHoseShape)

    void createAction();
    void textShow(bool showText);
    void drawPumpHoseShape(QPainter *painter);
    void drawPipes(QPainter *painter, qreal sixtWidth);
    void drawCollector(QPainter *painter, qreal sixtWidth);

    const ShapeType m_pumpHoseType;
    QGraphicsTextItem *m_pumpHoseText;
    QRectF m_pumpHoseRect;
    bool m_showPipes;
    bool m_showCollector;
    bool m_showText;

    QScopedPointer<QAction> m_showPipeAction;
    QScopedPointer<QAction> m_showCollectorAction;
    QScopedPointer<QAction> m_addTextAction;
    QList<QAction *> m_pumpHoseActionList;
};

class FirstAidShape : public TechnicsShape
{
public:
    enum {Type = UserType + 204};

    explicit FirstAidShape(QGraphicsItem *parent = nullptr);

    inline int type() const override {return Type;}
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;
    QRectF boundingRect() const override;
    QPainterPath shape() const override;

    QPixmap image() override;
    ShapeType shapeType() const override;
    void setRect(const QRectF &rect) override;
    QRectF rect() const override;
    void setHeight(const qreal &height) override;
    qreal height() const override;
    void setText(const QString &text) override;
    QString text() const override;

    void setPipes(bool showPipes);
    bool pipes() const;
    void setCollector(bool showCollector);
    bool collector();

protected:
    ~FirstAidShape() = default;

    void mousePressEvent(QGraphicsSceneMouseEvent *mouseEvent) override;

private:
    Q_DISABLE_COPY(FirstAidShape)

    void createAction();
    void textShow(bool showText);
    void drawFirstAidShape(QPainter *painter);
    void drawPipes(QPainter *painter, qreal sixtWidth);
    void drawCollector(QPainter *painter, qreal sixtWidth);

    const ShapeType m_firstAidType;
    QGraphicsTextItem *m_firstAidText;
    QRectF m_firstAidRect;
    bool m_showPipes;
    bool m_showCollector;
    bool m_showText;

    QScopedPointer<QAction> m_showPipeAction;
    QScopedPointer<QAction> m_showCollectorAction;
    QScopedPointer<QAction> m_addTextAction;
    QList<QAction *> m_firstAidActionList;
};

class EmergencyShape : public TechnicsShape
{
public:
    enum {Type = UserType + 205};

    explicit EmergencyShape(QGraphicsItem *parent = nullptr);

    inline int type() const override {return Type;}
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;
    QRectF boundingRect() const override;
    QPainterPath shape() const override;

    QPixmap image() override;
    ShapeType shapeType() const override;
    void setRect(const QRectF &rect) override;
    QRectF rect() const override;
    void setHeight(const qreal &height) override;
    qreal height() const override;
    void setText(const QString &text) override;
    QString text() const override;

    void setPipes(bool showPipes);
    bool pipes() const;
    void setCollector(bool showCollector);
    bool collector();

protected:
    ~EmergencyShape() = default;

    void mousePressEvent(QGraphicsSceneMouseEvent *mouseEvent) override;

private:
    Q_DISABLE_COPY(EmergencyShape)

    void createAction();
    void textShow(bool showText);
    void drawEmergencyShape(QPainter *painter);
    void drawPipes(QPainter *painter, qreal sixtWidth);
    void drawCollector(QPainter *painter, qreal sixtWidth);

    const ShapeType m_emergencyType;
    QGraphicsTextItem *m_emergencyText;
    QRectF m_emergencyRect;
    bool m_showPipes;
    bool m_showCollector;
    bool m_showText;

    QScopedPointer<QAction> m_showPipeAction;
    QScopedPointer<QAction> m_showCollectorAction;
    QScopedPointer<QAction> m_addTextAction;
    QList<QAction *> m_emergencyActionList;
};

class AutoLadderShape : public TechnicsShape
{
public:
    enum {Type = UserType + 206};

    explicit AutoLadderShape(QGraphicsItem *parent = nullptr);

    inline int type() const override {return Type;}
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;
    QRectF boundingRect() const override;
    QPainterPath shape() const override;

    QPixmap image() override;
    ShapeType shapeType() const override;
    void setRect(const QRectF &rect) override;
    QRectF rect() const override;
    void setHeight(const qreal &height) override;
    qreal height() const override;
    void setText(const QString &text) override;
    QString text() const override;

protected:
    ~AutoLadderShape() = default;

    void mousePressEvent(QGraphicsSceneMouseEvent *mouseEvent) override;

private:
    Q_DISABLE_COPY(AutoLadderShape)

    void createAction();
    void textShow(bool showText);
    void drawAutoLadderShape(QPainter *painter);

    const ShapeType m_autoLadderType;
    QRectF m_autoLadderRect;
    QGraphicsTextItem *m_autoLadderText;
    bool m_showText;

    QScopedPointer<QAction> m_addTextAction;
    QList<QAction *> m_autoLadderActionList;
};

class CrankLiftShape : public TechnicsShape
{
public:
    enum {Type = UserType + 207};

    explicit CrankLiftShape(QGraphicsItem *parent = nullptr);

    inline int type() const override {return Type;}
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;
    QRectF boundingRect() const override;
    QPainterPath shape() const override;

    QPixmap image() override;
    ShapeType shapeType() const override;
    void setRect(const QRectF &rect) override;
    QRectF rect() const override;
    void setHeight(const qreal &height) override;
    qreal height() const override;
    void setText(const QString &text) override;
    QString text() const override;

protected:
    ~CrankLiftShape() = default;

    void mousePressEvent(QGraphicsSceneMouseEvent *mouseEvent) override;

private:
    Q_DISABLE_COPY(CrankLiftShape)

    void createAction();
    void textShow(bool showText);
    void drawCrankLiftShape(QPainter *painter);

    const ShapeType m_crankLiftType;
    QRectF m_crankLiftRect;
    QGraphicsTextItem *m_crankLiftText;
    bool m_showText;

    QScopedPointer<QAction> m_addTextAction;
    QList<QAction *> m_crankLiftActionList;
};

class TelescopicLiftShape : public TechnicsShape
{
public:
    enum {Type = UserType + 208};

    explicit TelescopicLiftShape(QGraphicsItem *parent = nullptr);

    inline int type() const override {return Type;}
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;
    QRectF boundingRect() const override;
    QPainterPath shape() const override;

    QPixmap image() override;
    ShapeType shapeType() const override;
    void setRect(const QRectF &rect) override;
    QRectF rect() const override;
    void setHeight(const qreal &height) override;
    qreal height() const override;
    void setText(const QString &text) override;
    QString text() const override;

protected:
    ~TelescopicLiftShape() = default;

    void mousePressEvent(QGraphicsSceneMouseEvent *mouseEvent) override;

private:
    Q_DISABLE_COPY(TelescopicLiftShape)

    void createAction();
    void textShow(bool showText);
    void drawTelescopicLiftShape(QPainter *painter);

    const ShapeType m_telescopicLiftType;
    QRectF m_telescopicLiftRect;
    QGraphicsTextItem *m_telescopicLiftText;
    bool m_showText;

    QScopedPointer<QAction> m_addTextAction;
    QList<QAction *> m_telescopicLiftActionList;
};

class HoseCarShape : public TechnicsShape
{
public:
    enum {Type = UserType + 209};

    explicit HoseCarShape(QGraphicsItem *parent = nullptr);

    inline int type() const override {return Type;}
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;
    QRectF boundingRect() const override;
    QPainterPath shape() const override;

    QPixmap image() override;
    ShapeType shapeType() const override;
    void setRect(const QRectF &rect) override;
    QRectF rect() const override;
    void setHeight(const qreal &height) override;
    qreal height() const override;
    void setText(const QString &text) override;
    QString text() const override;

protected:
    ~HoseCarShape() = default;

    void mousePressEvent(QGraphicsSceneMouseEvent *mouseEvent) override;

private:
    Q_DISABLE_COPY(HoseCarShape)

    void createAction();
    void textShow(bool showText);
    void drawHoseCarShape(QPainter *painter);

    const ShapeType m_hoseCarType;
    QRectF m_hoseCarRect;
    QGraphicsTextItem *m_hoseCarText;
    bool m_showText;

    QScopedPointer<QAction> m_addTextAction;
    QList<QAction *> m_hoseCarActionList;
};

class CommShape : public TechnicsShape
{
public:
    enum {Type = UserType + 210};

    explicit CommShape(QGraphicsItem *parent = nullptr);

    inline int type() const override {return Type;}
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;
    QRectF boundingRect() const override;
    QPainterPath shape() const override;

    QPixmap image() override;
    ShapeType shapeType() const override;
    void setRect(const QRectF &rect) override;
    QRectF rect() const override;
    void setHeight(const qreal &height) override;
    qreal height() const override;
    void setText(const QString &text) override;
    QString text() const override;

protected:
    ~CommShape() = default;

    void mousePressEvent(QGraphicsSceneMouseEvent *mouseEvent) override;

private:
    Q_DISABLE_COPY(CommShape)

    void createAction();
    void textShow(bool showText);
    void drawCommShape(QPainter *painter);

    const ShapeType m_commType;
    QRectF m_commRect;
    QGraphicsTextItem *m_commText;
    bool m_showText;

    QScopedPointer<QAction> m_addTextAction;
    QList<QAction *> m_commActionList;
};

class TechServShape : public TechnicsShape
{
public:
    enum {Type = UserType + 211};

    explicit TechServShape(QGraphicsItem *parent = nullptr);

    inline int type() const override {return Type;}
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;
    QRectF boundingRect() const override;
    QPainterPath shape() const override;

    QPixmap image() override;
    ShapeType shapeType() const override;
    void setRect(const QRectF &rect) override;
    QRectF rect() const override;
    void setHeight(const qreal &height) override;
    qreal height() const override;
    void setText(const QString &text) override;
    QString text() const override;

protected:
    ~TechServShape() = default;

    void mousePressEvent(QGraphicsSceneMouseEvent *mouseEvent) override;

private:
    Q_DISABLE_COPY(TechServShape)

    void createAction();
    void textShow(bool showText);
    void drawTechServShape(QPainter *painter);

    const ShapeType m_techServType;
    QRectF m_techServRect;
    QGraphicsTextItem *m_techServText;
    bool m_showText;

    QScopedPointer<QAction> m_addTextAction;
    QList<QAction *> m_techServActionList;
};

class SmokRemShape : public TechnicsShape
{
public:
    enum {Type = UserType + 212};

    explicit SmokRemShape(QGraphicsItem *parent = nullptr);

    inline int type() const override {return Type;}
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;
    QRectF boundingRect() const override;
    QPainterPath shape() const override;

    QPixmap image() override;
    ShapeType shapeType() const override;
    void setRect(const QRectF &rect) override;
    QRectF rect() const override;
    void setHeight(const qreal &height) override;
    qreal height() const override;
    void setText(const QString &text) override;
    QString text() const override;

protected:
    ~SmokRemShape() = default;

    void mousePressEvent(QGraphicsSceneMouseEvent *mouseEvent) override;

private:
    Q_DISABLE_COPY(SmokRemShape)

    void createAction();
    void textShow(bool showText);
    void drawSmokRemShape(QPainter *painter);

    const ShapeType m_smokRemType;
    QRectF m_smokRemRect;
    QGraphicsTextItem *m_smokRemText;
    bool m_showText;

    QScopedPointer<QAction> m_addTextAction;
    QList<QAction *> m_smokRemActionList;
};

class PumpStatShape : public TechnicsShape
{
public:
    enum {Type = UserType + 213};

    explicit PumpStatShape(QGraphicsItem *parent = nullptr);

    inline int type() const override {return Type;}
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;
    QRectF boundingRect() const override;
    QPainterPath shape() const override;

    QPixmap image() override;
    ShapeType shapeType() const override;
    void setRect(const QRectF &rect) override;
    QRectF rect() const override;
    void setHeight(const qreal &height) override;
    qreal height() const override;
    void setText(const QString &text) override;
    QString text() const override;

    void setPipes(bool showPipes);
    bool pipes() const;
    void setCollector(bool showCollector);
    bool collector();

protected:
    ~PumpStatShape() = default;

    void mousePressEvent(QGraphicsSceneMouseEvent *mouseEvent) override;

private:
    Q_DISABLE_COPY(PumpStatShape)

    void createAction();
    void textShow(bool showText);
    void drawPumpStatShape(QPainter *painter);
    void drawPipes(QPainter *painter, qreal sixtWidth);
    void drawCollector(QPainter *painter, qreal sixtWidth);

    const ShapeType m_pumpStatType;
    QGraphicsTextItem *m_pumpStatText;
    QRectF m_pumpStatRect;
    bool m_showPipes;
    bool m_showCollector;
    bool m_showText;

    QScopedPointer<QAction> m_showPipeAction;
    QScopedPointer<QAction> m_showCollectorAction;
    QScopedPointer<QAction> m_addTextAction;
    QList<QAction *> m_pumpStatActionList;
};

class LafetTankerShape : public TechnicsShape
{
public:
    enum {Type = UserType + 214};

    explicit LafetTankerShape(QGraphicsItem *parent = nullptr);

    inline int type() const override {return Type;}
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;
    QRectF boundingRect() const override;
    QPainterPath shape() const override;

    QPixmap image() override;
    ShapeType shapeType() const override;
    void setRect(const QRectF &rect) override;
    QRectF rect() const override;
    void setHeight(const qreal &height) override;
    qreal height() const override;
    void setText(const QString &text) override;
    QString text() const override;

    void setPipes(bool showPipes);
    bool pipes() const;
    void setCollector(bool showCollector);
    bool collector();

protected:
    ~LafetTankerShape() = default;

    void mousePressEvent(QGraphicsSceneMouseEvent *mouseEvent) override;

private:
    Q_DISABLE_COPY(LafetTankerShape)

    void createAction();
    void textShow(bool showText);
    void drawLafetTankerShape(QPainter *painter);
    void drawPipes(QPainter *painter, qreal sixthWidth);
    void drawCollector(QPainter *painter, qreal sixthWidth);

    const ShapeType m_lafetTankerType;
    QGraphicsTextItem *m_lafetTankerText;
    QRectF m_lafetTankerRect;
    bool m_showPipes;
    bool m_showCollector;
    bool m_showText;

    QScopedPointer<QAction> m_showPipeAction;
    QScopedPointer<QAction> m_showCollectorAction;
    QScopedPointer<QAction> m_addTextAction;
    QList<QAction *> m_lafetTankerActionList;
};

class LafetCarShape : public TechnicsShape
{
public:
    enum {Type = UserType + 215};

    explicit LafetCarShape(QGraphicsItem *parent = nullptr);

    inline int type() const override {return Type;}
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;
    QRectF boundingRect() const override;
    QPainterPath shape() const override;

    QPixmap image() override;
    ShapeType shapeType() const override;
    void setRect(const QRectF &rect) override;
    QRectF rect() const override;
    void setHeight(const qreal &height) override;
    qreal height() const override;
    void setText(const QString &text) override;
    QString text() const override;

protected:
    ~LafetCarShape() = default;

    void mousePressEvent(QGraphicsSceneMouseEvent *mouseEvent) override;

private:
    Q_DISABLE_COPY(LafetCarShape)

    void createAction();
    void textShow(bool showText);
    void drawLafetCarShape(QPainter *painter);

    const ShapeType m_lafetCarType;
    QRectF m_lafetCarRect;
    QGraphicsTextItem *m_lafetCarText;
    bool m_showText;

    QScopedPointer<QAction> m_addTextAction;
    QList<QAction *> m_lafetCarActionList;
};

class AerodromeShape : public TechnicsShape
{
public:
    enum {Type = UserType + 216};

    explicit AerodromeShape(QGraphicsItem *parent = nullptr);

    inline int type() const override {return Type;}
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;
    QRectF boundingRect() const override;
    QPainterPath shape() const override;

    QPixmap image() override;
    ShapeType shapeType() const override;
    void setRect(const QRectF &rect) override;
    QRectF rect() const override;
    void setHeight(const qreal &height) override;
    qreal height() const override;
    void setText(const QString &text) override;
    QString text() const override;

    void setPipes(bool showPipes);
    bool pipes() const;
    void setCollector(bool showCollector);
    bool collector();

protected:
    ~AerodromeShape() = default;

    void mousePressEvent(QGraphicsSceneMouseEvent *mouseEvent) override;

private:
    Q_DISABLE_COPY(AerodromeShape)

    void createAction();
    void textShow(bool showText);
    void drawAerodromeShape(QPainter *painter);
    void drawPipes(QPainter *painter, qreal sixtWidth);
    void drawCollector(QPainter *painter, qreal sixtWidth);

    const ShapeType m_aerodromeType;
    QGraphicsTextItem *m_aerodromeText;
    QRectF m_aerodromeRect;
    bool m_showPipes;
    bool m_showCollector;
    bool m_showText;

    QScopedPointer<QAction> m_showPipeAction;
    QScopedPointer<QAction> m_showCollectorAction;
    QScopedPointer<QAction> m_addTextAction;
    QList<QAction *> m_aerodromeActionList;
};

class FoamShape : public TechnicsShape
{
public:
    enum {Type = UserType + 217};

    explicit FoamShape(QGraphicsItem *parent = nullptr);

    inline int type() const override {return Type;}
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;
    QRectF boundingRect() const override;
    QPainterPath shape() const override;

    QPixmap image() override;
    ShapeType shapeType() const override;
    void setRect(const QRectF &rect) override;
    QRectF rect() const override;
    void setHeight(const qreal &height) override;
    qreal height() const override;
    void setText(const QString &text) override;
    QString text() const override;

    void setPipes(bool showPipes);
    bool pipes() const;
    void setCollector(bool showCollector);
    bool collector();

protected:
    ~FoamShape() = default;

    void mousePressEvent(QGraphicsSceneMouseEvent *mouseEvent) override;

private:
    Q_DISABLE_COPY(FoamShape)

    void createAction();
    void textShow(bool showText);
    void drawFoamShape(QPainter *painter);
    void drawPipes(QPainter *painter, qreal sixtWidth);
    void drawCollector(QPainter *painter, qreal sixtWidth);

    const ShapeType m_foamType;
    QGraphicsTextItem *m_foamText;
    QRectF m_foamRect;
    bool m_showPipes;
    bool m_showCollector;
    bool m_showText;

    QScopedPointer<QAction> m_showPipeAction;
    QScopedPointer<QAction> m_showCollectorAction;
    QScopedPointer<QAction> m_addTextAction;
    QList<QAction *> m_foamActionList;
};

class ComboShape : public TechnicsShape
{
public:
    enum {Type = UserType + 218};

    explicit ComboShape(QGraphicsItem *parent = nullptr);

    inline int type() const override {return Type;}
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;
    QRectF boundingRect() const override;
    QPainterPath shape() const override;

    QPixmap image() override;
    ShapeType shapeType() const override;
    void setRect(const QRectF &rect) override;
    QRectF rect() const override;
    void setHeight(const qreal &height) override;
    qreal height() const override;
    void setText(const QString &text) override;
    QString text() const override;

    void setPipes(bool showPipes);
    bool pipes() const;
    void setCollector(bool showCollector);
    bool collector();

protected:
    ~ComboShape() = default;

    void mousePressEvent(QGraphicsSceneMouseEvent *mouseEvent) override;

private:
    Q_DISABLE_COPY(ComboShape)

    void createAction();
    void textShow(bool showText);
    void drawComboShape(QPainter *painter);
    void drawPipes(QPainter *painter, qreal sixtWidth);
    void drawCollector(QPainter *painter, qreal sixtWidth);

    const ShapeType m_comboType;
    QGraphicsTextItem *m_comboText;
    QRectF m_comboRect;
    bool m_showPipes;
    bool m_showCollector;
    bool m_showText;

    QScopedPointer<QAction> m_showPipeAction;
    QScopedPointer<QAction> m_showCollectorAction;
    QScopedPointer<QAction> m_addTextAction;
    QList<QAction *> m_comboActionList;
};

class AerosolShape : public TechnicsShape
{
public:
    enum {Type = UserType + 219};

    explicit AerosolShape(QGraphicsItem *parent = nullptr);

    inline int type() const override {return Type;}
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;
    QRectF boundingRect() const override;
    QPainterPath shape() const override;

    QPixmap image() override;
    ShapeType shapeType() const override;
    void setRect(const QRectF &rect) override;
    QRectF rect() const override;
    void setHeight(const qreal &height) override;
    qreal height() const override;
    void setText(const QString &text) override;
    QString text() const override;

protected:
    ~AerosolShape() = default;

    void mousePressEvent(QGraphicsSceneMouseEvent *mouseEvent) override;

private:
    Q_DISABLE_COPY(AerosolShape)

    void createAction();
    void textShow(bool showText);
    void drawAerosolShape(QPainter *painter);

    const ShapeType m_aerosolType;
    QRectF m_aerosolRect;
    QGraphicsTextItem *m_aerosolText;
    bool m_showText;

    QScopedPointer<QAction> m_addTextAction;
    QList<QAction *> m_aerosolActionList;
};

class PowderShape : public TechnicsShape
{
public:
    enum {Type = UserType + 220};

    explicit PowderShape(QGraphicsItem *parent = nullptr);

    inline int type() const override {return Type;}
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;
    QRectF boundingRect() const override;
    QPainterPath shape() const override;

    QPixmap image() override;
    ShapeType shapeType() const override;
    void setRect(const QRectF &rect) override;
    QRectF rect() const override;
    void setHeight(const qreal &height) override;
    qreal height() const override;
    void setText(const QString &text) override;
    QString text() const override;

protected:
    ~PowderShape() = default;

    void mousePressEvent(QGraphicsSceneMouseEvent *mouseEvent) override;

private:
    Q_DISABLE_COPY(PowderShape)

    void createAction();
    void textShow(bool showText);
    void drawPowderShape(QPainter *painter);

    const ShapeType m_powderType;
    QRectF m_powderRect;
    QGraphicsTextItem *m_powderText;
    bool m_showText;

    QScopedPointer<QAction> m_addTextAction;
    QList<QAction *> m_powderActionList;
};

class CarbonShape : public TechnicsShape
{
public:
    enum {Type = UserType + 221};

    explicit CarbonShape(QGraphicsItem *parent = nullptr);

    inline int type() const override {return Type;}
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;
    QRectF boundingRect() const override;
    QPainterPath shape() const override;

    QPixmap image() override;
    ShapeType shapeType() const override;
    void setRect(const QRectF &rect) override;
    QRectF rect() const override;
    void setHeight(const qreal &height) override;
    qreal height() const override;
    void setText(const QString &text) override;
    QString text() const override;

protected:
    ~CarbonShape() = default;

    void mousePressEvent(QGraphicsSceneMouseEvent *mouseEvent) override;

private:
    Q_DISABLE_COPY(CarbonShape)

    void createAction();
    void textShow(bool showText);
    void drawCarbonShape(QPainter *painter);

    const ShapeType m_carbonType;
    QRectF m_carbonRect;
    QGraphicsTextItem *m_carbonText;
    bool m_showText;

    QScopedPointer<QAction> m_addTextAction;
    QList<QAction *> m_carbonActionList;
};

class GazWaterShape : public TechnicsShape
{
public:
    enum {Type = UserType + 222};

    explicit GazWaterShape(QGraphicsItem *parent = nullptr);

    inline int type() const override {return Type;}
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;
    QRectF boundingRect() const override;
    QPainterPath shape() const override;

    QPixmap image() override;
    ShapeType shapeType() const override;
    void setRect(const QRectF &rect) override;
    QRectF rect() const override;
    void setHeight(const qreal &height) override;
    qreal height() const override;
    void setText(const QString &text) override;
    QString text() const override;

protected:
    ~GazWaterShape() = default;

    void mousePressEvent(QGraphicsSceneMouseEvent *mouseEvent) override;

private:
    Q_DISABLE_COPY(GazWaterShape)

    void createAction();
    void textShow(bool showText);
    void drawGazWaterShape(QPainter *painter);

    const ShapeType m_gazWaterType;
    QRectF m_gazWaterRect;
    QGraphicsTextItem *m_gazWaterText;
    bool m_showText;

    QScopedPointer<QAction> m_addTextAction;
    QList<QAction *> m_gazWaterActionList;
};

class TrackedShape : public TechnicsShape
{
public:
    enum {Type = UserType + 223};

    explicit TrackedShape(QGraphicsItem *parent = nullptr);

    inline int type() const override {return Type;}
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;
    QRectF boundingRect() const override;
    QPainterPath shape() const override;

    QPixmap image() override;
    ShapeType shapeType() const override;
    void setRect(const QRectF &rect) override;
    QRectF rect() const override;
    void setHeight(const qreal &height) override;
    qreal height() const override;
    void setText(const QString &text) override;
    QString text() const override;

protected:
    ~TrackedShape() = default;

    void mousePressEvent(QGraphicsSceneMouseEvent *mouseEvent) override;

private:
    Q_DISABLE_COPY(TrackedShape)

    void createAction();
    void textShow(bool showText);
    void drawTrackedShape(QPainter *painter);

    const ShapeType m_trackedType;
    QRectF m_trackedRect;
    QGraphicsTextItem *m_trackedText;
    bool m_showText;

    QScopedPointer<QAction> m_addTextAction;
    QList<QAction *> m_trackedActionList;
};

class TankShape : public TechnicsShape
{
public:
    enum {Type = UserType + 224};

    explicit TankShape(QGraphicsItem *parent = nullptr);

    inline int type() const override {return Type;}
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;
    QRectF boundingRect() const override;
    QPainterPath shape() const override;

    QPixmap image() override;
    ShapeType shapeType() const override;
    void setRect(const QRectF &rect) override;
    QRectF rect() const override;
    void setHeight(const qreal &height) override;
    qreal height() const override;
    void setText(const QString &text) override;
    QString text() const override;

protected:
    ~TankShape() = default;

    void mousePressEvent(QGraphicsSceneMouseEvent *mouseEvent) override;

private:
    Q_DISABLE_COPY(TankShape)

    void createAction();
    void textShow(bool showText);
    void drawTankShape(QPainter *painter);
    QPolygonF tankPolygon(const QRectF &rect) const;

    const ShapeType m_tankType;
    QRectF m_tankRect;
    QGraphicsTextItem *m_tankText;
    bool m_showText;

    QScopedPointer<QAction> m_addTextAction;
    QList<QAction *> m_tankActionList;
};

class GdzsShape : public TechnicsShape
{
public:
    enum {Type = UserType + 225};

    explicit GdzsShape(QGraphicsItem *parent = nullptr);

    inline int type() const override {return Type;}
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;
    QRectF boundingRect() const override;
    QPainterPath shape() const override;

    QPixmap image() override;
    ShapeType shapeType() const override;
    void setRect(const QRectF &rect) override;
    QRectF rect() const override;
    void setHeight(const qreal &height) override;
    qreal height() const override;
    void setText(const QString &text) override;
    QString text() const override;

protected:
    ~GdzsShape() = default;

    void mousePressEvent(QGraphicsSceneMouseEvent *mouseEvent) override;

private:
    Q_DISABLE_COPY(GdzsShape)

    void createAction();
    void textShow(bool showText);
    void drawGdzsShape(QPainter *painter);

    const ShapeType m_gdzsType;
    QRectF m_gdzsRect;
    QGraphicsTextItem *m_gdzsText;
    bool m_showText;

    QScopedPointer<QAction> m_addTextAction;
    QList<QAction *> m_gdzsActionList;
};

class WaterproofShape : public TechnicsShape
{
public:
    enum {Type = UserType + 226};

    explicit WaterproofShape(QGraphicsItem *parent = nullptr);

    inline int type() const override {return Type;}
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;
    QRectF boundingRect() const override;
    QPainterPath shape() const override;

    QPixmap image() override;
    ShapeType shapeType() const override;
    void setRect(const QRectF &rect) override;
    QRectF rect() const override;
    void setHeight(const qreal &height) override;
    qreal height() const override;
    void setText(const QString &text) override;
    QString text() const override;

protected:
    ~WaterproofShape() = default;

    void mousePressEvent(QGraphicsSceneMouseEvent *mouseEvent) override;

private:
    Q_DISABLE_COPY(WaterproofShape)

    void createAction();
    void textShow(bool showText);
    void drawWaterproofShape(QPainter *painter);

    const ShapeType m_waterproofType;
    QRectF m_waterproofRect;
    QGraphicsTextItem *m_waterproofText;
    bool m_showText;

    QScopedPointer<QAction> m_addTextAction;
    QList<QAction *> m_waterproofActionList;
};

class LaboratoryShape : public TechnicsShape
{
public:
    enum {Type = UserType + 227};

    explicit LaboratoryShape(QGraphicsItem *parent = nullptr);

    inline int type() const override {return Type;}
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;
    QRectF boundingRect() const override;
    QPainterPath shape() const override;

    QPixmap image() override;
    ShapeType shapeType() const override;
    void setRect(const QRectF &rect) override;
    QRectF rect() const override;
    void setHeight(const qreal &height) override;
    qreal height() const override;
    void setText(const QString &text) override;
    QString text() const override;

protected:
    ~LaboratoryShape() = default;

    void mousePressEvent(QGraphicsSceneMouseEvent *mouseEvent) override;

private:
    Q_DISABLE_COPY(LaboratoryShape)

    void createAction();
    void textShow(bool showText);
    void drawLaboratoryShape(QPainter *painter);

    const ShapeType m_laboratoryType;
    QRectF m_laboratoryRect;
    QGraphicsTextItem *m_laboratoryText;
    bool m_showText;

    QScopedPointer<QAction> m_addTextAction;
    QList<QAction *> m_laboratoryActionList;
};

class StaffCarShape : public TechnicsShape
{
public:
    enum {Type = UserType + 228};

    explicit StaffCarShape(QGraphicsItem *parent = nullptr);

    inline int type() const override {return Type;}
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;
    QRectF boundingRect() const override;
    QPainterPath shape() const override;

    QPixmap image() override;
    ShapeType shapeType() const override;
    void setRect(const QRectF &rect) override;
    QRectF rect() const override;
    void setHeight(const qreal &height) override;
    qreal height() const override;
    void setText(const QString &text) override;
    QString text() const override;

protected:
    ~StaffCarShape() = default;

    void mousePressEvent(QGraphicsSceneMouseEvent *mouseEvent) override;

private:
    Q_DISABLE_COPY(StaffCarShape)

    void createAction();
    void textShow(bool showText);
    void drawStaffCarShape(QPainter *painter);

    const ShapeType m_staffCarType;
    QRectF m_staffCarRect;
    QGraphicsTextItem *m_staffCarText;
    bool m_showText;

    QScopedPointer<QAction> m_addTextAction;
    QList<QAction *> m_staffCarActionList;
};

class TrailerShape : public TechnicsShape
{
public:
    enum {Type = UserType + 229};

    explicit TrailerShape(QGraphicsItem *parent = nullptr);

    inline int type() const override {return Type;}
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;
    QRectF boundingRect() const override;
    QPainterPath shape() const override;

    QPixmap image() override;
    ShapeType shapeType() const override;
    void setRect(const QRectF &rect) override;
    QRectF rect() const override;
    void setHeight(const qreal &height) override;
    qreal height() const override;
    void setText(const QString &text) override;
    QString text() const override;

protected:
    ~TrailerShape() = default;

    void mousePressEvent(QGraphicsSceneMouseEvent *mouseEvent) override;

private:
    Q_DISABLE_COPY(TrailerShape)

    void createAction();
    void textShow(bool showText);
    void drawTrailerShape(QPainter *painter);

    const ShapeType m_trailerType;
    QRectF m_trailerRect;
    QGraphicsTextItem *m_trailerText;
    bool m_showText;

    QScopedPointer<QAction> m_addTextAction;
    QList<QAction *> m_trailerActionList;
    QPainterPath m_trailerPath;
};
#endif // TECHNICSSHAPE_H
