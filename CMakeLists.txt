cmake_minimum_required(VERSION 3.20)
project(Modern_C)
set(CMAKE_CXX_STANDARD 20)

message(STATUS "Build type: ${CMAKE_BUILD_TYPE}")
set(CMAKE_CXX_FLAGS "${CMAKE_C_FLAGS} -Wall -Wextra")
set(CMAKE_CXX_FLAGS_DEBUG "-g -O0 -DDEBUG")
set(CMAKE_CXX_FLAGS_RELEASE "-O3 -DNDEBUG")
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall -Werror")
set(CMAKE_SHARED_LINKER_FLAGS "-lm")

add_library(list src/utils/list.c)


add_executable(challenge_1 src/challenge_1.c)
add_executable(challenge_2 src/challenge_2.c)
target_link_libraries(challenge_2 PRIVATE m)

add_executable(challenge_4 src/challenge_4.c)
add_executable(challenge_5 src/challenge_5.c)
target_link_libraries(challenge_5 PRIVATE m)

add_executable(challenge_6 src/challenge_6.c)


add_executable(tmp src/tmp.c)
target_link_libraries(tmp list)
