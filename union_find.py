def find(u):
	if u not in parent: # parent is a dictionary
		parent[u] = u
	path = []
	while u != parent[u]:
		path.append(u)
		u = parent[u]
	for v in path:
		parent[v] = u
	return u

def union(u, v):
	if find(u) == find(v):
		return False # No union
	parent[find(u)] = find(v) # Can optimize by tracking rank or size
	return True # successful union
