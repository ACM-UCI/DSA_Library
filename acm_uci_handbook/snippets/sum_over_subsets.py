from copy import copy

S = copy(A)
for i in range(N):
    for mask in range(1<<N):
        if mask & (1<<i):
            S[mask] += S[mask^(1<<i)]

