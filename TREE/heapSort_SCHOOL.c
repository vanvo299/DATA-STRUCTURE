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

void showHeap(heap H) {
	if (H->heapSize == 0) {
		printf("The heap is empty!\n");
		return;
	}
	printf("The heap: ");
	for (int i=1;i<=H->heapSize;i++)
		printf("%d ",H->heapArray[i].value);
	printf("\n");
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

struct ElementType* heapMaximum(heap H)
{
    if (H->heapSize < 1) {
        printf("The heap is empty !!!\n");
        return NULL;
    }
    return &H->heapArray[1];
}

//fix lại
struct ElementType *extractMaximum(heap H)
{
    if (H->heapSize < 1) {
        printf("The heap is empty!!! \n");
        return NULL;
    }
    struct ElementType tmp = H->heapArray[H->heapSize];
    H->heapArray[H->heapSize] = H->heapArray[1];
    H->heapArray[1] = tmp;
    H->heapSize--;
    maxHeapify(H, 1);
    return &H->heapArray[H->heapSize + 1];
}


void heapIncreaseKey(heap H, int i, int key)
{
    if (key < H->heapArray[i].value) {
        printf("The new valuw must be equal or larger than the node's current value !\n");
        return;
    }
    H->heapArray[i].value = key;
    while (i > 1 && H->heapArray[i].value > H->heapArray[i / 2].value) {
        struct ElementType tmp = H->heapArray[i];
        H->heapArray[i] = H->heapArray[i / 2];
        H->heapArray[i / 2] = tmp;
        i = i / 2;
    }
}

// tăng kích thước mảng lên 1 đơn vị
void openCapacity(heap H, int key)
{
    struct ElementType newNode;
    newNode.value = INT_MIN;
    H->heapSize++;
    H->heapArray[H->heapSize] = newNode;
    heapIncreaseKey(H, H->heapSize, key);
}

void heapInsertKey(heap H, int key) {
    if (H->heapSize < H->capacity) {
        H->heapSize++;
        H->heapArray[H->heapSize].value = INT_MIN;
        heapIncreaseKey(H, H->heapSize, key);
    } else {
        openCapacity(H, key);
    }    

}

int main()
{
    heap H = createHeap(10);
    int data[] ={4, 1, 3, 2, 16, 9, 10, 14, 8, 7};

    for (int i = 0; i < 11; i++) {
        H->heapArray[i + 1].value = data[i]; 
    }    
    // heapSort(H);
    buildMaxHeap(H);
    showHeapArray(H);
    
    // struct ElementType *max = heapMaximum(H);
    // printf("%d \n", max->value);

    // struct ElementType *max = extractMaximum(H);
    // printf("%d \n", max->value);
    // showHeap(H);

    // heapIncreaseKey(H, 1, 20);
    // showHeapArray(H);
    
    // heapInsertKey(H, 150);
    // showHeapArray(H);
    // heapInsertKey(H, 100000);
    // heapSort(H);
    // showHeapArray(H);
    
    return 0;
}