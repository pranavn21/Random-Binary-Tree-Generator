// Pranav Nair
// CS 3345 (UTDallas)
// NETID: PXN190027
// Modified code, originally provided by Professor Kamran Khan
// Due Date 10/24/2021

//#include <bits/stdc++.h>

#include <stdlib.h>
#include <time.h>
#include <fstream>
#include <iostream>

using namespace std;

struct Node {
	int data;
	struct Node* left;
	struct Node* right;
	int height;

	// val is the key or the value that
	// has to be added to the data part
	Node(int val)
	{
		data = val;
		height = 1;
		// Left and right child for node
		// will be initialized to null
		left = NULL;
		right = NULL;
	}
};

//taken from AVLTree.cpp
int height(Node *N)
{
	if (N == NULL)
		return 0;
	return N->height;
}


bool isBST(Node* root){
	if (root == NULL){
		return true; //if it's empty tree, it's a bst tree
	}
	if(root->left != NULL && root->data < root->left->data){
		// cout << "left problem at " << root->data << root->left->data << endl; For debuggin purposes 
		return false;
	}
	if(root->right != NULL && root->data > root->right->data){
		// cout << "right problem at " << root->data << endl; For debugging purposes
		return false;
	}
	return isBST(root->left) && isBST(root->right);
}

bool isAVL(Node* root){
	if (root == NULL){
		return true; //if empty tree, it's avl
	}
	int h1 = height(root->left);
	int h2 = height(root->right);
	
	if((h1-h2 < -1) || (h1-h2 > 1)){ //lopsided tree
		return false;
	}
	return isAVL(root->left) && isAVL(root->right);
}

//Copied from AVLTree.cpp
int max(int a, int b)
{
	return (a > b)? a : b;
}

Node* insert(Node* root, int key){
	if (root == NULL){ //empty tree
		return new Node(key);
	}

	Node* n = root;
	int dir = rand()%2; // value of 0 or 1
		
	if (dir == 0){ //left
		n->left = insert(n->left, key);
	} 
		
	else{ // right
		n->right = insert(n->right, key);
	}
	
	n->height = 1 + max(height(n->left),height(n->right)); //Updating height
	return root;
}

Node* readBook(char inputFile[])
{
	ifstream iFile(inputFile);
	int ISBN;
	char title[25];
	char lastName[25];
	Node* root = NULL;

	while(iFile >> ISBN >> title >> lastName){
		root = insert(root, ISBN);
	}

	return root;
}

int main()
{
	srand(time(NULL));
	
	/*create root*/
	struct Node* root = readBook((char*) "input.txt"); //  Very less likely to create a BST or AVL (even rarer). Use input3.txt instead to test if BST/AVL input occurs
	bool BSTstatus = isBST(root);

	if (BSTstatus){
	bool AVLstatus = isAVL(root);
		if (AVLstatus){
			cout << "The random binary tree did create an AVL tree." << endl;
		}
		else{
			cout << "The random binary tree did create a binary search tree but not an AVL tree." << endl;
		}
	}
	else{
		cout << "The random binary tree did not create as a binary search tree." << endl;
	}

	return 0;
}
