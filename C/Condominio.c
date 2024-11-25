#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define INPUT_PATH "C:\\Users\\mat.masdasdpero\\VSCode\\Workspace\\suites.txt"

//	TYPES
//	--	--	--	--	--	--	--	--	--	--	--	--	--	--	--	--	--	--	--	--	--	--	--	//
typedef unsigned char Bool;

typedef struct {
	int number;
	int amount;
	Bool paid;
	char* expiration;
} Payment;

typedef struct Suite {
	int number;
	int floor;
	int rooms;
	int nPayments;
	
	Payment Payments[4];
	char name[32];
	char surname[32];
	struct Suite *next;
} Suite;

typedef Suite* Node;

//	MAIN FUNCTIONS
//	--	--	--	--	--	--	--	--	--	--	--	--	--	--	--	--	--	--	--	--	--	--	--	//
void printMenu();

void listSuites(Node head);
Node loadSuites(Node head);
void saveSuites(Node head);

//	LISTS HANDLING
//	--	--	--	--	--	--	--	--	--	--	--	--	--	--	--	--	--	--	--	--	--	--	--	//
Node createNode(int number, int floor, int rooms, char *name, char *surname);
Node pushNode(Node head, int number, int floor, int rooms, char *name, char *surname);
void freeList(Node head);

//	I/O HANDLING
//	--	--	--	--	--	--	--	--	--	--	--	--	--	--	--	--	--	--	--	--	--	--	--	//
int readInt(const char* request);
char* readString(const char* format, const char* request);

int main() {
	Node head = NULL;
	int choice;

	while(1) {
		printMenu();
		choice = readInt("\nScegli l'operazione da eseguire: ");

		switch(choice) {
			case 1:
				char name[32];
				char surname[32];

				printf("\n\tInserisci i nome e cognome del proprietario: (nome cognome) ");
				scanf("%s %s", name, surname);
				
				head = pushNode(
					head,
					readInt("\tInserisci il numero: "),
					readInt("\tInserisci il piano: "),
					readInt("\tInserisci il numero di stanze: "),
					name,
					surname
				);

				break;
			case 2:
				listSuites(head);
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
				saveSuites(head);
				break;
			case 8:
				freeList(head);
				head = loadSuites(head);
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

void listSuites(Node head) {
	while(head != NULL) {
		printf(
			"\n\tAppartamento %d, piano %d, %d stanze"
			"\n\tProprietario: %s %s",
			head->number,
			head->floor,
			head->rooms,
			head->name,
			head->surname
		);

		head = head->next;
	}
}

Node loadSuites(Node head) {
	FILE* inputFile = fopen(INPUT_PATH, "r");

	if(inputFile == NULL)
		perror("Apertura file fallita");

	int floor, number, rooms;
	char name[32];
	char surname[32];

	while(fscanf(inputFile, "%d\t%d\t%d\t%s\t%s", &floor, &number, &rooms, name, surname) != EOF)
		head = pushNode(head, floor, number, rooms, name, surname);

	fclose(inputFile);
	return head;
}

void saveSuites(Node head) {
	FILE* inputFile = fopen(INPUT_PATH, "w");

	if(inputFile == NULL)
		perror("Apertura file fallita");

	while(head != NULL) {
		fprintf(inputFile, "%d\t%d\t%d\t%s\t%s\n", head->floor, head->number, head->rooms, head->name, head->surname);
		head = head->next;
	}

	fclose(inputFile);
}

//	LISTS HANDLING
//	--	--	--	--	--	--	--	--	--	--	--	--	--	--	--	--	--	--	--	--	--	--	--	//
Node createNode(int number, int floor, int rooms, char *name, char *surname) {
	Node dest = (Node) malloc(sizeof(Suite));
	dest->floor = floor;
	dest->number = number;
	dest->rooms = rooms;
	dest->next = NULL;
	dest->nPayments = 0;

	strcpy(dest->name, name);
	strcpy(dest->surname, surname);
	return dest;
}

Node pushNode(Node head, int number, int floor, int rooms, char *name, char *surname) {
	Node newNode = createNode(number, floor, rooms, name, surname);
	newNode->next = head;
	return newNode;
}

void freeList(Node head) {
	Node toPop;

	while(head != NULL) {
		toPop = head;
		head = head->next;
		free(toPop);
	}
}

//	I/O HANDLING
//	--	--	--	--	--	--	--	--	--	--	--	--	--	--	--	--	--	--	--	--	--	--	--	//

int readInt(const char* request) {
	int dest;
	printf(request);
	scanf("%d", &dest);
	return dest;
}