#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define LIST_SIZE 10
#define STR_MAX_SIZE 50

void inputList(char **list, int size);
void printList(char **list, int size);

void printSmallestStrings(char **list, int size);
void mirrorList(char **list, int size);

int main() {
	char **list;
	list = (char **) malloc(sizeof(char *) * LIST_SIZE);

	inputList(list, LIST_SIZE);
	printSmallestStrings(list, LIST_SIZE);

	mirrorList(list, LIST_SIZE);
	printList(list, LIST_SIZE);

	return 0;
}

void inputList(char **list, int size) {
	int i;

	printf("\nInserisci %d stringhe (una per riga):\n", size);

	for(i = 0; i < size; i ++) {
		char temp[size];
		int len;

		scanf("%s", temp);	
		len = strlen(temp);

		list[i] = (char *) malloc(sizeof(char) * (len + 1));
		strcpy(list[i], temp);
	}
}

void printList(char **list, int size) {
	int i;

	printf("\nLista risultante:\n");

	for(i = 0; i < size; i ++) {
		printf("%s\n", list[i]);
	}
}

void printSmallestStrings(char **list, int size) {
	int i;
	int smallest;

	for(i = 0; i < size; i ++) {
		if(strlen(list[i]) < smallest) {
			smallest = strlen(list[i]);
		}
	}

	printf("\nLe stringhe più corte:\n");

	for(i = 0; i < size; i ++) {
		if(strlen(list[i]) == smallest) {
			printf("%s\n", list[i]);
		}
	}
}

void mirrorList(char **list, int size) {
	int i;
	char *swap;

	for(i = 0; i < size / 2; i ++) {
		swap = list[i];
		list[i] = list[size - i - 1];
		list[size - i - 1] = swap;
	}
}