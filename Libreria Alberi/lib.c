#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
	int key;
	struct Node* left;
	struct Node* right;
} Node;

typedef Node* Nodept;

Nodept createNode(int key);
Nodept insertNode(Nodept root, int key);

Nodept searchNode(Nodept root, int key);
Nodept searchNodeMin(Nodept root);
Nodept searchNodeMax(Nodept root);

Nodept removeNode(Nodept root, int key);

void preorderTraversal(Nodept root);
void inorderTraversal(Nodept root);
void postorderTraversal(Nodept root);

Nodept createNode(int key) {
	Nodept newNode = (Nodept) malloc(sizeof(Node));
	newNode->key = key;
	newNode->left = NULL;
	newNode->right = NULL;
	return newNode;
}

Nodept insertNode(Nodept root, int key) {
	if(root == NULL)
		return createNode(key);

	if(root->key == key)
		return root;

	if(key < root->key)
		root->left = insertNode(root->left, key);
	else
		root->right = insertNode(root->right, key);

	return root;
}

Nodept searchNode(Nodept root, int key) {
	if(root == NULL)
		return NULL;

	if(root->key == key)
		return root;

	if(key < root->key)
		return searchNode(root->left, key);

	return searchNode(root->right, key);
}

Nodept searchNodeMin(Nodept root) {
	if(root == NULL)
		return NULL;

	if(root->left == NULL)
		return root;

	return searchNodeMin(root->left);
}

Nodept searchNodeMax(Nodept root) {
	if(root == NULL)
		return NULL;

	if(root->right == NULL)
		return root;

	return searchNodeMax(root->right);
}

Nodept removeNode(Nodept root, int key) {
	if(root == NULL)
		return NULL;
	
	if(key < root->key) { 
		root->left = removeNode(root->left, key);
		return root;
	}
	
	if(key > root->key) {
		root->right = removeNode(root->right, key);
		return root;
	}

	if(root->left == NULL && root->right == NULL) {
		free(root);
		return NULL;
	}
	
	if(root->left == NULL) {
		Nodept right = root->right;
		free(root);
		return right;
	}
	
	if(root->right == NULL) {
		Nodept left = root->left;
		free(root);
		return left;
	}
	
	Nodept minInRight = searchNodeMin(root->right);
	root->key = minInRight->key;
	root->right = removeNode(root->right, minInRight->key);
	return root;
}

void preorderTraversal(Nodept root) {
	if(root == NULL)
		return;

	printf("%d ", root->key);
	preorderTraversal(root->left);
	preorderTraversal(root->right);
}

void inorderTraversal(Nodept root) {
	if(root == NULL)
		return;

	inorderTraversal(root->left);
	printf("%d\t", root->key);
	inorderTraversal(root->right);
}

void postorderTraversal(Nodept root) {
	if(root == NULL)
		return;

	postorderTraversal(root->left);
	postorderTraversal(root->right);
	printf("%d ", root->key);
}