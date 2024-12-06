#include <stdio.h>

int main() {
	int n, sum = 0;
	printf("Inserisci un numero positivo: ");

	do
		scanf("%d", &n);
	while(n <= 0);

	for(int i = 1; i <= n; i ++)
		sum = sum + i;

	printf("La sommatoria vale: %d\n", sum);
	return 0;
}