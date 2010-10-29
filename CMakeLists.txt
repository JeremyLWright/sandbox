cmake_minimum_required (VERSION 2.6) 

project(Spatialdb)

find_package(GTest)
find_package(Doxygen)

include_directories(${GTEST_INCLUDE_DIRS})
include_directories(${CMAKE_CURRENT_SOURCE_DIR})
include_directories(sqlite3)
#doxygen confg
add_custom_target(doxygen
                    ${DOXYGEN_EXECUTABLE}
                    ${CMAKE_CURRENT_SOURCE_DIR}/config.doxygen)
#cleanup documentation on "make clean"
set_property(DIRECTORY APPEND PROPERTY
             ADDITIONAL_MAKE_CLEAN_FILES
             ../docs)
#add doxygen as dependency to doc-target
get_target_property(DOC_TARGET doc TYPE)
if(NOT DOC_TARGET)
    add_custom_target(doc)
endif()
add_dependencies(doc doxygen)

set(CMAKE_BUILD_TYPE Debug)
set(CMAKE_CXX_FLAGS "-O0 -pedantic -std=c++0x -Wall")
set(CMAKE_C_FLAGS "-DSQLITE_ENABLE_RTREE=1 ")
set(PROJECT_SOURCE_FILES
    Point.cpp
    Automaton.cpp
    AutomatonFactory.cpp
    Vector.cpp
    Point.cpp
    SpatialModel.cpp
    RegionFactory.cpp
    Region.cpp
    )
    
add_library(sqlite3 STATIC sqlite3.c)

# Build the executable 
add_executable(main main.cpp ${PROJECT_SOURCE_FILES})
target_link_libraries(main sqlite3 pthread dl)

if(GTEST_FOUND)
    add_custom_target(test
                      COMMAND test_spatialdb
                      DEPENDS test_spatialdb)
    add_executable(test_spatialdb
                    tests/test_Region.cpp
                    tests/test_Point.cpp
                    tests/test_Automaton.cpp
                    tests/test_AutomatonFactory.cpp
                    tests/test_SpatialModel.cpp
                    tests/test_RegionFactory.cpp)
    add_library(spatialdb STATIC ${PROJECT_SOURCE_FILES})
    target_link_libraries(test_spatialdb spatialdb sqlite3)
    target_link_libraries(test_spatialdb ${GTEST_BOTH_LIBRARIES})
endif(GTEST_FOUND)
