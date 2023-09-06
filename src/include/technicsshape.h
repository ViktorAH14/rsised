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
    enum ShapeType { Base
                     , Tanker           //АЦ
                     , PumpHose         //АНР
                     , FirstAid         //АПП
                     , Emergency        //АСА
                     , AutoLadder       //АЛ
                     , CrankLift        //АПК
                     , TelescopicLift   //ТПЛ
                     , HoseCar          //АР
                     , Comm             //АСО
                     , Tech_serv
                     , Smok_rem
                     , AutoPumpS
                     , CarriageCar_1
                     , CarriageCar_2
                     , Aerodrome
                     , Foam
                     , Combo
                     , Aerosol
                     , Powder
                     , Carbon
                     , GazWater
                     , Tracked
                     , Tank
                     , GDZS
                     , Waterproof
                     , Laboratory
                     , StaffCar
                     , Trailer
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
#endif // TECHNICSSHAPE_H
