#include <iostream>
#include <vector>


std::vector<bool> sieve(int max_prime) {
    std::vector<bool> primes(max_prime+1, true);
    primes[0] = primes[1] = false;

    for (int i = 4; i <= max_prime; i+=2)
        primes[i] = false;

    for (int i = 3; i <= max_prime; i+=2) if (primes[i])
        for (int j = i*2; j <= max_prime; j+=i)
            primes[j] = false;

    return primes;
}


int main() {

    int N = 5000;
    std::vector<bool> ans = sieve(N);

    std::cout << 2;
    int i = 3;
    int r = 1;

    while (i <= N) {
        if (ans[i]) {
            std::cout << "," << i;

            if (++r == 15) {
                std::cout << "\n";
                r = 0;
            }
        } 
        ++i;
    }


    return 0;
}
