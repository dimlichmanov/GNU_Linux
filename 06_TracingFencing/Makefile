GENERATES = wrap.so move

wrap.so: unlink_wrapper.c
	cc -shared -fPIC unlink_wrapper.c -o $@

move: move.c
	cc move.c -O0 -o $@

run: move
	./move input_PROTECT output_text

run_wrapped: move wrap.so
	LD_PRELOAD=./wrap.so ./move input_PROTECT output_text

clean:
	rm $(GENERATES)