#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef struct Node {
	int data;
	struct Node* next;
} Node;

Node* createNode(int data);
Node* addNode(Node* head, int data);
Node* appendNode(Node* head, int data);
Node* popNode(Node* head, unsigned int index);
int listLength(Node* head);
void printList(Node* head);

Node* onBusStop(Node* people, int N);

int main() {
	unsigned int N;
	unsigned int F;
	srand(time(NULL));

	printf("Inserire la capienza massima del bus: ");
	scanf("%u", &N);
	
	printf("Inserire il numero di fermate: ");
	scanf("%u", &F);

	Node* people = NULL;
	int i;

	for(i = 0; i < F; i++) {
		printf("\nFermata %d", i + 1);
		people = onBusStop(people, N);
		printList(people);
	}

	return 0;
}

Node* createNode(int data) {
	Node* newNode = (Node*) malloc(sizeof(Node));
	newNode->data = data;
	newNode->next = NULL;
	return newNode;
}

Node* addNode(Node* head, int data) {
	Node* newNode = createNode(data);
	newNode->next = head;
	return newNode;
}

Node* appendNode(Node* head, int data) {
	if(head == NULL)
		return createNode(data);

	Node* current = head;

	while(current->next != NULL)
		current = current->next;

	current->next = createNode(data);
	return head;
}

Node* popNode(Node* head, unsigned int index) {
	if(head == NULL)
		return NULL;

	Node* toPop = head;

	if(index == 0) {
		head = head->next;
		free(toPop);
		return head;
	}

	Node* prev;

	while(toPop->next != NULL && --index > 0) {
		prev = toPop;
		toPop = toPop->next;
	}

	prev->next = toPop->next;
	free(toPop);
	return head;
}

int listLength(Node* head) {
	int length = 0;

	while(head != NULL) {
		head = head->next;
		length++;
	}

	return length;
}

void printList(Node* head) {
	while(head != NULL) {
		printf("\t%d", head->data);
		head = head->next;
	}
}

Node* onBusStop(Node* people, int N) {
	int i;
	
	int peopleOnBus = listLength(people);
	int peopleToGetOut = rand() % (peopleOnBus + 1);
	int peopleToGetIn = rand() % (N - peopleOnBus + 1);
	int door = rand() % 2;
	int name;

	printf(
		"\n\tSono scese %d persone;"
		"\n\tsono salite %d persone;",
		peopleToGetOut, peopleToGetIn
	);

	if(door) {
		printf("\n\tporta anteriore.\n");

		for(i = 0; i < peopleToGetOut; i++)
			people = popNode(people, 0);
		
		for(i = 0; i < peopleToGetIn; i++)
			people = addNode(people, rand() % 1000);
	} else {
		printf("\n\tporta posteriore.\n");

		for(i = 0; i < peopleToGetOut; i++)
			people = popNode(people, -1);
		
		for(i = 0; i < peopleToGetIn; i++)
			people = appendNode(people, rand() % 1000);
	}

	return people;
}