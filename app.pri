DESTDIR = $${BIN_PATH}/
linux-g++: QMAKE_LFLAGS += -Wl,--rpath=\\\$\$ORIGIN/../../lib.$${OS_SUFFIX}/

DISTFILES += \
    $$PWD/.github/ISSUE_TEMPLATE/bug_report.yml \
    $$PWD/.github/ISSUE_TEMPLATE/build_issue.yml \
    $$PWD/.github/ISSUE_TEMPLATE/feature_request.yml
