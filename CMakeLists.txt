cmake_minimum_required(VERSION 3.10)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
project(ANTHILL)

file(GLOB_RECURSE SOURCES "src/*.cpp")
add_executable(${PROJECT_NAME} ${SOURCES})

target_include_directories(${PROJECT_NAME} PRIVATE "./src")

set_property(TARGET ${PROJECT_NAME} PROPERTY CXX_STANDARD 20)
set_property(TARGET ${PROJECT_NAME} PROPERTY CXX_STANDARD_REQUIRED ON)

target_compile_options(${PROJECT_NAME} PRIVATE -O3 -Wall)

find_package(SDL3 REQUIRED)

target_link_libraries(${PROJECT_NAME} PRIVATE SDL3::SDL3)
# target_link_options(${PROJECT_NAME} PRIVATE -static)
