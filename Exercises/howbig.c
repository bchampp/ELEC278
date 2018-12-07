// HowBig.c [180923]

#include	<stdio.h>
#include	<malloc.h>


void mallocFailureTest(void)
// Keep allocating memory until a failure occurs
{
	int	size;
	unsigned char	*p;

	for (size = 1000; ;size = size << 1)	{
		printf ("Try %10d: ", size);
		p = (unsigned char *) malloc (size);
		if (p == NULL)	{
			printf ("FAIL\n");
			return;
			}
		printf ("SUCCESS  address: %12x\n", p);
		free (p);
		}
}

void main (void)
{
	mallocFailureTest();
}
