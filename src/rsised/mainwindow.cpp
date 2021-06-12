#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QPainter>
#include <QFileDialog>
#include <QSvgGenerator>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    scene = new DiagramScene(this);
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

