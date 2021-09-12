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
    scene->setItemPen(penColorButton->color(), 1,
                      qvariant_cast<Qt::PenStyle>(penStyleComboBox->currentData()));
    ui->mainGraphicsView->setScene(scene);
    ui->mainGraphicsView->setRenderHints(QPainter::Antialiasing);

    connect(penColorButton, &KColorButton::changed, this, &MainWindow::changedItemPen);
    connect(penStyleComboBox, QOverload<int>::of(&QComboBox::currentIndexChanged),
            this, &MainWindow::changedItemPen);
    connect(penSizeCombobox, QOverload<int>::of(&QComboBox::currentIndexChanged),
            this, &MainWindow::changedItemPen);
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

void MainWindow::createStyleToolBar()
{
    // Pen style
    penStyleComboBox = new QComboBox(this);
    penStyleComboBox->addItem(QIcon(":images/icons/nopen.svg"), tr("NoPen"), "Qt::NoPen");
    penStyleComboBox->addItem(QIcon(":images/icons/solidline_48.png"), tr("Solid"), "Qt::SolidLine");
    penStyleComboBox->addItem(QIcon(":images/icons/dashline_48.png"), tr("Dash"), "Qt::DashLine");
    penStyleComboBox->addItem(QIcon(":images/icons/dotline_32.svg"), tr("Dot"), "Qt::DotLine");
    penStyleComboBox->addItem(QIcon(":images/icons/dashdotline_32.png"), tr("DashDot"), "Qt::DashDotLine");
    penStyleComboBox->addItem(QIcon(":images/icons/dashdotdot.svg"), tr("DashDotDot"), "Qt::DashDotDotLine");
    penStyleComboBox->setCurrentIndex(1);
    ui->styleToolBar->addWidget(penStyleComboBox);

    // Pen width
    penSizeCombobox = new QComboBox(this);
    for (int i = 0; i < 10; ++i) {
        penSizeCombobox->insertItem(i, QString().setNum(i), QString(i));
    }
    penSizeCombobox->setCurrentIndex(1);
    ui->styleToolBar->addWidget(penSizeCombobox);

    // Pen color
    QFrame *penColorFrame = new QFrame(this);
    QHBoxLayout *penColorHBoxLayout = new QHBoxLayout(this);
    penColorFrame->setLayout(penColorHBoxLayout);
    penColorButton = new KColorButton(this);
    penColorButton->setColor(Qt::black);
    penColorButton->setFixedWidth(32);
//    penColorButton->setFixedHeight(28);
    penColorHBoxLayout->addWidget(penColorButton);
    penColorHBoxLayout->setAlignment(penColorButton, Qt::AlignBottom);
    QLabel *penColorLabel = new QLabel(this);
    penColorLabel->setScaledContents(true);
    penColorLabel->setPixmap(QPixmap(":/images/icons/pen_l.png"));
    penColorLabel->setFixedHeight(28);
    penColorLabel->setFixedWidth(28);
    penColorHBoxLayout->addWidget(penColorLabel);
    ui->styleToolBar->addWidget(penColorFrame);

    ui->styleToolBar->addSeparator();
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
