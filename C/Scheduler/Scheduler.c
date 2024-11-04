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
Node* shift_node(Node* head);
void print_list(Node* head);

/*
	FUNCTIONS
*/

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

Node* shift_node(Node* head) {
	if(head == NULL)
		return NULL;

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