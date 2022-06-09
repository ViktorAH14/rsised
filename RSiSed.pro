TEMPLATE = subdirs

SUBDIRS += \
    src/rsised \
    src/shapeslib \
    tests/auto/tst_rsised/tst_rectshape

shapeslib.subdirs = src/shapeslib
tst_rectshape.subdirs = tests/auto/tst_rsised/tst_rectshape
app.subdirs = src/rsised

app.depends = shapeslib
tst_rectshape.depends = shapeslib
