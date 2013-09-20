#include<string>
#include<vector>
#include<iostream>

std::vector<std::string> p_all(const std::string& seq, int n) {
	std::vector<std::string> seqs;
	if(n == 1) {
		seqs.push_back(std::string(1, seq[0]));

		return seqs;
	}

	std::vector<std::string> sub_seqs = p_all(seq, n-1);
	for(std::vector<std::string>::iterator iter = sub_seqs.begin(); iter != sub_seqs.end(); ++iter) {
		std::string sub_seq = *iter;
		seqs.push_back(seq[n-1] + sub_seq);
		for(int i = 1; i < n-1; ++i)
			seqs.push_back(sub_seq.substr(0, i) + seq[n-1] + sub_seq.substr(i, n-1-i));
		seqs.push_back(sub_seq + seq[n-1]);
	}

	return seqs;
}

int main() {
	std::string seq = "abc";
	std::vector<std::string> seqs = p_all(seq, seq.length());
	for(std::vector<std::string>::iterator iter = seqs.begin(); iter != seqs.end(); ++iter)
		std::cout<<*iter<<std::endl;

	return 0;
}
	
