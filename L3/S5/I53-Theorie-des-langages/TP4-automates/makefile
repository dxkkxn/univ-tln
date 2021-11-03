CC = gcc
CFLAGS = -Wall -g

mygrep: mygrep.o compregrex.o
	$(CC) $(CFLAGS)	$^ -o $@ -lm

af: af.o afd.o afn.o compregrex.o
	$(CC) $(CFLAGS) $^ -o $@ -lm

%.o: %.c
	$(CC) -c $(CFLAGS) $< -o $@

clean:
	rm -f *.o *~
