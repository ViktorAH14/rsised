TEMPLATE = subdirs

SUBDIRS += \
    src/rsised \
    src/libshapes \
    tests/auto/tst_libshapes/tst_ellipseshape \
    tests/auto/tst_libshapes/tst_rectshape

libshapes.subdirs = src/libshapes
tst_rectshape.subdirs = tests/auto/tst_libshapes/tst_rectshape
tst_ellipseshape.subdirs = tests/auto/tst_libshapes/tst_ellipseshape
app.subdirs = src/rsised

app.depends = libshapes
tst_rectshape.depends = libshapes
tst_ellipseshape.depends = libshapes
