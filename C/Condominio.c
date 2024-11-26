#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define INPUT_PATH "D:\\VSCode\\Workspace\\apartments.txt" //"C:\\Users\\mat.masdasdpero\\VSCode\\Workspace\\suites.txt"

//	TYPES
//	--	--	--	--	--	--	--	--	--	--	--	--	--	--	--	--	--	--	--	--	--	--	--	//
typedef unsigned char Bool;

typedef struct {
	int number;
	int amount;
	char* expiration;
	Bool paid;
} Payment;

typedef struct Apartment {
	int number;
	int floor;
	int rooms;
	char* name;
	char* surname;
	Payment* Payments;
	struct Apartment *next;
} Apartment;

typedef Apartment* Node;

//	MAIN FUNCTIONS
//	--	--	--	--	--	--	--	--	--	--	--	--	--	--	--	--	--	--	--	--	--	--	--	//


//	LISTS HANDLING
//	--	--	--	--	--	--	--	--	--	--	--	--	--	--	--	--	--	--	--	--	--	--	--	//

/*
	@brief Initializes a new node with the given data
	@param number Apartment number
	@param floor Apartment floor
	@param rooms Number of rooms in the apartment
	@param name Owner's first name
	@param surname Owner's last name
	@return The created node
*/
Node createNode(int number, int floor, int rooms, char *name, char *surname);

/*
	@brief Inserts a new node at the head of the list
	@param head Head of the list
	@param number Apartment number
	@param floor Apartment floor
	@param rooms Number of rooms in the apartment
	@param name Owner's first name
	@param surname Owner's last name
	@return The new head of the list
*/
Node pushNode(Node head, int number, int floor, int rooms, char *name, char *surname);

/*
	@brief Deallocates the memory occupied by all nodes in the list
	@param head Head of the list
*/
void destroyList(Node head);

//	I/O HANDLING
//	--	--	--	--	--	--	--	--	--	--	--	--	--	--	--	--	--	--	--	--	--	--	--	//

/*
	@brief Reads an integer from the standard input
	@param request Message to display to the user
	@param min Minimum value allowed
	@param max Maximum value allowed (if lower than min, the check will be skipped)
	@param retry Message to display if the input is invalid
	@return The read integer
*/
int readInt(const char* request, int min, int max, const char* retry);

//	FUNCTIONS
//	--	--	--	--	--	--	--	--	--	--	--	--	--	--	--	--	--	--	--	--	--	--	--	//

int main() {
	Node head = NULL;
	int choice;

	while(1) {
		switch(choice) {
			case 1:
				break;
			case 2:
				break;
			case 3:
				break;
			case 4:
				break;
			case 5:
				break;
			case 6:
				break;
			case 7:
				break;
			case 8:
				freeList(head);
				break;
			case 0:
				exit(0);
			default:
				perror("Operazione non valida");
		}
	}

	return 0;
}

//	MAIN FUNCTIONS
//	--	--	--	--	--	--	--	--	--	--	--	--	--	--	--	--	--	--	--	--	--	--	--	//

void printMenu() {
	printf(
		"\nOperazioni disponibili:"
		"\n\t1. Inserisci un nuovo appartamento"
		"\n\t2. Visualizza la lista degli appartamenti"
		"\n\t3. Inserisci le rate annuali dell'appartamento"
		"\n\t4. Paga una rata annuale dell'appartamento"
		"\n\t5. Visualizza le rate annuali dell'appartamento"
		"\n\t6. Visualizza le rate annuali non pagate dell'appartamento"
		"\n\t7. Salva le informazioni su file"
		"\n\t8. Carica le informazioni da file"
		"\n\t0. Esci"
	);
}

//	LISTS HANDLING
//	--	--	--	--	--	--	--	--	--	--	--	--	--	--	--	--	--	--	--	--	--	--	--	//

Node createNode(int number, int floor, int rooms, char *name, char *surname) {
	Node dest = (Node) malloc(sizeof(Apartment));
	dest->floor = floor;
	dest->number = number;
	dest->rooms = rooms;
	dest->name = name;
	dest->surname = surname;
	dest->next = NULL;
	return dest;
}

Node pushNode(Node head, int number, int floor, int rooms, char *name, char *surname) {
	Node newNode = createNode(number, floor, rooms, name, surname);
	newNode->next = head;
	return newNode;
}

void destroyList(Node head) {
	Node toPop;

	while(head != NULL) {
		toPop = head;
		head = head->next;
		free(toPop);
	}
}

//	I/O HANDLING
//	--	--	--	--	--	--	--	--	--	--	--	--	--	--	--	--	--	--	--	--	--	--	--	//

int readInt(const char* request, int min, int max, const char* retry) {
	int dest;
	printf(request);

	while(1) {
		scanf("%d", &dest);

		if(min > max || dest > min && dest < max)
			break;

		printf(retry);
	}

	return dest;
}