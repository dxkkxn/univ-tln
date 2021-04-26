plot for [col=1:2] '../TP8-heap-sort/tri_tas' using 0:col with lines title columnheader;
set key autotitle columnhead;
replot 'counting_sort.txt' with lines ;
pause -1;

