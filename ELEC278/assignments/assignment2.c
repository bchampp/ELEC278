#include <stdio.h>
#include <stdlib.h>	
#include <ctype.h>

typedef struct ExpressionTreeNode {
	char key;
	struct ExpressionTreeNode *left;
	struct ExpressionTreeNode *right;
} ExpressionTreeNode;

//----------Creating a basic queue library---------------
typedef struct Node {
	ExpressionTreeNode *value;
	struct Node *next;
} Node;

typedef struct Stack {
	Node *start;
} Stack;

Node *createNode(ExpressionTreeNode *val) {
	Node *out = (Node *)malloc(sizeof(Node));
	out->value = val;
	out->next = NULL;
	
	return out;
}

void push(Stack *s, ExpressionTreeNode *val) {
	Node *cur = s->start;
	if (cur == NULL)
		s->start = createNode(val);
	else {
		while (cur->next != NULL)
			cur = cur->next;
		cur->next = createNode(val);
	}
}

ExpressionTreeNode *pop(Stack *s) {
	Node *cur = s->start;
	if (cur == NULL)
		return '\0';
	else if (cur->next == NULL) {
		s->start = NULL;
		return cur->value;
	} else {
		while (cur->next->next != NULL)
			cur = cur->next;
		ExpressionTreeNode *out = cur->next->value;
		cur->next = NULL;
		return out;
	}
}
//-----------End of Queue library-----------------

ExpressionTreeNode *newTreeNode(char key) { //creates a new node using the key and return the reference to the newly created node
	ExpressionTreeNode *new = (ExpressionTreeNode *)malloc(sizeof(ExpressionTreeNode));
	new->key = key;
	new->left = NULL;
	new->right = NULL;
	
	return new;
}

_Bool isEmpty(ExpressionTreeNode *r) { //check the tree with the root, r, if it is an empty tree
	if (r == NULL) 
		return 1;
	else
		return 0;
}

char getKey(ExpressionTreeNode *r) { //return the key of the tree node, r
	return r->key;
}

_Bool isLeaf(ExpressionTreeNode *r) { //check if the tree node, r, is a leaf
	if (r->left == NULL && r->right == NULL)
		return 1;
	else
		return 0;
}

int getHeight(ExpressionTreeNode *r) { //return the height of the tree with the root of r, root layer is height 0
	if (r == NULL) { //check if the root is null, return -1 (the default level value)
		return -1;
	}
	
	int left, right; 
	left = getHeight(r->left);
	right = getHeight(r->right);
	
	if (left > right)
		return left + 1;
	else
		return right + 1;
}

ExpressionTreeNode *buildExpTree (char *postfixExp) { //creates an expression tree from a postfix expression string as the parameter and return the root of the tree
	//Algorithm is as follows:
	//Loop through every letter in the expression:
	//	if it is an operator: pop the last 2 values in the stack, make a new node, these 2 new values are the left and right children, push the new node to the stack
	//	if it is anything else: push the value to the stack as a node
	
	char operators[4] = {'+', '-', '*', '/'};
	int i = -1;
	ExpressionTreeNode *t, *t1, *t2 = NULL; //temporary values to store nodes to be appended
	
	Stack *s = (Stack *)malloc(sizeof(Stack)); //Using the stack library created above
	s->start = NULL;
	
	while (postfixExp[++i] != '\0') { //loop through every value in the string
		char cur = postfixExp[i]; //current character we are looking at
		
		//checking if cur is an operator
		_Bool oper = 0;
		for (int a = 0; a < 4; a++) 
			if (cur == operators[a])
				oper = 1;
			
		if (oper == 1) { //if it is an operator
			t = newTreeNode(cur); //make new node
			t1 = pop(s); //pop last 2 vals on stack
			t2 = pop(s);
			
			t->right = t1; //assign them accordingly
			t->left = t2;
			
			push(s, t); //push this back to the stack
		} else { //not an operator
			push(s, newTreeNode(cur)); //push it as a node
		}
	}
	
	t = pop(s); //top value of stack should be the root
	return t;
}

int priority(char x)
{
    if(x == '(')
        return 0;
    if(x == '+' || x == '-')
        return 1;
    if(x == '*' || x == '/')
        return 2;
}

char *parseInfix(char *s) { //reads an infix expression, s, and converts it to a postfix expression as a return from the function
	//Algorithm is as follows:
	//Loop through every letter in the infix expression:
	//	if it's a letter: add it to the output string
	//	if it's a open parentheses: add it to the stack
	//	if it's a close parentheses: keep looping backwards through the stack adding every value to the output string until you hit an open parentheses
	//	if it's anything else (an operator): keep looping backwards through the stack while the prority is higher than the current character
	//										 adding every value to the output string and then adding the current character to the stack once complete
	//After the loop, pop any remaining characters from the stack and add em to the output string

	char stack[50]; //a quick array stack 
	char *out = (char *)malloc(sizeof(char)*50); //output string
	int top = -1, k = 0; //top is the top of the stack, k is the current poisition in the output string
	char *e, x; //e is pointer to current character, x is a var to be used temporarily
	e = s;
	while (*e != '\0') {
		if (isalnum(*e)) //if it's a letter
			out[k++] = *e;
		else if (*e == '(') //if it's open parentheses
			stack[++top] = *e;
		else if (*e == ')') { //if it's closed parentheses
			if (top >= 0) //pop stack value into x
				x = stack[top--];
			else 
				x = -1;
			while (x != '(' || x == -1) { //while x isn't open parentheses
				out[k++] = x; //add x to the output string
				if (top >= 0) //pop next stack value to x
					x = stack[top--];
				else 
					x = -1;
			}
		} else { //if it's anyhting else (expecting an operator)
			while(priority(stack[top]) >= priority(*e)) { //keep looping while the stack has a higher prority (for order of operations)
				if (top >= 0) //pop stack value to x
					x = stack[top--];
				else 
					x = -1;
				out[k++] = x; // add it to the output string
			}
			stack[++top] = *e; //add current character to the stack
		}
		e++; //move to next character
	}
	while (top >= 0) //put all remaining stack values to output string
		out[k++] = stack[top--];
	
	return out;
}

