#include <stdio.h>

int main() {
	int n;
	printf("Inserisci un numero: ");
	scanf("%d", &n);

	printf("I divisori del numero sono: ", n);
	for(int i = 2; i <= n; i ++)
		if(n % i == 0)
			printf("%d ", i);

	printf("FINE\n");
	return 0;
}