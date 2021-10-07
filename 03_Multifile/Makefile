GENERATES = prog README liboutput_static.a README-a prog-a liboutput.so *.obj *-so
TRASH = *.o *~ o.*
CC = cc
.DEFAULT_GOAL = README
#.DEFAULT_GOAL = README-a
#.DEFAULT_GOAL = README-so

all:    README prog

prog:	const.o fun.o prog.o

prog-a: prog.o liboutput_static.a
	$(CC) -L. $< -loutput_static -o $@

prog-so: prog.o liboutput.so
	$(CC) -L. $< -loutput -o $@

README: prog
	./$< 2> $@

README-a: prog-a
	./$< 2> $@

README-so: prog-so
	LD_LIBRARY_PATH=`pwd` ./$< 2> $@

liboutput_static.a: fun.o const.o
	ar -rcs $@ $^

liboutput.so: fun.obj const.obj
	$(CC) -shared $^ -o $@

fun.obj: fun.c
	$(COMPILE.c) -fPIC $< -o $@

const.obj: const.c
	$(COMPILE.c) -fPIC $< -o $@

clean:
	rm -f $(TRASH)

distclean:	clean
	rm -rf $(GENERATES)
