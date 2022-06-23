TEMPLATE = subdirs

SUBDIRS += \
    src/rsised \
    src/shapeslib \
    tests/auto/tst_libshapes/tst_rectshape

shapeslib.subdirs = src/shapeslib
tst_rectshape.subdirs = tests/auto/tst_libshapes/tst_rectshape
app.subdirs = src/rsised

app.depends = shapeslib
tst_rectshape.depends = shapeslib
