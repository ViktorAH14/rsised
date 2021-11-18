#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "rectangle.h"
#include "ellipse.h"
#include "polyline.h"
#include "curve.h"
#include "textitem.h"
#include "pixmapitem.h"
#include "rse_writer.h"
#include "rse_reader.h"
#include "svg_reader.h"

#include <QtWidgets>
#include <QSvgGenerator>
#include <KColorButton>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow), currentFile("")
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
    scene = new DiagramScene(ui->menuEdit, this);
    scene->setSceneRect(0, 0, 1240, 877); //A3
//    scene->setMode(DiagramScene::SelectItem); // TODO delete?
    scene->setItemPen(penColorButton->color(),
                      qvariant_cast<qreal>(penSizeCombo->currentText()),
                      qvariant_cast<Qt::PenStyle>(penStyleCombo->currentData()));
    scene->setItemBrush(brushColorButton->color(),
                        qvariant_cast<Qt::BrushStyle>(brushStyleCombo->currentData()));
    connect(scene, &QGraphicsScene::selectionChanged, this, &MainWindow::enableAction);
    ui->mainGraphicsView->setScene(scene);
    ui->mainGraphicsView->setRenderHints(QPainter::Antialiasing);
// TODO сделать выделение резиновой нитью   ui->mainGraphicsView->setDragMode(QGraphicsView::RubberBandDrag);

    QHBoxLayout *mainHBoxLayout = new QHBoxLayout;
    mainHBoxLayout->addWidget(shapeToolBox);
    mainHBoxLayout->addWidget(ui->mainGraphicsView);
    QWidget *mainWidget = new QWidget;
    mainWidget->setLayout(mainHBoxLayout);
    setCentralWidget(mainWidget);

    copyList = scene->selectedItems();

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

    scene->clear();

    RseReader *rseReader = new RseReader(ui->menuEdit);
    QRectF sceneRect = rseReader->getSceneRect(&file);
    scene->setSceneRect(sceneRect);
    file.close();

    if (!file.open(QFile::ReadOnly)) {
        QMessageBox::warning(this, tr("RSiSed"), tr("Cannot read file %1:\n%2.")
                             .arg(QDir::toNativeSeparators(fileName), file.errorString()));
        return;
    }

    QList<QGraphicsItem *> itemList = rseReader->getElement(&file);
    for (QGraphicsItem *item : qAsConst(itemList)) {
        if (Rectangle *rectangleItem = dynamic_cast<Rectangle *>(item)) {
            scene->addItem(rectangleItem);
        }
        if (Ellipse *ellipseItem = dynamic_cast<Ellipse *>(item)) {
            scene->addItem(ellipseItem);
        }
        if (Polyline *polylineItem = dynamic_cast<Polyline *>(item)) {
            scene->addItem(polylineItem);
        }
        if (Curve *curveItem = dynamic_cast<Curve *>(item)) {
            scene->addItem(curveItem);
        }
        if (QGraphicsLineItem *lineItem = dynamic_cast<QGraphicsLineItem *>(item)) {
            scene->addItem(lineItem);
        }
        if (TextItem *textItem = dynamic_cast<TextItem *>(item)) {
            scene->addItem(textItem);
        }
        if (PixmapItem *pixmapItem = dynamic_cast<PixmapItem *>(item)) {
            scene->addItem(pixmapItem);
        }
        if (TechnicsShape *technicsShapeItem = dynamic_cast<TechnicsShape *>(item)) {
            scene->addItem(technicsShapeItem);
        }
    }
    file.close();

#ifndef QT_NO_CURSOR
    QGuiApplication::restoreOverrideCursor();
#endif

    scene->setSelectableItems(true);
    setCurrentFile(fileName);
    ui->statusBar->showMessage(tr("File loaded"), 2000);
}

void MainWindow::closeEvent(QCloseEvent *event)
{
    if (maybeSave()) {
        scene->clearSelection();
        event->accept();
    } else {
        event->ignore();
    }
}

void MainWindow::newFile()
{
    if (maybeSave()) {
        scene->clear();
        setCurrentFile(QString());
    }
}

void MainWindow::open()
{
    if (maybeSave()) {
        QString fileName = QFileDialog::getOpenFileName(this, tr("Open")
                                                        , currentFile, tr("RSE files (*.rse)"));
        if (!fileName.isEmpty()) {
            loadFile(fileName);
        }
    }
}

