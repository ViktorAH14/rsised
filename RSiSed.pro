TEMPLATE = subdirs

SUBDIRS += \
    src/rsised \
    src/libshapes \
    tests/auto/tst_libshapes/tst_abstractshape \
    tests/auto/tst_libshapes/tst_buildingshape \
    tests/auto/tst_libshapes/tst_ellipseshape \
    tests/auto/tst_libshapes/tst_rectshape

libshapes.subdirs = src/libshapes
app.subdirs = src/rsised
tst_abstractshape.subdirs = tests/auto/tst_libshapes/tst_abstractshape
tst_rectshape.subdirs = tests/auto/tst_libshapes/tst_rectshape
tst_ellipseshape.subdirs = tests/auto/tst_libshapes/tst_ellipseshape
tst_buildingshape.subdirs = tests/auto/tst_libshapes/tst_buildingshape

app.depends = libshapes
tst_abstractshape.depends = libshapes
tst_rectshape.depends = libshapes
tst_ellipseshape.depends = libshapes
tst_buildingshape.depends = libshapes
