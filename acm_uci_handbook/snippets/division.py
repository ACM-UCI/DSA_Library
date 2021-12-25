def divide_modulo(a: int, b: int, mod: int):
    return (a * (pow(b, mod-2, mod) % mod)) % mod
