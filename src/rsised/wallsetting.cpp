#include "wallsetting.h"
#include "ui_wallsetting.h"

#include <QComboBox>
#include <QHBoxLayout>
#include <QPen>
#include <QBrush>

WallSetting::WallSetting(const QPen &wallPen, const QBrush &wallBrush, const qreal &wallHeight
                         , QWidget *parent) :
    QDialog(parent)
  , ui(new Ui::WallSetting)
  , m_penWidth{wallPen.width()}
  , m_penColor{wallPen.color()}
  , m_hatchingColor{wallBrush.color()}
  , m_hatchingStyle{wallBrush.style()}
  , m_wallHeight{wallHeight}
{
    ui->setupUi(this);
    createUi();
}

WallSetting::~WallSetting()
{
    delete ui;
}

int WallSetting::penWidth()
{
    return m_penWidth;
}

QColor WallSetting::penColor()
{
    return m_penColor;
}

QColor WallSetting::hatchingColor()
{
    return m_hatchingColor;
}

Qt::BrushStyle WallSetting::hatchingStyle()
{
    return m_hatchingStyle;
}

qreal WallSetting::wallHeight()
{
    return m_wallHeight;
}

void WallSetting::changePen()
{
    m_penWidth = qvariant_cast<int>(m_penWidthCombo->currentText());
    m_penColor.setNamedColor(qvariant_cast<QString>(m_penColorCombo->currentData()));
}

void WallSetting::changeHatching()
{
    m_hatchingColor.setNamedColor(qvariant_cast<QString>(m_colorHatchingCombo->currentData()));
    m_hatchingStyle = qvariant_cast<Qt::BrushStyle>(m_hatchingStyleCombo->currentData());
}

void WallSetting::changeWallWidth()
{
    m_wallHeight = qvariant_cast<int>(m_wallHeightCombo->currentText());
}

void WallSetting::createPenWidthCombo()
{
    m_penWidthCombo = new QComboBox(this);
    for (int i = 0; i < 10; ++i) {
        m_penWidthCombo->insertItem(i, QString().setNum(i), QString(i));
    }
    m_penWidthCombo->setCurrentText(QString::number(m_penWidth));
    m_penWidthCombo->setToolTip(tr("Change the thickness of the stroke line"));
    connect(m_penWidthCombo, QOverload<int>::of(&QComboBox::currentIndexChanged),
                this, &WallSetting::changePen);
}

void WallSetting::createPenColorCombo()
{
    m_penColorCombo = new QComboBox(this);
    m_penColorCombo->addItem(QIcon(":images/icons/white_48.png"), tr("White"), "#ffffff");
    m_penColorCombo->addItem(QIcon(":images/icons/lightgray_48.png"), tr("Light gray"), "#c0c0c0");
    m_penColorCombo->addItem(QIcon(":images/icons/gray_48.png"), tr("Gray"), "#a0a0a4");
    m_penColorCombo->addItem(QIcon(":images/icons/darkgray_48.png"), tr("Dark gray"), "#808080");
    m_penColorCombo->addItem(QIcon(":images/icons/black_48.png"), tr("Black"), "#000000");
    m_penColorCombo->addItem(QIcon(":images/icons/reed_48.png"), tr("Red"), "#ff0000");
    m_penColorCombo->addItem(QIcon(":images/icons/darkreed_48.png"), tr("Dark red"), "#800000");
    m_penColorCombo->addItem(QIcon(":images/icons/green_48.png"), tr("Green"), "#00ff00");
    m_penColorCombo->addItem(QIcon(":images/icons/darkgreen_48.png"), tr("Dark green"), "#008000");
    m_penColorCombo->addItem(QIcon(":images/icons/blue_48.png"), tr("Blue"), "#0000ff");
    m_penColorCombo->addItem(QIcon(":images/icons/darkblue_48.png"), tr("Dark blue"), "#000080");
    m_penColorCombo->addItem(QIcon(":images/icons/cyan_48.png"), tr("Cyan"), "#00ffff");
    m_penColorCombo->addItem(QIcon(":images/icons/darkcyan_48.png"), tr("Dark cyan"), "#008080");
    m_penColorCombo->addItem(QIcon(":images/icons/magneta_48.png"), tr("Magenta"), "#ff00ff");
    m_penColorCombo->addItem(QIcon(":images/icons/darkmagneta_48.png"), tr("Dark magenta")
                             , "#800080");
    m_penColorCombo->addItem(QIcon(":images/icons/yellow_48.png"), tr("Yellow"), "#ffff00");
    m_penColorCombo->addItem(QIcon(":images/icons/darkyellow_48.png"), tr("Dark yellow"), "#808000");
    m_penColorCombo->setCurrentIndex(m_penColorCombo->findData(m_penColor.name()));
    m_penColorCombo->setToolTip(tr("Change the wall pen color"));

    connect(m_penColorCombo, QOverload<int>::of(&QComboBox::currentIndexChanged),
                this, &WallSetting::changePen);
}

