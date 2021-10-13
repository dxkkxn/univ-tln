SHELL=/bin/bash
compte_rendu.tex:
	pdflatex compte_rendu.tex
timing0x.png:
	for i in {1..3}; do \
		gcc -O$$i crible.c -o crible.exe;\
		for n in {10..28}; do \
			./crible.exe -t -l $$n >> timingO$$i.dat;\
		done; \
	done; \
	gnuplot timingOx.plot;

timing.png : timing.dat timing.plot
	gnuplot timing.plot

timing.dat :
	for n in {10..28}; do ./crible.exe -t -l $$n >> timing.dat;  done  

pi.png: data.dat data.plot
	gnuplot data.plot
data.dat: crible.exe
	./crible.exe -p100 -l10 | tr -d 'pi()' | tr '=' ' ' > data.dat
crible.exe: crible.c
	gcc crible.c -o crible.exe

