qt_add_executable(tst_technicsshape tst_technicsshape.cpp)

target_link_libraries(tst_technicsshape PRIVATE
    shapes
    Qt6::Test
)

add_test(NAME tst_technicsshape COMMAND tst_technicsshape)
