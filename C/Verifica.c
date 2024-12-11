#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define ABSPATH "C:/users/matte/documents/vscode/C/"	//	Se necessario cambiare il path, altrimenti lasciare vuoto: ""
#define LISTACOMUNI "listacomuni"
#define ISTATLENGTH 5
#define NOMELENGTH 32
#define PROVINCIALENGTH 3
#define REGIONELENGTH 32
#define PREFISSOLENGTH 4
#define CODICEPOSTALELENGTH 6
#define CODICEFISCALELENGTH 8
#define LINKLENGTH 32

/*
	TYPES
*/

typedef struct Comune {
	char istat[ISTATLENGTH];
	char nome[NOMELENGTH];
	char provincia[PROVINCIALENGTH];
	char prefisso[PREFISSOLENGTH];
	char codicePostale[CODICEPOSTALELENGTH];
	char codiceFiscale[CODICEFISCALELENGTH];
	int popolazione;
	char regione[REGIONELENGTH];
	char link[LINKLENGTH];
	struct Comune *next;
} Comune;

typedef Comune* Node;

/*
	PROTOYPES
*/

void printComuniPerProvince(Node headRegione);
int countComuniOfProvince(Node headRegione, char *provincia);
void printInhabitantsPerProvince(Node headRegione);
char *getProvinceHash(Node headRegione, int *length);
int countInhabitantsOfProvince(Node headRegione, char *provincia);
Node createListFromRegionFile(Node headRegione, char *filename);
void saveRegionDataToFile(Node headRegione, char *filename);
void clearConsoleAndPrintMenu();
Node createListFromTxtFile(Node head, const char *filename);

char *inputString(const char *prompt, int maxLength);
int inputInt(const char *prompt, int min, int max);
const char *buildFilename(char* name, const char *extension);

Node createNode(char *istat, char *nome, char *provincia, char *regione, char *prefisso, char *codicePostale, char *codiceFiscale, int popolazione, char *link);
Node pushNode(Node head, char *istat, char *nome, char *provincia, char *regione, char *prefisso, char *codicePostale, char *codiceFiscale, int popolazione, char *link);
void destroyList(Node head);
void printList(Node head);

/*
	MAIN
*/

int main() {
	Node headComuni = NULL;
	headComuni = createListFromTxtFile(headComuni, LISTACOMUNI);

	while(1) {
		clearConsoleAndPrintMenu();
		int choice = inputInt("Scelta: ", 0, 4);
		
		if(choice == 0) {
			printf("Arrivederci!\n");
			return 0;
		}

		char *filename;
		Node headRegione = NULL;

		switch(choice) {
		case 1:
			filename = inputString("Scrivi il nome della regione di cui si vogliono salvare i dati: ", REGIONELENGTH);
			saveRegionDataToFile(headComuni, filename);
			break;
		case 2:
			filename = inputString("Scrivi il nome della regione di cui si vogliono visualizzare i dati salvati: ", REGIONELENGTH);
			headRegione = createListFromRegionFile(headRegione, filename);
			printf("Regione: %s\n", filename);
			printList(headRegione);
			break;
		case 3:
			filename = inputString("Scrivi il nome della regione di cui si vogliono visualizzare il totale di abitanti per provincia: ", REGIONELENGTH);
			headRegione = createListFromRegionFile(headRegione, filename);
			printInhabitantsPerProvince(headRegione);
			break;
		case 4:
			filename = inputString("Scrivi il nome della regione di cui si vogliono visualizzare il totale di comuni per provincia: ", REGIONELENGTH);
			headRegione = createListFromRegionFile(headRegione, filename);
			printComuniPerProvince(headRegione);
			break;
		}

		printf("Premi invio per continuare...");
		getchar();
	}

	return 0;
}

/*
	FUNCTIONS
*/

void printComuniPerProvince(Node headRegione) {
	int lenght = 0;
	char *provinceHash = getProvinceHash(headRegione, &lenght);
	int i;

	for(i = 0; i < lenght; i = i + 3) {
		int total = countComuniOfProvince(headRegione, provinceHash + i);
		printf("Totale di comuni nella provincia '%s': %d\n", provinceHash + i, total);
	}
}

