// Let adj be a NxN matrix where adj[u][v] is initially the
//  weight of edge u -> v
//  adj[u][v] will be INFTY if no edge exists
for (int k = 0; k < N; ++k) {
    for (int u = 0; u < N; ++u) {
        for (int v = 0; v < N; ++v) {
            if (adj[u][k] != INFTY && adj[k][v] != INFTY) {
                adj[u][v] = std::min(adj[u][v], adj[u][k]+adj[k][v]);
            }
        }
    }
}
// At this point adj[u][v] will be the cost of the shortest
//  path from u to v
//  If no path exists it will be INFTY
