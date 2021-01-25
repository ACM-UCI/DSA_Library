#include <vector>
#include <algorithm>
std::vector<int> lis_nlogn(const std::vector<int> &nums) {
	std::vector<int> dp, bptr(nums.size(), -1), ans;
	for (int i = 0; i < nums.size(); ++i) {
		int l = 0, r = dp.size();
		while (l < r) {
			int m = l + (r-l) / 2;
			if (nums[dp[m]] >= nums[i])
				r = m;
			else
				l = m + 1;
		}
		if (l == dp.size())
			dp.push_back(i);
		else if (nums[i] < nums[dp[l]])
			dp[l] = i;
		bptr[i] = l ? dp[l-1] : -1;
	}
	for (int ptr = dp.back(); ptr != -1; ptr = bptr[ptr])
		ans.push_back(nums[ptr]);
	std::reverse(ans.begin(), ans.end());
	return ans;
}
