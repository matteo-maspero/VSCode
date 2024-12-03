#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define FILE_PATH "C:\\Users\\matte\\documents\\VSCode\\Workspace\\suites.txt"
//#define FILE_PATH "C:\\Users\\mat.maspero\\documents\\VSCode\\Workspace\\suites.txt"

//	TYPES
//	--	--	--	--	--	--	--	--	--	--	--	--	--	--	--	--	--	--	--	--	--	--	--	//

/*
	@brief Pseudo-boolean type. Should only be used to store 0/1.
*/
typedef unsigned char Bool;

/*
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

/*
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

/*
	@brief Generic reference type for a node in a list.
*/
typedef Apartment* Node;

//	GENERAL FUNCTIONS
//	--	--	--	--	--	--	--	--	--	--	--	--	--	--	--	--	--	--	--	--	--	--	--	//

/*
	@brief Clears the console and displays the main menu.
*/
void clearConsoleAndPrintMenu();

/*
	@brief Lists all apartments in the list.
	@param head Head of the list
*/
void listApartments(Node head);

/*
	@brief Searches for an apartment in the list and reads the payments for it.
	@param head Head of the list
*/
void findApartmentAndReadPayments(Node head);

/*
	@brief Searches for an apartment in the list and pays a payment for it.
	@param head Head of the list
*/
void findApartmentAndPay(Node head);

/*
	@brief Lists all payments for an apartment.
	@param head Head of the list
*/
void listPayments(Node head);

/*
	@brief Lists all unpaid payments for an apartment.
	@param head Head of the list
*/
void listUnpaidPayments(Node head);

/*
	@brief Loads the list of apartments from a file.
	@return The head of the list
*/
Node loadApartmentsFromFile();

/*
	@brief Saves the list of apartments to a file.
	@param head Head of the list
*/
void saveApartmentsToFile(Node head);

//	LISTS HANDLING
//	--	--	--	--	--	--	--	--	--	--	--	--	--	--	--	--	--	--	--	--	--	--	--	//

/*
	@brief Initializes a new node with the given data.
	@param number Apartment number
	@param floor Apartment floor
	@param rooms Number of rooms in the apartment
	@param name Owner's first name
	@param surname Owner's last name
	@return The created node
*/
Node createNode(int number, int floor, int rooms, char *name, char *surname);

/*
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

/*
	@brief Searches for an apartment in the list.
	@param head Head of the list
	@param number Apartment number
	@param floor Apartment floor
	@return The found apartment, or NULL if not found
*/
Node findNode(Node head, int number, int floor);

/*
	@brief Deallocates the memory occupied by all nodes in the list.
	@param head Head of the list
*/
void destroyList(Node head);

//	I/O HANDLING
//	--	--	--	--	--	--	--	--	--	--	--	--	--	--	--	--	--	--	--	--	--	--	--	//

/*
	@brief Reads an integer from the standard input. Can be constrained to a range, extremes included.
	@param request Message to display to the user
	@param min Minimum value allowed
	@param max Maximum value allowed (if lower than min, the check will be skipped)
	@return The read integer
*/
int readInt(const char* request, int min, int max);

/*
	@brief Reads a string from the standard input.
	@param request Message to display to the user
	@param maxLength Maximum length of the string
	@return The read string
*/
char* readString(const char* request, int maxLength);

/*
	@brief Reads the payment information for an apartment.
	@param apartment Apartment to read the payments for
	@return The array of payments
*/
Payment* readPayments(Apartment* apartment);

//	GENERAL FUNCTIONS
//	--	--	--	--	--	--	--	--	--	--	--	--	--	--	--	--	--	--	--	--	--	--	--	//

