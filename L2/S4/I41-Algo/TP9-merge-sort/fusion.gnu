plot for [col=1:1] "tri_fusion" using col with lines title columnheader
replot for [col=1:3] '../TP7-tris-empiriques/tris_imp' using 0:col with lines title columnheader 
replot for [col=1:2] '../TP8-heap-sort/tri_tas' using 0:col with lines title columnheader;
pause -1;

