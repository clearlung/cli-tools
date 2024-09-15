CC = gcc
CFLAGS=-Wall -Wpedantic -I$(INC_DIR)

INC_DIR = include
SRC_DIR = src

DEPS = $(wildcard $(INC_DIR)/*.h)
SRC = $(wildcard $(SRC_DIR)/*.c)

$(SRC_DIR)/main: $(SRC_DIR)/main.c $(DEPS)
	$(CC) -o main $(SRC) $(CFLAGS)
