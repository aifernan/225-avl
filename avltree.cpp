// avltree.cpp
// Antonio Fernandez 
// 301393610

#include <iostream>
#include <string>
#include "avltree.hpp"

using namespace std;

// ----- EXCEPTION CLASS ----- //
EmptyTreeException::EmptyTreeException(string err) : errMsg(err) {}


EmptyTreeException::~EmptyTreeException() {}


string EmptyTreeException::getError() {return errMsg;}



// ----- NODE CLASS ----- //
AVLTree::Node::Node(int k, int h) : key(k), height(h), left(NULL), right(NULL), parent(NULL) {}


AVLTree::Node::~Node() {
	parent = NULL;
	left = NULL;
	right = NULL;
}


void AVLTree::Node::setKey(int k) {
	key = k;
	return;
}


bool AVLTree::Node::isExternal() {
	return (left == NULL && right == NULL);
}


bool AVLTree::Node::isRoot() {
	return (parent == NULL);
}



// ----- AVL TREE CLASS ----- //
// Constructor
AVLTree::AVLTree() : num_elems(0), root(new AVLTree::Node(0, 1)), end(new AVLTree::Node(0, -1)) {
	cout << "Counstructing new tree..." << endl << endl;
	root->parent = NULL;
	root->left = new AVLTree::Node;
	root->right = new AVLTree::Node;
}


// Helper function for destruction
void AVLTree::destruct(AVLTree::Node* n) {
	// Using postorder
	if (n != NULL) {
		destruct(n->left);
		destruct(n->right);
		delete n;
	}
	return;
}


// Destructor
AVLTree::~AVLTree() {
	destruct(root);
}


int AVLTree::max(int x, int y) {
	if (x >= y) {
		return x;
	} else {
		return y;
	}
}


// Functions that rotate the subtree rooted with n
// Returns the new root of the rotated subtree 
AVLTree::Node* AVLTree::right_rotate(AVLTree::Node* n) {
	if (n->isRoot()) {
		AVLTree::Node* left_tree = n->left;
		AVLTree::Node* right_tree_of_left = left_tree->right;

		// Rotate and update heights
		left_tree->right = n;
		right_tree_of_left->parent = n;
		n->left = right_tree_of_left;
		n->parent = left_tree;
		left_tree->parent = NULL;

		n->height = max(n->left->height, n->right->height) + 1;
		left_tree->height = max(left_tree->left->height, left_tree->right->height) + 1;

		return left_tree;

	} else {
		AVLTree::Node* left_tree = n->left;
		AVLTree::Node* right_tree_of_left = left_tree->right;
		AVLTree::Node* n_parent = n->parent;

		// Decouple
		if (n == n_parent->left) {
			n_parent->left = NULL;
		} else {
			n_parent->right = NULL;
		}
		n->parent = NULL;


		// Rotate and update heights
		left_tree->right = n;
		right_tree_of_left->parent = n;
		n->left = right_tree_of_left;
		n->parent = left_tree;
		left_tree->parent = NULL;

		n->height = max(n->left->height, n->right->height) + 1;
		left_tree->height = max(left_tree->left->height, left_tree->right->height) + 1;

		// Relink
		if (left_tree->key >= n_parent->key) {
			n_parent->right = left_tree;
		} else {
			n_parent->left = left_tree;
		}
		left_tree->parent = n_parent;

		return left_tree;
	}
}


AVLTree::Node* AVLTree::left_rotate(AVLTree::Node* n) {
	if (n->isRoot()) {
		AVLTree::Node* right_tree = n->right;
		AVLTree::Node* left_tree_of_right = right_tree->left;		

		// Rotate and update heights
		right_tree->left = n;
		left_tree_of_right->parent = n;
		n->right = left_tree_of_right;
		n->parent = right_tree;
		right_tree->parent = NULL;

		n->height = max(n->left->height, n->right->height) + 1;
		right_tree->height = max(right_tree->left->height, right_tree->right->height) + 1;

		return right_tree;

	} else { 
		AVLTree::Node* right_tree = n->right;
		AVLTree::Node* left_tree_of_right = right_tree->left;
		AVLTree::Node* n_parent = n->parent;

		// Decouple
		if (n == n_parent->left) {
			n_parent->left = NULL;
		} else {
			n_parent->right = NULL;
		}
		n->parent = NULL;

		// Rotate and update heights
		right_tree->left = n;
		left_tree_of_right->parent = n;
		n->right = left_tree_of_right;
		n->parent = right_tree;
		right_tree->parent = NULL;

		n->height = max(n->left->height, n->right->height) + 1;
		right_tree->height = max(right_tree->left->height, right_tree->right->height) + 1;

		// Relink
		if (right_tree->key >= n_parent->key) {
			n_parent->right = right_tree;
		} else {
			n_parent->left = right_tree;
		}
		right_tree->parent = n_parent;


		return right_tree;
	}
}


