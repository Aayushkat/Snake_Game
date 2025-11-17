# Makefile for Snake Game on macOS
CC = gcc
CFLAGS = -Wall -Wno-deprecated-declarations
FRAMEWORKS = -framework OpenGL -framework GLUT
TARGET = snake_game
SRC = Snake.c

all: $(TARGET)

$(TARGET): $(SRC)
	$(CC) $(CFLAGS) $(SRC) -o $(TARGET) $(FRAMEWORKS)

clean:
	rm -f $(TARGET)

run: $(TARGET)
	./$(TARGET)

.PHONY: all clean run
