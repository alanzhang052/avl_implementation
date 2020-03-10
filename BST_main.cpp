// Alan Zhang 2/29/20
// main.cpp

#include "BST.h"
#include <sstream>

using namespace std; 

int main(int argc, char* argv[]) {
	if (argc != 2) {
		cout << "Format: ./bst [string]" << endl;
		exit(1);
	}

	BST* q = new BST();

	stringstream ss;
	string func, bfs;
	int num;

	ss << argv[1];

	while (ss >> func) {
		if (func == "insert") {
			ss >> num;
			(*q).insert(num);
		} else if (func == "access") {
			ss >> num;
			(*q).access(num);
		} else if (func == "delete") {
			ss >> num;
			(*q).deleteElement(num);
		} else if (func == "print," || func == "print") {
			ss >> bfs;
			if (bfs == "bfs," || bfs == "bfs") {
				(*q).printBFS();
			} else {
				for (int i = 0; i < bfs.size(); i++) {
					ss.unget();	
				}
				(*q).print();
			}
		}
	}

	delete q;

	return 0;
}
