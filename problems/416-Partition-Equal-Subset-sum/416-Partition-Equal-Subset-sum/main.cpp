#include <iostream>
#include <cassert>
#include <vector>

using namespace std;

class Solution {
private:
	//memo[i][c]表示使用索引为[0...i]的这些元素，是否可以完全填充一个容量为c的背包
	//-1表示为未计算，0表示不可以填充，1表示可以填充
	vector<vector<int>> memo;

	//使用nums[0...index],是否可以完全填充一个容量为sum的背包
	bool tryPartition(const vector<int>& nums, int index, int sum) {
		if (sum == 0)
			return true;

		if (sum < 0 || index < 0)
			return false;

		if (memo[index][sum] != -1)
			return memo[index][sum] == 1;

		memo[index][sum] = (tryPartition(nums, index - 1, sum) || tryPartition(nums, index - 1, sum - nums[index])) ? 1 : 0;

		return memo[index][sum] == 1;
	}
public:
	bool canPartition(vector<int>& nums) {
		int sum = 0;
		for (int i = 0; i < nums.size(); i++) {
			assert(nums[i] > 0);
			sum += nums[i];
		}

		if (sum % 2 != 0)
			return false;

		memo = vector<vector<int>>(nums.size(), vector<int>(sum / 2 + 1, -1));
		return tryPartition(nums, nums.size() - 1, sum / 2);
	}
};