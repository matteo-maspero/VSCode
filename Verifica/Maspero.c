#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

//	Se necessario, definire il path della cartella in cui risiede l'eseguibile.
#define PATH "C:\\Users\\mat.maspero\\VSCode\\Verifica\\"
#define FILE1_NAME "sport"
#define FILE2_NAME "gare"

//	CONFIG
#define ATHLETES_NUM 5
#define NAME_LEN 32
#define CATEGORY_LEN 16
#define FIELD_LEN 16

char VetCognome[][25] = {"Bianchi Marco", "Rossi Luigi", "Neri Francesca", "Renzi Marta", "Corti Attilio"};
char VetCategoria[][25] = {"principiante", "avanzato", "mediano", "esperto"};
char VetSpecialita[][25] = {"libera", "slalom", "fondo", "mezzofondo"};

//	TYPES
typedef struct {
	int code;
	char name[NAME_LEN];
	int age;
	char category[CATEGORY_LEN];
	char field[FIELD_LEN];	//	Specialità.
	int points;
} Data;

typedef struct {
	char field[FIELD_LEN];
	int points;
} DataToSave;

typedef struct Node {
	//	Incapsuliamo la struct 'data' nel nodo.
	Data data;
	struct Node *next;
} Node;

typedef Node* NodePt;

//	PROTOTYPES DEFINITION
void clearConsoleAndPrintMenu();

NodePt generateAthletes();
void writeDataToTxtFile(NodePt headAthletes, const char *filename);
const char *getFullPath(char *filename, const char *extension);

NodePt readAthletesFromTxtFile(const char *filename);
NodePt readAthletesFromTxtFileFiltered(const char *filename, char *filter);
void printAthletes(NodePt headAthletes);

void writeFieldsToDatFile(NodePt headAthletes, const char *filename);
void printFieldsFromDatFile(const char *filename);

NodePt initNode(int code, char *name, int age, char *category, char *field, int points);
NodePt pushNode(NodePt head, NodePt entry);

int main() {
	NodePt headAthletes = NULL;
	srand(time(NULL));

	while(1) {
		NodePt filteredAthletes = NULL;
		char categoryFilter[CATEGORY_LEN];
		int choice;

		clearConsoleAndPrintMenu();
		scanf("%d", &choice);
		printf("\n");

		switch (choice) {
		case 1:
			headAthletes = generateAthletes();
			writeDataToTxtFile(headAthletes, FILE1_NAME);
			break;
		case 2:
			headAthletes = readAthletesFromTxtFile(FILE1_NAME);
			printAthletes(headAthletes);
			break;
		case 3:
			printf("Scegli la categoria di filtro: ");
			scanf("%s", categoryFilter);
			filteredAthletes = readAthletesFromTxtFileFiltered(FILE1_NAME, categoryFilter);
			printAthletes(filteredAthletes);
			break;
		case 4:
			if(headAthletes == NULL) {
				printf("Lista vuota, eseguire prima l'operazione 1 o 2.\n");
				break;
			}

			writeFieldsToDatFile(headAthletes, FILE2_NAME);
			break;
		case 5:
			printFieldsFromDatFile(FILE2_NAME);
			break;
		default:
			printf("Operazione non valida.\n");
		}

		while(getchar() != '\n');
		printf("Premere invio per continuare...\n");
		getchar();
	}

	return 0;
}

void clearConsoleAndPrintMenu() {
	//	Buggato sul terminale di VSCode...
	//	system("cls");

	//	Equivalente di system("cls");
	printf("\e[1;1H\e[2J");

	printf(
		"MENU - Operazioni disponibili:\n"
		"\t1 - Genera il file 'sport.txt' e genera in esso le informazioni degli atleti;\n"
		"\t2 - Visualizza il contenuto del file 'sport.txt', se presente;\n"
		"\t3 - Visualizza le informazioni filtrare per categoria;\n"
		"\t4 - Genera il file 'gare.dat' e riempilo riga per riga con le specialita' e il relativo punteggio totale;\n"
		"\t5 - Visualizza il contenuto del file binario;\n"
		"\t0 - Esci.\n"
		"Scegli il numero di un'operazione: "
	);
}

NodePt generateAthletes() {
	NodePt headAthletes = NULL;
	int i;

	for(i = 0; i < ATHLETES_NUM; i ++) {
		int code = rand() % 100;
		int age = 20 + rand() % 30;
		int points = rand() % 1000;
		int category = rand() % 4;
		int field = rand() % 4;

		headAthletes = pushNode(
			headAthletes,
			initNode(code, VetCognome[i], age, VetCategoria[category], VetSpecialita[field], points)
		);
	}

	return headAthletes;
}

void writeDataToTxtFile(NodePt headAthletes, const char *filename) {
	if(headAthletes == NULL) {
		printf("La lista data è vuota.");
		exit(1);
	}

	const char *fullPath = getFullPath( (char*) filename, ".txt" );
	FILE *txtFile = fopen(fullPath, "w");

	if(txtFile == NULL) {
		printf("Errore durante l'apertura di '%s'.", fullPath);
		exit(1);
	}

	while(headAthletes != NULL) {
		fprintf(
			txtFile, "%d,%s,%d,%s,%s,%d\n",
			headAthletes->data.code,
			headAthletes->data.name,
			headAthletes->data.age,
			headAthletes->data.category,
			headAthletes->data.field,
			headAthletes->data.points
		);
		headAthletes = headAthletes->next;
	}

	fclose(txtFile);
	
	printf("Il file è stato generato con successo.\n");
}

