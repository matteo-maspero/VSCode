#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define INPUT_PATH "D:\\VSCode\\Workspace\\suites.txt"

//	TYPES
//	--	--	--	--	--	--	--	--	--	--	--	--	--	--	--	--	--	--	--	--	--	--	--	//
typedef struct Installment {
	int value;
	int paid;
	int number;
	int month;
	int year;
	struct Installment *next;
} Installment;

typedef struct Suite {
	int floor;
	int number;
	int rooms;
	char name[32];
	char surname[32];
	struct Suite *next;
} Suite;

typedef Suite* Node;

//	LISTS HANDLING
//	--	--	--	--	--	--	--	--	--	--	--	--	--	--	--	--	--	--	--	--	--	--	--	//
Node createNode(int floor, int number, int rooms, char *name, char *surname);
Node insertNode(Node head, int floor, int number, int rooms, char *name, char *surname);

//	I/O HANDLING
//	--	--	--	--	--	--	--	--	--	--	--	--	--	--	--	--	--	--	--	--	--	--	--	//
int readInt(const char* request);
char* readString(const char* request);

Node readSuites(Node head);

void printSuite(Node head);
void printAllSuites(Node head);

int main() {
	Node head = NULL;

	head = readSuites(head);

	return 0;
}

//	LISTS HANDLING
//	--	--	--	--	--	--	--	--	--	--	--	--	--	--	--	--	--	--	--	--	--	--	--	//
Node createNode(int floor, int number, int rooms, char *name, char *surname) {
	Node dest = (Node) malloc(sizeof(Suite));
	dest->floor = floor;
	dest->number = number;
	dest->rooms = rooms;
	dest->next = NULL;

	strcpy(dest->name, name);
	strcpy(dest->surname, surname);
	return dest;
}

Node insertNode(Node head, int floor, int number, int rooms, char *name, char *surname) {
	if (head == NULL)
		return createNode(floor, number, rooms, name, surname);

	if (head->floor > floor || (head->floor == floor && head->number > number)) {
		Node dest = createNode(floor, number, rooms, name, surname);
		dest->next = head;
		return dest;
	}

	Node current = head;

	while (current->next != NULL && (current->next->floor < floor || (current->next->floor == floor && current->next->number < number)))
		current = current->next;

	Node dest = createNode(floor, number, rooms, name, surname);
	dest->next = current->next;
	current->next = dest;

	return head;
}

//	I/O HANDLING
//	--	--	--	--	--	--	--	--	--	--	--	--	--	--	--	--	--	--	--	--	--	--	--	//
int readInt(const char* request) {
	int dest;
	printf("%s", request);
	scanf("%d", &dest);
	return dest;
}

char* readString(const char* request) {
	char temp[32];
	printf("%s", request);
	scanf("%s", temp);
	
	char* dest = (char*) malloc(sizeof(char) * strlen(temp));
	strcpy(dest, temp);
	return dest;
}

Node readSuites(Node head) {
    FILE* inputFile = fopen(INPUT_PATH, "r");

    if (inputFile == NULL) {
        perror("Error opening file.");
        exit(1);
    }

    int floor, number, rooms;
    char name[32];
    char surname[32];

    while (fscanf(inputFile, "%d\t%d\t%d\t%s\t%s", &floor, &number, &rooms, name, surname) != EOF)
        head = insertNode(head, floor, number, rooms, name, surname);

    fclose(inputFile);
    return head;
}