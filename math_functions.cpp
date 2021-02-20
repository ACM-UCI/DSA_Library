#include <stdio.h>
#include <cmath>

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
	
	// ===== Begin Sums ===== //
	// All bounds in this section are start inclusive and end exclusive
	

	// This is the equivalent to python's sum(i for i in range(start, end, step))
	// Requirements:
	// 	- start < end
	// 	- step >= 0
	// If you want to sum with negative step, flip sum around and do with positive step
	long long arithmetic_sum(long long start, long long end, long long step) {
		long long n = 1+(end-start-1)/step;
		long long ans;
		switch (n&1) {
			case 0:
				// even
				ans = (2*start + (n-1)*step)*(n>>1);
				break;
			case 1:
				// odd
				ans = (start + ((n-1)>>1)*step)*n;
				break;
		}
		return ans;
	}

	// Geometic sum on two finite bounds
	// Requirements:
	// 	- start < end
	double geometric_sum(int start, int end, double a) {
		return (std::pow(a, start) - std::pow(a, end))/(1.0 - a);
	}

	// Geometric sum with finite start and infinite end
	// Requirements:
	// 	- |a| < 1
	double geometric_sum(int start, double a) {
		return (std::pow(a, start))/(1.0-a);
	}

	// sum from k=0 to infinity of k*(a**k)
	double geometric_sum_scaled(double a) {
		return a/((1-a)*(1-a));
	}
	// ===== End Sums ===== //
	
	// ===== Begin Linear Algebra ===== //
	template<typename T>
	struct Vector3D {
		T x,y,z;

		T dotProduct(const Vector3D<T>& v) const {
			return x*v.x + y*v.y + z*v.z;
		}

		Vector3D<T> crossProduct(const Vector3D<T>& v) const {
			return Vector3D{ y*v.z - z*v.y, z*v.x - x*v.z, x*v.y - y*v.x };
		}

		Vector3D<T> scale(T amt) const {
			return Vector3D{x*amt, y*amt, z*amt};
		}

		T ccw(const Vector3D<T>& v) const {
			return x*v.y - y*v.x;
		}

		T magnitudeSquared() const {
			return x*x + y*y + z*z;
		}

		double magnitude() const {
			return std::sqrt(magnitudeSquared());
		}

		double angleBetween(const Vector3D<T>& v) const {
			std::acos(dotProduct(v)/(magnitude() + v.magnitude()));
		}

		// finds projection of this onto v
		Vector3D<double> projectionOnto(const Vector3D<T>& v) const {
			double amt = ((double) dotProduct(v))/(v.magnitudeSquared());
			return Vector3D<double>{amt*v.x, amt*v.y, amt*v.z};
		}

		Vector3D<double> getUnitVector() const {
			double mag = magnitude();
			return Vector3D<double>{x/mag, y/mag, z/mag};
		}

		Vector3D<T> operator+(const Vector3D<T>& v) const {
			return Vector3D{ x+v.x, y+v.y, z+v.z };
		}

		Vector3D<T> operator-(const Vector3D<T>& v) const {
			return Vector3D{ x-v.x, y-v.y, z-v.z };
		}


		// This does radial sort
		// Only works for vectors in 2D
		bool operator<(const Vector3D<T>& v) const {
			T res = ccw(v);
			T a = ccw(Vector3D{1,0,0});
			T b = v.ccw(Vector3D{1,0,0});

			if ((a < 0 && b < 0) || (a > 0 && b > 0)) {
				if (res == 0) {
					T lenA = magnitudeSquared();
					T lenB = v.magnitudeSquared();

					if (y == 0 && v.y == 0) {
						// edge case to handle
						return x < v.x;
					}
					
					if (a > 0) {
						return lenA < lenB;
					} else {
						return lenA > lenB;
					}
				} else {
					return res > 0;
				}
			} else if (a < 0) {
				return true;
			} else {
				return false;
			}
		}

	};
	// ===== End Linear Algebra ===== //
}

int main() {
	
	return 0;
}
