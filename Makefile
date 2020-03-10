all: bst.out avl.out
	
bst.out: BST.h BST.cpp BST_main.cpp
	g++ -std=c++11 -o bst BST_main.cpp BST.cpp

avl.out: AVL.h AVL.cpp AVL_main.cpp
	g++ -std=c++11 -o avl AVL_main.cpp AVL.cpp

clean:
	rm bst
	rm avl
