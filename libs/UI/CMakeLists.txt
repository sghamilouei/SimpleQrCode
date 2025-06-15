
add_library(UI
    UI.cpp
    UI.h
)

target_include_directories(UI
    PRIVATE
        ${OpenCV_INCLUDE_DIRS}
)

target_link_libraries(UI
    PRIVATE
        ${OpenCV_LIBS}
)
