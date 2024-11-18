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
	char emergency;
	Patient *next;
} Patient;

//	--	--	--	--	--	--	--	--	//
//	FUNCTIONS
//	--	--	--	--	--	--	--	--	//

//	Utils
void chooseOption(char* choice);

//	Lists utils
Patient* createPatient(int age, char emergency);
Patient* pushPatient(Patient* head, int age);
Patient* appendPatient(Patient* head, int age);
Patient* addPatientToQueue(Patient* head, int age, char emergency);
void printQueue(Patient* head);

//	Files utils
Patient* readPatientsFromTxt(Patient* head);
void writePatientsToTxt(Patient* head);
Patient* readPatientsFromDat(Patient* head);
void writePatientsToDat(Patient* head);

//	Main
int main() {
	Patient* queue = NULL;
	char choice;

	while(1) {
		chooseOption(&choice);

		if(choice == 0) {
			printf("\nChiusura in corso...");
			break;
		}
		else if(choice == 1) {
			int age;
			char emergency;

			printf(
				"\nInserisci i seguenti dati del paziente:"
				"\n\tEta': "
			);
			
			scanf("%d", &age);
			printf("\tEmergenza: [0/1] ");
			scanf("\n%d", &emergency);
			
			queue = addPatientToQueue(queue, age, emergency);
		}
		else if(choice == 2) {
			queue = readPatientsFromTxt(queue);
			printf("\nCoda dei pazienti aggiornata.");
		}
		else if(choice == 3) {
			writePatientsToTxt(queue);
			printf("\nCoda dei pazienti salvata.");
		}
		else if(choice == 4) {
			printf("\nCoda dei pazienti:");
			printQueue(queue);
		}
		else {
			printf("\nScelta non valida.");
		}
	}

	return 0;
}

//	Utils
void chooseOption(char* choice) {
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

//	List utils
Patient* createPatient(int age, char emergency) {
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

Patient* addPatientToQueue(Patient* head, int age, char emergency) {
	if(emergency)
		return pushPatient(head, age);
	else
		return appendPatient(head, age);
}

void printQueue(Patient* head) {
	while (head != NULL) {
		printf(
			"\nDati del paziente:"
			"\n\tEta': %d,"
			"\n\tEmergency: %c",
			head->age, head->emergency
		);
		head = head->next;
	}
}

//	Files utils
Patient* readPatientsFromTxt(Patient* head) {
	FILE* inputFile = fopen(TXT_NAME, "r");

	if (inputFile == NULL)
		exit(1);

	int age;
	char emergency;

	while(fscanf(inputFile, "%d\t%c", &age, &emergency) != EOF)
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
		fprintf(outputFile, "%d\t%c\n", head->age, head->emergency);
		head = head->next;
	}

	fclose(outputFile);
}