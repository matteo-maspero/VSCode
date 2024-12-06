#include <stdio.h>

int main() {
	int n, sum = 0;

	do {
		printf("Inserisci un numero (0 per uscire dal loop): ");
		scanf("%d", &n);
		sum = sum + n;
	} while(n != 0);

	printf("La somma vale: %d\n", sum);
	return 0;
}