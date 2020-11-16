cmake_minimum_required(VERSION 3.11.0)
project(linuxBase)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_C_FLAGS_RELEASE "-O3 -march=core2 -mtune=native -s -fvisibility=hidden -flto -fwhole-program -DNDEBUG")
set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_C_FLAGS_RELEASE} --no-gnu-unique -fno-rtti")

file(GLOB_RECURSE SOURCES "${CMAKE_SOURCE_DIR}/src/*.cpp")

include_directories(/usr/local/include)
link_directories(/usr/local/lib)

add_library(linuxBase SHARED ${SOURCES})
target_link_libraries(linuxBase SDL2 GL)