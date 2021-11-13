cmake_minimum_required(VERSION 3.16)
set (RHASH_PATH /home/dlichman/RHash/librhash/)

set(PROJECT_NAME rhasher)
project(${PROJECT_NAME})
set (CMAKE_C_STANDARD  11)
include_directories(headers/)

find_library(RHASH
        NAMES rhash
        HINTS ${RHASH_PATH}
        )

include_directories(${RHASH_PATH})
add_executable(rhasher source/rhasher.c)

option(USE_GET "Use getline from string.h" ON)

if (USE_GET)
    add_library(newline_get libs/newline_get.c)
    target_link_libraries(rhasher ${RHASH} newline_get)
    target_compile_definitions(rhasher PRIVATE GET=1)
else()
    set (READLINE_PATH /usr/include/readline/)
    include_directories(${READLINE_PATH})
    find_library(READLINE
            NAMES readline
            HINTS /lib/x86_64-linux-gnu/)
    add_library(newline_read libs/newline_read.c)
    target_link_libraries(newline_read ${READLINE})
    target_link_libraries(rhasher ${RHASH} newline_read)
    target_compile_definitions(rhasher PRIVATE READ=1)
endif()
