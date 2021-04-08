#include <vector>
#include <algorithm>
template <typename T>
std::vector<std::vector<T>> combinations(std::vector<T> arr, int k) {
	std::vector<bool> inset(arr.size());
	std::fill(inset.begin()+std::max(0, (int)arr.size()-k), inset.end(), 1);
	std::vector<std::vector<T>> ans;
	do {
		ans.push_back({});
		for (int i = 0; i < arr.size(); ++i)
			if (inset[i])
				ans.back().push_back(arr[i]);
	} while(std::next_permutation(inset.begin(), inset.end()));
	return ans;
}
