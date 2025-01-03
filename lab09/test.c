#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <time.h>

void main()
{
	clock_t begin = clock();

	while(time(clock_t) < 10){
		printf("%d\n", time(clock_t));
	}

	clock_t end = clock();
	double time_spent = (double)(end - begin) / CLOCKS_PER_SEC;
}