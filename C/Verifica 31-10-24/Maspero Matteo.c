#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef struct __node {
	int age;
	int emergency;
	struct __node* next;
} Node;

/*
	PROTOTYPES
*/

Node* appendPatient(Node* head);
Node* addEmergencyPatient(Node* head);
Node* callNextPatient(Node* head);
Node* moveElderlyForward(Node* head);
Node* moveChildrenAfterElderly(Node* head);
Node* generateRandomPatient(Node* head);

/*
	LIB
*/

Node* initNode(int value, int emergency);
Node* appendNode(Node* head, int value, int emergency);
Node* addNode(Node* head, int value, int emergency);
Node* insertNodeWhereGreater(Node* head, int value, int emergency);
Node* popNode(Node* head, unsigned int position);
void printList(Node* head);
void exportToFile(Node* head);

///////////////////////////////////////////////////////////////////////////////////////

int main() {
	Node* queue = NULL;
	int choice;

	srand(time(NULL));

	while(1) {
		printf(
			"\nOperazioni possibili:"
			"\n0 | esci;"
			"\n1 | aggiungi un paziente in coda;"
			"\n2 | aggiungi un paziente urgente in testa;"
			"\n3 | chiama il prossimo paziente da uno dei 2 ambulatori;"
			"\n4 | sposta i pazienti over 70 in testa;"
			"\n5 | sposta i pazienti under 2 subito dopo gli anziani;"
			"\n6 | stampa la lista dei pazienti in coda;"
			"\n7 | genera un paziente casuale;"
			"\n8 | esporta in file."
			"\nScelta: "
		);
		scanf("%d", &choice);

		if(choice == 0)
			break;

		switch(choice) {
			case 1:
				queue = appendPatient(queue);
				break;
			case 2:
				queue = addEmergencyPatient(queue);
				break;
			case 3:
				queue = callNextPatient(queue);
				break;
			case 4:
				queue = moveElderlyForward(queue);
				break;
			case 5:
				queue = moveChildrenAfterElderly(queue);
				break;
			case 6:
				printf("\nLista dei pazienti in coda:");
				printList(queue);
				printf("\n");
				break;
			case 7:
				queue = generateRandomPatient(queue);
				break;
			case 8:
				exportToFile(queue);
				break;
			default:
				printf("\nInvalid choice.\n");
		}
	}

	return 0;
}

/*
	FUNCTIONS
*/

Node* appendPatient(Node* head) {
	int age;

	printf("\nInserisci l'età del paziente: ");
	scanf("%d", &age);
	return appendNode(head, age, 0);
}

Node* addEmergencyPatient(Node* head) {
	Node* newPatient;
	int age;

	printf("\nInserisci l'età del paziente: ");
	scanf("%d", &age);

	newPatient = addNode(head, age, 1);
	return newPatient;
}

Node* callNextPatient(Node* head) {
	int ambulatory;

	printf("\nQuale ambulatorio annuncerà la chiamata? (1 o 2) ");
	scanf("%d", &ambulatory);

	printf(
		"\nL'ambulatorio '%d' ha chiamato il primo paziente in coda:"
		"\n\tEta': %d", ambulatory, head->age
	);
	
	if(head->emergency)
		printf(" (Emergenza)\n");

	head = popNode(head, 0);
}

Node* moveElderlyForward(Node* head) {
	Node* current = head;
	Node* head2 = head;
	int pos = 0;

	while(current != NULL) {
		if(current->age > 70) {
			head = addNode(head, current->age, current->emergency);
			current = current->next;
			head = popNode(head, pos);
		} else
			current = current->next;

		pos++;
	}

	return head;
}

Node* moveChildrenAfterElderly(Node* head) {
	Node* current = head;
	int pos = 0;

	while(current != NULL) {
		if(current->age < 2) {
			head = insertNodeWhereGreater(head, current->age, current->emergency);
			current = current->next;
			head = popNode(head, pos);
		} else
			current = current->next;

		pos++;
	}

	return head;
}

Node* generateRandomPatient(Node* head) {
	int age = rand() % 100;
	int emergency = rand() % 2;

	if(emergency)
		return addNode(head, age, emergency);
	else
		return appendNode(head, age, emergency);		
}

/*
	LIB
*/

Node* initNode(int value, int emergency) {
	Node* result = (Node*) malloc(sizeof(Node));
	result->age = value;
	result->emergency = emergency;
	result->next = NULL;
	return result;
}

Node* appendNode(Node* head, int value, int emergency) {
	//	If the list is empty, return the new node;
	if(head == NULL)
		return initNode(value, emergency);

	Node* current = head;

	while(current->next != NULL)
		current = current->next;

	//	Append the new node to the last one;
	current->next = initNode(value, emergency);
	return head;
}

Node* addNode(Node* head, int value, int emergency) {
	Node* newHead = initNode(value, emergency);
	newHead->next = head;
	return newHead;
}

Node* insertNodeWhereGreater(Node* head, int value, int emergency) {
	//	If the list is empty or the new node has a value higher than 70, return the new node;
	if(head == NULL || head->age < 70)
		return addNode(head, value, emergency);

	Node* current = head;

	//	Iterate through the list to find the last node with a lower value;
	while(current->next != NULL && current->next->age > 70)
		current = current->next;

	//	Insert the new node after the last node with a lower value;
	Node* newNode = initNode(value, emergency);
	newNode->next = current->next;
	current->next = newNode;
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
	while(toPop->next != NULL && position > 0) {
		prev = toPop;
		toPop = toPop->next;
		position--;
	}

	prev->next = toPop->next;
	free(toPop);
	return head;
}

void printList(Node* head) {
	while(head != NULL) {
		printf("\n\tEta': %d", head->age);

		if(head->emergency)
			printf(" (Emergenza)");

		head = head->next;
	}
}

void exportToFile(Node* head) {
	FILE* dest = fopen("patients.txt", "w");

	if(dest == NULL) {
		printf("\nErrore nell'apertura del file.\n");
		return;
	}

	printf("\nEsportazione dei pazienti...");

	while(head != NULL) {
		if(head->emergency)
			fprintf(dest, "Paziente (Emergenza):");
		else
			fprintf(dest, "Paziente:");

		fprintf(dest,"\n\tEta': %d\n\n", head->age);
		head = head->next;
	}

	fclose(dest);
}