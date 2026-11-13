qt_add_executable(tst_equipmentshape tst_equipmentshape.cpp)

target_link_libraries(tst_equipmentshape PRIVATE
    shapes
    Qt6::Test
)

add_test(NAME tst_equipmentshape COMMAND tst_equipmentshape)
