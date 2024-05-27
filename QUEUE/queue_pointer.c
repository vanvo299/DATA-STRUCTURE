#include <stdio.h>
#include <stdlib.h>

struct ElementType{
    int value;
};

struct Node {
    struct ElementType val;
    struct Node *next;
};
typedef struct Node *Node;

struct queue {
    Node front, rear; // front: phan tu dau queue, rear: phan tu cuoi queue
    int size;
};

typedef struct queue *queue;

// tạo một Queue
queue createQueue()
{
    queue q = malloc(sizeof(struct queue));
    q->front = q->rear = NULL;
    q->size = 0;
    return q;
}

// Kiểm tra Queue có rỗng hay không
int is_empty(queue q)
{
    return q->size == 0;
}

// Tạo một node mới trong Queue
Node makeNode(struct ElementType x)
{
    Node newItem = malloc(sizeof(struct Node));
    newItem->val = x;
    newItem->next = NULL;
    return newItem;
}

// Thêm Phần tử vào Queue
void Push(queue q, struct ElementType x)
{
    Node P = makeNode(x);
    if(is_empty(q)) {
        q->front = q->rear = P;
    } else {
        q->rear->next = P;
        q->rear = P; 
    }
    q->size++;
}

// Xóa phần tử ở cuối Queue
void pop(queue q)
{
    if (is_empty(q)) {
        printf("The queue is empty !!!\n");
        return;
    }
        Node tmp = q->front;
        if (q->size == 1) {
            q->front = q->rear = NULL;
            q->size--;
            free(tmp);
        } else {
            q->front = tmp->next;
            q->size--;
            free(tmp);
        }
}

// In các phần tử có trong Queue
void show_queue(queue q)
{
    if (is_empty(q)) printf("The queue is empty. You cannot print !!\n");
    else {
        printf("The current state of the queue is: ");
        Node current = q->front;
        while(current != NULL) {
            printf("%d ", current->val.value);
            current = current->next;
        }
        printf("\n");
    }
}
int main()
{
    queue a = createQueue();
    struct ElementType a1, a2, a3, a4, a5;

    a1.value = 12;
    a2.value = 15;
    a3.value = 21;
    a4.value = -16;
    a5.value = 8;

    Push(a, a1);
    Push(a, a2);
    Push(a, a3);
    Push(a, a4);
    Push(a, a5);

    show_queue(a);

    pop(a);
    show_queue(a);

    free(a);
    return 0;
}