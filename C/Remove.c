#include <stdio.h>
#include <stdlib.h>

typedef int Data;

typedef struct __node {
	Data value;
	struct __node *next;
} Node;

typedef Node* List;

Node *createNode(Data value);
void print(List src);

int main() {
	List myList = NULL;
	
	return 0;
}

Node *createNode(Data value) {
	Node *newNode = (Node*) malloc(sizeof(Node));
	newNode->value = value;
	newNode->next = NULL;
	return newNode;
}

void append(List *stack, Data value) {
	Node *newNode = createNode(value);
	
	if(*stack == NULL) {
		*stack = newNode;
	} else {
		Node *node = *stack;
		while(node->next != NULL) {
			node = node->next;
		}
		node->next = newNode;
	}
}

void print(List src) {
	while(src != NULL) {
		printf("%d\t", src->value);
		src = src->next;
	}
}