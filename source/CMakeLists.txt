cmake_minimum_required(VERSION 3.5)
project (BarCharRace VERSION 1.0.0 LANGUAGES CXX )

set(CMAKE_EXPORT_COMPILE_COMMANDS 1)

# include_directories( "core" "libs" )
set ( APP_NAME "bcr")
add_executable( bcr "main.cpp" "rsc/animation_manager.cpp" "rsc/database.cpp" )
target_include_directories(${APP_NAME} PUBLIC ${CMAKE_SOURCE_DIR}/libs)
target_compile_features( ${APP_NAME} PUBLIC cxx_std_17 )
target_compile_options( ${APP_NAME} PRIVATE -Wall -pedantic -g)