// Checking and choosing function
// Choose appropriate rotations on an unbalanced subtree rooted at curr
AVLTree::Node* AVLTree::rebalance(AVLTree::Node* curr) {
	int balance_of_children = curr->left->height - curr->right->height;

	if (balance_of_children < -1 || balance_of_children > 1) { // If unbalanced, rotate according to 4 cases:
		// Left left
		if (balance_of_children > 1 && curr->left->left->height >= curr->left->right->height) {
			return right_rotate(curr);
		}
		// Right right
		else if (balance_of_children < -1 && curr->right->right->height >= curr->right->left->height) {
			return left_rotate(curr);
		}
		// Left right
		else if (balance_of_children > 1 && curr->left->left->height < curr->left->right->height) {
			curr->left = left_rotate(curr->left);
			return right_rotate(curr);
		}
		// Right left 
		else if (balance_of_children < -1 && curr->right->right->height < curr->right->left->height) {
			curr->right = right_rotate(curr->right);
			return left_rotate(curr);
		}
	}
	
	// If nothing happened, nothing happened.
	return curr;
}


// If the tree has Node with key k, return it
// Else return end
AVLTree::Node* AVLTree::find(int k) const {
	cout << "Finding " << k << "..." << endl;

	AVLTree::Node* curr = root;

	while (curr->isExternal() != 1) {
		if (curr->key < k) {
			curr = curr->right;	
		}
		else if (curr->key > k) {
			curr = curr->left;
		} 
		else if (curr->key == k) {
			return curr;
		}
	}

	cout << "Success!" << endl << endl;
	return end;
}


// Add k to the AVLTree (duplicates allowed), return its node
AVLTree::Node* AVLTree::put(int k) {
	cout << "Putting " << k << "..." << endl;

	AVLTree::Node* input_node = new AVLTree::Node(k, 1);
	input_node->left = new AVLTree::Node;
	input_node->right = new AVLTree::Node;

	// INSERTION //
	// Insert as in a normal BST, adding the height to the nodes we visit
	// Go to the right subtree if we have a duplicate
	if (size() == 0) {
		root->key = k;
		root->height = 1;
		num_elems++;

		return root;
	}

	AVLTree::Node* curr = root;
	AVLTree::Node* prev = root;

	while (curr->isExternal() != 1) {
		if (k >= curr->key) {
			prev = curr;
			curr = curr->right;
		} else {
			prev = curr;
			curr = curr->left;
		}
	}

	// We are now at an external node, now we insert
	if (k >= prev->key) {
		prev->right = input_node;
		input_node->parent = prev;
	} else {
		prev->left = input_node;
		input_node->parent = prev;
	}

	num_elems++;

	// UPDATING HEIGHTS //
	// Going up from our node, update the heights of all the node's ancestors.
	AVLTree::Node* curr2 = input_node;
	while (curr2 != NULL) {
		curr2->height = max(curr2->left->height, curr2->right->height) + 1;
		curr2 = curr2->parent;
	}

	// BALANCING //
	// Go up the tree towards towards the root, rebalancing as needed.
	// Take care of parent pointers
	AVLTree::Node* curr3 = input_node;
	AVLTree::Node* curr3_parent = input_node->parent;

	while (curr3->isRoot() != 1) {
		curr3 = rebalance(curr3);

		curr3_parent = curr3_parent->parent;
		curr3 = curr3->parent;
	}
	
	// We are now at the root, balance once more (no parent pointers to worry about)
	root = rebalance(root);
	
	cout << "Success!" << endl << endl;

	return input_node;
}