void WallSetting::createColorHatchingCombo()
{
    m_colorHatchingCombo = new QComboBox(this);
    m_colorHatchingCombo->addItem(QIcon(":images/icons/white_48.png"), tr("White"), "#ffffff");
    m_colorHatchingCombo->addItem(QIcon(":images/icons/lightgray_48.png"), tr("Light gray")
                                  , "#c0c0c0");
    m_colorHatchingCombo->addItem(QIcon(":images/icons/gray_48.png"), tr("Gray"), "#a0a0a4");
    m_colorHatchingCombo->addItem(QIcon(":images/icons/darkgray_48.png"), tr("Dark gray")
                                  , "#808080");
    m_colorHatchingCombo->addItem(QIcon(":images/icons/black_48.png"), tr("Black"), "#000000");
    m_colorHatchingCombo->addItem(QIcon(":images/icons/reed_48.png"), tr("Red"), "#ff0000");
    m_colorHatchingCombo->addItem(QIcon(":images/icons/darkreed_48.png"), tr("Dark red"), "#800000");
    m_colorHatchingCombo->addItem(QIcon(":images/icons/green_48.png"), tr("Green"), "#00ff00");
    m_colorHatchingCombo->addItem(QIcon(":images/icons/darkgreen_48.png"), tr("Dark green")
                                  , "#008000");
    m_colorHatchingCombo->addItem(QIcon(":images/icons/blue_48.png"), tr("Blue"), "#0000ff");
    m_colorHatchingCombo->addItem(QIcon(":images/icons/darkblue_48.png"), tr("Dark blue")
                                  , "#000080");
    m_colorHatchingCombo->addItem(QIcon(":images/icons/cyan_48.png"), tr("Cyan"), "#00ffff");
    m_colorHatchingCombo->addItem(QIcon(":images/icons/darkcyan_48.png"), tr("Dark cyan")
                                  , "#008080");
    m_colorHatchingCombo->addItem(QIcon(":images/icons/magneta_48.png"), tr("Magenta"), "#ff00ff");
    m_colorHatchingCombo->addItem(QIcon(":images/icons/darkmagneta_48.png"), tr("Dark magenta")
                                  , "#800080");
    m_colorHatchingCombo->addItem(QIcon(":images/icons/yellow_48.png"), tr("Yellow"), "#ffff00");
    m_colorHatchingCombo->addItem(QIcon(":images/icons/darkyellow_48.png"), tr("Dark yellow")
                                  , "#8080000");
    m_colorHatchingCombo->setCurrentIndex(m_colorHatchingCombo->findData(m_hatchingColor.name()));
    m_colorHatchingCombo->setToolTip(tr("Change the wall fill color"));

    connect(m_colorHatchingCombo, QOverload<int>::of(&QComboBox::currentIndexChanged),
                this, &WallSetting::changeHatching);
}

