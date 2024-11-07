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
	Node* input1 = NULL;
	Node* input2 = NULL;
	Node* input3 = NULL;

	Node* system_stack = NULL;
	Node* process_stack = NULL;

	FILE *input = NULL;

	input = fopen("input1.txt", "r");
	if(input == NULL)
		return 1;

	fill_inputX(input, input1);
	fclose(input);

	input = fopen("input2.txt", "r");
	if(input == NULL)
		return 1;

	fill_inputX(input, input2);
	fclose(input);
	
	input = fopen("input3.txt", "r");
	if(input == NULL)
		return 1;

	fill_inputX(input, input3);
	fclose(input);

	print_list(input1);
	print_list(input2);
	print_list(input3);

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