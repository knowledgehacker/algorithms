#include "BinarySearchTree.h"

void BinarySearchTree::postOrderNonRecursively1() {
	BinaryNode* lastVisited = 0;
	std::stack<BinaryNode*> nodes;

	BinaryNode* node = _root;
	do {
		while(node != 0 && node != lastVisited) {
			nodes.push(node);
			node = node->_left;
		}
	
		node = nodes.top();
		if(node->_right == 0 || node->_right == lastVisited) {
			// visit
			std::cout<<node->_value<<std::endl;
			nodes.pop();
			lastVisited = node;
		} else
			node = node->_right;
	} while(!nodes.empty());
}
