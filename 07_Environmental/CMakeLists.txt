cmake_minimum_required(VERSION 3.16)
set (RHASH_PATH /home/dlichman/RHash/librhash/)

set(PROJECT_NAME rhasher)
project(${PROJECT_NAME})
set (CMAKE_C_STANDARD  11)
include_directories(headers/)

find_library(RHASH
        NAMES rhash
        HINTS ${RHASH_PATH}
        REQUIRED
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

enable_testing()

add_test(NAME test_sha1
        COMMAND sh -c "sha1sum in.txt | head -n1 | awk '{print $1;}' > out_util.txt && ./rhasher < in.txt > out_app.txt && cmp out_util.txt out_app.txt"
        )

add_test(NAME test_md5
        COMMAND sh -c "md5sum in_5.txt | head -n1 | awk '{print $1;}' > out_util.txt && ./rhasher < in_5.txt > out_app.txt && cmp out_util.txt out_app.txt"
        )

add_custom_target(clean-cmake-files
        COMMAND sh -c "rm -r build/"
        )