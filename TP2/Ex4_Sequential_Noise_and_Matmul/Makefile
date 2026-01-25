CC = gcc
CFLAGS = -Wall -Wextra
TARGET = seq_noise

all: $(TARGET)_O0 $(TARGET)_O2

$(TARGET)_O0: seq_noise.c
	$(CC) $(CFLAGS) -O0 -o $@ $<

$(TARGET)_O2: seq_noise.c
	$(CC) $(CFLAGS) -O2 -o $@ $<

run_O0: $(TARGET)_O0
	./$(TARGET)_O0

run_O2: $(TARGET)_O2
	./$(TARGET)_O2

clean:
	rm -f $(TARGET)_O0 $(TARGET)_O2

.PHONY: all run_O0 run_O2 clean
