// minHeap (maxHeap thì thay đổi dấu)

#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define MAX_ELEMENT 15

struct ElementType{
    int value;
};

struct binaryHeap{
    unsigned int capacity;
    unsigned int heapSize;
    struct ElementType *harr;
};

typedef struct binaryHeap *binaryHeap;

// lấy vị trí của nút cha
int parent(int i) 
{
    return (i - 1) / 2;
}

// lấy vị trí của nút con bên trái
int leftChild(int i)
{
    return 2*i + 1;
}

// lấy vị trí của nút con bên phải
int rightChild(int i)
{
    return 2*i + 2;
}

// Trả về giá trị nhỏ nhất (tại gốc cây) trong heap mà không xóa nó.
int getMin(binaryHeap heap)
{
    return heap->harr[0].value;
}

void swap(struct ElementType *x, struct ElementType *y)
{
    struct ElementType temp = *x;
    *x = *y;
    *y = temp;
}

// tạo một cây heap
binaryHeap createBinaryHeap(int capacity)
{
    binaryHeap heap = malloc(sizeof(struct binaryHeap));
    heap->heapSize = 0;
    heap->capacity = capacity;
    heap->harr = malloc(sizeof(struct ElementType) * capacity);
    if (heap->harr == NULL) {
        printf("Memory allocation failed\n");
        free(heap);
        exit(1);
    }
    return heap;
}

// Thêm phần tử 
void insertKey(binaryHeap heap, struct ElementType k)
{
    if (heap->heapSize == heap->capacity) {
        printf("\nOverflow: Could not insertKey\n");
        return;
    }

    // them gia tri vao cuoi mang
    heap->heapSize++;
    int i = heap->heapSize - 1;
    heap->harr[i] = k;

    // doi cho cac phan tu neu khong dung thuoc tinh cua minHeap
    while(i != 0 && heap->harr[parent(i)].value > heap->harr[i].value) {
        swap(&heap->harr[i], &heap->harr[parent(i)]);
        i = parent(i);
    }
}

// Kiểm tra xem cây đã đúng tính chất chưa
void minHeapify(binaryHeap heap, int index)
{
    int l = leftChild(index);
    int r = rightChild(index);
    int smallest = index;
    if (l < heap->heapSize && heap->harr[l].value < heap->harr[index].value) {
        smallest = l;
    }
    if (r < heap->heapSize && heap->harr[r].value < heap->harr[index].value) {
        smallest = r;
    }
    // smallest chứa chỉ số của phần tử nhỏ nhất
    if (smallest != index) {
        swap(&heap->harr[index], &heap->harr[smallest]);
        minHeapify(heap, index);
    }
}

// Trả về phần tử nhỏ nhất trong heap và xóa nó.
struct ElementType extractMin(binaryHeap heap)
{
    if (heap->heapSize <= 0) {
        exit(1);
    }
    if (heap->heapSize == 1) {
        heap->heapSize--;
        return heap->harr[0];
    }

    struct ElementType root = heap->harr[0];
    heap->harr[0] = heap->harr[heap->heapSize - 1];
    heap->heapSize--;
    minHeapify(heap,0);

    return root;
}

// Thay đổi giá trị của phần tử tại vị trí i thành new_val.
void decreaseKey(binaryHeap heap, int i, int new_val)
{
    heap->harr[i].value = new_val;
    while(i != 0 && heap->harr[parent(i)].value > heap->harr[i].value) {
        swap(&heap->harr[parent(i)], &heap->harr[i]);
        i = parent(i);
    }
}

// xóa phần tử đầu tiên khỏi mảng
void deleteKey(binaryHeap heap, int i)
{
    decreaseKey(heap, i, INT_MIN);
    extractMin(heap);
}

// in
void printHeap(binaryHeap heap)
{
    printf("Cac phan tu trong Binary Heap: ");
    for (int i = 0; i < heap->heapSize; i++) {
        printf("%d ", heap->harr[i].value);
    }
    printf("\n");
}
int main()
{
    binaryHeap h = createBinaryHeap(30);
    struct ElementType h1, h2, h3, h4, h5, h6, h7;
    h1.value = 12;
    h2.value = 20;
    h3.value = 30;
    h4.value = 35;
    h5.value = 6;
    h6.value = 70;
    h7.value = 1;


    insertKey(h, h1);
    insertKey(h, h2);
    insertKey(h, h3);
    insertKey(h, h4);
    insertKey(h, h5);
    insertKey(h, h6);
    insertKey(h, h7);


    printHeap(h);
    printf("%d \n", getMin(h));
    // printf("%d \n", extractMin(h));
    // printf("%d \n", getMin(h));
    deleteKey(h, 0);
    // decreaseKey(h, 0, 3);
    printHeap(h);
    return 0;
}