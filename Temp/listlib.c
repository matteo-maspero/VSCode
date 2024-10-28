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
Node* SortLists(Node* head);

/*
	@brief Prints the given list;
	@param head: Pointer to the head of the list.
*/
void printList(Node* head);

int main() {
	Node* head1 = NULL;
	Node* head2 = NULL;
	int i, choice, x, y;
	int loop = 1;

	//	Append some nodes to work with;
	for(i = 0; i < 10; i++)
		head1 = appendNode(head1, i);

	for(i = 10; i < 20; i++)
		head2 = appendNode(head2, i);

	//	Print the original list;
	printf("\nPrima lista orginale:\n");
	printList(head1);

	//	Print the original list;
	printf("\n\nSeconda lista orginale:\n");
	printList(head2);

	while(loop) {
		printf(
			"\n\nOperations:\n"
			"1. Append a new node to the given list\n"
			"2. Add a new node at the beginning of the given list\n"
			"3. Insert a new node in the chosen position\n"
			"4. Insert a new node after the last node with a lower value\n"
			"5. Remove the chosen node (by value)\n"
			"6. Pop the chosen node (by position)\n"
			"7. Concatenate the two lists\n"
			"8. Sort both lists\n"
			"Enter your choice (invalid choices will stop the loop and exit): "
		);
		scanf("%d", &choice);

		switch (choice) {
			case 1:
				//	Appends a new node to the given list;
				printf("Enter the desired value: ");
				scanf("%d", &x);
				head1 = appendNode(head1, x);

				printf("\nLista dopo append:\n");
				printList(head1);
				break;
			case 2:
				//	Adds a new node at the beginning of the given list;
				printf("Enter the desired value: ");
				scanf("%d", &x);
				head1 = addNode(head1, x);

				printf("\nLista dopo add:\n");
				printList(head1);
				break;
			case 3:
				// Insert a new node in the chosen position;
				printf("Enter the value and the position (val pos): ");
				scanf("%d %d", &x, &y);
				head1 = insertNode(head1, x, y);

				printf("\nLista dopo insert:\n");
				printList(head1);
				break;
			case 4:
				// Insert a new node after the last node with a lower value;
				printf("Enter the desired value: ");
				scanf("%d", &x);
				head1 = insertNodeWhereGreater(head1, x);

				printf("\nLista dopo insertWhereGreater:\n");
				printList(head1);
				break;
			case 5:
				// Remove the chosen node (by value);
				printf("Enter the desired value: ");
				scanf("%d", &x);
				head1 = removeNode(head1, x);
				
				printf("\nLista dopo remove:\n");
				printList(head1);
				break;
			case 6:
				// Pop the chosen node (by position);
				printf("Enter the desired position: ");
				scanf("%d", &x);
				head1 = popNode(head1, x);

				printf("\nLista dopo pop:\n");
				printList(head1);
				break;
			case 7:
				// Concatenate the two lists;
				head1 = concatLists(head1, head2);
				printf("\nLista concatenata:\n");
				printList(head1);
				break;
			case 8:
				// Sort the lists;
				head1 = SortLists(head1);
				head2 = SortLists(head2);

				printf("\nListe ordinate:\n");
				printList(head1);
				printf("\n");
				printList(head2);
				break;
			default:
				loop = 0;
				break;
		}
	}

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

Node* SortLists(Node* head) {
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