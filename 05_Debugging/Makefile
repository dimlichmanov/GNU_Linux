bin:
	gcc -g -o0 range.c -o range

test:
	gdb ./range -x task1.py | grep '@@@' > out1.txt
	cmp out1.txt test1.txt
	gdb ./range -x task2.py | grep '@@@' > out2.txt
	cmp out2.txt test2.txt

clean:
	rm out*
	rm range