TEMPLATE = subdirs

SUBDIRS += \
    rsised \
    libshapes \
    tst_abstractshape \
    tst_buildingshape \
    tst_technicsshape \
    tst_ellipseshape \
    tst_rectshape

libshapes.subdir = src/libshapes
rsised.subdir = src/rsised
tst_abstractshape.subdir = tests/auto/tst_libshapes/tst_abstractshape
tst_rectshape.subdir = tests/auto/tst_libshapes/tst_rectshape
tst_ellipseshape.subdir = tests/auto/tst_libshapes/tst_ellipseshape
tst_buildingshape.subdir = tests/auto/tst_libshapes/tst_buildingshape
tst_technicsshape.subdir = tests/auto/tst_libshapes/tst_technicsshape

rsised.depends = libshapes
tst_abstractshape.depends = libshapes
tst_rectshape.depends = libshapes
tst_ellipseshape.depends = libshapes
tst_buildingshape.depends = libshapes
tst_technicsshape.depends = libshapes

OTHER_FILES = \
    COPYING \
    README.md \
    deploy/deploy.sh \
    deploy/linux/tar_gz/cqt_linux_targz.json \
    deploy/linux/tar_gz/uninstall.sh
