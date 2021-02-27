#include <iostream>
#include <vector>
#include <functional>
std::vector<std::vector<int>> tarjanSCC(std::vector<std::vector<int>> &adj) {
	int n = adj.size(), clock = 0;
	std::vector<int> low(n), dis(n); // 'dis'covery time and 'low'est node reachable
	std::vector<int> has(n), stk; // 'has' checks if 'stk' has a node
	std::vector<std::vector<int>> sccs; // holds a list of sccs with their nodes
	std::function<void (int)> dfs = [&](int u) {
		dis[u] = low[u] = ++clock;
		stk.push_back(u);
		has[u] = true;
		for (int v : adj[u]) {
			if (!dis[v])
				dfs(v);
			if (has[v]) // On the stack means found lower
				low[u] = std::min(low[u], low[v]);
		}
		if (low[u] == dis[u]) { // No path to low nodes, so it's the cutoff for an SCC
			sccs.push_back({});
			while (true) {
				int v = stk.back();
				stk.pop_back();
				has[v] = false;
				sccs.back().push_back(v);
				if (u == v)
					break;
			}
		}
	};
	for (int u = 0; u < adj.size(); ++u) // assumes zero indexed
		if (!dis[u])
			dfs(u);
	return sccs;
}
