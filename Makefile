CFLAGS=-Wall -Wextra -std=c11 -pedantic
LIBS=
execs: main.c
					$(CC) $(CFLAGS) -o exec main.c $(LIBS)
