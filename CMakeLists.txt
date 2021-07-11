cmake_minimum_required(VERSION 3.11.0)
project(gamesneeze)


set(CMAKE_CXX_STANDARD 20)
set(CMAKE_C_FLAGS_DEBUG "-Wall -Wextra -O3 -march=core2 -mtune=native -fvisibility=hidden -flto -ggdb -DDEBUG")
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_C_FLAGS_DEBUG} -std=c++2a -Wall -Wextra")

string(TOLOWER $ENV{USE_CLANG} USE_CLANG)
if(USE_CLANG STREQUAL "true")
  set(CMAKE_C_COMPILER "/usr/bin/clang")
  set(CMAKE_CXX_COMPILER "/usr/bin/clang++")

  set(CMAKE_C_FLAGS_RELEASE "-W -Wall -Wextra -O3 -march=native -mtune=native -fvisibility=hidden -flto -Wl,--strip-all")
  set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_C_FLAGS_RELEASE} -fno-rtti -std=c++2a -Wall -Wextra")
else()
  set(CMAKE_C_COMPILER "/usr/bin/gcc")
  set(CMAKE_CXX_COMPILER "/usr/bin/g++")

  set(CMAKE_C_FLAGS_RELEASE "-W -Wall -Wextra -O3 -march=native -mtune=native -s -fvisibility=hidden -flto -fwhole-program -Wl,--strip-all")
  set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_C_FLAGS_RELEASE} --no-gnu-unique -fno-rtti -std=c++2a")
endif()

set(CMAKE_SHARED_LINKER_FLAGS "${CMAKE_SHARED_LINKER_FLAGS} -Wl,--no-undefined")

file(GLOB_RECURSE SOURCES "${CMAKE_SOURCE_DIR}/src/*.cpp")
list(APPEND SOURCES "${CMAKE_SOURCE_DIR}/src/core/menu/imgui/GL/gl3w.c")

include_directories(/usr/local/include)
link_directories(/usr/local/lib)

add_library(gamesneeze SHARED ${SOURCES})
target_link_libraries(gamesneeze dl pthread SDL2 GL)
