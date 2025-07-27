cmake_minimum_required(VERSION 3.10)
project(UnixShell)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -Werror")

# List all source files
file(GLOB SOURCES "src/*.cpp")

add_executable(UnixShell ${SOURCES})