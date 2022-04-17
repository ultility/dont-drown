cmake_minimum_required(VERSION 3.0.0)
project(Dont_Drown VERSION 0.1.0)

include(CTest)
enable_testing()

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin)
set(LIBRARY_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/lib)
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${PROJECT_SOURCE_DIR}/modules)

include_directories(${PROJECT_SOURCE_DIR}/src)

add_library(Graphics src/Window.cpp src/Texture.cpp)
add_library(LevelMaker src/Platform.cpp src/Level.cpp)
add_library(Player src/Player.cpp)


add_executable(main src/DontDrown.cpp)



find_package(SDL2 CONFIG REQUIRED)
find_package(sdl2-image CONFIG REQUIRED)
#find_package(sdl2-mixer CONFIG REQUIRED)
#find_package(sdl2-ttf CONFIG REQUIRED)

target_link_libraries(main PRIVATE SDL2::SDL2 SDL2::SDL2main SDL2::SDL2-static)
target_link_libraries(main PRIVATE SDL2::SDL2_image)
target_link_libraries(main PRIVATE Graphics)
target_link_libraries(main PRIVATE Player)
#target_link_libraries(LevelMaker PRIVATE Graphics)
target_link_libraries(main PRIVATE LevelMaker)




include(CPack)

