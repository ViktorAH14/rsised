#include "wallsetting.h"
#include "ui_wallsetting.h"

#include <QComboBox>
#include <QHBoxLayout>

WallSetting::WallSetting(QWidget *parent) :
    QDialog(parent)
  , ui(new Ui::WallSetting)
  , m_penWidth{1}
  , m_penColor{QColor(Qt::black)}
  , m_hatchingColor{QColor(Qt::lightGray)}
  , m_hatchingStyle{Qt::SolidPattern}
  , m_wallHeight{10}
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
    m_penColor = qvariant_cast<Qt::GlobalColor>(m_penColorCombo->currentData());
}

void WallSetting::changeHatching()
{
    m_hatchingColor = qvariant_cast<Qt::GlobalColor>(m_colorHatchingCombo->currentData());
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
    m_penWidthCombo->setCurrentIndex(1);
    m_penWidthCombo->setToolTip(tr("Change the thickness of the stroke line"));
    connect(m_penWidthCombo, QOverload<int>::of(&QComboBox::currentIndexChanged),
                this, &WallSetting::changePen);
}

void WallSetting::createPenColorCombo()
{
    m_penColorCombo = new QComboBox(this);
    m_penColorCombo->addItem(QIcon(":images/icons/white_48.png"), tr("White"), "Qt::white");
    m_penColorCombo->addItem(QIcon(":images/icons/black_48.png"), tr("Black"), "Qt::black");
    m_penColorCombo->addItem(QIcon(":images/icons/lightgray_48.png"), tr("Light gray")
                                  , "Qt::lightGray");
    m_penColorCombo->addItem(QIcon(":images/icons/gray_48.png"), tr("Gray"), "Qt::gray");
    m_penColorCombo->addItem(QIcon(":images/icons/darkgray_48.png"), tr("Dark gray")
                                  , "Qt::darkGray");
    m_penColorCombo->addItem(QIcon(":images/icons/reed_48.png"), tr("Red"), "Qt::red");
    m_penColorCombo->addItem(QIcon(":images/icons/darkreed_48.png"), tr("Dark red")
                                  , "Qt::darkRed");
    m_penColorCombo->addItem(QIcon(":images/icons/green_48.png"), tr("Green"), "Qt::green");
    m_penColorCombo->addItem(QIcon(":images/icons/darkgreen_48.png"), tr("Dark green")
                                  , "Qt::darkGreen");
    m_penColorCombo->addItem(QIcon(":images/icons/blue_48.png"), tr("Blue"), "Qt::blue");
    m_penColorCombo->addItem(QIcon(":images/icons/darkblue_48.png"), tr("Dark blue")
                                  , "Qt::darkBlue");
    m_penColorCombo->addItem(QIcon(":images/icons/cyan_48.png"), tr("Cyan"), "Qt::cyan");
    m_penColorCombo->addItem(QIcon(":images/icons/darkcyan_48.png"), tr("Dark cyan")
                                  , "Qt::darkCyan");
    m_penColorCombo->addItem(QIcon(":images/icons/magneta_48.png"), tr("Magenta")
                                  , "Qt::magenta");
    m_penColorCombo->addItem(QIcon(":images/icons/darkmagneta_48.png"), tr("Dark magenta")
                                  , "Qt::darkMagenta");
    m_penColorCombo->addItem(QIcon(":images/icons/yellow_48.png"), tr("Yellow"), "Qt::yellow");
    m_penColorCombo->addItem(QIcon(":images/icons/darkyellow_48.png"), tr("Dark yellow")
                                  , "Qt::darkYellow");
    m_penColorCombo->setCurrentIndex(1);
    m_penColorCombo->setToolTip(tr("Change the wall pen color"));

    connect(m_penColorCombo, QOverload<int>::of(&QComboBox::currentIndexChanged),
                this, &WallSetting::changePen);
}

