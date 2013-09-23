#ifndef _FINDER_H_
#define _FINDER_H_

#include "Point.h"
#include "KMinHeap.h"

class DistInfo {
private:
	int _idx;
	double _dist;

public:
	DistInfo();
	DistInfo(const int idx, const Point& center, const Point point);
	DistInfo(const DistInfo& distInfo);
	inline int getIdx() const;
	inline double getDist() const;
	DistInfo& operator=(const DistInfo& distInfo);
	friend bool operator>(const DistInfo& lvalue, const DistInfo& rvalue);
	friend bool operator<(const DistInfo& lvalue, const DistInfo& rvalue);
	friend bool operator>=(const DistInfo& lvalue, const DistInfo& rvalue);
	friend bool operator<=(const DistInfo& lvalue, const DistInfo& rvalue);
	friend bool operator==(const DistInfo& lvalue, const DistInfo& rvalue);
	friend bool operator!=(const DistInfo& lvalue, const DistInfo& rvalue);
};

class Finder {
private:
	const Point _center;
	const Point* _points;
	int _k, _n;
	KMinHeap<DistInfo>* _heap;

public:
	// We assume "points" do not contain point "center", which always is not the case
	Finder(const Point center, const Point* points, int k, int n);
	void run();
	~Finder();

private:
	void print() const;
};

#endif
