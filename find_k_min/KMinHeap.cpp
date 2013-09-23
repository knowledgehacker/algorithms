#include "KMinHeap.h"

#include <new>
#include <iostream>

template<typename DataType>
KMinHeap<DataType>::KMinHeap(const DataType* const data_area, int size): _size(size) {
	try {
		_data_area = new DataType[_size];
	}catch(std::bad_alloc except) {
		// TODO: handle except
		std::cout<<"bad_alloc exception caught!"<<std::endl;

		return;
	}

	for(int i = 0; i < _size; ++i)
		_data_area[i] = data_area[i];

	build();
}

template<typename DataType>
bool KMinHeap<DataType>::insert(const DataType& data) {
	if(data > _data_area[0])
		return false;

	_data_area[0] = data;
	adjust_top_down(0);

	return true;
}

template<typename DataType>
bool KMinHeap<DataType>::exists(const DataType& data)const {
	if(data == _data_area[0])
		return true;

	int pos = 1;
	while(pos < _size) {
		if((pos+1) < _size) {
			if((_data_area[pos] == data) || (_data_area[pos+1] == data))
				return true;

			int b_pos, s_pos;
			if(_data_area[pos] < _data_area[pos+1]) {
				b_pos = pos+1;
				s_pos = pos;
			}else {
				b_pos = pos;
				s_pos = pos+1;
			}

			if(_data_area[b_pos] < data)
				return false;
			
			if(_data_area[s_pos] < data)
				pos = 2 * b_pos + 1;
			else
				pos = 2 * s_pos + 1;
		}else {
			if(_data_area[pos] == data)
				return true;
			
			if(_data_area[pos] < data)
				return false;
			
			pos = 2 * pos + 1;
		}
	}
	
	return false;	
}

template<typename DataType>
bool KMinHeap<DataType>::remove(const DataType& data) {
	// TODO: implement it
}

template<typename DataType>
DataType& KMinHeap<DataType>::get(const int idx)const {
	return _data_area[idx];
}

template<typename DataType>
KMinHeap<DataType>::~KMinHeap() {
	if(_data_area != 0) {
		delete[] _data_area;
		_data_area = 0;

		_size = 0;
	}
}

template<typename DataType>
void KMinHeap<DataType>::build() {
	int last_adjust_idx = _size/2;
	for(int i = 0; i < last_adjust_idx; ++i)
		adjust_top_down(i);
}

template<typename DataType>
bool KMinHeap<DataType>::adjust_top_down(const int idx) {
	int curr = idx;
	int child = curr * 2 + 1;
	if(child >= _size)
		return false;

	while(child < _size) {
		if(((child+1) < _size) && (_data_area[child+1] > _data_area[child]))
			++child;

		if(_data_area[child] <= _data_area[curr])
			break;

		DataType tmp = _data_area[curr];
		_data_area[curr] = _data_area[child];
		_data_area[child] = tmp;

		curr = child;
		child = curr * 2 + 1;
	}
}
