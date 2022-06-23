TEMPLATE = subdirs

SUBDIRS += \
    src/rsised \
    src/libshapes \
    tests/auto/tst_libshapes/tst_rectshape

libshapes.subdirs = src/libshapes
tst_rectshape.subdirs = tests/auto/tst_libshapes/tst_rectshape
app.subdirs = src/rsised

app.depends = libshapes
tst_rectshape.depends = libshapes