const char *getFullPath(char *filename, const char *extension) {
	char *result = (char*) malloc( sizeof(char) * (strlen(filename) + strlen(extension) + 1) );
	strcpy(result, PATH);
	strcat(result, filename);
	strcat(result, extension);
	return (const char*) result;
}

NodePt readAthletesFromTxtFile(const char *filename) {
	const char *fullPath = getFullPath( (char*) filename, ".txt" );
	FILE *txtFile = fopen(fullPath, "r");

	if(txtFile == NULL) {
		printf("Errore durante l'apertura di '%s'.", fullPath);
		exit(1);
	}

	NodePt headAthletes = NULL;
	int code;
	char name[NAME_LEN];
	int age;
	char category[CATEGORY_LEN];
	char field[FIELD_LEN];
	int points;

	while( fscanf(txtFile, "%d,%[^,],%d,%[^,],%[^,],%d\n", &code, name, &age, category, field, &points) == 6 )
		headAthletes = pushNode(
			headAthletes,
			initNode(code, name, age, category, field, points)
		);

	fclose(txtFile);
	
	return headAthletes;
}

NodePt readAthletesFromTxtFileFiltered(const char *filename, char *filter) {
	const char *fullPath = getFullPath( (char*) filename, ".txt" );
	FILE *txtFile = fopen(fullPath, "r");

	if(txtFile == NULL) {
		printf("Errore durante l'apertura di '%s'.", fullPath);
		exit(1);
	}

	NodePt filteredAthletes = NULL;
	int code;
	char name[NAME_LEN];
	int age;
	char category[CATEGORY_LEN];
	char field[FIELD_LEN];
	int points;

	while( fscanf(txtFile, "%d,%[^,],%d,%[^,],%[^,],%d\n", &code, name, &age, category, field, &points) == 6 )
		if( strcmp(category, filter) == 0 )
			filteredAthletes = pushNode(
				filteredAthletes,
				initNode(code, name, age, category, field, points)
			);

	fclose(txtFile);
	
	return filteredAthletes;
}

void printAthletes(NodePt head) {
	if(head == NULL) {
		printf("La lista degli atleti è vuota.\n");
		return;
	}

	while(head != NULL) {
		printf(
			"%s:\n"
			"\tCodice atleta: %d\n"
			"\tEta': %d\n"
			"\tCategoria: %s\n"
			"\tSpecialita': %s\n"
			"\tPunteggio: %d\n",
			head->data.name,
			head->data.code,
			head->data.age,
			head->data.category,
			head->data.field,
			head->data.points
		);
		head = head->next;
	}
}

void writeFieldsToDatFile(NodePt headAthletes, const char *filename) {
	if(headAthletes == NULL) {
		printf("La lista data è vuota.");
		exit(1);
	}

	const char *fullPath = getFullPath( (char*) filename, ".dat" );
	FILE *datFile = fopen(fullPath, "wb");

	if(datFile == NULL) {
		printf("Errore durante l'apertura di '%s'.", fullPath);
		exit(1);
	}

	int i;

	for(i = 0; i < 4; i ++) {
		DataToSave fieldToSave;
		strcpy(fieldToSave.field, VetSpecialita[i]);
		fieldToSave.points = 0;

		while(headAthletes != NULL) {
			if( strcmp(headAthletes->data.field, fieldToSave.field) == 0 )
				fieldToSave.points = fieldToSave.points + headAthletes->data.points;

			headAthletes = headAthletes->next;
		}
		
		fwrite(&fieldToSave, sizeof(DataToSave), 1, datFile);
	}

	fclose(datFile);
	printf("Il file è stato generato con successo.\n");
}

void printFieldsFromDatFile(const char *filename) {
	const char *fullPath = getFullPath( (char*) filename, ".dat" );
	FILE *datFile = fopen(fullPath, "rb");

	if(datFile == NULL) {
		printf("Errore durante l'apertura di '%s'.", fullPath);
		exit(1);
	}

	DataToSave readField;

	while( fread(&readField, sizeof(DataToSave), 1, datFile) == 1 ) {
		printf(
			"Specialità: %s\n"
			"Punteggio totale: %d\n\n",
			readField.field, readField.points
		);
	}

	fclose(datFile);
}

NodePt initNode(int code, char *name, int age, char *category, char *field, int points) {
	NodePt result = (NodePt) malloc(sizeof(Node));
	result->data.code = code;
	strcpy(result->data.name, name);
	result->data.age = age;
	strcpy(result->data.category, category);
	strcpy(result->data.field, field);
	result->data.points = points;
	result->next = NULL;
	return result;
}

NodePt pushNode(NodePt head, NodePt entry) {
	if(head == NULL)
		return entry;

	entry->next = head;
	return entry;
}