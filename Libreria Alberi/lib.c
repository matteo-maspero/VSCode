#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
	int data;
	struct Node* left;
	struct Node* right;
} Node;

typedef Node* Nodept;

/*
	FUNCTIONS
*/

Nodept createNode(int data);
Nodept insertNodeBST(Nodept root, int data);

Nodept findNode(Nodept root, int data);
Nodept findNodeMin(Nodept root);
Nodept findNodeMax(Nodept root);

Nodept removeNode(Nodept root, int data);

void preorderTraversal(Nodept root);
void inorderTraversal(Nodept root);
void postorderTraversal(Nodept root);

/*
	FUNCTIONS
*/

Nodept createNode(int data) {
	Nodept newNode = (Nodept) malloc(sizeof(Node));
	newNode->data = data;
	newNode->left = NULL;
	newNode->right = NULL;
	return newNode;
}

Nodept insertGeneric(Nodept root, int data) {
	if(root == NULL)
		return createNode(data);
		
	if(root->left == NULL)
		root->left = insertGeneric(root->left, data);
	else
		root->right = insertGeneric(root->right, data);

	return root;
}

Nodept insertNodeBST(Nodept root, int data) {
	if(root == NULL)
		return createNode(data);

	if(data < root->data)
		root->left = insertNodeBST(root->left, data);
	else
		root->right = insertNodeBST(root->right, data);

	return root;
}

Nodept findNode(Nodept root, int data) {
	if(root == NULL)
		return NULL;

	if(root->data == data)
		return root;

	Nodept left = findNode(root->left, data);
	if(left != NULL)
		return left;

	return findNode(root->right, data);
}

Nodept findNodeMin(Nodept root) {
	if(root == NULL)
		return NULL;

	if(root->left == NULL)
		return root;

	return findNodeMin(root->left);
}

Nodept findNodeMax(Nodept root) {
	if(root == NULL)
		return NULL;

	if(root->right == NULL)
		return root;

	return findNodeMax(root->right);
}

Nodept removeNode(Nodept root, int data) {
	if(root == NULL)
		return NULL;

	if(data < root->data)
		root->left = removeNode(root->left, data);
	else if(data > root->data)
		root->right = removeNode(root->right, data);
	
	if(root->data != data)
		return root;
	
	if(root->left == NULL && root->right == NULL) {
		free(root);
		return NULL;
	}

	Nodept temp = NULL;

	if(root->left == NULL) {
		temp = root->right;
		free(root);
		return temp;
	}

	if(root->right == NULL) {
		temp = root->left;
		free(root);
		return temp;
	}

	temp = findNodeMin(root->right);
	root->data = temp->data;
	root->right = removeNode(root->right, temp->data);
	return root;
}

void preorderTraversal(Nodept root) {
	if(root == NULL)
		return;

	printf("%d ", root->data);
	preorderTraversal(root->left);
	preorderTraversal(root->right);
}

void inorderTraversal(Nodept root) {
	if(root == NULL)
		return;

	inorderTraversal(root->left);
	printf("%d ", root->data);
	inorderTraversal(root->right);
}

void postorderTraversal(Nodept root) {
	if(root == NULL)
		return;

	postorderTraversal(root->left);
	postorderTraversal(root->right);
	printf("%d ", root->data);
}