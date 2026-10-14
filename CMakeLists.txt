cmake_minimum_required(VERSION 3.10.0)
project(mandelbrot-gl VERSION 0.1.0 LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 20)

add_subdirectory(vendor/SDL EXCLUDE_FROM_ALL)
add_library(glad vendor/glad/glad.c)
target_include_directories(glad PUBLIC vendor)

add_executable(mandelbrot-gl main.cpp)
target_include_directories(mandelbrot-gl PRIVATE src)
target_sources(mandelbrot-gl
PRIVATE
    main.cpp
    src/helpers.cpp
    src/fractalgl.cpp
)
target_link_libraries(mandelbrot-gl PRIVATE SDL3::SDL3 glad)

include(CTest)
enable_testing()

# file system macro
target_compile_definitions(mandelbrot-gl PRIVATE
    SOURCE_PATH="${CMAKE_CURRENT_SOURCE_DIR}"
)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)

