#include <stdio.h>
#include <stdlib.h>

/*
	Node ~(struct __node):
		int value: stored value
		struct __node* next: pointer to the next node
*/
typedef struct __node {
	int value;
	struct __node* next;
} Node;

/*
	@brief Creates and initializes a new node;
	@param value: Value to store in the new node;
	@return Pointer to the new node.
*/
Node* initNode(int value);

/*
	@brief Appends a new node to the given list;
	@param head: Pointer to the head of the list;
	@param value: Value to store in the new node;
	@return Pointer to the head of the list.
*/
Node* appendNode(Node* head, int value);

/*
	@brief Pops a node from the given list;
	@param head: Pointer to the head of the list;
	@param position: Position of the node to pop;
	@return Pointer to the head of the list.
*/
Node* popNode(Node* head, unsigned int position);

/*
	@brief Removes a node from the given list;
	@param head: Pointer to the head of the list;
	@param value: Value of the node to remove;
	@return Pointer to the head of the list.
*/
Node* removeNode(Node* head, int value);

/*
	@brief Prints the given list;
	@param head: Pointer to the head of the list.
*/
void printList(Node* head);

int main() {
	//	First node of our list.
	Node* head = NULL;

	//	Append some nodes to work with;
	head = appendNode(head, 1);
	head = appendNode(head, 2);
	head = appendNode(head, 3);
	head = appendNode(head, 4);
	head = appendNode(head, 5);

	//	Print the original list;
	printf("\nLista orginale:\n");
	printList(head);

	//	Pop the chosen node (by position);
	head = popNode(head, -1);
	printf("\nLista dopo pop:\n");
	printList(head);

	//	Remove the chosen node (by value);
	head = removeNode(head, 4);
	printf("\nLista dopo remove:\n");
	printList(head);

	return 0;
}

Node* initNode(int value) {
	Node* result = (Node*) malloc(sizeof(Node));
	result->value = value;
	result->next = NULL;
	return result;
}

Node* appendNode(Node* head, int value) {
	//	If the list is empty, return the new node;
	if(head == NULL)
		return initNode(value);

	Node* current = head;

	//	Iterate through the list to find the last node;
	while(current->next != NULL)
		current = current->next;

	//	Append the new node to the last one;
	current->next = initNode(value);
	return head;
}

Node* popNode(Node* head, unsigned int position) {
	Node* toPop = head;

	//	If the desired node is the first one, return the second one;
	if(position == 0) {
		head = head->next;
		free(toPop);
		return head;
	}

	Node* prev = head;

	//	Iterate through the list to find the desired node;
	while(toPop->next != NULL && --position > 0) {
		prev = toPop;
		toPop = toPop->next;
	}

	//	If the desired node is the last one, return the previous one;
	if(toPop->next == NULL) {
		free(toPop);
		prev->next = NULL;
		return head;
	}

	//	Otherwise, return the list without the desired node;
	prev->next = toPop->next;
	free(toPop);
	return head;
}

Node* removeNode(Node* head, int value) {
	Node* toRemove = head;

	//	If the desired node is the first one, return the second one;
	if(toRemove->value == value) {
		head = head->next;
		free(toRemove);
		return head;
	}

	Node* prev = head;

	//	Iterate through the list to find the desired node;
	while(toRemove->next != NULL && toRemove->value != value) {
		prev = toRemove;
		toRemove = toRemove->next;
	}

	//	If the desired node is not found, return the original list;
	if(toRemove->value != value)
		return head;

	//	Otherwise, return the list without the desired node;
	prev->next = toRemove->next;
	free(toRemove);
	return head;
}

void printList(Node* head) {
	while(head != NULL) {
		printf("%d\t", head->value);
		head = head->next;
	}
}