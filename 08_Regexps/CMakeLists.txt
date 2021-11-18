cmake_minimum_required(VERSION 3.16)
project(GNU_Linux C)

set(CMAKE_C_STANDARD 11)

add_executable(esub esub.c)

enable_testing()

#double slashes before pocket number required only in CMake


#RUN TESTS AFTER TARGET BUILD!

add_test(NAME test_tab
        COMMAND bash -c "./esub '(a).(b)' '\\2m\\1u\\\\\t' 'loshara arb nasd arb shfksdf' > out_util.txt && echo 'loshara arb nasd arb shfksdf' | sed -E 's/(a).(b)/\\2m\\1u\\\\\t/' > out_app.txt && cmp out_util.txt out_app.txt && rm out_app.txt && rm out_util.txt"
        )

add_test(NAME test_simple
        COMMAND bash -c "./esub 'a(.)b' '\\1' 'albania strong' > out_util.txt && echo 'albania strong' | sed -E 's/a(.)b/\\1/' > out_app.txt && cmp out_util.txt out_app.txt && rm out_app.txt && rm out_util.txt"
        )

add_test(NAME test_change
        COMMAND bash -c "./esub 'l(.).(.)x' '\\2\\1' 'i like linux' > out_util.txt && echo 'i like linux' | sed -E 's/l(.).(.)x/\\2\\1/' > out_app.txt && cmp out_util.txt out_app.txt && rm out_app.txt && rm out_util.txt"
        )


add_test(NAME test_nopockets
        COMMAND bash -c "./esub 'l...x' 'windows' 'i like linux' > out_util.txt && echo 'i like linux' | sed -E 's/l...x/windows/' > out_app.txt && cmp out_util.txt out_app.txt && rm out_app.txt && rm out_util.txt"
        )
