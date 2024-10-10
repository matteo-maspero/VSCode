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
void pop(List *stack, int position);
void print(List node);

int main() {
	List stack = createNode(0);
	append(stack, 1);
	append(stack, 2);
	append(stack, 3);
	append(stack, 4);

	pop(&stack, 4);
	print(stack);
	
	return 0;
}

Node *createNode(Data value) {
	Node *result = (Node*) malloc(sizeof(Node));
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

void pop(List *stack, int position) {
	if(position < 0)
		return;

	Node *node;

	if (position == 0) {
		node = (*stack)->next;
		free(*stack);
		*stack = node;
		return;
	}

	int i = 0;
	node = *stack;

	while(node->next != NULL && i < position - 1) {
		node = node->next;
		i++;
	}

	Node *temp = node->next->next;
	free(node->next);
	node->next = temp;
}

void print(List node) {
	while(node != NULL) {
		printf("%d\t", node->value);
		node = node->next;
	}
}