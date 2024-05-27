#include <stdio.h> 
#include <stdlib.h>

struct ElementType {
    unsigned long ID;
    char *name;
};

struct node {
    struct ElementType value;
    struct node *next;
};

typedef struct node *List;
typedef struct node *Position;

// số lượng phần tử của linked list
int size(List pL) 
{
    int count = 0;
    pL = pL->next;
    while(pL != NULL) {
        count++;
        pL = pL->next;
    }
    return count;
}

// hàm chèn phần tử vào cuối linked list
void insert(List *pL, struct ElementType s, Position p)
{
    Position newItem = malloc(sizeof(struct node));
    newItem->value = s;
    newItem->next = p->next;
    p->next = newItem; 
}

// hàm chèn thêm phần tử vào vị trí bất kì
void insert_k(List *pL, struct ElementType s, int k)
{
    int n = size(*pL);
    if (k > n + 1|| k < 1) {
        printf("Vi tri chen khong hop le ! \n");
        return;
    }
    Position newItem = malloc(sizeof(struct node));
    Position temp = *pL;
    temp = temp->next;
    for (int i = 1; i < k - 1; i++) {
        temp = temp->next;
    }
    newItem->value = s;
    newItem->next = temp->next;
    temp->next = newItem;
}
// ham in
void display(List pL)
{
    int count = 1;
    pL = pL->next;
    while (pL != NULL) {
        printf("*** %d | %ld | %s ***\n", count, pL->value.ID, pL->value.name);
        count++;
        pL = pL->next;
    }
}

// Hàm xóa phần tử trong Linked list
void Delete(List *pL, int k)
{
    int n = size(*pL);
    if (k < 1 || k > n + 1) {
        printf("Vi tri khong hop le ! \n");
        return;
    } 
    Position temp = *pL;
    if (k == 1) {
        (*pL) = (*pL)->next;
        free(temp);
    } else if (k == n + 1) {
        temp = temp->next;
        for (int i = 1; i < k - 1; i++) {
            temp = temp->next;
        }
        Position last = temp->next;
        temp->next = NULL;
        free(last);
    } else {
        temp = temp->next;
        for (int i = 1; i < k - 1; i++) {
            temp = temp->next;
        }
        Position del = temp->next;
        temp->next = del->next;
        free(del);
    }
}

// Hàm tìm kiếm một phần tử có trong linked list
void Find(List pL, unsigned long ID)
{
    int temp = 0;
    pL = pL->next;
    while(pL->next != NULL) {
        pL = pL->next;
        if (pL->value.ID == ID) {
            temp = 1;
            break;
        }
    }
    if (temp) {
        printf("Phan tu co ID %ld la: *** %ld | %s ***\n", ID, pL->value.ID, pL->value.name);
    } else printf("Khong tim thay thong tin co ID %ld trong danh sach\n", ID);
}
// tao mot lop moi
List CreateList()
{
    Position headerNode = malloc(sizeof(struct node));
    headerNode->next = NULL;
    return headerNode; 
}
int main()
{
    List Class = CreateList();
    struct ElementType std1, std2, std3, std4, std5;

    std1.name = "Luong Van Vo";
    std1.ID = 102230224;

    std2.name = "Nguyen Dang Bao Nguyen";
    std2.ID = 102230256;

    std3.name = "Dinh Minh Tue";
    std3.ID = 102230223;

    std4.name = "Phan Thi Nhan Vy";
    std4.ID = 102230225;

    std5.name = "Nguyen Tran Ly Na";
    std5.ID = 102230299;

    Position p = Class;
    insert(&Class, std1, Class);
    insert(&Class, std2, p);
    insert(&Class, std3, p);
    insert(&Class, std4, p);
    display(Class);

    printf("\n");
    int Pos;
    printf("Nhap vi tri can chen: "); scanf("%d", &Pos);
    insert_k(&Class, std5, Pos);
    display(Class);
    printf("\n");

    unsigned long Id;
    printf("Nhap Id can tim kiem: "); scanf("%ld", &Id);
    Find(Class, Id);

    printf("\n");
    int Pos_delete;
    printf("Nhap vi tri can xoa: "); scanf("%d", &Pos_delete);
    Delete(&Class, Pos_delete);
    display(Class);
    return 0;
}