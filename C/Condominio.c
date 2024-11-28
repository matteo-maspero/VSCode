#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define INPUT_PATH "D:\\VSCode\\Workspace\\apartments.txt" //"C:\\Users\\mat.masdasdpero\\VSCode\\Workspace\\suites.txt"

//	TYPES
//	--	--	--	--	--	--	--	--	--	--	--	--	--	--	--	--	--	--	--	--	--	--	--	//

/**
	@brief Pseudo-boolean type. Should only be used to store 0/1.
*/
typedef unsigned char Bool;

/**
	@brief Payment information for an apartment.
	@param number Payment number
	@param amount Payment amount
	@param expiration Payment expiration date
	@param paid True if the payment has been made, false otherwise
*/
typedef struct {
	int number;
	int amount;
	char* expiration;
	Bool paid;
} Payment;

/**
	@brief Apartment information.
	@param number Apartment number
	@param floor Apartment floor
	@param rooms Number of rooms in the apartment
	@param name Owner's first name
	@param surname Owner's last name
	@param Payments List of payments for the apartment
	@param next Next apartment in the list
*/
typedef struct Apartment {
	int number;
	int floor;
	int rooms;
	char* name;
	char* surname;
	Payment* Payments;
	struct Apartment *next;
} Apartment;

/**
	@brief Generic reference type for a node in a list.
*/
typedef Apartment* Node;

//	GENERAL FUNCTIONS
//	--	--	--	--	--	--	--	--	--	--	--	--	--	--	--	--	--	--	--	--	--	--	--	//

/**
	@brief Clears the console and displays the main menu.
*/
void clearConsoleAndPrintMenu();

//	LISTS HANDLING
//	--	--	--	--	--	--	--	--	--	--	--	--	--	--	--	--	--	--	--	--	--	--	--	//

/**
	@brief Initializes a new node with the given data.
	@param number Apartment number
	@param floor Apartment floor
	@param rooms Number of rooms in the apartment
	@param name Owner's first name
	@param surname Owner's last name
	@return The created node
*/
Node createNode(int number, int floor, int rooms, char *name, char *surname);

/**
	@brief Inserts a new node at the head of the list.
	@param head Head of the list
	@param number Apartment number
	@param floor Apartment floor
	@param rooms Number of rooms in the apartment
	@param name Owner's first name
	@param surname Owner's last name
	@return The new head of the list
*/
Node pushNode(Node head, int number, int floor, int rooms, char *name, char *surname);

/**
	@brief Deallocates the memory occupied by all nodes in the list.
	@param head Head of the list
*/
void destroyList(Node head);

//	I/O HANDLING
//	--	--	--	--	--	--	--	--	--	--	--	--	--	--	--	--	--	--	--	--	--	--	--	//

/**
	@brief Reads an integer from the standard input. Can be constrained to a range, extremes included.
	@param request Message to display to the user
	@param min Minimum value allowed
	@param max Maximum value allowed (if lower than min, the check will be skipped)
	@param retry Message to display if the input is invalid
	@return The read integer
*/
int readInt(const char* request, int min, int max, const char* retry);

//	GENERAL FUNCTIONS
//	--	--	--	--	--	--	--	--	--	--	--	--	--	--	--	--	--	--	--	--	--	--	--	//

int main() {
	Node head = NULL;
	int operationToPerform;

	while(1) {
		clearConsoleAndPrintMenu();
		operationToPerform = readInt("\nScegli un'operazione da eseguire: ", 0, 8, "Operazione non valida. Riprova: ");

		switch(operationToPerform) {
			case 0:
				printf("\nArrivederci!");
				return 0;
			default:
				perror("Should not happen at all.");
		}
	}

	return 0;
}

void clearConsoleAndPrintMenu() {
	//system("cls");	//	Bugged on VSCode
	printf("\033[H\033[J");	//	Clears the console

	printf(
		"Operazioni disponibili:"
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

		if(min > max || dest >= min && dest <= max)
			break;

		printf(retry);
	}

	return dest;
}