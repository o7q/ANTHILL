cmake_minimum_required(VERSION 3.10)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
project(ANTHILL)

file(GLOB_RECURSE SOURCES "src/*.cpp" "../px/src/*.cpp")
add_executable(${PROJECT_NAME} ${SOURCES})

# "./libs/SDL3/include" "./libs/stb/include" "./libs/miniaudio/include"
target_include_directories(${PROJECT_NAME} PRIVATE "./src" "../px/src")

set_property(TARGET ${PROJECT_NAME} PROPERTY CXX_STANDARD 17)
set_property(TARGET ${PROJECT_NAME} PROPERTY CXX_STANDARD_REQUIRED ON)

# extra flags: -Wextra
target_compile_options(${PROJECT_NAME} PRIVATE -O2 -Wall -Wpedantic -Wshadow -Wuninitialized)
# debugging: target_link_options(${PROJECT_NAME} PRIVATE -fsanitize=address,undefined)

# PATHS "./libs/SDL3" NO_DEFAULT_PATH
find_package(SDL3 REQUIRED)
target_link_libraries(${PROJECT_NAME} PRIVATE SDL3::SDL3)
