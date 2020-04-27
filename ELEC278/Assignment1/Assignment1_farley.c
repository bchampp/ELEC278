#include <stdio.h>
#include <stdlib.h>
#include <math.h>

typedef struct Node {
	double coef;
	int exp;
	struct Node *next;
} Node;

Node *head;

//Gets the degree of the polynomial
int getDegree() {
	return head->exp;
}

//Gets the ith coefficient, this function assumes i is the exponent
double getCoefficient(int i) {
	if (i > getDegree()) { //return 0 if i is greater than the degree of the polynomial
		return 0;
	}
	
	Node *cur = head; //loop through the nodes until you reach the desired one
	for (int n = 0; n < (head->exp - i); n++) {
		cur = cur->next;
	}
	return cur->coef; //return the coefficient
}

//Sets the ith coefficient to c, this function assumes i is the exponent
void setCoefficient(int i, double c) {
	if (i > getDegree()) { //return 0 if i is greater than the degree of the polynomial
		return;
	}
	
	Node *cur = head; //loop through the nodes until you reach the desired one
	for (int n = 0; n < (head->exp - i); n++) {
		cur = cur->next;
	}
	cur->coef = c; //set the coefficient
}

//Sets the current polynomial to be p
void assign(Node *p) {
	head = p;
}

//Adds the polynomial 'p' to the current one and returns a new polynomial
Node *plus(Node *p) {
	Node *out = (Node *)malloc(sizeof(Node)); //create the list that will be outputted
	Node *cur = out;
	
	Node *cur0 = head; //the current list
	Node *cur1 = p;	//the inputted list
	
	int biggest = getDegree(); //checking highest degree to go to
	if (biggest < p->exp)
		biggest = p->exp;
	for(int i = 0; i <= biggest; i++) { //for every term with degree biggest-i...
		cur->exp = biggest - i; //set exponent
		cur->coef = 0;
		if (biggest-i <= cur0->exp) { //add coeff if the current polynomial has a term here, advance term if so
			cur->coef += cur0->coef;
			cur0 = cur0->next;
		}
		if (biggest-i <= cur1->exp) { //add coeff if the given polynomial has a term here, advance term if so
			cur->coef += cur1->coef;
			cur1 = cur1->next;
		}
		cur->next = (Node *)malloc(sizeof(Node)); //allocated new memory for the next node in the output list
		if (i != biggest) //set the cur var to move forward if not the last
			cur = cur->next;
	}
	cur->next = NULL; //set the next val of the last Node to NULL in the list
	
	return out; //return the created list
}


//Subtracts the polynomial 'p' from the current one and returns a new polynomial
Node *minus(Node *p) {
	Node *out = (Node *)malloc(sizeof(Node)); //create the list that will be outputted
	Node *cur = out;
	
	Node *cur0 = head; //the current list
	Node *cur1 = p;	//the inputted list
	
	int biggest = getDegree(); //checking highest degree to go to
	if (biggest < p->exp)
		biggest = p->exp;
	for(int i = 0; i <= biggest; i++) { //for every term with degree biggest-i...
		cur->exp = biggest - i; //set exponent
		cur->coef = 0;
		if (biggest-i <= cur0->exp) { //add coeff if the current polynomial has a term here, advance term if so
			cur->coef += cur0->coef;
			cur0 = cur0->next;
		}
		if (biggest-i <= cur1->exp) { //subtract coeff if the given polynomial has a term here, advance term if so
			cur->coef -= cur1->coef;
			cur1 = cur1->next;
		}
		cur->next = (Node *)malloc(sizeof(Node)); //allocated new memory for the next node in the output list
		if (i != biggest) //set the cur var to move forward if not the last
			cur = cur->next;
	}
	cur->next = NULL; //set the next val of the last Node to NULL in the list
	
	return out; //return the created list
}

//Multiply the polynomial 'p' with the current one and returns a new polynomial
Node *times(Node *p) {
	Node *out = (Node *)malloc(sizeof(Node)); //create the list that will be outputted
	Node *cur = out;
	
	Node *cur0 = head; //the current list
	Node *cur1 = p;	//the inputted list
	
	int size = getDegree() * p->exp; //initalize the output list completely
	while (size >= 0) {
		cur->exp = size--;
		cur->coef = 0;
		cur->next = (Node *)malloc(sizeof(Node));
		if (size > 0)
			cur = cur->next;
	}
	cur->next = NULL;
	
	for(int i = 0; i <= getDegree(); i++) { //for every term in the current polynomial...
		cur = out;
		cur1 = p;
		for(int n = 0; n <= p->exp; n++) { //loop through the other polynomial 'p' and multiply the 2 nodes, add the result into the out list
			int exp = (getDegree() - i) * (cur1->exp); //get what exp will be generated
			while (cur->exp > exp) //go to that node in the out list
				cur = cur->next;
			cur->coef += cur0->coef * cur1->coef; //add the product of the 2 nodes coeffs
			cur1 = cur1->next; //move on
		}
		cur0 = cur0->next;
	}
	
	return out; //return the created list
}

//Evaluates the polynomial for a certain value x and returns a new list
double eval(double x) {
	double out = 0;
	Node *cur = head;
	
	for (int i = 0; i <= getDegree(); i++) { //loop through every node in list and evaluate while adding to out
		out += cur->coef * pow(x, cur->exp);
		cur = cur->next;
	}
	
	return out; //return the created list
}

//Calculates the derivative of the current list and returns it in a new list
Node *getDerivative() {
	Node *out = (Node *)malloc(sizeof(Node));
	Node *cur = out;
	Node *cur0 = head;
	
	for (int i = 0; i < getDegree(); i++) { //loop through every node in current but last, set the output list nodes based on derivative rules
		cur->exp = cur0->exp-1;
		cur->coef = cur0->exp * cur0->coef;
		if (i < getDegree() - 1) {
			cur->next = (Node *)malloc(sizeof(Node));
			cur = cur->next;
		}
		cur0 = cur0->next;
	}
	
	return out; //return the created list
}

//Displays the polynomial 'node'
void display(Node *node) {
	printf("Polynomial: ");
	
	Node *cur = node;
	for (int i = 0; i <= node->exp; i++) {
		if (i != node->exp)
			printf("%0.3f*x^%d + ", cur->coef, cur->exp);
		else
			printf("%0.3f", cur->coef);
		cur = cur->next;
	}

	printf("\n");
}

int main() {
	head = (Node *)malloc(sizeof(Node));
	Node *cur = head;
	for (int i = 0; i <= 3; i++) { //initalize the current node
		cur->exp = 3-i;
		cur->coef = 0;
		if (i != 3) {
			cur->next = (Node *)malloc(sizeof(Node));
			cur = cur->next;
		} else 
			cur->next = NULL;
	}
	
	setCoefficient(3, 1);
	setCoefficient(2, 1);
	setCoefficient(1, 1);
	setCoefficient(0, 1);
	
	display(head);
	printf("f(%0.2f) = %f\n", 2.0, eval(2.0));
	
	Node *old = head;
	head = getDerivative();
	display(head);
	printf("f'(%0.2f) = %f\n", 2.0, eval(2.0));
	
	head = plus(old);
	display(head);
	printf("f'(%0.2f) + f(%0.2f) = %f\n", 2.0, 2.0, eval(2.0));
	
	
	return 0;
}