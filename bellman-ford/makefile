CC=gcc
#CFLAGS=-Wall -Werror

SRC=bellmanFord.c ../common/inputHandler.c edgeList.c
OBJ=$(SRC:.c=.o)
TARGET=bellman-ford.bin

.PHONY: all clean

all: $(TARGET)

$(TARGET): $(OBJ)
	$(CC) $(CFLAGS) -o $@ $^
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@
clean: rm -f $(OBJ) $(TARGET)
