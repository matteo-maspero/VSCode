#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define NUMBERS 100
#define MIN 1
#define MAX 9
#define RESULTS 5

int main() {
	int numbers[NUMBERS];
	//	Init to {} to set all elements to 0
	int frequencies[MAX - MIN] = {};
	int results[RESULTS] = {};
	
	int i, j;
	int max, maxIndex;

	srand(time(NULL));
	printf("Array iniziale:\n");

	for(i = 0; i < NUMBERS; ++i) {
		numbers[i] = rand() % (MAX - MIN) + MIN;
		printf("%d\t", numbers[i]);

		if((i + 1) % 10 == 0)
			printf("\n");
	}

	for(i = 0; i < NUMBERS; ++i)
		++frequencies[numbers[i] - MIN];
	
	for (i = 0; i < RESULTS; ++i) {
		max = frequencies[0];
		maxIndex = 0;
		
		for (j = 1; j < MAX - MIN; ++j)
			if(frequencies[j] > max) {
				max = frequencies[j];
				maxIndex = j;
			}
		
		results[i] = maxIndex + MIN;
		//	Reset the frequency to avoid duplicate results
		frequencies[maxIndex] = 0;
	}

	printf("I numeri più frequenti sono:\n");

	for(i = 0; i < RESULTS; ++i)
		printf("%d\t", results[i]);
}