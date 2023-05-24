CC=gcc
#CFLAGS=-Wall -Werror

SRC=kruskal.c quickSort.c ../common/inputHandler.c
OBJ=$(SRC:.c=.o)
TARGET=kruskal.bin

.PHONY: all clean

all: $(TARGET)

$(TARGET): $(OBJ)
	$(CC) $(CFLAGS) -o $@ $^
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@
clean: rm -f $(OBJ) $(TARGET)
