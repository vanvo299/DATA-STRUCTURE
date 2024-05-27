// Ứng dụng Hash làm từ điển (Simple Dictionary)
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define HASH_SIZE 10 
#define MAX_LENGTH 20

struct Node {
    char word[MAX_LENGTH];
    struct Node *next;
};

typedef struct Node *Node;

Node hashTable[HASH_SIZE];


int hashString(const char a[])
{
    int i = 0;
    int j = 9;
    while(a[i] != '\0') {
        j = (31 * j + a[i]) % HASH_SIZE;
        i++;
    }
    return j;
}

void insert(char *word)
{
    int index = hashString(word);
    Node tmp = malloc(sizeof(struct Node));
    tmp->next = NULL;
    strcpy(tmp->word, word);
    if (hashTable[index] == NULL) {
        hashTable[index] = tmp;
    } else {
        tmp->next = hashTable[index];
        hashTable[index] = tmp;
    }
}

int check(char *word)
{
    int index = hashString(word);
    Node current = hashTable[index];
    while (current != NULL) {
        if (strcmp(current->word, word) == 0) {
            printf("%s \n", word);
            return 1;
        }
        current = current->next;
    }
    printf("Not found !!\n");
    return 0;
}
int main()
{
    char apple[] = "Qua tao";
    char cow[] = "Con bo";
    char computer[] = "May tinh";
    insert(apple);
    insert(cow);
    insert(computer);
    
    check(apple);
    check(cow);
    check(computer);
    return 0;
}