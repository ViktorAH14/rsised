/*
 * Copyright (c) 2022 by Viktor Ermolov <ermolovva@gmail.com>.
 *
 * This file is part of the RSiSed project, a editor of the alignment of forces
 * and means in extinguishing a fire. (RSiSed)
 *
 * RSiSed is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * RSiSed is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <https://www.gnu.org/licenses/>.
 */

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "diagramscene.h"
#include "../include/technicsshape.h"
#include "../include/buildingstruct.h"
#include "../include/deviceshape.h"

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
    void print();
    void insertImage();
    void deleteItem();
    void selectAll();
    void sceneZoomInOut();
    void sceneScaleChanged(const QString &scale);
    void selectedItem();
    void bringToFront();
    void sendToBack();
    void about();
    void aboutQt();

// Simple draw
    void drawPolyline();
    void drawRect();
    void drawEllipse();
    void drawCurve();
    void insertText();

// Shapes
    void insertTechnicsShape(QAbstractButton *button);
    void insertDeviceShape(QAbstractButton *button);
    void insertBuildingStructShape(QAbstractButton *button);

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
    QWidget *createBuildingStructCellWidget(const QString &text, BuildingStruct::ShapeType type);

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
    QButtonGroup *buildingStructButtonGroup;
};
#endif // MAINWINDOW_H
