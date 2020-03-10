// Alan Zhang 2/29/20
// AVL.h

#ifndef AVL_H
#define AVL_H

#include <iostream>

struct Node {
	Node(int element) {
		val = element;
		left = NULL;
		right = NULL;
		height = 1;
	} 
	~Node() {
		delete left;
		delete right;
	}
	Node* left;
	Node* right;
	int val;
	int height;
};

class AVL {
public:
	~AVL();
	Node* getRoot();
	int getHeight(Node* n);
	int getBalance(Node* n);
	Node* rotateLeft(Node* n);
	Node* rotateRight(Node* n);

	Node* insert(int element, Node* n);
	void access(int element);
	Node* deleteElement(int element, Node* n);
	void print();
	void printBFS();

private:
	Node* root;
	bool isBalanced = true;
};

#endif