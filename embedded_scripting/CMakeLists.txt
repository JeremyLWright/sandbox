CMAKE_MINIMUM_REQUIRED(VERSION 2.8)
project(EmbeddedScripting)
SET(CMAKE_CXX_FLAGS " -std=gnu++0x")
SET(CMAKE_CXX_FLAGS_DEBUG "-g3 -ggdb -O0 -Wall -std=gnu++0x")
SET(CMAKE_CXX_FLAGS_RELEASE "-O2 -std=gnu++0x")

include_directories(".")

add_subdirectory(ScriptEngine)

add_subdirectory(RenderManager)
ExternalProject_Get_Property(SDL_gfx-2.0 INSTALL_DIR)
include_directories(".")
include_directories(${INSTALL_DIR}/include)
link_directories(${INSTALL_DIR}/lib)

ExternalProject_Get_Property(SDL_ttf-2.0.11 INSTALL_DIR)
include_directories(${INSTALL_DIR}/include)
link_directories(${INSTALL_DIR}/lib)

ExternalProject_Get_Property(SDL_image-1.2.12 INSTALL_DIR)
include_directories(${INSTALL_DIR}/include)
link_directories(${INSTALL_DIR}/lib)

add_definitions(-DRENDER)
include_directories("/usr/include/SDL") # So the SDL_gfx library can find SDL.

#SET(GameSources experiment.cpp)

add_executable(run-life main.cpp )#${GameSources})
target_link_libraries(run-life RenderManager ScriptEngine)

#file(GLOB TestSources Tests/*.cpp)


#add_executable(unit-test ${TestSources})
#target_link_libraries(unit-test gtest gtest_main rt pthread)
