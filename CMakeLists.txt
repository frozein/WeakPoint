cmake_minimum_required(VERSION 3.12)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

project(scarletgamejam VERSION 1.0)

# find source files:
file(GLOB_RECURSE scarletgamejam_src CONFIGURE_DEPENDS "src/*.cpp")
add_executable(${PROJECT_NAME} ${scarletgamejam_src})

# find include diretories and libraries
find_package(SDL2 REQUIRED)
find_library(LIBSDL2     SDL2)
find_library(LIBSDL2MAIN SDL2main)
find_library(LIBSDL2IMG  SDL2_image)
find_library(LIBSDL2TTF  SDL2_ttf)
find_library(LIBSDL2MIX  SDL2_mixer)
target_link_libraries(${PROJECT_NAME} ${LIBSDL2} ${LIBSDL2MAIN} ${LIBSDL2IMG} ${LIBSDL2TTF} ${LIBSDL2MIX})
include_directories("src/" ${SDL2_INCLUDE_DIRS})

# set working directory:
set_property(TARGET ${PROJECT_NAME} PROPERTY WORKING_DIRECTORY "../assets/")
if(WIN32)
    set_property(TARGET ${PROJECT_NAME} PROPERTY VS_DEBUGGER_WORKING_DIRECTORY "../assets/")
    set_property(TARGET ${PROJECT_NAME} PROPERTY VS_DPI_AWARE "PerMonitor") # set dpi awareness (only works on windows)
endif()