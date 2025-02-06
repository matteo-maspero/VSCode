#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define nNUMBERS 100

void sortDelDiocane(int *numbers, int size);

int main() {
	int numbers[nNUMBERS];
	int i;

	srand(time(NULL));

	for (i = 0; i < nNUMBERS; ++i) {
		numbers[i] = rand() % 100;
		printf("%d\t", numbers[i]);
	}

	sortDelDiocane(numbers, nNUMBERS);
	printf("\n\n\n");
	
	for (i = 1; i < nNUMBERS; ++i)
		printf("%d\t", numbers[i]);

	return 0;
}

void sortDelDiocane(int *numbers, int size) {
	if (size < 2)
		return;
	
	int i, temp;
	int iMin = 0;
	int iMax = 0;

	for (i = 1; i < size; ++i) {
		if (numbers[i] < numbers[iMin])
			iMin = i;
		if (numbers[i] > numbers[iMax])
			iMax = i;
	}

	temp = numbers[0];
	numbers[0] = numbers[iMin];
	numbers[iMin] = temp;

	temp = numbers[size - 1];
	numbers[size - 1] = numbers[iMax];
	numbers[iMax] = temp;

	sortDelDiocane(numbers + 1, size - 2);
}