#include <vector>
#include <unordered_map>
#include <cmath>
long long totient(long long a) {
	//if you have used sieve to precompute primes
	//use #define PRECOMPUTED
	//make sure the array storing the primes is names "primes"
	//sieve must go to primes larger than or equal to a
	//   (in case a is a prime)

	#ifdef PRECOMPUTED
	//O(logn) complexity
	long long output{};
	for(int i{}; i < primes.size(); ++i){
		int counter{};
		while(a%primes[i] == 0){
			a /= primes[i];
			if(counter)
				count *= primes[i];
			else
				counter = 1;
		}
		if(counter == 0)
			continue;
		if(output)
			output *= counter*(primes[i]-1)
		else
			output = counter*(primes[i]-1);
	}
	return output;
	#endif
	#ifndef PRECOMPUTED
	//O(sqrt(n)) complexity

	long long output{};
	long long counter{};
	while(a%2 == 0){
		a /= 2;
		if(counter)
			counter *= 2;
		else
			counter = 1;
	}
	if(counter != 0){
		output = counter;
	}
	for(int i=3; i < (long long)std::sqrt(a); i += 2){
		counter = 0;
		while(a%i == 0){
			a /= i;
			if(counter)
				counter *= i;
			else
				counter = 1;
		}
		if(counter == 0)
			continue;
		if(output)
			output *= counter*(i-1);
		else
			output = counter * (i-1);
	}
	if(a != 1){
		if(output)
			output *= a-1;
		else
			output = a-1;
	}
	return output;
	#endif
}
