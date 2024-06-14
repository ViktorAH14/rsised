PROJECT_ROOT_PATH = $${PWD}

#win32: OS_SUFFIX = win32
#win64-x-g++: OS_SUFFIX = win64

win32: contains(QT_ARCH, i386) {
            OS_SUFFIX = win32
        } else {
            OS_SUFFIX = win64
        }

linux-g++: OS_SUFFIX = linux

CONFIG(debug, debug|release) {
    BUILD_FLAG = debug
    LIB_SUFFIX = d
} else {
    CONFIG(force_debug_info) {
        BUILD_FLAG = profile
        QMAKE_CXXFLAGS += --coverage
        QMAKE_LFLAGS += --coverage
        } else {
        BUILD_FLAG = release
        }
}

LIBS_PATH = $${PROJECT_ROOT_PATH}/lib.$${OS_SUFFIX}/
INC_PATH = $${PROJECT_ROOT_PATH}/include/
IMPORT_PATH = $${PROJECT_ROOT_PATH}/import/
BIN_PATH = $${PROJECT_ROOT_PATH}/bin/$${OS_SUFFIX}/$${BUILD_FLAG}/

BUILD_PATH = $${PROJECT_ROOT_PATH}/build/$${OS_SUFFIX}/$${BUILD_FLAG}/$${TARGET}/
RCC_DIR = $${BUILD_PATH}/rcc/
UI_DIR = $${BUILD_PATH}/ui/
MOC_DIR = $${BUILD_PATH}/moc/
OBJECTS_DIR = $${BUILD_PATH}/obj/

LIBS += -L$${LIBS_PATH}/
INCLUDEPATH += $${INC_PATH}/
INCLUDEPATH += $${IMPORT_PATH}/

#linux-g++: QMAKE_CXXFLAGS += -std=c++17
