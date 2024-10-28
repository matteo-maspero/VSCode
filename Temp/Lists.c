#include <stdio.h>
#include <stdlib.h>

/*
	TYPES
*/

typedef int Data;

typedef struct __node {
	Data value;
	struct __node *next;
} Node;

typedef Node* List;

/*
	FUNCTIONS
*/

Node* createNode(Data value);
void append(List node, Data value);
List add(List node, Data value);
List insert(List node, Data value, int position);
void print(List node);

int main() {
	List myList = NULL;
	
	append(myList, 1);
	
	print(myList);
	getchar();
	return 0;
}

Node* createNode(Data value) {
	Node* node = (Node*)malloc(sizeof(Node));
	node->value = value;
	node->next = NULL;
	return node;
}

void append(List node, Data value) {
	Node* newNode = createNode(value);

	if(node == NULL)
		node = newNode;
	else {
		while(node->next != NULL)
			node = node->next;

		node->next = newNode;
	}
}

List add(List node, Data value) {
	Node* newNode = createNode(value);
	newNode->next = node;
	return newNode;
}

List insert(List node, Data value, int position) {
	int i = 0;
	Node* newNode = createNode(value);

	if(position == 0) {
		newNode->next = node;
		return newNode;
	}

	Node* prev = node;

	while(prev->next != NULL && i < position - 1) {
		prev = prev->next;
		i++;
	}

	newNode->next = prev->next;
	prev->next = newNode;
	return node;
}

void print(List node) {
	while(node != NULL) {
		printf("%d\t", node->value);
		node = node->next;
	}
}