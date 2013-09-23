#ifndef _B_TREE_EXCEPTION_H_
#define _B_TREE_EXCEPTION_H_

#include <exception>
#include <string>

class BTreeException : public std::exception {
private:
	std::string except_info;

public:
	BTreeException(const std::string& what_arg) : except_info(what_arg) {
	}

	const char* what() const throw() {
		return except_info.c_str();
	}

	~BTreeException() throw() {
	}
};

#endif
