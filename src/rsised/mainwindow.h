#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "diagramscene.h"

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
class QActionGroup;
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    bool save();
    //Simple draw
    void drawLine();
    void drawRect();
    void drawEllipse();
    void drawCurve();
    void moveItem();

    void deleteItem();

private:
    Ui::MainWindow *ui;
    DiagramScene *scene;
    QActionGroup *modeGroup;

    QString path;
};
#endif // MAINWINDOW_H
