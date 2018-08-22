
add_executable(brickset_console main.cpp)
target_link_libraries(brickset_console LINK_PUBLIC brickset)
set_property(TARGET brickset_console PROPERTY CXX_STANDARD 17)
set_property(TARGET brickset_console PROPERTY CXX_STANDARD_REQUIRED ON)

