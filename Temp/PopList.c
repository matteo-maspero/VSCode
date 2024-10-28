#include <stdio.h>
#include <stdlib.h>

typedef int Data;

typedef struct struct_node {
	Data value;
	struct struct_node *next;
} Node;

typedef Node* List;

Node *createNode(Data value);
void append(List node, Data value);
void pop(List node);
void print(List node);

int main() {
	List stack = createNode(0);
	append(stack, 1);
	append(stack, 2);
	append(stack, 3);
	append(stack, 4);

	pop(stack);
	pop(stack);
	print(stack);

	return 0;
}

Node *createNode(Data value) {
	Node * result = (Node*) malloc(sizeof(Node));
	result->value = value;
	result->next = NULL;

	return result;
}

void append(List node, Data value) {
	while(node->next != NULL) {
		node = node->next;
	}

	node->next = createNode(value);
}

void pop(List node) {
	if(node == NULL)
		return;

	if(node->next == NULL) {
		free(node);
		node = NULL;
		return;
	}

	while(node->next->next != NULL) {
		node = node->next;
	}

	free(node->next);
	node->next = NULL;
}

void print(List node) {
	while(node != NULL) {
		printf("%d\t", node->value);
		node = node->next;
	}
}