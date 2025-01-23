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

Nodept searchNodeGeneric(Nodept root, int key);
Nodept searchNodeMinGeneric(Nodept root, Nodept min);
Nodept searchNodeMaxGeneric(Nodept root, Nodept max);

int heightGeneric(Nodept root);
int countNodesGeneric(Nodept root);
int sumNodesGeneric(Nodept root);

Nodept removeNode(Nodept root, int key);

void preorderTraversal(Nodept root);
void inorderTraversal(Nodept root);
void postorderTraversal(Nodept root);

int main() {
	Nodept root = NULL;

	root = insertNode(root, 2);
	root = insertNode(root, 1);
	root = insertNode(root, 8);
	root = insertNode(root, 7);
	root = insertNode(root, 6);
	root = insertNode(root, 9);
	root = insertNode(root, 4);
	root = insertNode(root, 7);
	root = insertNode(root, 3);
	root = insertNode(root, 5);
	
	preorderTraversal(root);
	printf("\n");
	inorderTraversal(root);
	printf("\n");
	postorderTraversal(root);
	printf("\n");

	return 0;
}

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

Nodept searchNodeGeneric(Nodept root, int key) {
	if(root == NULL)
		return NULL;

	if(root->key == key)
		return root;

	Nodept left = searchNodeGeneric(root->left, key);

	if(left != NULL)
		return left;
	return searchNodeGeneric(root->right, key);
}

Nodept searchNodeMinGeneric(Nodept root, Nodept min) {
	if(root == NULL)
		return min;

	if(min == NULL || root->key < min->key)
		min = root;

	Nodept left = searchNodeMinGeneric(root->left, min);
	Nodept right = searchNodeMinGeneric(root->right, min);

	if(left != NULL && left->key < min->key)
		min = left;
	if(right != NULL && right->key < min->key)
		min = right;
	return min;
}

Nodept searchNodeMaxGeneric(Nodept root, Nodept max) {
	if(root == NULL)
		return max;

	if(max == NULL || root->key > max->key)
		max = root;

	Nodept left = searchNodeMaxGeneric(root->left, max);
	Nodept right = searchNodeMaxGeneric(root->right, max);

	if(left != NULL && left->key > max->key)
		max = left;
	if(right != NULL && right->key > max->key)
		max = right;
	return max;
}

int heightGeneric(Nodept root) {
	if (root == NULL)
		return 0;

	int leftHeight = heightGeneric(root->left);
	int rightHeight = heightGeneric(root->right);

	if(leftHeight > rightHeight)
		return leftHeight + 1;
	return rightHeight + 1;
}

int countNodesGeneric(Nodept root) {
	if(root == NULL)
		return 0;
	return countNodesGeneric(root->left) + countNodesGeneric(root->right) + 1;
}

int sumNodesGeneric(Nodept root) {
	if(root == NULL)
		return 0;
	return sumNodesGeneric(root->left) + sumNodesGeneric(root->right) + root->key;
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

	printf("%d\t", root->key);
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
	printf("%d\t", root->key);
}
