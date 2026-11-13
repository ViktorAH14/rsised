qt_add_executable(tst_ellipseshape tst_ellipseshape.cpp)

target_link_libraries(tst_ellipseshape PRIVATE
    shapes
    Qt6::Test
)

add_test(NAME tst_ellipseshape COMMAND tst_ellipseshape)
