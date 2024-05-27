#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

struct ElementType{
    int value;
};

struct heap{
    unsigned int capacity;
    unsigned int heapSize;
    struct ElementType *heapArray;
};

typedef struct heap *heap;

int parent(int i)
{
    return i / 2;
}

int leftChild(int i)
{
    return 2*i;
}

int rightChild(int i)
{
    return 2*i + 1;
}

heap createHeap(int length)
{
    heap H = malloc(sizeof(struct heap));
    if (H == NULL) {
        printf("Not enough memory\n");
        exit(1);
    }
    H->capacity = length;
    H->heapSize = 0;
    H->heapArray = malloc(sizeof(struct ElementType) * (length + 1)); // bỏ qua nút 0 
    if (H->heapArray == NULL) {
        printf("Memory allocation failed !\n");
        free(H);
        exit(1);
    }
    return H;
}


void maxHeapify(heap H, int i)
{
    int l = leftChild(i);
    int r = rightChild(i);
    int largest = i;
    if (l <= H->heapSize && H->heapArray[l].value > H->heapArray[largest].value) {
        largest = l;
    }
    if (r <= H->heapSize && H->heapArray[r].value > H->heapArray[largest].value) {
        largest = r;
    }

    // largest chứa chỉ số của phần tử lớn nhất trong nhánh
    if (largest != i) {
        struct ElementType tmp = H->heapArray[i];
        H->heapArray[i] = H->heapArray[largest];
        H->heapArray[largest] = tmp; 
        maxHeapify(H, largest);
    }
}

// Hàm bắt đầu từ các nút không phải là lá và gọi maxHeapify trên từng nút đó để đảm bảo tính chất heap tối đa.
void buildMaxHeap(heap H)
{
    H->heapSize = H->capacity;
    for (int i = H->capacity / 2; i > 0; i--) {
        maxHeapify(H, i);
    }
}

void heapSort(heap H)
{
    buildMaxHeap(H);
    for (int i = H->capacity; i >= 2; i--) {
        struct ElementType tmp = H->heapArray[1];
        H->heapArray[1] = H->heapArray[i];
        H->heapArray[i] = tmp;
        H->heapSize--;
        maxHeapify(H, 1);
    }
}

void showHeapArray(heap H)
{
    if (H->capacity == 0) {
        printf("The heap array is empty !\n");
        return;
    }
    printf("The current state of the heap is: ");
    for (int i = 1; i <= H->capacity; i++) {
        printf("%d ", H->heapArray[i].value);
    }
    printf("\n");
}

int main()
{
    heap H = createHeap(10);
    int data[] ={4, 1, 3, 2, 16, 9, 10, 14, 8, 7};

    for (int i = 0; i < 10; i++) {
        H->heapArray[i + 1].value = data[i]; 
    }    
    heapSort(H);
    // buildMaxHeap(H);
    showHeapArray(H);
    return 0;
}