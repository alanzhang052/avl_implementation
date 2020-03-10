// Alan Zhang 2/29/20
// AVL.cpp

#include "AVL.h"
#include <stack>
#include <list>

using namespace std;

AVL::~AVL() {
	delete root;
}

Node* AVL::getRoot() {
	return root;
}

int AVL::getHeight(Node* n) {
	if (!n) {
		return 0;
	}
	return n->height;
}

int AVL::getBalance(Node* n) {
	if (!n) {
		return 0;
	}
	// cout << "Node: " << n->val << " " << getHeight(n->left) << " " << getHeight(n->right) << endl;
	return getHeight(n->left) - getHeight(n->right);
}

Node* AVL::rotateLeft(Node* n) {
	Node* a = n->right;
	Node* b = n->right->left;

	a->left = n;
	n->right = b;

	n->height = max(getHeight(n->left), getHeight(n->right)) + 1;
	a->height = max(getHeight(a->left), getHeight(a->right)) + 1;

	return a;
}  

Node* AVL::rotateRight(Node* n) {  
    Node* a = n->left;  
    Node* b = n->left->right; 

    a->right = n;  
    n->left = b;  

    n->height = max(getHeight(n->left), getHeight(n->right)) + 1;  
    a->height = max(getHeight(a->left), getHeight(a->right)) + 1;  

    return a;  
}  

Node* AVL::insert(int element, Node* n){
	if (!root) {
		cout << "Element inserted" << endl;
		root = new Node(element);
		return root;
	}

	if (!n) { 
		cout << "Element inserted" << endl;
		return new Node(element);
	}
	
	if (element < n->val)  {
		n->left = insert(element, n->left);
	} else if (element > n->val) {
		n->right = insert(element, n->right);
	} else {
		cout << "Element already present" << endl;
		return n;
	}

	n->height = max(getHeight(n->left), getHeight(n->right)) + 1;

	int bal = getBalance(n);
	// cout << "Node: " << n->val << " " << bal << endl;

	if (bal > 1 && element < n->left->val) { // #1 - (LL) Single Rotation
		// cout << "Left Left Rotation" << endl;
		if (n == root) {
			root = rotateRight(n);
			return root;
		} else {
			return rotateRight(n);
		}
	} 
	if (bal < -1 && element > n->right->val) { // #2 - (RR) Single Rotation
		// cout << "Right Right Rotation" << endl;
		if (n == root) {
			root = rotateLeft(n);
			return root;
		} else {
			return rotateLeft(n);
		}
	}
	if (bal > 1 && element > n->left->val) { // #1 - (LR) Double Rotation
		// cout << "Left Right Rotation" << endl;
		n->left = rotateLeft(n->left);
		if (n == root) {
			root = rotateRight(n);
			return root;
		} else {
			return rotateRight(n);
		}
	} 
	if (bal < -1 && element < n->right->val) { // #2 - (RL) Double Rotation
		// cout << "Right Left Rotation" << endl;
		n->right = rotateRight(n->right);
		if (n == root) {
			root = rotateLeft(n);
			return root;
		} else {
			return rotateLeft(n);
		}
	}
	return n;
}

void AVL::access(int element){
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

Node* AVL::deleteElement(int element, Node* n){
	if (!root) {
		cout << "Element not found" << endl;
		return 0;
	}

	if (!n) { 
		cout << "Element not found" << endl;
		return 0;
	}
	
	if (element < n->val)  {
		// cout << n->val << endl;
		n->left = deleteElement(element, n->left);
	} else if (element > n->val) {
		// cout << n->val << endl;
		n->right = deleteElement(element, n->right);
	} else {
		if (!n->left && !n->right) {
			// cout << "problem1" << endl;
			// delete n;
			// n = NULL;
			n->left = NULL;
			n->right = NULL;
			delete n;
		} else if (n->left && !n->right) {
			// cout << "problem2" << endl;
			Node* temp = n->left;
			n->val = temp->val;
			n->left = temp->left;
			n->right = temp->right;
			// delete temp;
			// temp = NULL;
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
	}

	if (!n) {
		return root;
	}

	n->height = max(getHeight(n->left), getHeight(n->right)) + 1;

	int bal = getBalance(n);
	// cout << "Node: " << n->val << " " << bal << endl;

	if (bal > 1 && element < n->left->val) { // #1 - (LL) Single Rotation
		// cout << "Left Left Rotation" << endl;
		if (n == root) {
			root = rotateRight(n);
			return root;
		} else {
			return rotateRight(n);
		}
	} 
	if (bal < -1 && element > n->right->val) { // #2 - (RR) Single Rotation
		// cout << "Right Right Rotation" << endl;
		if (n == root) {
			root = rotateLeft(n);
			return root;
		} else {
			return rotateLeft(n);
		}
	}
	if (bal > 1 && element > n->left->val) { // #1 - (LR) Double Rotation
		// cout << "Left Right Rotation" << endl;
		n->left = rotateLeft(n->left);
		if (n == root) {
			root = rotateRight(n);
			return root;
		} else {
			return rotateRight(n);
		}
	} 
	if (bal < -1 && element < n->right->val) { // #2 - (RL) Double Rotation
		// cout << "Right Left Rotation" << endl;
		n->right = rotateRight(n->right);
		if (n == root) {
			root = rotateLeft(n);
			return root;
		} else {
			return rotateLeft(n);
		}
	}
	return n;
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

void AVL::print() {
	if (!root) {
		cout << "Empty tree" << endl;
		return;
	}

	preOrderTraversal(root);
	inOrderTraversal(root);
	postOrderTraversal(root);
	return;
} 

void AVL::printBFS() {
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
