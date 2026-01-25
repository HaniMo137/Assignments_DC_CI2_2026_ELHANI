CC = gcc
CFLAGS = -Wall -Wextra
TARGET = instruction_schedule

all: $(TARGET)_O0 $(TARGET)_O2

$(TARGET)_O0: instruction_schedule.c
	$(CC) $(CFLAGS) -O0 -o $@ $<

$(TARGET)_O2: instruction_schedule.c
	$(CC) $(CFLAGS) -O2 -o $@ $<

clean:
	rm -f $(TARGET)_O0 $(TARGET)_O2

.PHONY: all clean
