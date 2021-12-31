# Let adj be a NxN matrix where adj[u][v] is initially the
#  weight of edge u -> v
#  adj[u][v] will be INFTY if no edge exists
for k in range(N):
    for u in range(N):
        for v in range(N):
            if adj[u][k] != INFTY and adj[k][v] != INFTY:
                adj[u][v] = min(adj[u][v], adj[u][k]+adj[k][v])
# At this point adj[u][v] will be the cost of the shortest
#  path from u to v
#  If no path exists it will be INFTY