int countComuniOfProvince(Node headRegione, char *provincia) {
	int total = 0;

	while(headRegione != NULL) {
		if(strcmp(headRegione->provincia, provincia) == 0)
			total ++;
		
		headRegione = headRegione->next;
	}

	return total;
}

void printInhabitantsPerProvince(Node headRegione) {
	int lenght = 0;
	char *provinceHash = getProvinceHash(headRegione, &lenght);
	int i;

	for(i = 0; i < lenght; i = i + 3) {
		int total = countInhabitantsOfProvince(headRegione, provinceHash + i);
		printf("Totale di abitanti nella provincia '%s': %d\n", provinceHash + i, total);
	}
}

char *getProvinceHash(Node headRegione, int *length) {
	char *result = (char*) malloc(sizeof(char));
	int flag;
	int i;
	*length = 0;

	while(headRegione != NULL) {
		flag = 1;

		for(i = 0; i < *length; i = i + 3)
			if(strcmp(result + i, headRegione->provincia) == 0)
				flag = 0;

		if(flag) {
			result = (char*) realloc(result, strlen(result) + sizeof(char) * 3);	//	length + \0 + strlen(provincia) + \0
			memcpy(result + *length, headRegione->provincia, 3);
			*length = *length + 3;
		}

		headRegione = headRegione->next;
	}

	return result;
}

int countInhabitantsOfProvince(Node headRegione, char *provincia) {
	int total = 0;

	while(headRegione != NULL) {
		if(strcmp(headRegione->provincia, provincia) == 0)
			total = total + headRegione->popolazione;
		
		headRegione = headRegione->next;
	}

	return total;
}

Node createListFromRegionFile(Node headRegione, char *filename) {
	FILE *file = fopen(buildFilename(filename, ".dat"), "rb");

	if(file == NULL) {
		printf("Errore nell'apertura del file '%s'\n", filename);
		exit(1);
	}

	if(headRegione != NULL) {
		printf("La lista data non è vuota, i suoi dati verranno cancellati.\n");
		destroyList(headRegione);
	}

	char istat[ISTATLENGTH];
	char nome[NOMELENGTH];
	char provincia[PROVINCIALENGTH];
	char prefisso[PREFISSOLENGTH];
	char codicePostale[CODICEPOSTALELENGTH];
	char codiceFiscale[CODICEFISCALELENGTH];
	int popolazione;

	while(fread(istat, sizeof(char), ISTATLENGTH, file) == ISTATLENGTH) {
		long nameBegin = ftell(file);
		fread(nome, sizeof(char), NOMELENGTH, file);
		int nameLength = strlen(nome) + 1;
		fseek(file, nameBegin + nameLength, SEEK_SET);

		fread(provincia, sizeof(char), PROVINCIALENGTH, file);
		fread(prefisso, sizeof(char), PREFISSOLENGTH, file);
		fread(codicePostale, sizeof(char), CODICEPOSTALELENGTH, file);
		fread(codiceFiscale, sizeof(char), CODICEFISCALELENGTH, file);
		fread(&popolazione, sizeof(int), 1, file);
		headRegione = pushNode(headRegione, istat, nome, provincia, filename, prefisso, codicePostale, codiceFiscale, popolazione, (char*) "");
	}

	fclose(file);
	while(getchar() != '\n');
	return headRegione;
}

void saveRegionDataToFile(Node headRegione, char *filename) {
	FILE *file = fopen(buildFilename(filename, ".dat"), "wb");

	if(file == NULL) {
		printf("Errore nell'apertura del file '%s'\n", filename);
		exit(1);
	}

	while(headRegione != NULL) {
		if(strcmp(headRegione->regione, filename) != 0) {
			headRegione = headRegione->next;
			continue;
		}

		fwrite(headRegione->istat, sizeof(char), ISTATLENGTH, file);
		fwrite(headRegione->nome, sizeof(char), strlen(headRegione->nome) + 1, file);
		fwrite(headRegione->provincia, sizeof(char), PROVINCIALENGTH, file);
		fwrite(headRegione->prefisso, sizeof(char), PREFISSOLENGTH, file);
		fwrite(headRegione->codicePostale, sizeof(char), CODICEPOSTALELENGTH, file);
		fwrite(headRegione->codiceFiscale, sizeof(char), CODICEFISCALELENGTH, file);
		fwrite(&headRegione->popolazione, sizeof(int), 1, file);
		headRegione = headRegione->next;
	}

	fclose(file);
}

