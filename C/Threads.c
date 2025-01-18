#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <time.h>

#define NUM_RANDOM_NUMBERS 5

void* printRandomNumbers(void* arg) {
	int *data = (int*) arg;
	int i;

	for (i = 0; i < NUM_RANDOM_NUMBERS; i++)
		printf("Thread %d: %d\n", data[0], rand() % (data[2] - data[1] + 1) + data[1]);

	pthread_exit(NULL);
	return NULL;
}

int main() {
	pthread_t t1, t2;
	int range1[] = {1, 10, 20};
	int range2[] = {2, 30, 50};

	srand(time(NULL));

	pthread_create(&t1, NULL, printRandomNumbers, range1);
	pthread_create(&t2, NULL, printRandomNumbers, range2);

	pthread_join(t1, NULL);
	pthread_join(t2, NULL);

	return 0;
}