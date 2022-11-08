cmake_minimum_required(VERSION 3.12)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

project(dronegame VERSION 1.0)

file(GLOB_RECURSE dronegame_src CONFIGURE_DEPENDS "src/*.cpp")

find_package(sdl2 REQUIRED)
if(WIN32)
    find_package(sdl2-image REQUIRED) # lol
else()
    find_package(sdl2_image REQUIRED)
endif()
find_package(sdl2_mixer REQUIRED)
find_package(sdl2_ttf REQUIRED)
set(dronegame_lib ${SDL2_LIBRARIES} ${SDL2IMAGE_LIBRARIES} ${SDL2MIXER_LIBRARIES} ${SDL2TTF_LIBRARIES})

add_executable(${PROJECT_NAME} ${dronegame_src})

set_property(TARGET ${PROJECT_NAME} PROPERTY WORKING_DIRECTORY "../assets/")
if(WIN32)
    set_property(TARGET ${PROJECT_NAME} PROPERTY VS_DEBUGGER_WORKING_DIRECTORY "../assets/")
    set_property(TARGET ${PROJECT_NAME} PROPERTY VS_DPI_AWARE "PerMonitor")
endif()

target_link_libraries(${PROJECT_NAME} ${dronegame_lib})
include_directories("src/" ${SDL2_INCLUDE} ${SDL2IMAGE_INCLUDE} ${SDL2MIXER_INCLUDE} ${SDL2TTF_INCLUDE})