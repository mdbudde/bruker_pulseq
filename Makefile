# Makefile to compile and run loadseqtest.c with LoadSequence.c

CC = gcc
CFLAGS = -Wall -Wextra -O2 -std=c99
TARGET = loadseqtest
SRC = loadseqtest.c PulseqInterpreter.c

all: $(TARGET)

$(TARGET): $(SRC)
	$(CC) $(CFLAGS) -o $(TARGET) $(SRC)

clean:
	rm -f $(TARGET)

.PHONY: all clean