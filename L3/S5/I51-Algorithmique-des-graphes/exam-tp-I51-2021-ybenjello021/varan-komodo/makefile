CFLAGS=-Wall -g 
varan.exe : varan.c komodo.exe
	gcc $(CFLAGS) -o varan.exe varan.c

komodo.exe : varan.c
	gcc $(CFLAGS) -O2 -o komodo.exe varan.c
