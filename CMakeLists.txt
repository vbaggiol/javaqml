cmake_minimum_required(VERSION 3.8)

project(DOtherSideJNIProject LANGUAGES C)

set(DOTHERSIDE_INCLUDE_DIR "" CACHE PATH "Path to dotherside include directory")
set(DOTHERSIDE_LIBRARY_DIR "" CACHE PATH "Path to the directory that contains the dotherside shared library")

find_package(JNI REQUIRED)

include_directories(${JNI_INCLUDE_DIRS} ${DOTHERSIDE_INCLUDE_DIR})
link_directories(${DOTHERSIDE_LIBRARY_DIR})
add_library(DOtherSideJNI SHARED DOtherSideJNI.c)
target_link_libraries(DOtherSideJNI ${JNI_LIBRARIES} DOtherSide)

file(GLOB_RECURSE JavaFiles "*.java")
add_custom_target(JavaFiles SOURCES ${JavaFiles})
