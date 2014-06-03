#include<stack>
#include<map>
#include<utility>
#include<iostream>

class BinaryNode {
public:
	int _value;
	BinaryNode* _left;
	BinaryNode* _right;
	bool _visited;

public:
	BinaryNode(int value): _value(value), _left(0), _right(0), _visited(false) {
	}

	~BinaryNode() {

	}
};

class BinarySearchTree {
private:
	BinaryNode* _root;

public:
	BinarySearchTree(): _root(0) {
	}

	bool insert(int value) {
		BinaryNode* node = new BinaryNode(value);
		/*
		if(_root == 0) {
			_root = node;
			return true;
		}
		*/

		return insert(_root, node);
	}

	void preOrder() {
		preOrder(_root);
	}

	void inOrder() {
		inOrder(_root);
	}

	void postOrder() {
		postOrder(_root);
	}

	void postOrderNonRecursively() {
		std::stack<BinaryNode*> nodes;
		nodes.push(_root);

		while(!nodes.empty()) {
			BinaryNode* node = nodes.top();
			if((node->_left == 0 || node->_left->_visited == true) 
				&& (node->_right == 0 || node->_right->_visited == true)) {
				// visit node
				std::cout<<node->_value<<std::endl;
				nodes.pop();
				node->_visited = true;
			} else {
				BinaryNode* right = node->_right;
				if(right != 0) {
					nodes.push(right);
					//right->_visited = false;
				}

				BinaryNode* left = node->_left;
				if(left != 0) {
					nodes.push(left);
					//left->_visited = false;
				}
			}
		}
	}

	void postOrderNonRecursively1();

	~BinarySearchTree() {
		destroy(_root);
	}

private:
	bool insert(BinaryNode*& subtree, BinaryNode* node) {
		if(subtree == 0) {
			subtree = node;

			return true;
		}

		if(node->_value == subtree->_value)
			return false;
		else if(node->_value < subtree->_value)
			return insert(subtree->_left, node);
		else
			return insert(subtree->_right, node);

		/*
		int value = node->_value;
		if(subtree->_value == value)
			return false;
		else {
			if(value < subtree->_value) {
				if(subtree->_left != 0)
					return insert(subtree->_left, node);
				else {
					subtree->_left = node;
					return true;
				}
			} else {
				if(subtree->_right != 0)
					return insert(subtree->_right, node);
				else {
					subtree->_right = node;
					return true;
				}
			}
		}
		*/
	}

	void preOrder(BinaryNode* subtree) {
		if(subtree == 0)
			return;

		// visit
		std::cout<<subtree->_value<<std::endl;

		if(subtree->_left != 0)
			preOrder(subtree->_left);

		if(subtree->_right != 0)
			preOrder(subtree->_right);
	}

	void inOrder(BinaryNode* subtree) {
		if(subtree == 0)
			return;

		if(subtree->_left != 0)
			inOrder(subtree->_left);

		// visit
		std::cout<<subtree->_value<<std::endl;

		if(subtree->_right != 0)
			inOrder(subtree->_right);
	}

	void postOrder(BinaryNode* subtree) {
		if(subtree == 0)
			return;

		if(subtree->_left != 0)
			postOrder(subtree->_left);

		if(subtree->_right != 0)
			postOrder(subtree->_right);

		// visit
		std::cout<<subtree->_value<<std::endl;
	}

	void destroy(BinaryNode* node) {
		if(node->_left != 0)
			destroy(node->_left);

		if(node->_right != 0)
			destroy(node->_right);

		if(node != 0)
			delete node;
	}
};
