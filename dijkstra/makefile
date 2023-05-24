CC=gcc
#CFLAGS=-Wall -Werror

SRC=dijkstra.c ../prim/inputHandler.c ../prim/heap.c
OBJ=$(SRC:.c=.o)
TARGET=dijkstra.bin

.PHONY: all clean

all: $(TARGET)

$(TARGET): $(OBJ)
	$(CC) $(CFLAGS) -o $@ $^
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@
clean: rm -f $(OBJ) $(TARGET)
