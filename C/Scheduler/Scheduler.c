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

void fill_inputX(FILE *input, Node* stack) {
	char name[3];
	int length;
	int i = 0;

	while(fscanf(input, "%s %d", name, length) != EOF) {
		stack = append_node(stack, name, length);
		i++;
	}
}

int main() {
	/*
	Node* col1[4] = {{"P1", 60}, {"P2", 50}, {"P3", 45}, {"P4", 30}};
	Node* col2[4] = {{"M1", 80}, {"M2", 20}, {"M3", 15}, {"M4", 60}, {"M5", 30}};
	Node* col3[3] = {{"R1", 50}, {"R2", 40}, {"R3", 10}};
	*/
	Node* system_stack = NULL;
	Node* process_stack = NULL;

	process_stack = append_node(process_stack, "P0", 10);
	process_stack = append_node(process_stack, "P1", 11);
	process_stack = append_node(process_stack, "P2", 12);
	process_stack = append_node(process_stack, "P3", 13);
	process_stack = append_node(process_stack, "P4", 14);

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