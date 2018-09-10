cmake_minimum_required(VERSION 3.8)

project(DOtherSideJNIProject LANGUAGES C)

find_package(JNI REQUIRED)

include_directories(${JNI_INCLUDE_DIRS})
add_library(DOtherSideJNI SHARED DOtherSideJNI.c)
target_link_libraries(DOtherSideJNI ${JNI_LIBRARIES} DOtherSide)

file(GLOB_RECURSE JavaFiles "*.java")
add_custom_target(JavaFiles SOURCES ${JavaFiles})
