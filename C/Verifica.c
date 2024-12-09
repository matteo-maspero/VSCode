#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//#define ASSETS_PATH "C:\\Users\\matte\\Documents\\VSCode\\Assets\\"
#define ASSETS_PATH "C:\\Users\\mat.maspero\\VSCode\\Assets\\"
#define INPUT_FILE "listacomuni"

/*
	TYPES
*/

typedef struct Comune {
	char *istat;
	char *name;
	char *province;
	char *region;
	char *prefix;
	char *postalCode;
	char *fiscalCode;
	int population;
	char *link;
	struct Comune* next;
} Comune;

typedef Comune* Node;

/*
	PROTOYPES
*/

int inputInt(const char *prompt, int min, int max);
char *inputStr(const char *prompt);

Node createNode(char *istat, char *name, char *province, char *region, char *prefix, char *postalCode, char *fiscalCode, int population, char *link);
Node appendNode(Node head, char *istat, char *name, char *province, char *region, char *prefix, char *postalCode, char *fiscalCode, int population, char *link);
Node freeList(Node head);

void printMenu();

const char *getFullPath(char *fileName, const char *extension);
Node loadComuni(Node head, char *fileName);
void saveDataToDatFile(Node head, char *fileName);
void readDataFromDatFile(char *fileName);

/*
	MAIN
*/

int main() {
	Node head = NULL;
	int choice;
	char *fileName;
	head = loadComuni(head, (char*) INPUT_FILE);

	while(1) {
		printMenu();
		choice = inputInt("Scelta: ", 0, 4);

		switch(choice) {
		case 1:
			fileName = inputStr("Inserisci il nome della regione: ");
			saveDataToDatFile(head, fileName);
			break;
		case 2:
			fileName = inputStr("Inserisci il nome della regione: ");
			readDataFromDatFile(fileName);
			break;
		case 0:
			printf("Arrivederci!\n");
			return 0;
		}
	}

	return 0;
}

/*
	FUNCTIONS
*/

int inputInt(const char *prompt, int min, int max) {
	int input;
	printf(prompt);
	scanf("%d", &input);

	if(min > max)
		return input;

	while(input < min || input > max) {
		printf("Valore non valido. Riprova: ");
		scanf("%d", &input);
	}

	return input;
}

char *inputStr(const char *prompt) {
	char temp[32];
	printf(prompt);
	while(getchar() != '\n');	
	scanf("%[^\n]", temp);

	char *result = (char*) malloc(sizeof(char) * (strlen(temp) + 1));
	strcpy(result, temp);
	return result;
}

Node createNode(char *istat, char *name, char *province, char *region, char *prefix, char *postalCode, char *fiscalCode, int population, char *link) {
	Node newNode = (Node) malloc(sizeof(Comune));
	newNode->istat = istat;
	newNode->name = name;
	newNode->province = province;
	newNode->region = region;
	newNode->prefix = prefix;
	newNode->postalCode = postalCode;
	newNode->fiscalCode = fiscalCode;
	newNode->population = population;
	newNode->link = link;
	newNode->next = NULL;
	return newNode;
}

Node appendNode(Node head, char *istat, char *name, char *province, char *region, char *prefix, char *postalCode, char *fiscalCode, int population, char *link) {
	if(head == NULL)
		return createNode(istat, name, province, region, prefix, postalCode, fiscalCode, population, link);
	
	Node current = head;
	
	while(current->next != NULL)
		current = current->next;
	
	current->next = createNode(istat, name, province, region, prefix, postalCode, fiscalCode, population, link);;
	return head;
}

Node freeList(Node head) {
	Node toBeFreed;

	while(head != NULL) {
		toBeFreed = head;
		free(toBeFreed);
		head = head->next;
	}

	return NULL;
}

void printMenu() {
	printf(
		"+-------------------------------------------------------------------------------+\n"
		"| 1. Salva i dati di una regione a scelta su file                               |\n"
		"| 2. Visualizza i dati di una regione a scelta                                  |\n"
		"| 3. Visualizza il numero di abitanti di ogni provincia in una regione a scelta |\n"
		"| 4. Visualizza il numero di comuni in una regione a scelta                     |\n"
		"| 0. Termina il loop                                                            |\n"
		"+-------------------------------------------------------------------------------+\n"
	);
}

