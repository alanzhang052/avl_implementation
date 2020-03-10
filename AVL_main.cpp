#include "AVL.h"
#include <sstream>

using namespace std;

int main(int argc, char* argv[]) {
	if (argc != 2) {
		cout << "Format: ./avl [string]" << endl;
		exit(1);
	}

	AVL* q = new AVL();

	stringstream ss;
	string func, bfs;
	int num;

	ss << argv[1];

	while (ss >> func) {
		if (func == "insert") {
			ss >> num;
			(*q).insert(num, (*q).getRoot());
		} else if (func == "access") {
			ss >> num;
			(*q).access(num);
		} else if (func == "delete") {
			ss >> num;
			(*q).deleteElement(num, (*q).getRoot());
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