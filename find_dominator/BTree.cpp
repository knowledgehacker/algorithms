#include "BTree.h"
#include <iostream>
#include <sstream>

// BNode implementation
BNode::BNode(const int value) {
	this->value = value;
	this->lchild = 0;
	this->rchild = 0;
}

BNode::~BNode() {
	this->lchild = 0;
	this->rchild = 0;
}

// BTree implementation
BTree::BTree() : root(0) {
}

void BTree::pre_traverse() const {
	pre_traverse(root);
	std::cout<<std::endl;
}

void BTree::pre_traverse(const BNode* node) const {
	std::cout<<node->value<<" ";

	if(node->lchild != 0)
		pre_traverse(node->lchild);

	if(node->rchild != 0)
		pre_traverse(node->rchild);
}

void BTree::in_traverse() const {
	in_traverse(root);
	std::cout<<std::endl;
}

void BTree::in_traverse(const BNode* node) const {
	if(node->lchild != 0)
		in_traverse(node->lchild);

	std::cout<<node->value<<" ";

	if(node->rchild != 0)
		in_traverse(node->rchild);
}

void BTree::post_traverse() const {
	post_traverse(root);
	std::cout<<std::endl;
}

void BTree::post_traverse(const BNode* node) const {
	if(node->lchild != 0)
		post_traverse(node->lchild);

	if(node->rchild != 0)
		post_traverse(node->rchild);

	std::cout<<node->value<<" ";
}

void BTree::insert(const int data) throw(BTreeException) {
	if(root == 0) {
		root = new BNode(data);
		return;
	}

	BNode* parent = 0;
	BNode* curr = root;
	while(1) {
		while(curr != 0) {
			if(curr->value == data) {
				std::stringstream ss;
				ss<<data;
				throw BTreeException("Node with data " + ss.str() + " already exists.");
			}

			if(curr->value < data)
				break;

			parent = curr;
			curr = curr->lchild;
		}
		if(curr == 0) {
			parent->lchild = new BNode(data);
			break;
		}
		else {
			if(curr->rchild == 0) {
				curr->rchild = new BNode(data);
				break;
			}else {
				parent = curr;
				curr = curr->rchild;
			}
		}
	}	
}

void BTree::remove(const int data) throw(BTreeException) {
	BNode* target_node = root;
	while(target_node != 0) {
		int value = target_node->value;
		if(value == data)
			break;

		if(value > data)
			target_node = target_node->lchild;
		else
			target_node = target_node->rchild;
	}
	
	// no node with data "data" found
	if(target_node == 0) {
		std::stringstream ss;
		ss<<data;

		throw BTreeException("BTree::remove - Node with data " + ss.str() + " not exists.");
	}
	std::cout<<"target_node: "<<target_node->value<<std::endl;

	// replace the target node with the node with maximum data in the left subtree
	if(target_node->lchild != 0) {
		BNode* max_node_parent = target_node;
		BNode* max_node = target_node->lchild;
		while(max_node->rchild != 0) {
			max_node_parent = max_node;
			max_node = max_node->rchild;
		}
		std::cout<<"max_node: "<<max_node->value<<std::endl;

		max_node_parent->rchild = max_node->lchild;
		target_node->value = max_node->value;
		
		return;
	}

	// replace the target node with the node with minimum data in the right subtree
	if(target_node->rchild != 0) {
		BNode* min_node_parent = target_node;
		BNode* min_node = target_node->rchild;
		while(min_node->lchild != 0) {
			min_node_parent = min_node;
			min_node = min_node->lchild;
		}
		std::cout<<"min_node: "<<min_node->value<<std::endl;

		min_node_parent->lchild = min_node->rchild;
		target_node->value = min_node->value;

		return;	
	}

	// the target node is the node to remove
	delete target_node;
}

BNode* BTree::dominator(const int data1, const int data2) throw(BTreeException) {
	std::stack<BNode*> node_chain1;
	std::stack<BNode*> node_chain2;

	find_node_chain(node_chain1, data1);
	find_node_chain(node_chain2, data2);

	int depth_diff = node_chain1.size() - node_chain2.size();
	if(depth_diff > 0)
		return common(node_chain1, node_chain2, depth_diff);
	else
		return common(node_chain2, node_chain1, -depth_diff);
}

void BTree::find_node_chain(std::stack<BNode*>& node_chain, const int data) throw(BTreeException) {
	node_chain.push(root);

	BNode* tmp = root;
	while(tmp != 0) {
		int value = tmp->value;
		if(value == data)
			return;
		
		tmp = value > data ? tmp->lchild : tmp->rchild;
		node_chain.push(tmp);
	}

	std::stringstream ss;
	ss<<data;
	throw BTreeException("Node with data " + ss.str() + " does not exist.");
}

BNode* BTree::common(std::stack<BNode*>& node_chain1, std::stack<BNode*>& node_chain2, int depth_diff)const {
	while(depth_diff-- > 0)
		node_chain1.pop();

	while(!node_chain1.empty()) {
		BNode* node1 = node_chain1.top();
		BNode* node2 = node_chain2.top();
		if(node1->value == node2->value)
			return node1;

		node_chain1.pop();	
		node_chain2.pop();	
	}

	return 0;
}

BTree::~BTree() {
	if(root != 0)
		destroyTree(root);	
}

void BTree::destroyTree(BNode* subtree) {
	if(subtree->lchild != 0)
		destroyTree(subtree->lchild);

	if(subtree->rchild != 0)
		destroyTree(subtree->rchild);

	if(subtree != 0)
		delete subtree;
}
