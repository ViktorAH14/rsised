qt_add_executable(tst_rectshape tst_rectshape.cpp)

target_link_libraries(tst_rectshape PRIVATE
    shapes
    Qt6::Test
)

add_test(NAME tst_rectshape COMMAND tst_rectshape)
