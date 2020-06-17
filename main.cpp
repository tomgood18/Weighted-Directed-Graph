#include "directed_graph.hpp"

int main() {
    directed_graph<double> g1;

	vertex<double> a(0, 800); 
	vertex<double> b(1, 3000);
	vertex<double> c(2, 400);
	vertex<double> d(3, 710);
	vertex<double> e(4, 221);


	g1.add_vertex(a);
	g1.add_vertex(b);
	g1.add_vertex(c);
	g1.add_vertex(d);
	g1.add_vertex(e);
	

	//g1.remove_vertex(1);

    vector<vertex<double>> vertex_list = g1.get_vertices();
	cout << "all vertices: ";
	for (vertex<double> vt : vertex_list) {
	 	cout << "(" << vt.id << ", " << vt.weight << ") ";
	}
	cout << endl;

	// g1.add_edge(0, 1, 6);
	// g1.add_edge(1, 2, 9);
	// g1.add_edge(2, 3, 3);
	// g1.add_edge(3, 4, 4);

    // g1.add_edge(0, 1, 6);
	// g1.add_edge(0, 2, 9);
	// g1.add_edge(1, 4, 3);
	// g1.add_edge(2, 3, 4);
	// g1.add_edge(3, 2, 7);
	// g1.add_edge(3, 4, 5);
	// g1.add_edge(3, 0, 1);

	g1.add_edge(0, 1, 6);
	g1.add_edge(0, 3, 9);
	g1.add_edge(0, 2, 3);
	g1.add_edge(1, 0, 3);
	g1.add_edge(1, 4, 3);
	g1.add_edge(3, 1, 7);
	g1.add_edge(3, 6, 5);
	g1.add_edge(4, 3, 5);
	g1.add_edge(4, 5, 5);
	g1.add_edge(5, 4, 5);
	g1.add_edge(5, 6, 5);
	g1.add_edge(6, 0, 5);

	cout << "all neighbours of 0: ";
	vector<vertex<double>> neighbour_list = g1.get_neighbours(0);
	for (vertex<double> nb : neighbour_list) {
	 	cout << "(" << nb.id << ", " << nb.weight << ") ";
		
	}
	cout << "Number of neighbours: " << neighbour_list.size();
	cout << endl;

	cout << "all second neighbours of 0: ";
	vector<vertex<double>> second_neighbour_list = g1.get_second_order_neighbours(0);
	for (vertex<double> snb : second_neighbour_list) {
	 	cout << "(" << snb.id << ", " << snb.weight << ") ";
		
	}
	cout << "Number of second neighbours: " << second_neighbour_list.size();
	cout << endl;

	int x = 2;
	cout << "Breadth first search for " << x << ": ";
	vector<vertex<double>> breadth_first = g1.breadth_first(x);
	for(vertex<double> bf : breadth_first){
		cout << "(" << bf.id << ", " << bf.weight << ") ";
	}
	cout << endl;

	cout << "Depth first search for " << x << ": ";
	vector<vertex<double>> depth_first = g1.depth_first(x);
	for(vertex<double> df : depth_first){
		cout << "(" << df.id << ", " << df.weight << ") ";
	}
	cout << endl;


	// if (g1.num_vertices() == 5){
    //     cout << "num_vertices() likely correct" << ", " << g1.num_vertices() << endl;
    // } else {
    //     cout << "incorrect; something wrong with add_vertex() or num_vertices()" << ", " << g1.num_vertices() << endl;
    // }

	// if (g1.num_edges() == 7){
    //     cout << "num_edges() likely correct" << ", " << g1.num_edges() << endl;
    // } else {
    //     cout << "incorrect; something wrong with num_edges()" << ", " << g1.num_edges() << endl;
    // }

	// if (g1.adjacent(0, 1)) {
	// 	cout << "Adjacent!";
	// } else {
	// 	cout << "Not adjacent!";
	// }
	// cout << "\n";

	// for(int i = 0; i<5; i++){
	int i = 3;
	cout << "Vertex with ID " << i << " has " << g1.out_degree(i) << " out_degree values" << "\n";
	cout << "Vertex with ID " << i << " has " << g1.in_degree(i) << " in_degree values" << "\n";
	cout << "Vertex with ID " << i << " has " << g1.degree(i) << " degree values" << "\n";
	// }

	if (g1.reachable(0, 3)) {
		cout << "Reachable!";
	} else {
		cout << "Not Reachable!";
	}

	cout << "\n";

	if(g1.contain_cycles()){
		cout << "Contains a cycle";
	} else {
		cout << "Doesn't contain a cycle";
	}



	

	

}