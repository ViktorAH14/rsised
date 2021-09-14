#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QtWidgets>
#include <QSvgGenerator>
#include <KColorButton>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);

// Create toolbars
    createSimpleDrawToolBar();
    createStyleToolBar();

// Create scene and view
    scene = new DiagramScene(this);
    scene->setSceneRect(0, 0, 1920, 1080);
    scene->setMode(DiagramScene::MoveItem);
    scene->setItemPen(penColorButton->color(),
                      qvariant_cast<qreal>(penSizeCombobox->currentText()),
                      qvariant_cast<Qt::PenStyle>(penStyleComboBox->currentData()));
    scene->setItemBrush(brushColorButton->color(),
                        qvariant_cast<Qt::BrushStyle>(brushStyleComboBox->currentData()));
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
    qreal currentPenWidth = qvariant_cast<qreal>(penSizeCombobox->currentText());
    Qt::PenStyle currentPenStyle = qvariant_cast<Qt::PenStyle>(penStyleComboBox->currentData());
    scene->setItemPen(currentPenColor, currentPenWidth, currentPenStyle);
}

void MainWindow::changedItemBrush()
{
    QColor currentBrushColor = brushColorButton->color();
    Qt::BrushStyle currentBrushStyle = qvariant_cast<Qt::BrushStyle>(brushStyleComboBox->currentData());
    scene->setItemBrush(currentBrushColor, currentBrushStyle);
}

