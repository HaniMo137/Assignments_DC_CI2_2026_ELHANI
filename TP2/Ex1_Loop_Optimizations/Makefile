CC = gcc
CFLAGS_O0 = -O0
CFLAGS_O2 = -O2

all: unroll_O0 unroll_O2

unroll_O0: loop_unroll.c
	$(CC) $(CFLAGS_O0) -o unroll_O0 loop_unroll.c

unroll_O2: loop_unroll.c
	$(CC) $(CFLAGS_O2) -o unroll_O2 loop_unroll.c

clean:
	rm -f unroll_O0 unroll_O2