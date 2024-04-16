#include <stdio.h>
#include <stdlib.h>

struct ElementType {
    int value;
};

struct Node {
    struct ElementType e;
    struct Node *next;
};

typedef struct Node *Stack;
typedef struct Node *StackNode;

// ham tao mot stack moi
Stack create_stack()
{
    Stack S = malloc(sizeof(struct Node));
    S->next = NULL;
    return S;
}

// kiem tra xem stack co rong khong
int is_empty(Stack S)
{
    if (S == NULL) {
        printf("you must use create_stack function first\n");
        return 1;
    }
    else return S->next == NULL;
}

void make_null(Stack S)
{
    if (S == NULL) {
        printf("you must use create_stack function first\n");
        return;
    }
    else S->next = NULL;
}

void push(Stack *S, struct ElementType e)
{
    Stack newStack = malloc(sizeof(struct Node));
    newStack->e = e;
    newStack->next = (*S)->next;
    (*S)->next = newStack;
}

void pop(Stack S)
{
    if (!is_empty(S)) {
        StackNode topNode = S->next;
        S->next = S->next->next;
        free(topNode);
    }
}

StackNode Top(Stack S)
{
    if (is_empty(S)) {
        printf("The stack is empty!!!\n");
    } else {
        return S->next;
    }
}

void show_stack(Stack S)
{
    
    if (is_empty(S)) {
        printf("The stack is empty!!!\n");
    } else {
        S = S->next;
        printf("The current state of the stack is: ");
        while(S != NULL) {
            printf("%d ", S->e.value);
            S = S->next;
            }
    }
    printf("\n");
}
int main()
{
    Stack a = create_stack();
    struct ElementType a1, a2, a3, a4, a5;

    a1.value = 1;
    a2.value = 2;
    a3.value = 3;
    a4.value = 4;
    a5.value = 5;


    push(&a, a1);
    push(&a, a2);
    push(&a, a3);
    push(&a, a4);
    push(&a, a5);
    show_stack(a);

    pop(a);
    show_stack(a);
    return 0;
}