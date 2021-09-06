#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QtWidgets>
#include <QSvgGenerator>
#include <KColorCombo>
#include <KColorButton>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    modeGroup = new QActionGroup(this);
    modeGroup->addAction(ui->actionDrawLine);
    modeGroup->addAction(ui->actionMoveItem);
    modeGroup->addAction(ui->actionDrawRectangle);
    modeGroup->addAction(ui->actionDrawEllipse);
    modeGroup->addAction(ui->actionDrawCurve);
    modeGroup->setExclusive(true);

    QFrame *colorPenFrame = new QFrame(this);
    QHBoxLayout *colorPenHBoxLayout = new QHBoxLayout(this);
    colorPenFrame->setLayout(colorPenHBoxLayout);
    KColorButton *colorItemPenButton = new KColorButton(this);
    colorItemPenButton->setColor(Qt::black);
    colorItemPenButton->setFixedWidth(28);
    colorItemPenButton->setFixedHeight(17);
    colorPenHBoxLayout->addWidget(colorItemPenButton);
    colorPenHBoxLayout->setAlignment(colorItemPenButton, Qt::AlignBottom);
    QLabel *colorPenLabel = new QLabel(this);
    colorPenLabel->setScaledContents(true);
    colorPenLabel->setPixmap(QPixmap(":/images/icons/pen_l.png"));
    colorPenLabel->setFixedHeight(28);
    colorPenLabel->setFixedWidth(28);
    colorPenHBoxLayout->addWidget(colorPenLabel);
    ui->styleToolBar->addWidget(colorPenFrame);

    scene = new DiagramScene(this);
    scene->setSceneRect(0, 0, 1920, 1080);
    scene->setMode(DiagramScene::MoveItem);
    ui->mainGraphicsView->setScene(scene);
    ui->mainGraphicsView->setRenderHints(QPainter::Antialiasing);

    connect(colorItemPenButton, &KColorButton::changed, scene, &DiagramScene::setPenColor);
}

MainWindow::~MainWindow()
{
    delete ui;
}

bool MainWindow::save()
{
    QString newPath = QFileDialog::getSaveFileName(this, tr("Save SVG"),
                                                   path, tr("SVG files (*.svg)"));
    if (newPath.isEmpty())
        return false;
    path = newPath;

    QSvgGenerator generator;
    generator.setFileName(path);
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

void MainWindow::deleteItem()
{
    QList<QGraphicsItem *> selectedItems = scene->selectedItems();
    for (QGraphicsItem *item:qAsConst(selectedItems)) {
        scene->removeItem(item);
        delete item;
    }
}
