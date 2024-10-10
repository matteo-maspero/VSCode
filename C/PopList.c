#include <stdio.h>
#include <stdlib.h>

typedef int Data;

typedef struct struct_node {
	Data value;
	struct struct_node *next;
} Node;

typedef Node* List;

Node *createNode(Data value);
void append(List dest, Data value);
void pop(List dest);
void print(List list);

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
	Node * result = (Node *) malloc(sizeof(Node));
	result->value = value;
	result->next = NULL;

	return result;
}

void append(List dest, Data value) {
	while (dest->next != NULL) {
		dest = dest->next;
	}

	dest->next = createNode(value);
}

void pop(List dest) {
	while (dest->next->next != NULL) {
		dest = dest->next;
	}

	free(dest->next);
	dest->next = NULL;
}

void print(List list) {
	while (list != NULL) {
		printf("%d\t", list->value);
		list = list->next;
	}
}