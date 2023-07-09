cmake_minimum_required(VERSION 3.26)

project(RPG)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)
set(CMAKE_EXPORT_COMPILE_COMMANDS True)

find_package(SDL2 REQUIRED)
find_package(SDL2_Image REQUIRED)

aux_source_directory("game/source" SOURCE_FILES)

add_executable(${PROJECT_NAME} ${SOURCE_FILES})

target_include_directories(${PROJECT_NAME} PUBLIC "game/include")

target_link_libraries(${PROJECT_NAME} PRIVATE SDL2)
target_link_libraries(${PROJECT_NAME} PRIVATE SDL2_image)
target_link_libraries(${PROJECT_NAME} PRIVATE tmxlite)