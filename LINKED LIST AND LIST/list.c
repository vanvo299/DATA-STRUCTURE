#include <stdio.h>
#include <stdlib.h>
const int MAX_SIZE = 100;

struct ElementType{
    unsigned long ID;
    char *name;
};
typedef struct ElementType *Student;

struct listInfo{
    int count;
    int max_size;
    Student *list;
};
typedef struct listInfo *Class;

// hàm tạo class mới
Class CreateClass(int max_size)
{
    Class cls = malloc(sizeof(struct listInfo));
    cls->count = 0;
    cls->max_size = max_size;
    cls->list = malloc(sizeof(struct ElementType));
    return cls;
}

// ham chen phan tu vao cuoi
void insert(Class cls, Student s, int Pos)
{
    if (Pos > cls->count || cls->count > cls->max_size) return;
    for (int i = cls->count; i > Pos; i--) {
        cls->list[i] = cls->list[i - 1];
    }
    cls->list[Pos] = s;
    cls->count++;
}

// ham chen phan tu vao vi tri k
void insert_k(Class cls, Student s, int k)
{
    if (k < 0 || k > cls->count) return;
    for (int i = cls->count; i > k; i--) {
        cls->list[i] = cls->list[i - 1];
    }
    cls->list[k] = s;
    cls->count++;
}
// ham in
void display(Class cls)
{
    for (int i = 0; i < cls->count; i++) {
        printf("*** %d | %ld | %s ***\n", i + 1, cls->list[i]->ID, cls->list[i]->name);
    }
}

// ham xoa
void erase(Class cls, int Pos)
{
    if (Pos < 0 || Pos > cls->count) return;
    for (int i = Pos; i < cls->count - 1; i++) {
        cls->list[i] = cls->list[i + 1];
    }
    cls->count--;
}
// ham giai phong dung luong
void destroy(Class cls)
{
    for (int i = 0; i < cls->count; i++) {
        free(cls->list[i]->name);
        free(cls->list[i]);
    }
    free(cls->list);
    free(cls);
}

// ham kiem tra xem list co bi rong khong
void isEmpty(Class cls)
{
    if (cls->count == 0) {
        printf("The list is Empty\n");
    } else printf("The list is not Empty\n");
}

// in phan tu dau va phan tu cuoi
void isLast_and_isFirst(Class cls)
{
    printf("The first element is list: *** %ld | %s ***\n", cls->list[0]->ID, cls->list[0]->name);
    printf("The last element is list: *** %ld | %s ***\n", cls->list[cls->count - 1]->ID, cls->list[cls->count - 1]->name);
}

// ham tim phan tu truoc no
void FindPrevious(Class cls, int k)
{
    if (k < 0 || k > cls->count) return;
    printf("The element previous k in list: *** %ld | %s ***\n", cls->list[k - 1]->ID, cls->list[k - 1]->name);
}

//  ham tim kiem
void Find(Class cls, unsigned long ID) 
{
    int Pos;
    int temp = 0;
    for (int i = 0; i < cls->count; i++) {
        if (cls->list[i]->ID == ID) {
            Pos = i;
            temp = 1;
        }
    }
    if (temp == 0) {
        printf("Khong tim thay phan tu co ID %ld trong list\n", ID);
    } else printf("Phan tu o vi tri %d la: *** %ld | %s ***\n", Pos, cls->list[Pos]->ID, cls->list[Pos]->name);
}
int main()
{
    Class cls10 = CreateClass(MAX_SIZE);

    isEmpty(cls10);
    printf("\n");
    Student std1 = malloc(sizeof(struct ElementType));
    std1->name = "Luong Van Vo";
    std1->ID = 102230224;

    Student std2 = malloc(sizeof(struct ElementType));
    std2->name = "Nguyen Dang Bao Nguyen";
    std2->ID = 102230256;

    Student std3 = malloc(sizeof(struct ElementType));
    std3->name = "Dinh Minh Tue";
    std3->ID = 102230223;

    Student std4 = malloc(sizeof(struct ElementType));
    std4->name = "Phan Thi Nhan Vy";
    std4->ID = 102230225;

    insert(cls10, std1, 0);
    insert(cls10, std2, 1);
    insert(cls10, std3, 2);
    display(cls10);
    printf("\n");

    isEmpty(cls10);
    printf("\n");

    int chen_k; 
    printf("Nhap vi tri k can chen: "); scanf("%d", &chen_k);
    insert_k(cls10, std4, chen_k);
    display(cls10);
    printf("\n");

    isLast_and_isFirst(cls10);
    printf("\n");

    int previous_K;
    printf("Nhap vi tri can tim phan tu truoc no: "); scanf("%d", &previous_K);
    FindPrevious(cls10, previous_K);
    printf("\n");

    unsigned long ID_k;
    printf("Nhap ID can tim: "); scanf("%ld", &ID_k);
    Find(cls10, ID_k);
    printf("\n");

    int erase_k;
    printf("Nhap vi tri can xoa: "); scanf("%d", &erase_k);
    erase(cls10, erase_k);
    printf("List sau khi xoa phan tu o vi tri %d la: \n", erase_k);
    display(cls10); 

    destroy(cls10);
    return 0;
}