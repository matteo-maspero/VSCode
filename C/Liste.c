#include <stdio.h>
#include <stdlib.h>

typedef struct node {
	int value;
	struct node *next;
} Node;

typedef Node* List;

List new(int value);
void append(List list, Node *entry);
void insert(List *list, Node *entry, int pos);

int main() {
	List list = new(0);
	Node *node1 = new(1);
	Node *node2 = new(2);
	Node *node3 = new(3);

	append(list, node1);
	append(list, node2);
	insert(&list, node3, 2);

	Node *idx = list;

	while(idx != NULL) {
		printf("%d\n", idx->value);
		idx = idx->next;
	}

	return 0;
}

Node *new(int value) {
	Node *new = (Node*)malloc(sizeof(Node));
	new->value = value;
	new->next = NULL;

	return new;
}

void append(List list, Node *entry) {
	Node *node = list;

	while (node->next != NULL) {
		node = node->next;
	}

	node->next = entry;
}

void insert(List *list, Node *entry, int pos) {
	Node *node = *list;
	int i = 0;

	while(node->next != NULL && i < pos) {
		node = node->next;
		i ++;
	}

	if(pos == 0) {
		entry->next = *list;
		*list = entry;
	} else {
		entry->next = node->next;
		node->next = entry;
	}
}