int main() {
	Node head = NULL;
	int operationToPerform;

	while(1) {
		clearConsoleAndPrintMenu();
		operationToPerform = readInt("Scegli un'operazione da eseguire: ", 0, 8);

		switch(operationToPerform) {
			case 1:
				head = pushNode(
					head,
					readInt("Inserisci il numero dell'appartamento: ", 1, 0),
					readInt("Inserisci il piano dell'appartamento: ", 1, 0),
					readInt("Inserisci il numero di stanze dell'appartamento: ", 1, 0),
					readString("Inserisci il nome del proprietario: ", 32),
					readString("Inserisci il cognome del proprietario: ", 32)
				);
				break;
			case 2:
				printf("Lista degli appartamenti:\n");
				listApartments(head);
				break;
			case 3:
				findApartmentAndReadPayments(head);
				break;
			case 4:
				findApartmentAndPay(head);
				break;
			case 5:
				listPayments(head);
				break;
			case 6:
				listUnpaidPayments(head);
				break;
			case 7:
				saveApartmentsToFile(head);
				break;
			case 8:
				head = loadApartmentsFromFile();
				break;
			case 0:
				printf("Arrivederci!");
				return 0;
		}

		printf("\nPremi un tasto per continuare...");
		getchar();
		getchar();
	}

	return 0;
}

void clearConsoleAndPrintMenu() {
	//system("cls");	//	Bugged on VSCode
	printf("\033[H\033[J");	//	Clears the console

	printf(
		"Operazioni disponibili:\n"
		"\t1. Inserisci un nuovo appartamento\n"
		"\t2. Visualizza la lista degli appartamenti\n"
		"\t3. Inserisci le rate annuali dell'appartamento\n"
		"\t4. Paga una rata annuale dell'appartamento\n"
		"\t5. Visualizza le rate annuali dell'appartamento\n"
		"\t6. Visualizza le rate annuali non pagate dell'appartamento\n"
		"\t7. Salva le informazioni su file\n"
		"\t8. Carica le informazioni da file\n"
		"\t0. Esci\n"
	);
}

void listApartments(Node head) {
	while(head != NULL) {
		printf(
			"\tAppartamento %d, piano %d, %d stanze, proprietario %s %s\n",
			head->number,
			head->floor,
			head->rooms,
			head->name,
			head->surname
		);
		head = head->next;
	}
}

void findApartmentAndReadPayments(Node head) {
	int apartmentNumber = readInt("\tInserisci il numero dell'appartamento: ", 1, 0);
	int apartmentFloor = readInt("\tInserisci il piano dell'appartamento: ", 1, 0);
	Node apartment = findNode(head, apartmentNumber, apartmentFloor);

	if(apartment == NULL) {
		printf("\tL'appartamento richiesto non esiste.\n");
		return;
	}

	apartment->Payments = readPayments(apartment);
}

void findApartmentAndPay(Node head) {
	int apartmentNumber = readInt("\tInserisci il numero dell'appartamento: ", 1, 0);
	int apartmentFloor = readInt("\tInserisci il piano dell'appartamento: ", 1, 0);
	Node apartment = findNode(head, apartmentNumber, apartmentFloor);

	if(apartment == NULL) {
		printf("\tL'appartamento richiesto non esiste.\n");
		return;
	}

	int paymentNumber = readInt("\tInserisci il numero della rata da pagare: ", 1, 4) - 1;
	int i;

	for(i = 0; i < 4; i ++) {
		if(apartment->Payments[i].number == paymentNumber) {
			if(apartment->Payments[i].paid) {
				printf("\tLa rata selezionata e' gia' stata pagata.\n");
				return;
			}

			apartment->Payments[i].paid = 1;
			printf("\tRata pagata con successo.\n");
			return;
		}
	}

	printf("\tLa rata selezionata non esiste.\n");
	return;
}

void listPayments(Node head) {
	int apartmentNumber = readInt("\tInserisci il numero dell'appartamento: ", 1, 0);
	int apartmentFloor = readInt("\tInserisci il piano dell'appartamento: ", 1, 0);
	Node apartment = findNode(head, apartmentNumber, apartmentFloor);

	if(apartment == NULL) {
		printf("\tL'appartamento richiesto non esiste.\n");
		return;
	}

	int i;

	for(i = 0; i < 4; i ++) {
		printf(
			"\tRata %d, importo %d, scadenza %s, %s\n",
			apartment->Payments[i].number,
			apartment->Payments[i].amount,
			apartment->Payments[i].expiration,
			apartment->Payments[i].paid ? "pagata" : "non pagata"
		);
	}
}

