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
#include "../include/buildingshape.h"
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
    explicit MainWindow(QWidget *parent = nullptr);
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
    void deleteShape();
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
    void drawPie();
    void drawCurve();
    void insertText();

// Shapes
    void insertTechnicsShape(QAbstractButton *button);
    void insertDeviceShape(QAbstractButton *button);
    void insertBuildingShape(QAbstractButton *button);

// Style toolbar
    void changedItemPen();
    void changedItemBrush();

// Font style toolbar
    void changedFont();

// Door setting
    void changeDoorState();
    void changeDoorLeafPosition();

// Wall setting
    bool showWallSettingDialog();

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
    QWidget *createBuildingShapeCellWidget(const QString &text, BuildingShape::ShapeType type);

    void loadFile(const QString &fileName);
    bool maybeSave();
    bool saveFile(const QString &fileName);
    void setCurrentFile(const QString &fileName);

    Ui::MainWindow *ui;
    DiagramScene *m_scene;
    QMenu *m_contextMenu;

    QString m_currentFile;
    QString m_imagePath;
    QList<QGraphicsItem *> m_copyList;

    QToolBar *m_styleToolBar;
    QToolBar *m_textStyleToolBar;
    QToolBar *m_sceneScaleToolBar;

    QAction *m_doorLeafPosAction;
    QAction *m_doorOpenAction;
    QAction *m_doorAjarAction;
    QAction *m_doorCloseAction;
    QActionGroup    *m_doorStateActionGroup;

    QAction *m_boldAction;
    QAction *m_italicAction;
    QAction *m_underLineAction;

    QAction *m_sceneScaleMinAction;
    QAction *m_sceneScaleMaxAction;
    QActionGroup *m_simpleDrawModeActionGr;

    QComboBox *m_penStyleCombo;
    QComboBox *m_penSizeCombo;
    QComboBox *m_brushStyleCombo;
    QFont m_currentFont;
    QFontComboBox *m_fontCombo;
    QComboBox *m_fontSizeCombo;
    QComboBox *m_sceneScaleCombo;

    KColorButton *m_penColorButton;
    KColorButton *m_brushColorButton;
    KColorButton *m_textColorButton;

    QToolBox *m_shapeToolBox;
    QButtonGroup *m_technicsButtonGroup;
    QButtonGroup *m_deviceButtonGroup;
    QButtonGroup *m_buildingShapeButtonGroup;
};
#endif // MAINWINDOW_H
