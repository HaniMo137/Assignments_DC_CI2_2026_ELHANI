CC = gcc
CFLAGS = -Wall -Wextra -O2 -lm
TARGET = amdahl_law

all: $(TARGET)

$(TARGET): amdahl_law.c
	$(CC) $(CFLAGS) -o $@ $<

run: $(TARGET)
	./$(TARGET)

clean:
	rm -f $(TARGET)

.PHONY: all run clean