void WallSetting::createColorHatchingCombo()
{
    m_colorHatchingCombo = new QComboBox(this);
    m_colorHatchingCombo->addItem(QIcon(":images/icons/white_48.png"), tr("White"), "Qt::white");
    m_colorHatchingCombo->addItem(QIcon(":images/icons/lightgray_48.png"), tr("Light gray")
                                  , "Qt::lightGray");
    m_colorHatchingCombo->addItem(QIcon(":images/icons/gray_48.png"), tr("Gray"), "Qt::gray");
    m_colorHatchingCombo->addItem(QIcon(":images/icons/darkgray_48.png"), tr("Dark gray")
                                  , "Qt::darkGray");
    m_colorHatchingCombo->addItem(QIcon(":images/icons/black_48.png"), tr("Black"), "Qt::black");
    m_colorHatchingCombo->addItem(QIcon(":images/icons/reed_48.png"), tr("Reed"), "Qt::red");
    m_colorHatchingCombo->addItem(QIcon(":images/icons/darkreed_48.png"), tr("Dark reed")
                                  , "Qt::darkRed");
    m_colorHatchingCombo->addItem(QIcon(":images/icons/green_48.png"), tr("Green"), "Qt::green");
    m_colorHatchingCombo->addItem(QIcon(":images/icons/darkgreen_48.png"), tr("Dark green")
                                  , "Qt::darkGreen");
    m_colorHatchingCombo->addItem(QIcon(":images/icons/blue_48.png"), tr("Blue"), "Qt::blue");
    m_colorHatchingCombo->addItem(QIcon(":images/icons/darkblue_48.png"), tr("Dark blue")
                                  , "Qt::darkBlue");
    m_colorHatchingCombo->addItem(QIcon(":images/icons/cyan_48.png"), tr("Cyan"), "Qt::cyan");
    m_colorHatchingCombo->addItem(QIcon(":images/icons/darkcyan_48.png"), tr("Dark cyan")
                                  , "Qt::darkCyan");
    m_colorHatchingCombo->addItem(QIcon(":images/icons/magneta_48.png"), tr("Magenta")
                                  , "Qt::magenta");
    m_colorHatchingCombo->addItem(QIcon(":images/icons/darkmagneta_48.png"), tr("Dark magenta")
                                  , "Qt::darkMagenta");
    m_colorHatchingCombo->addItem(QIcon(":images/icons/yellow_48.png"), tr("Yellow"), "Qt::yellow");
    m_colorHatchingCombo->addItem(QIcon(":images/icons/darkyellow_48.png"), tr("Dark yellow")
                                  , "Qt::darkYellow");
    m_colorHatchingCombo->setCurrentIndex(1);
    m_colorHatchingCombo->setToolTip(tr("Change the wall fill color"));

    connect(m_colorHatchingCombo, QOverload<int>::of(&QComboBox::currentIndexChanged),
                this, &WallSetting::changeHatching);
}

void WallSetting::createHatchigStyleCombo()
{
    m_hatchingStyleCombo = new QComboBox(this);
    m_hatchingStyleCombo->addItem(QIcon(":images/icons/nobrush.png"), tr("No brush"), "Qt::NoBrush");
    m_hatchingStyleCombo->addItem(QIcon(":images/icons/solidbrush.png"), tr("Solid")
                                  , "Qt::SolidPattern");
    m_hatchingStyleCombo->addItem(QIcon(":images/icons/gridbrush.png"), tr("Cross")
                                  , "Qt::CrossPattern");
    m_hatchingStyleCombo->addItem(QIcon(":images/icons/bdiagbrush.png"), tr("BDiag")
                                  , "Qt::BDiagPattern");
    m_hatchingStyleCombo->addItem(QIcon(":images/icons/fdiagbrush.png"), tr("FDiag")
                                  , "Qt::FDiagPattern");
    m_hatchingStyleCombo->addItem(QIcon(":images/icons/diagcrossbrush.png"), tr("DiagCross")
                                  , "Qt::DiagCrossPattern");
    m_hatchingStyleCombo->addItem(QIcon(":images/icons/dense_1.png"), tr("Dense 1")
                                  , "Qt::Dense1Pattern");
    m_hatchingStyleCombo->addItem(QIcon(":images/icons/dense_2.png"), tr("Dense 2")
                                  , "Qt::Dense2Pattern");
    m_hatchingStyleCombo->addItem(QIcon(":images/icons/dense_3.png"), tr("Dense 3")
                                  , "Qt::Dense3Pattern");
    m_hatchingStyleCombo->addItem(QIcon(":images/icons/dense_4.png"), tr("Dense 4")
                                  , "Qt::Dense4Pattern");
    m_hatchingStyleCombo->addItem(QIcon(":images/icons/dense_5.png"), tr("Dense 5"), "Qt::Dense5Pattern");

    m_hatchingStyleCombo->addItem(QIcon(":images/icons/dense_6.png"), tr("Dense 6")
                                  , "Qt::Dense6Pattern");
    m_hatchingStyleCombo->addItem(QIcon(":images/icons/dense_7.png"), tr("Dense 7")
                                  , "Qt::Dense7Pattern");
    m_hatchingStyleCombo->setCurrentIndex(1);
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
    m_wallHeightCombo->setCurrentIndex(2);
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
