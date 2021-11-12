cmake_minimum_required(VERSION 3.16)

set(PROJECT_NAME rhasher)
project(${PROJECT_NAME})
set (CMAKE_C_STANDARD  11)


include_directories(/home/dlichman/RHash/librhash)
add_executable(rhasher Source/rhasher.c)
target_link_libraries(rhasher /home/dlichman/RHash/librhash/librhash.so)