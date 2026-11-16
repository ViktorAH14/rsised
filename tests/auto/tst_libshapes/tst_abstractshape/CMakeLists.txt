qt_add_executable(tst_abstractshape tst_abstractshape.cpp)

target_link_libraries(tst_abstractshape PRIVATE
    shapes
    Qt6::Test
)

add_test(NAME tst_abstractshape COMMAND tst_abstractshape)
