def lcm(a: int, b: int):
    return a * (b // gcd(a,b))
