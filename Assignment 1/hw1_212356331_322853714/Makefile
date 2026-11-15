CC = gcc
CFLAGS = -Wall -Wextra -g

hw1shell: shell.o parser.o commands.o
	$(CC) $(CFLAGS) -o hw1shell shell.o parser.o commands.o

shell.o: shell.c shell.h
	$(CC) $(CFLAGS) -c shell.c

parser.o: parser.c shell.h
	$(CC) $(CFLAGS) -c parser.c

commands.o: commands.c shell.h
	$(CC) $(CFLAGS) -c commands.c

clean:
	rm -f hw1shell *.o