bool MainWindow::save()
{
    if (currentFile.isEmpty()) {
        return saveAs();
    } else {
        return saveFile(currentFile);
    }
}

bool MainWindow::saveAs()
{
    QFileDialog fileDialog(this, tr("Save"), currentFile, tr("RSiSed files (*.rse)"));
    fileDialog.setWindowModality(Qt::WindowModal);
    fileDialog.setAcceptMode(QFileDialog::AcceptSave);
    if (fileDialog.exec() != QDialog::Accepted) {
        return false;
    }
    return saveFile(fileDialog.selectedFiles().constFirst());
}

void MainWindow::copy()
{
    copyList.clear();
    copyList = scene->selectedItems();
    if (!copyList.isEmpty()) {
        ui->actionPaste->setEnabled(true);
    }
}

void MainWindow::paste()
{
    for (QGraphicsItem *item : qAsConst(copyList)) {
        if (Rectangle *oldRect = dynamic_cast<Rectangle *>(item)) {
            Rectangle *newRect = new Rectangle(ui->menuEdit);
            newRect->setRect(oldRect->rect());
            newRect->setX(oldRect->x() + 10.0);
            newRect->setY(oldRect->y() + 10.0);
            newRect->setPen(oldRect->pen());
            newRect->setBrush(oldRect->brush());
            scene->addItem(newRect);
        }
        if (Ellipse *oldEllipse = dynamic_cast<Ellipse *>(item)) {
            Ellipse *newEllipse = new Ellipse(ui->menuEdit);
            newEllipse->setRect(oldEllipse->rect());
            newEllipse->setX(oldEllipse->x() + 10.0);
            newEllipse->setY(oldEllipse->y() + 10.0);
            newEllipse->setPen(oldEllipse->pen());
            newEllipse->setBrush(oldEllipse->brush());
            scene->addItem(newEllipse);
        }
        if (Polyline *oldPolyline = dynamic_cast<Polyline *>(item)) {
            Polyline *newPolyline = new Polyline(ui->menuEdit);
            newPolyline->setPath(oldPolyline->path());
            newPolyline->setX(oldPolyline->x() + 10.0);
            newPolyline->setY(oldPolyline->y() + 10.0);
            newPolyline->setPen(oldPolyline->pen());
            scene->addItem(newPolyline);
        }
        if (Curve *oldCurve = dynamic_cast<Curve *>(item)) {
            Curve *newCurve = new Curve(ui->menuEdit);
            newCurve->setPath(oldCurve->path());
            newCurve->setX(oldCurve->x() + 10.0);
            newCurve->setY(oldCurve->y() + 10.0);
            newCurve->setPen(oldCurve->pen());
            scene->addItem(newCurve);
        }
        if (QGraphicsLineItem *oldLine = dynamic_cast<QGraphicsLineItem *>(item)) {
            QGraphicsLineItem *newLine = new QGraphicsLineItem();
            newLine->setFlag(QGraphicsItem::ItemIsMovable, true);
            newLine->setLine(oldLine->line());
            newLine->setX(oldLine->x() + 10.0);
            newLine->setY(oldLine->y() + 10.0);
            newLine->setPen(oldLine->pen());
            scene->addItem(newLine);
        }
        if (TextItem *oldText = dynamic_cast<TextItem *>(item)) {
            TextItem *newText = new TextItem(ui->menuEdit);
            newText->setPlainText(oldText->document()->toPlainText());
            newText->setPos(QPointF(oldText->x() + 10, oldText->y() + 10));
            newText->setFont(oldText->font());
            newText->setDefaultTextColor(oldText->defaultTextColor());
            newText->setZValue(oldText->zValue());
            scene->addItem(newText);
        }
        if (TechnicsShape *oldTechnicsShape = dynamic_cast<TechnicsShape *>(item)) {
            TechnicsShape::ShapeType shapeType = oldTechnicsShape->shapeType();
            QTransform shapeTransform = oldTechnicsShape->transform();
            TechnicsShape *newTechnicsShape = new TechnicsShape(ui->menuEdit, shapeType);
            newTechnicsShape->setPos(QPointF(oldTechnicsShape->x() + 10
                                             , oldTechnicsShape->y() + 10));
            newTechnicsShape->setZValue(oldTechnicsShape->zValue());
            newTechnicsShape->setTransform(shapeTransform);
            scene->addItem(newTechnicsShape);
        }
    }
    scene->setSelectableItems(true);
}

