CC = mpicc
CFLAGS = -Wall -O2

all: ping_pong

ping_pong: ping_pong.c
	$(CC) $(CFLAGS) -o ping_pong ping_pong.c

clean:
	rm -f ping_pong

run: ping_pong
	@echo "Running ping-pong with 2 processes:"
	@mpirun -np 2 ./ping_pong
	@echo ""
	@echo "Running ping-pong with 4 processes:"
	@mpirun -np 4 ./ping_pong

.PHONY: all clean run
