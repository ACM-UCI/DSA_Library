def gcd(a: int, b: int):
    return a if b == 0 else gcd(b, a%b)
