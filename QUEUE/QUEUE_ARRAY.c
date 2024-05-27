// Queue 
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <math.h>


struct ElementType{
    int value;
};

struct Queue {
    unsigned int capacity;
    int count; // so luong phan tu co trong queue
    int front, rear;
    struct ElementType *arrayQueue;
};

typedef struct Queue *Queue;

// tao queue
Queue createQueue(unsigned int capacity)
{
    Queue q = malloc(sizeof(struct Queue));
    if (q == NULL) {
        printf("Not enough memory !\n");
        return NULL;
    }
  
    q->arrayQueue = malloc(sizeof(struct ElementType) * capacity);

    if (q->arrayQueue == NULL) {
        printf("Not enough memory\n");
        return NULL;
    }
    q->capacity = capacity;
    q->count = 0;
    q->front = 0;
    q->rear = -1;
    return q;
}

// kiem tra xem queue co rong khong
int is_empty(Queue q)
{
    return q->count == 0;
}

// Kiểm tra xem Queue co full khong
int is_full(Queue q)
{
    return q->count == q->capacity;
}

// Bien mot Queue thanh Queue rong
int reset(Queue q) 
{
    q->count = 0;
    q->rear = -1;
    q->front = 0;
}

// Thêm phần tử vào Queue
void enQueue(Queue q, struct ElementType e)
{
    if (is_full(q)) {
        printf("The queue is full\n");
        return;
    }
    q->rear = (q->rear + 1) % q->capacity;
    q->arrayQueue[q->rear] = e;
    q->count++;
}

// Lấy phần tử từ Queue ra ngoài
struct ElementType deQueue(Queue q)
{
    if (is_empty(q)) {
        printf("The queue is empty !!\n");
        struct ElementType e;
        e.value = INT_MIN;
        return e;
    }
    struct ElementType item = q->arrayQueue[q->front];
    q->front = (q->front + 1) % q->capacity;
    q->count--;
    return item;
}

// in phần tử trong Queue 
void showQueue(int index, Queue q) {
    
    if (is_empty(q)) {
        printf("The queue is empty. You cannot print the queue.\n");
        return;
    }
    
    if (index == q->rear) {
        printf("%d ", q->arrayQueue[index].value);
    } else {
        showQueue((index + 1) % q->capacity, q);
        printf("%d ", q->arrayQueue[index].value);
    }
}

// In phan tu duoc lay ra
void printDeQueue(Queue q)
{
    int x = deQueue(q).value;
    if (x != INT_MIN) printf("DeQueue: %d\n", x);
}
int main()
{
    Queue q = createQueue(100);
    struct ElementType q1, q2, q3, q4, q5;
    
    q1.value = 2;
    q2.value = 4;
    q3.value = 1;
    q4.value = 3;

    enQueue(q, q1);
    enQueue(q, q2);
    enQueue(q, q3);
    enQueue(q, q4);

    printf("The current state of the queue is: ");
    showQueue(q->front,q);
    printf("\n");
    
    printDeQueue(q);
    printDeQueue(q);
    printDeQueue(q);
    printDeQueue(q);
    printDeQueue(q);


    return 0;
}