void listUnpaidPayments(Node head) {
	int apartmentNumber = readInt("\tInserisci il numero dell'appartamento: ", 1, 0);
	int apartmentFloor = readInt("\tInserisci il piano dell'appartamento: ", 1, 0);
	Node apartment = findNode(head, apartmentNumber, apartmentFloor);

	if(apartment == NULL) {
		printf("\tL'appartamento richiesto non esiste.\n");
		return;
	}

	int i;

	for(i = 0; i < 4; i ++) {
		if(!apartment->Payments[i].paid)
			printf(
				"\tRata %d, importo %d, scadenza %s\n",
				apartment->Payments[i].number,
				apartment->Payments[i].amount,
				apartment->Payments[i].expiration
			);
	}
}

Node loadApartmentsFromFile() {
	FILE* file = fopen(FILE_PATH, "r");

	if(file == NULL) {
		printf("\tImpossibile aprire il file per la lettura.\n");
		return NULL;
	}

	Node head = NULL;
	int number, floor, rooms;
	char name[32], surname[32];
	Payment *payments;

	while(fscanf(file, "%d %d %d %s %s", &number, &floor, &rooms, name, surname) == 5)
		head = pushNode(head, number, floor, rooms, name, surname);

	Node current = head;
	int i;

	while(current != NULL) {
		payments = (Payment*) malloc(4 * sizeof(Payment));

		for(i = 0; i < 4; i ++) {
			fscanf(
				file,
				"%d %d %s %hhu",
				&payments[i].number,
				&payments[i].amount,
				payments[i].expiration,
				&payments[i].paid
			);
		}

		current->Payments = payments;
		current = current->next;
	}

	fclose(file);
	return head;
}

void saveApartmentsToFile(Node head) {
	FILE* file = fopen(FILE_PATH, "w");

	if(file == NULL) {
		printf("\tImpossibile aprire il file per la scrittura.\n");
		return;
	}

	while(head != NULL) {
		fprintf(
			file,
			"%d %d %d %s %s\n",
			head->number,
			head->floor,
			head->rooms,
			head->name,
			head->surname
		);

		int i;

		for(i = 0; i < 4; i ++) {
			fprintf(
				file,
				"%d %d %s %d\n",
				head->Payments[i].number,
				head->Payments[i].amount,
				head->Payments[i].expiration,
				head->Payments[i].paid
			);
		}

		head = head->next;
	}

	fclose(file);
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

Node findNode(Node head, int number, int floor) {
	while(head != NULL) {
		if(head->number == number && head->floor == floor)
			return head;
		head = head->next;
	}
	return NULL;
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

int readInt(const char* request, int min, int max) {
	int dest;
	printf(request);

	while(1) {
		if(scanf("%d", &dest) != 1) {
			printf("\tInput non valido. Riprova: ");
			continue;
		}

		if(min > max)
			break;

		if(dest < min || dest > max) {
			printf("\tIl numero scelto non appartiene al range specificato. Riprova: ");
			continue;
		}

		break;
	}

	return dest;
}

char* readString(const char* request, int maxLength) {
	char* dest = (char*) malloc(maxLength * sizeof(char));
	printf(request);
	scanf("%s", dest);

	dest = (char*) realloc(dest, (strlen(dest) + 1) * sizeof(char));
	return dest;
}

char* readDate(const char* request) {
	char temp[6];
	printf(request);
	
	while(scanf("%s", temp) != 1)
		printf("\tInput non valido. Riprova: ");

	char* dest = (char*) malloc(6 * sizeof(char));
	strcpy(dest, temp);
	return dest;
}

Payment* readPayments(Apartment* apartment) {
	Payment* dest = (Payment*) malloc(4 * sizeof(Payment));
	int i;

	for(i = 0; i < 4; i ++) {
		dest[i].number = readInt("\tInserisci il numero della rata: ", 1, 0);
		dest[i].amount = readInt("\tInserisci l'importo della rata: ", 1, 0);
		dest[i].expiration = readDate("\tInserisci la scadenza della rata (gg/mm): ");
		dest[i].paid = 0;
	}

	return dest;
}