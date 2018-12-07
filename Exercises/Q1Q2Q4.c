// Q1Q2.c [180924]
// Code for questions 1 and 2 from exercise 1.

#include	<stdio.h>
#include	<malloc.h>

typedef int *IntegerPointer;


void P_Q1(void)
{
	IntegerPointer	A, B;
	A = (IntegerPointer)malloc(sizeof(int));
	B = (IntegerPointer)malloc(sizeof(int));
	*A = 19;
	*B = 5;
	A = B;
	*B = 7;
	printf("%d\n", *A);
}

void P_Q2 ( void )
{
	int	*A, *B;
	A = (int *)malloc(sizeof(int));
	B = (int *)malloc(sizeof(int));
	*A=19;
	*B=5;
	*A = *B;
	*B = 7;
	printf("%d  %d\n",*A, *B);
}

void P_Q4 (void)
{
	int	*pA;
	int	tmp;
	pA = NULL;
	printf ("Can we read the location?\n");
	tmp = *pA;
	printf ("Address NULL seems to contain %08ld\n", tmp);

	printf ("Can we write it?\n");
	*pA = 42;		// NOT GOOD!
	*pA = tmp;		// restore what was there
	printf ("Seems to have worked\n");
	printf ("Value is: %d\n", *pA);
}



void main (void)
{
	printf ("Output P_Q1\n");
	P_Q1();
	printf ("Output P_Q2\n");
	P_Q2();
	printf ("Output P_Q4\n");
	P_Q4();
}
