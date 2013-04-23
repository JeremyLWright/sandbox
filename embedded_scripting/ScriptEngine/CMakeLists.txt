CMAKE_MINIMUM_REQUIRED(VERSION 2.8)
Find_Package(BISON REQUIRED)
Find_Package(FLEX REQUIRED)

SET(CMAKE_CXX_FLAGS "-O0 -Wall -std=gnu++0x")
SET(CMAKE_CXX_FLAGS_DEBUG "-O0 -g3 -ggdb -Wall -std=gnu++0x")
SET(CMAKE_CXX_FLAGS_RELEASE "-O2 -DNDEBUG -std=gnu++0x")

BISON_TARGET(MoonLangParser MoonLanguage.y
    ${CMAKE_CURRENT_BINARY_DIR}/MoonLangParser.cpp  COMPILE_FLAGS "-rall" )
FLEX_TARGET(MoonLangLexer MoonLanguage.l
    ${CMAKE_CURRENT_BINARY_DIR}/MoonLangLexer.cpp
    COMPILE_FLAGS "--header-file=${CMAKE_CURRENT_BINARY_DIR}/MoonLangLexer.hpp")
ADD_FLEX_BISON_DEPENDENCY(MoonLangLexer MoonLangParser)
include_directories(.)
include_directories(${CMAKE_CURRENT_BINARY_DIR})
#set(HandSources SymbolTable.cpp Symbol.cpp)
set(PROJ_SOURCES ${BISON_MoonLangParser_OUTPUTS} ${FLEX_MoonLangLexer_OUTPUTS})
add_library(ScriptEngine ${PROJ_SOURCES})
target_link_libraries(ScriptEngine ${FLEX_LIBRARIES})

