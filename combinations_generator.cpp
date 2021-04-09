#include <vector>
#include <algorithm>
template <typename T>
class Combinations {
public:
	class Iterator {
		const std::vector<T> values;
		std::vector<bool> inactive;
		bool finished;
	public:
		Iterator (const std::vector<T> values, size_t k, bool finished = false)
				: values{values}, inactive(values.size(), 1), finished{finished} {
			std::fill(inactive.begin(), inactive.begin() + k, 0);
		}
		std::vector<T> operator*() {
			std::vector<T> combination;
			for (size_t i = 0; i < values.size(); ++i)
				if (!inactive[i])
					combination.push_back(values[i]);
			return combination;
		}
		Iterator &operator++() {
			if (!finished)
				finished = !std::next_permutation(inactive.begin(), inactive.end());
			return *this;
		};
		bool operator!=(const Iterator& other) { return other.finished != finished; }
	};
	Combinations(std::vector<T> values, size_t k) : values{values}, k{k} {}
	Iterator begin() { return Iterator(values, std::min(values.size(), k)); }
	Iterator end() { return Combinations::endingIterator; }
private:
	size_t k;
	std::vector<T> values;
	static Iterator endingIterator;
};
template <typename T>
typename Combinations<T>::Iterator Combinations<T>::endingIterator({}, 0, true);

// #include <iostream>
// int main() {
// 	for (auto comb : Combinations<int>({1, 2, 3}, 2)) {
// 		for(auto x : comb)
// 			std::cout << x << " ";
// 		std::cout << std::endl;
// 	}
// 	auto combinations = Combinations<int>({1, 2, 3}, 2);
// 	for (auto it = combinations.begin(); it != combinations.end(); ++it) {
// 		for(auto x : *it)
// 			std::cout << x << " ";
// 		std::cout << std::endl;
// 	}
// }
