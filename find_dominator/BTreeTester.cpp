#include "BTree.h"
#include <ctime>
#include <cstdlib>
#include <iostream>

void test_insert(BTree& btree, const int* data_set, const int data_set_size) {
	for(int i = 0; i < data_set_size; ++i) {
		try {
			btree.insert(data_set[i]);
		}catch(BTreeException& bte) {
			std::cerr<<bte.what()<<std::endl;
		}
	}

	/*
	btree.pre_traverse();
	btree.in_traverse();
	btree.post_traverse();
	*/
}

void test_insert_non_duplicate_data(BTree& btree) {
	int data_set[] = {23, 57, 76, 12, 90, 6, 88, 35, 99, 50, 45};
	int data_set_size = sizeof(data_set)/sizeof(int);

	test_insert(btree, data_set, data_set_size);
}

void test_insert_duplicate_data(BTree& btree) {
	int data_set[] = {23, 57, 76, 12, 90, 6, 88, 35, 99, 76, 50, 45};
	int data_set_size = sizeof(data_set)/sizeof(int);

	test_insert(btree, data_set, data_set_size);
}

void test_remove_data(BTree& btree, const int data) {
	test_insert_non_duplicate_data(btree);
	try {
		btree.remove(data);
	}catch(BTreeException& bte) {
		std::cerr<<bte.what()<<std::endl;
	}

	btree.pre_traverse();
	btree.in_traverse();
	btree.post_traverse();
}

void test_remove_data_exists(BTree& btree) {
	//int data = 35;
	int data = 57;
	test_remove_data(btree, data);
}

void test_remove_data_non_exists(BTree& btree) {
	int data = 5;
	test_remove_data(btree, data);
}

int test_find_dominator(BTree& btree, const int data1, const int data2) {
    test_insert_non_duplicate_data(btree);
    
    // the dominator should be 57
	BNode* dominator = 0;
    try {
        dominator = btree.dominator(data1, data2);
    }catch(BTreeException& bte) {
        std::cerr<<bte.what()<<std::endl;

		return -1;
    }
    
	return dominator != 0 ? dominator->value : -1;
}

void test_find_dominator_with_data_non_exists(BTree& btree) {
	int data1 = 45;
	int data2 = 33;
	int dominator = test_find_dominator(btree, data1, data2);
	std::cout<<"dominator is "<<dominator<<", expected -1"<<std::endl;
}

bool test_find_dominator_with_data_exists(BTree& btree) {
	int data1 = 45;
	int data2 = 88;
	int dominator = test_find_dominator(btree, data1, data2);
	std::cout<<"dominator is "<<dominator<<", expected 57"<<std::endl;
}

int main(int argc, char** argv) {
	/*
	BTree bt1;
	test_insert_duplicate_data(bt1);

	BTree bt2;
	test_insert_non_duplicate_data(bt2);

	BTree bt3;
	test_find_dominator_with_data_exists(bt3);

	BTree bt4;
	test_find_dominator_with_data_non_exists(bt4);
	*/

	BTree bt4;
	test_remove_data_exists(bt4);

	BTree bt5;
	test_remove_data_non_exists(bt5);

	return 0;
}
