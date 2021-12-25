int modulo(int a, int b) {
    const int res = a%b;
    return res >= 0 ? res : res + b;
}