char *parsePrefix(char *s) { //reads a prefix expression, s, and converts it to a postfix expression as a return from the function
	//Algorithm is as follows:
	//Loop through every letter in the prefix expression backwards:
	//	if its an operator: take the top 2 strings in the stack, concatenate them, and append the current character to the end of the new string, push it to the stack
	//	otherwise: push the character to the stack
	//once the loop is done, return the top value of the stack
	
	char operators[4] = {'+', '-', '*', '/'};
	int i = 0;
	char cur = s[i];
	while (cur != '\0') //get to the end of the string so we can loop backwards through it
		cur = s[++i];
	
	char *stack[50]; //stack of char pointers
	int top = -1;
	i--;
	while (i >= 0) { //loop backwards through the string
		char cur = s[i--]; //current character
		
		//Checking if cur is an operator
		_Bool oper = 0;
		for (int a = 0; a < 4; a++) 
			if (cur == operators[a])
				oper = 1;
			
		if (oper == 1) { //if it is an operator
			char *op1 = stack[top--]; //pop last 2 vals in stack
			char *op2 = stack[top--];
			char *new = (char *)malloc(sizeof(char)*50); //new string to add back
			char *e = op1, *ptr = new;
			while (*e != '\0') { //loop through first string and add every character to the new one
				*ptr = *e;
				ptr++;
				e++;
			}
			e = op2;
			while (*e != '\0') { //loop through second string and add every character to the new one
				*ptr = *e;
				ptr++;
				e++;
			}
			*ptr = cur; //add cur to the end of the new string
			ptr++;
			*ptr = '\0'; //add terminating character
			
			stack[++top] = new; //push the new string to the stack
		} else {
			char *new = (char *)malloc(sizeof(char));
			*new = cur;
			stack[++top] = new; //push cur to stack
		}
	}
	return stack[top];
}

//The next three are almost the same, the internal order of each depends on which traversal is being used
char *preorder(ExpressionTreeNode *r) { 
	char *out = (char *)malloc(sizeof(char)*50);
	if (r == NULL) {
		out[0] = '\0';
		return out;
	}
	char *ptr = out;
	*ptr = r->key;
	ptr++;
	char *left = preorder(r->left);
	char *right = preorder(r->right);
	while (*left != '\0') {
		*ptr = *left;
		ptr++;
		left++;
	}
	while (*right != '\0') {
		*ptr = *right;
		ptr++;
		right++;
	}
	*ptr = '\0';
	
	return out;
}

char *postorder(ExpressionTreeNode *r) { 
	char *out = (char *)malloc(sizeof(char)*50);
	if (r == NULL) {
		out[0] = '\0';
		return out;
	}
	char *ptr = out;
	char *left = postorder(r->left);
	char *right = postorder(r->right);
	while (*left != '\0') {
		*ptr = *left;
		ptr++;
		left++;
	}
	while (*right != '\0') {
		*ptr = *right;
		ptr++;
		right++;
	}
	*ptr = r->key;
	ptr++;
	*ptr = '\0';
	
	return out;
}

char *inorder(ExpressionTreeNode *r) { 
	char *out = (char *)malloc(sizeof(char)*50);
	if (r == NULL) {
		out[0] = '\0';
		return out;
	}
	char *ptr = out;
	char *left = inorder(r->left);
	char *right = inorder(r->right);
	while (*left != '\0') {
		*ptr = *left;
		ptr++;
		left++;
	}
	*ptr = r->key;
	ptr++;
	while (*right != '\0') {
		*ptr = *right;
		ptr++;
		right++;
	}
	*ptr = '\0';
	
	return out;
}

char *breadthfirstrecurse(ExpressionTreeNode *r) { 
	char *out = (char *)malloc(sizeof(char)*50);
	if (r == NULL) {
		out[0] = '\0';
		return out;
	}
	char *ptr = out;
	if (r->left != NULL) {
		*ptr = r->left->key;
		ptr++;
	}
	if (r->right != NULL) {
		*ptr = r->right->key;
		ptr++;
	}
	
	char *left = breadthfirstrecurse(r->left);
	char *right = breadthfirstrecurse(r->right);
	while (*left != '\0') {
		*ptr = *left;
		ptr++;
		left++;
	}
	while (*right != '\0') {
		*ptr = *right;
		ptr++;
		right++;
	}
	
	*ptr = '\0';
	
	return out;
}

char *breadthfirst(ExpressionTreeNode *r) {
	char *out = (char *)malloc(sizeof(char)*50);
	char *ptr = out;
	*ptr = r->key;
	ptr++;
	char *t = breadthfirstrecurse(r);
	while (*t != '\0') {
		*ptr = *t;
		ptr++;
		t++;
	}
	*ptr = '\0';
	return out;
}

int main() {
	ExpressionTreeNode *t = buildExpTree("ab/cd-e*+");
	printf("%s\n", preorder(t));
	printf("%s\n", postorder(t));
	printf("%s\n", inorder(t));
	printf("%s\n", breadthfirst(t));
	
	return 0;
}