bool AVLTree::empty() const {return num_elems == 0;}


void AVLTree::erase(int k) throw (EmptyTreeException) {
	cout << "Deleting " << k << "..." << endl;
	if (empty()) {
		throw EmptyTreeException("Tree is empty!");
	}

	// DELETION //
	// Delete as in a normal BST
	AVLTree::Node* curr = find(k);
	if (curr == getEnd()) {
		cout << "Input not in tree." << endl << endl;
		return;
	}

	AVLTree::Node* prev = curr->parent;

	// 0 or 1 child case
	if (curr->left->isExternal() == 1 || curr->right->isExternal() == 1) {
		AVLTree::Node* to_bring_up;

		// to_bring_up would be an external node if curr had 0 children
		if (curr->left->isExternal()) {
			to_bring_up = curr->right;
		} else {
			to_bring_up = curr->left;
		}

		if (curr->isRoot()) {
			cout << "Trying to delete root, returning." << endl;
			return;
		}

		if (curr == prev->left) {
			prev->left = to_bring_up;
		} else if (curr == prev->right) {
			prev->right = to_bring_up;
		}

		to_bring_up->parent = prev;

		delete curr;

	// Two children case
	} else {
		AVLTree::Node* parent_of_successor;
		AVLTree::Node* inorder_successor = curr->right;

		// Find inorder successor
		while (inorder_successor->left->isExternal() != 1) {
			parent_of_successor = inorder_successor;
			inorder_successor = inorder_successor->left;
		}

		if (parent_of_successor->isRoot() != 1) {
			parent_of_successor->left = inorder_successor->right;
		} else {
			curr->right = inorder_successor->right;
		}

		curr->key = inorder_successor->key;
		delete inorder_successor;
	}

	num_elems--;

	// UPDATING HEIGHTS //
	// Find where k used to be, go up the tree to update height of the ancestors of k
	AVLTree::Node* curr2 = root;

	while (curr2->left->isExternal() != 1 && curr2->right->isExternal() != 1) {	
		if (k >= curr2->key) {
			curr2 = curr2->right;
		} else {
			curr2 = curr2->left;
		}
	}

	// Will be used for balancing up tree
	AVLTree::Node* curr3 = curr2;

	// Now go back up
	while (curr2 != NULL) {
		curr2->height = max(curr2->left->height, curr2->right->height) + 1;
		curr2 = curr2->parent;
	}

	// BALANCING //
	// Go up the tree towards towards the root, rebalancing as needed.
	// Take care of parent pointers
	AVLTree::Node* curr3_parent = curr3->parent;

	while (curr3->isRoot() != 1) {
		curr3 = rebalance(curr3);		
		
		curr3_parent = curr3_parent->parent;
		curr3 = curr3->parent;
	}

	// We are now at the root, balance once more (no parent pointers to worry about)
	root = rebalance(root);
	cout << "Success!" << endl << endl;

	return;
}


int AVLTree::size() const {return num_elems;}


AVLTree::Node* AVLTree::getEnd() const {return end;}


AVLTree::Node* AVLTree::getRoot() const {return root;}


// Print each node using preorder traversal
void AVLTree::preOrderPrint(AVLTree::Node* n, int indent) {
	if (n != NULL) {
		for (int i = 0; i < indent; i++) {
			cout << "    ";
		}

		if (n->isExternal()) {
			cout << "L (" << n->height << ")"<< endl;	
		} else {
			cout << n->key << " (" << n->height << ")" << endl;
		}

		preOrderPrint(n->left, indent + 1);
		preOrderPrint(n->right, indent + 1);
	}

	return;
}


// Print sequence using inorder traversal
void AVLTree::inOrderPrint(AVLTree::Node* n) {
	if (n != NULL && n->isExternal() != 1) {
		inOrderPrint(n->left);
		cout << n->key << " ";
		inOrderPrint(n->right);
	}

	return;
}


void AVLTree::print() {
	cout << "Printing AVL Tree: " << endl << endl;
	preOrderPrint(root, 0);
	cout << endl << endl;
	return;
}