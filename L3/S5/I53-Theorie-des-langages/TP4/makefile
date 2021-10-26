CC = gcc
CFLAGS = -Wall -g

all: af

af: af.o afd.o afn.o
	$(CC) $(CFLAGS) $^ -o $@ -lm

%.o: %.c
	$(CC) -c $(CFLAGS) $< -o $@

clean:
	rm -f *.o *~
