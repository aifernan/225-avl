// avltree.hpp
// Antonio Fernandez
// 301393610

#include <string>
using namespace std;

class EmptyTreeException {
public:
	EmptyTreeException(string err);
	~EmptyTreeException();
	string getError();

private:
	string errMsg;
};

class AVLTree {
public:
	class Node;
	friend class AVLTree::Node;

	class Node {
	public:
		Node* parent;
		Node* left;
		Node* right;
		int key;
		int height;

		Node(int k = -1, int h = 0); // Default to make it an external node
		~Node();
		void setKey(int k);
		void setHeight(int h);
		bool isExternal();
		bool isRoot();
	};

	AVLTree();
	~AVLTree();

	void destruct(Node* n);
	Node* find(int k) const;

	int max(int x, int y);
	Node* right_rotate(Node* n);
	Node* left_rotate(Node* n);
	Node* rebalance(Node* curr);
	
	Node* put(int k);
	void erase(int k)
		throw (EmptyTreeException);
	int size() const;
	bool empty() const;
	Node* getEnd() const;
	Node* getRoot() const;
	void preOrderPrint(Node* n, int indent);
	void inOrderPrint(Node* n);
	void print();


private:
	Node* end;
	Node* root;
	int num_elems;
};