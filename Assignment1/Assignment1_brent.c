#include <stdio.h>

double dipower (double x, int exp)
{
    int isneg = (exp < 0);
    double rslt = 1.0;
    int count;
    if (isneg) exp = -exp;
    for(count = 1; count <= exp; count++)
        rslt = rslt*x;
    if (isneg) rslt = 1/rslt;
    return rslt;
}

typedef struct polynomial
{
    struct poly *next; //link to next term 
    int exp; //exponent value
    double mult; //factor value -> a
} poly, *poly; 

poly *newTerm(int exponent, double coef)
/* Create new polyterm node. Return NULL if no term created
return pointer to polyterm if malloc works. If created, exp and
factor fields are initialized */
{
    poly *temp = (poly*)malloc(sizeof(poly));
    if (temp != NULL){
        temp -> next = NULL;
        temp -> exp = exponent;
        temp -> mult = coef;
    }
    return temp;
}//newTerm()

typedef struct node 
{
    double coef;
    int exp; 
    Node* next; 

} Node; 

void setCoefficient(); 
//this functino is used to set the coefficients of a polynomial. It takes two arguments, i, c.
// sets the value of A_i, the I^th coefficient, to C


double getCoefficient(int i);
int getDegree();
void assign (Node *p);
Node *plus(Node *p);
Node *minus(Node *p);
Node *times(Node *p);
double eval(double x);
Node *getDerivative();
void display(Node *node);

int main(){
    
    float x; 
    float y = 2*x;
    x = 5; 
    printf("%f", x);
    
}

void setCoefficient(float i, float c);
