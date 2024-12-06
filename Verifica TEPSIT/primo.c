#include <stdio.h>

int isPrime(int num) {
	if(num < 2)
		return 0;
	
	for(int i = 2; i * i <= num; i ++)
		if (!(num % i))
			return 0;

	return 1;
}

int main() {
	int number;
	printf("Inserisci un numero: ");
	scanf("%d", &number);

	if(isPrime(number))
		printf("Il numero e' primo.\n");
	else
		printf("Il numero non è primo.\n");

	return 0;
}