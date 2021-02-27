from functools import reduce

def extended_euclid(a, b): # ax + bx = 1
	if b == 0:
		return 1, 0
	k = a // b
	x, y = euclid(b, a % b, show_work)
	return y, x - k * y

def chinese_remainder_theorem(a: [int], m: [int]): # x = a (mod m)
	n = len(a)
	z, y = [], [],
	product = reduce(lambda x, y : x*y, m, 1)
	for i, x in enumerate(m):
		z.append(product//x)
	for (i, (zi, mi)) in enumerate(zip(z, m)):
		y.append(invert(zi, mi))
	x = 0
	for i in range(n):
		x += a[i]*y[i]*z[i]
	return x % product

def inverse_mod(a, m): # a = 1 (mod m)
	b, x = euclid(a, m, show_work)
	return b % m

def modexp(a, b, m): # a^b (mod m)
	assert(b >= 0)
	if b <= 1:
		return a % m if b else 1
	rec = modexp(a, b//2, m, show_work) % m
	ans = rec**2 * (a if b%2 else 1) % m
	return ans

