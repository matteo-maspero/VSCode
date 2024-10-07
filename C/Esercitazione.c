/*
Proviamo, con l'aiuto di inserisciIntesta e Incoda a creare una lista di elementi ordinati chiesti all'utente.
Questo significa che scegliete un tipo di ordinamento al quale corrisponderà una LIFO o una FIFO e poi inserite al posto giusto gli elementi sotto forma di lista
*/

#include <stdio.h>
#include <stdlib.h>

typedef struct struct_node {
	int value;
	struct struct_node *next;
} Node;

typedef Node* List;

Node *createNode(int value);
List insert(List current, int value);
void print(List list);

int main() {
	List stack = NULL;
	int i;
	
	while(1) {
		int temp;

		printf("Inserisci un numero (-1 per terminare): ");
		scanf("%d", &temp);

		if(temp == -1)
			break;

		stack = insert(stack, temp);
	}

	print(stack);
	return 0;
}

Node *createNode(int value) {
	Node * result = (Node *) malloc(sizeof(Node));
	result->value = value;
	result->next = NULL;

	return result;
}

List insert(List stack, int value) {
	Node *newNode = createNode(value);

	if(stack == NULL || value < stack->value) {
		newNode->next = stack;
		stack = newNode;
	} else {
		Node *current = stack;

		while(current->next != NULL && current->next->value < value) {
			current = current->next;
		}

		newNode->next = current->next;
		current->next = newNode;
	}

	return stack;
}

void print(List list) {
	while (list != NULL) {
		printf("%d\t", list->value);
		list = list->next;
	}
}