#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//	--	--	--	--	--	--	--	--	//
//	TYPES & GLOBAL VALUES
//	--	--	--	--	--	--	--	--	//

#define TXT_NAME "patients.txt"
#define DAT_NAME "patients.dat"

typedef struct Patient{
	int age;
	int emergency;
	Patient *next;
} Patient;

//	--	--	--	--	--	--	--	--	//
//	FUNCTIONS
//	--	--	--	--	--	--	--	--	//

//	Utils
void chooseOption(int* choice);
Patient* performAction(Patient* head, int choice);

//	Lists utils
Patient* createPatient(int age, int emergency);
Patient* pushPatient(Patient* head, int age);
Patient* appendPatient(Patient* head, int age);
Patient* addPatientToQueue(Patient* head, int age, int emergency);
void printQueue(Patient* head);

//	Files utils
Patient* readPatientsFromTxt(Patient* head);
void writePatientsToTxt(Patient* head);
Patient* readPatientsFromDat(Patient* head);
void writePatientsToDat(Patient* head);

//	Main
int main() {
	Patient* queue = NULL;
	int choice;

	while(1) {
		chooseOption(&choice);

		if(choice == 0) {
			printf("\nChiusura in corso...");
			break;
		}

		queue = performAction(queue, choice);
	}

	return 0;
}

//	Utils
void chooseOption(int* choice) {
	printf(
		"\n+--------------------------------------+"
		"\n| Segliere una delle seguenti opzioni  |"
		"\n+--------------------------------------+"
		"\n| 0. Termina il programma              |"
		"\n| 1. Aggiungi un paziente in coda      |"
		"\n| 2. Leggi la coda dal file di testo   |"
		"\n| 3. Stampa la coda nel file di testo  |"
		"\n| 4. Stampa la coda in console         |"
		"\n+--------------------------------------+"
		"\n\tScelta: "
	);

	scanf("%d", choice);
}

Patient* performAction(Patient* head, int choice) {
	switch(choice) {
		case 1:
		int age;
		int emergency;
		
		printf(
			"\nInserisci i seguenti dati del paziente:"
			"\n\tEta': "
		);
		scanf("%d", &age);
		printf("\tEmergenza: [0/1] ");
		scanf("%d", &emergency);

		head = addPatientToQueue(head, age, emergency);
		break;

		case 2:
		head = readPatientsFromTxt(head);
		printf("\nCoda dei pazienti aggiornata.");
		break;

		case 3:
		writePatientsToTxt(head);
		printf("\nCoda dei pazienti salvata.");
		break;

		case 4:
		printf("\nCoda dei pazienti:");
		printQueue(head);
		break;

		default:
		printf("\nScelta non valida.");
		break;
	}

	return head;
}

//	List utils
Patient* createPatient(int age, int emergency) {
	Patient* newPatient = (Patient*) malloc(sizeof(Patient));
	newPatient->age = age;
	newPatient->emergency = emergency;
	newPatient->next = NULL;
	return newPatient;
}

Patient* pushPatient(Patient* head, int age) {
	Patient* newPatient = createPatient(age, 1);
	newPatient->next = head;
	return newPatient;
}

Patient* appendPatient(Patient* head, int age) {
	if(head == NULL)
		return createPatient(age, 0);

	Patient* current = head;

	while(current->next != NULL)
		current = current->next;

	current->next = createPatient(age, 0);
	return head;
}

Patient* addPatientToQueue(Patient* head, int age, int emergency) {
	if(emergency)
		return pushPatient(head, age);
	else
		return appendPatient(head, age);
}

void printQueue(Patient* head) {
	while (head != NULL) {
		printf("\n\tEta' paziente: %d", head->age);

		if(head->emergency)
			printf(" (Emergenza)");

		head = head->next;
	}
}

//	Files utils
Patient* readPatientsFromTxt(Patient* head) {
	FILE* inputFile = fopen(TXT_NAME, "r");

	if (inputFile == NULL)
		exit(1);

	int age;
	int emergency;

	while(fscanf(inputFile, "%d\t%d", &age, &emergency) != EOF)
		head = addPatientToQueue(head, age, emergency);
	
	fclose(inputFile);
	return head;
}

void writePatientsToTxt(Patient* head) {
	if(head == NULL)
		return;

	FILE* outputFile = fopen(TXT_NAME, "w");

	if (outputFile == NULL)
		exit(1);

	while (head != NULL) {
		fprintf(outputFile, "%d\t%d\n", head->age, head->emergency);
		head = head->next;
	}

	fclose(outputFile);
}