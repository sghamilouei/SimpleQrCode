cmake_minimum_required(VERSION 3.16)
project(OpenCV_UI_Test)

set(CMAKE_CXX_STANDARD 17)

# مهم: vcpkg toolchain قبلاً در CLion تنظیم شده باشه
find_package(OpenCV REQUIRED)

# اضافه کردن زیرپروژه UI
add_subdirectory(libs/UI)

# فایل اجرایی اصلی
add_executable(MainApp src/main.cpp)

# مسیر include برای فایل‌های UI
target_include_directories(MainApp
        PRIVATE
        ${PROJECT_SOURCE_DIR}/libs
)

# 👇 این بخش مهم‌ترین قسمت است
target_link_libraries(MainApp
        PRIVATE
        UI
        ${OpenCV_LIBS}
)
