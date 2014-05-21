#include<climits>
#include<cstdio>

static const int NON_EXIST = INT_MIN;

// forward declaration
void construct_subsets(int a[], int k, int n);

void construct_all_subsets(int a[], int n) {
	construct_subsets(a, 0, n);
}

void construct_subsets(int a[], int k, int n) {
	int c[2];
	int candidate_num = 2;

	if(k == n) {
		for(int i = 0; i < k; ++i)
			if(a[i] != NON_EXIST)
				printf("%d ", a[i]);
		printf("\n");
		return;
	}

	c[0] = NON_EXIST;
	c[1] = a[k];
	for(int i = 0; i < candidate_num; ++i) {
		a[k] = c[i];
		construct_subsets(a, k+1, n);
	}
}

int main(int argc, char** argv) {
	int a[] = {8, 9, 5};
	construct_all_subsets(a, sizeof(a)/sizeof(int));
}
