#include <iostream>
#include <thread>
using namespace std;

#define SIZE 16

int countEven(int arr[], int size);
int countEvenParallel(int arr[], int size);

void fillArray(int arr[], int size);
void printArray(int arr[], int size);

int main() {
	int arr[SIZE];

	fillArray(arr, SIZE);
	cout << "Array:\n";
	printArray(arr, SIZE);

	int even = countEven(arr, SIZE);
	cout << "\n\nNumeri pari: " << even;

	int even2 = countEvenParallel(arr, SIZE);
	cout << "\nNumeri pari (parallelo): " << even2;

	return 0;
}

int countEven(int arr[], int size) {
	int count = 0;

	for(int i = 0; i < size; i++)
		if(!(arr[i] % 2))
			count++;
	
	return count;
}


int countEvenParallel(int arr[], int size) {
	int count = 0;

	thread thread1([&]() {
		for (int i = 0; i < size / 2; i++) {
			if (!(arr[i] % 2)) {
				count++;
			}
		}
	});

	thread thread2([&]() {
		for (int i = size / 2; i < size; i++) {
			if (!(arr[i] % 2)) {
				count++;
			}
		}
	});

	thread1.join();
	thread2.join();
	return count;
}

void fillArray(int arr[], int size) {
	for(int i = 0; i < size; i++) {
		arr[i] = i;
	}
}

void printArray(int arr[], int size) {
	for(int i = 0; i < size; i++) {
		cout << "\t" << arr[i];
	}
}