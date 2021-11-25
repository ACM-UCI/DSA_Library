import functools, operator

def extended_euclid(a, b): # ax + bx = 1
	if b == 0:
		return 1, 0
	k = a // b
	x, y = extended_euclid(b, a % b)
	return y, x - k * y

def inverse_mod(a, m): # a = 1 (mod m)
	b, x = extended_euclid(a, m)
	return b % m

def chinese_remainder_theorem(a: [int], m: [int]): # x = a (mod m)
	z, y = [], [],
	product = functools.reduce(operator.mul, m, 1)
	x = 0
	for ai, mi in zip(a, m):
		zi = product//mi
		yi = inverse_mod(zi, mi)
		x = (x + ai*yi*zi) % product
	return x
