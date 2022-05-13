// main.cpp - Assignment 6
// Antonio Fernandez
// 301393610

#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>
#include "avltree.hpp"

int main() {
	cout << "Running test driver for AVL Tree Class..." << endl << endl;
	srand(time(0));
	AVLTree* T1 = new AVLTree;
	int n;

	for (int i = 0; i < 4; i++) {
		// Generate random keys from -50 to 50
		n = (rand() % 999 + 1) - 500;
		T1->put(n);
	}

	T1->put(3);
	T1->put(3);
	T1->put(18);

	cout << "T1: " << endl;
	T1->print();
	T1->erase(18);

	cout << "T1 after deletion:" << endl;
	T1->print();

	AVLTree::Node* n1 = T1->find(3);
	cout << n1->key << endl << endl;

	AVLTree::Node* n2 = T1->find(18);
	if (n2 == T1->getEnd()) {
		cout << "Found end pointer! Input key does not exist." << endl << endl;
	} else {
		cout << "Did not find anything." << endl << endl;
	}

	cout << "Inorder sequence of Tree:" << endl;
	T1->inOrderPrint(T1->getRoot());
	cout << endl << endl;

	delete T1;

	AVLTree* T2 = new AVLTree;

	for (int i = 0; i < 95; i++) {
		// Generate random keys from -50 to 50
		n = (rand() % 999 + 1) - 500;
		T2->put(n);
	}

	T2->put(33);
	T2->put(65);
	T2->put(79);
	T2->put(72);
	T2->put(50);


	cout << "T2: " << endl;
	T2->print();

	T2->erase(50);
	T2->erase(33);
	T2->erase(65);
	T2->erase(79);
	T2->erase(72);

	cout << "T2 after deletion:" << endl;
	T2->print();

	cout << "Inorder sequence of Tree:" << endl;
	T2->inOrderPrint(T2->getRoot());
	cout << endl << endl;

	delete T2;

	return 0;
}