#include<iostream>
#include<vector>

class Node {
public:
	int _to;
	double _value;
	Node* _next;

	Node(int to, double value) {
		_to = to;
		_value = value;

		_next = 0;
	}
}; 

class Graph {
private:
	int _vertex_num;
	Node** _node_list;

public:
	Graph(const int vertex_num) : _vertex_num(vertex_num) {
		_node_list = new Node*[vertex_num];
		for(int i = 0; i < vertex_num; ++i)
			_node_list[i] = 0;
	}

	void print() {
		for(int i = 0; i < _vertex_num; ++i) {
			std::cout<<i<<"->";
			Node* head = _node_list[i];
			while(head != 0) {
				std::cout<<"("<<head->_to<<", "<<head->_value<<")";

				head = head->_next;
			}
			std::cout<<std::endl;
		}
	}

	// we do not check whether the edge already exists in the graph or not
	void insert(int from, int to, double value) {
		Node* node = new Node(to, value);
		if(_node_list[from] == 0)
			_node_list[from] = node;
		else {
			node->_next = _node_list[from]->_next;
			_node_list[from]->_next = node;
		}
	}

	bool remove(int from, int to) {
		if(_node_list[from] == 0)
			return false;

		Node* prev = 0;
		Node* curr = _node_list[from];
		while(curr != 0) {
			if(curr->_to == to)
				break;

			prev = curr;
			curr = curr->_next;
		}
		if(curr == 0)
			return false;

		prev->_next = curr->_next;
		curr->_next = 0;
		delete curr;

		return true;
	}


	void depth_first_traverse() {
		bool* visited = new bool[_vertex_num];
		for(int i = 0; i < _vertex_num; ++i)
			visited[i] = false;
	
		// depth first traverse begging from vertex "0"
		dfs(0, visited);

		delete[] visited;
	}

	void dfs(int vertex, bool* visited) {
		Node* head = _node_list[vertex];
		if(head == 0) {
			//visit(vertex);
			std::cout<<vertex<<std::endl;

			return;
		}

		//visit(vertex);
		std::cout<<vertex<<std::endl;

		for(Node* curr = head; curr != 0; curr = curr->_next) {
			int vertex = curr->_to;
			if(!visited[vertex]) {	
				visited[vertex] = true;
				dfs(vertex, visited);
			} 
		}
	}

	// find paths "from --> to" in the graph which does not contain any loop
	void find_paths(int from, int to) {
		std::vector<int> path;
		find_paths(from, to, path, 0);
	}

	void find_paths(int curr, int to, std::vector<int> path, const int path_length) {
		if(curr == to) {
			for(int i = 0; i < path_length; ++i)
				std::cout<<path[i]<<"->";
			std::cout<<to<<std::endl;

			return;
		}

		path.push_back(curr);
		Node* head = _node_list[curr];
		while(head != 0) {
			find_paths(head->_to, to, path, path_length+1);
			head = head->_next;
		}
	}

	~Graph() {
		Node* tmp = 0;
		for(int i = 0; i < _vertex_num; ++i) {
			Node* curr = _node_list[i];
			while(curr != 0) {
				tmp = curr->_next;
				delete curr;
				curr = tmp;
			}
		}
	}
};

int main(int argc, char** argv) {
	Graph graph(7);
	graph.insert(0, 1, 0+1);
	graph.insert(0, 2, 0+2);
	graph.insert(1, 3, 1+3);
	graph.insert(1, 4, 1+4);
	graph.insert(1, 6, 1+6);
	graph.insert(3, 5, 3+5);
	graph.insert(4, 5, 4+5);
	graph.insert(5, 2, 5+2);
	graph.insert(5, 6, 5+6);
	graph.insert(6, 2, 6+2);
	graph.print();
	std::cout<<"----------"<<std::endl;

	std::cout<<"1-->2:"<<std::endl;
	graph.find_paths(1, 2);
	std::cout<<"1-->0:"<<std::endl;
	graph.find_paths(1, 0);

	std::cout<<"depth first traverse:"<<std::endl;
	graph.depth_first_traverse();

	return 0;
}	
