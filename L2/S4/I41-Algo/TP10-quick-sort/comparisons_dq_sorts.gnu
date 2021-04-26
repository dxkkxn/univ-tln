set key autotitle columnheader
plot "quicksort.txt" with lines
replot "quicksortv2.txt" with lines
replot "quicksortv3.txt" with lines
replot for [col=1:1] "../TP9-merge-sort/tri_fusion" using col with lines title columnheader
replot for [col=1:2] '../TP8-heap-sort/tri_tas' using 0:col with lines title columnheader;
pause -1;

