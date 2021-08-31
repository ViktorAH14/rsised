#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QtWidgets>
#include <QSvgGenerator>

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

    scene = new DiagramScene(this);
    scene->setSceneRect(0, 0, 1920, 1080);
    scene->setMode(DiagramScene::MoveItem);
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
