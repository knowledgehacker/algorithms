#include<vector>
#include<iostream>

std::vector<int*> permutation_construct(int n, int k) {
	std::vector<int*> seqs;
	if(k == 1) {
		for(int i = 0; i < n; ++i) {
			int* seq = new int[n];
			for(int j = 0; j < n; ++j)
				seq[j] = -1;
			seq[i] = 0;

			seqs.push_back(seq);
		}

		return seqs;
	}

	std::vector<int*> sub_seqs = permutation_construct(n, k-1);
	for(std::vector<int*>::iterator iter = sub_seqs.begin(); iter != sub_seqs.end(); ++iter) {
		int* sub_seq = *iter;
		/*
		std::cout<<"sub_seq: ";
		for(int i = 0; i < n; ++i)
			std::cout<<sub_seq[i]<<" ";
		std::cout<<std::endl;
		*/

		int seq_cnt = 0;	
		int idx = 0;
		while(seq_cnt++ < (n-(k-1))) {
			int* seq = new int[n];
			for(int i = 0; i < n; ++i)
				seq[i] = sub_seq[i];

			for(int i = idx; i < n; ++i) {
				if(sub_seq[i] == -1) {
					seq[i] = k-1;
					idx = i+1;

					break;
				}
			}

			/*			
			std::cout<<"seq: ";
			for(int i = 0; i < n; ++i)
				std::cout<<seq[i]<<" ";
			std::cout<<std::endl;
			*/

			seqs.push_back(seq);	
		}
	}

	return seqs;
}

void permutation_destroy(std::vector<int*>& seqs) {
	for(std::vector<int*>::iterator iter = seqs.begin(); iter != seqs.end(); ++iter)
		delete[] *iter;
}

int main() {
	int n, k;
	std::cout<<"n: ";
	std::cin>>n;
	std::cout<<"k: ";
	std::cin>>k;

	std::vector<int*> seqs = permutation_construct(n, k);

	int seq_cnt = 0;
	for(std::vector<int*>::iterator iter = seqs.begin(); iter != seqs.end(); ++iter) {
		int* seq = *iter;
		for(int i = 0; i < n; ++i)
			if(seq[i] != -1)
				std::cout<<"("<<i+1<<": "<<seq[i]+1<<"), ";
		std::cout<<std::endl;
	
		++seq_cnt;
	}
	std::cout<<"seq_cnt: "<<seq_cnt<<std::endl;

	permutation_destroy(seqs);

	return 0;
}
	
