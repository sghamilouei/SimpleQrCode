add_library(FrameHandler FrameHandler.cpp)
target_include_directories(FrameHandler PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

find_package(OpenCV CONFIG REQUIRED)

target_link_libraries(FrameHandler PRIVATE
        ${OpenCV_LIBS}
)
