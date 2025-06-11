add_library(Archive Archive.cpp)
target_include_directories(Archive PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

find_package(OpenCV CONFIG REQUIRED)
if(NOT TARGET nlohmann_json)
    find_package(nlohmann_json REQUIRED)
endif()

target_link_libraries(Archive PRIVATE
        ${OpenCV_LIBS}
        nlohmann_json
)