#include<limits.h>
#include<stdio.h>

typedef struct bound_tag {
	int start;
	int end;
} Bound;

/*
Bound mcs(int* sequence, int size, int* max_value) {
	if(size == 0) {
		Bound bound = {-1, -1};
		return bound;
	}

	return max_contiguous_subsequence(sequence, 0, size, max_value);
}
*/

Bound max_contiguous_subsequence(int* sequence, int start, int end, int* max_value) {
	Bound bound;
	if((end-start) == 1) {
		bound.start = start;
		bound.end = end;

		*max_value = sequence[start];

		return bound;
	}

	if(sequence[end-1] <= 0)
		return max_contiguous_subsequence(sequence, start, end-1, max_value);
	else {
		Bound sub_max_bound;
		int sub_max_value = INT_MIN;
		int i = start;
		while(i < end-1) {
			int j;
			for(j = i; (j < end-1) && (sequence[j] <= 0); ++j);
			if(j < end-1) {
				int sub_value = INT_MIN;
				Bound sub_bound = max_contiguous_subsequence(sequence, j, end-1, &sub_value);
				if(sub_value > sub_max_value) {
					sub_max_bound = sub_bound;
					sub_max_value = sub_value;
				}
			}

			i = j+1;
		}

		bound = sub_max_bound;
		*max_value = sub_max_value;

		int value = 0;
		int k;
		for(k = bound.end; k < end; ++k)
			value += sequence[k];

		if(value > 0) {
			bound.end = end;
			*max_value += value;
		}
	}

	return bound;
}

int main(int argc, char** argv) {
	int max_value = INT_MIN;
	int sequence[] = {-3, 8, -5, -2, 3, 4, -6, 7, 9, 2, 3, -2, 4, -1};
	//int sequence[] = {-5, 3, 4, -6, 7};
	int sequenceNum = sizeof(sequence)/sizeof(int);
	int i;
	for(i = 0; i < sequenceNum; ++i)
		printf("%d ", sequence[i]);
	printf("\n");

	Bound bound = max_contiguous_subsequence(sequence, 0, sequenceNum, &max_value);
	//Bound bound = mcs(sequence, sequenceNum, &max_value);
	printf("max_value: %d, [%d, %d]\n", max_value, bound.start, bound.end);

	return 0;
}
