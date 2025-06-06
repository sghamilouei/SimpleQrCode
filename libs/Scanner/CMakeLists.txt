add_library(Scanner Scanner.cpp)
target_include_directories(Scanner PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

find_package(OpenCV CONFIG REQUIRED)
if(NOT TARGET ZXing::Core)
    find_package(ZXing REQUIRED)
endif()

target_link_libraries(Scanner PRIVATE
        ${OpenCV_LIBS}
        ZXing::ZXing
)