#include <stdio.h>
#include <limits.h>
#include <stdlib.h>

struct Node {
	int coeff;
	int expo;
	struct Node *next;
};

typedef struct Node *POLYNOMIAL;
typedef struct Node *POSITION;

POLYNOMIAL createPolynomial(){
	POLYNOMIAL headerNode = malloc(sizeof(struct Node));
	headerNode->expo = INT_MAX;
	headerNode->next = NULL;
}

void insert_polynomial(POLYNOMIAL poly,int coeff, int expo){
	POSITION prev;
	prev = poly;
	while (poly!=NULL && expo<poly->expo){
		prev = poly;
		poly = poly->next;
	}
	if (prev->expo==coeff)
		prev->coeff+=coeff;
	else {
		POSITION newItem  = malloc(sizeof(struct Node));
		newItem->coeff = coeff;
		newItem->expo = expo;
		//insert into linked list
		newItem->next = prev->next;
		prev->next = newItem;
	}
}

void display_polynomial(POLYNOMIAL poly){
	poly = poly->next;
	while (poly!=NULL)
	{
		printf(" %dx^%d ",poly->coeff,poly->expo);
		poly=poly->next;
	}
	printf("\n");
}

int main (){
	POLYNOMIAL poly1 = createPolynomial();
	POLYNOMIAL poly2 = createPolynomial();
	POLYNOMIAL poly_sum = createPolynomial();
	POLYNOMIAL poly_prod = createPolynomial();
	
	insert_polynomial(poly1,10,1000);
	insert_polynomial(poly1,5,14);
	insert_polynomial(poly1,1,0);
	insert_polynomial(poly1,5,15);
	
	display_polynomial(poly1);
	
	return 0;
}