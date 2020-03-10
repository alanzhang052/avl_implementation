// Alan Zhang 2/29/20
// BST.h

#ifndef BST_H
#define BST_H

#include <iostream>

struct Node {
	Node(int element) {
		val = element;
		left = NULL;
		right = NULL;
	} 
	~Node() {
		delete left;
		delete right;
	}
	Node* left;
	Node* right;
	int val;
};

class BST {
public:
	~BST();
	void insert(int element);
	void access(int element);
	void deleteElement(int element);
	void print();
	void printBFS();

private:
	Node* root;
};

#endif