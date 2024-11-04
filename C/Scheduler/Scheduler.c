#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*
	LISTLIB_H
*/

typedef struct Node {
	char* id;		//	"P1"
	int length;		//	ms
	struct Node* next;
} Node;

Node* init_node(char id[3], int length);
Node* append_node(Node* head, char id[3], int length);
Node* insert_node(Node* head, char id[3], int length, unsigned int position);
Node* shift_head_left(Node* head);
Node* pop_head(Node* head);
void print_list(Node* head);

/*
	FUNCTIONS
*/

int main() {
	Node* g1[] = { init_node("P1", 60), init_node("P2", 50), init_node("P3", 45), init_node("P4", 30) };
	Node* g2[] = { init_node("M1", 80), init_node("M2", 20), init_node("M3", 15), init_node("M4", 60), init_node("M5", 30) };
	Node* g3[] = { init_node("R1", 50),	init_node("R2", 40), init_node("R3", 10) };

	Node* process_stack = NULL;
	Node* system_process = NULL;

	print_list(process_stack);

	return 0;
}

/*
	LISTLIB_H
*/

Node* init_node(char* id, int length) {
	Node* result = (Node*) malloc(sizeof(Node));
	result->id = id;
	result->length = length;
	result->next = NULL;
	return result;
}

Node* append_node(Node* head, char* id, int length) {
	if(head == NULL)
		return init_node(id, length);

	Node* item = head;

	while(item->next != NULL && item->next != head)
		item = item->next;
	
	item->next = init_node(id, length);
	item->next->next = head;
	return head;
}

Node* insert_node(Node* head, char id[3], int length, unsigned int position) {
	if(head == NULL)
		return init_node(id, length);

	Node* item = head;
	Node* new_node = init_node(id, length);

	if(position == 0) {
		new_node->next = head;
		return new_node;
	}

	while(position > 1 && item->next != head) {
		item = item->next;
		position--;
	}

	new_node->next = item->next;
	item->next = new_node;
	return head;
}

Node* shift_head_left(Node* head) {
	if(head == NULL)
		return NULL;

	return head->next;
}

Node* pop_head(Node* head) {
	if(head == NULL)
		return NULL;

	Node* to_pop = head;

	while(head->next != to_pop)
		head = head->next;

	head->next = to_pop->next;
	free(to_pop);
	return head->next;
}

void print_list(Node* head) {
	Node* item = head;

	while(item != NULL) {
		printf(
			"\nProcesso:"
			"\n\tNome\t%s"
			"\n\tBurst\t%d"
			, item->id, item->length
		);

		item = item->next;
		if(item == head)
			break;
	}
}