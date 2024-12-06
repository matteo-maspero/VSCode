#include <stdio.h>
#define SIZE 10

int main() {
	int arr[SIZE];
	printf("Inserisci i numeri nell'array separati da uno spazio (x y z ...): ");

	for(int i = 0; i < SIZE; i ++)
		scanf("%d", arr + i);

	int target;
	printf("Inserisci il numero da cercare: ");
	scanf("%d", &target);

	for(int i = 0; i < SIZE; i ++)
		if(arr[i] == target) {
			printf("Il numero si trova nella posizione %d\n", i);
			break;
		}

	return 0;
}