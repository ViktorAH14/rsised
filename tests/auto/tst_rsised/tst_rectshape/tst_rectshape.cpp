#include <QtTest>
#include <QMenu>

#include "../../../../src/rsised/rectshape.h"

class tst_RectShape : public QObject
{
    Q_OBJECT

private slots:
    void construction();

};

void tst_RectShape::construction()
{
//    QMenu *contextMenu = new QMenu();
//    RectShape *rectShape = new RectShape(contextMenu);

//    delete rectShape;
}

QTEST_APPLESS_MAIN(tst_RectShape)

#include "tst_rectshape.moc"
