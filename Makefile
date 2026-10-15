CC = gcc
CFLAGS = -std=c11 -Wall -Wextra -pedantic
TARGET = line_editor

all: $(TARGET)

$(TARGET): line_editor.c
	$(CC) $(CFLAGS) line_editor.c -o $(TARGET)

clean:
	rm -f $(TARGET) $(TARGET).exe
