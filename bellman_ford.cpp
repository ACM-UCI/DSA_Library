#include <vector>

// ========== FOR THE USER TO DEFINE ========== //
typedef int WeightType;					// by default all edge weight computations will use integers
const WeightType INFINITY = 1e9;		// by default a path of infinite cost will be 1e9
const WeightType NEG_INFINITY = -1e9;	// by default a negative weight of infinite value is -1e9
// ============================================ //



// GRAPH ABSTRACTION ==========================
struct Edge {
	int v;	// the destination vertice
	WeightType w;	// the weight of the edge
};

typedef std::vector<Edge> EdgeList;	
typedef std::vector<EdgeList> AdjList;	// Type for adjacency lists.
										// If you have graph g represented as an adjacency list, g[u] = list of all edges with source of u
typedef std::vector<WeightType> Costs;	// the return type of the bellmanFord() function, defines SSSP between source and all nodes
// END GRAPH ABSTRACTION ======================


// From a single source returns a Costs vector containing the cost of the shortest path to all nodes. If unreachable will be INFINITY. 
// If reachable through negative cycle will be NEG_INFINITY.
Costs bellmanFord(AdjList& adj, int source) {
	
	Costs dists(adj.size(), INFINITY);
	dists[source] = 0;	// SSSP to source is 0
	for (int i = 0; i < adj.size()-1; ++i) {
		for (int u = 0; u < adj.size(); ++u) {
			for (int j = 0; j < adj[u].size(); ++j) {
				Edge& e = adj[u][j];
				if (dists[u] != INFINITY) 
					dists[e.v] = std::min(dists[e.v], dists[u] + e.w);
			}
		}
	}

	// Check for Negative Cycles
	for (int i = 0; i < adj.size(); ++i) {	// This outer loop is required to determine which nodes have a -INFINITY path
											// You can remove this loop if you only wish to find the existence of negative cycles, in which case just check for one dists[i]==NEG_INFINITY
		for (int u = 0; u < adj.size(); ++u) {
			for (int j = 0; j < adj[u].size(); ++j) {
				Edge& e = adj[u][j];
				if (dists[u] != INFINITY && dists[e.v] > dists[u] + e.w) {
					dists[e.v] = NEG_INFINITY;
				}
			}
		}
	}

	return dists;
}
