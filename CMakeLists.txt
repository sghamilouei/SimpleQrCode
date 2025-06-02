
cmake_minimum_required(VERSION 3.31)

# Integrate vcpkg before the project() command
if(DEFINED ENV{VCPKG_ROOT} AND NOT DEFINED CMAKE_TOOLCHAIN_FILE)
    set(CMAKE_TOOLCHAIN_FILE "$ENV{VCPKG_ROOT}/scripts/buildsystems/vcpkg.cmake"
            CACHE STRING "Vcpkg toolchain file")
endif()

project(SimpleQrCode)

set(CMAKE_CXX_STANDARD 20)

# Find required packages
find_package(nlohmann_json CONFIG REQUIRED)
find_package(ZXing CONFIG REQUIRED)
find_package(OpenCV CONFIG REQUIRED)
find_package(Protobuf CONFIG REQUIRED)

# Your existing subdirectories
add_subdirectory(libs/FrameHandler FrameHandler)
add_subdirectory(libs/Scanner Scanner)
add_subdirectory(libs/UI UI)
add_subdirectory(libs/Archive Archive)

add_executable(SimpleQrCode src/main.cpp)

target_link_libraries(SimpleQrCode PRIVATE
        FrameHandler
        Scanner
        UI
        Archive
        nlohmann_json::nlohmann_json
        ZXing::ZXing
        ${OpenCV_LIBS}
        protobuf::libprotobuf
)