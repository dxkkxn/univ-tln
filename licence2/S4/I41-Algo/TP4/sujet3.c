#include <stdio.h>
#include <stdlib.h>

int main()
{
	int exp[12] = {10,50,100,500,1000,5000,10000,50000,100000,500000,1000000,5000000}
	for(int i = 0; i < 12; i++)
	{
		execl("./", "seconds.sh", "./sujet1", exp[i]);
		execl("./", "seconds.sh", "./sujet2", exp[i]);	 
	}
}
