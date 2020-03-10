// Alan Zhang 2/29/20
// BST.cpp

#include "BST.h"
#include <stack>
#include <list>

using namespace std;

BST::~BST() {
	delete root;
}

void BST::insert(int element) {
	if (!root) {
		root = new Node(element);
		cout << "Element inserted" << endl;
		return;
	}

	Node* n = root;
	while (n) {
		if (element < n->val) {
			if (n->left) {
				n = n->left;
			} else {
				n->left = new Node(element);
				cout << "Element inserted" << endl;
				return;
			}
		} else if (element > n->val) {
			if (n->right) {
				n = n->right;
			} else {
				n->right = new Node(element);
				cout << "Element inserted" << endl;
				return;
			}
		} else if (element == n->val) {
			cout << "Element already present" << endl;
			return;
		}	
	}
}

void BST::access(int element) {
	if (!root) {
		cout << "Element not found" << endl;
		return;
	}

	Node* n = root;
	while (n) {
		if (element > n->val) {
			n = n->right;
		} else if (element < n->val) {
			n = n->left;
		} else if (element == n->val) {
			cout << "Element accessed" << endl;
			return;
		}	
	}
	cout << "Element not found" << endl;
}

void BST::deleteElement(int element) {
	if (!root) {
		cout << "Element not found" << endl;
		return;
	}

	Node* n = root;
	Node* par = root;
	while (n) {
		if (element > n->val) {
			par = n;
			n = n->right;
		} else if (element < n->val) {
			par = n;
			n = n->left;
		} else if (element == n->val) {
			if (!n->left && !n->right) {
				cout << "problem1" << endl;
				// delete n;
				// n = NULL;
				if (n == root) {
					root = NULL;
					delete root;
				} else {
					if (n == par->left) {
						par->left = NULL;
					}
					if (n == par->right) {
						par->right = NULL;
					}
				}
				delete n;
			} else if (n->left && !n->right) {
				// cout << "problem2" << endl;
				if (n == root) {
					root = NULL;
				}
				Node* temp = n->left;
				n->val = temp->val;
				n->left = temp->left;
				n->right = temp->right;
				// delete temp;
				// temp = NULL;
				// free(temp);
				temp->left = NULL;
				temp->right = NULL;
				delete temp;
			} else if (n->right && !n->left) {
				// cout << "problem 3" << endl;
				Node* temp = n->right;
				n->val = temp->val;
				n->left = temp->left;
				n->right = temp->right;
				// delete temp;
				// temp = NULL;
				temp->left = NULL;
				temp->right = NULL;
				delete temp;
			} else if (n->left && n->right) {
				// cout << "problem 4" << endl;
				Node* temp = n;
				Node* parent = n;
				temp = temp->right;
				while (temp->left) {
					parent = temp;
					temp = temp->left;
				}
				n->val = temp->val;
				if (temp == parent->right) {
					parent->right = NULL;
				} else if (temp == parent->left) {
					parent->left = NULL;
				}
				// delete temp;
				// temp = NULL;
				temp->left = NULL;
				temp->right = NULL;
				delete temp;
			}
			cout << "Element deleted" << endl;
			// par = NULL;
			// n = NULL;
			// delete par;
			// delete n;
			return;
		}	
	}
	cout << "Element not found" << endl;
} 

void preOrderTraversal(Node* n) {
	stack<Node*> nodeStack;
	nodeStack.push(n);
	while (!nodeStack.empty()) {
		Node* temp = nodeStack.top();
		nodeStack.pop();

		if (temp->right) {
			nodeStack.push(temp->right);
		}
		if (temp->left) {
			nodeStack.push(temp->left);
		}

		if (nodeStack.empty()) {
			cout << temp->val;
		} else {
			cout << temp->val << " ";
		}
	}
	cout << endl;
} 

void inOrderTraversal(Node* n) {
	stack<Node*> nodeStack;
	
	while (n || !nodeStack.empty()) {
		while (n) {
			nodeStack.push(n);
			n = n->left;
		}
		n = nodeStack.top();
		nodeStack.pop();

		if (n->right || !nodeStack.empty()) {
			cout << n->val << " ";
		} else {
			cout << n->val;
		}

		n = n->right;
	}
	cout << endl;
} 

void postOrderTraversal(Node* n) {
	stack<Node*> nodeStack;

    do {
        while (n) {
            if (n->right) {
                nodeStack.push(n->right);
            }
            nodeStack.push(n);

            n = n->left;
        }
        
        n = nodeStack.top();
        nodeStack.pop();
       
        if (n->right && !nodeStack.empty() && nodeStack.top() == n->right) {
            nodeStack.pop();
            nodeStack.push(n);
            n = n->right;
        } else {
        	if (nodeStack.empty()) {
        		cout << n->val;
        	} else {
            	cout << n->val << " ";
            	n = NULL;
        	}
        }
    } while(!nodeStack.empty());

    cout << endl;
} 

void BST::print() {
	if (!root) {
		cout << "Empty tree" << endl;
		return;
	}

	preOrderTraversal(root);
	inOrderTraversal(root);
	postOrderTraversal(root);
	return;
} 

void BST::printBFS() {
	if (!root) {
		cout << "Empty tree" << endl;
		return;
	}

	list<Node*> nodeQueue;

	nodeQueue.push_back(root);

	while (!nodeQueue.empty()) {
		Node* n = nodeQueue.front();
		nodeQueue.pop_front();

		if (n->left) {
			nodeQueue.push_back(n->left);
		}
		if (n->right) {
			nodeQueue.push_back(n->right);
		}

		if (nodeQueue.empty()) {
			cout << n->val;
		} else {
			cout << n->val << " ";
		}
	}
	cout << endl;
}
