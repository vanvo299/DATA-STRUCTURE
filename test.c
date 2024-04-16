#include <stdio.h>
#include <limits.h>
#include <stdlib.h>
#include <math.h>

struct Node {
	int coeff;
	int expo;
	struct Node *next;
};

typedef struct Node *POLYNOMIAL;
typedef struct Node *POSITION;

POLYNOMIAL createPolynomial(){
	POLYNOMIAL headerNode = malloc(sizeof(struct Node));
	headerNode->next = NULL;
	headerNode->expo = INT_MAX;
	return headerNode;
}

void insert_polynomial(POLYNOMIAL poly, int coeff, int expo){
	POSITION prev = poly;
	//Find a correct position to insert
	while (poly!=NULL && poly->expo>=expo){
		prev = poly;
		poly=poly->next;
	}
	
	if (prev->expo == expo)
		prev->coeff += coeff;
	else {
		//Create a new Node
		POSITION newItem = malloc(sizeof(struct Node));
		newItem->coeff = coeff;
		newItem->expo = expo;
		
		//Insert into the linked list
		newItem->next = prev->next;
		prev->next = newItem;
	}	
}

void display_polynomial(POLYNOMIAL poly) {
	poly = poly->next;
	while (poly != NULL) {
        printf(" %dx^%d ", poly->coeff, poly->expo);
        poly = poly->next;
    }
    printf("\n");
}

void sum_polynomial(POLYNOMIAL poly1, POLYNOMIAL poly2, POLYNOMIAL poly_sum){
	poly1 = poly1->next;
	poly2 = poly2->next;
	while (poly1!=NULL){
		insert_polynomial(poly_sum,poly1->coeff,poly1->expo);
		poly1=poly1->next;
	}
	while (poly2!=NULL){
		insert_polynomial(poly_sum,poly2->coeff,poly2->expo);
		poly2=poly2->next;
	}
}

void mult_polynomial(POLYNOMIAL poly1, POLYNOMIAL poly2, POLYNOMIAL poly_prod)
{
    poly1 = poly1->next;
    poly2 = poly2->next;
    while (poly1!=NULL)
    {
        POSITION tmp = poly2;
        while(tmp != NULL)
        {
            insert_polynomial(poly_prod, poly1->coeff*tmp->coeff, poly1->expo + tmp->expo);
            tmp = tmp->next;
        }
        poly1 = poly1->next;
    }
}

int main(){
	POLYNOMIAL poly1 = createPolynomial();
	POLYNOMIAL poly2 = createPolynomial();
	POLYNOMIAL poly_sum = createPolynomial();
	POLYNOMIAL poly_prod = createPolynomial();
	
	insert_polynomial(poly1,-1,6);insert_polynomial(poly1,5,5);
	insert_polynomial(poly1,1,2);insert_polynomial(poly1,-1,0);
	
	insert_polynomial(poly2,3,5);insert_polynomial(poly2,-2,3);
	insert_polynomial(poly2,11,1);insert_polynomial(poly2,5,0);
	
	display_polynomial(poly1);
	display_polynomial(poly2);
	
	sum_polynomial(poly1,poly2,poly_sum);
	mult_polynomial(poly1,poly2,poly_prod);
	
	printf("SUM: ");
	display_polynomial(poly_sum);
	
	printf("MULTIPLY: ");
	display_polynomial(poly_prod);
	
	return 0;
}