#ifndef LISTLIB_H
#define LISTLIB_H

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
	@brief Adds a new node to the beginning of the given list;
	@param head: Pointer to the head of the list;
	@param value: Value to store in the new node;
	@return Pointer to the head of the list.
*/
Node* addNode(Node* head, int value);

/*
	@brief Inserts a new node in the given position;
	@param head: Pointer to the head of the list;
	@param value: Value to store in the new node;
	@param position: Position of the new node;
	@return Pointer to the head of the list.
*/
Node* insertNode(Node* head, int value, unsigned int position);

/*
	@brief Inserts a new node after the last node with a lower value;
	@param head: Pointer to the head of the list;
	@param value: Value to store in the new node;
	@return Pointer to the head of the list.
*/
Node* insertNodeWhereGreater(Node* head, int value);

/*
	@brief Removes a node from the given list;
	@param head: Pointer to the head of the list;
	@param value: Value of the node to remove;
	@return Pointer to the head of the list.
*/
Node* removeNode(Node* head, int value);

/*
	@brief Pops a node from the given list;
	@param head: Pointer to the head of the list;
	@param position: Position of the node to pop;
	@return Pointer to the head of the list.
*/
Node* popNode(Node* head, unsigned int position);

/*
	@brief Concatenates two lists;
	@param head1: Pointer to the head of the first list;
	@param head2: Pointer to the head of the second list.
*/
Node* concatLists(Node* head1, Node* head2);

/*
	@brief Mixes two lists and sort them;
	@param head1: Pointer to the head of the first list;
	@param head2: Pointer to the head of the second list;
	@return Pointer to the head of the new list.
*/
Node* SortList(Node* head);

/*
	@brief Prints the given list;
	@param head: Pointer to the head of the list.
*/
void printList(Node* head);

#endif