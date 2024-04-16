#include <stdio.h>
#include <stdlib.h>
#define MAX_DEGREE 100

typedef struct polynomial{
    int coeff_array[MAX_DEGREE + 1];
    unsigned long high_power;
} *POLYNOMIAL;

void zero_polynomial(POLYNOMIAL poly)
{
    for (int i = 0; i <= MAX_DEGREE; i++) {
        poly->high_power = 0;
        poly->coeff_array[i] = 0;
    }
}

int max(int a, int b)
{
    return a>b?a:b;
}

void sum_polynomial(POLYNOMIAL poly_sum, POLYNOMIAL poly1, POLYNOMIAL poly2)
{
    zero_polynomial(poly_sum);
    poly_sum->high_power = max(poly1->high_power, poly2->high_power);
    for (int i = poly_sum->high_power; i >= 0; i--) {
        poly_sum->coeff_array[i] += poly1->coeff_array[i] + poly2->coeff_array[i];
    }
}

void mult_polynomial(POLYNOMIAL poly_prod, POLYNOMIAL poly1, POLYNOMIAL poly2)
{
    zero_polynomial(poly_prod);
    poly_prod->high_power = poly1->high_power + poly2->high_power;
    for (int i = 0; i <= poly1->high_power; i++) {
        for (int j = 0; j <= poly2->high_power; j++) {
            poly_prod->coeff_array[i+j] += poly1->coeff_array[i] * poly2->coeff_array[j];
        }
    }
}

void display(POLYNOMIAL poly)
{
    for (int i = poly->high_power; i >= 0; i--) {
        printf(" %dx^%ld ", poly->coeff_array[i], poly->high_power);
    }
    printf("\n");
}
int main()
{
    POLYNOMIAL poly1 = malloc(sizeof(struct polynomial));
    POLYNOMIAL poly2 = malloc(sizeof(struct polynomial));
    POLYNOMIAL poly_sum = malloc(sizeof(struct polynomial));
    POLYNOMIAL poly_prod = malloc(sizeof(struct polynomial));

    printf("Nhap he so cua da thuc dau tien: ");
    poly1->high_power = 3;
    for (int i = 0; i <= poly1->high_power; i++) {
        scanf("%d", &poly1->coeff_array[i]);
    }

    printf("Nhap he so cua da thuc thu hai: ");
    poly2->high_power = 2;
    for (int i = 0; i <= poly2->high_power; i++) {
        scanf("%d", &poly2->coeff_array[i]);
    }

    display(poly1);
    display(poly2);

    sum_polynomial(poly_sum, poly1, poly2);
    mult_polynomial(poly_prod, poly1, poly2);

    printf("SUM: ");
    display(poly_sum);
    printf("MULT: ");
    display(poly_prod);

    return 0;
}