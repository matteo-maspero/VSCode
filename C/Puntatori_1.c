#include <stdio.h>

int main() {
	int *p1, *p2, *p3;
	int a, b, c;

	scanf("%d", &a);
	scanf("%d", &b);
	scanf("%d", &c);

	p2 = &c;
	p1 = &b;
	p3 = p1;

	a = (*p2 + *p1) / 3;
	*p1 = a * (*p2) - 2 * (*p3);
	*p2 = a + (*p1) - (*p2);

	p3 = p2;
	p2 = &(*p1);
	p1 = &a;

	*p1 = ((*p2) * 4) % (*p3);
	*p2 = (*p1) + (*p2) - 3 * (*p3);
	*p3 = ((*p1) - (*p2)) / 5;

	printf("a = %d\n", a);
	printf("b = %d\n", b);
	printf("c = %d\n", c);
	printf("*p1 = %d\n", *p1);
	printf("*p2 = %d\n", *p2);
	printf("*p3 = %d\n", *p3);
	printf("p1 = %x\n", p1);
	printf("p2 = %x\n", p2);

	return 0;
}