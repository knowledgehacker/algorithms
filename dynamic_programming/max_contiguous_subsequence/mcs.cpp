#include<climits>
#include<iostream>
#include<vector>
#include<utility>

typedef struct result {
	int start;
	int end;
	
	int max_value;
} Result;

// forward declaration
void sub_mcs(int* sequence, int size, int start, Result& result);

void mcs(int* sequence, int size, Result& result) {
	if(size == 0) {
		result.start = -1;
		result.end = -1;
		result.max_value = INT_MIN;

		return;
	};

	Result sub_result;
	std::vector<Result> sub_results;
	int start = 0;
	do {
		while(start < size) {
			if(sequence[start] > 0)
				break;
			++start;
		}

		sub_mcs(sequence, size, start, sub_result);
		sub_results.push_back(sub_result);

		while((start < size) && (sequence[start++] > 0));
	} while(start < size);


	int idx = 0;
	int max_value = sub_results[0].max_value;
	for(int i = 1; i < sub_results.size(); ++i) {
		int value = sub_results[i].max_value;
		if(value > max_value) {
			max_value = value;
			idx = i;
		}
	}

	result = sub_results[idx];
}

void sub_mcs(int* sequence, int size, int start, Result& result) {
	int max_value = 0;
	int end = start;
	while(end < size) {
		while(end < size) {
			if(sequence[end] <= 0)
				break;

			max_value += sequence[end];
			++end;
		}
		
		int sum = 0;
		int j = end;
		while(j < size) {
			sum += sequence[j];
			if(sum > 0)
				break;

			++j;
		}
		if(j < size) {
			max_value += sum;
			end = j+1;
		} else
			break;
	}
	
	result.start = start;
	result.end = end;
	result.max_value = max_value;
}

int main(int argc, char** argv) {
    //int sequence[] = {-5, 4, -6, 3};
    int sequence[] = {-3, 8, -5, -2, 3, 4, -6, 7, 9, 2, 3, -2, 4, -1};
    int sequenceNum = sizeof(sequence)/sizeof(int);
	for(int i = 0; i < sequenceNum; ++i)
		std::cout<<sequence[i]<<" ";
	std::cout<<std::endl;

	Result result;
	mcs(sequence, sequenceNum, result);
	std::cout<<"max_value: "<<result.max_value<<", ["<<result.start<<", "<<result.end<<"]"<<std::endl;

	return 0;
}
