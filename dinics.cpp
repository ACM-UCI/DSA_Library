// As of right now this solves https://open.kattis.com/problems/maxflow 
#include <bits/stdc++.h>

typedef long long LL;

struct Edge {
	int u, v, v_index, residual_index;
	LL c;
	LL init;
};

typedef std::vector<Edge> EdgeList;
typedef std::vector<EdgeList> AdjList;
typedef std::vector<int> LevelGraph;
typedef std::vector<int> Pruner;

const LL INF = std::numeric_limits<LL>::max();

int N, M, S, T;
AdjList adj;
LevelGraph levels;
Pruner next;		// use to prune the DFS, holds the next edge to search in DFS
LL maxFlow;

void augment(Edge& e, int flow) {
	adj[e.u][e.v_index].c -= flow;
	adj[e.v][e.residual_index].c += flow;
}

LL dfs(int u, LL flow) {
	if (u == T) return flow;

	int numEdges = adj[u].size();
	for (; next[u] < numEdges; ++next[u]) {
		Edge& e = adj[u][next[u]];

		if (e.c > 0 && levels[u]+1 == levels[e.v]) {	// there is flow and goes to next level
			LL bottleNeck = dfs(e.v, std::min(flow, e.c));
			if (bottleNeck > 0) {
				// augment the edge
				augment(e, bottleNeck);
				return bottleNeck;
			}
		}
	}

	return 0;
}


// Perform a BFS to build level graph and determine whether blocking flow reached
bool bfs() {
	levels.assign(N, -1);

	std::queue<int> q;
	q.push(S);	// start at the source
	levels[S] = 0;
	while (!q.empty()) {
		int u = q.front(); q.pop();

		for (const Edge& e : adj[u]) {
			if (e.c > 0 && levels[e.v] == -1) {
				levels[e.v] = levels[u] + 1;
				q.push(e.v);
			}
		}
	}

	return levels[T] != -1;
}


void dinics() {

	maxFlow = 0;
	while (bfs()) {	// loop while there is not a blocking flow
		next.assign(N, 0);

		// dfs from source to sink until no more flow
		for (LL f = dfs(S, INF); f != 0; f = dfs(S, INF)) {
			maxFlow += f;
		}
	}
}

int main() {

	scanf("%d %d %d %d", &N, &M, &S, &T);
	adj.assign(N, EdgeList());
	for (int i = 0; i < M; ++i) {
		int u, v; LL c; scanf("%d %d %lld", &u, &v, &c);
		if (u == v) continue;

		int v_index = adj[u].size();
		int residual_index = adj[v].size();
		adj[u].push_back(Edge{u,v,v_index, residual_index,c,c});
		adj[v].push_back(Edge{v,u,residual_index,v_index,0,0});
	}

	dinics();

	EdgeList ans;
	for (int i = 0; i < N; ++i) {
		for (Edge e : adj[i]) {
			if (e.init - e.c > 0) {
				ans.push_back(e);
			}
		}
	}
	int edgeCount = ans.size();

	printf("%d %lld %d\n", N, maxFlow, edgeCount);
	for (Edge& e : ans) {
		printf("%d %d %lld\n", e.u, e.v, e.init - e.c);
	}

	return 0;
}

