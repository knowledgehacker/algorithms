#include <vector>
#include <iostream>

/*
 * Cm_k selects k elements from first m ones of total n elements.
 */
// C(m, k) = C(m-1, k-1) + C(m, k-1)
std::vector<bool*> Cm_k(int k, int m, int n){ 
	std::vector<bool*> selectionList;
	if(m < k)
		return selectionList;
	if(m == k){
		bool* selection = new bool[n];
		for(int i = 0; i < n; ++i)
			selection[i] = false;
		
		for(int i = 0; i < m; ++i)
			selection[i] = true;
		selectionList.push_back(selection);

		return selectionList;
	}
	
	if(k == 1){
		for(int i = 0; i < m; ++i){
			bool* selection = new bool[n];
			for(int j = 0; j < n; ++j)
				selection[j] = false;

			selection[i] = true;
			selectionList.push_back(selection);
		}

		return selectionList;
	}
			
	selectionList = Cm_k(k-1, m-1, n);
	int selectionNum = selectionList.size();
	for(int j = 0; j < selectionNum; ++j)
		selectionList[j][m-1] = true;
	
	std::vector<bool*> subSelectionList = Cm_k(k, m-1, n);
	int subSelectionNum = subSelectionList.size();
	for(int j = 0; j < subSelectionNum; ++j)
		selectionList.push_back(subSelectionList[j]);

	return selectionList;
}

void releaseSelectionList(std::vector<bool*> selectionList){
	int selectionNum = selectionList.size();
	for(int i = 0; i < selectionNum; ++i)
		delete []selectionList[i];
}

int main(){
	int k, n;
	// C(n, k)
	std::cin>>n>>k;

	std::vector<bool*> selectionList = Cm_k(k, n, n);
	int selectionNum = selectionList.size();
	for(int i = 0; i < selectionNum; ++i){
		bool* selection = selectionList[i];
		for(int j = 0; j < n; ++j)
			if(selection[j])
				std::cout<<j+1<<" ";
		std::cout<<std::endl;
	}
	releaseSelectionList(selectionList);

	return 0;
}

