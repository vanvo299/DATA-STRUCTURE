#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define EMPTY_POS -1
#define MIN_SIZE_STACK 5
struct ElementType{
	char value;
};

struct Stack{
	unsigned int sizeStack;
	int tos;
	struct ElementType *arrayStack;
};

typedef struct Stack *Stack;

int is_empty(Stack S)
{
	return S->tos == EMPTY_POS;
}

int is_full(Stack S)
{
	return S->tos == (S->sizeStack - 1);
}

void make_empty(Stack S)
{
	S->tos = EMPTY_POS;
}

Stack createStack(unsigned int max_elements)
{
	if (max_elements < MIN_SIZE_STACK) {
		printf("The stack is too small !!!\n");
		return NULL;
	}
	Stack S = malloc(sizeof(struct Stack));
	S->tos = EMPTY_POS;
	S->sizeStack = max_elements;
	S->arrayStack = malloc(sizeof(struct ElementType) * max_elements);
	return S;
}
void push(Stack S, struct ElementType e)
{
	if (is_full(S)) {
		printf("The stack is full !!!\n");
		return;
	}
	S->arrayStack[++S->tos] = e;
}

void pop(Stack S) 
{
	if (is_empty(S)) {
		printf("The stack is empty !!!\n");
		return;
	}
	S->arrayStack[S->tos--];
}

struct ElementType top(Stack S)
{
	if (is_empty(S)) {
		printf("The stack is empty !!!\n");
	} else return S->arrayStack[S->tos];
}

void showStack(Stack S)
{
	if (is_empty(S)) {
		printf("The stack is empty\n");
		return;
	}
	printf("The current state of the stack is: ");
	for (int i = S->tos; i >= 0; i--) {
		printf("%d ", S->arrayStack[i].value);
	}
	printf("\n");
}
int main()
{
	char *a = "([i + 5 *(17 - j/(6*k))])";
	Stack s = createStack(100);
	struct ElementType open, close;
	for (int i = 0; i < strlen(a); i++) {
		if (a[i] == '(' || a[i] == '[') {
			open.value = a[i];
			push(s, open);
		}
		if (a[i] == ']') {
			if (is_empty(s) || top(s).value != '[') {
				printf("Not balanced\n");
				return 0;
			}
			pop(s);
		}
		if (a[i] == ')') {
			if (is_empty(s) || top(s).value != '(') {
				printf("Not balanced\n");
				return 0;
			}
			pop(s);
		}
	}

	if (is_empty(s)) {
		printf("Balanced\n");
	} else printf("Not balanced\n");
	return 0;
}