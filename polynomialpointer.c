#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <ctype.h>

struct node{
    int coeff;
    int expo;
    struct node *next;
};

typedef struct node *POLYNOMIAL;
typedef struct node *Position;

void insert(POLYNOMIAL poly, int coeff, int expo)
{
    Position prev;
    while (poly != NULL && expo <= poly->expo)
    {
        prev = poly;
        poly = poly->next;
    }
    if (prev->expo == expo)
    {
        prev->coeff += coeff;
        return;
    }
    Position new = malloc(sizeof(struct node));
    new->expo = expo;
    new->coeff = coeff;
    new->next = poly;
    prev->next = new;
}

void display_polymonial(POLYNOMIAL poly)
{
    poly = poly->next;
    while (poly != NULL)
    {
        int expo = poly->expo;
        int coeff = poly->coeff;
        if (expo == 1)
        {
            if (coeff == 1)
            {
                printf("x");
            }
            else if (coeff > 0)
            {
                printf("+%dx", coeff);
            }
            else if (coeff < 0)
            {
                printf("%dx", coeff);
            }
        }
        else if (expo == 0)
        {
            if (coeff > 0)
            {
                printf("+%d", coeff);
            }
            else if (coeff < 0)
            {
                printf("%d", coeff);
            }
        }
        else
        {
            if (coeff == 1)
            {
                printf("x^%d", expo);
            }
            else if (coeff > 0)
            {
                printf("+%dx^%d", coeff, expo);
            }
            else if (coeff < 0)
            {
                printf("%dx^%d", coeff, expo);
            }
        }
        poly = poly->next;
    }
    printf("\n");
}

void add_poly(POLYNOMIAL poly1, POLYNOMIAL poly2, POLYNOMIAL poly_sum)
{
    poly1 = poly1->next;
    poly2 = poly2->next;
    while (poly1!=NULL)
    {
        insert(poly_sum, poly1->coeff, poly1->expo);
        poly1 = poly1->next;
    }
    while (poly2!=NULL)
    {
        insert(poly_sum, poly2->coeff, poly2->expo);
        poly2 = poly2->next;
    }
}

void mult_poly(POLYNOMIAL poly1, POLYNOMIAL poly2, POLYNOMIAL poly_prod)
{
    poly1 = poly1->next;
    poly2 = poly2->next;
    while (poly1!=NULL)
    {
        Position tmp = poly2;
        while(tmp != NULL)
        {
            insert(poly_prod, poly1->coeff*tmp->coeff, poly1->expo + tmp->expo);
            tmp = tmp->next;
        }
        poly1 = poly1->next;
    }
}

POLYNOMIAL create_poly()
{
    POLYNOMIAL headernode = malloc(sizeof(struct node));
    headernode->next = NULL;
    headernode->expo = INT_MAX;
    return headernode;
}

int main(void)
{
    POLYNOMIAL poly1 = create_poly();
    POLYNOMIAL poly2 = create_poly();
    POLYNOMIAL poly_sum = create_poly();
    POLYNOMIAL poly_prod = create_poly();
    insert(poly1, 1000, 10);
    insert(poly1, 14, 8);
    insert(poly1, 7, 1);
    insert(poly1, 3, 2);
    insert(poly2, 3, 3);
    insert(poly2, 4, 4);
    insert(poly2, 5, 5);
    insert(poly2, 6, 6);
    printf("POLY1: \n");
    display_polymonial(poly1);
    printf("POLY2: \n");
    display_polymonial(poly2);
    add_poly(poly1, poly2, poly_sum);
    printf("SUM: \n");
    display_polymonial(poly_sum);
    mult_poly(poly1, poly2, poly_prod);
    printf("PRODUCT: \n");
    display_polymonial(poly_prod);
}

