#include <stdio.h>

int factorial(int n);

int main() {
	int num;
	printf("Inserisci un numero positivo: ");

	do
		scanf("%d", &num);
	while(num < 0);

	printf("Il fattoriale vale: %d\n", factorial(num));
	return 0;
}

int factorial(int n) {
	if(n == 0)
		return 1;
	else
		return n * factorial(n - 1);
}