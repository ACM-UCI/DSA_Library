#include <vector>
#include <unordered_map>
long long totient(long long a) {
	class delayedPropagationEratosthenes{
		public:
			std::unordered_map<long long, std::vector<long long>> nums;
			long long currentNum;
			delayedPropagationEratosthenes(){
				currentNum = 2;
			}
			long long getNext(){
				while(nums.count(currentNum)){
					for(long long i = 0; i < nums[currentNum].size(); ++i){
						nums[currentNum + nums[currentNum][i]].push_back(nums[currentNum][i]);
					}
					nums.erase(currentNum);
					currentNum++;
				}
				return currentNum++;
			}
	};
	delayedPropagationEratosthenes sieve = delayedPropagationEratosthenes();
	long long output{};
	while(a != 1 && a != -1){
		long long prime = sieve.getNext();
		long long counter{};
		while(a % prime == 0){
			a /= prime;
			if(counter)
				counter *= prime;
			else
				counter = 1;
		}
		if(!counter)
			continue;
		if(output)
			output *= counter * (prime-1);
		else
			output = counter * (prime-1);
	}
	return output;
}
