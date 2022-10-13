#ifndef WALLSETTING_H
#define WALLSETTING_H

#include <QDialog>

class QComboBox;

namespace Ui {
class WallSetting;
}

class WallSetting : public QDialog
{
    Q_OBJECT

public:
    explicit WallSetting(QWidget *parent = nullptr);
    ~WallSetting();

    int penWidth();
    QColor penColor();
    QColor hatchingColor();
    Qt::BrushStyle hatchingStyle();
    qreal wallHeight();

private slots:
    void changePen();
    void changeHatching();
    void changeWallWidth();

private:
    Ui::WallSetting *ui;

    void createPenWidthCombo();
    void createPenColorCombo();
    void createColorHatchingCombo();
    void createHatchigStyleCombo();
    void createWallHeightCombo();
    void createUi();

    QComboBox   *m_penWidthCombo;
    QComboBox   *m_penColorCombo;
    QComboBox   *m_colorHatchingCombo;
    QComboBox   *m_hatchingStyleCombo;
    QComboBox   *m_wallHeightCombo;

    int m_penWidth;
    QColor  m_penColor;
    QColor  m_hatchingColor;
    Qt::BrushStyle  m_hatchingStyle;
    qreal   m_wallHeight;
};

#endif // WALLSETTING_H
