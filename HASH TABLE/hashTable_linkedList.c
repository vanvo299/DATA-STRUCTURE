// HASH TABLE - Xử lí va chạm bằng LinkedList

#include <stdio.h>
#include <stdlib.h>

#define HASH_SIZE 11

struct Node {
    int value;
    struct Node *next;
};

typedef struct Node Node;

Node *hashTable[HASH_SIZE];

int hash_function(int data)
{
    return data % HASH_SIZE;
}

void insert(int data)
{
    int index = hash_function(data);
    Node *tmp = malloc(sizeof(struct Node));
    tmp->value = data;
    tmp->next = NULL;
    if (hashTable[index] == NULL) {
        hashTable[index] = tmp;
        return;
    }
    tmp->next = hashTable[index];
    hashTable[index] = tmp;
}

int find(int data)
{
    int index = hash_function(data);
    Node *current = hashTable[index];
    while(current != NULL) {
        if (current->value == data) return 1;
        current = current->next;
    }
    return 0;
}
int main()
{
    insert(21);
    insert(13);
    insert(2);
    int check = find(13);
    printf("%d ", check);

    return 0;
}