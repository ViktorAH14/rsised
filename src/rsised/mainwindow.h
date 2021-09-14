#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "diagramscene.h"

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
class QActionGroup;
class QLabel;
class QComboBox;
class KColorButton;
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    bool save();
    void deleteItem();

// Simple draw
    void drawLine();
    void drawRect();
    void drawEllipse();
    void drawCurve();
    void moveItem();

// Style toolbar
    void changedItemPen();
    void changedItemBrush();

private:
    void createStyleToolBar();
    void createSimpleDrawToolBar();

    Ui::MainWindow *ui;
    QToolBar *styleToolBar;
    DiagramScene *scene;
    QActionGroup *simpleDrawModeGroup;
    QComboBox *penStyleComboBox;
    QComboBox *penSizeCombobox;
    KColorButton *penColorButton;
    QComboBox *brushStyleComboBox;
    KColorButton *brushColorButton;

    QString filePath;
};
#endif // MAINWINDOW_H
