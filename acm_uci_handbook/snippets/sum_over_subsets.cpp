// Initialize S array
for (int i = 0; i < (1<<N); ++i)
    S[i] = A[i];

for (int i = 0; i < N; ++i) for (int mask = 0; mask < (1<<N); ++mask)
    if (mask & (1<<i))
        S[mask] += S[mask^(1<<i)];
