#ifndef DIRECTED_GRAPH_H
#define DIRECTED_GRAPH_H

#include<iostream>
#include<string>
#include<vector>
#include<queue>
#include <list> 
#include <stack>
// include more libraries here if you need to

using namespace std; // the standard namespace are here just in case.

/*
	the vertex class
*/
template <typename T>
class vertex {

public:
	int id;
	T weight;
	vertex(int x, T y) : id(x), weight(y) {}

	// add more functions here if you need to
};

/*
	the graph class
*/
template <typename T>
class directed_graph {

private:

	vector<vector<T>> adj_matrix; // adj_matrix[u_id][v_id] = the weight for edge (u_id, u_id)

	// vertex_weights stores all vertices in the graph, as well as the vertices' weights
	vector<T> vertex_weights; // vertex_weights[u_id] stores the weight of vertex u_id

	//You will need to add some data members here
	//to actually represent the graph internally,
	//and keep track of whatever you need to.

public:

// For video:	- Talk about implementing 'get_vertices' for all functions that needed them before realising ability to remove 'const' keyword for cleaner code
//				- 



	directed_graph(); //A constructor for directed_graph. The graph should start empty.
	~directed_graph(); //A destructor. Depending on how you do things, this may not be necessary.

	bool contains(const int&) const; //Returns true if the graph contains the given vertex_id, false otherwise. - DONE
	bool adjacent(const int&, const int&) const; //Returns true if the first vertex is adjacent to the second, false otherwise. - DONE

	void add_vertex(const vertex<T>&); //Adds the passed in vertex to the graph (with no edges). - DONE
	void add_edge(const int&, const int&, const T&); //Adds a weighted edge from the first vertex to the second. - DONE

	void remove_vertex(const int&); //Removes the given vertex. Should also clear any incident edges. - DONE
	void remove_edge(const int&, const int&); //Removes the edge between the two vertices, if it exists. - DONE

	size_t in_degree(const int&) const; //Returns number of edges coming in to a vertex. - DONE
	size_t out_degree(const int&) const; //Returns the number of edges leaving a vertex. - DONE
	size_t degree(const int&) const; //Returns the degree of the vertex (both in edges and out edges). - DONE

	size_t num_vertices(); //Returns the total number of vertices in the graph. - DONE
	size_t num_edges(); //Returns the total number of edges in the graph. - DONE

	vector<vertex<T>> get_vertices(); //Returns a vector containing all the vertices. - DONE
	vector<vertex<T>> get_neighbours(const int&); //Returns a vector containing all the vertices reachable from the given vertex. The vertex is not considered a neighbour of itself. - DONE
	vector<vertex<T>> get_second_order_neighbours(const int&); // Returns a vector containing all the second_order_neighbours (i.e., neighbours of neighbours) of the given vertex. - DONE
															  // A vector cannot be considered a second_order_neighbour of itself.
	bool reachable(const int&, const int&) ; //Returns true if the second vertex is reachable from the first (can you follow a path of out-edges to get from the first to the second?). Returns false otherwise. - DONE
	bool contain_cycles() ; // Return true if the graph contains cycles (there is a path from any vertices directly/indirectly to itself), false otherwise. - DONE

	vector<vertex<T>> depth_first(const int&); //Returns the vertices of the graph in the order they are visited in by a depth-first traversal starting at the given vertex. - DONE
	vector<vertex<T>> breadth_first(const int&); //Returns the vertices of the graph in the order they are visisted in by a breadth-first traversal starting at the given vertex. - DONE

	directed_graph<T> out_tree(const int&); //Returns a spanning tree of the graph starting at the given vertex using the out-edges. This means every vertex in the tree is reachable from the root. - ATTEMPTED

	vector<vertex<T>> pre_order_traversal(const int&, directed_graph<T>&); // returns the vertices in the visiting order of a pre-order traversal of the minimum spanning tree starting at the given vertex.
	vector<vertex<T>> in_order_traversal(const int&, directed_graph<T>&); // returns the vertices in the visiting order of an in-order traversal of the minimum spanning tree starting at the given vertex.
	vector<vertex<T>> post_order_traversal(const int&, directed_graph<T>&); // returns the vertices in ther visitig order of a post-order traversal of the minimum spanning tree starting at the given vertex.

	vector<vertex<T>> significance_sorting(); // Return a vector containing a sorted list of the vertices in descending order of their significance.

};

// Define all your methods down here (or move them up into the header, but be careful you don't double up). If you want to move this into another file, you can, but you should #include the file here.
// Although these are just the same names copied from above, you may find a few more clues in the full method headers.
// Note also that C++ is sensitive to the order you declare and define things in - you have to have it available before you use it.

