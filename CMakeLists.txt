cmake_minimum_required(VERSION 3.20)
project(Archive_Module)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_library(Archive STATIC
        archive.cpp
        Archve.h
        Archive.cpp
)

target_include_directories(Archive PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

find_package(OpenCV REQUIRED)
find_package(nlohmann_json CONFIG REQUIRED)

target_link_libraries(Archive PRIVATE
        ${OpenCV_LIBS}
        nlohmann_json::nlohmann_json
)