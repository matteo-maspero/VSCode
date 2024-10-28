#include <stdio.h>
#include <stdlib.h>

typedef struct struct_node {
	int value;
	struct struct_node *next;
} Node;

typedef Node* List;

Node *createNode(int value);
void append(List dest, int value);

int main() {
	int n, i;
	int result = 1;

	printf("Inserire un numero: ");
	scanf("%d", &n);

	if(n < 0)
		return 1;

	List stack = createNode(1);

	for(i = 2; i <= n; i ++) {
		append(stack, i);
	}

	Node *current = stack;

	while(current != NULL) {
		result *= current->value;
		current = current->next;
	}

	printf("Il fattoriale vale %d\n", result);
	return 0;
}

Node *createNode(int value) {
	Node * result = (Node *) malloc(sizeof(Node));
	result->value = value;
	result->next = NULL;

	return result;
}

void append(List dest, int value) {
	while (dest->next != NULL) {
		dest = dest->next;
	}

	dest->next = createNode(value);
}