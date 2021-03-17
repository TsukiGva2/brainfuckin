cmake_minimum_required(VERSION 3.10)

project(Brainfuckin C)

add_executable(Brainfuckin brainfuckin.c)

INCLUDE (CheckIncludeFiles)

CHECK_INCLUDE_FILES (unistd.h USE_UNISTD_H)
CHECK_INCLUDE_FILES (windows.h USE_WINDOWS_H)
CONFIGURE_FILE(${CMAKE_CURRENT_SOURCE_DIR}/config.h.in ${CMAKE_CURRENT_BINARY_DIR}/config.h)
