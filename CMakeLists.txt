cmake_minimum_required(VERSION 3.23)
project(Modern_C)

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall -Werror")

add_executable(challenge_1 src/challenge_1.c)
add_executable(challenge_2 src/challenge_2.c)

add_executable(challenge_4 src/challenge_4.c)
add_executable(challenge_5 src/challenge_5.c)
