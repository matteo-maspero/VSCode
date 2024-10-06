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
void add(List *dest, Data value);
void print(List list);

int main() {
	int n;
	int i;

	printf("Inserisci il numero di elementi: ");
	scanf("%d", &n);
	
	List list1 = createNode(0);
	List list2 = createNode(0);

	for(i = 0; i < n; i ++) {
		add(&list1, i + 1);
		append(list2, i + 1);
	}

	printf("\nLista 1:\n");
	print(list1);

	printf("\n\nLista 2:\n");
	print(list2);

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

void add(List *dest, Data value) {
	Node *newNode = createNode(value);
	newNode->next = *dest;
	*dest = newNode;
}

void print(List list) {
	while (list != NULL) {
		printf("%d\t", list->value);
		list = list->next;
	}
}