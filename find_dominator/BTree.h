#ifndef _B_TREE_H_
#define _B_TREE_H_

#include "BTreeException.h"
#include <stack>

class BNode {
public:
	int value;
	BNode* lchild;
	BNode* rchild;

public:
	BNode(const int value);
	~BNode();
};

class BTree {
private:
	BNode* root;

public:
	BTree();

	void pre_traverse() const;
	void in_traverse() const;
	void post_traverse() const;
	void insert(const int data) throw(BTreeException);
	void remove(const int data) throw(BTreeException);
	BNode* dominator(const int data1, const int data2) throw(BTreeException);

	~BTree();

private:
	void pre_traverse(const BNode* node) const;
	void in_traverse(const BNode* node) const;
	void post_traverse(const BNode* node) const;
	BNode* common(std::stack<BNode*>& node_chain1, std::stack<BNode*>& node_chain2, int deepth_diff) const;
	void find_node_chain(std::stack<BNode*>& node_chain, const int data) throw(BTreeException);
	void destroyTree(BNode* subtree);
};

#endif
