#include <stdio.h>
#include <stdlib.h>

typedef struct __node {
	int value;
	struct __node* next;
} Node;

Node* initNode(int value);
Node* appendNode(Node* head, int value);
Node* popNode(Node* head, unsigned int position);
Node* removeNode(Node* head, int value);
void printList(Node* head);

int main() {
	Node* head = NULL;

	head = appendNode(head, 1);
	head = appendNode(head, 2);
	head = appendNode(head, 3);
	head = appendNode(head, 4);
	head = appendNode(head, 5);

	printf("\nLista orginale:\n");
	printList(head);

	head = popNode(head, -1);
	printf("\nLista dopo pop:\n");
	printList(head);

	head = removeNode(head, 4);
	printf("\nLista dopo remove:\n");
	printList(head);

	return 0;
}

Node* initNode(int value) {
	Node* result = (Node*) malloc(sizeof(Node));
	result->value = value;
	result->next = NULL;
	return result;
}

Node* appendNode(Node* head, int value) {
	if(head == NULL)
		return initNode(value);

	Node* current = head;

	while(current->next != NULL)
		current = current->next;

	current->next = initNode(value);
	return head;
}

Node* popNode(Node* head, unsigned int position) {
	Node* toPop = head;

	if(position == 0) {
		head = head->next;
		free(toPop);
		return head;
	}

	Node* prev = head;

	while(toPop->next != NULL && --position > 0) {
		prev = toPop;
		toPop = toPop->next;
	}

	if(toPop->next == NULL) {
		free(toPop);
		prev->next = NULL;
		return head;
	}

	prev->next = toPop->next;
	free(toPop);
	return head;
}

Node* removeNode(Node* head, int value) {
	Node* toRemove = head;

	if(toRemove->value == value) {
		head = head->next;
		free(toRemove);
		return head;
	}

	Node* prev = head;

	while(toRemove->next != NULL && toRemove->value != value) {
		prev = toRemove;
		toRemove = toRemove->next;
	}

	if(toRemove->value != value)
		return head;

	prev->next = toRemove->next;
	free(toRemove);
	return head;
}

void printList(Node* head) {
	while(head != NULL) {
		printf("%d\t", head->value);
		head = head->next;
	}
}