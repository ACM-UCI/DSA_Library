int pow(int b, int k, int mod) {
    if (k == 0) return 1 % mod;
    else if (k == 1) return b % mod;
    else {
        int res = pow(b, k/2, mod);
        return (((res*res)%mod) * ((k%2 ? b : 1)%mod))%mod;
    }
}
