
all: main.c list.c
	$ gcc -o list list.c main.c

clean:
	rm list