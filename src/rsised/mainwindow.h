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

    void loadFile(const QString &fileName);

protected:
    void closeEvent(QCloseEvent *event) override;


private slots:
    void newFile();
    void open();
    bool save();
    bool saveAs();
    void copy();
    void paste();
    void cut();
    void enableAction();
    void openSVG();
    bool saveSVG();
    void deleteItem();
    void selectAll();
    void sceneZoomInOut();
    void sceneScaleChanged(const QString &scale);

// Simple draw
    void drawPolyline();
    void drawRect();
    void drawEllipse();
    void drawCurve();
    void selectedItem();

// Style toolbar
    void changedItemPen();
    void changedItemBrush();

private:
    void disableAction();
    void createActions();
    void createMenu();
    void createStyleToolBar();
    void createSimpleDrawToolBar();
    void createSceneScaleToolBar();

    bool maybeSave();
    bool saveFile(const QString &fileName);
    void setCurrentFile(const QString &fileName);

    Ui::MainWindow *ui;
    DiagramScene *scene;

    QString currentFile;
    QList<QGraphicsItem *> copyList;

    QToolBar *styleToolBar;
    QToolBar *sceneScaleToolBar;

    QAction *sceneScaleMinAction;
    QAction *sceneScaleMaxAction;
    QActionGroup *simpleDrawModeActionGr;

    QComboBox *penStyleCombo;
    QComboBox *penSizeCombo;
    QComboBox *brushStyleCombo;
    QComboBox *sceneScaleCombo;

    KColorButton *penColorButton;
    KColorButton *brushColorButton;
};
#endif // MAINWINDOW_H
