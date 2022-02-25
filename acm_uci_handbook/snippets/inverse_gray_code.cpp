int rev_g(int g) {
    int n = 0;
    for (; g; g >>= 1) { n ^= g; }
    return n;
}