void MainWindow::cut()
{
    QList<QGraphicsItem *> cutList;
    copy();
    for (QGraphicsItem *item : qAsConst(copyList)) {
        if (Rectangle *oldRect = dynamic_cast<Rectangle *>(item)) {
            Rectangle *newRect = new Rectangle(ui->menuEdit);
            newRect->setRect(oldRect->rect());
            newRect->setX(oldRect->x() + 10.0);
            newRect->setY(oldRect->y() + 10.0);
            newRect->setPen(oldRect->pen());
            newRect->setBrush(oldRect->brush());
            cutList.append(newRect);
        }
        if (Ellipse *oldEllipse = dynamic_cast<Ellipse *>(item)) {
            Ellipse *newEllipse = new Ellipse(ui->menuEdit);
            newEllipse->setRect(oldEllipse->rect());
            newEllipse->setX(oldEllipse->x() + 10.0);
            newEllipse->setY(oldEllipse->y() + 10.0);
            newEllipse->setPen(oldEllipse->pen());
            newEllipse->setBrush(oldEllipse->brush());
            cutList.append(newEllipse);
        }
        if (Polyline *oldPolyline = dynamic_cast<Polyline *>(item)) {
            Polyline *newPolyline = new Polyline(ui->menuEdit);
            newPolyline->setPath(oldPolyline->path());
            newPolyline->setX(oldPolyline->x() + 10.0);
            newPolyline->setY(oldPolyline->y() + 10.0);
            newPolyline->setPen(oldPolyline->pen());
            cutList.append(newPolyline);
        }
        if (Curve *oldCurve = dynamic_cast<Curve *>(item)) {
            Curve *newCurve = new Curve(ui->menuEdit);
            newCurve->setPath(oldCurve->path());
            newCurve->setX(oldCurve->x() + 10.0);
            newCurve->setY(oldCurve->y() + 10.0);
            newCurve->setPen(oldCurve->pen());
            cutList.append(newCurve);
        }
        if (QGraphicsLineItem *oldLine = dynamic_cast<QGraphicsLineItem *>(item)) {
            QGraphicsLineItem *newLine = new QGraphicsLineItem();
            newLine->setFlag(QGraphicsItem::ItemIsMovable, true);
            newLine->setLine(oldLine->line());
            newLine->setX(oldLine->x() + 10.0);
            newLine->setY(oldLine->y() + 10.0);
            newLine->setPen(oldLine->pen());
            cutList.append(newLine);
        }
        if (TextItem *oldText = dynamic_cast<TextItem *>(item)) {
            TextItem *newText = new TextItem(ui->menuEdit);
            newText->setPlainText(oldText->document()->toPlainText());
            newText->setPos(QPointF(oldText->x() + 10, oldText->y() + 10));
            newText->setFont(oldText->font());
            newText->setDefaultTextColor(oldText->defaultTextColor());
            newText->setZValue(oldText->zValue());
            cutList.append(newText);
        }
        if (TechnicsShape *oldTechnicsShape = dynamic_cast<TechnicsShape *>(item)) {
            TechnicsShape::ShapeType shapeType = oldTechnicsShape->shapeType();
            QTransform shapeTransform = oldTechnicsShape->transform();
            TechnicsShape *newTechnicsShape = new TechnicsShape(ui->menuEdit, shapeType);
            newTechnicsShape->setPos(QPointF(oldTechnicsShape->x() + 10
                                             , oldTechnicsShape->y() + 10));
            newTechnicsShape->setZValue(oldTechnicsShape->zValue());
            newTechnicsShape->setTransform(shapeTransform);
            cutList.append(newTechnicsShape);
        }
    }
    copyList = cutList;
    cutList.clear();
    deleteItem();
}

void MainWindow::openSVG()
{
    if (maybeSave()) {
        QString fileName = QFileDialog::getOpenFileName(this, tr("Open SVG")
                                                        , "", tr("SVG files (*.svg)"));
        if (fileName.isEmpty()) {
            return;
        }

        scene->clear();
        SvgReader *svgReader = new SvgReader(ui->menuEdit);
        scene->setSceneRect(svgReader->getSize(fileName));

        QList<QGraphicsItem *> itemList = svgReader->getElements(fileName);
        for (QGraphicsItem *item : qAsConst(itemList)) {
            if (Rectangle *rectangleItem = dynamic_cast<Rectangle *>(item)) {
                scene->addItem(rectangleItem);
            }
            if (Ellipse *ellipseItem = dynamic_cast<Ellipse *>(item)) {
                scene->addItem(ellipseItem);
            }
            if (Polyline *polylineItem = dynamic_cast<Polyline *>(item)) {
                scene->addItem(polylineItem);
            }
            if (Curve *curveItem = dynamic_cast<Curve *>(item)) {
                scene->addItem(curveItem);
            }
            if (QGraphicsLineItem *lineItem = dynamic_cast<QGraphicsLineItem *>(item)) {
                scene->addItem(lineItem);
            }
            if (TextItem *textItem = dynamic_cast<TextItem *>(item)) {
                scene->addItem(textItem);
            }
            if (PixmapItem *pixmapItem = dynamic_cast<PixmapItem *>(item)) {
                scene->addItem(pixmapItem);
            }
        }
        scene->setSelectableItems(true);
        setCurrentFile(fileName);
        return;
    }
}

