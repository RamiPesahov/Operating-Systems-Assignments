CC = gcc
CFLAGS = -Wall -Wextra -g

TARGET = hw1shell

all: $(TARGET)

$(TARGET): main.c
	$(CC) $(CFLAGS) -o $(TARGET) shell.c

# Rule to clean up build artifacts
clean:
	rm -f $(TARGET)