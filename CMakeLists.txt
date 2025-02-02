cmake_minimum_required(VERSION 3.10)

project(ANTHILL)

file(GLOB_RECURSE SOURCES "src/*.cpp")
add_executable(${PROJECT_NAME} ${SOURCES})

set_property(TARGET ${PROJECT_NAME} PROPERTY CXX_STANDARD 17)
set_property(TARGET ${PROJECT_NAME} PROPERTY CXX_STANDARD_REQUIRED ON)

target_compile_options(${PROJECT_NAME} PRIVATE -O3 -Wall)

find_package(SDL3 REQUIRED)
find_package(SDL3_image REQUIRED)
find_package(SDL3_mixer REQUIRED)
find_package(SDL3_ttf REQUIRED)

target_link_libraries(${PROJECT_NAME} PRIVATE SDL3::SDL3 SDL3_image::SDL3_image SDL3_mixer::SDL3_mixer SDL3_ttf::SDL3_ttf)
target_link_options(${PROJECT_NAME} PRIVATE -static)