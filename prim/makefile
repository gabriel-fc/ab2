CC=gcc
#CFLAGS=-Wall -Werror

SRC=prim.c ../common/inputHandler.c ../common/heap.c
OBJ=$(SRC:.c=.o)
TARGET=prim.bin

.PHONY: all clean

all: $(TARGET)

$(TARGET): $(OBJ)
	$(CC) $(CFLAGS) -o $@ $^
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@
clean: rm -f $(OBJ) $(TARGET)
