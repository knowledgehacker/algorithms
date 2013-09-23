#ifndef _K_MIN_HEAP_H_
#define _K_MIN_HEAP_H_

template<typename DataType>
class KMinHeap {
private:
	DataType* _data_area;
	int _size;

public:
	KMinHeap(const DataType* const data_area, int size);
	bool insert(const DataType& data);
	bool exists(const DataType& data)const;
	bool remove(const DataType& data);
	DataType& get(const int idx)const;

    ~KMinHeap();

private:
	void build();
	bool adjust_top_down(const int idx);	
};

#endif
