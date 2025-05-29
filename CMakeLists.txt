cmake_minimum_required(VERSION 3.31)
project(SimpleQrCode)

set(CMAKE_CXX_STANDARD 20)

add_subdirectory(libs/FrameHandler FrameHandler)
add_subdirectory(libs/Scanner Scanner)
add_subdirectory(libs/UI UI)
add_subdirectory(libs/Archive Archive)

add_executable(SimpleQrCode src/main.cpp)

target_link_libraries(SimpleQrCode PRIVATE FrameHandler)
target_link_libraries(SimpleQrCode PRIVATE Scanner)
target_link_libraries(SimpleQrCode PRIVATE UI)
target_link_libraries(SimpleQrCode PRIVATE Archive)


