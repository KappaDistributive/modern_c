cmake_minimum_required(VERSION 3.20)
project(Modern_C)

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall -Werror")
set(CMAKE_SHARED_LINKER_FLAGS "-lm")

add_executable(challenge_1 src/challenge_1.c)
add_executable(challenge_2 src/challenge_2.c)
target_link_libraries(challenge_2 PRIVATE m)

add_executable(challenge_4 src/challenge_4.c)
add_executable(challenge_5 src/challenge_5.c)
target_link_libraries(challenge_5 PRIVATE m)

add_executable(challenge_6 src/challenge_6.c)