bool MainWindow::saveSVG()
{
    QString newPath = QFileDialog::getSaveFileName(this, tr("Save SVG"),
                                                   currentFile, tr("SVG files (*.svg)"));
    if (newPath.isEmpty())
        return false;
    currentFile = newPath;

    QSvgGenerator generator;
    generator.setFileName(currentFile);
    generator.setSize(QSize(scene->width(), scene->height()));
    generator.setViewBox(QRect(0, 0, scene->width(), scene->height()));
    generator.setTitle(tr("SVG RSiSed"));
    generator.setDescription(tr("File created by RSiSed"));

    QPainter painter;
    painter.begin(&generator);
    scene->render(&painter);
    painter.end();

    return true;
}

void MainWindow::insertImage()
{
    imagePath = QFileDialog::getOpenFileName(this, tr("Insert image"), ""
                                             , tr("Images (*.bmp *.gif *.jpg *.jpeg *.png *.pbm *.pgm *.ppm *.xbm *.xpm)"));
    if (imagePath.isEmpty()) {
        return;
    }
    ui->mainGraphicsView->setCursor(Qt::ArrowCursor);
    scene->setMode(DiagramScene::InsertImage);
    scene->setSelectableItems(false);
    scene->insertPixmap(imagePath);
    ui->actionSelect_All->setDisabled(true);
    ui->actionDeleteItem->setDisabled(true);
}

void MainWindow::drawPolyline()
{
    ui->mainGraphicsView->setCursor(Qt::CrossCursor);
    scene->setMode(DiagramScene::InsertPolyline);
    scene->setSelectableItems(false);
    ui->actionSelect_All->setDisabled(true);
    ui->actionDeleteItem->setDisabled(true);
}

void MainWindow::drawRect()
{
    ui->mainGraphicsView->setCursor(Qt::CrossCursor);
    scene->setMode(DiagramScene::InsertRect);
    scene->setSelectableItems(false);
    ui->actionSelect_All->setDisabled(true);
    ui->actionDeleteItem->setDisabled(true);
}

void MainWindow::drawEllipse()
{
    ui->mainGraphicsView->setCursor(Qt::CrossCursor);
    scene->setMode(DiagramScene::InsertEllipse);
    scene->setSelectableItems(false);
    ui->actionSelect_All->setDisabled(true);
    ui->actionDeleteItem->setDisabled(true);
}

void MainWindow::drawCurve()
{
    ui->mainGraphicsView->setCursor(Qt::CrossCursor);
    scene->setMode(DiagramScene::InsertCurve);
    scene->setSelectableItems(false);
    ui->actionSelect_All->setDisabled(true);
    ui->actionDeleteItem->setDisabled(true);
}

void MainWindow::insertText()
{
    ui->mainGraphicsView->setCursor(Qt::IBeamCursor);
    scene->setMode(DiagramScene::InserText);
    scene->setSelectableItems(false);
    ui->actionSelect_All->setDisabled(true);
    ui->actionDeleteItem->setDisabled(true);
}

void MainWindow::insertTechnicsShape(QAbstractButton *button)
{
    const QList<QAbstractButton *> buttons = technicsButtonGroup->buttons();
    for (QAbstractButton *m_button : buttons) {
        if (m_button != button)
            button->setChecked(false);
    }
    const int id = technicsButtonGroup->id(button);
    TechnicsShape::ShapeType type {TechnicsShape::ShapeType(id)};
    TechnicsShape technicsShape(ui->menuEdit, type);
    ui->mainGraphicsView->setCursor(QCursor(technicsShape.image()));
    scene->setMode(DiagramScene::InsertShape);
    scene->setTechnicsShapeType(TechnicsShape::ShapeType(id));
    scene->setSelectableItems(false);
    if (simpleDrawModeActionGr->checkedAction() != nullptr)
        simpleDrawModeActionGr->checkedAction()->setChecked(false);
    ui->actionSelect_All->setDisabled(true);
    ui->actionDeleteItem->setDisabled(true);
}

