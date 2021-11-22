#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "diagramscene.h"
#include "technics_shape.h"

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
class QActionGroup;
class QLabel;
class QComboBox;
class QFontComboBox;
class QToolBox;
class QButtonGroup;
class QAbstractButton;
class KColorButton;
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

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
    void insertImage();
    void deleteItem();
    void selectAll();
    void sceneZoomInOut();
    void sceneScaleChanged(const QString &scale);
    void selectedItem();

// Simple draw
    void drawPolyline();
    void drawRect();
    void drawEllipse();
    void drawCurve();
    void insertText();

// Shapes
    void insertTechnicsShape(QAbstractButton *button);
    void insertDeviceShape(QAbstractButton *button);

// Style toolbar
    void changedItemPen();
    void changedItemBrush();

// Font style toolbar
    void changedFont();

private:
    void createShapeToolBox();
    void disableAction();
    void createActions();
    void createMenu();
    void createStyleToolBar();
    void createFontStyleToolBar();
    void createSimpleDrawToolBar();
    void createSceneScaleToolBar();
    QWidget *createTechnicsCellWidget(const QString &text, TechnicsShape::ShapeType type);
    QWidget *createDeviceCellWidget(const QString &text, DeviceShape::ShapeType type);

    void loadFile(const QString &fileName);
    bool maybeSave();
    bool saveFile(const QString &fileName);
    void setCurrentFile(const QString &fileName);

    Ui::MainWindow *ui;
    DiagramScene *scene;

    QString currentFile;
    QString imagePath;
    QList<QGraphicsItem *> copyList;

    QToolBar *styleToolBar;
    QToolBar *textStyleToolBar;
    QToolBar *sceneScaleToolBar;

    QAction *boldAction;
    QAction *italicAction;
    QAction *underLineAction;
    QAction *sceneScaleMinAction;
    QAction *sceneScaleMaxAction;
    QActionGroup *simpleDrawModeActionGr;

    QComboBox *penStyleCombo;
    QComboBox *penSizeCombo;
    QComboBox *brushStyleCombo;
    QFont currentFont;
    QFontComboBox *fontCombo;
    QComboBox *fontSizeCombo;
    QComboBox *sceneScaleCombo;

    KColorButton *penColorButton;
    KColorButton *brushColorButton;
    KColorButton *textColorButton;

    QToolBox *shapeToolBox;
    QButtonGroup *technicsButtonGroup;
    QButtonGroup *deviceButtonGroup;
};
#endif // MAINWINDOW_H
