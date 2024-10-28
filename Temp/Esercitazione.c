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
Node* popNode(Node* head, int index);
void printList(Node* head);

int main() {
	unsigned int N;
	unsigned int F;
	srand(time(NULL));

	printf("Inserire la capienza massima del bus: ");
	scanf("%u", &N);
	
	printf("Inserire il numero di fermate: ");
	scanf("%u", &F);

	Node* people = NULL;

	people = addNode(people, 1);
	people = addNode(people, 2);
	people = addNode(people, 3);
	people = addNode(people, 4);
	people = addNode(people, 5);

	people = popNode(people, 2);

	printList(people);

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

Node* popNode(Node* head, int index) {
	if(head == NULL)
		return NULL;

	Node* toPop = head;

	if(index == 0) {
		head = head->next;
		free(toPop);
		return head;
	}

	Node* prev;

	while(--index > 0) {
		if(toPop->next == NULL)
			return head;
		
		prev = toPop;
		toPop = toPop->next;
	}

	prev->next = toPop->next;
	free(toPop);
	return head;
}

void printList(Node* head) {
	while(head != NULL) {
		printf("%d ", head->data);
		head = head->next;
	}
	printf("\n");
}