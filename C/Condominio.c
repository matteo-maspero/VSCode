#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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
	char *name;
	char *surname;
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
Node readSuite(Node head);

void printSuite(Node head);
void printAllSuites(Node head);

int main() {
	Node head = NULL;

	head = readSuite(head);
	head = readSuite(head);
	head = readSuite(head);
	head = readSuite(head);

	return 0;
}

//	LISTS HANDLING
//	--	--	--	--	--	--	--	--	--	--	--	--	--	--	--	--	--	--	--	--	--	--	--	//
Node createNode(int floor, int number, int rooms, char *name, char *surname) {
	Node dest = (Node) malloc(sizeof(Suite));
	dest->floor = floor;
	dest->number = number;
	dest->rooms = rooms;
	dest->name = name;
	dest->surname = surname;
	dest->next = NULL;
	return dest;
}

Node insertNode(Node head, int floor, int number, int rooms, char *name, char *surname) {
	if(head == NULL)
		return createNode(floor, number, rooms, name, surname);
	
	if(head->floor > floor && head->number > number) {
		Node dest = createNode(floor, number, rooms, name, surname);
		dest->next = head;
		return dest;
	}

	Node current = head->next;
	//TODO
	while(current != NULL) {
		if(current->floor < floor)
			if(current->number < number) {
				Node dest = createNode(floor, number, rooms, name, surname);
				dest->next = current->next;
				current->next = dest;
				return head;
			}

		current = current->next;
	}

	return head;
}

//	I/O HANDLING
//	--	--	--	--	--	--	--	--	--	--	--	--	--	--	--	--	--	--	--	--	--	--	--	//
int readInt(const char* request) {
	printf("%s", request);
	int dest;
	scanf("%d", &dest);
	return dest;
}

char* readString(const char* request) {
	printf("%s", request);
	char temp[32];
	scanf("%s", temp);
	
	char* dest = (char*) malloc(sizeof(char) * strlen(temp));
	strcpy(dest, temp);
	return dest;
}

Node readSuite(Node head) {
	int floor, number, rooms;
	char* name,* surname;

	printf("\nInserisci i dati della suite:");
	floor = readInt("\n\tPiano: ");
	number = readInt("\tId suite: ");
	rooms = readInt("\tNumero di vani: ");
	name = readString("\tNome proprietario: ");
	surname = readString("\tCognome proprietario: ");

	return insertNode(head, floor, number, rooms, name, surname);
}