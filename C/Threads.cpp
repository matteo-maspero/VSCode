#include <iostream>
#include <random>
#include <thread>
using namespace std;

int main() {
	thread t1([]() {		
		for (int i = 0; i < 5; i++)
			printf("t1 %d\n", rand() % 11 + 10);
	});

	thread t2([]() {		
		for (int i = 0; i < 5; i++)
			printf("t2 %d\n", rand() % 21 + 30);
	});

	t1.join();
	t2.join();

	return 0;
}