int divide_modulo(int a, int b, int mod) {
    return (a * (pow(b, mod-2, mod) % mod)) % mod;
}
