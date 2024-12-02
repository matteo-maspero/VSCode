/*
	Ho riscritto parte del programma della verifica includendo solo le funzioni strettamente necessarie per una maggiore pulizia,
	per avere un focus maggiore sulle richieste e per velocizzare la compilazione del programma.
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//	--	--	--	--	--	--	--	--	//
//	TYPES & GLOBAL VALUES
//	--	--	--	--	--	--	--	--	//

//	Cambiare il percorso in base alla propria configurazione
#define BASE_PATH "C:/Users/Matteo/Desktop/"
#define TXT_NAME BASE_PATH "patients.txt"
#define DAT_NAME BASE_PATH "patients.dat"

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
Patient* readQueueFromTxt(Patient* head);
void writeQueueToTxt(Patient* head);
Patient* readQueueFromDat(Patient* head);
void writeQueueToDat(Patient* head);

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
		"\n| 2. Stampa la coda in console         |"
		"\n| 3. Leggi la coda dal file di testo   |"
		"\n| 4. Leggi la coda dal file binario    |"
		"\n| 5. Stampa la coda nel file di testo  |"
		"\n| 6. Stampa la coda nel file binario   |"
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
		printf("\nCoda dei pazienti:");
		printQueue(head);
		break;

		case 3:
		head = readQueueFromTxt(head);
		printf("\nCoda dei pazienti aggiornata.");
		break;

		case 4:
		head = readQueueFromDat(head);
		printf("\nCoda dei pazienti aggiornata.");
		break;

		case 5:
		writeQueueToTxt(head);
		printf("\nCoda dei pazienti salvata.");
		break;

		case 6:
		writeQueueToDat(head);
		printf("\nCoda dei pazienti salvata.");
		break;

		default:
		printf("\nScelta non valida.");
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
Patient* readQueueFromTxt(Patient* head) {
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

void writeQueueToTxt(Patient* head) {
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

Patient* readQueueFromDat(Patient* head) {
	FILE* inputFile = fopen(DAT_NAME, "rb");

	if (inputFile == NULL)
		exit(1);

	int age;
	int emergency;

	while(fread(&age, sizeof(int), 1, inputFile) && fread(&emergency, sizeof(int), 1, inputFile))
		head = addPatientToQueue(head, age, emergency);

	fclose(inputFile);
	return head;
}

void writeQueueToDat(Patient* head) {
	if(head == NULL)
		return;

	FILE* outputFile = fopen(DAT_NAME, "wb");

	if (outputFile == NULL)
		exit(1);

	while (head != NULL) {
		fwrite(&head->age, sizeof(int), 1, outputFile);
		fwrite(&head->emergency, sizeof(int), 1, outputFile);
		head = head->next;
	}

	fclose(outputFile);
}