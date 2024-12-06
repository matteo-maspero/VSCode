#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define ASSETS_PATH "C:\\Users\\matte\\Documents\\VSCode\\Assets\\"
#define INPUT_FILE "listacomuni"

/*
	TYPES
*/

typedef struct Comune {
	char* istat;
	char* name;
	char* province;
	char* region;
	char* prefix;
	char* postalCode;
	char* fiscalCode;
	int population;
	char* link;
	struct Comune* next;
} Comune;

typedef Comune* Node;

/*
	PROTOYPES
*/

Node createNode(char* istat, char* name, char* province, char* region, char* prefix, char* postalCode, char* fiscalCode, int population, char* link);
Node appendNode(Node head, char* istat, char* name, char* province, char* region, char* prefix, char* postalCode, char* fiscalCode, int population, char* link);
Node freeList(Node head);

const char* getFullPath(char* fileName, const char* extension);
Node loadComuni(Node head, char* fileName);

/*
	MAIN
*/

int main() {
	Node head = NULL;
	head = loadComuni(head, (char*) INPUT_FILE);
	return 0;
}

/*
	FUNCTIONS
*/

Node createNode(char* istat, char* name, char* province, char* region, char* prefix, char* postalCode, char* fiscalCode, int population, char* link) {
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

Node appendNode(Node head, char* istat, char* name, char* province, char* region, char* prefix, char* postalCode, char* fiscalCode, int population, char* link) {
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

const char* getFullPath(char* fileName, const char* extension) {
	char* fullPath = (char*) malloc( sizeof(char) * (strlen(ASSETS_PATH) + strlen(fileName) + strlen(extension) + 1) );
	strcpy(fullPath, ASSETS_PATH);
	strcat(fullPath, fileName);
	strcat(fullPath, extension);
	return (const char*) fullPath;
}

Node loadComuni(Node head, char* fileName) {
	FILE *inputFile = fopen(getFullPath(fileName, ".txt"), "r");

	if(inputFile == NULL) {
		printf("Errore nell'apertura del file %s\n", fileName);
		exit(1);
	}

	if(head != NULL)
		head = freeList(head);

	char buffer[128];

	while(fgets(buffer, 128, inputFile) != NULL) {
		char *istat = strdup(strtok(buffer, ";"));
		char *name = strdup(strtok(NULL, ";"));
		char *province = strdup(strtok(NULL, ";"));
		char *region = strdup(strtok(NULL, ";"));
		char *prefix = strdup(strtok(NULL, ";"));
		char *postalCode = strdup(strtok(NULL, ";"));
		char *fiscalCode = strdup(strtok(NULL, ";"));
		int population = atoi(strtok(NULL, ";"));
		char *link = strdup(strtok(NULL, "\n"));
		head = appendNode(head, istat, name, province, region, prefix, postalCode, fiscalCode, population, link);
	}

	fclose(inputFile);
	return head;
}