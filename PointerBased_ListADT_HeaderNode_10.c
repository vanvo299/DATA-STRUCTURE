#include <stdio.h>

struct ElementType {
	unsigned long ID;
	char *name;
};

struct Node {
	struct ElementType value;
	struct Node *next;
};

typedef struct Node *List;
typedef struct Node *Position;

Position insert(List *pL, struct ElementType e, Position p){
	Position newItem = malloc(sizeof(struct Node));
	newItem->value = e;
			
	newItem->next = p->next;
	p->next = newItem;	
	
	return newItem;
}

void display(List pL) {
	int count = 1;
	pL = pL->next;
	while (pL!=NULL) {
		printf("*** %d | ID: %ld       | Name: %s ***\n",
			  count,pL->value.ID, pL->value.name);
		count++;
		pL = pL->next;
	}
}

List createList() {	
	Position headerNode = malloc(sizeof(struct Node));
	headerNode->next = NULL;
	return headerNode;
}

int main() {
	List pL = createList();
	struct ElementType item1, item2, item3;
	
	item1.ID = 1001; item1.name = "Nguyen Van An";
	item2.ID = 1002; item2.name = "Nguyen Van Binh";
	item3.ID = 1003; item3.name = "Nguyen Van Chau";
	
	Position p = pL;
	p = insert(&pL,item1,pL);
	p = insert(&pL,item2,p);
	p = insert(&pL,item3,p);
	
	display(pL);
	
	free(pL);
	return 0;
}