void WallSetting::createHatchigStyleCombo()
{
    m_hatchingStyleCombo = new QComboBox(this);
    m_hatchingStyleCombo->addItem(QIcon(":images/icons/nobrush.png"), tr("No brush"), "0");
    m_hatchingStyleCombo->addItem(QIcon(":images/icons/solidbrush.png"), tr("Solid"), "1");
    m_hatchingStyleCombo->addItem(QIcon(":images/icons/bdiagbrush.png"), tr("BDiag"), "12");
    m_hatchingStyleCombo->addItem(QIcon(":images/icons/fdiagbrush.png"), tr("FDiag"), "13");
    m_hatchingStyleCombo->addItem(QIcon(":images/icons/diagcrossbrush.png"), tr("DiagCross"), "14");
    m_hatchingStyleCombo->addItem(QIcon(":images/icons/dense_1.png"), tr("Dense 1"), "2");
    m_hatchingStyleCombo->addItem(QIcon(":images/icons/dense_2.png"), tr("Dense 2"), "3");
    m_hatchingStyleCombo->addItem(QIcon(":images/icons/dense_3.png"), tr("Dense 3"), "4");
    m_hatchingStyleCombo->addItem(QIcon(":images/icons/dense_4.png"), tr("Dense 4"), "5");
    m_hatchingStyleCombo->addItem(QIcon(":images/icons/dense_5.png"), tr("Dense 5"), "6");
    m_hatchingStyleCombo->addItem(QIcon(":images/icons/dense_6.png"), tr("Dense 6"), "7");
    m_hatchingStyleCombo->addItem(QIcon(":images/icons/dense_7.png"), tr("Dense 7"), "8");
    m_hatchingStyleCombo->setCurrentIndex(m_hatchingStyleCombo->
                                          findData(QString::number(m_hatchingStyle)));
    m_hatchingStyleCombo->setToolTip(tr("Change the wall fill style"));
    connect(m_hatchingStyleCombo, QOverload<int>::of(&QComboBox::currentIndexChanged),
                this, &WallSetting::changeHatching);
}

void WallSetting::createWallHeightCombo()
{
    m_wallHeightCombo = new QComboBox(this);
    for (int i = 6; i < 26; i += 2) {
        m_wallHeightCombo->insertItem(i, QString().setNum(i), QString(i));
    }
    m_wallHeightCombo->setCurrentText(QString::number(m_wallHeight));
    m_wallHeightCombo->setToolTip(tr("Change the wall thickness"));
    connect(m_wallHeightCombo, QOverload<int>::of(&QComboBox::currentIndexChanged),
                this, &WallSetting::changeWallWidth);
}

void WallSetting::createUi()
{
    QVBoxLayout *vBoxLayout = new QVBoxLayout(this);

    createPenWidthCombo();
    QHBoxLayout *penWidthLayout = new QHBoxLayout(this);
    penWidthLayout->addWidget(ui->lbPenWidth);
    penWidthLayout->addWidget(m_penWidthCombo);
    vBoxLayout->addLayout(penWidthLayout);

    createPenColorCombo();
    QHBoxLayout *penColorLayout = new QHBoxLayout(this);
    penColorLayout->addWidget(ui->lbPenColor);
    penColorLayout->addWidget(m_penColorCombo);
    vBoxLayout->addLayout(penColorLayout);

    createColorHatchingCombo();
    QHBoxLayout *colorHatchingLayout = new QHBoxLayout(this);
    colorHatchingLayout->addWidget(ui->lbColorHatching);
    colorHatchingLayout->addWidget(m_colorHatchingCombo);
    vBoxLayout->addLayout(colorHatchingLayout);

    createHatchigStyleCombo();
    QHBoxLayout *hatchingStyleLayout = new QHBoxLayout(this);
    hatchingStyleLayout->addWidget(ui->lbHatching);
    hatchingStyleLayout->addWidget(m_hatchingStyleCombo);
    vBoxLayout->addLayout(hatchingStyleLayout);

    createWallHeightCombo();
    QHBoxLayout *wallWidthLayout = new QHBoxLayout(this);
    wallWidthLayout->addWidget(ui->lbWallWidth);
    wallWidthLayout->addWidget(m_wallHeightCombo);
    vBoxLayout->addLayout(wallWidthLayout);

    vBoxLayout->addWidget(ui->buttonBox);
}
