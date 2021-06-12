#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "diagramscene.h"

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    bool save();

private:
    Ui::MainWindow *ui;
    DiagramScene *scene;

    QString path;
};
#endif // MAINWINDOW_H
