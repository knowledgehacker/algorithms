#include "BinarySearchTree.h"

int main(int argc, char** argv) {
	BinarySearchTree bst;
	bst.insert(9);
	bst.insert(7);
	bst.insert(11);
	bst.insert(4);
	bst.insert(5);
	bst.insert(10);
	bst.insert(15);
	
	// pre order traverse
	std::cout<<"pre order:"<<std::endl;
	bst.preOrder();

	// post order traverse
	std::cout<<"post order:"<<std::endl;
	bst.postOrder();

	std::cout<<"post order non recursive:"<<std::endl;
	bst.postOrderNonRecursively1();

	//system("pause");

	return 0;
}
