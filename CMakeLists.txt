cmake_minimum_required(VERSION 3.10)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
project(ANTHILL)

file(GLOB_RECURSE SOURCES "src/*.cpp")
add_executable(${PROJECT_NAME} ${SOURCES})

# "./3rd_party/SDL3/include" "./3rd_party/stb/include" "./3rd_party/miniaudio/include"
target_include_directories(${PROJECT_NAME} PRIVATE "./src")

set_property(TARGET ${PROJECT_NAME} PROPERTY CXX_STANDARD 17)
set_property(TARGET ${PROJECT_NAME} PROPERTY CXX_STANDARD_REQUIRED ON)

target_compile_options(${PROJECT_NAME} PRIVATE -O3 -Wall)

# PATHS "./3rd_party/SDL3" NO_DEFAULT_PATH
find_package(SDL3 REQUIRED)
target_link_libraries(${PROJECT_NAME} PRIVATE SDL3::SDL3)
