#include <stdio.h>
#include <stdlib.h>

typedef struct Dato {
	int value;
	struct Dato* next;
} Dato;

typedef Dato* Node;

Node initNode(int value);
Node appendNode(Node head, int value);
void printList(Node head);
void printListReverse(Node head);

int main() {
	Node head = NULL;
	
	for(int i = 0; i < 10; i ++)
		head = appendNode(head, i);

	printList(head);
	printf("FINE\n");
	printListReverse(head);
	printf("FINE\n");
	return 0;
}

Node initNode(int value) {
	Node node = (Node) malloc(sizeof(Dato));
	node->value = value;
	node->next = NULL;
	return node;
}

Node appendNode(Node head, int value) {
	if(head == NULL)
		return initNode(value);

	Node current = head;
	while(current->next != NULL)
		current = current->next;
	
	current->next = initNode(value);
	return head;
}

void printList(Node head) {
	while(head != NULL) {
		printf("%d ", head->value);
		head = head->next;
	}
}

void printListReverse(Node head) {
	if(head == NULL)
		return;

	printListReverse(head->next);
	printf("%d ", head->value);
}