template <typename T>
directed_graph<T>::directed_graph() {
	adj_matrix.resize(100); // Step 1: create an array of the size 100

	for(int i=0; i<adj_matrix.size(); i++){
		adj_matrix[i].resize(100); // Step 2: define each array element as an array of the size 100
									// til now, we get a matrix (array of arrays) of the size 100*100
		
		for(int j=0; j<adj_matrix[i].size(); j++){ // Step 3: initialise an empty graph that contains no edges
			adj_matrix[i][j] = 0; // 0 indicates there is no edge from i to j in the graph
		}
	}

	// initialise the matrix to contain no vertex
	vertex_weights.resize(100); // Step 1: creat an array of the size 100. Therefore, the graph can contain at most 100 vertices.
	for(int i=0; i<vertex_weights.size(); i++){ // Step 2: initilise an empty graph that contains no vertices
		vertex_weights[i] = 0;  // 0 indicate the vertex with the id of i is not in the graph 
	}
}

template <typename T>
directed_graph<T>::~directed_graph() {}

template <typename T>
bool directed_graph<T>::contains(const int& u_id) const { 
	if (vertex_weights[u_id] != 0){ // suppose a valid vertex_weight should be a non-zero numeric 
		return true;
	}
	return false;
}

template <typename T>
bool directed_graph<T>::adjacent(const int& u_id, const int& v_id) const { 
	bool adjacent;
	if(contains(u_id) && contains(v_id)){
		if (adj_matrix[u_id][v_id] > 0) {
			adjacent = true;
		} else {
			adjacent = false;
		}
	}
	return adjacent;
 }

template <typename T>
void directed_graph<T>::add_vertex(const vertex<T>& u) {
	vertex_weights[u.id] = u.weight; // to add a vertex to the graph, simply give a non-zero weight to the array index indicated by the vertex_id
}

template <typename T>
void directed_graph<T>::add_edge(const int& u_id, const int& v_id, const T& weight) {
	if(contains(u_id) && contains(v_id)){ // Step 1: check if the vertices are in the graph
		adj_matrix[u_id][v_id] = weight; // Step 2: to add an edge, simply give a non-zero weight to the corresponding cell of adj_matrix
	}
}

template <typename T>
void directed_graph<T>::remove_vertex(const int& u_id) {
	if (contains(u_id)){
		vertex_weights[u_id] = 0; // to remove a vertex, simply set its weight to zero
	}
	
}

template <typename T>
void directed_graph<T>::remove_edge(const int& u_id, const int& v_id) {
	if(contains(u_id) && contains(v_id)){ // Step 1: check if the vertices are in the graph
		adj_matrix[u_id][v_id] = 0; // Step 2: to delete an edge, simply give a zero to the corresponding cell of adj_matrix
	}
}

template <typename T>
size_t directed_graph<T>::in_degree(const int& u_id) const { 
	size_t in_counter = 0;
	if (contains(u_id)){
		for(int i = 0; i < vertex_weights.size(); i++) {
			if (adj_matrix[i][u_id] != adj_matrix[i][(vertex_weights.size() + 1)]){
				++in_counter;
			}
		}
	}
	return in_counter;
}

template <typename T>
size_t directed_graph<T>::out_degree(const int& u_id) const { 
	size_t degree;
	vector<vertex<T>> result;
	if(contains(u_id)){ // Step 1: first make sure the vertex is in the graph
		for (int i=0; i<adj_matrix[u_id].size(); i++){
			if(adj_matrix[u_id][i] > 0){ // Step 2: check if there is an edge from the given vertex to every other vertex
				result.push_back(vertex<T>(i, vertex_weights[i])); // if yes, add the other vertex to the result
			}
		}
	}
	return result.size();
}

template <typename T>
size_t directed_graph<T>::degree(const int& u_id) const { 
	size_t size;
	if(contains(u_id)){
		size_t out_size = out_degree(u_id);
		size_t in_size = in_degree(u_id);
		size = out_size + in_size;
	}
	
	return size; 
}

template <typename T>
size_t directed_graph<T>::num_vertices() {
	vector<vertex<T>> vertice_list = get_vertices();
	return vertice_list.size(); 
}

template <typename T>
size_t directed_graph<T>::num_edges() { 
	vector<vertex<T>> vertice_list = get_vertices();
	vector<vertex<T>> result;
	
	for (vertex<T> v : vertice_list) {
		for (int i=0; i<adj_matrix[v.id].size(); i++){
			if(adj_matrix[v.id][i] > 0){ // Step 2: check if there is an edge from the given vertex to every other vertex
				result.push_back(vertex<T>(i, vertex_weights[i])); // if yes, add the other vertex to the result
			}
		}
	}
	return result.size();
}

template <typename T>
vector<vertex<T>> directed_graph<T>::get_vertices() {
	vector<vertex<T>> vertice_list;

	for(int i=0; i<vertex_weights.size(); i++){ // Step 1: get the ids of all vertices in the graph
		if (vertex_weights[i] > 0){
			vertice_list.push_back(vertex<T>(i, vertex_weights[i])); // Step 2: build a vertex class for each vertex_id
		}
	}
	
	return vertice_list; // return a vector of vertex classes
}

template <typename T>
vector<vertex<T>> directed_graph<T>::get_neighbours(const int& u_id) {
	vector<vertex<T>> result;

	if(contains(u_id)){ // Step 1: first make sure the vertex is in the graph
		for (int i=0; i<adj_matrix[u_id].size(); i++){
			if(adj_matrix[u_id][i] > 0){
				if (i != u_id) // Step 2: check if there is an edge from the given vertex to every other vertex
				{
					result.push_back(vertex<T>(i, vertex_weights[i])); // if yes, add the other vertex to the result
				}
				
			}
		}
	}

	return result;
}