void clearConsoleAndPrintMenu() {
	//	system("cls");	Buggato su VSCode
	printf("\e[1;1H\e[2J");	//	Equivalente di system("cls")

	printf(
		"Operazioni disponibili:\n"
		"1. Scegli una regione e salvane i dati su file;\n"
		"2. Scegli una regione e visualizzane i dati salvati;\n"
		"3. Scegli una regione e visualizzane il totale di abitanti per provincia;\n"
		"4. Scegli una regione e visualizzane il totale di comuni per provincia;\n"
		"0. Esci.\n"
	);
}

Node createListFromTxtFile(Node head, const char *filename) {
	FILE *file = fopen(buildFilename( (char*) LISTACOMUNI, ".txt" ), "r");

	if(file == NULL) {
		printf("Errore nell'apertura del file '%s'\n", filename);
		exit(1);
	}

	if(head != NULL) {
		printf("La lista data non è vuota, i suoi dati verranno cancellati.\n");
		destroyList(head);
	}

	head = NULL;
	char istat[ISTATLENGTH];
	char nome[NOMELENGTH];
	char provincia[PROVINCIALENGTH];
	char regione[REGIONELENGTH];
	char prefisso[PREFISSOLENGTH];
	char codicePostale[CODICEPOSTALELENGTH];
	char codiceFiscale[CODICEFISCALELENGTH];
	int popolazione;
	char link[LINKLENGTH];

	while(fscanf(file, "%[^;];%[^;];%[^;];%[^;];%[^;];%[^;];%[^;];%d;%s\n", istat, nome, provincia, regione, prefisso, codicePostale, codiceFiscale, &popolazione, link) == 9)
		head = pushNode(head, istat, nome, provincia, regione, prefisso, codicePostale, codiceFiscale, popolazione, link);
	
	fclose(file);
	return head;
}

char *inputString(const char *prompt, int maxLength) {
	printf(prompt);
	char *result = (char*) malloc(maxLength);
	scanf("%s", result);
	return (char*) realloc(result, strlen(result) + 1);
}

int inputInt(const char *prompt, int min, int max) {
	printf(prompt);
	int result;
	scanf("%d", &result);

	if(min > max)
		return result;

	while(result < min || result > max) {
		printf("Input non valido. Riprova: ");
		scanf("%d", &result);
	}

	return result;
}

const char *buildFilename(char* name, const char *extension) {
	char *result = (char*) malloc(strlen(name) + strlen(extension) + 1);
	strcpy(result, ABSPATH);
	strcat(result, name);
	strcat(result, extension);
	return (const char*) result;
}

Node createNode(char *istat, char *nome, char *provincia, char *regione, char *prefisso, char *codicePostale, char *codiceFiscale, int popolazione, char *link) {
	Node result = (Node) malloc(sizeof(Comune));
	strcpy(result->istat, istat);
	strcpy(result->nome, nome);
	strcpy(result->provincia, provincia);
	strcpy(result->prefisso, prefisso);
	strcpy(result->codicePostale, codicePostale);
	strcpy(result->codiceFiscale, codiceFiscale);
	result->popolazione = popolazione;
	strcpy(result->regione, regione);
	strcpy(result->link, link);
	result->next = NULL;
	return result;
}

Node pushNode(Node head, char *istat, char *nome, char *provincia, char *regione, char *prefisso, char *codicePostale, char *codiceFiscale, int popolazione, char *link) {
	Node result = createNode(istat, nome, provincia, regione, prefisso, codicePostale, codiceFiscale, popolazione, link);

	if(head == NULL)
		return result;
	
	result->next = head;
	return result;
}

void destroyList(Node head) {
	Node next;
	
	while(head != NULL) {
		next = head->next;
		free(head);
		head = next;
	}
}

void printList(Node head) {
	while(head != NULL) {
		printf(
			"Istat: %s\n"
			"Nome: %s\n"
			"Provincia: %s\n"
			"Prefisso: %s\n"
			"Codice postale: %s\n"
			"Codice fiscale: %s\n"
			"Popolazione: %d\n\n",
			head->istat, head->nome, head->provincia, head->regione, head->prefisso, head->codicePostale, head->codiceFiscale, head->popolazione, head->link
		);
		head = head->next;
	}
}