void MainWindow::selectedItem()
{
    ui->mainGraphicsView->setCursor(Qt::ArrowCursor);
    scene->setMode(DiagramScene::SelectItem);
    scene->setSelectableItems(true);
    ui->actionSelect_All->setEnabled(true);
}

void MainWindow::changedItemPen()
{
    QColor currentPenColor = penColorButton->color();
    qreal currentPenWidth = qvariant_cast<qreal>(penSizeCombo->currentText());
    Qt::PenStyle currentPenStyle = qvariant_cast<Qt::PenStyle>(penStyleCombo->currentData());
    scene->setItemPen(currentPenColor, currentPenWidth, currentPenStyle);
}

void MainWindow::changedItemBrush()
{
    QColor currentBrushColor = brushColorButton->color();
    Qt::BrushStyle currentBrushStyle = qvariant_cast<Qt::BrushStyle>
            (brushStyleCombo->currentData());
    scene->setItemBrush(currentBrushColor, currentBrushStyle);
}

void MainWindow::changedFont()
{
    currentFont = fontCombo->currentFont();
    currentFont.setPointSize(fontSizeCombo->currentText().toInt());
    currentFont.setWeight(boldAction->isChecked() ? QFont::Bold : QFont::Normal);
    currentFont.setItalic(italicAction->isChecked());
    currentFont.setUnderline(underLineAction->isChecked());
    QColor currentTextColor(textColorButton->color());
    scene->setItemFont(currentFont, currentTextColor);
}

