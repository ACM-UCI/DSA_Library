
namespace math {

	// ===== Begin Modulo ===== //
	// - Returns a % b, works in the case that a is negative
	long long modulo(long long a, long long b) {
		const long long result = a%b;
		return result >= 0 ? result : result+b;
	}

	long modulo(long a, long b) {
		const long result = a%b;
		return result >= 0 ? result : result + b;
	}

	int modulo(int a, int b) {
		const int result = a%b;
		return result >= 0 ? result : result + b;
	}
	// ===== End Modulo ===== //

	// ===== Begin Power ===== //
	long long pow(long long b, long long k, long long mod) {
		if (k == 0) return 1 % mod;
		else if (k == 1) return b % mod;
		else {
			long long res = pow(b, k/2, mod) % mod;
			return (((res*res)%mod) * (k%2 ? b : 1)) % mod;
		}
	}
	// ===== End Power ===== //
	
	// ===== Begin Division Under Modulo ===== //
	// mod must be a prime number for this function to work
	// 	- common prime numbers you will find include 1,000,000,007
	long long divide_modulo(long long a, long long b, long long mod) {
		return (a * (math::pow(b, mod-2, mod) % mod)) % mod;
	}
	// ===== End Division Under Modulo ===== //

	// ===== Begin GCD ===== //
	long long gcd(long long a, long long b) {
		return b == 0 ? a : gcd(b, a%b);
	}

	long gcd(long a, long b) {
		return b == 0 ? a : gcd(b, a%b);
	}

	int gcd(int a, int b) {
		return b == 0 ? a : gcd(b, a%b);
	}
	// ===== End GCD ===== //

	// ===== Begin LCM ===== //
	long long lcm(long long a, long long b) {
		return a * (b / gcd(a,b));
	}

	long lcm(long a, long b) {
		return a * (b / gcd(a,b));
	}

	int lcm(int a, int b) {
		return a * (b / gcd(a,b));
	}
	// ===== End LCM ===== //
}
