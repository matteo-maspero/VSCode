#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define SIZE 16

int binarySearch(int *arr, int target, int start, int end);

int main() {
	int arr[SIZE];
	srand(time(NULL));

	printf("L'array e': ");
	arr[0] = rand() % 10;

	for(int i = 1; i < SIZE; i ++) {
		arr[i] = arr[i - 1] + rand() % 10;
		printf("%d ", arr[i]);
	}

	int target;
	printf("\nInserisci il numero da cercare: ");
	scanf("%d", &target);

	int position = binarySearch(arr, target, 0, SIZE - 1);

	if(position == -1)
		printf("Il numero non è stato trovato.\n");
	else
		printf("Il numero si trova in posizione %d\n", position);

	return 0;
}

int binarySearch(int *arr, int target, int start, int end) {
	if(start > end)
		return -1;

	int mid = (start + end) / 2;

	if(arr[mid] == target)
		return mid;
	else if(arr[mid] < target)
		return binarySearch(arr, target, mid + 1, end);
	else
		return binarySearch(arr, target, start, mid - 1);
}