void MainWindow::createShapeToolBox()
{
    technicsButtonGroup = new QButtonGroup(this);
    technicsButtonGroup->setExclusive(false);
    connect(technicsButtonGroup, QOverload<QAbstractButton *>::of(&QButtonGroup::buttonClicked),
            this, &MainWindow::insertTechnicsShape);

    QGridLayout *technicsLayout = new QGridLayout;
    technicsLayout->addWidget(createTechnicsCellWidget(tr("Car"), TechnicsShape::Base), 0, 0);
    technicsLayout->addWidget(createTechnicsCellWidget(tr("Tanker"), TechnicsShape::Tanker), 0, 1);
    technicsLayout->setRowStretch(3, 10);
    technicsLayout->setColumnStretch(2, 10);

    QWidget *technicsWidget = new QWidget;
    technicsWidget->setLayout(technicsLayout);

    shapeToolBox = new QToolBox;
    shapeToolBox->setSizePolicy(QSizePolicy(QSizePolicy::Maximum, QSizePolicy::Ignored));
    shapeToolBox->setMinimumWidth(technicsWidget->sizeHint().width());
    shapeToolBox->addItem(technicsWidget, tr("Technics"));
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
    QList<QGraphicsItem *> selectedItems = scene->selectedItems();
    if (selectedItems.isEmpty()) {
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
    sceneScaleMinAction = new QAction(QIcon(":images/icons/zoomminus.png"),
                                      tr("Zoom out"), this);
    sceneScaleMinAction->setShortcut(tr("Ctrl+-"));
    sceneScaleMinAction->setToolTip(tr("Zoom out the scene by 10%"));
    connect(sceneScaleMinAction, &QAction::triggered, this, &MainWindow::sceneZoomInOut);

    sceneScaleMaxAction = new QAction(QIcon(":images/icons/zoomplus.png"),
                                      tr("Zoom in"), this);
    sceneScaleMaxAction->setShortcut(tr("Ctrl++"));
    sceneScaleMaxAction->setToolTip(tr("Zoom in on the scene by 10%"));
    connect(sceneScaleMaxAction, &QAction::triggered, this, &MainWindow::sceneZoomInOut);

    boldAction = new QAction(QIcon(":images/icons/bold_48.png"), tr("Bold"), this);
    boldAction->setCheckable(true);
    boldAction->setShortcut(tr("Ctrl+B"));
    connect(boldAction, &QAction::triggered, this, &MainWindow::changedFont);

    italicAction = new QAction(QIcon(":images/icons/italic_48.png"), tr("Italic"), this);
    italicAction->setCheckable(true);
    italicAction->setShortcut(tr("Ctrl+I"));
    connect(italicAction, &QAction::triggered, this, &MainWindow::changedFont);

    underLineAction = new QAction(QIcon(":images/icons/underline_48.png"), tr("Underline"), this);
    underLineAction->setCheckable(true);
    underLineAction->setShortcut(tr("Ctrl+U"));
    connect(underLineAction, &QAction::triggered, this, &MainWindow::changedFont);
}

void MainWindow::createMenu()
{
    ui->menuView->addAction(sceneScaleMinAction);
    ui->menuView->addAction(sceneScaleMaxAction);
}

void MainWindow::createStyleToolBar()
{
    // Pen style
    penStyleCombo = new QComboBox(this);
    penStyleCombo->addItem(QIcon(":images/icons/nobrush.png"), tr("NoPen"), "Qt::NoPen");
    penStyleCombo->addItem(QIcon(":images/icons/solidline_48.png"), tr("Solid"), "Qt::SolidLine");
    penStyleCombo->addItem(QIcon(":images/icons/dashline_48.png"), tr("Dash"), "Qt::DashLine");
    penStyleCombo->addItem(QIcon(":images/icons/dotline_32.svg"), tr("Dot"), "Qt::DotLine");
    penStyleCombo->addItem(QIcon(":images/icons/dashdotline_32.png"), tr("DashDot"), "Qt::DashDotLine");
    penStyleCombo->addItem(QIcon(":images/icons/dashdotdot.svg"), tr("DashDotDot"), "Qt::DashDotDotLine");
    penStyleCombo->setCurrentIndex(1);
    penStyleCombo->setToolTip(tr("Changing the pen style"));
    connect(penStyleCombo, QOverload<int>::of(&QComboBox::currentIndexChanged),
            this, &MainWindow::changedItemPen);

    // Pen width
    penSizeCombo = new QComboBox(this);
    for (int i = 0; i < 10; ++i) {
        penSizeCombo->insertItem(i, QString().setNum(i), QString(i));
    }
    penSizeCombo->setCurrentIndex(1);
    penSizeCombo->setToolTip(tr("Changing the pen thickness"));
    connect(penSizeCombo, QOverload<int>::of(&QComboBox::currentIndexChanged),
            this, &MainWindow::changedItemPen);

    // Pen color
    QFrame *penColorFrame = new QFrame(this);
    QHBoxLayout *penColorHBoxLayout = new QHBoxLayout;
    penColorFrame->setLayout(penColorHBoxLayout);
    penColorButton = new KColorButton(this);
    penColorButton->setColor(Qt::black);
    penColorButton->setFixedWidth(32);
    penColorButton->setToolTip(tr("Changing the color of the pen"));
    penColorHBoxLayout->addWidget(penColorButton);
    QLabel *penColorLabel = new QLabel(this);
    penColorLabel->setScaledContents(true);
    penColorLabel->setPixmap(QPixmap(":/images/icons/pen_l.png"));
    penColorLabel->setFixedSize(28, 28);
    penColorHBoxLayout->addWidget(penColorLabel);
    connect(penColorButton, &KColorButton::changed, this, &MainWindow::changedItemPen);

    // Brush style
    brushStyleCombo = new QComboBox(this);
    brushStyleCombo->addItem(QIcon(":images/icons/nobrush.png"), tr("No brush"), "Qt::NoBrush");
    brushStyleCombo->addItem(QIcon(":images/icons/solidbrush.png"), tr("Solid"), "Qt::SolidPattern");
    brushStyleCombo->addItem(QIcon(":images/icons/horizontalbrush.png"), tr("Horizontal"), "Qt::HorPattern");
    brushStyleCombo->addItem(QIcon(":images/icons/verticalbrush.png"), tr("Vertical"), "Qt::VerPattern");
    brushStyleCombo->addItem(QIcon(":images/icons/gridbrush.png"), tr("Cross"), "Qt::CrossPattern");
    brushStyleCombo->addItem(QIcon(":images/icons/bdiagbrush.png"), tr("BDiag"), "Qt::BDiagPattern");
    brushStyleCombo->addItem(QIcon(":images/icons/fdiagbrush.png"), tr("FDiag"), "Qt::FDiagPattern");
    brushStyleCombo->addItem(QIcon(":images/icons/diagcrossbrush.png"), tr("DiagCross"), "Qt::DiagCrossPattern");
    brushStyleCombo->addItem(QIcon(":images/icons/dense_1.png"), tr("Dense 1"), "Qt::Dense1Pattern");
    brushStyleCombo->addItem(QIcon(":images/icons/dense_2.png"), tr("Dense 2"), "Qt::Dense2Pattern");
    brushStyleCombo->addItem(QIcon(":images/icons/dense_3.png"), tr("Dense 3"), "Qt::Dense3Pattern");
    brushStyleCombo->addItem(QIcon(":images/icons/dense_4.png"), tr("Dense 4"), "Qt::Dense4Pattern");
    brushStyleCombo->addItem(QIcon(":images/icons/dense_5.png"), tr("Dense 5"), "Qt::Dense5Pattern");
    brushStyleCombo->addItem(QIcon(":images/icons/dense_6.png"), tr("Dense 6"), "Qt::Dense6Pattern");
    brushStyleCombo->addItem(QIcon(":images/icons/dense_7.png"), tr("Dense 7"), "Qt::Dense7Pattern");
    brushStyleCombo->setCurrentIndex(1);
    brushStyleCombo->setToolTip(tr("Changing the fill style"));
    connect(brushStyleCombo, QOverload<int>::of(&QComboBox::currentIndexChanged),
            this, &MainWindow::changedItemBrush);

    // Brush color
    QFrame *brushColorFrame = new QFrame(this);
    QHBoxLayout *brushColorHBoxLayout = new QHBoxLayout(this);
    brushColorFrame->setLayout(brushColorHBoxLayout);
    brushColorButton = new KColorButton(this);
    brushColorButton->setColor(Qt::white);
    brushColorButton->setFixedWidth(32);
    brushColorButton->setToolTip(tr("Changing the fill color"));
    brushColorHBoxLayout->addWidget(brushColorButton);
    QLabel *brushColorLabel = new QLabel(this);
    brushColorLabel->setScaledContents(true);
    brushColorLabel->setPixmap(QPixmap(":/images/icons/brushpaint_32.png"));
    brushColorLabel->setFixedSize(28, 28);
    brushColorHBoxLayout->addWidget(brushColorLabel);
    connect(brushColorButton, &KColorButton::changed, this, &MainWindow::changedItemBrush);

    // Create item style ToolBar
    styleToolBar = addToolBar(tr("Item style"));
    styleToolBar->addWidget(penStyleCombo);
    styleToolBar->addWidget(penSizeCombo);
    styleToolBar->addWidget(penColorFrame);
    styleToolBar->addSeparator();
    styleToolBar->addWidget(brushStyleCombo);
    styleToolBar->addWidget(brushColorFrame);
}

void MainWindow::createFontStyleToolBar()
{
    fontCombo = new QFontComboBox();
    fontCombo->setWritingSystem(QFontDatabase::Cyrillic);
    fontCombo->setToolTip(tr("Change the font of the text"));
    connect(fontCombo, &QFontComboBox::currentFontChanged, this, &MainWindow::changedFont);

    fontSizeCombo = new QComboBox;
    fontSizeCombo->setEditable(true);
    for (int i = 8; i < 30; i = i + 2)
        fontSizeCombo->addItem(QString().setNum(i));
    QIntValidator *validator = new QIntValidator(2, 64, this);
    fontSizeCombo->setValidator(validator);
    fontSizeCombo->setCurrentIndex(2);
    fontCombo->setToolTip(tr("Change the font size of the text"));
    connect(fontSizeCombo, &QComboBox::currentTextChanged, this, &MainWindow::changedFont);

    textColorButton = new KColorButton(this);
    textColorButton->setColor(Qt::black);
    textColorButton->setFixedWidth(32);
    textColorButton->setToolTip(tr("Changing the color of the text"));
    connect(textColorButton, &KColorButton::changed, this, &MainWindow::changedFont);

    textStyleToolBar = addToolBar(tr("Font style")) ;
    textStyleToolBar->addWidget(fontCombo);
    textStyleToolBar->addWidget(fontSizeCombo);
    textStyleToolBar->addAction(boldAction);
    textStyleToolBar->addAction(italicAction);
    textStyleToolBar->addAction(underLineAction);
    textStyleToolBar->addWidget(textColorButton);
}

void MainWindow::createSimpleDrawToolBar()
{
    simpleDrawModeActionGr = new QActionGroup(this);
    simpleDrawModeActionGr->addAction(ui->actionSelectedItem);
    simpleDrawModeActionGr->addAction(ui->actionDrawPolyline);
    simpleDrawModeActionGr->addAction(ui->actionDrawCurve);
    simpleDrawModeActionGr->addAction(ui->actionDrawRectangle);
    simpleDrawModeActionGr->addAction(ui->actionDrawEllipse);
    simpleDrawModeActionGr->addAction(ui->actionInsertText);
    simpleDrawModeActionGr->addAction(ui->actionInsertImage);
    simpleDrawModeActionGr->setExclusive(true);
}

void MainWindow::createSceneScaleToolBar()
{
    sceneScaleCombo = new QComboBox(this);
    QStringList scales;
    scales << tr("25%") << tr("50%") << tr("75%") << tr("100%") << tr("125%")
           << tr("150%") << tr("200%") << tr("300%") << tr("500%");
    sceneScaleCombo->addItems(scales);
    sceneScaleCombo->setCurrentIndex(3);
    sceneScaleCombo->setEditable(true);
    sceneScaleCombo->setToolTip("Changing the scene scale");
    connect(sceneScaleCombo, &QComboBox::currentTextChanged,
            this, &MainWindow::sceneScaleChanged);

    sceneScaleToolBar = addToolBar(tr("Scene scale"));
    sceneScaleToolBar->addAction(sceneScaleMinAction);
    sceneScaleToolBar->addAction(sceneScaleMaxAction);
    sceneScaleToolBar->addWidget(sceneScaleCombo);
}

QWidget *MainWindow::createTechnicsCellWidget(const QString &text, TechnicsShape::ShapeType type)
{
    TechnicsShape shapeItem(ui->menuEdit, type);
    QIcon icon(shapeItem.image());

    QToolButton *technicsButton = new QToolButton;
    technicsButton->setIcon(icon);
    technicsButton->setIconSize(QSize(18, 38));
    technicsButton->setCheckable(true);
    technicsButtonGroup->addButton(technicsButton, int(type));

    QGridLayout *technicsShapeLayout = new QGridLayout;
    technicsShapeLayout->addWidget(technicsButton, 0, 0, Qt::AlignHCenter);
    technicsShapeLayout->addWidget(new QLabel(text), 1, 0, Qt::AlignCenter);

    QWidget *technicsShapeWidget = new QWidget;
    technicsShapeWidget->setLayout(technicsShapeLayout);

    return technicsShapeWidget;
}

bool MainWindow::maybeSave()
{
    if (!scene->isChanged()) {
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
        QList<QGraphicsItem *> itemsList = scene->items();
        QRectF sceneRect = scene->sceneRect();
        RseWriter *writer = new RseWriter();
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

    ui->statusBar->showMessage(tr("File saved"), 2000);
    setCurrentFile(fileName);

    return true;
}

void MainWindow::setCurrentFile(const QString &fileName)
{
    currentFile = fileName;
    QString showName = currentFile;
    if (currentFile.isEmpty()) {
        showName = "untitled.rse";
    }
    setWindowTitle(showName + " - RSiSed");
    setWindowModified(false); // NOTE для Setting
    scene->setSceneChanged(false);
}

void MainWindow::deleteItem()
{
    QList<QGraphicsItem *> selectedItems = scene->selectedItems();
    for (QGraphicsItem *item : qAsConst(selectedItems)) {
        scene->removeItem(item);
        delete item;
    }
}

void MainWindow::selectAll()
{
    QList<QGraphicsItem *> items = scene->items();
    for (QGraphicsItem *item : qAsConst(items)) {
        item->setSelected(true);
    }
}

void MainWindow::sceneZoomInOut()
{
    double oldScale = sceneScaleCombo->currentText().leftRef
            (sceneScaleCombo->currentText().indexOf(tr("%"))).toDouble();
    if (sender() == sceneScaleMinAction) {
        oldScale = oldScale - 10;
    } else if (sender() == sceneScaleMaxAction) {
        oldScale = oldScale + 10;
    }
    QString newScale = QString().setNum(oldScale) + tr("%");
    sceneScaleCombo->setCurrentText(newScale);
    sceneScaleChanged(newScale);
}

void MainWindow::sceneScaleChanged(const QString &scale)
{
    double newScale = scale.leftRef(scale.indexOf(tr("%"))).toDouble() / 100.0;
    QTransform oldMatrix = ui->mainGraphicsView->transform();
    ui->mainGraphicsView->resetTransform();
    ui->mainGraphicsView->translate(oldMatrix.dx(), oldMatrix.dy());
    ui->mainGraphicsView->scale(newScale, newScale);
}