void MainWindow::createStyleToolBar()
{
    // Pen style
    penStyleComboBox = new QComboBox(this);
    penStyleComboBox->addItem(QIcon(":images/icons/nobrush.png"), tr("NoPen"), "Qt::NoPen");
    penStyleComboBox->addItem(QIcon(":images/icons/solidline_48.png"), tr("Solid"), "Qt::SolidLine");
    penStyleComboBox->addItem(QIcon(":images/icons/dashline_48.png"), tr("Dash"), "Qt::DashLine");
    penStyleComboBox->addItem(QIcon(":images/icons/dotline_32.svg"), tr("Dot"), "Qt::DotLine");
    penStyleComboBox->addItem(QIcon(":images/icons/dashdotline_32.png"), tr("DashDot"), "Qt::DashDotLine");
    penStyleComboBox->addItem(QIcon(":images/icons/dashdotdot.svg"), tr("DashDotDot"), "Qt::DashDotDotLine");
    penStyleComboBox->setCurrentIndex(1);
    connect(penStyleComboBox, QOverload<int>::of(&QComboBox::currentIndexChanged),
            this, &MainWindow::changedItemPen);

    // Pen width
    penSizeCombobox = new QComboBox(this);
    for (int i = 0; i < 10; ++i) {
        penSizeCombobox->insertItem(i, QString().setNum(i), QString(i));
    }
    penSizeCombobox->setCurrentIndex(1);
    connect(penSizeCombobox, QOverload<int>::of(&QComboBox::currentIndexChanged),
            this, &MainWindow::changedItemPen);

    // Pen color
    QFrame *penColorFrame = new QFrame(this);
    QHBoxLayout *penColorHBoxLayout = new QHBoxLayout(this);
    penColorFrame->setLayout(penColorHBoxLayout);
    penColorButton = new KColorButton(this);
    penColorButton->setColor(Qt::black);
    penColorButton->setFixedWidth(32);
//    penColorButton->setFixedHeight(28);
    penColorHBoxLayout->addWidget(penColorButton);
//    penColorHBoxLayout->setAlignment(penColorButton, Qt::AlignBottom);
    QLabel *penColorLabel = new QLabel(this);
    penColorLabel->setScaledContents(true);
    penColorLabel->setPixmap(QPixmap(":/images/icons/pen_l.png"));
    penColorLabel->setFixedSize(28, 28);
    penColorHBoxLayout->addWidget(penColorLabel);
    connect(penColorButton, &KColorButton::changed, this, &MainWindow::changedItemPen);

    // Brush style
    brushStyleComboBox = new QComboBox(this);
    brushStyleComboBox->addItem(QIcon(":images/icons/nobrush.png"), tr("No brush"), "Qt::NoBrush");
    brushStyleComboBox->addItem(QIcon(":images/icons/solidbrush.png"), tr("Solid"), "Qt::SolidPattern");
    brushStyleComboBox->addItem(QIcon(":images/icons/horizontalbrush.png"), tr("Horizontal"), "Qt::HorPattern");
    brushStyleComboBox->addItem(QIcon(":images/icons/verticalbrush.png"), tr("Vertical"), "Qt::VerPattern");
    brushStyleComboBox->addItem(QIcon(":images/icons/gridbrush.png"), tr("Cross"), "Qt::CrossPattern");
    brushStyleComboBox->addItem(QIcon(":images/icons/bdiagbrush.png"), tr("BDiag"), "Qt::BDiagPattern");
    brushStyleComboBox->addItem(QIcon(":images/icons/fdiagbrush.png"), tr("FDiag"), "Qt::FDiagPattern");
    brushStyleComboBox->addItem(QIcon(":images/icons/diagcrossbrush.png"), tr("DiagCross"), "Qt::DiagCrossPattern");
    brushStyleComboBox->addItem(QIcon(":images/icons/dense_1.png"), tr("Dense 1"), "Qt::Dense1Pattern");
    brushStyleComboBox->addItem(QIcon(":images/icons/dense_2.png"), tr("Dense 2"), "Qt::Dense2Pattern");
    brushStyleComboBox->addItem(QIcon(":images/icons/dense_3.png"), tr("Dense 3"), "Qt::Dense3Pattern");
    brushStyleComboBox->addItem(QIcon(":images/icons/dense_4.png"), tr("Dense 4"), "Qt::Dense4Pattern");
    brushStyleComboBox->addItem(QIcon(":images/icons/dense_5.png"), tr("Dense 5"), "Qt::Dense5Pattern");
    brushStyleComboBox->addItem(QIcon(":images/icons/dense_6.png"), tr("Dense 6"), "Qt::Dense6Pattern");
    brushStyleComboBox->addItem(QIcon(":images/icons/dense_7.png"), tr("Dense 7"), "Qt::Dense7Pattern");
    brushStyleComboBox->setCurrentIndex(1);
    connect(brushStyleComboBox, QOverload<int>::of(&QComboBox::currentIndexChanged),
            this, &MainWindow::changedItemBrush);

    // Brush color
    QFrame *brushColorFrame = new QFrame(this);
    QHBoxLayout *brushColorHBoxLayout = new QHBoxLayout(this);
    brushColorFrame->setLayout(brushColorHBoxLayout);
    brushColorButton = new KColorButton(this);
    brushColorButton->setColor(Qt::white);
    brushColorButton->setFixedWidth(32);
    brushColorHBoxLayout->addWidget(brushColorButton);
    QLabel *brushColorLabel = new QLabel(this);
    brushColorLabel->setScaledContents(true);
    brushColorLabel->setPixmap(QPixmap(":/images/icons/brushpaint_32.png"));
    brushColorLabel->setFixedSize(28, 28);
    brushColorHBoxLayout->addWidget(brushColorLabel);
    connect(brushColorButton, &KColorButton::changed, this, &MainWindow::changedItemBrush);

    // Create item style ToolBar
    styleToolBar = addToolBar(tr("Item style"));
    styleToolBar->addWidget(penStyleComboBox);
    styleToolBar->addWidget(penSizeCombobox);
    styleToolBar->addWidget(penColorFrame);
    styleToolBar->addSeparator();
    styleToolBar->addWidget(brushStyleComboBox);
    styleToolBar->addWidget(brushColorFrame);
}

void MainWindow::createSimpleDrawToolBar()
{
    simpleDrawModeGroup = new QActionGroup(this);
    simpleDrawModeGroup->addAction(ui->actionDrawLine);
    simpleDrawModeGroup->addAction(ui->actionMoveItem);
    simpleDrawModeGroup->addAction(ui->actionDrawRectangle);
    simpleDrawModeGroup->addAction(ui->actionDrawEllipse);
    simpleDrawModeGroup->addAction(ui->actionDrawCurve);
    simpleDrawModeGroup->setExclusive(true);
}

void MainWindow::deleteItem()
{
    QList<QGraphicsItem *> selectedItems = scene->selectedItems();
    for (QGraphicsItem *item:qAsConst(selectedItems)) {
        scene->removeItem(item);
        delete item;
    }
}
