
Struct Edge {
	int v;	// the destination vertice
	int w;	// the weight of the edge
};

typedef std::vector<Edge> EdgeList;	
typedef std::vector<EdgeList> AdjList;	// Type for adjacency lists.
										// If you have graph g represented as an adjacency list, g[u] = list of all edges with source of u
const INFINITY = std::numeric_limits<int>::max();

void bellmanFord(AdjList& adj, std::vector<int>& dist, int source, int dest) {

	dist.assign(adj.size(), INFINITY);

}
