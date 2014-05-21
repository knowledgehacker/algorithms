#include<climits>
#include<cstdio>

static const int MAX_CANDIDATE_NUM = 10;

// forward declaration
void permutate(int data[], int idx[], int k, int n);

// permutate indexes of the arry
void permutate_all(int data[], int n) {
	int* idx = new int[n];
	for(int i = 0; i < n; ++i)
		idx[i] = i;

	permutate(data, idx, 0, n);

	delete[] idx;
}

void permutate(int data[], int idx[], int k, int n) {
	bool c[MAX_CANDIDATE_NUM];
	int candidate_num = n;

	if(k == n) {
		for(int i = 0; i < k; ++i)
			printf("%d ", data[idx[i]]);
		printf("\n");
		return;
	}

	for(int i = 0; i < candidate_num; ++i)
		c[i] = false;
	for(int i = 0; i < k; ++i)
		c[idx[i]] = true;

	for(int i = 0; i < candidate_num; ++i) {
		if(c[i] == false) {
			idx[k] = i;
			permutate(data, idx, k+1, n);
		}
	}
}

int main(int argc, char** argv) {
	int data[] = {8, 9, 5};
	permutate_all(data, sizeof(data)/sizeof(int));
}
