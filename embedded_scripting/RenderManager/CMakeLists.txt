include(ExternalProject)
CMAKE_MINIMUM_REQUIRED(VERSION 2.8)

find_package(SDL REQUIRED)

ExternalProject_Add(
    SDL_gfx-2.0
    #URL http://www.ferzkopp.net/Software/SDL_gfx-2.0/SDL_gfx-2.0.22.tar.gz
    URL http://downloads.sourceforge.net/project/sdlgfx/SDL_gfx-2.0.23.tar.gz
    URL_MD5 fcc3c4f2d1b4943409bf7e67dd65d03a
    #INSTALL_DIR libs/SDL_gfx-2.0
    CONFIGURE_COMMAND <SOURCE_DIR>/configure --prefix=<INSTALL_DIR>
    )
ExternalProject_Get_Property(SDL_gfx-2.0 INSTALL_DIR)
include_directories("${INSTALL_DIR}/include")
include_directories("/usr/include/SDL") # So the SDL_gfx library can find SDL.


ExternalProject_Add(
    SDL_image-1.2.12
    URL http://www.libsdl.org/projects/SDL_image/release/SDL_image-1.2.12.tar.gz
    URL_MD5 a0f9098ebe5400f0bdc9b62e60797ecb
    #INSTALL_DIR libs/SDL_image-1.2.12
    CONFIGURE_COMMAND <SOURCE_DIR>/configure --prefix=<INSTALL_DIR>
    )
ExternalProject_Get_Property(SDL_image-1.2.12 INSTALL_DIR)
include_directories("${INSTALL_DIR}/include")

ExternalProject_Add(
    SDL_ttf-2.0.11
    URL http://www.libsdl.org/projects/SDL_ttf/release/SDL_ttf-2.0.11.tar.gz
    #INSTALL_DIR libs/SDL_ttf-2.0.11
    CONFIGURE_COMMAND <SOURCE_DIR>/configure --prefix=<INSTALL_DIR>
    )
ExternalProject_Get_Property(SDL_ttf-2.0.11 INSTALL_DIR)
include_directories("${INSTALL_DIR}/include")

add_library(RenderManager STATIC RenderManager.cpp Ship.cpp
    TextBox.cpp)
add_dependencies(RenderManager SDL_gfx-2.0 SDL_image-1.2.12 SDL_ttf-2.0.11)
target_link_libraries(RenderManager SDL_gfx SDL_image SDL_ttf ${SDL_LIBRARY})





