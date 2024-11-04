#include <stdio.h>
#include <stdlib.h>
#include "listlib.h"

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

	while(current->next != NULL)
		current = current->next;

	//	Append the new node to the last one;
	current->next = initNode(value);
	return head;
}

Node* addNode(Node* head, int value) {
	Node* newHead = initNode(value);
	newHead->next = head;
	return newHead;
}

Node* insertNode(Node* head, int value, unsigned int position) {
	//	If the desired position is the first one, return the new node;
	if(position == 0)
		return addNode(head, value);

	Node* current = head;

	//	Iterate through the list to find the desired position;
	while(current->next != NULL && --position > 0)
		current = current->next;

	//	Insert the new node in the desired position;
	Node* newNode = initNode(value);
	newNode->next = current->next;
	current->next = newNode;
	return head;
}

Node* insertNodeWhereGreater(Node* head, int value) {
	//	If the list is empty or the new node has a higher value than the first one, return the new node;
	if(head == NULL || head->value >= value)
		return addNode(head, value);

	Node* current = head;

	//	Iterate through the list to find the last node with a lower value;
	while(current->next != NULL && current->value < value)
		current = current->next;

	//	Insert the new node after the last node with a lower value;
	Node* newNode = initNode(value);
	newNode->next = current->next;
	current->next = newNode;
	return head;
}

Node* removeNode(Node* head, int value) {
	//	If the list is empty, return it;
	if(head == NULL)
		return head;

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

Node* popNode(Node* head, unsigned int position) {
	//	If the list is empty, return it;
	if(head == NULL)
		return head;

	Node* toPop;

	//	If the desired node is the first one, return the second one;
	if(position == 0) {
		toPop = head;
		head = head->next;
		free(toPop);
		return head;
	}

	Node* prev = head;
	toPop = head->next;

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

Node* concatLists(Node* head1, Node* head2) {
	//	If the first list is empty, return the second one;
	if(head1 == NULL)
		return head2;

	Node* current = head1;

	while(current->next != NULL)
		current = current->next;

	current->next = head2;
	return head1;
}

Node* SortList(Node* head) {
	//	If the list is empty or has only one node, return it;
	if(head == NULL || head->next == NULL)
		return head;

	Node* current = head;
	Node* next;
	int temp;

	//	Iterate through the list;
	while(current->next != NULL) {
		next = current->next;

		//	Sort the list;
		while(next != NULL) {
			if(current->value > next->value) {
				temp = current->value;
				current->value = next->value;
				next->value = temp;
			}

			next = next->next;
		}

		current = current->next;
	}

	return head;
}

void printList(Node* head) {
	while(head != NULL) {
		printf("%d\t", head->value);
		head = head->next;
	}
}