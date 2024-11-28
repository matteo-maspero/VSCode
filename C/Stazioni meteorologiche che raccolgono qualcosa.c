#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define PATH "C:\\Users\\mat.maspero\\VSCode\\Workspace\\"
#define FILE_NAME PATH "stazioni.txt"

typedef struct City {
	char* name;
	char* province;
	char* region;
	int maxTemp;
	int minTemp;
	int moisture;
	struct City* next;
} City;

typedef City* Node;

/*
	PROTOTYPES: LISTS
*/

Node createNode(char* name, char* province, char* region, int maxTemp, int minTemp, int moisture);
Node insertNode(Node head, char* name, char* province, char* region, int maxTemp, int minTemp, int moisture);
Node getRandomNode(Node head);
int listLen(Node head);

/*
	PROTOYPES: FILES
*/

Node loadDataToList(Node head);
void saveDataToFile(Node head);

/*
	MAIN
*/

int main() {
	Node inputHead = NULL;

	srand(time(NULL));

	inputHead = loadDataToList(inputHead);

	//todo

	Node outputHead = NULL;
	Node temp;
	int outputLength = rand() % listLen(inputHead) + 1;
	int i;

	for(i = 0; i < outputLength; i ++) {
		temp = getRandomNode(inputHead);
		temp->maxTemp = rand() % 60 - 20;
		temp->minTemp = rand() % temp->maxTemp - 20;
		temp->moisture = rand() % 101;
	}

	saveDataToFile(outputHead);

	return 0;
}

/*
	FUNCTIONS: LISTS
*/

Node createNode(char* name, char* province, char* region, int maxTemp, int minTemp, int moisture) {
	Node newNode = (Node) malloc(sizeof(City));
	newNode->name = name;
	newNode->province = province;
	newNode->region = region;
	newNode->maxTemp = maxTemp;
	newNode->minTemp = minTemp;
	newNode->moisture = moisture;
	return newNode;
}

Node insertNode(Node head, char* name, char* province, char* region, int maxTemp, int minTemp, int moisture) {
	Node newNode = createNode(name, province, region, maxTemp, minTemp, moisture);
	newNode->next = head;
	return newNode;
}

Node getRandomNode(Node head) {
	int i = rand() % listLen(head);

	while(i > 0) {
		head = head->next;
		i --;
	}

	return head;
}

int listLen(Node head) {
	int len = 0;

	while (head != NULL) {
		head = head->next;
		len ++;
	}

	return len;
}

/*
	FUNCTIONS: FILES
*/

Node loadDataToList(Node head) {
	FILE* file = fopen(FILE_NAME, "r");

	if(file == NULL) 
		perror("ERROR! ");

	char tempName[64], tempProvince[3], tempRegion[4];

	while (fscanf(file, "%s;%s;%s", tempName, tempProvince, tempRegion) != EOF) {
		head = insertNode(
			head,
			(char*) malloc(sizeof(char) * strlen(tempName)),
			(char*) malloc(sizeof(char) * 3),
			(char*) malloc(sizeof(char) * 4),
			0, 0, 0
		);
	}

	fclose(file);
	return head;
}

void saveDataToFile(Node head) {
	FILE* file = fopen(FILE_NAME, "wb");

	if(file == NULL) 
		perror("ERROR! ");

	while (head != NULL) {
		fprintf(file, "%s;%s;%s;%d;%d;%d\n", head->name, head->province, head->region, head->maxTemp, head->minTemp, head->moisture);
		head = head->next;
	}

	printf("I dati sono stati salvati con successo!");
	fclose(file);
}