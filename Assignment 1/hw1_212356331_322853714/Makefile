CC = gcc
CFLAGS = -Wall -Wextra -g

TARGET = hw1shell
SRCS = shell.c parser.c
HDRS = shell.h

all: $(TARGET)

$(TARGET): $(SRCS) $(HDRS)
	$(CC) $(CFLAGS) -o $(TARGET) $(SRCS)

# Rule to clean up build artifacts
clean:
	rm -f $(TARGET)