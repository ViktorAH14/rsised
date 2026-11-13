qt_add_executable(tst_buildingshape tst_buildingshape.cpp)

target_link_libraries(tst_buildingshape PRIVATE
    shapes
    Qt6::Test
)

add_test(NAME tst_buildingshape COMMAND tst_buildingshape)