template <typename T>
vector<vertex<T>> directed_graph<T>::get_second_order_neighbours(const int& u_id) { 
	vector<vertex<T>> first_orders = get_neighbours(u_id);
	vector<vertex<T>> second_orders;
	vector<vertex<T>> results;
	bool is_duplicate = false;
	bool is_first_neighbour;
	if(contains(u_id)){
		for (auto x: first_orders) {
			
			for (int i=0; i<adj_matrix[x.id].size(); i++){
				is_duplicate = false;
				if(adj_matrix[x.id][i] > 0){ 
					if(i != u_id) {
						for(auto v : second_orders){ // check if the current results contain this vertex id
							if (v.id == i){
								is_duplicate = true; // j already exists in results
								break;
							}
						}
						if (!is_duplicate ){
							second_orders.push_back(vertex(i, vertex_weights[i])); // only add the vertex when it is not in the current results
						}
					}
				}
			}
		}
	}
	return second_orders; 
}

template <typename T>
bool directed_graph<T>::reachable(const int& u_id, const int& v_id)  { 
	if (contains(u_id) && contains(v_id)) {
		vector<vertex<T>> dfs = depth_first(u_id);
		for (auto x : dfs) {
			if (x.id == v_id){
				return true;
			}
		}
	}
	return false;
}

template <typename T>
bool directed_graph<T>::contain_cycles() { 
	vector<vertex<T>> vertice_list = get_vertices();
	for (auto x : vertice_list){
		vector<vertex<T>> x_neighbours = get_neighbours(x.id);
		for (auto y : x_neighbours) {
			if(reachable(y.id, x.id)){
				return true;
			}
		}
	}
	return false; 
}

template <typename T>	//	-	Talk about changing from using ordered to just implementing.
vector<vertex<T>> directed_graph<T>::depth_first(const int& u_id)  { 
	vector<vertex<T>> result;
	bool visited[vertex_weights.size()];
	for (unsigned i = 0; i < vertex_weights.size(); i++){
		visited[i] = false;
	}
	stack<int> unprocessed;
	unprocessed.push(u_id);
	while (!unprocessed.empty()){
		int n = unprocessed.top();
		unprocessed.pop();
		if (!visited[n]){
			visited[n] = true;
			result.push_back(vertex<T>(n, vertex_weights[n]));
			for (unsigned i = vertex_weights.size(); i != 0; i--){
				if (adj_matrix[n][i-1]){
					unprocessed.push(i-1);
				}
			}
		}
	}
	return result;
}


template <typename T>	//	-	Talk about changing from using ordered to just implementing.
vector<vertex<T>> directed_graph<T>::breadth_first(const int& u_id) { 
	vector<vertex<T>> result;
	bool visited[vertex_weights.size()];
	for (unsigned i = 0; i < vertex_weights.size(); i++){
		visited[i] = false;
	}
	queue<int> unprocessed;
	unprocessed.push(u_id);
	while (!unprocessed.empty()){
		int n = unprocessed.front();
		unprocessed.pop();
		if (!visited[n]){
			visited[n] = true;
			result.push_back(vertex<T>(n, vertex_weights[n]));
			for (unsigned i = 0; i < vertex_weights.size(); i++){
				if (adj_matrix[n][i]){
					unprocessed.push(i);
				}
			}
		}
	}
	return result;	
}

template <typename T>
directed_graph<T> directed_graph<T>::out_tree(const int& u_id) { 
	directed_graph<T> tree;
	bool visited[vertex_weights.size()];
	for (unsigned i = 0; i < vertex_weights.size(); i++){
		visited[i] = false;
	}
	queue<pair<int,int>> unprocessed;
	unprocessed.push({u_id, u_id});
	while (!unprocessed.empty()){
		pair<int, int> n = unprocessed.front();
		unprocessed.pop();
		if (!visited[n.first]){
			visited[n.first] = true;
			tree.add_edge(n.first, n.second, adj_matrix[n.first][n.second]); 
			for (unsigned i = 0; i < vertex_weights.size(); i++){
				if (adj_matrix[n.first][i]){
					unprocessed.push({i, n.first});
				}
			}
		}
	}
	return tree;
}

template <typename T>
vector<vertex<T>> directed_graph<T>::pre_order_traversal(const int& u_id, directed_graph<T>& mst) { return vector<vertex<T>>(); }

template <typename T>
vector<vertex<T>> directed_graph<T>::in_order_traversal(const int& u_id, directed_graph<T>& mst) { return vector<vertex<T>>(); }

template <typename T>
vector<vertex<T>> directed_graph<T>::post_order_traversal(const int& u_id, directed_graph<T>& mst) { return vector<vertex<T>>(); }

template <typename T>
vector<vertex<T>> directed_graph<T>::significance_sorting() { return vector<vertex<T>>(); }

#endif