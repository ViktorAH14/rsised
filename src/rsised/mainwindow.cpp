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

#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "config.h"
#include "../include/rectshape.h"
#include "../include/ellipseshape.h"
#include "../include/polylineshape.h"
#include "../include/curve.h"
#include "../include/textshape.h"
#include "../include/pixmapshape.h"
#include "rse_writer.h"
#include "rse_reader.h"
#include "svg_reader.h"
#include "wallsetting.h"

#include <QtWidgets>
#include <QSvgGenerator>
#include <KColorButton>
#include <QPrinter>
#include <QPrintDialog>
#include <QScopedPointer>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , m_currentFile("")
    , m_wallPen(QPen(Qt::black, 1))
    , m_wallBrush(QBrush(Qt::lightGray))
    , m_wallHeight{10}
{
    ui->setupUi(this);

    createActions();
    createShapeToolBox();
    createMenu();
    disableAction();
    setUnifiedTitleAndToolBarOnMac(true);

// Create toolbars
    createSimpleDrawToolBar();
    createStyleToolBar();
    createFontStyleToolBar();
    createSceneScaleToolBar();

// Create scene and view
    m_scene = new DiagramScene(m_contextMenu, this);
    m_scene->setSceneRect(0, 0, 1240, 877); //A3
    m_scene->setItemPen(m_penColorButton->color(),
                      qvariant_cast<qreal>(m_penSizeCombo->currentText()),
                      qvariant_cast<Qt::PenStyle>(m_penStyleCombo->currentData()));
    m_scene->setItemBrush(m_brushColorButton->color(),
                        qvariant_cast<Qt::BrushStyle>(m_brushStyleCombo->currentData()));
    connect(m_scene, &QGraphicsScene::selectionChanged, this, &MainWindow::enableAction);
    ui->mainGraphicsView->setScene(m_scene);
    ui->mainGraphicsView->setRenderHints(QPainter::Antialiasing);

    QSplitter *mainSplitter = new QSplitter(this);
    mainSplitter->addWidget(m_shapeToolBox);
    mainSplitter->addWidget(ui->mainGraphicsView);
    setCentralWidget(mainSplitter);

    m_copyList = m_scene->selectedItems();

    setCurrentFile(QString());
    changedFont();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::loadFile(const QString &fileName)
{
    QFile file(fileName);
    if (!file.open(QFile::ReadOnly | QFile::Text)) {
        QMessageBox::warning(this, tr("RSiSed"), tr("Cannot read file %1:\n%2.")
                             .arg(QDir::toNativeSeparators(fileName), file.errorString()));
        return;
    }
#ifndef QT_NO_CURSOR
    QGuiApplication::setOverrideCursor(Qt::WaitCursor);
#endif

    m_scene->clear();

    QScopedPointer<RseReader> sc_rseReader(new RseReader(m_contextMenu));
    QRectF sceneRect = sc_rseReader->getSceneRect(&file);
    m_scene->setSceneRect(sceneRect);
    file.close();

    if (!file.open(QFile::ReadOnly)) {
        QMessageBox::warning(this, tr("RSiSed"), tr("Cannot read file %1:\n%2.")
                             .arg(QDir::toNativeSeparators(fileName), file.errorString()));
        return;
    }

    QList<QGraphicsItem *> shapeList = sc_rseReader->getElement(&file);
    for (QGraphicsItem *p_shape : qAsConst(shapeList)) {
        if (RectShape *p_rectangleShape = dynamic_cast<RectShape *>(p_shape)) {
            m_scene->addItem(p_rectangleShape);
        }
        if (EllipseShape *p_ellipseShape = dynamic_cast<EllipseShape *>(p_shape)) {
            m_scene->addItem(p_ellipseShape);
        }
        if (PolylineShape *p_polylineShape = dynamic_cast<PolylineShape *>(p_shape)) {
            m_scene->addItem(p_polylineShape);
        }
        if (Curve *p_curveShape = dynamic_cast<Curve *>(p_shape)) {
            m_scene->addItem(p_curveShape);
        }
        if (QGraphicsLineItem *p_lineShape = dynamic_cast<QGraphicsLineItem *>(p_shape)) {
            m_scene->addItem(p_lineShape);
        }
        if (TextShape *p_textShape = dynamic_cast<TextShape *>(p_shape)) {
            m_scene->addItem(p_textShape);
        }
        if (PixmapShape *p_pixmapShape = dynamic_cast<PixmapShape *>(p_shape)) {
            m_scene->addItem(p_pixmapShape);
        }
        if (TechnicsShape *p_technicsShape = dynamic_cast<TechnicsShape *>(p_shape)) {
            m_scene->addItem(p_technicsShape);
        }
        if (DeviceShape *p_deviceShape = dynamic_cast<DeviceShape *>(p_shape)) {
            m_scene->addItem(p_deviceShape);
        }
        if (BuildingShape *p_buildingShape = dynamic_cast<BuildingShape *>(p_shape)) {
            m_scene->addItem(p_buildingShape);
        }
    }
    file.close();

#ifndef QT_NO_CURSOR
    QGuiApplication::restoreOverrideCursor();
#endif

    m_scene->setSelectableItems(true);
    setCurrentFile(fileName);
    ui->statusBar->showMessage(tr("File loaded"), 10000);
}

void MainWindow::closeEvent(QCloseEvent *event)
{
    if (maybeSave()) {
        m_scene->clearSelection();
        event->accept();
    } else {
        event->ignore();
    }
}

void MainWindow::newFile()
{
    if (maybeSave()) {
        m_scene->clear();
        setCurrentFile(QString());
    }
}

void MainWindow::open()
{
    if (maybeSave()) {
        QString fileName = QFileDialog::getOpenFileName(this, tr("Open")
                                                        , m_currentFile, tr("RSE files (*.rse)"));
        if (!fileName.isEmpty()) {
            loadFile(fileName);
        }
    }
}

bool MainWindow::save()
{
    if (m_currentFile.isEmpty()) {
        return saveAs();
    } else {
        return saveFile(m_currentFile);
    }
}

bool MainWindow::saveAs()
{
    QFileDialog fileDialog(this, tr("Save"), m_currentFile, tr("RSiSed files (*.rse)"));
    fileDialog.setWindowModality(Qt::WindowModal);
    fileDialog.setAcceptMode(QFileDialog::AcceptSave);
    if (fileDialog.exec() != QDialog::Accepted) {
        return false;
    }
    return saveFile(fileDialog.selectedFiles().constFirst());
}

void MainWindow::copy()
{
    if (!m_copyList.isEmpty()) {
        QList<QGraphicsItem *> shapeList = m_scene->items();
        for (QGraphicsItem *p_shape : qAsConst(m_copyList)) {
            if (!shapeList.contains(p_shape))
                delete p_shape;
        }
        m_copyList.clear();
    }

    QList<QGraphicsItem *> selectedList = m_scene->selectedItems();
    for (QGraphicsItem *p_shape : qAsConst(selectedList)) {
        if (RectShape *p_oldRectangleShape = dynamic_cast<RectShape *>(p_shape)) {
            RectShape *p_newRectangleShape = new RectShape();
            p_newRectangleShape->setMenu(m_contextMenu);
            p_newRectangleShape->setRect(p_oldRectangleShape->rect());
            p_newRectangleShape->setX(p_oldRectangleShape->x() + 10.0);
            p_newRectangleShape->setY(p_oldRectangleShape->y() + 10.0);
            p_newRectangleShape->setPen(p_oldRectangleShape->pen());
            p_newRectangleShape->setBrush(p_oldRectangleShape->brush());
            m_copyList.append(p_newRectangleShape);
        }
        if (EllipseShape *p_oldEllipseShape = dynamic_cast<EllipseShape *>(p_shape)) {
            EllipseShape *p_newEllipseShape = new EllipseShape();
            p_newEllipseShape->setMenu(m_contextMenu);
            p_newEllipseShape->setRect(p_oldEllipseShape->rect());
            p_newEllipseShape->setX(p_oldEllipseShape->x() + 10.0);
            p_newEllipseShape->setY(p_oldEllipseShape->y() + 10.0);
            p_newEllipseShape->setPen(p_oldEllipseShape->pen());
            p_newEllipseShape->setBrush(p_oldEllipseShape->brush());
            if ((p_oldEllipseShape->spanAngle() != 0)
                    && (qAbs(p_oldEllipseShape->spanAngle()) % (360 *16) != 0)) {
                p_newEllipseShape->setStartAngle(p_oldEllipseShape->startAngle());
                p_newEllipseShape->setSpanAngle(p_oldEllipseShape->spanAngle());
            }
            m_copyList.append(p_newEllipseShape);
        }
        if (PolylineShape *p_oldPolyline = dynamic_cast<PolylineShape *>(p_shape)) {
            PolylineShape *p_newPolyline = new PolylineShape(m_contextMenu);
            p_newPolyline->setPath(p_oldPolyline->path());
            p_newPolyline->setX(p_oldPolyline->x() + 10.0);
            p_newPolyline->setY(p_oldPolyline->y() + 10.0);
            p_newPolyline->setPen(p_oldPolyline->pen());
            m_copyList.append(p_newPolyline);
        }
        if (Curve *p_oldCurve = dynamic_cast<Curve *>(p_shape)) {
            Curve *p_newCurve = new Curve(m_contextMenu);
            p_newCurve->setPath(p_oldCurve->path());
            p_newCurve->setX(p_oldCurve->x() + 10.0);
            p_newCurve->setY(p_oldCurve->y() + 10.0);
            p_newCurve->setPen(p_oldCurve->pen());
            m_copyList.append(p_newCurve);
        }
        if (QGraphicsLineItem *p_oldLine = dynamic_cast<QGraphicsLineItem *>(p_shape)) {
            QGraphicsLineItem *p_newLine = new QGraphicsLineItem();
            p_newLine->setFlag(QGraphicsItem::ItemIsMovable, true);
            p_newLine->setLine(p_oldLine->line());
            p_newLine->setX(p_oldLine->x() + 10.0);
            p_newLine->setY(p_oldLine->y() + 10.0);
            p_newLine->setPen(p_oldLine->pen());
            m_copyList.append(p_newLine);
        }
        if (TextShape *p_oldText = dynamic_cast<TextShape *>(p_shape)) {
            TextShape *p_newText = new TextShape(m_contextMenu);
            p_newText->setPlainText(p_oldText->document()->toPlainText());
            p_newText->setPos(QPointF(p_oldText->x() + 10, p_oldText->y() + 10));
            p_newText->setFont(p_oldText->font());
            p_newText->setDefaultTextColor(p_oldText->defaultTextColor());
            p_newText->setZValue(p_oldText->zValue());
            m_copyList.append(p_newText);
        }
        if (TechnicsShape *p_oldTechnicsShape = dynamic_cast<TechnicsShape *>(p_shape)) {
            TechnicsShape::ShapeType shapeType = p_oldTechnicsShape->shapeType();
            QTransform shapeTransform = p_oldTechnicsShape->transform();
            QString shapeText{p_oldTechnicsShape->text()};
            TechnicsShape *p_newTechnicsShape{TechnicsShape::createTechnicsShape(shapeType)};
            p_newTechnicsShape->setMenu(m_contextMenu);
            p_newTechnicsShape->setRect(p_oldTechnicsShape->rect());
            p_newTechnicsShape->setPos(QPointF(p_oldTechnicsShape->x() + 10
                                             , p_oldTechnicsShape->y() + 10));
            p_newTechnicsShape->setZValue(p_oldTechnicsShape->zValue());
            p_newTechnicsShape->setTransform(shapeTransform);
            if (!shapeText.isEmpty())
                p_newTechnicsShape->setText(shapeText);
            m_copyList.append(p_newTechnicsShape);
        }
        if (DeviceShape *p_oldDeviceShape = dynamic_cast<DeviceShape *>(p_shape)) {
            DeviceShape::ShapeType shapeType = p_oldDeviceShape->shapeType();
            QTransform shapeTransform = p_oldDeviceShape->transform();
            DeviceShape *p_newDeviceShape = new DeviceShape(shapeType);
            p_newDeviceShape->setMenu(m_contextMenu);
            p_newDeviceShape->setPos(QPointF(p_oldDeviceShape->x() + 10
                                             , p_oldDeviceShape->y() + 10));
            p_newDeviceShape->setZValue(p_oldDeviceShape->zValue());
            p_newDeviceShape->setTransform(shapeTransform);
            m_copyList.append(p_newDeviceShape);
        }
        if (BuildingShape *p_oldBuildingShape = dynamic_cast<BuildingShape *>(p_shape)) {
            BuildingShape::ShapeType shapeType = p_oldBuildingShape->shapeType();
            QTransform shapeTransform = p_oldBuildingShape->transform();
            BuildingShape *p_newBuildingShape{BuildingShape::createBuildingShape(shapeType)};
            p_newBuildingShape->setMenu(m_contextMenu);
            p_newBuildingShape->setRect(p_oldBuildingShape->rect());
            p_newBuildingShape->setPos(QPointF(p_oldBuildingShape->x() + 10
                                             , p_oldBuildingShape->y() + 10));
            p_newBuildingShape->setHeight(p_oldBuildingShape->height());
            p_newBuildingShape->setPen(p_oldBuildingShape->pen());
            p_newBuildingShape->setBrush(p_oldBuildingShape->brush());
            p_newBuildingShape->setZValue(p_oldBuildingShape->zValue());
            p_newBuildingShape->setTransform(shapeTransform);

            if (DoorShape *p_oldDoorShape = dynamic_cast<DoorShape *>(p_shape)) {
                DoorShape *p_newDoorShape = dynamic_cast<DoorShape *>(p_newBuildingShape);
                p_newDoorShape->setDoorState(p_oldDoorShape->doorState());
                p_newDoorShape->setLeafPosition(p_oldDoorShape->leafPosition());
            }

            m_copyList.append(p_newBuildingShape);
        }
    }

    ui->actionPaste->setEnabled(true);
}

void MainWindow::paste()
{
    for (QGraphicsItem *p_shape : qAsConst(m_copyList))
        m_scene->addItem(p_shape);

    m_copyList.clear();
    ui->actionPaste->setEnabled(false);
    m_scene->setSelectableItems(true);
}

void MainWindow::cut()
{
    copy();
    deleteShape();
}

void MainWindow::openSVG()
{
    if (maybeSave()) {
        QString fileName = QFileDialog::getOpenFileName(this, tr("Open SVG")
                                                        , "", tr("SVG files (*.svg)"));
        if (fileName.isEmpty()) {
            return;
        }

        m_scene->clear();
        QScopedPointer<SvgReader> sc_svgReader(new SvgReader(ui->menuEdit));
        m_scene->setSceneRect(sc_svgReader->getSize(fileName));

        QList<QGraphicsItem *> shapeList = sc_svgReader->getElements(fileName);
        for (QGraphicsItem *p_shape : qAsConst(shapeList)) {
            if (RectShape *p_rectangleShape = dynamic_cast<RectShape *>(p_shape)) {
                m_scene->addItem(p_rectangleShape);
            }
            if (EllipseShape *p_ellipseShape = dynamic_cast<EllipseShape *>(p_shape)) {
                m_scene->addItem(p_ellipseShape);
            }
            if (PolylineShape *p_polylineShape = dynamic_cast<PolylineShape *>(p_shape)) {
                m_scene->addItem(p_polylineShape);
            }
            if (Curve *p_curveShape = dynamic_cast<Curve *>(p_shape)) {
                m_scene->addItem(p_curveShape);
            }
            if (QGraphicsLineItem *p_lineItem = dynamic_cast<QGraphicsLineItem *>(p_shape)) {
                m_scene->addItem(p_lineItem);
            }
            if (TextShape *p_textShape = dynamic_cast<TextShape *>(p_shape)) {
                m_scene->addItem(p_textShape);
            }
            if (PixmapShape *p_pixmapShape = dynamic_cast<PixmapShape *>(p_shape)) {
                m_scene->addItem(p_pixmapShape);
            }
        }
        m_scene->setSelectableItems(true);
        setCurrentFile(fileName);
        return;
    }
}

bool MainWindow::saveSVG()
{
    QString newPath = QFileDialog::getSaveFileName(this, tr("Save SVG"),
                                                   m_currentFile, tr("SVG files (*.svg)"));
    if (newPath.isEmpty())
        return false;
    m_currentFile = newPath;

    QSvgGenerator svgGenerator;
    svgGenerator.setFileName(m_currentFile);
    svgGenerator.setSize(QSize(m_scene->width(), m_scene->height()));
    svgGenerator.setViewBox(QRect(0, 0, m_scene->width(), m_scene->height()));
    svgGenerator.setTitle(tr("SVG RSiSed"));
    svgGenerator.setDescription(tr("File created by RSiSed"));

    QPainter svgPainter;
    svgPainter.begin(&svgGenerator);
    m_scene->render(&svgPainter);
    svgPainter.end();

    return true;
}

void MainWindow::print()
{
    QPrinter printer;
    if (QPrintDialog(&printer).exec() == QDialog::Accepted) {
         QPainter printPainter(&printer);
         printPainter.setRenderHint(QPainter::Antialiasing);
         m_scene->render(&printPainter);
    }
}

void MainWindow::insertImage()
{
    m_imagePath = QFileDialog::getOpenFileName(this, tr("Insert image"), ""
                                             , tr("Images (*.bmp *.gif *.jpg *.jpeg *.png *.pbm *.pgm *.ppm *.xbm *.xpm)"));
    if (m_imagePath.isEmpty()) {
        return;
    }
    ui->mainGraphicsView->setCursor(Qt::ArrowCursor);
    ui->mainGraphicsView->setDragMode(QGraphicsView::NoDrag);
    m_scene->setMode(DiagramScene::InsertImage);
    m_scene->setSelectableItems(false);
    m_scene->insertPixmap(m_imagePath);
    ui->actionSelect_All->setDisabled(true);
    ui->actionDeleteItem->setDisabled(true);
}

void MainWindow::drawPolyline()
{
    ui->mainGraphicsView->setCursor(Qt::CrossCursor);
    ui->mainGraphicsView->setDragMode(QGraphicsView::NoDrag);
    m_scene->setMode(DiagramScene::InsertPolyline);
    m_scene->setSelectableItems(false);
    ui->actionSelect_All->setDisabled(true);
    ui->actionDeleteItem->setDisabled(true);
}

void MainWindow::drawRect()
{
    ui->mainGraphicsView->setCursor(Qt::CrossCursor);
    ui->mainGraphicsView->setDragMode(QGraphicsView::NoDrag);
    m_scene->setMode(DiagramScene::InsertRectShape);
    m_scene->setSelectableItems(false);
    ui->actionSelect_All->setDisabled(true);
    ui->actionDeleteItem->setDisabled(true);
}

void MainWindow::drawEllipse()
{
    ui->mainGraphicsView->setCursor(Qt::CrossCursor);
    ui->mainGraphicsView->setDragMode(QGraphicsView::NoDrag);
    m_scene->setMode(DiagramScene::InsertEllipse);
    m_scene->setSelectableItems(false);
    ui->actionSelect_All->setDisabled(true);
    ui->actionDeleteItem->setDisabled(true);
}

void MainWindow::drawPie()
{
    ui->mainGraphicsView->setCursor(Qt::CrossCursor);
    ui->mainGraphicsView->setDragMode(QGraphicsView::NoDrag);
    m_scene->setMode(DiagramScene::InsertPie);
    m_scene->setSelectableItems(false);
    ui->actionSelect_All->setDisabled(true);
    ui->actionDeleteItem->setDisabled(true);
}

void MainWindow::drawCurve()
{
    ui->mainGraphicsView->setCursor(Qt::CrossCursor);
    ui->mainGraphicsView->setDragMode(QGraphicsView::NoDrag);
    m_scene->setMode(DiagramScene::InsertCurve);
    m_scene->setSelectableItems(false);
    ui->actionSelect_All->setDisabled(true);
    ui->actionDeleteItem->setDisabled(true);
}

void MainWindow::insertText()
{
    ui->mainGraphicsView->setCursor(Qt::IBeamCursor);
    ui->mainGraphicsView->setDragMode(QGraphicsView::NoDrag);
    m_scene->setMode(DiagramScene::InserText);
    m_scene->setSelectableItems(false);
    ui->actionSelect_All->setDisabled(true);
    ui->actionDeleteItem->setDisabled(true);
}

void MainWindow::insertTechnicsShape(QAbstractButton *button)
{
    const QList<QAbstractButton *> buttonList = m_technicsButtonGroup->buttons();
    for (const QAbstractButton *p_button : buttonList) {
        if (p_button != button)
            button->setChecked(false);
    }
    const int idButton = m_technicsButtonGroup->id(button);
    TechnicsShape::ShapeType shapeType {TechnicsShape::ShapeType(idButton)};
    QScopedPointer<TechnicsShape, TechnicsShape::TechnicsShapeDeleter>
            sc_technicsShape{TechnicsShape::createTechnicsShape(shapeType)};
    ui->mainGraphicsView->setCursor(QCursor(sc_technicsShape->image()));
    ui->mainGraphicsView->setDragMode(QGraphicsView::NoDrag);
    m_scene->setMode(DiagramScene::InsertTechnicsShape);
    m_scene->setTechnicsShapeType(TechnicsShape::ShapeType(idButton));
    m_scene->setSelectableItems(false);
    if (m_simpleDrawModeActionGr->checkedAction() != nullptr)
        m_simpleDrawModeActionGr->checkedAction()->setChecked(false);
    ui->actionSelect_All->setDisabled(true);
    ui->actionDeleteItem->setDisabled(true);
}

void MainWindow::insertDeviceShape(QAbstractButton *button)
{
    const QList<QAbstractButton *> buttonList = m_deviceButtonGroup->buttons();
    for (const QAbstractButton *p_button : buttonList) {
        if (p_button != button)
            button->setChecked(false);
    }
    const int idButton = m_deviceButtonGroup->id(button);
    DeviceShape::ShapeType shapeType {DeviceShape::ShapeType(idButton)};
    DeviceShape deviceShape(shapeType);
    ui->mainGraphicsView->setCursor(QCursor(deviceShape.image()));
    ui->mainGraphicsView->setDragMode(QGraphicsView::NoDrag);
    m_scene->setMode(DiagramScene::InsertDeviceShape);
    m_scene->setDeviceShapeType(DeviceShape::ShapeType(idButton));
    m_scene->setSelectableItems(false);
    if (m_simpleDrawModeActionGr->checkedAction() != nullptr)
        m_simpleDrawModeActionGr->checkedAction()->setChecked(false);
    ui->actionSelect_All->setDisabled(true);
    ui->actionDeleteItem->setDisabled(true);
}

void MainWindow::insertBuildingShape(QAbstractButton *button)
{
    const QList<QAbstractButton *> buttonList = m_buildingShapeButtonGroup->buttons();
    for (const QAbstractButton *p_button : buttonList) {
        if (p_button != button)
            button->setChecked(false);
    }
    const int idButton = m_buildingShapeButtonGroup->id(button);
    BuildingShape::ShapeType shapeType {BuildingShape::ShapeType(idButton)};
    QScopedPointer<BuildingShape, BuildingShape::BuildingShapeDeleter>
            sc_buildingShape{BuildingShape::createBuildingShape(shapeType)};
    if (shapeType == BuildingShape::Wall) {
        sc_buildingShape->setPen(m_wallPen);
        sc_buildingShape->setBrush(m_wallBrush);
        sc_buildingShape->setHeight(m_wallHeight);
    }
    ui->mainGraphicsView->setCursor(QCursor(sc_buildingShape->image()));
    ui->mainGraphicsView->setDragMode(QGraphicsView::NoDrag);
    m_scene->setMode(DiagramScene::InsertBuildingShape);
    m_scene->setBuildingShapeType(BuildingShape::ShapeType(idButton));
    m_scene->setSelectableItems(false);
    if (m_simpleDrawModeActionGr->checkedAction() != nullptr)
        m_simpleDrawModeActionGr->checkedAction()->setChecked(false);
    ui->actionSelect_All->setDisabled(true);
    ui->actionDeleteItem->setDisabled(true);
}

void MainWindow::selectedItem()
{
    ui->mainGraphicsView->setCursor(Qt::ArrowCursor);
    ui->mainGraphicsView->setDragMode(QGraphicsView::RubberBandDrag);
    m_scene->setMode(DiagramScene::SelectItem);
    m_scene->setSelectableItems(true);
    ui->actionSelect_All->setEnabled(true);
}

void MainWindow::bringToFront()
{
    if (m_scene->selectedItems().isEmpty())
        return;

    QGraphicsItem *p_selectedShape = m_scene->selectedItems().constFirst();
    const QList<QGraphicsItem *> overlapShapeList = p_selectedShape->collidingItems();
    qreal zValue = 0;
    zValue = std::accumulate(overlapShapeList.begin(), overlapShapeList.end(), zValue
                             , [](qreal zValue, QGraphicsItem *p_shape){
            return p_shape->zValue() >= zValue  ? p_shape->zValue() + 0.1 : zValue;});
    p_selectedShape->setZValue(zValue);
}

void MainWindow::sendToBack()
{
    if (m_scene->selectedItems().isEmpty())
        return;

    QGraphicsItem *p_selectShape = m_scene->selectedItems().constFirst();
    const QList<QGraphicsItem *> overlapShapeList = p_selectShape->collidingItems();
    qreal zValue = 0;
    zValue = std::accumulate(overlapShapeList.begin(), overlapShapeList.end(), zValue
                             , [](qreal zValue, QGraphicsItem *p_shape){
            return p_shape->zValue() <= zValue ? p_shape->zValue() - 0.1 : zValue;});
    p_selectShape->setZValue(zValue);
}

void MainWindow::about()
{
    QString header = tr("<p align=\"center\"><b> RSiSed </b>") + VERSION + " (" + DATE +")""</p>";
    QString app = tr("<p>This application is designed for the alignment of forces "
                     "and means in case of fire. (<b>RSiSed</b>)</p>");
    QString license = "<p>Copyright (c) 2022 by Viktor Ermolov <br>"
                         "Email: " EMAIL "</p>"

                         "<p><b>RSiSed</b> is free software: you can redistribute it and/or modify "
                         "it under the terms of the GNU General Public License as published by "
                         "the Free Software Foundation, either version 3 of the License, or "
                         "(at your option) any later version.</p>"

                         "<p><b>RSiSed</b> is distributed in the hope that it will be useful, "
                         "but WITHOUT ANY WARRANTY; without even the implied warranty of "
                         "MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the "
                         "GNU General Public License for more details.</p>"

                         "<p>You should have received a copy of the GNU General Public License "
                         "along with this program. "
                         "If not, see ";
    QString linkGNU = "<a href= \"https://www.gnu.org/licenses/\">https://www.gnu.org/licenses/</a> .</p>";
    QMessageBox::about(this, tr("About RSiSed"), header + app + license + linkGNU);
}

void MainWindow::aboutQt()
{
    QMessageBox::aboutQt(this, tr("About Qt"));
}

void MainWindow::changedItemPen()
{
    QColor currentPenColor = m_penColorButton->color();
    qreal currentPenWidth = qvariant_cast<qreal>(m_penSizeCombo->currentText());
    Qt::PenStyle currentPenStyle = qvariant_cast<Qt::PenStyle>(m_penStyleCombo->currentData());
    m_scene->setItemPen(currentPenColor, currentPenWidth, currentPenStyle);
}

void MainWindow::changedItemBrush()
{
    QColor currentBrushColor = m_brushColorButton->color();
    Qt::BrushStyle currentBrushStyle = qvariant_cast<Qt::BrushStyle>
            (m_brushStyleCombo->currentData());
    m_scene->setItemBrush(currentBrushColor, currentBrushStyle);
}

void MainWindow::changedFont()
{
    m_currentFont = m_fontCombo->currentFont();
    m_currentFont.setPointSize(m_fontSizeCombo->currentText().toInt());
    m_currentFont.setWeight(m_boldAction->isChecked() ? QFont::Bold : QFont::Normal);
    m_currentFont.setItalic(m_italicAction->isChecked());
    m_currentFont.setUnderline(m_underLineAction->isChecked());
    QColor currentTextColor(m_textColorButton->color());
    m_scene->setItemFont(m_currentFont, currentTextColor);
}

bool MainWindow::showWallSettingDialog()
{
    WallSetting *p_wallSettingDialog = new WallSetting(m_wallPen, m_wallBrush, m_wallHeight, this);

    if (p_wallSettingDialog->exec() != QDialog::Accepted)
        return false;

    int currentPenWidth{p_wallSettingDialog->penWidth()};
    QColor currentPenColor{p_wallSettingDialog->penColor()};
    m_wallPen = QPen(currentPenColor, currentPenWidth);
    m_scene->setWallPen(currentPenColor, currentPenWidth);
    QColor currentHtchingColor{p_wallSettingDialog->hatchingColor()};
    Qt::BrushStyle currentHatchingStyle{p_wallSettingDialog->hatchingStyle()};
    m_wallBrush = QBrush(currentHtchingColor, currentHatchingStyle);
    m_scene->setWallHatching(currentHtchingColor, currentHatchingStyle);
    qreal currentWallHeight{p_wallSettingDialog->wallHeight()};
    m_wallHeight = p_wallSettingDialog->wallHeight();
    m_scene->setWallHeight(currentWallHeight);

    QScopedPointer<BuildingShape, BuildingShape::BuildingShapeDeleter>
            sc_buildingShape{BuildingShape::createBuildingShape(BuildingShape::Wall)};
    sc_buildingShape->setPen(QPen(currentPenColor, currentPenWidth));
    sc_buildingShape->setBrush(QBrush(currentHtchingColor, currentHatchingStyle));
    sc_buildingShape->setHeight(currentWallHeight);
    QIcon icon(sc_buildingShape->image());
    qreal iconWidth{sc_buildingShape->rect().width() / 2.0};
    qreal iconHeight{36.0};
    m_buildingShapeButtonGroup->button(BuildingShape::Wall)->setIcon(icon);
    m_buildingShapeButtonGroup->button(BuildingShape::Wall)->setIconSize(QSize(iconWidth
                                                                               , iconHeight));
    ui->actionSelectedItem->setChecked(true);
    selectedItem();

    return true;
}

void MainWindow::createShapeToolBox()
{
    m_technicsButtonGroup = new QButtonGroup(this);
    m_technicsButtonGroup->setExclusive(false);
    connect(m_technicsButtonGroup, QOverload<QAbstractButton *>::of(&QButtonGroup::buttonClicked)
            , this, &MainWindow::insertTechnicsShape);
    QGridLayout *p_technicsLayout = new QGridLayout(this);
    p_technicsLayout->addWidget(createTechnicsCellWidget(tr("Car"), TechnicsShape::Base), 0, 0);
    p_technicsLayout->addWidget(createTechnicsCellWidget(tr("Tanker")
                                                       , TechnicsShape::Tanker), 0, 1);
    p_technicsLayout->addWidget(createTechnicsCellWidget(tr("Auto pump")
                                                       , TechnicsShape::PumpHose), 0, 2);
    p_technicsLayout->addWidget(createTechnicsCellWidget(tr("First aid")
                                                       , TechnicsShape::FirstAid), 0, 3);
    p_technicsLayout->addWidget(createTechnicsCellWidget(tr("Emergency")
                                                       , TechnicsShape::Emergency), 1, 0);
    p_technicsLayout->addWidget(createTechnicsCellWidget(tr("Auto ladder")
                                                       , TechnicsShape::AutoLadder), 1, 1);
    p_technicsLayout->addWidget(createTechnicsCellWidget(tr("Crank lift")
                                                       , TechnicsShape::CrankLift), 1, 2);
    p_technicsLayout->addWidget(createTechnicsCellWidget(tr("Telescopic lift")
                                                       , TechnicsShape::TelescopicLift), 1, 3);
    p_technicsLayout->addWidget(createTechnicsCellWidget(tr("Hose_car")
                                                         , TechnicsShape::HoseCar), 2, 0);
//    p_technicsLayout->addWidget(createTechnicsCellWidget(tr("Comm"), TechnicsShape::Comm), 3, 0);
//    p_technicsLayout->addWidget(createTechnicsCellWidget(tr("Tech_serv")
//                                                       , TechnicsShape::Tech_serv), 3, 1);
//    p_technicsLayout->addWidget(createTechnicsCellWidget(tr("Smok_rem")
//                                                       , TechnicsShape::Smok_rem), 3, 2);
//    p_technicsLayout->addWidget(createTechnicsCellWidget(tr("AutoPumpS")
//                                                       , TechnicsShape::AutoPumpS), 4, 0);
//    p_technicsLayout->addWidget(createTechnicsCellWidget(tr("CarriageCar_1")
//                                                       , TechnicsShape::CarriageCar_1), 4, 1);
//    p_technicsLayout->addWidget(createTechnicsCellWidget(tr("CarriageCar_2")
//                                                       , TechnicsShape::CarriageCar_2), 4, 2);
//    p_technicsLayout->addWidget(createTechnicsCellWidget(tr("Aerodrom")
//                                                       , TechnicsShape::Aerodrome), 5, 0);
//    p_technicsLayout->addWidget(createTechnicsCellWidget(tr("Foam")
//                                                       , TechnicsShape::Foam), 5, 1);
//    p_technicsLayout->addWidget(createTechnicsCellWidget(tr("Combo")
//                                                       , TechnicsShape::Combo), 5, 2);
//    p_technicsLayout->addWidget(createTechnicsCellWidget(tr("Aerosol")
//                                                       , TechnicsShape::Aerosol), 6, 0);
//    p_technicsLayout->addWidget(createTechnicsCellWidget(tr("Powder")
//                                                       , TechnicsShape::Powder), 6, 1);
//    p_technicsLayout->addWidget(createTechnicsCellWidget(tr("Carbon")
//                                                       , TechnicsShape::Carbon), 6, 2);
//    p_technicsLayout->addWidget(createTechnicsCellWidget(tr("GazWater")
//                                                       , TechnicsShape::GazWater), 7, 0);
//    p_technicsLayout->addWidget(createTechnicsCellWidget(tr("Tracked")
//                                                       , TechnicsShape::Tracked), 7, 1);
//    p_technicsLayout->addWidget(createTechnicsCellWidget(tr("Tank")
//                                                       , TechnicsShape::Tank), 7, 2);
//    p_technicsLayout->addWidget(createTechnicsCellWidget(tr("GDZS")
//                                                       , TechnicsShape::GDZS), 8, 0);
//    p_technicsLayout->addWidget(createTechnicsCellWidget(tr("Waterproof")
//                                                       , TechnicsShape::Waterproof), 8, 1);
//    p_technicsLayout->addWidget(createTechnicsCellWidget(tr("Laboratory")
//                                                       , TechnicsShape::Laboratory), 8, 2);
//    p_technicsLayout->addWidget(createTechnicsCellWidget(tr("StaffCar")
//                                                       , TechnicsShape::StaffCar), 9, 0);
//    p_technicsLayout->addWidget(createTechnicsCellWidget(tr("Trailer")
//                                                       , TechnicsShape::Trailer), 9, 1);
//    p_technicsLayout->addWidget(createTechnicsCellWidget(tr("Vessel")
//                                                       , TechnicsShape::Vessel), 9, 2);
//    p_technicsLayout->addWidget(createTechnicsCellWidget(tr("Boat")
//                                                       , TechnicsShape::Boat), 10, 0);
//    p_technicsLayout->addWidget(createTechnicsCellWidget(tr("Train")
//                                                       , TechnicsShape::Train), 10, 1);
//    p_technicsLayout->addWidget(createTechnicsCellWidget(tr("Plane")
//                                                           , TechnicsShape::Plane), 10, 2);
//    p_technicsLayout->addWidget(createTechnicsCellWidget(tr("Seaplane")
//                                                           , TechnicsShape::Seaplane), 11, 0);
//    p_technicsLayout->addWidget(createTechnicsCellWidget(tr("Helicopter")
//                                                           , TechnicsShape::Helicopter), 11, 1);
//    p_technicsLayout->addWidget(createTechnicsCellWidget(tr("MotoPump 1")
//                                                           , TechnicsShape::MotoPump_1), 11, 2);
//    p_technicsLayout->addWidget(createTechnicsCellWidget(tr("MotoPump 2")
//                                                           , TechnicsShape::MotoPump_2), 12, 0);
//    p_technicsLayout->addWidget(createTechnicsCellWidget(tr("TrailerPowder")
//                                                           , TechnicsShape::TrailerPowder), 12, 1);
//    p_technicsLayout->addWidget(createTechnicsCellWidget(tr("Adapted")
//                                                       , TechnicsShape::Adapted), 12, 2);
//    p_technicsLayout->addWidget(createTechnicsCellWidget(tr("Other adapted")
//                                                       , TechnicsShape::OtherAdapted), 13, 0);
//    p_technicsLayout->addWidget(createTechnicsCellWidget(tr("Ambulance")
//                                                       , TechnicsShape::Ambulance), 13, 1);
//    p_technicsLayout->addWidget(createTechnicsCellWidget(tr("Police")
//                                                       , TechnicsShape::Police), 13, 2);
    p_technicsLayout->setRowStretch(14, 10);
    p_technicsLayout->setColumnStretch(3, 10);
    QWidget *p_technicsWidget = new QWidget(this);
    p_technicsWidget->setLayout(p_technicsLayout);

    m_deviceButtonGroup = new QButtonGroup(this);
    m_deviceButtonGroup->setExclusive(false);
    connect(m_deviceButtonGroup, QOverload<QAbstractButton *>::of(&QButtonGroup::buttonClicked)
            , this, &MainWindow::insertDeviceShape);
    QGridLayout *p_deviceLayout = new QGridLayout(this);
    p_deviceLayout->addWidget(createDeviceCellWidget(tr("Barrel 0"), DeviceShape::Barrel_0), 0, 0);
    p_deviceLayout->addWidget(createDeviceCellWidget(tr("Barrel 1"), DeviceShape::Barrel_1), 0, 1);
    p_deviceLayout->addWidget(createDeviceCellWidget(tr("Barrel 2"), DeviceShape::Barrel_2), 0, 2);
    p_deviceLayout->addWidget(createDeviceCellWidget(tr("Barrel 3"), DeviceShape::Barrel_3), 1, 0);
    p_deviceLayout->addWidget(createDeviceCellWidget(tr("Barrel 4"), DeviceShape::Barrel_4), 1, 1);
    p_deviceLayout->addWidget(createDeviceCellWidget(tr("Barrel 5"), DeviceShape::Barrel_5), 1, 2);
    p_deviceLayout->addWidget(createDeviceCellWidget(tr("Barrel 6"), DeviceShape::Barrel_6), 2, 0);
    p_deviceLayout->addWidget(createDeviceCellWidget(tr("Carriage 1")
                                                   , DeviceShape::Carriage_1), 2, 1);
    p_deviceLayout->addWidget(createDeviceCellWidget(tr("Carriage 2")
                                                   , DeviceShape::Carriage_2), 2, 2);
    p_deviceLayout->addWidget(createDeviceCellWidget(tr("Carriage 3")
                                                   , DeviceShape::Carriage_3), 3, 0);
    p_deviceLayout->addWidget(createDeviceCellWidget(tr("Carriage 4")
                                                   , DeviceShape::Carriage_4), 3, 1);
    p_deviceLayout->addWidget(createDeviceCellWidget(tr("Carriage 5")
                                                   , DeviceShape::Carriage_5), 3, 2);
    p_deviceLayout->addWidget(createDeviceCellWidget(tr("Branch 2")
                                                   , DeviceShape::Branches_2), 4, 0);
    p_deviceLayout->addWidget(createDeviceCellWidget(tr("Branch 3")
                                                   , DeviceShape::Branches_3), 4, 1);
    p_deviceLayout->addWidget(createDeviceCellWidget(tr("Branch 4")
                                                   , DeviceShape::Branches_4), 4, 2);
    p_deviceLayout->addWidget(createDeviceCellWidget(tr("Ladder 1"), DeviceShape::Ladder_1), 5, 0);
    p_deviceLayout->addWidget(createDeviceCellWidget(tr("Ladder 2"), DeviceShape::Ladder_2), 5, 1);
    p_deviceLayout->addWidget(createDeviceCellWidget(tr("Ladder 3"), DeviceShape::Ladder_3), 5, 2);
    p_deviceLayout->addWidget(createDeviceCellWidget(tr("Reel"), DeviceShape::Reel), 6, 0);
    p_deviceLayout->addWidget(createDeviceCellWidget(tr("Reel_mob")
                                                   , DeviceShape::Reel_mobile), 6, 1);
    p_deviceLayout->addWidget(createDeviceCellWidget(tr("Column"), DeviceShape::Column), 6, 2);
    p_deviceLayout->addWidget(createDeviceCellWidget(tr("HydElev")
                                                   , DeviceShape::HydrElevator), 7, 0);
    p_deviceLayout->addWidget(createDeviceCellWidget(tr("FoamMix")
                                                   , DeviceShape::Foam_mix), 7, 1);
    p_deviceLayout->addWidget(createDeviceCellWidget(tr("Collect")
                                                   , DeviceShape::Collector), 7, 2);
    p_deviceLayout->addWidget(createDeviceCellWidget(tr("Bridge"), DeviceShape::Bridge), 8, 0);
    p_deviceLayout->addWidget(createDeviceCellWidget(tr("Smok 1"), DeviceShape::SmokePump_1), 8, 1);
    p_deviceLayout->addWidget(createDeviceCellWidget(tr("Smok 2"), DeviceShape::SmokePump_2), 8, 2);
    p_deviceLayout->addWidget(createDeviceCellWidget(tr("Hose"), DeviceShape::Hose), 9, 0);
    p_deviceLayout->addWidget(createDeviceCellWidget(tr("FLift 1"), DeviceShape::FoamLift_1), 9, 1);
    p_deviceLayout->addWidget(createDeviceCellWidget(tr("FLift 2"), DeviceShape::FoamLift_2), 9, 2);
    p_deviceLayout->setRowStretch(10, 10);
    p_deviceLayout->setColumnStretch(3, 10);
    QWidget *p_deviceWidget = new QWidget(this);
    p_deviceWidget->setLayout(p_deviceLayout);

    m_buildingShapeButtonGroup = new QButtonGroup(this);
    m_buildingShapeButtonGroup->setExclusive(false);
    connect(m_buildingShapeButtonGroup
            , QOverload<QAbstractButton *>::of(&QButtonGroup::buttonClicked)
            , this, &MainWindow::insertBuildingShape);
    QGridLayout *p_buildShapeLayout= new QGridLayout(this);
    p_buildShapeLayout->addWidget(createBuildingShapeCellWidget(tr("Wall")
                                                                , BuildingShape::Wall), 0, 0);
    p_buildShapeLayout->addWidget(createBuildingShapeCellWidget(tr("Window")
                                                                , BuildingShape::Window), 0, 1);
    p_buildShapeLayout->addWidget(createBuildingShapeCellWidget(tr("Door")
                                                                , BuildingShape::Door), 0, 2);
    p_buildShapeLayout->addWidget(createBuildingShapeCellWidget(tr("Opening")
                                                                , BuildingShape::Open), 1, 0);
    p_buildShapeLayout->addWidget(createBuildingShapeCellWidget(tr("Stairwell")
                                                                , BuildingShape::Stairwell), 1, 1);
    p_buildShapeLayout->addWidget(createBuildingShapeCellWidget(tr("Stairs")
                                                                , BuildingShape::Stairs), 1, 2);
    p_buildShapeLayout->setRowStretch(3, 10);
    p_buildShapeLayout->setColumnStretch(3, 10);
    QWidget *p_buildingWidget = new QWidget(this);
    p_buildingWidget->setLayout(p_buildShapeLayout);

    m_shapeToolBox = new QToolBox(this);
    m_shapeToolBox->addItem(p_buildingWidget, tr("Building structures"));
    m_shapeToolBox->addItem(p_technicsWidget, tr("Technics"));
    m_shapeToolBox->addItem(p_deviceWidget, tr("Device"));
    m_shapeToolBox->setSizePolicy(QSizePolicy::Maximum, QSizePolicy::Ignored);
    m_shapeToolBox->setMinimumWidth(p_technicsWidget->sizeHint().width());
}

void MainWindow::disableAction()
{
    ui->actionCopy->setDisabled(true);
    ui->actionPaste->setDisabled(true);
    ui->actionCut->setDisabled(true);
    ui->actionDeleteItem->setDisabled(true);
}

void MainWindow::enableAction()
{
    QList<QGraphicsItem *> selectedShapeList = m_scene->selectedItems();
    if (selectedShapeList.isEmpty()) {
        ui->actionCopy->setDisabled(true);
        ui->actionCut->setDisabled(true);
        ui->actionDeleteItem->setDisabled(true);
    } else {
        ui->actionCopy->setEnabled(true);
        ui->actionCut->setEnabled(true);
        ui->actionDeleteItem->setEnabled(true);
    }
}

void MainWindow::createActions()
{
    // Scene
    m_sceneScaleMinAction = new QAction(QIcon(":images/icons/zoomminus.png"),
                                      tr("Zoom out"), this);
    m_sceneScaleMinAction->setShortcut(tr("Ctrl+-"));
    m_sceneScaleMinAction->setText("Zoom out");
    m_sceneScaleMinAction->setToolTip(tr("Zoom out the scene by 10%"));
    connect(m_sceneScaleMinAction, &QAction::triggered, this, &MainWindow::sceneZoomInOut);

    m_sceneScaleMaxAction = new QAction(QIcon(":images/icons/zoomplus.png"),
                                      tr("Zoom in"), this);
    m_sceneScaleMaxAction->setText("Zoom in");
    m_sceneScaleMaxAction->setShortcut(tr("Ctrl++"));
    m_sceneScaleMaxAction->setToolTip(tr("Zoom in on the scene by 10%"));
    connect(m_sceneScaleMaxAction, &QAction::triggered, this, &MainWindow::sceneZoomInOut);

    // Font
    m_boldAction = new QAction(QIcon(":images/icons/bold_48.png"), tr("Bold"), this);
    m_boldAction->setCheckable(true);
    m_boldAction->setShortcut(tr("Ctrl+B"));
    connect(m_boldAction, &QAction::triggered, this, &MainWindow::changedFont);

    m_italicAction = new QAction(QIcon(":images/icons/italic_48.png"), tr("Italic"), this);
    m_italicAction->setCheckable(true);
    m_italicAction->setShortcut(tr("Ctrl+I"));
    connect(m_italicAction, &QAction::triggered, this, &MainWindow::changedFont);

    m_underLineAction = new QAction(QIcon(":images/icons/underline_48.png"), tr("Underline"), this);
    m_underLineAction->setCheckable(true);
    m_underLineAction->setShortcut(tr("Ctrl+U"));
    connect(m_underLineAction, &QAction::triggered, this, &MainWindow::changedFont);
}

void MainWindow::createMenu()
{
    //Create menuView
    ui->menuView->addAction(m_sceneScaleMinAction);
    ui->menuView->addAction(m_sceneScaleMaxAction);

    // Create shape context menu
    m_contextMenu = new QMenu(this);
    m_contextMenu->addAction(ui->actionCopy);
    m_contextMenu->addAction(ui->actionPaste);
    m_contextMenu->addAction(ui->actionCut);
    m_contextMenu->addAction(ui->actionDeleteItem);
    m_contextMenu->addAction(ui->actionSelect_All);
    m_contextMenu->addSeparator();
    m_contextMenu->addAction(ui->actionBring_to_front);
    m_contextMenu->addAction(ui->actionSend_to_back);
}

void MainWindow::createStyleToolBar()
{
    // Pen style
    m_penStyleCombo = new QComboBox(this);
    m_penStyleCombo->addItem(QIcon(":images/icons/nobrush.png"), tr("NoPen"), "Qt::NoPen");
    m_penStyleCombo->addItem(QIcon(":images/icons/solidline_48.png"), tr("Solid"), "Qt::SolidLine");
    m_penStyleCombo->addItem(QIcon(":images/icons/dashline_48.png"), tr("Dash"), "Qt::DashLine");
    m_penStyleCombo->addItem(QIcon(":images/icons/dotline_32.svg"), tr("Dot"), "Qt::DotLine");
    m_penStyleCombo->addItem(QIcon(":images/icons/dashdotline_32.png"), tr("DashDot"), "Qt::DashDotLine");
    m_penStyleCombo->addItem(QIcon(":images/icons/dashdotdot.svg"), tr("DashDotDot"), "Qt::DashDotDotLine");
    m_penStyleCombo->setCurrentIndex(1);
    m_penStyleCombo->setToolTip(tr("Changing the pen style"));
    connect(m_penStyleCombo, QOverload<int>::of(&QComboBox::currentIndexChanged),
            this, &MainWindow::changedItemPen);

    // Pen width
    m_penSizeCombo = new QComboBox(this);
    for (int i = 0; i < 10; ++i) {
        m_penSizeCombo->insertItem(i, QString().setNum(i), QString(i));
    }
    m_penSizeCombo->setCurrentIndex(1);
    m_penSizeCombo->setToolTip(tr("Changing the pen thickness"));
    connect(m_penSizeCombo, QOverload<int>::of(&QComboBox::currentIndexChanged),
            this, &MainWindow::changedItemPen);

    // Pen color
    QFrame *p_penColorFrame = new QFrame(this);
    QHBoxLayout *p_penColorHBoxLayout = new QHBoxLayout(this);
    p_penColorFrame->setLayout(p_penColorHBoxLayout);
    m_penColorButton = new KColorButton(this);
    m_penColorButton->setColor(Qt::black);
    m_penColorButton->setFixedWidth(32);
    m_penColorButton->setToolTip(tr("Changing the color of the pen"));
    p_penColorHBoxLayout->addWidget(m_penColorButton);
    QLabel *p_penColorLabel = new QLabel(this);
    p_penColorLabel->setScaledContents(true);
    p_penColorLabel->setPixmap(QPixmap(":/images/icons/pen_l.png"));
    p_penColorLabel->setFixedSize(28, 28);
    p_penColorHBoxLayout->addWidget(p_penColorLabel);
    connect(m_penColorButton, &KColorButton::changed, this, &MainWindow::changedItemPen);

    // Brush style
    m_brushStyleCombo = new QComboBox(this);
    m_brushStyleCombo->addItem(QIcon(":images/icons/nobrush.png"), tr("No brush"), "Qt::NoBrush");
    m_brushStyleCombo->addItem(QIcon(":images/icons/solidbrush.png"), tr("Solid"), "Qt::SolidPattern");
    m_brushStyleCombo->addItem(QIcon(":images/icons/horizontalbrush.png"), tr("Horizontal"), "Qt::HorPattern");
    m_brushStyleCombo->addItem(QIcon(":images/icons/verticalbrush.png"), tr("Vertical"), "Qt::VerPattern");
    m_brushStyleCombo->addItem(QIcon(":images/icons/gridbrush.png"), tr("Cross"), "Qt::CrossPattern");
    m_brushStyleCombo->addItem(QIcon(":images/icons/bdiagbrush.png"), tr("BDiag"), "Qt::BDiagPattern");
    m_brushStyleCombo->addItem(QIcon(":images/icons/fdiagbrush.png"), tr("FDiag"), "Qt::FDiagPattern");
    m_brushStyleCombo->addItem(QIcon(":images/icons/diagcrossbrush.png"), tr("DiagCross"), "Qt::DiagCrossPattern");
    m_brushStyleCombo->addItem(QIcon(":images/icons/dense_1.png"), tr("Dense 1"), "Qt::Dense1Pattern");
    m_brushStyleCombo->addItem(QIcon(":images/icons/dense_2.png"), tr("Dense 2"), "Qt::Dense2Pattern");
    m_brushStyleCombo->addItem(QIcon(":images/icons/dense_3.png"), tr("Dense 3"), "Qt::Dense3Pattern");
    m_brushStyleCombo->addItem(QIcon(":images/icons/dense_4.png"), tr("Dense 4"), "Qt::Dense4Pattern");
    m_brushStyleCombo->addItem(QIcon(":images/icons/dense_5.png"), tr("Dense 5"), "Qt::Dense5Pattern");
    m_brushStyleCombo->addItem(QIcon(":images/icons/dense_6.png"), tr("Dense 6"), "Qt::Dense6Pattern");
    m_brushStyleCombo->addItem(QIcon(":images/icons/dense_7.png"), tr("Dense 7"), "Qt::Dense7Pattern");
    m_brushStyleCombo->setCurrentIndex(1);
    m_brushStyleCombo->setToolTip(tr("Changing the fill style"));
    connect(m_brushStyleCombo, QOverload<int>::of(&QComboBox::currentIndexChanged),
            this, &MainWindow::changedItemBrush);

    // Brush color
    QFrame *p_brushColorFrame = new QFrame(this);
    QHBoxLayout *p_brushColorHBoxLayout = new QHBoxLayout(this);
    p_brushColorFrame->setLayout(p_brushColorHBoxLayout);
    m_brushColorButton = new KColorButton(this);
    m_brushColorButton->setColor(Qt::white);
    m_brushColorButton->setFixedWidth(32);
    m_brushColorButton->setToolTip(tr("Changing the fill color"));
    p_brushColorHBoxLayout->addWidget(m_brushColorButton);
    QLabel *p_brushColorLabel = new QLabel(this);
    p_brushColorLabel->setScaledContents(true);
    p_brushColorLabel->setPixmap(QPixmap(":/images/icons/brushpaint_32.png"));
    p_brushColorLabel->setFixedSize(28, 28);
    p_brushColorHBoxLayout->addWidget(p_brushColorLabel);
    connect(m_brushColorButton, &KColorButton::changed, this, &MainWindow::changedItemBrush);

    // Create item style ToolBar
    m_styleToolBar = addToolBar(tr("Item style"));
    m_styleToolBar->addWidget(m_penStyleCombo);
    m_styleToolBar->addWidget(m_penSizeCombo);
    m_styleToolBar->addWidget(p_penColorFrame);
    m_styleToolBar->addSeparator();
    m_styleToolBar->addWidget(m_brushStyleCombo);
    m_styleToolBar->addWidget(p_brushColorFrame);
}

void MainWindow::createFontStyleToolBar()
{
    m_fontCombo = new QFontComboBox(this);
    m_fontCombo->setWritingSystem(QFontDatabase::Cyrillic);
    m_fontCombo->setToolTip(tr("Change the font of the text"));
    connect(m_fontCombo, &QFontComboBox::currentFontChanged, this, &MainWindow::changedFont);

    m_fontSizeCombo = new QComboBox(this);
    m_fontSizeCombo->setEditable(true);
    for (int i = 8; i < 30; i = i + 2)
        m_fontSizeCombo->addItem(QString().setNum(i));
    QIntValidator *p_validator = new QIntValidator(2, 64, this);
    m_fontSizeCombo->setValidator(p_validator);
    m_fontSizeCombo->setCurrentIndex(2);
    m_fontSizeCombo->setToolTip(tr("Change the font size of the text"));
    connect(m_fontSizeCombo, &QComboBox::currentTextChanged, this, &MainWindow::changedFont);

    m_textColorButton = new KColorButton(this);
    m_textColorButton->setColor(Qt::black);
    m_textColorButton->setFixedWidth(32);
    m_textColorButton->setToolTip(tr("Changing the color of the text"));
    connect(m_textColorButton, &KColorButton::changed, this, &MainWindow::changedFont);

    m_textStyleToolBar = addToolBar(tr("Font style")) ;
    m_textStyleToolBar->addWidget(m_fontCombo);
    m_textStyleToolBar->addWidget(m_fontSizeCombo);
    m_textStyleToolBar->addAction(m_boldAction);
    m_textStyleToolBar->addAction(m_italicAction);
    m_textStyleToolBar->addAction(m_underLineAction);
    m_textStyleToolBar->addWidget(m_textColorButton);
}

void MainWindow::createSimpleDrawToolBar()
{
    m_simpleDrawModeActionGr = new QActionGroup(this);
    m_simpleDrawModeActionGr->addAction(ui->actionSelectedItem);
    m_simpleDrawModeActionGr->addAction(ui->actionDrawPolyline);
    m_simpleDrawModeActionGr->addAction(ui->actionDrawCurve);
    m_simpleDrawModeActionGr->addAction(ui->actionDrawRectangle);
    m_simpleDrawModeActionGr->addAction(ui->actionDrawEllipse);
    m_simpleDrawModeActionGr->addAction(ui->actionDrawPie);
    m_simpleDrawModeActionGr->addAction(ui->actionInsertText);
    m_simpleDrawModeActionGr->addAction(ui->actionInsertImage);
    m_simpleDrawModeActionGr->setExclusive(true);
}

void MainWindow::createSceneScaleToolBar()
{
    m_sceneScaleCombo = new QComboBox(this);
    QStringList scalesList;
    scalesList << tr("25%") << tr("50%") << tr("75%") << tr("100%") << tr("125%")
           << tr("150%") << tr("200%") << tr("300%") << tr("500%");
    m_sceneScaleCombo->addItems(scalesList);
    m_sceneScaleCombo->setCurrentIndex(3);
    m_sceneScaleCombo->setEditable(true);
    m_sceneScaleCombo->setToolTip(tr("Changing the scene scale"));
    connect(m_sceneScaleCombo, &QComboBox::currentTextChanged,
            this, &MainWindow::sceneScaleChanged);

    m_sceneScaleToolBar = addToolBar(tr("Scene scale"));
    m_sceneScaleToolBar->addAction(m_sceneScaleMinAction);
    m_sceneScaleToolBar->addAction(m_sceneScaleMaxAction);
    m_sceneScaleToolBar->addWidget(m_sceneScaleCombo);
}

QWidget *MainWindow::createTechnicsCellWidget(const QString &text, TechnicsShape::ShapeType type)
{
    QScopedPointer<TechnicsShape, TechnicsShape::TechnicsShapeDeleter>
            sc_technicsShape{TechnicsShape::createTechnicsShape(type)};
    QIcon icon(sc_technicsShape->image());
    qreal iconWidth{sc_technicsShape->boundingRect().width() / 2.0};
    qreal iconHeight{sc_technicsShape->boundingRect().height() / 2.0};

    QToolButton *p_technicsButton = new QToolButton(this);
    p_technicsButton->setIcon(icon);
    p_technicsButton->setIconSize(QSize(iconWidth, iconHeight));
    p_technicsButton->setCheckable(true);
    m_technicsButtonGroup->addButton(p_technicsButton, int(type));

    QGridLayout *p_technicsShapeLayout = new QGridLayout(this);
    p_technicsShapeLayout->addWidget(p_technicsButton, 0, 0, Qt::AlignHCenter);
    p_technicsShapeLayout->addWidget(new QLabel(text, this), 1, 0, Qt::AlignCenter);

    QWidget *p_technicsShapeWidget = new QWidget(this);
    p_technicsShapeWidget->setLayout(p_technicsShapeLayout);

    return p_technicsShapeWidget;
}

QWidget *MainWindow::createDeviceCellWidget(const QString &text, DeviceShape::ShapeType type)
{
    DeviceShape deviceShape(type);
    QIcon icon(deviceShape.image());
    qreal iconWidth{deviceShape.boundingRect().width() / 2.0};
    qreal iconHeight{deviceShape.boundingRect().height() / 2.0};

    QToolButton *p_deviceButtton = new QToolButton(this);
    p_deviceButtton->setIcon(icon);
    p_deviceButtton->setIconSize(QSize(iconWidth, iconHeight));
    p_deviceButtton->setCheckable(true);
    m_deviceButtonGroup->addButton(p_deviceButtton, int(type));

    QGridLayout *p_deviceShapeLayout = new QGridLayout(this);
    p_deviceShapeLayout->addWidget(p_deviceButtton, 0, 0, Qt::AlignCenter);
    p_deviceShapeLayout->addWidget(new QLabel(text, this), 1, 0, Qt::AlignCenter);

    QWidget *p_deviceShapeWidget = new QWidget(this);
    p_deviceShapeWidget->setLayout(p_deviceShapeLayout);

    return p_deviceShapeWidget;
}

QWidget *MainWindow::createBuildingShapeCellWidget(const QString &text
                                                   , BuildingShape::ShapeType type)
{
    QScopedPointer<BuildingShape, BuildingShape::BuildingShapeDeleter>
            sc_buildingShape{BuildingShape::createBuildingShape(type)};
    QIcon icon(sc_buildingShape->image());
    qreal iconWidth{sc_buildingShape->rect().width() / 2.0};
    qreal iconHeight{36.0};

    QToolButton *p_buildingButtton = new QToolButton(this);
    p_buildingButtton->setIcon(icon);
    p_buildingButtton->setIconSize(QSize(iconWidth, iconHeight));
    p_buildingButtton->setCheckable(true);
    m_buildingShapeButtonGroup->addButton(p_buildingButtton, int(type));

    QGridLayout *p_buildingShapeLayout = new QGridLayout(this);
    p_buildingShapeLayout->addWidget(p_buildingButtton, 0, 0, Qt::AlignCenter);
    p_buildingShapeLayout->addWidget(new QLabel(text, this), 1, 0, Qt::AlignCenter);

    QWidget *p_buildingShapeWidget = new QWidget(this);
    p_buildingShapeWidget->setLayout(p_buildingShapeLayout);

    return p_buildingShapeWidget;
}

bool MainWindow::maybeSave()
{
    if (!m_scene->isChanged()) {
        return true;
    }
    const QMessageBox::StandardButton ret
            = QMessageBox::warning(this, tr("RSiSed"),
                                   tr("The document has been modified.\n"
                                      "Do you want to save your changes?"),
                                   QMessageBox::Save | QMessageBox::Discard
                                   | QMessageBox::Cancel);
    switch (ret) {
    case QMessageBox::Save:
        return save();
    case QMessageBox::Cancel:
        return false;
    default:
        break;
    }
    return true;
}

bool MainWindow::saveFile(const QString &fileName)
{
    QString errorMessage;
    QGuiApplication::setOverrideCursor(Qt::WaitCursor);
    QFileInfo fi(fileName);
    QString suffix = fi.suffix();
    QSaveFile file(fileName);
    if (file.open(QFile::WriteOnly) && suffix == "rse") {
        QList<QGraphicsItem *> itemsList = m_scene->items();
        QRectF sceneRect = m_scene->sceneRect();
        QScopedPointer <RseWriter> writer(new RseWriter());
        writer->writeRse(&file, itemsList, sceneRect);
        if (!file.commit()) {
            errorMessage = tr("Cannot write file %1:\n%2.")
                    .arg(QDir::toNativeSeparators(fileName), file.errorString());
        }
    } else {
        errorMessage = tr("Cannot open file %1 for writing:\n%2.")
                .arg(QDir::toNativeSeparators(fileName), file.errorString());
    }
    QGuiApplication::restoreOverrideCursor();

    if (!errorMessage.isEmpty()) {
        QMessageBox::warning(this, tr("RSiSed"), errorMessage);
        return false;
    }

    ui->statusBar->showMessage(tr("File saved"), 10000);
    setCurrentFile(fileName);

    return true;
}

void MainWindow::setCurrentFile(const QString &fileName)
{
    m_currentFile = fileName;
    QString showName = m_currentFile;
    if (m_currentFile.isEmpty()) {
        showName = tr("untitled.rse");
    }
    setWindowTitle(showName + tr(" - RSiSed"));
    setWindowModified(false); // NOTE для Setting
    m_scene->setSceneChanged(false);
}

void MainWindow::deleteShape()
{
    QList<QGraphicsItem *> selectedShapeList = m_scene->selectedItems();
    for (QGraphicsItem *p_deletedShape : qAsConst(selectedShapeList)) {
        m_scene->removeItem(p_deletedShape);
        if (WallShape *p_deletedWallShape = dynamic_cast<WallShape *>(p_deletedShape)) {
            QSet<WallShape *> collidingWallSet = p_deletedWallShape->collidingWalls();
            for (WallShape *p_collidingWall : qAsConst(collidingWallSet))
                p_collidingWall->removeCollidingWall(p_deletedWallShape);
        }
        if (!m_copyList.contains(p_deletedShape))
            delete p_deletedShape;
    }
}

void MainWindow::selectAll()
{
    QList<QGraphicsItem *> shapeList = m_scene->items();
    for (QGraphicsItem *p_shape : qAsConst(shapeList)) {
        p_shape->setSelected(true);
    }
}

void MainWindow::sceneZoomInOut()
{
    double oldScale = m_sceneScaleCombo->currentText().leftRef
            (m_sceneScaleCombo->currentText().indexOf(tr("%"))).toDouble();
    if (sender() == m_sceneScaleMinAction) {
        oldScale = oldScale - 10;
    } else if (sender() == m_sceneScaleMaxAction) {
        oldScale = oldScale + 10;
    }
    QString newScale = QString().setNum(oldScale) + tr("%");
    m_sceneScaleCombo->setCurrentText(newScale);
    sceneScaleChanged(newScale);
}

void MainWindow::sceneScaleChanged(const QString &scale)
{
    double newScale = scale.leftRef(scale.indexOf(tr("%"))).toDouble() / 100.0;
    QTransform oldTransform = ui->mainGraphicsView->transform();
    ui->mainGraphicsView->resetTransform();
    ui->mainGraphicsView->translate(oldTransform.dx(), oldTransform.dy());
    ui->mainGraphicsView->scale(newScale, newScale);
}
