#include <stdio.h>
#include <stdlib.h>

typedef struct lista {
	int value;
	struct lista *next;
} Lista;

Lista *new(int value);
void append(Lista *lista, Lista *entry);
void insert(Lista **lista, Lista *entry, int pos);

int main() {
	Lista *lista = new(0);
	Lista *nodo1 = new(1);
	Lista *nodo2 = new(2);
	Lista *nodo3 = new(3);

	append(lista, nodo1);
	append(lista, nodo3);
	insert(&lista, nodo2, 5);

	Lista *idx = lista;

	while(idx != NULL) {
		printf("%d\n", idx->value);
		idx = idx->next;
	}

	return 0;
}

Lista *new(int value) {
	Lista *new = (Lista *)malloc(sizeof(Lista));
	new->value = value;
	new->next = NULL;

	return new;
}

void append(Lista *lista, Lista *entry) {
	Lista *node = lista;

	while (node->next != NULL) {
		node = node->next;
	}

	node->next = entry;
}

void insert(Lista **lista, Lista *entry, int pos) {
	Lista *node = *lista;
	int i = 0;

	while(node->next != NULL && i < pos - 1) {
		node = node->next;
		i ++;
	}

	if(pos == 0) {
		entry->next = *lista;
		*lista = entry;
	} else {
		entry->next = node->next;
		node->next = entry;
	}
}