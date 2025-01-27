cmake_minimum_required(VERSION 3.31)
project(2dEngine CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED True)

include_directories(
    /usr/include/SDL2
    ${CMAKE_SOURCE_DIR}/engine
    ${CMAKE_SOURCE_DIR}/imgui
    ${CMAKE_SOURCE_DIR}/imgui/backends
    ${CMAKE_SOURCE_DIR}/source
    ${CMAKE_SOURCE_DIR}/source/states
)

link_directories(
    /usr/lib/x86_64-linux-gnu  # Adjust this if the libraries are in a different directory
)

file(GLOB_RECURSE ENGINE_SOURCES "engine/*.cpp")
file(GLOB_RECURSE SOURCE_SOURCES "source/*.cpp")
file(GLOB_RECURSE IMGUI_SOURCES "imgui/*.cpp")

set(SOURCES ${ENGINE_SOURCES} ${SOURCE_SOURCES} ${IMGUI_SOURCES})

find_package(SDL2 REQUIRED)
find_package(SDL2_IMAGE REQUIRED)
find_package(SDL2_TTF REQUIRED)
find_package(SDL2_MIXER REQUIRED)
#include_directories(
#    ${SDL2_INCLUDE_DIRS} 
#    ${SDL2_IMAGE_INCLUDE_DIRS}
#    ${SDL2_TTF_INCLUDE_DIRS}
#    ${SDL2_MIXER_INCLUDE_DIRS}
#)

add_executable(2dEngine ${SOURCES})

#target_link_libraries(2dEngine ${SDL2_LIBRARIES} ${SDL2_IMAGE_LIBRARIES} ${SDL2_TTF_LIBRARIES} ${SDL2_MIXER_LIBRARIES})
target_link_libraries(2dEngine SDL2 SDL2_image SDL2_ttf SDL2_mixer)
