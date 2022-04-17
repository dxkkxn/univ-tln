CFLAGS = -Wall -Wextra -g
main_optimized.exe: optimized_main.c main.exe
	gcc $(CFLAGS) optimized_main.c -lm -o opti_main.exe
main.exe: main.c
	gcc $(CFLAGS) main.c -lm -o main.exe
