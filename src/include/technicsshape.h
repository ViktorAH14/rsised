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
                     , Tanker
                     , AutoPump
                     , FirstAid
                     , Emergency
                     , AutoLadder
                     , CrankLift
                     , TelescopicLift
                     , Hose
                     , Comm
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

private:
    Q_DISABLE_COPY(BaseShape)

    const ShapeType m_baseType;
    QRectF m_baseRect;
    QGraphicsTextItem *m_baseText;
    bool m_showText;
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
    void drawPipes(qreal roundRadius, QPainter *painter);
    void drawCollector(QPainter *painter, qreal roundRadius);

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
#endif // TECHNICSSHAPE_H
