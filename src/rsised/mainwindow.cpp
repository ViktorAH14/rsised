#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QtWidgets>
#include <QSvgGenerator>
#include <KColorButton>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    createActions();
    createMenu();

// Create toolbars
    createSimpleDrawToolBar();
    createStyleToolBar();
    createSceneScaleToolBar();

// Create scene and view
    scene = new DiagramScene(this);
    scene->setSceneRect(0, 0, 1920, 1080);
    scene->setMode(DiagramScene::MoveItem);
    scene->setItemPen(penColorButton->color(),
                      qvariant_cast<qreal>(penSizeCombo->currentText()),
                      qvariant_cast<Qt::PenStyle>(penStyleCombo->currentData()));
    scene->setItemBrush(brushColorButton->color(),
                        qvariant_cast<Qt::BrushStyle>(brushStyleCombo->currentData()));
    ui->mainGraphicsView->setScene(scene);
    ui->mainGraphicsView->setRenderHints(QPainter::Antialiasing);
}

MainWindow::~MainWindow()
{
    delete ui;
}

bool MainWindow::save()
{
    QString newPath = QFileDialog::getSaveFileName(this, tr("Save SVG"),
                                                   filePath, tr("SVG files (*.svg)"));
    if (newPath.isEmpty())
        return false;
    filePath = newPath;

    QSvgGenerator generator;
    generator.setFileName(filePath);
    generator.setSize(QSize(scene->width(), scene->height()));
    generator.setViewBox(QRect(0, 0, scene->width(), scene->height()));
    generator.setTitle(tr("SVG diagramscene"));
    generator.setDescription(tr("File created by SVG diagramscene"));

    QPainter painter;
    painter.begin(&generator);
    scene->render(&painter);
    painter.end();

    return true;
}
void MainWindow::drawLine()
{
    ui->mainGraphicsView->setCursor(Qt::CrossCursor);
    scene->setMode(DiagramScene::InsertLine);
    scene->setSelectableItems(false);
}

void MainWindow::drawRect()
{
    ui->mainGraphicsView->setCursor(Qt::CrossCursor);
    scene->setMode(DiagramScene::InsertRect);
    scene->setSelectableItems(false);
}

void MainWindow::drawEllipse()
{
    ui->mainGraphicsView->setCursor(Qt::CrossCursor);
    scene->setMode(DiagramScene::InsertEllipse);
    scene->setSelectableItems(false);
}

void MainWindow::drawCurve()
{
    ui->mainGraphicsView->setCursor(Qt::CrossCursor);
    scene->setMode(DiagramScene::InsertCurve);
    scene->setSelectableItems(false);
}

void MainWindow::moveItem()
{
    ui->mainGraphicsView->setCursor(Qt::ArrowCursor);
    scene->setMode(DiagramScene::MoveItem);
    scene->setSelectableItems(true);
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

void MainWindow::createSimpleDrawToolBar()
{
    simpleDrawModeActionGr = new QActionGroup(this);
    simpleDrawModeActionGr->addAction(ui->actionDrawLine);
    simpleDrawModeActionGr->addAction(ui->actionMoveItem);
    simpleDrawModeActionGr->addAction(ui->actionDrawRectangle);
    simpleDrawModeActionGr->addAction(ui->actionDrawEllipse);
    simpleDrawModeActionGr->addAction(ui->actionDrawCurve);
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

void MainWindow::deleteItem()
{
    QList<QGraphicsItem *> selectedItems = scene->selectedItems();
    for (QGraphicsItem *item:qAsConst(selectedItems)) {
        scene->removeItem(item);
        delete item;
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
