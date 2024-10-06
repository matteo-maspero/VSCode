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