#include "Finder.h"
#include "KMinHeap.cpp"
#include <iostream>
#include <cmath>

DistInfo::DistInfo(): _idx(-1), _dist(-1.0) {
}

DistInfo::DistInfo(const int idx, const Point& center, const Point point): _idx(idx) {
	int diffX = point.getX() - center.getX();
	int diffY = point.getY() - center.getY();
	_dist = sqrt(diffX * diffX + diffY * diffY);
}

DistInfo::DistInfo(const DistInfo& distInfo) {
	_idx = distInfo._idx;
	_dist = distInfo._dist;
}

int DistInfo::getIdx() const {
	return _idx;
}

double DistInfo::getDist() const {
	return _dist;
}

DistInfo& DistInfo::operator=(const DistInfo& distInfo) {
	_idx = distInfo._idx;
	_dist = distInfo._dist;

	return *this;
}

bool operator>(const DistInfo& lvalue, const DistInfo& rvalue) {
	return lvalue._dist > rvalue._dist;	
}

bool operator<(const DistInfo& lvalue, const DistInfo& rvalue) {
	return lvalue._dist < rvalue._dist;
}

bool operator>=(const DistInfo& lvalue, const DistInfo& rvalue) {
	return lvalue._dist >= rvalue._dist;
}

bool operator<=(const DistInfo& lvalue, const DistInfo& rvalue) {
	return lvalue._dist <= rvalue._dist;
}

bool operator==(const DistInfo& lvalue, const DistInfo& rvalue) {
	return lvalue._dist == rvalue._dist;
}

bool operator!=(const DistInfo& lvalue, const DistInfo& rvalue) {
	return lvalue._dist != rvalue._dist;
}

// We assume "points" do not contain point "center", which always is not the case
Finder::Finder(const Point center, const Point* points, int k, int n): _center(center), _points(points), _k(k), _n(n) {
	DistInfo* distInfos = new DistInfo[_k];
	for(int i = 0; i < _k; ++i) {
		DistInfo distInfo(i, _center, _points[i]);
		distInfos[i] = distInfo;
	}
	_heap = new KMinHeap<DistInfo>(distInfos, _k);
}

void Finder::run() {
	for(int i = _k; i < _n; ++i) {
		DistInfo distInfo(i, _center, _points[i]);
		_heap->insert(distInfo);
	}

	print();
}

void Finder::print()const {
	for(int i = 0; i < _k; ++i) {
		DistInfo distInfo = _heap->get(i);
		std::cout<<_points[distInfo.getIdx()]<<" ";
	}
	std::cout<<std::endl;
}

Finder::~Finder() {
	if(_heap != 0) {
		delete _heap;
		_heap = 0;
	}
}