const char *getFullPath(char *fileName, const char *extension) {
	char *fullPath = (char*) malloc( sizeof(char) * (strlen(ASSETS_PATH) + strlen(fileName) + strlen(extension) + 1) );
	strcpy(fullPath, ASSETS_PATH);
	strcat(fullPath, fileName);
	strcat(fullPath, extension);
	return (const char*) fullPath;
}

Node loadComuni(Node head, char *fileName) {
	FILE *inputFile = fopen(getFullPath(fileName, ".txt"), "r");

	if(inputFile == NULL) {
		printf("Errore nell'apertura del file %s\n", fileName);
		exit(1);
	}

	if(head != NULL)
		head = freeList(head);

	int population;

	while(1) {
		char *istat = (char*) malloc(sizeof(char) * 5);
		char *name = (char*) malloc(sizeof(char) * 32);
		char *province = (char*) malloc(sizeof(char) * 3);
		char *region = (char*) malloc(sizeof(char) * 32);
		char *prefix = (char*) malloc(sizeof(char) * 4);
		char *postalCode = (char*) malloc(sizeof(char) * 6);
		char *fiscalCode = (char*) malloc(sizeof(char) * 8);
		char *link = (char*) malloc(sizeof(char) * 64);
		
		if(fscanf(inputFile, "%[^;];%[^;];%[^;];%[^;];%[^;];%[^;];%[^;];%d;%s\n", istat, name, province, region, prefix, postalCode, fiscalCode, &population, link) != 9)
			break;

		head = appendNode(head, istat, name, province, region, prefix, postalCode, fiscalCode, population, link);
	}

	fclose(inputFile);
	return head;
}

void saveDataToDatFile(Node head, char *fileName) {
	FILE *outputFile = fopen(getFullPath(fileName, ".dat"), "wb");

	if(outputFile == NULL) {
		printf("Errore nell'apertura del file %s\n", fileName);
		exit(1);
	}

	while(head != NULL) {
		if(strcmp(head->region, fileName) == 0) {
			fwrite(head->istat, sizeof(char), strlen(head->istat) + 1, outputFile);
			fwrite(head->name, sizeof(char), strlen(head->name) + 1, outputFile);
			fwrite(head->province, sizeof(char), strlen(head->province) + 1, outputFile);
			fwrite(head->prefix, sizeof(char), strlen(head->prefix) + 1, outputFile);
			fwrite(head->postalCode, sizeof(char), strlen(head->postalCode) + 1, outputFile);
			fwrite(head->fiscalCode, sizeof(char), strlen(head->fiscalCode) + 1, outputFile);
			fwrite(&(head->population), sizeof(int), 1, outputFile);
			fwrite("\n", sizeof(char), 2, outputFile);
		}

		head = head->next;
	}

	fclose(outputFile);
}

void readDataFromDatFile(char *fileName) {
	FILE *inputFile = fopen(getFullPath(fileName, ".dat"), "rb");

	if(inputFile == NULL) {
		printf("Errore nell'apertura del file %s\n", fileName);
		exit(1);
	}

	char istat[5];
	char name[32];
	char province[3];
	char prefix[4];
	char postalCode[6];
	char fiscalCode[8];
	int population;

	while(fread(istat, sizeof(char), sizeof(istat), inputFile) == sizeof(istat)) {
		fread(name, sizeof(char), sizeof(name), inputFile);
		fread(province, sizeof(char), sizeof(province), inputFile);
		fread(prefix, sizeof(char), sizeof(prefix), inputFile);
		fread(postalCode, sizeof(char), sizeof(postalCode), inputFile);
		fread(fiscalCode, sizeof(char), sizeof(fiscalCode), inputFile);
		fread(&population, sizeof(int), 1, inputFile);
		fseek(inputFile, 1, SEEK_CUR);

		printf("\tIstat: %s\n", istat);
		printf("\tName: %s\n", name);
		printf("\tProvince: %s\n", province);
		printf("\tPrefix: %s\n", prefix);
		printf("\tPostal Code: %s\n", postalCode);
		printf("\tFiscal Code: %s\n", fiscalCode);
		printf("\tPopulation: %d\n", population);
		printf("\n");
	}

	fclose(inputFile);
}